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
// $Id$
// GEANT4 tag $Name$
//
//---------------------------------------------------------------------------
//
// ClassName:   G4BertiniKaonBuilder
//
// Author: 2011 G.Folger
//  devired from G4BertiniPionBuilder
//
// Modified:
//
//----------------------------------------------------------------------------
//
#ifndef G4BertiniKaonBuilder_h
#define G4BertiniKaonBuilder_h 1

#include "globals.hh"

#include "G4HadronElasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4VKaonBuilder.hh"

#include "G4QHadronInelasticDataSet.hh"
#include "G4CascadeInterface.hh"   

class G4BertiniKaonBuilder : public G4VKaonBuilder
{
  public: 
    G4BertiniKaonBuilder();
    virtual ~G4BertiniKaonBuilder();

  public: 
    virtual void Build(G4HadronElasticProcess * aP);
    virtual void Build(G4KaonPlusInelasticProcess * aP);
    virtual void Build(G4KaonMinusInelasticProcess * aP);
    virtual void Build(G4KaonZeroLInelasticProcess * aP);
    virtual void Build(G4KaonZeroSInelasticProcess * aP);

    void SetMinEnergy(G4double aM) {theMin = aM;}
    void SetMaxEnergy(G4double aM) {theMax = aM;}

  private:
    G4QHadronInelasticDataSet * theKaonData;
    G4CascadeInterface * theModel;    
    G4double theMin;
    G4double theMax;

};
#endif

