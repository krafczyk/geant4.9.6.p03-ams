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
//
// 20100804  M. Kelsey -- Add name string to ctor
// 20110719  M. Kelsey -- Add initial state code to ctor
// 20110725  M. Kelsey -- Instantiate cross-section object for self-registration
// 20110916  M. Kelsey -- Drop self-registration due to platform inconsistencies

#include "G4CascadeKplusPChannel.hh"
#include "G4InuclParticleNames.hh"
using namespace G4InuclParticleNames;

namespace {
  // Outgoing particle types of a given multiplicity

  static const G4int kpp2bfs[1][2] =
    {{1, 11}};

  static const G4int kpp3bfs[4][3] =
    {{1,7,11}, {2,3,11}, {1,3,15}, {11,11,21}};
 
  static const G4int kpp4bfs[10][4] =
    {{1,7,7,11},  {1,3,5,11},  {2,3,7,11},  {1,3,7,15},  {2,3,3,15},
     {1,11,15,17},{1,11,11,13},{2,11,11,17},{7,11,11,21},{3,11,15,21}};

  static const G4int kpp5bfs[19][5] =
    {{1,7,7,7,11},   {1,3,5,7,11},   {2,3,7,7,11},   {2,3,3,5,11},
     {1,3,7,7,15},   {1,3,3,5,15},   {2,3,3,7,15},   {1,7,11,15,17},
     {1,7,11,11,13}, {1,5,11,11,17}, {1,3,11,13,15}, {2,3,11,15,17},
     {2,3,11,11,13}, {2,7,11,11,17}, {1,3,15,15,17}, {7,7,11,11,21},
     {3,5,11,11,21}, {3,7,11,15,21}, {3,3,15,15,21}}; 
 
  static const G4int kpp6bfs[28][6] =
    {{1,7,7,7,7,11},   {1,3,5,7,7,11},   {1,3,3,5,5,11},
     {2,3,7,7,7,11},   {2,3,3,5,7,11},   {1,3,7,7,7,15},
     {1,3,3,5,7,15},   {2,3,3,7,7,15},   {2,3,3,3,5,15},
     {1,7,7,11,11,13}, {1,3,5,11,11,13}, {1,5,7,11,11,17},
     {1,7,7,11,15,17}, {1,3,5,11,15,17}, {1,3,7,11,13,15},
     {2,3,3,11,13,15}, {2,7,7,11,11,17}, {2,3,5,11,11,17},
     {2,3,7,11,11,13}, {2,3,7,11,15,17}, {1,3,3,13,15,15},
     {1,3,7,15,15,17}, {2,3,3,15,15,17}, {7,7,7,11,11,21},
     {3,5,7,11,11,21}, {3,7,7,11,15,21}, {3,3,5,11,15,21},
     {3,3,7,15,15,21}};
 
  static const G4int kpp7bfs[38][7] =
    {{1,7,7,7,7,7,11},   {1,3,5,7,7,7,11},   {1,3,3,5,5,7,11},
     {2,3,7,7,7,7,11},   {2,3,3,5,7,7,11},   {2,3,3,3,5,5,11},
     {1,3,7,7,7,7,15},   {1,3,3,5,7,7,15},   {1,3,3,3,5,5,15},
     {2,3,3,7,7,7,15},   {2,3,3,3,5,7,15},   {1,7,7,7,11,11,13},
     {1,3,5,7,11,11,13}, {1,5,7,7,11,11,17}, {1,3,5,5,11,11,17},
     {1,7,7,7,11,15,17}, {1,3,5,7,11,15,17}, {1,3,7,7,11,13,15},
     {1,3,3,5,11,13,15}, {1,3,3,7,13,15,15}, {1,3,7,7,15,15,17},
     {1,3,3,5,15,15,17}, {2,3,3,7,11,13,15}, {2,7,7,7,11,11,17},
     {2,3,5,7,11,11,17}, {2,3,7,7,11,11,13}, {2,3,3,5,11,11,13},
     {2,3,7,7,11,15,17}, {2,3,3,5,11,15,17}, {2,3,3,7,15,15,17},
     {2,3,3,3,13,15,15}, {7,7,7,7,11,11,21}, {3,5,7,7,11,11,21},
     {3,3,5,5,11,11,21}, {3,3,5,7,11,15,21}, {3,7,7,7,11,15,21},
     {3,3,7,7,15,15,21}, {3,3,3,5,15,15,21}};

  // Cross sections for K+ p -> 2-7 body final states
  // 
  // first index:      0: channels for mult = 2
  //                 1-4: channels for mult = 3 
  //                5-14: channels for mult = 4
  //               15-33: channels for mult = 5
  //               34-61: channels for mult = 6
  //               62-99: channels for mult = 7
  //
  // second index: kinetic energy
  // 
  static const G4double kppCrossSections[100][31] = {
    //
    // multiplicity 2 (1 channel)
    //
    // K+ p
    {10.0, 11.7, 11.8, 12.1, 12.4, 12.6, 12.5, 12.4, 12.2, 12.1,
     12.0,  9.78, 7.34, 6.01, 5.09, 4.54, 4.13, 3.91, 3.75, 3.60,
     3.50, 3.40, 3.30, 3.20, 3.10, 3.07, 3.05, 3.02, 3.00, 2.98, 2.75},
    //
    //  multiplicity 3 (4 channels)
    //
    //  K+ p pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.05, 0.16, 
      0.37, 1.77, 1.91, 1.55, 1.26, 1.31, 1.10, 0.86, 0.75, 0.70, 
      0.65, 0.61, 0.57, 0.53, 0.50, 0.47, 0.46, 0.44, 0.41, 0.39, 0.30},

    //  K+ n pi+ 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.03, 0.10, 
      0.24, 0.94, 1.42, 1.19, 1.09, 0.82, 0.73, 0.63, 0.54, 0.49, 
      0.44, 0.41, 0.38, 0.35, 0.33, 0.31, 0.29, 0.27, 0.25, 0.24, 0.16},
 
    //  K0 p pi+ 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.05, 0.20, 0.60,
      1.41, 4.99, 4.29, 3.04, 2.09, 1.86, 1.24, 1.07, 0.94, 0.86,
      0.78, 0.71, 0.63, 0.55, 0.48, 0.38, 0.28, 0.27, 0.27, 0.26, 0.15},
 
    // K+ L K+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.03, 0.02, 0.02, 0.02, 0.02, 0.03, 0.02, 
      0.02, 0.02, 0.02, 0.02, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
    //
    //  multiplicity 4 (10 channels)
    //
    // K+ p 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.50, 0.59, 0.60, 0.69, 0.75, 0.75, 0.75, 
      0.72, 0.70, 0.68, 0.67, 0.66, 0.65, 0.63, 0.61, 0.59, 0.59, 0.55},
  
    // K+ p pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.16, 1.52, 2.10, 2.28, 2.12, 2.01, 1.88, 1.88, 1.80,
      1.79, 1.77, 1.75, 1.66, 1.42, 1.25, 1.16, 1.18, 1.19, 1.15, 0.84},
 
    // K+ n pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.49, 0.68, 0.7,  0.61, 0.60, 0.59, 0.58,
      0.57, 0.56, 0.55, 0.55, 0.55, 0.55, 0.55, 0.54, 0.53, 0.53, 0.50},

    // K0 p pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.17, 1.11, 2.07, 2.11, 2.42, 1.81, 1.67, 1.56, 1.45,
      1.44, 1.44, 1.44, 1.42, 1.36, 1.08, 1.23, 1.16, 1.10, 1.01, 0.50},

    // K0 n 2pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.02, 0.32, 0.47, 0.59, 0.6,  0.48, 0.43, 0.40, 0.38,
      0.37, 0.35, 0.33, 0.32, 0.30, 0.26, 0.22, 0.18, 0.13, 0.13, 0.11},

    // K+ p K0bar K0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.02, 0.02, 0.01, 0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K+ K-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.02, 0.03, 0.04,
      0.04, 0.05, 0.05, 0.05, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04},

    // K+ n K+ K0bar   
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03},
                          
    // K+ L K+ pi0 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.02, 0.02,
      0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.01},
 
    // K+ L K0 pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.03, 0.04, 0.04,
      0.03, 0.03, 0.03, 0.03, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03, 0.02},
    //
    //  multiplicity 5 (19 channels)
    // 
    // K+ p 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.16, 0.31, 0.49, 0.59, 0.67, 0.71,
      0.74, 0.78, 0.79, 0.75, 0.71, 0.69, 0.68, 0.68, 0.67, 0.65, 0.47},
   
    // K+ p pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.08, 0.24, 0.58, 0.70, 0.84, 0.99, 1.12, 1.18,
      1.24, 1.30, 1.31, 1.25, 1.18, 1.15, 1.14, 1.13, 1.12, 1.09, 0.79},
 
    // K+ n pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.04, 0.08, 0.13, 0.14, 0.16, 0.17,
      0.19, 0.20, 0.21, 0.23, 0.24, 0.25, 0.24, 0.23, 0.23, 0.23, 0.18},
 
    // K+ n 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.03, 0.14, 0.19, 0.21, 0.24, 0.26, 0.28,
      0.31, 0.33, 0.35, 0.38, 0.40, 0.41, 0.40, 0.39, 0.38, 0.37, 0.30},
 
    // K0 p pi+ 2pi0 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.09, 0.19, 0.29, 0.34, 0.37, 0.37,
      0.37, 0.36, 0.36, 0.35, 0.35, 0.33, 0.29, 0.26, 0.23, 0.22, 0.17},
 
    // K0 p 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.07, 0.32, 0.43, 0.50, 0.56, 0.62, 0.61,
      0.61, 0.60, 0.60, 0.59, 0.59, 0.55, 0.49, 0.44, 0.38, 0.36, 0.28},
 
    // K0 n 2pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.05, 0.08, 0.08, 0.12, 0.12,
      0.12, 0.12, 0.12, 0.12, 0.12, 0.11, 0.10, 0.10, 0.10, 0.10, 0.10},
 
    // K+ p K0bar K0 pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
                           
    // K+ p K+ K- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03},
 
    // K+ p K+ K0bar pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,    
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // K+ p K- K0 pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.03,
      0.04, 0.05, 0.06, 0.06, 0.05, 0.05, 0.06, 0.06, 0.05, 0.05, 0.04},
 
    // K+ n K0bar K0 pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // K+ n K+ K- pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // K+ n K+ K0bar pi0

    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // K0 p K0 K0bar pi+

    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},
 
    // K+ L K+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // K+ L K+ pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02},
 
    // K+ L K0 pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 
      0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.04, 0.04, 0.04, 0.03},
 
    // K0 L K0 2pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02},
    //
    //  multiplicity 6 (28 channels)
    // 
    // K+ p 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.04, 0.05, 0.07, 0.07,
      0.08, 0.09, 0.09, 0.10, 0.10, 0.10, 0.10, 0.09, 0.09, 0.09, 0.08},
 
    // K+ p pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.03, 0.07, 0.09, 0.11, 0.12,
      0.13, 0.14, 0.16, 0.16, 0.17, 0.17, 0.16, 0.15, 0.14, 0.14, 0.13},
           
    // K+ p 2pi+ 2pi-   
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.04, 0.07, 0.11, 0.15, 0.19, 0.20,
      0.22, 0.24, 0.26, 0.27, 0.29, 0.29, 0.27, 0.25, 0.24, 0.24, 0.22},
  
    // K+ n pi+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.05, 0.06, 0.07,
      0.07, 0.08, 0.08, 0.16, 0.23, 0.31, 0.38, 0.46, 0.53, 0.60, 0.90},
 
    // K+ n 2pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.04, 0.06, 0.08, 0.10, 0.11,
      0.12, 0.13, 0.14, 0.26, 0.39, 0.51, 0.63, 0.76, 0.88, 1.00, 1.50},
 
    // K0 p pi+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.02, 0.07, 0.18, 0.28, 0.37, 0.41,
      0.45, 0.49, 0.51, 0.52, 0.53, 0.53, 0.52, 0.50, 0.49, 0.46, 0.24},
 
    // K0 p 2pi+ pi0 pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.08, 0.15, 0.31, 0.46, 0.62, 0.69,
      0.75, 0.81, 0.85, 0.87, 0.89, 0.89, 0.86, 0.84, 0.81, 0.77, 0.40},

    // K0 n 2pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.05, 0.05,
      0.05, 0.05, 0.05, 0.06, 0.06, 0.06, 0.07, 0.07, 0.07, 0.07, 0.08},

    // K0 n 3pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.06, 0.08, 0.08,
      0.08, 0.09, 0.09, 0.10, 0.10, 0.10, 0.11, 0.11, 0.12, 0.12, 0.14},

    // K+ p K+ K- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02},

    // K+ p K+ K- pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03},

    // K+ p K+ K0bar pi0 pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, 0.0},
 
    // K+ p K0 K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K0 K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // K+ p K0 K- pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,   
      0.02, 0.03, 0.04, 0.04, 0.05, 0.05, 0.06, 0.06, 0.07, 0.07, 0.08},

    // K+ n K0 K- 2pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,   
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02},

    // K+ n K+ K0bar 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,   
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02},

    // K+ n K+ K0bar pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03},

    // K+ n K+ K- pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03},

    // K+ n K0 K0bar pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.03},

    // K0 p K0 K- 2pi+ 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0bar p K0 K0 pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0bar n K0 K0 2pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
 
    // K+ L K+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01},
 
    // K+ L K+ pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.02},

    // K+ L K0 pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.04},

    // K+ L K0 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.06},

    // K0 L K0 2pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.02,
      0.02, 0.02, 0.02, 0.01, 0.01, 0.02, 0.01, 0.01, 0.01, 0.01, 0.02},
    //
    //  multiplicity 7 (38 channels)
    // 
    // K+ p 5pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.02, 0.03, 0.04, 0.06,
      0.07, 0.09, 0.10, 0.12, 0.13, 0.14, 0.14, 0.15, 0.16, 0.16, 0.19},

    // K+ p pi+ pi- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.03, 0.05, 0.07, 0.10,
      0.12, 0.14, 0.17, 0.19, 0.22, 0.23, 0.24, 0.25, 0.26, 0.26, 0.31},

    // K+ p 2pi+ 2pi- pi0 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.05, 0.08, 0.12, 0.16,
      0.20, 0.24, 0.28, 0.32, 0.36, 0.38, 0.40, 0.42, 0.44, 0.44, 0.52},

    // K+ n pi+ 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01,
      0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.04, 0.04, 0.04, 0.04, 0.05},

    // K+ n 2pi+ pi- 2pi0 
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.02, 0.02, 0.02, 0.03, 0.03, 0.03, 0.06, 0.06, 0.07, 0.07, 0.08},

    // K+ n 3pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.02, 0.02,
      0.03, 0.03, 0.03, 0.04, 0.04, 0.04, 0.10, 0.10, 0.11, 0.11, 0.13},

    // K0 p pi+ 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.03, 0.03,
      0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.05, 0.05, 0.04, 0.04, 0.04},
           
    // K0 p 2pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.02, 0.04, 0.05, 0.05,
      0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.08, 0.08, 0.07, 0.07, 0.06},

    // K0 p 3pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.04, 0.06, 0.09, 0.09,
      0.10, 0.10, 0.10, 0.11, 0.11, 0.11, 0.13, 0.13, 0.12, 0.12, 0.10},

    // K0 n 2pi+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0 n 3pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01,
      0.02, 0.02, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K+ p K+ K- 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K+ K- pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K+ K0bar pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K+ K0bar pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K0 K0bar 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ p K0 K0bar pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},
           
    // K+ p K0 K- pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},
    
    // K+ p K0 K- 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0 p K0 K- 2pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0 p K0 K0bar pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K0 p K0 K0bar 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ n K0 K- 2pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K+ n K+ K0bar 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ n K+ K0bar pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K+ n K+ K- pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},
 
    // K+ n K+ K- 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K+ n K0 K0bar pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ n K0 K0bar 2pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K0 n K0 K0bar 2pi+ pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K0 n K0 K- 3pi+
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K+ L K+ 4pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01},

    // K+ L K+ pi+ pi- 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ L K+ 2pi+ 2pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K+ L K0 2pi+ pi- pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02},

    // K+ L K0 pi+ 3pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0 L K0 2pi+ 2pi0
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01},

    // K0 L K0 3pi+ pi-
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
      0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.01,
      0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01} };
}

G4CascadeKplusPChannelData::data_t
G4CascadeKplusPChannelData::data(kpp2bfs, kpp3bfs, kpp4bfs,
				 kpp5bfs, kpp6bfs, kpp7bfs,
				 kppCrossSections, kpl*pro, "KplusP");
