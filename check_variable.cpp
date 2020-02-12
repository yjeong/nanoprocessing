void set_histo_ratio(TH1F *histo_Ratio){
	histo_Ratio->SetMarkerStyle(20);
	histo_Ratio->SetMarkerSize(1.2);
	histo_Ratio->GetYaxis()->SetTitle("Ratio");
	histo_Ratio->GetYaxis()->SetTitleSize(0.17);
	histo_Ratio->GetYaxis()->SetTitleOffset(0.2);
	histo_Ratio->GetYaxis()->SetLabelSize(0.13);
	histo_Ratio->GetYaxis()->CenterTitle();
	histo_Ratio->GetYaxis()->SetNdivisions(6);
	histo_Ratio->GetXaxis()->SetLabelSize(0.13);
	histo_Ratio->GetXaxis()->SetTitleSize(0.2);
	histo_Ratio->SetAxisRange(0.5,1.5,"y");
}

void check_variable(){
	const int nBranch = 2;
	TString inputdir_1 = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/";
	TString inputdir_2 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/";

	TString sample_name_1 = "F25F8B84-587A-B243-B7A6-34AD053DEDC5_fatjetbaby_TT_TuneCUETP8M2T4_rpvfitnbge0";
	TString sample_name_2 = "000F136A-D9F5-934E-8714-FB807DF9A0A6_fatjetbaby_TT_TuneCUETP8M2T4";

	TString outputdir = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/plots/";

	TString branch[nBranch] = {"mj12","jets_pt"};

	TH1F *h1[nBranch];
	TH1F *h2[nBranch];
	TH1F *heff[nBranch];
	TTree *mytree_1;
	TTree *mytree_2;
	TFile *tfile_1;
	TFile *tfile_2;
	TCanvas *c_[nBranch];

	TPad *plotpad_[nBranch];
	TPad *ratiopad_[nBranch];

	tfile_1 = new TFile(inputdir_1+sample_name_1+".root");
	mytree_1 = (TTree*)tfile_1->Get("tree");
	tfile_2 = new TFile(inputdir_2+sample_name_2+".root");
	mytree_2 = (TTree*)tfile_2->Get("tree");

	for(int j=0; j<nBranch; j++){
		c_[j] = new TCanvas;
		plotpad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.3,0.98,0.98);
		ratiopad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.1,0.98,0.35);
		plotpad_[j]->Draw();
		ratiopad_[j]->Draw();
		h1[j] = new TH1F(Form("h1_%d",j),branch[j],100,0,2000);
		mytree_1->Project(Form("h1_%d",j),branch[j]);
		h2[j] = new TH1F(Form("h2_%d",j),branch[j],100,0,2000);
		mytree_2->Project(Form("h2_%d",j),branch[j]);
		plotpad_[j]->cd();
		h1[j]->SetLineColor(kRed);
		h2[j]->SetLineColor(kBlue);
		h1[j]->Draw();
		h2[j]->Draw("histsame");

		ratiopad_[j]->cd();
		heff[j] = new TH1F(Form("heff_%d",j),Form(""),100,0,2000);
		set_histo_ratio(heff[j]);
		heff[j]->GetXaxis()->SetTitle(branch[j]);
		heff[j]->Divide(h1[j],h2[j]);
		heff[j]->Draw();
		c_[j]->SaveAs(outputdir+branch[j]+".png");
	}
}
