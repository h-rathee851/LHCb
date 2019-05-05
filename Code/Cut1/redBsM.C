#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


void redBsM(){

  TFile* file  = new TFile("small.root");
  TTree* tree = (TTree*)file->Get("DecayTree");

  Double_t Ds_M; tree->SetBranchAddress("Ds_M", &Ds_M);
  Double_t Ds_DIRA_ORIVX; tree->SetBranchAddress("Ds_DIRA_ORIVX", &Ds_DIRA_ORIVX);
  Double_t Bs_IPCHI2_OWNPV; tree->SetBranchAddress("Bs_IPCHI2_OWNPV", &Bs_IPCHI2_OWNPV);


  Double_t Bs_LOKI_DTF_CHI2NDOF_DsConstr; tree->SetBranchAddress("Bs_LOKI_DTF_CHI2NDOF_DsConstr", &Bs_LOKI_DTF_CHI2NDOF_DsConstr);

  




  TFile *newfile = new TFile("smallBsM.root","recreate");
  TTree *newtree = tree->CloneTree(0);


  Int_t num_entries  = tree->GetEntries();
  Int_t ev_print = num_entries/100;

  Int_t k = 0;
  
  for (auto i =0 ; i < tree->GetEntries(); ++i){
       	   tree->GetEntry(i);


	   // cout<<Bs_LOKI_DTF_CHI2NDOF_DsConstr<<"\n";	  
	   
	   if(Ds_M > 1955 && Ds_M < 1980 && Ds_DIRA_ORIVX > 0 && Bs_IPCHI2_OWNPV < 10 && Bs_LOKI_DTF_CHI2NDOF_DsConstr > 0 && Bs_LOKI_DTF_CHI2NDOF_DsConstr < 3.5){

	     newtree->Fill();
	     
	     }
	   
	    k++;
	    if(k==ev_print) {
	    Int_t percent = i*100/num_entries;
            cout<< percent << "\% done" << endl;
            k=0;
	    }
	   
  }


   newtree->AutoSave();
  
}
