{
	const int nBranch = 2;
	const int nSample = 2;
	TString inputdir_1 = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/";
	TString inputdir_2 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/";

	TString inputdir[] = {"/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/","/xrootd_user/yjeong/xrootd/nanoprocessing/2016/"};

	TString sample_name_1 = "F25F8B84-587A-B243-B7A6-34AD053DEDC5_fatjetbaby_TT_TuneCUETP8M2T4_rpvfitnbge0";
	TString sample_name_2 = "000F136A-D9F5-934E-8714-FB807DF9A0A6_fatjetbaby_TT_TuneCUETP8M2T4";

	TString outputdir = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/plots/";

	TString branch[nBranch] = {"mj12","jets_pt"};

	TH1F *h1[nBranch];
	TH1F *h2[nBranch];
	TTree *mytree_1;
	TTree *mytree_2;
	TFile *tfile_1;
	TFile *tfile_2;
	TCanvas *c_[nBranch];

	tfile_1 = new TFile(inputdir_1+sample_name_1+".root");
	mytree_1 = (TTree*)tfile_1->Get("tree");
	tfile_2 = new TFile(inputdir_2+sample_name_2+".root");
	mytree_2 = (TTree*)tfile_2->Get("tree");

	for(int j=0; j<nBranch; j++){
		c_[j] = new TCanvas;
		h1[j] = new TH1F(Form("h1_%d",j),branch[j],100,0,2000);
		mytree_1->Project(Form("h1_%d",j),branch[j]);
		h2[j] = new TH1F(Form("h2_%d",j),branch[j],100,0,2000);
		mytree_2->Project(Form("h2_%d",j),branch[j]);
		h1[j]->Draw();
		h2[j]->Draw("histsame");
		c_[j]->SaveAs(outputdir+branch[j]+".png");
	}
}
