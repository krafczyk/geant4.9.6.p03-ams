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
/// \file field/field01/include/F01EventAction.hh
/// \brief Definition of the F01EventAction class
//
//
// $Id$
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef F01EventAction_h
#define F01EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class F01RunAction;
class F01EventActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class F01EventAction : public G4UserEventAction
{
  public:
    F01EventAction(F01RunAction* F01RA);
    ~F01EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void SetEventVerbose(G4int level);
    void SetPrintModulo(G4int val)  {fPrintModulo = val;};
        
  private:
    G4int    fCalorimeterCollID;
    F01EventActionMessenger*  fEventMessenger;
    F01RunAction* fRunAction;
    G4int fVerboseLevel;
    G4int fPrintModulo;             
};

#endif
