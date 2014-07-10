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

#include "G4AnyType.hh"
#include "G4UIcommand.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"

template <> void G4AnyType::Ref<bool>::FromString(const std::string& val)  {
  fRef = G4UIcommand::ConvertToBool(val.c_str());
}

template <> void G4AnyType::Ref<G4String>::FromString(const std::string& val)  {
  if (val[0] == '"' ) fRef = val.substr(1,val.size()-2);
  else fRef = val;
}

template <> void G4AnyType::Ref<G4ThreeVector>::FromString(const std::string& val)  {
  fRef = G4UIcommand::ConvertTo3Vector(val.c_str());
}
