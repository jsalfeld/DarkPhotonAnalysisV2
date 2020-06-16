#!/bin/bash

declare -a S=()
S+=( `ls -d ScoutingRun*/` )

if [ $# -eq 0 ]
then
    echo "Provide at least one of these arguments : --submit --status --resubmit --kill --clean"

elif [ $# -gt 1 ]
then
    echo "Only one argument allowed"

elif [ $1 != "--status" ] && [ $1 != "--submit" ] && [ $1 != "--resubmit" ] && [ $1 != "--kill" ] && [ $1 != "--clean" ]
then
    echo "One of the following arguments is allowed  : --submit --status --resubmit --kill --clean"

else 
    for X in ${S[@]};
    do
        cd $X/;

        if [ $1 = --status ]
        then
            echo " " 
            echo ---------------------- $X -----------------------
            for Y in `ls -d */`
            do
                crab status -d $Y;
            done
        fi
        
        if [ $1 = --submit ]
        then
            cp ../crabConfig.py ./;
            crab submit;
        fi
        
        if [ $1 = --kill ]
        then
            for Y in `ls -d */`
            do
                crab kill -d $Y;
            done
        fi
        
        if [ $1 = --resubmit ]
        then
            for Y in `ls -d */`
            do
                crab resubmit -d $Y;
            done
        fi
        
        if [ $1 = --clean ]
        then
            rm -rf ./*;
        fi
        
        cd ../;
    done;


fi
