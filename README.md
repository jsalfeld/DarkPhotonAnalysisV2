# DarkPhotonAnalysisV2

For 2017 nTuple production:
```
ssh "you"@lxplus6.cern.ch ##important here SLC6
cmsrel CMSSW_9_2_1
cd CMSSW_9_2_1/src
cmsenv
git clone https://github.com/jsalfeld/DarkPhotonAnalysisV2
cd DarkPhotonAnalysisV2/DimuonAnalysis/test/
cmsRun scout2017_cfg.py
```
There is a macro to do selection with, in ```DarkPhotonAnalysisV2/DimuonAnalysis/test/```. There is a setup ```DarkPhotonAnalysisV2/DimuonAnalysis/crab/``` in to submit samples defined in ```DarkPhotonAnalysisV2/DimuonAnalysis/python/samples``` 
