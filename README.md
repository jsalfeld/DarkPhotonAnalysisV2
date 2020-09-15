# DarkPhotonAnalysisV2

For 2017 data nTuple production:
```
ssh "you"@lxplus6.cern.ch ##important here SLC6
cmsrel CMSSW_9_2_1
cd CMSSW_9_2_1/src
cmsenv
git clone https://github.com/jsalfeld/DarkPhotonAnalysisV2
cd DarkPhotonAnalysisV2/DimuonAnalysis/test/
cmsRun scout2017_cfg.py
```
There is a macro to do selection with, in ```DarkPhotonAnalysisV2/DimuonAnalysis/macros/```. There is a setup ```DarkPhotonAnalysisV2/DimuonAnalysis/crab/``` in to submit samples defined in ```DarkPhotonAnalysisV2/DimuonAnalysis/python/samples``` 


For 2018 data nTuple production:
```
ssh "you"@lxplus.cern.ch
SCRAM_ARCH=slc7_amd64_gcc700
cmsrel CMSSW_10_1_6
cd CMSSW_10_1_6/src
cmsenv
git clone https://github.com/jsalfeld/DarkPhotonAnalysisV2
cd DarkPhotonAnalysisV2/DimuonAnalysis/
scram b -j 8
cd test
cmsRun scout2018_cfg.py
```
