import os
import sys
from ROOT import TChain, TSelector, TTree, TH1F, TCanvas, TPad, TStyle, TString
year=sys.argv[1]

inputdir = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/"
outputdir = "/cms/scratch/yjeong/RPV_MC/2016/"

if year == "2017":
	inputdir = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/2017v4/2019_10_23/skim_rpvfit/"
	outputdir = "/cms/scratch/yjeong/RPV_MC/2017/"

if year == "2018":
	inputdir = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/2018v4/2019_10_23/skim_rpvfit"
	outputdir = "/cms/scratch/yjeong/RPV_MC/2018/"

flists = os.listdir(inputdir)
for flist in flists:
	tag = flist.replace('.root','').replace('_rpvfitnbge0','').split("fatjetbaby_")
	if year == 2017 or year == 2018:
		tag = flist.replace('.root','').replace('_rpvfit','').split("fatjetbaby_")
	mc = TChain("tree")
	mc.Add(inputdir+"*_fatjetbaby_"+tag[1]+"_rpvfitnbge0"+".root")
	mc.Merge(outputdir+tag[1]+".root")
