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

void check_variable(){
	//TString inputdir_1 = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/processed/";
	//TString inputdir_2 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/processed/";

	TString inputdir = "/cms/scratch/yjeong/";

	//TString sample_name_1 = "4809C572-5167-514C-9186-FF01CBCA4C9C_fatjetbaby_";//version4
	TString sample_name_1 = "309FDC84-3CC9-B240-9A42-E30CC61AFACB_fatjetbaby_";//version4
	TString sample_name_2 = "C4B46A18-6E92-C946-8C93-E12F3161541A_fatjetbaby_";//version5

	tag_name = "TT_TuneCUETP8M2T4";

	TString outputdir = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/plots/";

	TTree *mytree_1;
	TTree *mytree_2;
	TFile *tfile_1;
	TFile *tfile_2;

	tfile_1 = new TFile(inputdir+sample_name_1+tag_name+".root");
	mytree_1 = (TTree*)tfile_1->Get("tree");
	tfile_2 = new TFile(inputdir+sample_name_2+tag_name+".root");
	mytree_2 = (TTree*)tfile_2->Get("tree");

	TObjArray *blist;
	blist = mytree_2->GetListOfBranches();
	//const int nBranch = blist->GetEntries();
	blist->Print();
	cout<< blist->GetEntries() <<endl;//56
	cout<< typeid(blist->GetEntries()).name() <<endl;
	cout<<"version4 entries: "<<mytree_1->GetEntries()<<endl;
	cout<<"version5 entries: "<<mytree_2->GetEntries()<<endl;
	const double nBranch = 56;
	//const int nBranch__ = blist->GetEntries();

	TH1F *h1[nBranch];
	TH1F *h2[nBranch];
	TH1F *heff[nBranch];
	TCanvas *c_[nBranch];

	TPad *plotpad_[nBranch];
	TPad *ratiopad_[nBranch];
	TLegend *l_[nBranch];

	float xmin[nBranch];
	float xmax[nBranch];
	float ymax = 0;
	int bin = 100;
	TString var_name;

	double norm_1 = 1;
	double norm_2 = 1;
	double a,b;
	const int x=1;
	//float w_lumi_ = 0.1;//seperated
	//float w_lumi_ = 0.05;//seperated 
	//float w_lumi_ = 0.02;//seperated // x_range: 0.04
	//float w_lumi_ = 0.01;//one line // x_range: 0.02 //float: seperated
	//float w_lumi_ = 0.009;//one line //float: seperated
	//float w_lumi_ = 0.008;//seperated
	//float w_lumi_ = 0.007;//seperated
	//float w_lumi_ = 0.006;//seperated
	float w_lumi_ = 0.005;//one line // x_range: 0.01
	//float w_lumi_ = 0.001;//seperated
	//float w_lumi_ = 0.0001;//seperated 
	//float w_lumi_ = 0.00003;//serperated
	//float w_lumi_ = 1.2;//serperated

	double x_range = 0;

	for(int j=0; j<nBranch; j++){
		l_[j] = new TLegend(0.65,0.54,0.75,0.80);

		var_name = blist->At(j)->GetName();
		cout<<"Name: "<<var_name<< endl;

		if(xmax[j]==0 && xmin[j]==0) {a=3; b=-3;}
		if(xmax[j]-xmin[j]==0) {a=3; b=-3;}
		if(j==15+x){a=15;b=-15;}//leps_pdgID
		if(j==33+x || j==47+x || j==44+x || j==18+x || j==12+x || j==24+x){a=1000;b=0;}//jets_pt, fjets_m, fjets_pt, mus_pt, leps_pt, els_pt
		if(j==29+x || j==30+x || j==22+x){a=20;b=0;}//els_miniso, els_reliso, mus_miniso
		if(j==36+x){a=250;b=0;}//jets_m
		if(j==7 || j==8 || j==38) b=0;//w_btag_csv, w_btag_dcsv, jets_csv
		if(j==9) {a=w_lumi_;b=-w_lumi_;}//w_lumi

		xmax[j] = mytree_2->GetMaximum(blist->At(j)->GetName())+a;
		xmin[j] = mytree_2->GetMinimum(blist->At(j)->GetName())+b;

		//if(j==9) cout<<"bin_size: "<<(xmax[j]-xmin[j])/bin<<endl;
		if(j==9) x_range = (xmax[j]-xmin[j]);
		cout<<"xmin :"<<xmin[j]<<", xmax :"<<xmax[j]<<endl;

		c_[j] = new TCanvas;
		plotpad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.3,0.98,0.98);
		ratiopad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.1,0.98,0.35);
		//plotpad_[j]->SetLogy();
		plotpad_[j]->Draw();
		ratiopad_[j]->Draw();

		h1[j] = new TH1F(Form("h1_%d",j),tag_name,bin,xmin[j],xmax[j]);
		mytree_1->Project(Form("h1_%d",j),blist->At(j)->GetName());
		h2[j] = new TH1F(Form("h2_%d",j),tag_name,bin,xmin[j],xmax[j]);
		mytree_2->Project(Form("h2_%d",j),blist->At(j)->GetName());
		plotpad_[j]->cd();

		if(j!=15){
			norm_1 = h1[j]->Integral();
			h1[j]->Scale(1/norm_1);
			norm_2 = h2[j]->Integral();
			h2[j]->Scale(1/norm_2);
		}

		ymax = h2[j]->GetMaximum();

		h1[j]->SetLineColor(kRed);
		h1[j]->SetLineStyle(7);
		h1[j]->SetLineWidth(3);
		h2[j]->SetLineColor(kBlue);

		l_[j]->AddEntry(h2[j],"NanoAODv4");
		l_[j]->AddEntry(h1[j],"NanoAODv5");

		set_legend_style(l_[j]);

		h1[j]->SetMaximum(ymax*2);
		h1[j]->Draw();
		h2[j]->Draw("histsame");

		l_[j]->Draw();
		ratiopad_[j]->cd();
		heff[j] = new TH1F(Form("heff_%d",j),Form(""),bin,xmin[j],xmax[j]);
		set_histo_ratio(heff[j]);
		heff[j]->GetXaxis()->SetTitle(blist->At(j)->GetName());
		heff[j]->Divide(h2[j],h1[j]);
		heff[j]->Draw("e");
		c_[j]->SaveAs(outputdir+tag_name+"_"+blist->At(j)->GetName()+".png");
	}
	cout<<"x_range: "<<x_range<<endl;
}
