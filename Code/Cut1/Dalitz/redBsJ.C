#include <TFile.h>
#include <TTree.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


void redBsJ(){

  TFile* file  = new TFile("output.root");
  TTree* tree = (TTree*)file->Get("DecayTree");

   Double_t Bs10_LOKI_DTF_CHI2NDOF_BsDsPi0Constr; tree->SetBranchAddress("Bs10_LOKI_DTF_CHI2NDOF_BsDsPi0Constr", &Bs10_LOKI_DTF_CHI2NDOF_BsDsPi0Constr);
  Double_t Bs10_M; tree->SetBranchAddress("Bs10_M", &Bs10_M);
  Double_t Bs10_LOKI_MASS_BsDsPi0Constr; tree->SetBranchAddress("Bs10_LOKI_MASS_BsDsPi0Constr", &Bs10_LOKI_MASS_BsDsPi0Constr);
  Double_t Bs10_OWNPV_Z; tree->SetBranchAddress("Bs10_OWNPV_Z", &Bs10_OWNPV_Z);

  Double_t Bs_LOKI_MASS_DsConstr; tree->SetBranchAddress("Bs_LOKI_MASS_DsConstr", &Bs_LOKI_MASS_DsConstr);
  Double_t Bs_M; tree->SetBranchAddress("Bs_M", &Bs_M);
 
  Double_t g1_PT; tree->SetBranchAddress("g1_PT", &g1_PT);
  Double_t g2_PT; tree->SetBranchAddress("g2_PT", &g2_PT);
  Double_t g2_IsNotH; tree->SetBranchAddress("g2_IsNotH", &g2_IsNotH);
  Double_t g1_MM; tree->SetBranchAddress("g1_MM", &g1_MM);


  Double_t pi0_MM; tree->SetBranchAddress("pi0_MM", &pi0_MM);
  Double_t pi0_PT; tree->SetBranchAddress("pi0_PT", &pi0_PT);
  Double_t pi0_Vetogg; tree->SetBranchAddress("pi0_Vetogg", &pi0_Vetogg);

  Double_t eminus1_ProbNNe; tree->SetBranchAddress("eminus1_ProbNNe", &eminus1_ProbNNe);
  Double_t eplus1_ProbNNe; tree->SetBranchAddress("eplus1_ProbNNe", &eplus1_ProbNNe);
  


  TFile *newfile = new TFile("smallBsJ.root","recreate");
  TTree *newtree = tree->CloneTree(0);


  Int_t num_entries  = tree->GetEntries();
  Int_t ev_print = num_entries/100;

  Int_t k = 0;
  
  for (auto i =0 ; i < tree->GetEntries(); ++i){
       	   tree->GetEntry(i);


	   // cout<<Bs_LOKI_DTF_CHI2NDOF_DsConstr<<"\n";	  


	    // pi0_Vetogg == 0  ;
	   // && g1_PT > 300 && g2_PT > 300
	   
	   if (eminus1_ProbNNe > 0.2 && eplus1_ProbNNe > 0.2 && g2_IsNotH > 0.1 && pi0_PT > 500  && pi0_MM > 120  && Bs_LOKI_MASS_DsConstr > 5300 && Bs10_LOKI_DTF_CHI2NDOF_BsDsPi0Constr < 5 && pi0_MM < 150 && Bs_LOKI_MASS_DsConstr < 5400){

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
