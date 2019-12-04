#!/usr/bin/env python
import sys
import os
import os.path
import glob
import ROOT
ROOT.gROOT.SetBatch(True)
year=sys.argv[1]

outputdir="/xrootd_user/yjeong/xrootd/nanoprocessing/2016/"
#mcfilelist=['B9BE0928-B0F3-1A48-A7C7-253C2A9914AD_fatjetbaby_SMS-T1tbs_RPV_mGluino1000_TuneCUETP8M1.root']
if year == "2017":
	outputdir="/xrootd_user/yjeong/xrootd/nanoprocessing/2017/"
	#mcfilelist=['F913867E-4152-3D46-BBD4-21577739C5C7_fatjetbaby_WJetsToLNu_HT-800To1200_TuneCP5.root']
if year == "2018":
	outputdir="/xrootd_user/yjeong/xrootd/nanoprocessing/2018/"
	mcfilelist=['047491A6-AAA2-004A-8238-DF9004A167EA_fatjetbaby_SMS-T1tbs_RPV_mGluino1600_TuneCP2.root',
		'2133B12E-A851-854D-8CD0-F1E154A919A3_fatjetbaby_SMS-T1tbs_RPV_mGluino1500_TuneCP2.root',
		'B6BD9D2B-5670-9F42-B1EA-9C075A191AA4_fatjetbaby_SMS-T1tbs_RPV_mGluino1800_TuneCP2.root',
		'10EA471A-00BC-F549-80A8-CFC66699B539_fatjetbaby_SMS-T1tbs_RPV_mGluino1700_TuneCP2.root',
		'226A9772-2645-E94B-A8A7-0C91FE200FBA_fatjetbaby_SMS-T1tbs_RPV_mGluino1000_TuneCP2.root',
		'1265E85C-4BDF-9B44-BF5D-A06C85F9548A_fatjetbaby_SMS-T1tbs_RPV_mGluino1900_TuneCP2.root',
		'3F75AEC2-852B-1F4C-87F7-A143080B6888_fatjetbaby_SMS-T1tbs_RPV_mGluino1400_TuneCP2.root',
		'B78F0ADB-A949-4F47-B55F-FC20E1069651_fatjetbaby_SMS-T1tbs_RPV_mGluino1100_TuneCP2.root',
		'6CC39734-930C-284E-9BFF-AF52607BB321_fatjetbaby_SMS-T1tbs_RPV_mGluino2100_TuneCP2.root',
		'AE1026D8-0EF7-C841-B4E8-F407434BD728_fatjetbaby_SMS-T1tbs_RPV_mGluino1300_TuneCP2.root',
		'D2BAC3EC-77AE-3346-903B-597318C437F6_fatjetbaby_SMS-T1tbs_RPV_mGluino2000_TuneCP2.root',
		'E0997843-0C39-1A45-A0E0-2889DF17950D_fatjetbaby_SMS-T1tbs_RPV_mGluino1200_TuneCP2.root',
		'7915D234-F191-1944-AC0B-4A3ABDDF2A6B_fatjetbaby_SMS-T1tbs_RPV_mGluino2200_TuneCP2.root',
		'05D18498-1CF3-D041-800C-E8DD650B9E89_fatjetbaby_ST_t-channel_top_4f_InclusiveDecays_TuneCP5.root',
		'00EC7DAB-E404-C34B-854B-4CB06884703A_fatjetbaby_ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5.root',
		'F087BEA4-D52F-594C-961C-6BDD7D06EC6E_fatjetbaby_ST_tW_top_5f_inclusiveDecays_TuneCP5.root',
		'D6F15CA3-5C99-D74A-8E01-23B1DF2509F7_fatjetbaby_ST_tW_antitop_5f_inclusiveDecays_TuneCP5.root',
		'DAC962A5-D4F9-1146-B99D-25412A760E98_fatjetbaby_ST_s-channel_4f_leptonDecays_TuneCP5.root',
		'FDE30F30-EC05-2C43-B26E-3E8701E35486_fatjetbaby_QCD_HT100to200_TuneCP5.root',
		'FC90C07E-F518-8E48-9532-5B196EBFB930_fatjetbaby_QCD_HT200to300_TuneCP5.root',
		'FAB5966A-FDBD-C04D-A5D1-34F4AEE59F71_fatjetbaby_QCD_HT300to500_TuneCP5.root',
		'FEDD6502-A97F-4740-A884-53255555E435_fatjetbaby_QCD_HT500to700_TuneCP5.root',
		'DDB2ED1A-2799-6D4D-98D0-94CBA8070694_fatjetbaby_QCD_HT700to1000_TuneCP5.root',
		'F09BEEB2-CFB2-BC4A-B3AF-5C79B36DE27B_fatjetbaby_QCD_HT1000to1500_TuneCP5.root',
		'07A1120E-5F1B-8A49-877E-4C430F5464BE_fatjetbaby_QCD_HT1500to2000_TuneCP5.root',
		'F6A10DBF-078C-EF4C-8A34-A1424BAB74C0_fatjetbaby_QCD_HT2000toInf_TuneCP5.root',
		'F87C9678-E621-E84D-9381-0108F2A7396C_fatjetbaby_WJetsToLNu_HT-200To400_TuneCP5.root',
                '0A70AF21-CD19-5C45-B94A-F6EF9C7E7C7E_fatjetbaby_WJetsToLNu_HT-400To600_TuneCP5.root',
                'FE49104C-A17B-AD4B-B315-321D1C861D31_fatjetbaby_WJetsToLNu_HT-600To800_TuneCP5.root',
                'FDE57421-497F-BA4F-863B-F5A46CE35624_fatjetbaby_WJetsToLNu_HT-800To1200_TuneCP5.root',
                'F95A2921-8785-7147-8663-4874444E41CF_fatjetbaby_WJetsToLNu_HT-1200To2500_TuneCP5.root',
                '3CFEFDD0-F466-FC4D-A4AE-D1565448F117_fatjetbaby_WJetsToLNu_HT-2500ToInf_TuneCP5.root',
		'AD542D69-B400-E344-BDA9-F4423FD29F41_fatjetbaby_WZZ_TuneCP5.root',
		'F761513F-84A1-0047-9C2B-70B28E75B2D3_fatjetbaby_WWW_4F_TuneCP5.root',
		'CC7C3EE0-68E6-D347-8901-09A7DAFC3C17_fatjetbaby_WWZ_TuneCP5.root',
		'04C4802B-BD22-2A48-A998-75BD4248499E_fatjetbaby_ZZZ_TuneCP5.root',
		'2680A039-A67D-884E-991C-A8A63DCCC820_fatjetbaby_TTWJetsToQQ_TuneCP5.root',
		'F3F4B9F3-47B9-404D-86F6-B32F99ED7C9F_fatjetbaby_TTWJetsToLNu_TuneCP5.root',
		'8B78960A-C88A-D846-9BCF-6272B6F3C4EC_fatjetbaby_TTJets_TuneCP5.root',
		'B49727B5-80EA-AE42-8D2D-8CA52FFDD11E_fatjetbaby_TTZToQQ_TuneCP5.root',
		'E41E2904-9D00-CE4C-B7B3-1B7594BA2BAF_fatjetbaby_TTZToLLNuNu_M-10_TuneCP5.root',
		'ED676302-6790-5943-82EA-AFCD42C616A8_fatjetbaby_ZZ_TuneCP5.root',
		'57B58E32-AFAA-B044-9083-AB789FF9B3A6_fatjetbaby_WZ_TuneCP5.root',
		'F2CAB2DB-1B08-D848-821B-44E9A1651AE3_fatjetbaby_WW_TuneCP5.root',
		'30F44A1B-E74B-6F4A-9088-1D1170542117_fatjetbaby_TTTT_TuneCP5.root'
]

if year == "2018":
 print('---------------------------------------------cross section check----------------------------------------------')
 print('%50s %26s' %("tag", "Xsection"))
 print('--------------------------------------------------------------------------------------------------------------')
 for i, mcname in enumerate(mcfilelist):
  tag=mcname.replace('.root','').replace('_TuneCP5','').replace('_TuneCP2','').split("fatjetbaby_")
  rfname = outputdir+mcname
  f=ROOT.TFile(rfname)
  t = f.Get("tree")
  t.GetEntry()
  print('%50s %26.1f' %(tag[1], t.xsec))
 print('--------------------------------------------------------------------------------------------------------------')


flistdir="/cms/ldap_home/yjeong/flist/"+year

print('--------------------------------------------------------------------------------------------------------------')
print('%50s %10s %15s %15s' %("tag", "flist", "processed", "completion"))
print('--------------------------------------------------------------------------------------------------------------')

# compare flist and the output directory, and generate a status summary table
flists = os.listdir(flistdir)
for flist in flists:
#flist_WW_TuneCP5.txt
	if year == "2016":
	 tag=flist.replace('.txt','').replace('flist_','').replace('_TuneCUETP8M1','').replace('_TuneCUETP8M2T4','') # extract tag
	if year == "2017" or year == "2018":
	 tag=flist.replace('.txt','').replace('flist_','').replace('_TuneCP5','').replace('_TuneCP2','') # extract tag
	if "outputdir" in tag:
		continue
	num_lines = sum(1 for line in open(flistdir+"/"+flist)) # number of files in flist
	num_processed = sum(1 for line in glob.glob(outputdir+"*_fatjetbaby_"+tag+"*")) # number of files processed

	print('%50s %10d %15d %15.1f%%' %(tag, num_lines, num_processed, 1.0*num_processed/num_lines*100))
print('--------------------------------------------------------------------------------------------------------------')

# generate list of files that have been processed
splits = outputdir.split("/")
list_output_file = open("/cms/ldap_home/yjeong/flist/flist_outputdir_"+splits[4]+"_"+splits[5]+".txt", "w")

lines = os.listdir(outputdir)
for line in lines:
	if ".root" not in line: continue
	list_output_file.write(line+"\n")

list_output_file.close()

