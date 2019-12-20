{
	int NumberOfTag = 46;
	TString tag[NumberOfTag] = {
		"TTTT_TuneCUETP8M2T4",
		"SMS-T1tbs_RPV_mGluino2100_TuneCUETP8M1",
		"WJetsToLNu_HT-600To800_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1200_TuneCUETP8M1",
		"QCD_HT2000toInf_TuneCUETP8M1",
		"ZZZ_TuneCUETP8M1",
		"ST_tW_top_5f_inclusiveDecays",
		"SMS-T1tbs_RPV_mGluino1900_TuneCUETP8M1",
		"WZ_TuneCUETP8M1",
		"WJetsToLNu_HT-800To1200_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1300_TuneCUETP8M1",
		"QCD_HT200to300_TuneCUETP8M1",
		"ZZ_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino2000_TuneCUETP8M1",
		"ST_t-channel_antitop_4f_inclusiveDecays",
		"TTZToQQ_TuneCUETP8M1",
		"ST_tW_antitop_5f_inclusiveDecays",
		"SMS-T1tbs_RPV_mGluino1800_TuneCUETP8M1",
		"ST_t-channel_top_4f_inclusiveDecays",
		"SMS-T1tbs_RPV_mGluino1000_TuneCUETP8M1",
		"QCD_HT1500to2000_TuneCUETP8M1",
		"WJetsToLNu_HT-2500ToInf_TuneCUETP8M1",
		"TT_TuneCUETP8M2T4",
		"TTWJetsToQQ_TuneCUETP8M1",
		"ST_s-channel_4f_leptonDecays",
		"DYJetsToLL_M-50_TuneCUETP8M1",
		"QCD_HT500to700_TuneCUETP8M1",
		"WJetsToLNu_HT-400To600_TuneCUETP8M1",
		"WWW_4F_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1400_TuneCUETP8M1",
		"WW_TuneCUETP8M1",
		"WJetsToLNu_HT-1200To2500_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1100_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1600_TuneCUETP8M1",
		"WZZ_TuneCUETP8M1",
		"DYJetsToLL_M-10to50_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino2200_TuneCUETP8M1",
		"QCD_HT700to1000_TuneCUETP8M1",
		"QCD_HT300to500_TuneCUETP8M1",
		"QCD_HT1000to1500_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1500_TuneCUETP8M1",
		"ST_s-channel_4f_InclusiveDecays",
		"TTZToLLNuNu_M-10_TuneCUETP8M1",
		"SMS-T1tbs_RPV_mGluino1700_TuneCUETP8M1",
		"TTWJetsToLNu_TuneCUETP8M1",
		"WWZ_TuneCUETP8M1"
	};

	TString Path_sample, outputdir;
	Path_sample = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/";
	outputdir = "/cms/scratch/yjeong/RPV_MC/2016/";

	TChain *mc[NumberOfTag];
	static int count;
	for(int i = 0; i < NumberOfTag; i++ ){
		mc[i] = new TChain("tree");
		mc[i].Add(Path_sample+"*_fatjetbaby_"+tag[i]+".root");
		mc[i].Merge(outputdir+tag[i]+".root");
		cout <<"Merging process : "<<tag[i]<<" Complete !!!"<<"  "<<++count<<"/"<<NumberOfTag<<endl;
	}
}
