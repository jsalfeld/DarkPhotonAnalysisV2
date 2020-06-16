import FWCore.ParameterSet.Config as cms

# Set parameters externally 
from FWCore.ParameterSet.VarParsing import VarParsing
params = VarParsing('analysis')

params.register(
    'isMC', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether the sample is simulation or data'
)

params.register(
    'useWeights', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to use the events weights from a Monte Carlo generator'
)

params.register(
    'filterTrigger', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to ask the event to fire a trigger used in the analysis'
)

params.register(
    'filterMuons', 
    True, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to ask the event to contain at least two muons'
)

params.register(
    'reducedInfo', 
    False, 
    VarParsing.multiplicity.singleton,VarParsing.varType.bool,
    'Flag to indicate whether or not to store just the reduced information'
)

params.register(
    'trigProcess', 
    'HLT', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'GlobalTagData', 
    '92X_dataRun2_Prompt_v4', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'GlobalTagMC', 
    '92X_dataRun2_Prompt_v4', 
    VarParsing.multiplicity.singleton,VarParsing.varType.string,
    'Process name for the HLT paths'
)

params.register(
    'xsec', 
    0.001, 
    VarParsing.multiplicity.singleton,VarParsing.varType.float,
    'Cross-section for a Monte Carlo Sample'
)

# Define the process
process = cms.Process("LL")

# Parse command line arguments
params.parseArguments()

# Message Logger settings
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.destinations = ['cout', 'cerr']
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Set the process options -- Display summary at the end, enable unscheduled execution
process.options = cms.untracked.PSet( 
    allowUnscheduled = cms.untracked.bool(True),
    wantSummary      = cms.untracked.bool(False) 
)

# How many events to process
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# Input EDM files
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring([
#		'file:/afs/cern.ch/user/b/bortigno/public/darkphoton/DP_MZd35Epsilon2e-2_fall17_AODSIM_step3.root',
		#'/store/mc/RunIIFall17DRPremix/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/AODSIM/94X_mc2017_realistic_v10-v1/710000/D0953F14-71EB-E711-A97D-02163E01377D.root',
		#'/store/mc/RunIIFall17DRPremix/Muplus_Pt1000-gun/AODSIM/RECOSIMstep_94X_mc2017_realistic_v10-v1/50000/082B4547-48EB-E711-B491-001E67E6F783.root',
        	#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/AEFA61EC-D783-E711-AB3E-02163E013445.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/B4716947-DF83-E711-9B9A-02163E014281.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/BE7B27E8-DA83-E711-94E1-02163E01A1C4.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/C8ECBD88-CE83-E711-8783-02163E014641.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/CE811785-F183-E711-B346-02163E0134FB.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/D60780E1-CB83-E711-B281-02163E01429E.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/397/00000/E0F09602-E283-E711-BE54-02163E01A518.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/398/00000/A805E352-F583-E711-9B0B-02163E01263A.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/34E87E12-F983-E711-BDBD-02163E01A4C2.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/6E97F22C-0E84-E711-830A-02163E011AC9.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/805388B8-0084-E711-A1F1-02163E01A3B7.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/94C20668-F583-E711-9C21-02163E01A628.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/96843482-0284-E711-8049-02163E01A788.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/C8923AB0-0184-E711-8841-02163E01A3B7.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/417/00000/08AE8987-1684-E711-93E6-02163E013480.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/417/00000/0AEE291F-2484-E711-832D-02163E012197.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/417/00000/58A46538-2584-E711-8715-02163E01A5FD.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/183/00000/549B1286-A881-E711-8855-02163E01A420.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/183/00000/5AF3FE8B-A881-E711-B978-02163E01446B.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/183/00000/8A8CCC8B-A881-E711-B400-02163E01A4C0.root',
		#'/store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/417/00000/62C76E07-2084-E711-B113-02163E01A5AA.root',*/
		#'/store/data/Run2018B/ScoutingCaloMuon/RAW/v1/000/317/392/00000/6412DF26-0968-E811-BFD9-FA163E33236D.root',
		'root://cmsxrootd.fnal.gov//store/data/Run2017C/ScoutingCaloMuon/RAW/v1/000/301/399/00000/34E87E12-F983-E711-BDBD-02163E01A4C2.root'
	])
)

# Load the standard set of configuration modules
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')

##--- l1 stage2 digis ---
process.load("EventFilter.L1TRawToDigi.gtStage2Digis_cfi")
process.gtStage2Digis.InputLabel = cms.InputTag( "hltFEDSelectorL1" )
process.load('PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff')


# Load the global tag
from Configuration.AlCa.GlobalTag import GlobalTag
if params.isMC : 
    process.GlobalTag.globaltag = params.GlobalTagMC
else :
    process.GlobalTag.globaltag = params.GlobalTagData

# Define the services needed for the treemaker
process.TFileService = cms.Service("TFileService", 
    fileName = cms.string("scout.root")
)

# Tree for the generator weights
process.gentree = cms.EDAnalyzer("LHEWeightsTreeMaker",
    lheInfo = cms.InputTag("externalLHEProducer"),
    genInfo = cms.InputTag("generator"),
    useLHEWeights = cms.bool(params.useWeights)
)

from DarkPhotonAnalysisV2.DimuonAnalysis.TriggerPaths2017_cfi import getL1Conf

# Make tree
process.mmtree = cms.EDAnalyzer('ScoutingTreeMaker2017',
	isMC             = cms.bool(params.isMC),
	xsec             = cms.double(params.xsec),
	useLHEWeights    = cms.bool(params.useWeights),
	applyHLTFilter   = cms.bool(params.filterTrigger),
	require2Muons    = cms.bool(params.filterMuons),
	storeReducedInfo = cms.bool(params.reducedInfo),
    	triggerresults   = cms.InputTag("TriggerResults", "", params.trigProcess),
	doL1 = cms.bool(True),
        triggerConfiguration = cms.PSet(
    		hltResults            = cms.InputTag('TriggerResults','','HLT'),
    		l1tResults            = cms.InputTag(''),
    		daqPartitions         = cms.uint32(1),
    		l1tIgnoreMaskAndPrescale = cms.bool(False),
    		#l1tIgnoreMask         = cms.bool(False),
   		#l1techIgnorePrescales = cms.bool(False),
    		throw                 = cms.bool(False)
  	),
	ReadPrescalesFromFile = cms.bool( False ),
        AlgInputTag = cms.InputTag("gtStage2Digis"),
        l1tAlgBlkInputTag = cms.InputTag("gtStage2Digis"),
        l1tExtBlkInputTag = cms.InputTag("gtStage2Digis"),
        l1Seeds           = cms.vstring(getL1Conf()),
#	vertices          = cms.InputTag("hltScoutingPrimaryVertexPacker","primaryVtx"),
	vertices          = cms.InputTag("hltScoutingMuonPackerCalo","displacedVtx"),
#	beamspot          = cms.InputTag("")
	muons             = cms.InputTag("hltScoutingMuonPackerCalo"),
	#pfcands          = cms.InputTag("hltScoutingPFPacker"),
	rho               = cms.InputTag("hltScoutingCaloPacker", "rho"),
    	pileupinfo        = cms.InputTag("addPileupInfo"),
    	geneventinfo      = cms.InputTag("generator"),
    	gens              = cms.InputTag("genParticles", "", "HLT")
)

# Analysis path
if params.isMC : 
    process.p = cms.Path(process.gentree + process.mmtree)
else : 
    process.p = cms.Path(  process.gtStage2Digis + process.mmtree)

