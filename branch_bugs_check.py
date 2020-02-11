import os
import sys
import ROOT 
from ROOT import TH1D, TTree, TFile

fbkg = TFile.Open("/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/F25F8B84-587A-B243-B7A6-34AD053DEDC5_fatjetbaby_TT_TuneCUETP8M2T4_rpvfitnbge0.root")
fsig = TFile.Open("/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/D0256A01-F080-EF4B-9DD7-8816EAB61639_fatjetbaby_SMS-T1tbs_RPV_mGluino1600_TuneCUETP8M1_rpvfitnbge0.root")
fdat = TFile.Open("/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/F6B3A04F-54C9-4A44-B8E7-121662ECAD33_fatjetbaby_JetHTRun2016H_rpvfitnbge0.root")

tbkg = fbkg.Get("tree")
tsig = fsig.Get("tree")
tdat = fdat.Get("tree")

brlist_bkg = tbkg.GetListOfBranches().Clone()
brlist_sig = tsig.GetListOfBranches().Clone()
brlist_dat = tdat.GetListOfBranches().Clone()

brlist = []
histlist = []

for i in range(0, len(brlist_bkg)-1):
	print(brlist_bkg[i])
	brlist.append(brlist_bkg[i].GetName())
	print(brlist[i])
	if brlist[i]=='event':
		continue
	mxbkg = tbkg.GetMaximum(brlist[i])
	mxsig = tsig.GetMaximum(brlist[i])
	mxdat = tdat.GetMaximum(brlist[i])	
	mnbkg = tbkg.GetMinimum(brlist[i])
	mnsig = tsig.GetMinimum(brlist[i])
	mndat = tdat.GetMinimum(brlist[i])
	tbkg.GetEntry(24)
	nbinsbkg = int(mxbkg-mnbkg)
	nbinssig = int(mxsig-mnsig)
	nbinsdat = int(mxdat-mndat)
	if (mxbkg==1 and mnbkg ==0) or (mxsig==1 and mnsig==0) or (mxdat==1 and mndat==0):
		nbinsbkg = 2
		mxbkg = 2
		nbinssig = 2
		mxsig = 2
		nbinsdat = 2
		mxdat = 2 
	if nbinsbkg>=100 or nbinssig>=100 or nbinsdat>=100:
		nbinsbkg = int(nbinsbkg/100)
		nbinssig = int(nbinssig/100)
		nbinsdat = int(nbinsdat/100)
	if nbinsbkg<=0 or nbinssig<=0 or nbinsdat<=0:
		nbinsbkg = 99
		nbinssig = 99
		nbinsdat = 99
	hbkg = TH1D('hbkg','hbkg', nbinsbkg, mnbkg, mxbkg)	
	hsig = TH1D('hsig','hsig', nbinssig, mnsig, mxsig)
	hdat = TH1D('hdat','hdat', nbinsdat, mndat, mxdat)
	#Histogram Section#
	tbkg.Draw(brlist[i]+'>>hbkg',"","goff")
	tsig.Draw(brlist[i]+'>>hsig',"","goff")
	tdat.Draw(brlist[i]+'>>hdat',"","goff")
	hbkg.SetTitle(brlist[i])
	hbkg.SetStats(0)
	hbkg.SetMinimum(0)
	hsig.SetTitle(brlist[i])
	hsig.SetStats(0)
	hsig.SetMinimum(0)
	hdat.SetTitle(brlist[i])
	hdat.SetStats(0)
	hdat.SetMinimum(0)
	c1 = ROOT.TCanvas( 'c1', 'c1', 2400, 800)
	c1.Divide(3,1)
	c1.cd(1)
	hbkg.Draw("")
	c1.cd(2)
	hsig.Draw("")
	c1.cd(3)
	hdat.Draw("")
	c1.Print("./Plots/"+brlist[i]+".png")
	#c1.Print("./Plots/"+brlist[i]+".C")
	hbkg.Reset()
	hsig.Reset()
	hdat.Reset()

