#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


void redBsJ(){

  TFile* file  = new TFile("outMer.root");
  TTree* tree = (TTree*)file->Get("DecayTree");

   Double_t pi0_Vetogg; tree->SetBranchAddress("pi0_Vetogg", &pi0_Vetogg);
 
  // Double_t g2_MM; tree->SetBranchAddress("g2_M", &g2_MM);
 // Double_t g1_MM; tree->SetBranchAddress("g1_M", &g1_MM);
  
  Double_t Bs10_LOKI_DTF_CHI2NDOF_BsJpsiPi0Constr; tree->SetBranchAddress("Bs10_LOKI_DTF_CHI2NDOF_BsJpsiPi0Constr", &Bs10_LOKI_DTF_CHI2NDOF_BsJpsiPi0Constr);
  Double_t Bs10_OWNPV_Z; tree->SetBranchAddress("Bs10_OWNPV_Z", &Bs10_OWNPV_Z);

  Double_t Bs_LOKI_MASS_JpsiConstr; tree->SetBranchAddress("Bs_LOKI_MASS_JpsiConstr", &Bs_LOKI_MASS_JpsiConstr);
    
  Double_t Bs10_M; tree->SetBranchAddress("Bs10_M", &Bs10_M);
  Double_t Bs_M; tree->SetBranchAddress("Bs_M", &Bs_M);
  Double_t pi0_PT; tree->SetBranchAddress("pi0_PT", &pi0_PT);



  Double_t pi0_M; tree->SetBranchAddress("pi0_M", &pi0_M);

  Double_t Bs10_LOKI_MASS_BsJpsiPi0Constr; tree->SetBranchAddress("Bs10_LOKI_MASS_BsJpsiPi0Constr", &Bs10_LOKI_MASS_BsJpsiPi0Constr);  




  TFile *newfile = new TFile("finMer.root","recreate");
  TTree *newtree = tree->CloneTree(0);


  Int_t num_entries  = tree->GetEntries();
  Int_t ev_print = num_entries/100;

  Int_t k = 0;
  
  for (auto i =0 ; i < tree->GetEntries(); ++i){
       	   tree->GetEntry(i);


	   // cout<<Bs_LOKI_DTF_CHI2NDOF_DsConstr<<"\n";	  
	   
	   if (pi0_PT > 500  && pi0_M > 120 && Bs10_LOKI_DTF_CHI2NDOF_BsJpsiPi0Constr < 5 && pi0_M < 150 && Bs_LOKI_MASS_JpsiConstr > 5300 && Bs_LOKI_MASS_JpsiConstr < 5400){

	     newtree->Fill();
	     
	     }
	   
	    k++;
	    if(k==ev_print) {
	    Int_t percent = i*100/num_entries;
            cout<< percent << "\% done"<<'\n';
            k=0;
	    }
	   
  }


   newtree->AutoSave();
  
}
