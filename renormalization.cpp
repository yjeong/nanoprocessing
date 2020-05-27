// ------------------------------------
// Author : Jae Hyeok Yoo
//          jaehyeok@hep.ucsb.edu
// ------------------------------------
//
// * This code is composed of 3 blocks
//  
// Block 1 : Read information about PF candidates from a cfA ntuple   
//           and write that information on a text file  
// Block 2 : Read the text file from (1) and run Fastjet package. 
//           The information of the recontructed jets will be 
//           written on a text file 
// Block 3 : Read the text file from (2) and make new branches in 
//           the input cfA in (1) to store the information 
// 
// * Pre-requisites
//
// (1) Download(http://fastjet.fr) and set up Fastjet package
//    * version 3.0.6(http://fastjet.fr/repo/fastjet-3.0.6.tar.gz) 
//    * manual : http://fastjet.fr/repo/fastjet-doc-3.0.6.pdf
//      --> Chapter 2 has an instruction to set up the code
// (2) Turn off some of the printouts so that fastjet_example 
//     prints out only information of PF candidates, i.e., 
//     no table header, ... 
// 
// * To run this code, do
//   
//      $root -b -q makeJetP4_notext.C++\(\"cfA_QCD_HT-250To500_TuneZ2star_8TeV-madgraph-pythia6_Summer12_DR53X-PU_S10_START53_V7A-v1_AODSIM_UCSB2047_v71_f6_1_OWX_Test.root\",1.2,10\)
// 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream> // for stringstream

#include "TROOT.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TSystem.h"
#include "TH2F.h"
#include "TEllipse.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TBranch.h"
#include "TString.h"
#include "TLorentzVector.h"
#include "TChain.h"


#include "utilities.h"  

// compile
//  $ g++ normalization.cpp  `root-config --cflags --glibs` -o normalization.exe

using namespace std;

const bool DEBUG = false; 

void normalizationonefile(TString inputfile, TString outputdir, TString normalization, int year) 
{
	TH1D *h_btag;
	TH1D *h_pu;
	TH1D *h_isr;
	bool donormalization = true; 
	double btag_mean = 1;
	double pu_mean = 1;
	double isr_mean = 1;

	TChain ch("tree");
        ch.Add(inputfile);
        h_btag = new TH1D("h_btag","",1,0,100);
        h_pu = new TH1D("h_pu","",1,0,100);
        h_isr = new TH1D("h_isr","",1,0,100);
        ch.Draw("w_btag_dcsv>>h_btag","","goff");
        ch.Draw("w_pu>>h_pu","","goff");
        ch.Draw("w_isr>>h_isr","","goff");
        btag_mean = h_btag->GetMean();
        pu_mean = h_pu->GetMean();
        isr_mean = h_isr->GetMean();

	// normalization
	TString normalizationcut;
	//float normalizationcut=1;
	if(normalization=="btagNorm") {
		//if(year==2016 && inputfile.Contains("SMS") || inputfile.Contains("TTJets")){//16
		if(0){//16
		  normalizationcut="w_isr";
		} 
		//if((year>=2017) && inputfile.Contains("SMS") || inputfile.Contains("TTJets")){//17, 18
		if(1){//17, 18
		  normalizationcut="w_btag_dcsv";
		}
		cout<<"w_btag: "<<btag_mean<<endl;
		cout<<"w_pu: "<<pu_mean<<endl;
		cout<<"w_isr: "<<isr_mean<<endl;
	}

	else {
		cout << "enter a correct normalization!" << endl;
		donormalization = false; 
	}

	TObjArray *tokens = inputfile.Tokenize("/"); 
	TString outputfile = (dynamic_cast<TObjString*>(tokens->At(tokens->GetEntries()-1)))->GetString();
	outputfile.ReplaceAll(".root", Form("_%s.root", normalization.Data()));

	TFile *newfile= new TFile(outputfile,"recreate");
	TTree *ctree = ch.CopyTree(normalizationcut);
	//cout<< normalizationcut <<endl;
	newfile->cd();
	if(ctree) ctree->Write();
	newfile->Close();

	cout << "copying " << outputfile << " to " << outputdir << endl; 
	gSystem->Exec(Form("mv %s %s", outputfile.Data(), outputdir.Data()));  
}


# ifndef __CINT__  // the following code will be invisible for the interpreter
int main(int argc, char **argv)
//int main()
{
	int year=0;
	TString inputdir, outputdir, normalization; 

	if(argc<3)
	{
		cout << " Please provide proper arguments" << endl;
		cout << "" << endl;
		cout << "   ./process.exe [input dir] [normalization] " << endl; 
		cout << "" << endl;
		cout << " where normalization = rpvfit, trig, rpvfitnbge0, ht1000" << endl;
		return 0;
	}
	else 
	{
		inputdir     = argv[1];
		normalization         = argv[2];

		outputdir = inputdir;
		outputdir.ReplaceAll("processed", Form("normalization_%s", normalization.Data()));
		cout << " input   dir  : " << inputdir << endl;
		cout << " output  dir  : " << outputdir << endl;
		cout << " normalization         : " << normalization << endl;
	}

	if(inputdir.Contains("2016")) year = 2016;
	if(inputdir.Contains("2017")) year = 2017;
	if(inputdir.Contains("2018")) year = 2018;

	// make normalization directory
	gSystem->mkdir(outputdir.Data());

	// get list of files in a directory
	//vector<TString> files = globVector(Form("%s/*_TT*.root", inputdir.Data())); 
	vector<TString> files = globVector(Form("%s/*_SMS*.root", inputdir.Data())); 

	cout << "normalizing " << files.size() << " files" << endl;

	for(int i=0; i<files.size(); i++)
	{
		//if(normalization!="rpvfit" && normalization!="trig") continue; 

		cout << "normalizing: " << files.at(i) << endl; 
		normalizationonefile(files.at(i), outputdir, normalization, year); 
	}

	return 0;
}
# endif
