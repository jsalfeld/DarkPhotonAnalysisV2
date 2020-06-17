samples = {}

# Each sample has the following information
# Dataset name
# Collection of strings to be passed to cmsRun when running the config file (for VarParsing .. e.g. 'isMC=True')
# JSON file in case of data 
# Number of lumis / events to process

def AddSCSamples(samples):


    samples['ScoutingRunA']  = [
        '/ScoutingCaloMuon/Run2018A-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON_MuonPhys.txt',
        100
    ]

    samples['ScoutingRunB']  = [
        '/ScoutingCaloMuon/Run2018B-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON_MuonPhys.txt',
        100
    ]

    samples['ScoutingRunC']  = [
        '/ScoutingCaloMuon/Run2018C-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON_MuonPhys.txt',
        100
    ]


    samples['ScoutingRunD']  = [
        '/ScoutingCaloMuon/Run2018D-v1/RAW',
        [],
        'LumiBased',
        '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON_MuonPhys.txt',
        100
    ]

