#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /afs/cern.ch/work/j/jsalfeld/Princeton/DarkStuff/newPackage/CMSSW_10_1_6/src/DarkPhotonAnalysisV2/DimuonAnalysis/macros/

eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers

in=/$1
out2="${in/scout_/hists18C_}"
out="/afs/cern.ch/work/j/jsalfeld/Princeton/DarkStuff/newPackage/CMSSW_10_1_6/src/DarkPhotonAnalysisV2/DimuonAnalysis/macros/"$out2
echo $out

root -l -b trimscoutMakeTheCardsLMnew_2018C.C\(\"$in\"\,\"$out\"\,false\)
