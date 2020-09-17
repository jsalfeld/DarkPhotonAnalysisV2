import os
import subprocess
import commands

m=0.2
for d in range(0,400):
	m=m+(m*0.01)

	#if d<90 or d>112:
	#	continue
	
	print('now at mass', m)
	os.system("combine -M AsymptoticLimits dpCard_2018CIterV0_"+str(d)+".txt -m "+str(m)+" -n asympMassIndex_"+str(d)+"")	
