import os
import sys
from ROOT import TChain, TSelector, TTree, TH1F, TCanvas, TPad, TStyle, TString
#year=sys.argv[1]

inputdir = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/"
outputdir = "/cms/scratch/yjeong/RPV_MC/2016/"

filename="file_list_2016"
tagname=open("/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/"+filename+".txt",'r')

flists = os.listdir(inputdir)
#for i, mcname in enumerate(tagname):
for flist in flists:
	tag = flist.replace('.root','').replace('_rpvfitnbge0','').split("fatjetbaby_")
	mc = TChain("tree")
	mc.Add(inputdir+"*_fatjetbaby_"+tag[1]+"_rpvfitnbge0"+".root")
	mc.Merge(outputdir+tag[1]+".root")
