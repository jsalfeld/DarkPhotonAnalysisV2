#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /afs/cern.ch/work/j/jsalfeld/Princeton/DarkStuff/CMSSW_9_4_6/src/DarkPhotonAnalysis/DimuonAnalysis2017/macros/

eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers

in=/$1
out2="${in/scout_/hists_}"
out="/afs/cern.ch/work/j/jsalfeld/Princeton/DarkStuff/CMSSW_9_4_6/src/DarkPhotonAnalysis/DimuonAnalysis2017/macros/"$out2
echo $out

root -l -b trimscoutMakeTheCardsLMnew.C\(\"$in\"\,\"$out\"\,false\)
