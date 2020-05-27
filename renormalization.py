import sys
import os
import os.path
import glob
import ROOT
from ROOT import TChain, TSelector, TTree, TH1F, TCanvas, TPad, TStyle, TString, TH1D
ROOT.gROOT.SetBatch(True)
year = sys.argv[1]

inputdir="/xrootd_user/yjeong/xrootd/nanoprocessing/"+year+"/processed/"

flistdir = "/cms/ldap_home/yjeong/flist/"+year
flists = os.listdir(flistdir)
h_btag = ROOT.TH1D("h_btag","",1,0,100)

print('-------------------------------------------btag_dcsv_weight check---------------------------------------------')
print('%46s %3s %26s' %(year, "tag", "btag_dcsv"))
print('--------------------------------------------------------------------------------------------------------------')

for i, mcname in enumerate(flists):
	tag = mcname.replace('.txt','').replace('flist_','')
	mc = TChain("tree")
	mc.Add(inputdir+"*_fatjetbaby_"+tag+".root")
	mc.GetEntry()
	mc.Draw("w_btag_dcsv>>h_btag","","goff")
	btag_mean = h_btag.GetMean()
	print('%50s %26.2f' %(tag, btag_mean))
print('--------------------------------------------------------------------------------------------------------------')


