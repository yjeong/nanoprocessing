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

	TString inputdir = "/cms/scratch/yjeong/RPV_MC/2016/";

	TString sample_name_1 = "processed_v5/31CD3EC0-7352-1342-B38F-65BBF755DF0B_fatjetbaby_";//version5
	TString sample_name_2 = "processed_v6/1A542160-4CF8-384F-88A9-3EBCDA217FB1_fatjetbaby_";//version6

	tag_name = "TTJets_HT-2500toInf_TuneCUETP8M1";

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
	cout<< blist->GetEntries() <<endl;
	cout<< typeid(blist->GetEntries()).name() <<endl;
	cout<<"version5 entries: "<<mytree_1->GetEntries()<<endl;
	cout<<"version6 entries: "<<mytree_2->GetEntries()<<endl;
	const int nBranch = 72;

	TH1F *h1[nBranch];
	TH1F *h2[nBranch];
	TH1F *heff[nBranch];
	TCanvas *c_[nBranch];

	TPad *plotpad_[nBranch];
	TPad *ratiopad_[nBranch];
	TLegend *l_[nBranch];

	float xmin[nBranch] = {0,};
	float xmax[nBranch] = {0,};
	float ymax = 0;
	int bin = 100;
	TString var_name;

	double norm_1 = 1;
	double norm_2 = 1;
	float a=0,b=0;

	float x_min[nBranch] = 0;
	float x_max[nBranch] = 0;

	for(int j=0; j<nBranch; j++){
		l_[j] = new TLegend(0.65,0.54,0.75,0.80);

		var_name = blist->At(j)->GetName();
		cout<<"Name: "<<var_name<< endl;

		xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName());
		xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName());

		if(xmax[j]==0 && xmin[j]==0) {a=3; b=-3;}
		else if(xmax[j]-xmin[j]==0) {a=1; b=-1;}
		if(var_name.Contains("pt")) {a=700; b=-1;}
		if(var_name.Contains("pdgid")) {a=15; b=-15;}
		if(var_name.Contains("jets_m")) {a=50; b=-1;}
		if(var_name.Contains("jets_hflavor")) {a=7; b=-1;}
		if(var_name.Contains("els_miniso") || var_name.Contains("els_reliso") || var_name.Contains("mus_miniso")) {a=10; b=0;}

		x_max[j] = xmax[j]+a;
		x_min[j] = xmin[j]+b;

		//if(j==9) cout<<"bin_size: "<<(xmax[j]-xmin[j])/bin<<endl;
		cout<<"xmin :"<<x_min[j]<<", xmax :"<<x_max[j]<<endl;

		c_[j] = new TCanvas;
		plotpad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.3,0.98,0.98);
		ratiopad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.1,0.98,0.35);
		//plotpad_[j]->SetLogy();
		plotpad_[j]->Draw();
		ratiopad_[j]->Draw();

		h1[j] = new TH1F(Form("h1_%d",j),tag_name,bin,x_min[j],x_max[j]);
		mytree_1->Project(Form("h1_%d",j),blist->At(j)->GetName());
		h2[j] = new TH1F(Form("h2_%d",j),tag_name,bin,x_min[j],x_max[j]);
		mytree_2->Project(Form("h2_%d",j),blist->At(j)->GetName());
		plotpad_[j]->cd();

		norm_1 = h1[j]->Integral();
		h1[j]->Scale(1/norm_1);
		norm_2 = h2[j]->Integral();
		h2[j]->Scale(1/norm_2);

		ymax = h2[j]->GetMaximum();

		h1[j]->SetLineColor(kRed);
		h1[j]->SetLineStyle(7);
		h1[j]->SetLineWidth(3);
		h2[j]->SetLineColor(kBlue);

		l_[j]->AddEntry(h1[j],"NanoAODv5");
		l_[j]->AddEntry(h2[j],"NanoAODv6");

		set_legend_style(l_[j]);

		h1[j]->SetMaximum(ymax*2);
		h1[j]->Draw();
		h2[j]->Draw("same");

		l_[j]->Draw();
		ratiopad_[j]->cd();
		heff[j] = new TH1F(Form("heff_%d",j),Form(""),bin,x_min[j],x_max[j]);
		set_histo_ratio(heff[j]);
		heff[j]->GetXaxis()->SetTitle(blist->At(j)->GetName());
		heff[j]->Divide(h2[j],h1[j]);
		heff[j]->Draw("e");
		c_[j]->SaveAs(outputdir+tag_name+"_"+blist->At(j)->GetName()+".png");
	}
}
