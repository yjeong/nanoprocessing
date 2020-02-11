{
	const int sample_num = 2;
	//const int nBranch = 54;
	TString inputdir[sample_num] = {"/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/",
		"/xrootd_user/yjeong/xrootd/nanoprocessing/2016/"
	};
	TString outputdir = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/plots/";

	TString sample_name[sample_num] = {
		"F25F8B84-587A-B243-B7A6-34AD053DEDC5_fatjetbaby_TT_TuneCUETP8M2T4_rpvfitnbge0",
		"000F136A-D9F5-934E-8714-FB807DF9A0A6_fatjetbaby_TT_TuneCUETP8M2T4"
	};
	float mj12;

	TH1F *h1[sample_num];
	TTree *mytree[sample_num];
	TFile *tfile[sample_num];
	TCanvas *c_[sample_num];

	for(int i = 0; i < sample_num; i++){
		c_[i] = new TCanvas(Form("c_%d",i),Form(""),800,800);
		tfile[i] = new TFile(inputdir[i]+sample_name[i]+".root");
		h1[i] = new TH1F(Form("h1_%d",i),Form("title_%d",i),30,0,600);
		mytree[i] = (TTree*)tfile[i]->Get("tree");
		tfile[i]->GetObject("tree_",tree);
		mytree[i]->SetBranchAddress("mj12",&mj12);
		//tfile[i]->Print();
		h1[i]->Fill(mj12);
		c_[i]->Draw();
		c_[i]->SaveAs(outputdir+"mj12.png");
		/*for(int j=0; j<nBranch; j++){
			//h1[i][j]->Fill(tree);
		}*/
	}
}
