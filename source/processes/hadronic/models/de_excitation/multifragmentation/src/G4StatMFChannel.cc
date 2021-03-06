//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id$
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara
//
// Modified:
// 25.07.08 I.Pshenichnov (in collaboration with Alexander Botvina and Igor 
//          Mishustin (FIAS, Frankfurt, INR, Moscow and Kurchatov Institute, 
//          Moscow, pshenich@fias.uni-frankfurt.de) fixed semi-infinite loop 

#include <numeric>

#include "G4StatMFChannel.hh"
#include "G4PhysicalConstants.hh"
#include "G4HadronicException.hh"
#include "G4Pow.hh"

class SumCoulombEnergy : public std::binary_function<G4double,G4double,G4double>
{
public:
  SumCoulombEnergy() : total(0.0) {}
  G4double operator() (G4double& , G4StatMFFragment*& frag)
  { 
      total += frag->GetCoulombEnergy();
      return total;
  }
    
  G4double GetTotal() { return total; }
public:
  G4double total;  
};

G4StatMFChannel::G4StatMFChannel() : 
  _NumOfNeutralFragments(0), 
  _NumOfChargedFragments(0)
{}

G4StatMFChannel::~G4StatMFChannel() 
{ 
  if (!_theFragments.empty()) {
    std::for_each(_theFragments.begin(),_theFragments.end(),
		  DeleteFragment());
  }
}

G4bool G4StatMFChannel::CheckFragments(void)
{
    std::deque<G4StatMFFragment*>::iterator i;
    for (i = _theFragments.begin(); 
	 i != _theFragments.end(); ++i) 
      {
	G4int A = (*i)->GetA();
	G4int Z = (*i)->GetZ();
       	if ( (A > 1 && (Z > A || Z <= 0)) || (A==1 && Z > A) || A <= 0 ) return false;
    }
    return true;
}

void G4StatMFChannel::CreateFragment(G4int A, G4int Z)
    // Create a new fragment.
    // Fragments are automatically sorted: first charged fragments, 
    // then neutral ones.
{
    if (Z <= 0.5) {
	_theFragments.push_back(new G4StatMFFragment(A,Z));
	_NumOfNeutralFragments++;
    } else {
	_theFragments.push_front(new G4StatMFFragment(A,Z));
	_NumOfChargedFragments++;
    }
	
    return;
}

G4double G4StatMFChannel::GetFragmentsCoulombEnergy(void)
{
    G4double Coulomb = std::accumulate(_theFragments.begin(),_theFragments.end(),
					 0.0,SumCoulombEnergy());
//      G4double Coulomb = 0.0;
//      for (unsigned int i = 0;i < _theFragments.size(); i++)
//  	Coulomb += _theFragments[i]->GetCoulombEnergy();
    return Coulomb;
}



G4double G4StatMFChannel::GetFragmentsEnergy(G4double T) const
{
    G4double Energy = 0.0;
	
    G4double TranslationalEnergy = (3./2.)*T*static_cast<G4double>(_theFragments.size());

    std::deque<G4StatMFFragment*>::const_iterator i;
    for (i = _theFragments.begin(); i != _theFragments.end(); ++i)
      {
	Energy += (*i)->GetEnergy(T);
      }
    return Energy + TranslationalEnergy;	
}

G4FragmentVector * G4StatMFChannel::GetFragments(G4int anA, 
						 G4int anZ,
						 G4double T)
    //
{
    // calculate momenta of charged fragments  
    CoulombImpulse(anA,anZ,T);
	
    // calculate momenta of neutral fragments
    FragmentsMomenta(_NumOfNeutralFragments, _NumOfChargedFragments, T);

    G4FragmentVector * theResult = new G4FragmentVector;
    std::deque<G4StatMFFragment*>::iterator i;
    for (i = _theFragments.begin(); i != _theFragments.end(); ++i)
	theResult->push_back((*i)->GetFragment(T));

    return theResult;
}

void G4StatMFChannel::CoulombImpulse(G4int anA, G4int anZ, G4double T)
    // Aafter breakup, fragments fly away under Coulomb field.
    // This method calculates asymptotic fragments momenta.
{
    // First, we have to place the fragments inside of the original nucleus volume
    PlaceFragments(anA);
	
	// Second, we sample initial charged fragments momenta. There are
	// _NumOfChargedFragments charged fragments and they start at the begining
	// of the vector _theFragments (i.e. 0) 
    FragmentsMomenta(_NumOfChargedFragments, 0, T);

    // Third, we have to figure out the asymptotic momenta of charged fragments 
    // For taht we have to solve equations of motion for fragments
    SolveEqOfMotion(anA,anZ,T);

    return;
}

void G4StatMFChannel::PlaceFragments(G4int anA)
    // This gives the position of fragments at the breakup instant. 
    // Fragments positions are sampled inside prolongated ellipsoid.
{
    G4Pow* g4pow = G4Pow::GetInstance();
    const G4double R0 = G4StatMFParameters::Getr0();
    const G4double Rsys = 2.0*R0*g4pow->Z13(anA);

    G4bool TooMuchIterations;
    do 
      {
	TooMuchIterations = false;
	
	// Sample the position of the first fragment
	G4double R = (Rsys - R0*g4pow->Z13(_theFragments[0]->GetA()))*
	  std::pow(G4UniformRand(),1./3.);
	_theFragments[0]->SetPosition(IsotropicVector(R));
	
	
	// Sample the position of the remaining fragments
	G4bool ThereAreOverlaps = false;
	std::deque<G4StatMFFragment*>::iterator i;
	for (i = _theFragments.begin()+1; i != _theFragments.end(); ++i) 
	  {
	    G4int counter = 0;
	    do 
	      {
		R = (Rsys - R0*g4pow->Z13((*i)->GetA()))*std::pow(G4UniformRand(),1./3.);
		(*i)->SetPosition(IsotropicVector(R));
		
		// Check that there are not overlapping fragments
		std::deque<G4StatMFFragment*>::iterator j;
		for (j = _theFragments.begin(); j != i; ++j) 
		  {
		    G4ThreeVector FragToFragVector = (*i)->GetPosition() - (*j)->GetPosition();
		    G4double Rmin = R0*(g4pow->Z13((*i)->GetA()) +
					g4pow->Z13((*j)->GetA()));
		    if ( (ThereAreOverlaps = (FragToFragVector.mag2() < Rmin*Rmin)) ) break;
		  }
		counter++;
	      } while (ThereAreOverlaps && counter < 1000);
	    
	    if (counter >= 1000) 
	      {
		TooMuchIterations = true;
		break;
	      } 
	  }
    } while (TooMuchIterations);
    
    return;
}

void G4StatMFChannel::FragmentsMomenta(G4int NF, G4int idx,
				       G4double T)
    // Calculate fragments momenta at the breakup instant
    // Fragment kinetic energies are calculated according to the 
    // Boltzmann distribution at given temperature.
    // NF is number of fragments
    // idx is index of first fragment
{
    G4double KinE = (3./2.)*T*static_cast<G4double>(NF);
	
    G4ThreeVector p;
	
    if (NF <= 0) return;
    else if (NF == 1) 
      {
	// We have only one fragment to deal with
	p = IsotropicVector(std::sqrt(2.0*_theFragments[idx]->GetNuclearMass()*KinE));
	_theFragments[idx]->SetMomentum(p);
      } 
    else if (NF == 2) 
      {
	// We have only two fragment to deal with
	G4double M1 = _theFragments[idx]->GetNuclearMass();
	G4double M2 = _theFragments[idx+1]->GetNuclearMass();
	p = IsotropicVector(std::sqrt(2.0*KinE*(M1*M2)/(M1+M2)));		
	_theFragments[idx]->SetMomentum(p);
	_theFragments[idx+1]->SetMomentum(-p);
      } 
    else 
      {
	// We have more than two fragments
	G4double AvailableE;
	G4int i1,i2;
	G4double SummedE;
	G4ThreeVector SummedP;
	do 
	  {
	    // Fisrt sample momenta of NF-2 fragments 
	    // according to Boltzmann distribution
	    AvailableE = 0.0;
	    SummedE = 0.0;
	    SummedP.setX(0.0);SummedP.setY(0.0);SummedP.setZ(0.0);
	    for (G4int i = idx; i < idx+NF-2; i++) 
	      {
		G4double E;
		G4double RandE;
		G4double Boltzmann;
		do 
		  {
		    E = 9.0*T*G4UniformRand();
		    Boltzmann = std::sqrt(E)*std::exp(-E/T);
		    RandE = std::sqrt(T/2.)*std::exp(-0.5)*G4UniformRand();
		  } 
		while (RandE > Boltzmann);
		p = IsotropicVector(std::sqrt(2.0*E*_theFragments[i]->GetNuclearMass()));
		_theFragments[i]->SetMomentum(p);
		SummedE += E;
		SummedP += p;
	      }	
	    // Calculate momenta of last two fragments in such a way
	    // that constraints are satisfied
	    i1 = idx+NF-2;  // before last fragment index
	    i2 = idx+NF-1;  // last fragment index
	    p = -SummedP;
	    AvailableE = KinE - SummedE;
	    // Available Kinetic Energy should be shared between two last fragments
	  } 
	while (AvailableE <= p.mag2()/(2.0*(_theFragments[i1]->GetNuclearMass()+
					    _theFragments[i2]->GetNuclearMass())));		
		
	G4double H = 1.0 + _theFragments[i2]->GetNuclearMass()/_theFragments[i1]->GetNuclearMass();
	G4double CTM12 = H*(1.0 - 2.0*_theFragments[i2]->GetNuclearMass()*AvailableE/p.mag2());
	G4double CosTheta1;
	G4double Sign;

        if (CTM12 > 0.9999) {CosTheta1 = 1.;} 
        else {
	 do 
	   {
	     do 
	       {
		 CosTheta1 = 1.0 - 2.0*G4UniformRand();
	       } 
	     while (CosTheta1*CosTheta1 < CTM12);
	   }
          while (CTM12 >= 0.0 && CosTheta1 < 0.0);
	}

	if (CTM12 < 0.0) Sign = 1.0;
	else if (G4UniformRand() <= 0.5) Sign = -1.0;
	else Sign = 1.0;
		
		
	G4double P1 = (p.mag()*CosTheta1+Sign*std::sqrt(p.mag2()*(CosTheta1*CosTheta1-CTM12)))/H;
	G4double P2 = std::sqrt(P1*P1+p.mag2() - 2.0*P1*p.mag()*CosTheta1);
	G4double Phi = twopi*G4UniformRand();
	G4double SinTheta1 = std::sqrt(1.0 - CosTheta1*CosTheta1);
	G4double CosPhi1 = std::cos(Phi);
	G4double SinPhi1 = std::sin(Phi);
	G4double CosPhi2 = -CosPhi1;
	G4double SinPhi2 = -SinPhi1;
	G4double CosTheta2 = (p.mag2() + P2*P2 - P1*P1)/(2.0*p.mag()*P2);
	G4double SinTheta2 = 0.0;
	if (CosTheta2 > -1.0 && CosTheta2 < 1.0) SinTheta2 = std::sqrt(1.0 - CosTheta2*CosTheta2);
	
	G4ThreeVector p1(P1*SinTheta1*CosPhi1,P1*SinTheta1*SinPhi1,P1*CosTheta1);
	G4ThreeVector p2(P2*SinTheta2*CosPhi2,P2*SinTheta2*SinPhi2,P2*CosTheta2);
	G4ThreeVector b(1.0,0.0,0.0);
	
	p1 = RotateMomentum(p,b,p1);
	p2 = RotateMomentum(p,b,p2);
	
	SummedP += p1 + p2;
	SummedE += p1.mag2()/(2.0*_theFragments[i1]->GetNuclearMass()) + 
	    p2.mag2()/(2.0*_theFragments[i2]->GetNuclearMass());		
		
	_theFragments[i1]->SetMomentum(p1);
	_theFragments[i2]->SetMomentum(p2);
		
      }

    return;
}


void G4StatMFChannel::SolveEqOfMotion(G4int anA, G4int anZ, G4double T)
    // This method will find a solution of Newton's equation of motion
    // for fragments in the self-consistent time-dependent Coulomb field
{
  G4double CoulombEnergy = (3./5.)*(elm_coupling*anZ*anZ)*
    std::pow(1.0+G4StatMFParameters::GetKappaCoulomb(),1./3.)/
    (G4StatMFParameters::Getr0()*G4Pow::GetInstance()->Z13(anA))
    - GetFragmentsCoulombEnergy();
  if (CoulombEnergy <= 0.0) return;
  
  G4int Iterations = 0;
  G4double TimeN = 0.0;
  G4double TimeS = 0.0;
  G4double DeltaTime = 10.0;
  
  G4ThreeVector * Pos = new G4ThreeVector[_NumOfChargedFragments];
  G4ThreeVector * Vel = new G4ThreeVector[_NumOfChargedFragments];
  G4ThreeVector * Accel = new G4ThreeVector[_NumOfChargedFragments];
  
  G4int i;
  for (i = 0; i < _NumOfChargedFragments; i++) 
    {
      Vel[i] = (1.0/(_theFragments[i]->GetNuclearMass()))*
	_theFragments[i]->GetMomentum();
      Pos[i] = _theFragments[i]->GetPosition();
    }
  
  do 
    {

      G4ThreeVector distance;
      G4ThreeVector force;

      for (i = 0; i < _NumOfChargedFragments; i++) 
	{
	  force.setX(0.0); force.setY(0.0); force.setZ(0.0);
	  for (G4int j = 0; j < _NumOfChargedFragments; j++) 
	    {
	      if (i != j) 
		{
		  distance = Pos[i] - Pos[j];
		  force += (elm_coupling*_theFragments[i]->GetZ()
					  *_theFragments[j]->GetZ()/
			    (distance.mag2()*distance.mag()))*distance;
		}
	    }
	  Accel[i] = (1./(_theFragments[i]->GetNuclearMass()))*force;
	}

      TimeN = TimeS + DeltaTime;
	
      G4ThreeVector SavedVel;
      for ( i = 0; i < _NumOfChargedFragments; i++) 
	{
	  SavedVel = Vel[i];
	  Vel[i] += Accel[i]*(TimeN-TimeS);
	  Pos[i] += (SavedVel+Vel[i])*(TimeN-TimeS)*0.5;
	}
      
      // 		if (Iterations >= 50 && Iterations < 75) DeltaTime = 4.;
      // 		else if (Iterations >= 75) DeltaTime = 10.;

      TimeS = TimeN;

    } 
  while (Iterations++ < 100);
	
  // Summed fragment kinetic energy
  G4double TotalKineticEnergy = 0.0;
  for (i = 0; i < _NumOfChargedFragments; i++) 
    {
      TotalKineticEnergy += _theFragments[i]->GetNuclearMass()*
	0.5*Vel[i].mag2();
    }
  // Scaling of fragment velocities
  G4double KineticEnergy = (3./2.)*_theFragments.size()*T;
  G4double Eta = ( CoulombEnergy + KineticEnergy ) / TotalKineticEnergy;
  for (i = 0; i < _NumOfChargedFragments; i++) 
    {
      Vel[i] *= Eta;
    }
  
  // Finally calculate fragments momenta
  for (i = 0; i < _NumOfChargedFragments; i++) 
    {
      _theFragments[i]->SetMomentum(_theFragments[i]->GetNuclearMass()*Vel[i]);
    }
  
  // garbage collection
  delete [] Pos;
  delete [] Vel;
  delete [] Accel;
  
  return;
}



G4ThreeVector G4StatMFChannel::RotateMomentum(G4ThreeVector Pa,
					      G4ThreeVector V, G4ThreeVector P)
    // Rotates a 3-vector P to close momentum triangle Pa + V + P = 0
{
  G4ThreeVector U = Pa.unit();
  
  G4double Alpha1 = U * V;
  
  G4double Alpha2 = std::sqrt(V.mag2() - Alpha1*Alpha1);

  G4ThreeVector N = (1./Alpha2)*U.cross(V);
  
  G4ThreeVector RotatedMomentum(
				( (V.x() - Alpha1*U.x())/Alpha2 ) * P.x() + N.x() * P.y() + U.x() * P.z(),
				( (V.y() - Alpha1*U.y())/Alpha2 ) * P.x() + N.y() * P.y() + U.y() * P.z(),
				( (V.z() - Alpha1*U.z())/Alpha2 ) * P.x() + N.z() * P.y() + U.z() * P.z()
				);
  return RotatedMomentum;
}





G4ThreeVector G4StatMFChannel::IsotropicVector(const G4double Magnitude)
    // Samples a isotropic random vector with a magnitud given by Magnitude.
    // By default Magnitude = 1
{
    G4double CosTheta = 1.0 - 2.0*G4UniformRand();
    G4double SinTheta = std::sqrt(1.0 - CosTheta*CosTheta);
    G4double Phi = twopi*G4UniformRand();
    G4ThreeVector Vector(Magnitude*std::cos(Phi)*SinTheta,
			 Magnitude*std::cos(Phi)*CosTheta,
			 Magnitude*std::sin(Phi));
    return Vector;
}
