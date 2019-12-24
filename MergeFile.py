import os
import sys
import ROOT
from ROOT import TChain, TSelector, TTree, TH1F, TCanvas, TPad, TStyle, TString
year=sys.argv[1]

simple_in = "/cms/ldap_home/jaehyeok/nanoprocessing/condor/xrootd/"
simple_out = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/mc/"

inputdir = simple_in+"2016v4/2019_12_10/skim_rpvfitnbge0/"
outputdir = simple_out+"2016/"

if year == "2017":
	inputdir = simple_in+"2017v4/2019_10_23/skim_rpvfit/"
	outputdir = simple_out+"2017/"

if year == "2018":
	inputdir = simple_in+"2018v4/2019_10_23/skim_rpvfit/"
	outputdir = simple_out+"2018/"

flists = os.listdir(inputdir)
print('---------------------------------------------------'+year+'-------------------------------------------------------')
print('%40s %20s %25s %20s' %("tag", "Merged files", "Not merged event", 'Merged event'))
print('--------------------------------------------------------------------------------------------------------------')

for flist in flists:
	tag = flist.replace('.root','').replace('_rpvfitnbge0','').split("fatjetbaby_")
	if year == 2017 or year == 2018:
		tag = flist.replace('.root','').replace('_rpvfit','').split("fatjetbaby_")
	mc = TChain("tree")
	mc.Add(inputdir+"*_fatjetbaby_"+tag[1]+"_rpvfitnbge0"+".root")
	nfiles=mc.Add(inputdir+"*_fatjetbaby_"+tag[1]+"_rpvfitnbge0"+".root")
	nfiles=str(nfiles)
	t1 = mc.GetEntries()
	t1 = str(t1)
	mc.Merge(outputdir+tag[1]+"_"+nfiles+".root")
	t2 = mc.GetEntries()
	t2 = str(t2)
	print('%40s %20s %25s %20s' %(tag[1], nfiles, t1, t2))
print('--------------------------------------------------------------------------------------------------------------')
