using namespace RooFit;


void Fit(){

  TFile *file =  new TFile("outputFin.root");
  TTree* tree1 = (TTree*) file->Get("t");

  RooRealVar Mass("Mass","Mass",5400,6000) ;
  RooDataSet data("data","dataset with mass",Mass,Import(*tree1)) ;


  RooRealVar mean("mean","mean",5720,5710,5730) ;
  RooRealVar sigma("sigma","sigma",20.,3.,100.) ;
  RooGaussian sig("sig","signal p.d.f.",Mass,mean,sigma) ;
    
   RooRealVar c0("c0","coefficient #0", 0.9,-10.0,10.) ;
   RooRealVar c1("c1","coefficient #1",0.1, -10.,10.) ;
   //RooExponential bkg("bkg","background p.d.f.",Mass,c0);
   RooRealVar c2("c2", "coefficient #2",1.,-10.,100.) ;
   //  RooRealVar c3("c3", "coefficient #3",100.,-100.,1.) ;
   // RooPolynomial bkg("bkg","background p.d.f.",Mass,RooArgList(c0,c1)) ;

   RooChebychev bkg("bkg","background p.d.f.",Mass,RooArgList(c0, c1)) ;
  RooRealVar fsig1("fsig1","signal fraction1",50,0.,10000.) ;
  RooRealVar fsig2("fsig2","signal fraction2",2700,0.,10000.) ;  

  // model(x) = fsig*sig(x) + (1-fsig)*bkg(x)
  RooAddPdf model("model","model",RooArgList(sig,bkg),RooArgList(fsig1,fsig2)) ;

  model.fitTo(data, Range(5600,5900));


  
  
  RooDataSet* data2 = model.generate(Mass) ;

   data2->Print();
 
  RooPlot* frame = Mass.frame() ;
  //data2->plotOn(frame,Binning(50),MarkerColor(kRed));
  data.plotOn(frame,Binning(50),RooFit::Name("data") );
  model.plotOn(frame, Range(5500,6000),RooFit::Name("model"));
  model.plotOn(frame, Components("sig"),LineStyle(kDashed)) ;

  frame->GetXaxis()->SetTitle("Mass (MeV)");
  auto leg = new TLegend(0.2,0.6,0.49,0.89);
  leg->AddEntry(frame->findObject("data"),"Data","lep");
  leg->AddEntry(frame->findObject("model"),"Fit","l");
 
  frame->Draw();
   leg->Draw("SAME");




}
