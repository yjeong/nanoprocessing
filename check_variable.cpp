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
	TString inputdir_1 = "/xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/skim_rpvfitnbge0/";
	TString inputdir_2 = "/xrootd_user/yjeong/xrootd/nanoprocessing/2016/skim_rpvfitnbge0/";

	TString sample_name_1 = "F25F8B84-587A-B243-B7A6-34AD053DEDC5_fatjetbaby_TT_TuneCUETP8M2T4_rpvfitnbge0";
	TString sample_name_2 = "000F136A-D9F5-934E-8714-FB807DF9A0A6_fatjetbaby_TT_TuneCUETP8M2T4_rpvfitnbge0";

	TString outputdir = "/cms/scratch/yjeong/CMSSW_7_1_0/src/nanoprocessing/plots/";

	TTree *mytree_1;
	TTree *mytree_2;
	TFile *tfile_1;
	TFile *tfile_2;

	tfile_1 = new TFile(inputdir_1+sample_name_1+".root");
	mytree_1 = (TTree*)tfile_1->Get("tree");
	tfile_2 = new TFile(inputdir_2+sample_name_2+".root");
	mytree_2 = (TTree*)tfile_2->Get("tree");

	TObjArray *blist;
	blist = mytree_1->GetListOfBranches();
	//const int nBranch = blist->GetEntries();
	blist->Print();
	//cout<< blist->GetEntries()+3 <<endl;//55
	const int nBranch = 55;
	const int nBranch__ = blist->GetEntries();
	cout<< typeid(blist->GetEntries()).name() <<endl;

	TH1F *h1[nBranch];
	TH1F *h2[nBranch];
	TH1F *heff[nBranch];
	TCanvas *c_[nBranch];

	TPad *plotpad_[nBranch];
	TPad *ratiopad_[nBranch];
	TLegend *l_[nBranch];

	double xmin[nBranch];
	double xmax[nBranch];
	double ymax = 0;
	int bin = 50;
	TString var_name;

	double norm_1 = 1;
	double norm_2 = 1;
	double a,b;

	for(int j=0; j<nBranch; j++){
		l_[j] = new TLegend(0.65,0.54,0.75,0.80);

		var_name = blist->At(j)->GetName();
		cout<<"Name: "<<var_name<< endl;

		if(xmax[j]==0 || xmin[j]==0) {a=6; b=-6;}
		if(j==15){a=15;b=-15;}
		if(j==33 || j==47 || j==44 || j==18 || j==12 || j==24){a=1000;b=0;}
		if(j==29||j==30||j==22){a=20;b=0;}
		if(j==36){a=250;b=0;}

		xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName())+a;
		xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName())+b;

		/*if(xmax[j]==0 || xmin[j]==0){
			xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName())+6;
			xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName())-6;
		}
		if(j==15){
			xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName())+15;
			xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName())-15;
		}
		if(j==33 || j==47 || j==44 || j==18 || j==12 || j==24){//pt or mass
			xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName())+1000;
			xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName());
		}
		if(j==29||j==30||j==22){//isolation
			xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName())+20;
			xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName());
		}
		if(j==36){
			xmax[j] = mytree_1->GetMaximum(blist->At(j)->GetName())+250;
			xmin[j] = mytree_1->GetMinimum(blist->At(j)->GetName());
		}*/

		c_[j] = new TCanvas;
		plotpad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.3,0.98,0.98);
		ratiopad_[j] = new TPad(Form("title_%d",j),Form(""),0.02,0.1,0.98,0.35);
		plotpad_[j]->Draw();
		ratiopad_[j]->Draw();

		h1[j] = new TH1F(Form("h1_%d",j),blist->At(j)->GetName(),bin,xmin[j],xmax[j]);
		mytree_1->Project(Form("h1_%d",j),blist->At(j)->GetName());
		h2[j] = new TH1F(Form("h2_%d",j),blist->At(j)->GetName(),bin,xmin[j],xmax[j]);
		mytree_2->Project(Form("h2_%d",j),blist->At(j)->GetName());
		plotpad_[j]->cd();

		if(j!=15){
			norm_1 = h1[j]->Integral();
			h1[j]->Scale(1/norm_1);
			norm_2 = h2[j]->Integral();
			h2[j]->Scale(1/norm_2);
		}

		ymax = h2[j]->GetMaximum();

		cout<<"xmin :"<<xmin[j]<<", xmax :"<<xmax[j]<<endl;

		h1[j]->SetLineColor(kRed);
		h2[j]->SetLineColor(kBlue);

		l_[j]->AddEntry(h1[j],"NanoAODv4");
		l_[j]->AddEntry(h2[j],"NanoAODv5");

		set_legend_style(l_[j]);

		h1[j]->SetMaximum(ymax*1.2);
		h1[j]->Draw();
		h2[j]->Draw("histsame");
		l_[j]->Draw();

		ratiopad_[j]->cd();
		heff[j] = new TH1F(Form("heff_%d",j),Form(""),bin,xmin[j],xmax[j]);
		set_histo_ratio(heff[j]);
		heff[j]->GetXaxis()->SetTitle(blist->At(j)->GetName());
		heff[j]->Divide(h1[j],h2[j]);
		heff[j]->Draw("e");
		c_[j]->SaveAs(outputdir+blist->At(j)->GetName()+".png");
	}
}
