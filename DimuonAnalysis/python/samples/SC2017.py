samples = {}

# Each sample has the following information
# Dataset name
# Collection of strings to be passed to cmsRun when running the config file (for VarParsing .. e.g. 'isMC=True')
# JSON file in case of data 
# Number of lumis / events to process

def AddSCSamples(samples):


    samples['ScoutingRunC']  = [
        '/ScoutingCaloMuon/Run2017C-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON_MuonPhys.txt',
        100
    ]

    samples['ScoutingRunD']  = [
        '/ScoutingCaloMuon/Run2017D-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON_MuonPhys.txt',
        100
    ]

    samples['ScoutingRunE']  = [
        '/ScoutingCaloMuon/Run2017E-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON_MuonPhys.txt',
        100
    ]
#"""
    samples['ScoutingRunF']  = [
        '/ScoutingCaloMuon/Run2017F-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON_MuonPhys.txt',
        100
    ]

    
    

