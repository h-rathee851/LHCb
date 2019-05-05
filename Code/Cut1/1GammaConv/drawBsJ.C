#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void drawBsJ(){


  TFile *file =  new TFile("output.root");
  TTree* tree = (TTree*) file->Get("DecayTree");

 
  
  
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
  

  TH1F* hist1 = new TH1F("hist1", "hist1", 500,5400,5400);
  TH1F* hist2 = new TH1F("hist2","hist2",1000,100,100);

  
  Int_t num_entries  = tree->GetEntries();
  Int_t ev_print = num_entries/100;

  Int_t k = 0;

  for (auto i =0 ; i < tree->GetEntries(); ++i){
       	   tree->GetEntry(i);

	   // pi0_Vetogg == 0  ;
	   // && g1_PT > 300 && g2_PT > 300
	    
	   
	   if( eminus1_ProbNNe > 0.2 && eplus1_ProbNNe > 0.2 && g2_IsNotH > 0.1 && pi0_PT > 300  && pi0_MM > 110  && Bs_LOKI_MASS_DsConstr > 5300 && Bs10_LOKI_DTF_CHI2NDOF_BsDsPi0Constr < 5 && pi0_MM < 180 && Bs_LOKI_MASS_DsConstr < 5400 && g1_MM < ((Bs10_OWNPV_Z*.04)+20) )
	     {


	       if(Bs10_LOKI_MASS_BsDsPi0Constr > 0 && Bs10_LOKI_MASS_BsDsPi0Constr < 8000){


		   hist1->Fill(Bs10_LOKI_MASS_BsDsPi0Constr);

	       }
	     
	       hist2->Fill(Bs10_M-Bs_M);
	     
	     
	    }


	    k++;
	    if(k==ev_print) {
	    Int_t percent = i*100/num_entries;
            cout<< percent << "\% done" << endl;
            k=0;
	    }

	   
 }
       
  TCanvas *c1 = new TCanvas("c1","Ds10_M");
  hist1->Draw();
  TCanvas *c2 = new TCanvas("c2","Ds10_M-Ds_M");
  hist2->SetLineColor(2);
  hist2->Draw();

  

}
