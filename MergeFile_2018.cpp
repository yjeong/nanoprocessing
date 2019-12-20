{
	int NumberOfTag = 45;
	TString tag[NumberOfTag] = {
		"QCD_HT1000to1500_TuneCP5",
		"QCD_HT100to200_TuneCP5",
		"QCD_HT1500to2000_TuneCP5",
		"QCD_HT2000toInf_TuneCP5",
		"QCD_HT200to300_TuneCP5",
		"QCD_HT300to500_TuneCP5",
		"QCD_HT500to700_TuneCP5",
		"QCD_HT700to1000_TuneCP5",
		"SMS-T1tbs_RPV_mGluino1000_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1100_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1200_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1300_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1400_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1500_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1600_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1700_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1800_TuneCP2",
		"SMS-T1tbs_RPV_mGluino1900_TuneCP2",
		"SMS-T1tbs_RPV_mGluino2000_TuneCP2",
		"SMS-T1tbs_RPV_mGluino2100_TuneCP2",
		"SMS-T1tbs_RPV_mGluino2200_TuneCP2",
		"ST_s-channel_4f_leptonDecays_TuneCP5",
		"ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5",
		"ST_t-channel_top_4f_InclusiveDecays_TuneCP5",
		"ST_tW_antitop_5f_inclusiveDecays_TuneCP5",
		"ST_tW_top_5f_inclusiveDecays_TuneCP5",
		"TTJets_TuneCP5",
		"TTTT_TuneCP5",
		"TTWJetsToLNu_TuneCP5",
		"TTWJetsToQQ_TuneCP5",
		"TTZToLLNuNu_M-10_TuneCP5",
		"TTZToQQ_TuneCP5",
		"WJetsToLNu_HT-1200To2500_TuneCP5",
		"WJetsToLNu_HT-200To400_TuneCP5",
		"WJetsToLNu_HT-2500ToInf_TuneCP5",
		"WJetsToLNu_HT-400To600_TuneCP5",
		"WJetsToLNu_HT-600To800_TuneCP5",
		"WJetsToLNu_HT-800To1200_TuneCP5",
		"WWW_4F_TuneCP5",
		"WWZ_TuneCP5",
		"WW_TuneCP5",
		"WZZ_TuneCP5",
		"WZ_TuneCP5",
		"ZZZ_TuneCP5",
		"ZZ_TuneCP5"
	};

	TString Path_sample, outputdir;
	Path_sample = "/xrootd_user/yjeong/xrootd/nanoprocessing/2018/";
	outputdir = "/cms/scratch/yjeong/RPV_MC/2018/";

	TChain *mc[NumberOfTag];
	static int count;
	for(int i = 0; i < NumberOfTag; i++ ){
		mc[i] = new TChain("tree");
		mc[i].Add(Path_sample+"*_fatjetbaby_"+tag[i]+".root");
		mc[i].Merge(outputdir+tag[i]+".root");
		cout <<"Merging process : "<<tag[i]<<" Complete !!!" <<"  "<<++count<<"/"<<NumberOfTag<<endl;
	}
}
