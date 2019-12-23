import os
import sys
year=sys.argv[1]

listfile = open('file_list_2016.txt','w')
path = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0"

if year == "2017":
	listfile = open('file_list_2017.txt','w')
	path = "/xrootd_user/yjeong/xrootd/nanoprocessing/2017"

if year == "2018":
	listfile = open('file_list_2018.txt','w')
	path = "/xrootd_user/yjeong/xrootd/nanoprocessing/2018"

file_list = os.listdir(path)
process=[]

for flist in file_list:
	tag=flist
	process.append(tag)

process = list(set(process))

for i in range(0, len(process)-1):	
	listfile.write(process[i])
	listfile.write('\n')

listfile.close()
