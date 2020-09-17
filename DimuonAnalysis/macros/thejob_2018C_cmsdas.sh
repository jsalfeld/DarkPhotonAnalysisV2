#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd $2

eval `scramv1 runtime -sh` # cmsenv is an alias not on the workers

in=/$1
out2="${in/scout_/hists18C_cmsdas}"
out=$2/$out2
echo $out

root -l -b trimscoutMakeTheCardsLMnew_2018C_cmsdas.C\(\"$in\"\,\"$out\"\,false\)
