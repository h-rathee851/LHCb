#include <string>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TCut.h"
#include "TChain.h"
#include "TMath.h"
/* 
*  Example of how to write a reduced ntuple
*  Two selections, Matts (add on to roadmap):
*  Use: .L ApplySelection.C+
*        ApplySelection("theFile.root")
* Giving extra arguments allows to change ntuple and output name
*        ApplySelection("EtaDown.root", "rhoGammaDown/rhoGammaDown", "_Selected.root");
*/ 


/** First some helpers to avoid duplicating code */


TFile* openOutput(std::string& tree, std::string& input, std::string& output) {
  // helper for opening the file
  TFile* outFile  =new TFile(output.c_str(),"RECREATE", "", 6);
  std::cout << "Reading: " << tree << " from " << input  << " to " << output << std::endl;
  return outFile;
}

void finalize(TTree* cutTree, TFile* output){
  // helper for finalizing
  TTree*  newtree = cutTree->CloneTree(-1);
  newtree->Write();
  output->Close();
}

/* Now the main business */

std::string Cutter(std::string fileName = "mcall.root", std::string treeName = "Bs1_Bspi0_pi0ResolvedTree", std::string outputName = "_cut.root", std::string cutString  = "Bs_LOKI_DTF_VCHI2NDOF<5 & phi_PT>1000 & Bs_LOKI_DTF_CTAU >0.2"){

  // Matts selection, generally applied on top of the road map

  // get the input

  if(treeName != "DecayTree"){
  treeName += "/DecayTree";
  }
  TChain* decaytree = new TChain(treeName.c_str());
  decaytree->Add(fileName.c_str());
	
 
  // make the output file
  TFile* outFile = openOutput(treeName,fileName,outputName); 
  TCut cut = cutString.c_str();

  TTree* smalltree = decaytree->CopyTree(cut);
  finalize(smalltree,outFile);  

  return outputName;
}

