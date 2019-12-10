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

mcfilelist=[
	'65BED8D0-FB9A-8F46-B01B-A41623E5A52D_fatjetbaby_SMS-T1tbs_RPV_mGluino1000_TuneCUETP8M1.root',
	'BD16B6A8-2FD7-8848-A2E7-F85EB04B35BD_fatjetbaby_SMS-T1tbs_RPV_mGluino1100_TuneCUETP8M1.root',
	'0E5405C2-8F38-9E42-A05C-E18D0A2BCB57_fatjetbaby_SMS-T1tbs_RPV_mGluino1200_TuneCUETP8M1.root',
	'1CF81570-BA24-A84C-8833-44005395EB64_fatjetbaby_SMS-T1tbs_RPV_mGluino1300_TuneCUETP8M1.root',
	'0C98ADA9-7A6A-AB46-82FB-7D7451548697_fatjetbaby_SMS-T1tbs_RPV_mGluino1400_TuneCUETP8M1.root',
	'1FCF10AB-F561-2A4A-8D8D-B85B637412B8_fatjetbaby_SMS-T1tbs_RPV_mGluino1500_TuneCUETP8M1.root',
	'3F46567A-A70F-E246-A351-7F314047C617_fatjetbaby_SMS-T1tbs_RPV_mGluino1600_TuneCUETP8M1.root',
	'4BE64D6D-2A6F-454C-A273-1659C26604A8_fatjetbaby_SMS-T1tbs_RPV_mGluino1700_TuneCUETP8M1.root',
	'7E718445-4B82-1B4D-B68D-C951F53B1338_fatjetbaby_SMS-T1tbs_RPV_mGluino1800_TuneCUETP8M1.root',
	'2B68109E-42F2-CE42-8138-599F1FEC809F_fatjetbaby_SMS-T1tbs_RPV_mGluino1900_TuneCUETP8M1.root',
	'A2DAFE0D-FFA8-974D-8976-689ACA066D81_fatjetbaby_SMS-T1tbs_RPV_mGluino2000_TuneCUETP8M1.root',
	'7A9039FF-E878-4942-B7ED-3A963F6E210A_fatjetbaby_SMS-T1tbs_RPV_mGluino2100_TuneCUETP8M1.root',
	'4F1A6A7F-85B2-5E40-A220-DA23E439D561_fatjetbaby_SMS-T1tbs_RPV_mGluino2200_TuneCUETP8M1.root',
	'6CE4E938-769F-D443-AE60-7CCF1492A45C_fatjetbaby_WJetsToLNu_HT-400To600_TuneCUETP8M1.root',
	'087284C3-8175-7741-B9CC-EFE745C7C266_fatjetbaby_WJetsToLNu_HT-600To800_TuneCUETP8M1.root',
	'98B66374-7076-2748-9B40-77570F95D2CF_fatjetbaby_WJetsToLNu_HT-800To1200_TuneCUETP8M1.root',
	'CF75AE97-F7BB-B745-975D-997B31E1EBE1_fatjetbaby_WJetsToLNu_HT-1200To2500_TuneCUETP8M1.root',
	'88AF4FFE-FDA7-004E-9342-41C9CAA23D34_fatjetbaby_WJetsToLNu_HT-2500ToInf_TuneCUETP8M1.root',
	'2725B9D3-60CD-AF4E-AB70-413D0744A3AA_fatjetbaby_QCD_HT200to300_TuneCUETP8M1.root',
	'A9A81D00-8C3C-9341-969B-21B2F0CC5D84_fatjetbaby_QCD_HT300to500_TuneCUETP8M1.root',
	'8FD118C1-2B61-7443-9C31-2D4E05B9130F_fatjetbaby_QCD_HT500to700_TuneCUETP8M1.root',
	'6C1E3A79-7B26-124F-87CC-02E25BBD454A_fatjetbaby_QCD_HT700to1000_TuneCUETP8M1.root',
	'2A038441-7CED-6D42-805B-6C18E07CFFB3_fatjetbaby_QCD_HT1000to1500_TuneCUETP8M1.root',
	'4E6BEC34-2E0F-F345-B6D1-91D63719DE44_fatjetbaby_QCD_HT1500to2000_TuneCUETP8M1.root',
	'7826DAE5-24E5-F14D-BF57-CFDEC63D56E9_fatjetbaby_QCD_HT2000toInf_TuneCUETP8M1.root',
	'0EE7C7D0-E04B-5747-A0BD-F68AEE97904C_fatjetbaby_ST_tW_top_5f_inclusiveDecays.root',
	'01FE8033-D0A6-5D47-8853-F0ED75799043_fatjetbaby_ST_tW_antitop_5f_inclusiveDecays.root',
	'57DD964C-E49A-954E-87B5-854081F55713_fatjetbaby_ST_s-channel_4f_leptonDecays.root',
	'F35B5498-4B67-264A-812F-E64852A9EC82_fatjetbaby_ST_s-channel_4f_InclusiveDecays.root',
	'0C72E1E0-B36D-2C46-9EA2-9065BFC1821F_fatjetbaby_ST_t-channel_antitop_4f_inclusiveDecays.root',
	'A06AF59A-AA71-6141-B6DB-1A13DFAC0F7E_fatjetbaby_ST_t-channel_top_4f_inclusiveDecays.root',
	'8AF666A0-A0A7-884F-91BF-9E57F708EB3E_fatjetbaby_DYJetsToLL_M-50_TuneCUETP8M1.root',
	'1FFC254C-D107-F94B-B1BC-4B992942A991_fatjetbaby_DYJetsToLL_M-10to50_TuneCUETP8M1.root',
	'5C91C014-766B-8E4C-A418-A5EC9EDFA59F_fatjetbaby_WZ_TuneCUETP8M1.root',
	'5B3ACB49-51FB-9546-9262-06A7EA6522A7_fatjetbaby_WW_TuneCUETP8M1.root',
	'CF5913EA-2CD0-E54C-BB75-EBC9A6EAC853_fatjetbaby_ZZ_TuneCUETP8M1.root',
	'2AC1B3AD-3A47-A944-B8CF-784F34EAD830_fatjetbaby_TTZToQQ_TuneCUETP8M1.root',
	'92980F73-B737-DA48-9BC9-A6F759883C8F_fatjetbaby_TTZToLLNuNu_M-10_TuneCUETP8M1.root',
	'9A3DBAAE-7A8C-D540-A62A-74AE0AF13595_fatjetbaby_TT_TuneCUETP8M2T4.root',
	'5074FBFB-CDB5-DB4B-812A-06C504DE1885_fatjetbaby_TTWJetsToLNu_TuneCUETP8M1.root',
	'86B5FA8B-86E1-1249-B7B3-2D83D24D5E10_fatjetbaby_TTWJetsToQQ_TuneCUETP8M1.root',
	'9DA03B56-3C39-5148-939C-8F6181BC422D_fatjetbaby_WWW_4F_TuneCUETP8M1.root',
	'805B8B63-030F-624A-99F7-97B7A5038E4C_fatjetbaby_WZZ_TuneCUETP8M1.root',
	'D0D17A1C-7E0E-EE42-9E8F-0BD3A6065138_fatjetbaby_ZZZ_TuneCUETP8M1.root',
	'B1D295EC-DEF7-1E4C-8548-A2DB8EDEBEF9_fatjetbaby_WWZ_TuneCUETP8M1.root',
	'0240D362-1E08-E541-BDC7-623D912C2480_fatjetbaby_TTTT_TuneCUETP8M2T4.root'
]

if year == "2017":
	mcfilelist=[
	'118C47B8-4AEA-E246-8960-5F047B82CD77_fatjetbaby_SMS-T1tbs_RPV_mGluino1000_TuneCP2.root',
	'CCCA38AD-4BB0-D049-822B-DBC18AB371F8_fatjetbaby_SMS-T1tbs_RPV_mGluino1100_TuneCP2.root',
	'CEA377F4-231F-E74C-885F-1FDA8D1E8507_fatjetbaby_SMS-T1tbs_RPV_mGluino1200_TuneCP2.root',
	'A59915C3-F33F-7F4E-BD87-A971FF02D5DB_fatjetbaby_SMS-T1tbs_RPV_mGluino1300_TuneCP2.root',
	'11A98E94-DFF2-554E-A0E3-BE4C5F54AA1C_fatjetbaby_SMS-T1tbs_RPV_mGluino1400_TuneCP2.root',
	'CCB656C8-6FD5-494C-96F1-A61ADB5F989D_fatjetbaby_SMS-T1tbs_RPV_mGluino1600_TuneCP2.root',
	'B60C3DCD-A008-7A4E-BA75-B3AFD5DA614E_fatjetbaby_SMS-T1tbs_RPV_mGluino1700_TuneCP2.root',
	'561558F9-48F4-A44B-BE8E-0D1E445760D9_fatjetbaby_SMS-T1tbs_RPV_mGluino2000_TuneCP2.root',
	'D8C5D653-11C2-3743-BCB7-5F50A28FE1AE_fatjetbaby_SMS-T1tbs_RPV_mGluino2100_TuneCP2.root',
	'9EEAD34E-B715-2042-8018-D782BA71012C_fatjetbaby_SMS-T1tbs_RPV_mGluino2200_TuneCP2.root',
	'C5B17F1F-0CE2-CF46-B5F2-39C53B2E34D1_fatjetbaby_QCD_HT100to200_TuneCP5.root',
	'9830B7CA-BB11-5641-A0C3-EB4BBFDCEE50_fatjetbaby_QCD_HT200to300_TuneCP5.root',
	'53E4D61D-4E40-1241-80A9-ABA93C5DF063_fatjetbaby_QCD_HT300to500_TuneCP5.root',
	'CAEB2603-BC29-E943-BEA8-F0F0321ED5C5_fatjetbaby_QCD_HT500to700_TuneCP5.root',
	'CA82CA10-F6E4-3F4F-BEF3-310A74A61A53_fatjetbaby_QCD_HT700to1000_TuneCP5.root',
	'79540BE0-E33E-514D-AEDC-5C617E04DA1A_fatjetbaby_QCD_HT1000to1500_TuneCP5.root',
	'91396482-AE5F-9B4B-962F-EDA1A884DC9A_fatjetbaby_QCD_HT1500to2000_TuneCP5.root',
	'20D60F68-810C-434A-8D5F-E875CC2B3FCA_fatjetbaby_QCD_HT2000toInf_TuneCP5.root',
	'73C48567-85B8-2B41-805F-A9468374E071_fatjetbaby_WJetsToLNu_HT-200To400_TuneCP5.root',
	'1BAFF7C5-BC96-0D42-B6BA-768AA6DC244A_fatjetbaby_WJetsToLNu_HT-400To600_TuneCP5.root',
	'9ABF77A8-87C8-A743-B43D-12E65201F224_fatjetbaby_WJetsToLNu_HT-600To800_TuneCP5.root',
	'998A45FB-35E2-CA4D-8B05-5A0CD9012981_fatjetbaby_WJetsToLNu_HT-800To1200_TuneCP5.root',
	'912285A4-CDA6-E64C-B80F-7D71CE6EAAC8_fatjetbaby_WJetsToLNu_HT-1200To2500_TuneCP5.root',
	'9FF4E66C-6E22-564C-9683-8C9BBCA653F9_fatjetbaby_WJetsToLNu_HT-2500ToInf_TuneCP5.root',
	'2EB22C8F-0437-DC45-B367-D60648F680C2_fatjetbaby_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5.root',
	'7BE73617-2ACF-454B-9B83-8114DDD985AB_fatjetbaby_ST_t-channel_top_4f_inclusiveDecays_TuneCP5.root',
	'2D33403A-4F83-F242-8E8B-E900C6C55662_fatjetbaby_ST_tW_top_5f_inclusiveDecays_TuneCP5.root',
	'AC2CDECE-82D4-D941-8EBC-3E33A3E0D8E8_fatjetbaby_ST_tW_antitop_5f_inclusiveDecays_TuneCP5.root',
	'99E72BCA-022E-0545-AA44-4642171701DF_fatjetbaby_ST_s-channel_4f_leptonDecays_TuneCP5.root',
	'622C16AB-3234-5148-BFDF-6B35EBCBC031_fatjetbaby_DYJetsToLL_M-50_TuneCP5.root',
	'876594AA-BA82-8543-8F3B-FC0F30FF3B86_fatjetbaby_DYJetsToLL_M-10to50_TuneCP5.root',
	'9AD059EA-C578-3C49-908E-44A5E0CEA5A8_fatjetbaby_WZZ_TuneCP5.root',
	'BA1440B5-8F63-8748-AD3D-6D140FDBCE34_fatjetbaby_WWZ_4F_TuneCP5.root',
	'83D276EF-B34B-0249-847A-B2C47D98D35C_fatjetbaby_WWW_4F_TuneCP5.root',
	'5516A1AC-5EE0-2E4A-83DC-40A7269EA0FD_fatjetbaby_ZZZ_TuneCP5.root',
	'62AD844D-9A34-3C42-8F01-520BB88EF478_fatjetbaby_TTWJetsToLNu_TuneCP5.root',
	'EAEC120E-D192-F042-9E3A-5EDC59F913E4_fatjetbaby_TTJets_TuneCP5.root',
	'7CE18298-D8EB-554B-A1A9-9DA185EBB0A1_fatjetbaby_TTWJetsToQQ_TuneCP5.root',
	'34A535F7-FAC1-604D-B226-43DB1DAB2FDD_fatjetbaby_TTZToQQ_TuneCP5.root',
	'0D21586B-C001-6A41-A06B-63260FE54F3A_fatjetbaby_TTZToLLNuNu_M-10_TuneCP5.root',
	'74D69851-EB7F-BF4B-AC41-17989D4FB9FF_fatjetbaby_TTWW_TuneCP5.root',
	'8DC8188D-246C-6D41-A24A-78C0CBBC6F17_fatjetbaby_ZZ_TuneCP5.root',
	'6483D1AD-062C-DE42-8590-3AC6BE5DF6A8_fatjetbaby_WZ_TuneCP5.root',
	'1ABA4820-0167-4C4F-99BB-2A936554C3AD_fatjetbaby_WW_TuneCP5.root',
	'72F9BB63-F69D-DA4D-A042-22077BE4F080_fatjetbaby_TTTT_TuneCP5.root'
]

if year == "2018":
	mcfilelist=[
		'226A9772-2645-E94B-A8A7-0C91FE200FBA_fatjetbaby_SMS-T1tbs_RPV_mGluino1000_TuneCP2.root',
		'B78F0ADB-A949-4F47-B55F-FC20E1069651_fatjetbaby_SMS-T1tbs_RPV_mGluino1100_TuneCP2.root',
		'E0997843-0C39-1A45-A0E0-2889DF17950D_fatjetbaby_SMS-T1tbs_RPV_mGluino1200_TuneCP2.root',
		'AE1026D8-0EF7-C841-B4E8-F407434BD728_fatjetbaby_SMS-T1tbs_RPV_mGluino1300_TuneCP2.root',
		'3F75AEC2-852B-1F4C-87F7-A143080B6888_fatjetbaby_SMS-T1tbs_RPV_mGluino1400_TuneCP2.root',
		'2133B12E-A851-854D-8CD0-F1E154A919A3_fatjetbaby_SMS-T1tbs_RPV_mGluino1500_TuneCP2.root',
		'047491A6-AAA2-004A-8238-DF9004A167EA_fatjetbaby_SMS-T1tbs_RPV_mGluino1600_TuneCP2.root',
		'10EA471A-00BC-F549-80A8-CFC66699B539_fatjetbaby_SMS-T1tbs_RPV_mGluino1700_TuneCP2.root',
		'B6BD9D2B-5670-9F42-B1EA-9C075A191AA4_fatjetbaby_SMS-T1tbs_RPV_mGluino1800_TuneCP2.root',
		'1265E85C-4BDF-9B44-BF5D-A06C85F9548A_fatjetbaby_SMS-T1tbs_RPV_mGluino1900_TuneCP2.root',
		'D2BAC3EC-77AE-3346-903B-597318C437F6_fatjetbaby_SMS-T1tbs_RPV_mGluino2000_TuneCP2.root',
		'6CC39734-930C-284E-9BFF-AF52607BB321_fatjetbaby_SMS-T1tbs_RPV_mGluino2100_TuneCP2.root',
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

print('---------------------------------------------cross section check----------------------------------------------')
print('%46s %3s %26s' %(year, "tag", "Xsection"))
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
print('%46s %3s %10s %15s %15s' %(year, "tag", "flist", "processed", "completion"))
print('--------------------------------------------------------------------------------------------------------------')

# compare flist and the output directory, and generate a status summary table
flists = os.listdir(flistdir)
for flist in flists:
#flist_WW_TuneCP5.txt
	tag=flist.replace('.txt','').replace('flist_','') # extract tag
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

