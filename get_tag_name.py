import os
import sys
year=sys.argv[1]

simple_in = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/"
simple_out = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/"

listfile = open(simple_out+'tag_list_2016.txt','w')
path = simple_in+"2016v4/2019_12_10/skim_rpvfitnbge0/"

if year == "2017":
	listfile = open(simple_out+'tag_list_2017.txt','w')
	path = simple_in+"2017v4/2019_10_23/skim_rpvfit/"

if year == "2018":
	listfile = open(simple_out+'tag_list_2018.txt','w')
	path = simple_in+"2018v4/2019_10_23/skim_rpvfit/"

file_list = os.listdir(path)
process=[]

for flist in file_list:
	tag=flist.replace('.root','').replace('_rpvfitnbge0','').split('fatjetbaby_')
	process.append(tag[1])

process = list(set(process))

for i in range(0, len(process)-1):	
	listfile.write(process[i])
	listfile.write('\n')

listfile.close()
