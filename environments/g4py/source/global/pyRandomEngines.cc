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
// $Name$
// ====================================================================
//   pyRandomEngines.cc
//
//                                         2005 Q
// ====================================================================
#include <boost/python.hpp>
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Ranlux64Engine.h"
#include "CLHEP/Random/RanluxEngine.h"

using namespace boost::python;
using namespace CLHEP;

// ====================================================================
// module definition
// ====================================================================
void export_RandomEngines()
{
  class_<HepRandomEngine, boost::noncopyable>
    ("HepRandomEngine", "base class of random engine", no_init)
    ;

  class_<HepJamesRandom, bases<HepRandomEngine> >
    ("HepJamesRandom", "HepJames random engine")
    ;

  class_<RanecuEngine, bases<HepRandomEngine> >
    ("RanecuEngine", "Ranecu random engine")
    ;

  class_<RanluxEngine, bases<HepRandomEngine> >
    ("RanluxEngine", "Ranlux random engine")
    ;

  class_<Ranlux64Engine, bases<HepRandomEngine> >
    ("Ranlux64Engine", "Ranlux64 random engine")
    ;

}