#------------------------------------------------------------------------------
# CMakeLists.txt
# Module : G4brep
# Package: Geant4.src.G4geometry..G4brep
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

