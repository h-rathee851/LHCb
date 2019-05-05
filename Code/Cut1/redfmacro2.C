#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void redfmacro2(){

  
       TFile* file  = new TFile("temp.root");
       TTree* tree = (TTree*)file->Get("Bs1_Bspi0_2GammaConvTree/DecayTree");

       Double_t Ds_M; tree->SetBranchAddress("Ds_M", &Ds_M);
       
       Double_t Kplus_PE; tree->SetBranchAddress("Kplus_PE", &Kplus_PE);
       Double_t Kplus_PX; tree->SetBranchAddress("Kplus_PX", &Kplus_PX);
       Double_t Kplus_PY; tree->SetBranchAddress("Kplus_PY", &Kplus_PY);
       Double_t Kplus_PZ; tree->SetBranchAddress("Kplus_PZ", &Kplus_PZ);

       Double_t Kminus_PE; tree->SetBranchAddress("Kminus_PE", &Kminus_PE);
       Double_t Kminus_PX; tree->SetBranchAddress("Kminus_PX", &Kminus_PX);
       Double_t Kminus_PY; tree->SetBranchAddress("Kminus_PY", &Kminus_PY);
       Double_t Kminus_PZ; tree->SetBranchAddress("Kminus_PZ", &Kminus_PZ);

       Double_t piminus_PE; tree->SetBranchAddress("piminus_PE", &piminus_PE);
       Double_t piminus_PX; tree->SetBranchAddress("piminus_PX", &piminus_PX);
       Double_t piminus_PY; tree->SetBranchAddress("piminus_PY", &piminus_PY);
       Double_t piminus_PZ; tree->SetBranchAddress("piminus_PZ", &piminus_PZ);

       TFile *newfile = new TFile("small.root","recreate");
       TTree *newtree = tree->CloneTree(0);

       Int_t num_entries  = tree->GetEntries();
       Int_t ev_print = num_entries/100;

       Int_t k = 0;
       
       for (auto i =0 ; i < tree->GetEntries(); ++i){
       	   tree->GetEntry(i);

	   TLorentzVector Kplus(Kplus_PX, Kplus_PY, Kplus_PZ, Kplus_PE);
	   TLorentzVector Kminus(Kminus_PX, Kminus_PY, Kminus_PZ, Kminus_PE);
	   TLorentzVector piminus(piminus_PX, piminus_PY, piminus_PZ, piminus_PE);

	   TLorentzVector phi = Kplus + Kminus;
	   TLorentzVector kstar = Kplus + piminus;
	   // cout << phi.M() << "\n";

	   // scatter1->Fill(phi.M2(), kstar.M2());

	   
	   if((abs( phi.M() - 1019) < 10)  || (abs(kstar.M() - 892) < 100 ))
	   {
	     /*histo1->Fill(Ds_M);
	      histo2->Fill(phi.M());
	      histo3->Fill(kstar.M());
	      scatter2->Fill(phi.M2(), kstar.M2());
	     */

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
