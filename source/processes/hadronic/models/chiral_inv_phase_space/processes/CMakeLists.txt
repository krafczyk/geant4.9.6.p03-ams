#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : G4hadronic_proc_ci
# Package: Geant4.src.G4processes.G4hadronic.G4hadronic_models.G4hadronic_chips.G4hadronic_proc_ci
#
# CMakeLists.txt for building a single granular library.
#
# Generated on : 24/9/2010
#
# $Id$
#
#------------------------------------------------------------------------------

if(GEANT4_BUILD_GRANULAR_LIBS)
    include(Geant4MacroLibraryTargets)
    GEANT4_GRANULAR_LIBRARY_TARGET(COMPONENT sources.cmake)
endif()

