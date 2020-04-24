#include <typeinfo>

void set_histo_ratio(TH1F *histo_Ratio){
	histo_Ratio->SetMarkerStyle(20);
	histo_Ratio->SetMarkerSize(0.6);
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

void set_legend_style(TLegend *l1){
	l1->SetFillColor(0);
	l1->SetLineColor(0);
	l1->SetLineStyle(kSolid);
	l1->SetLineWidth(1);
	l1->SetFillStyle(1001);
	l1->SetTextFont(42);
	l1->SetTextSize(0.045);
}

void comparison_variable(){

	const int Sample_Num = 2;
	TFile *tfile[Sample_Num];
	TH1F *h[Sample_Num];
	TTree *tree_[Sample_Num];
	TCanvas *c;
	c = new TCanvas;

	float ht, mj12, w_lumi;
	int njets, nbm;
	double ymax = 0;
	double norm_1 = 1, norm_2 = 1;

	TString variable = "NJets";

	TString inputdir, outputdir;
	inputdir = "/cms/scratch/yjeong/";
	outputdir = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/plots/";

	TString sample_name[Sample_Num] = {
		"mergedbaby__TTJets_Tune_skim_rpvfit_rpvmc_nfiles_60_ntruleps0",
		"TTJets_Tune"
	};

	for (int i=0; i < Sample_Num; i++){
		tfile[i] = new TFile(inputdir+sample_name[i]+".root");
	}

	for(int i=0; i<Sample_Num; i++){
		h[i] = new TH1F(Form("h_%d",i),Form("var_%d",i),10,0,18);
		tree_[i] = (TTree*)tfile[i]->Get("tree");
		tree_[i]->SetBranchAddress("ht",&ht);
		tree_[i]->SetBranchAddress("mj12",&mj12);
		tree_[i]->SetBranchAddress("w_lumi",&w_lumi);
		tree_[i]->SetBranchAddress("njets",&njets);
		tree_[i]->SetBranchAddress("nbm",&nbm);

		//for(int j=0; j<tree[i]->GetEntries(); j++){
		for(int j=0; j<10000; j++){
			tree_[i]->GetEntry(j);
			h[i]->Fill(njets,w_lumi);
		}

		if(i==0){
			norm_1 = h[i]->Integral();
			h[i]->Scale(1/norm_1);
		}
		if(i==1){
			norm_2 = h[i]->Integral();
			h[i]->Scale(1/norm_2);
		}

		if(i==0){
			ymax = h[i]->GetMaximum();
			h[i]->SetMaximum(ymax*2);
		}
		c->cd();
		if(i==0)h[i]->Draw();
		else if(i>0)h[i]->Draw("same");
	}
	c->SaveAs(outputdir+variable+".png");
}
