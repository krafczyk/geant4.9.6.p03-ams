#------------------------------------------------------------------------------
# sources.cmake
# Module : G4phys_lists
# Package: Geant4.src.G4physicslists.G4phys_lists
#
# Sources description for a library.
# Lists the sources and headers of the code explicitely.
# Lists include paths needed.
# Lists the internal granular and global dependencies of the library.
# Source specific properties should be added at the end.
#
# Generated on : 24/9/2010
#
# $Id$
# GEANT4 Tag $Name$
#
#------------------------------------------------------------------------------

# List external includes needed.
include_directories(${CLHEP_INCLUDE_DIRS})
include_directories(${EXPAT_INCLUDE_DIRS})

# List internal includes needed.
include_directories(${CMAKE_SOURCE_DIR}/source/digits_hits/digits/include)
include_directories(${CMAKE_SOURCE_DIR}/source/digits_hits/hits/include)
include_directories(${CMAKE_SOURCE_DIR}/source/event/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/magneticfield/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/navigation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/geometry/volumes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/HEPGeometry/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/HEPRandom/include)
include_directories(${CMAKE_SOURCE_DIR}/source/global/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/intercoms/include)
include_directories(${CMAKE_SOURCE_DIR}/source/materials/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/bosons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/hadrons/barions/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/hadrons/ions/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/hadrons/mesons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/leptons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/particles/shortlived/include)
include_directories(${CMAKE_SOURCE_DIR}/source/physics_lists/builders/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/cuts/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/decay/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/dna/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/highenergy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/lowenergy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/muons/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/standard/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/utils/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/electromagnetic/xrays/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/cross_sections/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/binary_cascade/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/cascade/cascade/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/cascade/evaporation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/cascade/utils/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/chiral_inv_phase_space/body/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/chiral_inv_phase_space/cross_sections/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/chiral_inv_phase_space/fragmentation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/chiral_inv_phase_space/interface/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/chiral_inv_phase_space/processes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/coherent_elastic/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/evaporation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/fermi_breakup/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/fission/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/gem_evaporation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/handler/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/multifragmentation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/photon_evaporation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/de_excitation/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/high_energy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/im_r_matrix/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/inclxx/utils/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/inclxx/incl_physics/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/inclxx/interface/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/isotope_production/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/lend/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/lepto_nuclear/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/low_energy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/neutron_hp/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/diffraction/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/hadronization/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/parton_string/qgsm/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/pre_equilibrium/exciton_model/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/radioactive_decay/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/theo_high_energy/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/models/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/processes/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/stopping/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/hadronic/util/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/management/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/optical/include)
include_directories(${CMAKE_SOURCE_DIR}/source/processes/transportation/include)
include_directories(${CMAKE_SOURCE_DIR}/source/run/include)
include_directories(${CMAKE_SOURCE_DIR}/source/track/include)
include_directories(${CMAKE_SOURCE_DIR}/source/tracking/include)

#
# Define the Geant4 Module.
#
include(Geant4MacroDefineModule)
GEANT4_DEFINE_MODULE(NAME G4phys_lists
    HEADERS
        CHIPS.hh
        CHIPS.icc
        CHIPS_HP.hh
        CHIPS_HP.icc
        FTF_BIC.hh
        FTF_BIC.icc
        FTFP_BERT_EMV.hh
        FTFP_BERT_EMV.icc
        FTFP_BERT_EMX.hh
        FTFP_BERT_EMX.icc
        FTFP_BERT.hh
        FTFP_BERT.icc
        FTFP_BERT_HP.hh
        FTFP_BERT_HP.icc
        FTFP_BERT_TRV.hh
        FTFP_BERT_TRV.icc
        G4GenericPhysicsList.hh
        G4GenericPhysicsList.icc
        G4HadronInelasticQBBC.hh
        G4PhysListFactory.hh
        G4VHadronPhysics.hh
        HadronPhysicsCHIPS.hh
        HadronPhysicsCHIPS_HP.hh
        HadronPhysicsFTF_BIC.hh
        HadronPhysicsFTFP_BERT.hh
        HadronPhysicsFTFP_BERT_HP.hh
        HadronPhysicsFTFP_BERT_TRV.hh
        HadronPhysicsLHEP_EMV.hh
        HadronPhysicsLHEP.hh
        HadronPhysicsQGS_BIC.hh
        HadronPhysicsQGSC_BERT.hh
        HadronPhysicsQGSC_CHIPS.hh
        HadronPhysicsQGSP_BERT_CHIPS.hh
        HadronPhysicsQGSP_BERT.hh
        HadronPhysicsQGSP_BERT_95.hh
        HadronPhysicsQGSP_BERT_HP.hh
        HadronPhysicsQGSP_BERT_NOLEP.hh
        HadronPhysicsQGSP_BERT_TRV.hh
        HadronPhysicsQGSP_BIC.hh
        HadronPhysicsQGSP_BIC_HP.hh
        HadronPhysicsQGSP_FTFP_BERT.hh
        HadronPhysicsQGSP_FTFP_BERT_95.hh
        HadronPhysicsQGSP.hh
	HadronPhysicsQGSP_INCLXX.hh
        HadronPhysicsShielding.hh
        LBE.hh
        LBE.icc
        LHEP_EMV.hh
        LHEP_EMV.icc
        LHEP.hh
        LHEP.icc
        MaxTimeCuts.hh
        MinEkineCuts.hh
        QBBC.hh
        QGS_BIC.hh
        QGS_BIC.icc
        QGSC_BERT.hh
        QGSC_BERT.icc
        QGSC_CHIPS.hh
        QGSC_CHIPS.icc
        QGSP_BERT_CHIPS.hh
        QGSP_BERT_CHIPS.icc
        QGSP_BERT_EMV.hh
        QGSP_BERT_EMV.icc
        QGSP_BERT_EMX.hh
        QGSP_BERT_EMX.icc
        QGSP_BERT.hh
        QGSP_BERT.icc
        QGSP_BERT_95.hh
        QGSP_BERT_95.icc
        QGSP_BERT_95XS.hh
        QGSP_BERT_95XS.icc
        QGSP_BERT_HP.hh
        QGSP_BERT_HP.icc
        QGSP_BERT_NOLEP.hh
        QGSP_BERT_NOLEP.icc
        QGSP_BERT_TRV.hh
        QGSP_BERT_TRV.icc
        QGSP_BIC_EMY.hh
        QGSP_BIC_EMY.icc
        QGSP_BIC.hh
        QGSP_BIC_HP.hh
        QGSP_BIC_HP.icc
        QGSP_BIC.icc
        QGSP_FTFP_BERT.hh
        QGSP_FTFP_BERT.icc
        QGSP_FTFP_BERT_95.hh
        QGSP_FTFP_BERT_95.icc
        QGSP_FTFP_BERT_95XS.hh
        QGSP_FTFP_BERT_95XS.icc
        QGSP.hh
        QGSP.icc
	QGSP_INCLXX.hh
	QGSP_INCLXX.icc
        QGSP_QEL.hh
        QGSP_QEL.icc
        Shielding.hh
        Shielding.icc
        SpecialCuts.hh
	G4PhysListUtil.hh
    SOURCES
        G4HadronInelasticQBBC.cc
        G4PhysListFactory.cc
        G4VHadronPhysics.cc
        HadronPhysicsCHIPS.cc
        HadronPhysicsCHIPS_HP.cc
        HadronPhysicsFTF_BIC.cc
        HadronPhysicsFTFP_BERT.cc
        HadronPhysicsFTFP_BERT_HP.cc
        HadronPhysicsFTFP_BERT_TRV.cc
        HadronPhysicsLHEP.cc
        HadronPhysicsLHEP_EMV.cc
        HadronPhysicsQGS_BIC.cc
        HadronPhysicsQGSC_BERT.cc
        HadronPhysicsQGSC_CHIPS.cc
        HadronPhysicsQGSP_BERT.cc
        HadronPhysicsQGSP_BERT_95.cc
        HadronPhysicsQGSP_BERT_CHIPS.cc
        HadronPhysicsQGSP_BERT_HP.cc
        HadronPhysicsQGSP_BERT_NOLEP.cc
        HadronPhysicsQGSP_BERT_TRV.cc
        HadronPhysicsQGSP_BIC.cc
        HadronPhysicsQGSP_BIC_HP.cc
        HadronPhysicsQGSP.cc
        HadronPhysicsQGSP_FTFP_BERT.cc
        HadronPhysicsQGSP_FTFP_BERT_95.cc
        HadronPhysicsQGSP_INCLXX.cc
        HadronPhysicsShielding.cc
        MaxTimeCuts.cc
        MinEkineCuts.cc
        QBBC.cc
        SpecialCuts.cc
	G4PhysListUtil.cc
    GRANULAR_DEPENDENCIES
        G4baryons
        G4bosons
        G4cuts
        G4decay
        G4digits
        G4emdna
        G4emhighenergy
        G4emlowenergy
        G4emstandard
        G4emutils
        G4event
        G4geometrymng
        G4globman
        G4had_im_r_matrix
        G4had_lend
        G4had_mod_man
        G4had_mod_util
        G4had_lept_nuclear
        G4had_neu_hp
        G4had_preequ_exciton
        G4had_string_diff
        G4had_string_frag
        G4had_string_man
        G4had_theo_max
        G4hadronic_HE
        G4hadronic_LE
        G4hadronic_bert_cascade
        G4hadronic_binary
        G4hadronic_body_ci
        G4hadronic_coherent_elastic
        G4hadronic_crosec_ci
        G4hadronic_deex_evaporation
        G4hadronic_deex_fermi_breakup
        G4hadronic_deex_fission
        G4hadronic_deex_gem_evaporation
        G4hadronic_deex_handler
        G4hadronic_deex_management
        G4hadronic_deex_multifragmentation
        G4hadronic_deex_photon_evaporation
        G4hadronic_deex_util
        G4hadronic_fragm_ci
        G4hadronic_hetcpp_evaporation
        G4hadronic_hetcpp_utils
        G4had_inclxx
        G4hadronic_interface_ci
        G4hadronic_iso
        G4hadronic_mgt
        G4hadronic_proc
        G4hadronic_proc_ci
        G4hadronic_qgstring
        G4hadronic_radioactivedecay
        G4hadronic_stop
        G4hadronic_util
        G4hadronic_xsect
        G4hits
        G4intercoms
        G4ions
        G4leptons
        G4magneticfield
        G4materials
        G4mesons
        G4muons
        G4navigation
        G4optical
        G4partman
        G4phys_builders
        G4procman
        G4run
        G4shortlived
        G4track
        G4tracking
        G4transportation
        G4volumes
        G4xrays
    GLOBAL_DEPENDENCIES
        G4digits_hits
        G4event
        G4geometry
        G4global
        G4intercoms
        G4materials
        G4particles
        G4processes
        G4run
        G4track
        G4tracking
    LINK_LIBRARIES
)

# List any source specific properties here

