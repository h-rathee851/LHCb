

void redfmacro()
{

	TFile* file  = new TFile("Bs1_Bspi0_Dspi_2017_MU.root");
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

       //TH1F* histo1 = new TH1F("histo1", "histo1", 100, 1930,2010);
       //TH1F* histo2 = new TH1F("histo2", "histo2", 100, 1000,2000);
       //TH1F* histo3 = new TH1F("histo3", "histo3", 100, 600,1500);
       //TH2F* scatter1 = new TH2F("scatter1","scatter1", 1000,100.,100.,1000,100.,100.);
       // TH2F* scatter2 = new TH2F("scatter2","scatter2", 1000,100.,100.,1000,100.,100.);


       // Event *event = 0;
       TFile *newfile = new TFile("small.root","recreate");
       TTree *t = new TTree("t","tree1");
      
       t->Branch("Ds_M",&Ds_M,"Ds_M/D");
       
       t->Branch("Kplus_PE",&Kplus_PE,"Kplus_PE/D");
       t->Branch("Kplus_PX",&Kplus_PX,"Kplus_PX/D");
       t->Branch("Kplus_PY",&Kplus_PY,"Kplus_PY/D");
       t->Branch("Kplus_PZ",&Kplus_PZ,"Kplus_PZ/D");

       t->Branch("Kminus_PE",&Kminus_PE,"Kminus_PE/D");
       t->Branch("Kminus_PX",&Kminus_PX,"Kminus_PX/D");
       t->Branch("Kminus_PY",&Kminus_PY,"Kminus_PY/D");
       t->Branch("Kminus_PZ",&Kminus_PZ,"Kminus_PZ/D");

       t->Branch("piminus_PE",&piminus_PE,"piminus_PE/D");
       t->Branch("piminus_PX",&piminus_PX,"piminus_PX/D");
       t->Branch("piminus_PY",&piminus_PY,"piminus_PY/D");
       //  t->Branch("piminus_PZ",&piminus_PZ,"piminus_PZ/D");
	 
       
      

  
       for (auto i =0 ; i < tree->GetEntries(); ++i){
       	   tree->GetEntry(i);

	   TLorentzVector Kplus(Kplus_PX, Kplus_PY, Kplus_PZ, Kplus_PE);
	   TLorentzVector Kminus(Kminus_PX, Kminus_PY, Kminus_PZ, Kminus_PE);
	   TLorentzVector piminus(piminus_PX, piminus_PY, piminus_PZ, piminus_PE);

	   TLorentzVector phi = Kplus + Kminus;
	   TLorentzVector kstar = Kplus + piminus;
	   // cout << phi.M() << "\n";

	   // scatter1->Fill(phi.M2(), kstar.M2());

	   t->Fill();
	   
	   if((abs( phi.M() - 1019) < 10)  || (abs(kstar.M() - 892) < 100 ))
	   {
	     /*histo1->Fill(Ds_M);
	      histo2->Fill(phi.M());
	      histo3->Fill(kstar.M());
	      scatter2->Fill(phi.M2(), kstar.M2());
	     */
	     
	    }


 	  

    
  }

        newfile->Write();
       /*

     	TCanvas *c1 = new TCanvas("c1","DsM");
  	histo1->SetMinimum(0);
	histo1->Draw();
       	TCanvas *c2 = new TCanvas("c2","phi Resonance");
	histo2->SetMinimum(0);
	histo2->SetLineColor(1);
	histo2->Draw();
	TCanvas *c3 = new TCanvas("c3","k* Resonance");
	histo3->SetLineColor(2);
	histo3->Draw();

	TCanvas *c4 = new TCanvas("c4","");
	scatter1->Draw();
	scatter2->SetMarkerColor(2);
	scatter2->Draw("SAME");      
 */

}
