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
// ./skim.exe /xrootd_user/jaehyeok/xrootd/2016v4/2019_12_10/processed/ rpvfitnbge0
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
//  $ g++ skim.cpp  `root-config --cflags --glibs` -o skim.exe

using namespace std;

const bool DEBUG = false; 

void skimonefile(TString inputfile, TString outputdir, TString skim) 
{
	bool doskim = true; 

  // skim cut
  TString skimcut="0";
  if(skim=="rpvfit") {
		skimcut="ht>1200&&nbm>0&&mj12>500&&njets>=4";
	}
	else if(skim=="trig") {
		skimcut="nbm>0&&mj12>500&&njets>=4";
	}
	else if(skim=="rpvfitnbge0") {
		if(inputfile.Contains("TTJets_Tune")) skimcut="ht>1200&&mj12>500&&njets>=4&&stitch_ht==1";
		else skimcut="ht>1200&&mj12>500&&njets>=4";
	}
	else if(skim=="ht1000") {
		skimcut="ht>1000";
	}
	else {
		cout << "enter a correct skim!" << endl;
	  doskim = false; 
	}

	if(doskim) {
		TChain ch("tree");
		ch.Add(inputfile);

		TObjArray *tokens = inputfile.Tokenize("/"); 
		TString outputfile = (dynamic_cast<TObjString*>(tokens->At(tokens->GetEntries()-1)))->GetString();
		outputfile.ReplaceAll(".root", Form("_%s.root", skim.Data()));

		TFile *newfile= new TFile(outputfile,"recreate");
		TTree *ctree = ch.CopyTree(skimcut);
		newfile->cd();
		if(ctree) ctree->Write();
		newfile->Close();

		cout << "copying " << outputfile << " to " << outputdir << endl; 
		gSystem->Exec(Form("mv %s %s", outputfile.Data(), outputdir.Data()));  
	} 
}


# ifndef __CINT__  // the following code will be invisible for the interpreter
int main(int argc, char **argv)
//int main()
{
  TString inputdir, outputdir, skim; 
  
  if(argc<3)
  {
    cout << " Please provide proper arguments" << endl;
    cout << "" << endl;
    cout << "   ./process.exe [input dir] [skim] " << endl; 
    cout << "" << endl;
    cout << " where skim = rpvfit, trig, rpvfitnbge0, ht1000" << endl;
    return 0;
  }
  else 
  {
    inputdir     = argv[1];
    skim         = argv[2];
   
    outputdir = inputdir;
    outputdir.ReplaceAll("processed", Form("skim_%s", skim.Data()));
    cout << " input   dir  : " << inputdir << endl;
    cout << " output  dir  : " << outputdir << endl;
    cout << " skim         : " << skim << endl;
  }

  // make skim directory
  gSystem->mkdir(outputdir.Data());

  // get list of files in a directory
  //vector<TString> files = globVector(Form("%s/*.root", inputdir.Data())); 
  //vector<TString> files = globVector(Form("%s/*_DYJets*.root", inputdir.Data())); 
  //vector<TString> files = globVector(Form("%s/*_TT*.root", inputdir.Data())); 
  //vector<TString> files = globVector(Form("%s/*_W*.root", inputdir.Data())); 
  //vector<TString> files = globVector(Form("%s/*_ST*.root", inputdir.Data())); 
  vector<TString> files = globVector(Form("%s/*TTJets_*.root", inputdir.Data())); 

	cout << "skimming " << files.size() << " files" << endl;
	
  for(int i=0; i<files.size(); i++)
  {
    //if(skim!="rpvfit" && skim!="trig") continue; 

    cout << "skimming: " << files.at(i) << endl; 
    skimonefile(files.at(i), outputdir, skim); 
  }

  return 0;
}
# endif
