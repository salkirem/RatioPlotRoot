///////// FOR RUN THIS FILE :
            // open the Delphes folder on the terminal ex: cd Delphes-3.5.0
//////// Start ROOT and load Delphes shared library: 
           
           // OPEN root ON TERMINAL  
           // root[0] gSystem->Load("libDelphes");
           // root [1]  .X Folder_Name/Ratio.C("events_PYTHIA8_0_1.root");
           // "events_PYTHIA8_0_1.root" file contains the data which we use in this analysis.
////////

void Ratio(const char *inputFile){
///// creating chain of root trees and defining object of class with ExRootTr... and for reading the given data
  gSystem->Load("libDelphes");


  TChain chain("Delphes");
  chain.Add(inputFile);
  
  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  
///// To create TClonesArray, access branches of the root file that will be use in this analysis 
  TClonesArray *branchElectron= treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");

///// Histograms 
  TH1 *h1 = new TH1F("h1", "Electron_PT", 50,0,500);
  TH1 *hee = new TH1F("hee","Electron_Eta",20,-3,3);
  TH1 *hep =new TH1F("hep","Electron_Phi",20,-4,4);
  TH1 *h2 = new TH1F("h2", "Muon_PT",50,0,500);
  TH1 *hme= new TH1F("hme", "Muon_Eta",20,-3,3);
  TH1 *hmp= new TH1F("hmp", "Muon_Phi",20,-4,4);
 

///// output of the analysis can be collected by creating TFile   
 TFile *output = TFile::Open("EMRatio.root", "RECREATE"); 


///// Loop over all events
	for(Int_t entry = 0; entry < numberOfEntries; ++entry)
  {
////// Load selected branches with data from specified event    
        treeReader->ReadEntry(entry);
////// selecting events that have at least 1 electron 
        if(branchElectron->GetEntries() > 0)
///// loop on electron gives all the electrons and fill the histogram with the leaf of branch: PT,ETA etc.
      {
              for(int i = 0; i < branchElectron->GetEntries(); ++i)   {
                    Electron *electron = (Electron *) branchElectron->At(i);
                    h1->Fill(electron->PT);
                    hee->Fill(electron->Eta);
                    hep->Fill(electron->Phi);
                    //cout << "electron_pt="<< electron->PT << endl;
                    
              } 
      }
///// same process with electrons
        if(branchMuon->GetEntries() > 0)
      {
              for(int j = 0; j < branchMuon->GetEntries(); ++j)   {
                    Muon *muon = (Muon *) branchMuon->At(j);
                    
                    h2->Fill(muon->PT);
                    hme->Fill(muon->Eta);
                    hmp->Fill(muon->Phi);

                    //cout << "muon_pt="<< muon->PT << endl;
              } 
      }

  }
///// create canvas 
	TCanvas *c1 = new TCanvas("c1","pt ratio",1600,1600);
//// PT histograms draw in the new pad, pad1. 	 
	TPad *pad1 =new TPad("pad1","PAD PT",0,0.3,1,1.0);
	  //pad1->SetBottomMargin(0.1);
   	pad1->SetGridx();        
   	pad1->Draw();             
   	pad1->cd();  //// open pad1 so pad1 is the current pad

    //Y axis of the histogram h1 in the range of 0 to 5000
    h1->SetMinimum(0);  h1->SetMaximum(5000);            	
   	h1->Draw();         
   	h2->Draw("same");      ///h1 and h2 draw on the same place. h2 on h1       
   
   	c1->cd();         ///// turn to the canvas c1
   	TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
    pad2->SetTopMargin(0.1);
   	pad2->SetGridx();  ////Vertical grid
    pad2->SetGridy();  ////Horizontal grid
   	pad2->Draw();

 //// open pad2, now pad2 is the current canvas and define the ratio plot
  	pad2->cd();      
   	TH1F *h3 = (TH1F*)h2->Clone("h3");
   	
//// h1,h2,h3 settings: color, no statistic , font and size     
	  h3->SetLineColor(kRed);
   	h3->Sumw2();
   	h3->Divide(h1);
   	h3->Draw();       // Draw the ratio plot
    h3->SetStats(0); 
    h1->SetTitle(" ");
   	h1->SetLineColor(kBlue);
    h1->SetStats(0); 
	  h2->SetLineColor(kRed);
    h2->SetStats(0);
   	h3->SetTitle(""); 
   	h3->GetYaxis()->SetTitle("m/e");
    h3->GetYaxis()->SetTitleOffset(1.5);
    h3->GetYaxis()->SetTitleSize(26);
   	h3->GetYaxis()->SetTitleFont(43);
   	h3->GetYaxis()->SetLabelFont(43); 
   	h3->GetYaxis()->SetLabelSize(30);
    h3->GetXaxis()->SetLabelFont(43); 
   	h3->GetXaxis()->SetLabelSize(30);
    h1->GetYaxis()->SetLabelFont(43); 
   	h1->GetYaxis()->SetLabelSize(30);
    h1->GetXaxis()->SetLabelFont(43); 
   	h1->GetXaxis()->SetLabelSize(30);
    h1->SetLineWidth(2);
    h2->SetLineWidth(2);
    h3->SetLineWidth(2);
    
//// turn back to pad 1 for creating the legend of the used branches
    pad1->cd();
    TLegend *leg = new TLegend(0.8,0.8,0.9,0.9);
    leg->AddEntry(h1,"Elektron PT","l");
    leg->AddEntry(h2,"Muon PT","l");
    leg -> Draw();

    TCanvas *c2 = new TCanvas("c2","eta ratio",1600,1600);
    TPad *pad3 =new TPad("pad3","PAD ETA",0,0.3,1,1.0);
	
    //pad3->SetBottomMargin(0.1);
   	pad3->SetGridx();       
   	pad3->Draw();             
   	pad3->cd();              
   	hee->SetMinimum(0);  
   	hee->SetMaximum(3000);
	  hee->Draw();         
   	hme->Draw("same");   

    c2->cd();          
   	TPad *pad5 = new TPad("pad2", "pad ETA RATIO", 0, 0.05, 1, 0.3);
    pad5->SetTopMargin(0.1);
   	pad5->SetGridx(); 
    pad5->SetGridy(); 
   	pad5->Draw();
   	pad5->cd();       
   
   	TH1F *heme = (TH1F*)hme->Clone("heme");

	  heme->SetLineColor(kRed);
   	heme->Sumw2();
   	heme->Divide(hee);
   	heme->Draw();       
    heme->SetStats(0); 
    hee->SetTitle(" ");
   	hee->SetLineColor(kBlue);
    hee->SetStats(0); 
	  hme->SetLineColor(kRed);
    hme->SetStats(0);
    heme->SetTitle(""); 
   	heme->GetYaxis()->SetTitle("m/e");
    heme->GetYaxis()->SetTitleOffset(1.5);
    heme->GetYaxis()->SetTitleSize(26);
   	heme->GetYaxis()->SetTitleFont(43);
   	heme->GetYaxis()->SetLabelFont(43); 
   	heme->GetYaxis()->SetLabelSize(30);
    heme->GetXaxis()->SetLabelFont(43); 
   	heme->GetXaxis()->SetLabelSize(30);
    hee->GetYaxis()->SetLabelFont(43); 
   	hee->GetYaxis()->SetLabelSize(30);
    hee->GetXaxis()->SetLabelFont(43); 
   	hee->GetXaxis()->SetLabelSize(30);
    hee->SetLineWidth(2);
    hme->SetLineWidth(2);
    heme->SetLineWidth(2);

    pad3->cd();
    TLegend *leg1 = new TLegend(0.8,0.8,0.9,0.9);

    leg1->AddEntry(hee,"Elektron ETA","l");
    leg1->AddEntry(hme,"Muon ETA","l");
    leg1 -> Draw();
 
    TCanvas *c3 = new TCanvas("c3","phi ratio",1600,1600);
    TPad *pad4 =new TPad("pad4","PAD PHI",0,0.3,1,1.0);
		//pad4->SetBottomMargin(0.1);
   	pad4->SetGridx();        
   	pad4->Draw();             
   	pad4->cd();              
   	// Define  limit of Y axis on the histogram hep ..
    hep->SetMinimum(0);  	hep->SetMaximum(2000);
	  hep->Draw();         
   	hmp->Draw("same"); 
   	
    c3->cd();          
   	TPad *pad6 = new TPad("pad2", "pad PHI RATIO", 0, 0.05, 1, 0.3);
    
    pad6->SetTopMargin(0.1);
   	pad6->SetGridx(); 
    pad6->SetGridy(); 
   	pad6->Draw();
   	pad6->cd();      
    
   	TH1F *hemp = (TH1F*)hmp->Clone("hemp");
   	
  	hemp->SetLineColor(kRed);
   	hemp->Sumw2();
   	hemp->Divide(hep);
   	hemp->Draw(); 
    hemp->SetStats(0); 
    hep->SetTitle(" ");
   	hep->SetLineColor(kBlue);
    hep->SetStats(0); 
	  hmp->SetLineColor(kRed);
    hmp->SetStats(0); 
   	hemp->SetTitle(""); 
    hemp->GetYaxis()->SetTitle("m/e"); 
    hemp->GetYaxis()->SetTitleOffset(1.5);
    hemp->GetYaxis()->SetTitleSize(26);
   	hemp->GetYaxis()->SetTitleFont(43);
   	hemp->GetYaxis()->SetLabelFont(43); 
   	hemp->GetYaxis()->SetLabelSize(30);
    hemp->GetXaxis()->SetLabelFont(43); 
   	hemp->GetXaxis()->SetLabelSize(30);
    hep->GetYaxis()->SetLabelFont(43); 
   	hep->GetYaxis()->SetLabelSize(30);
    hep->GetXaxis()->SetLabelFont(43); 
   	hep->GetXaxis()->SetLabelSize(30);
    hep->SetLineWidth(2);
    hmp->SetLineWidth(2);
    hemp->SetLineWidth(2);
   	
    pad4->cd();
    TLegend *leg2 = new TLegend(0.8,0.8,0.9,0.9);
    leg2->AddEntry(hep,"Elektron phi","l");
    leg2->AddEntry(hmp,"Muon phi","l");
    leg2 -> Draw();

////// open the Output which we define in the beginning with TFile for filling the root file 
 output->cd();

 h1->Write();
 h2->Write();
 h3->Write();
 hee->Write();
 hme->Write();
 heme->Write();
 hep->Write();
 hmp->Write();
 hemp->Write();
////// To get PDF form of the analysis  
 c1->Print("PTratio3.pdf","pdf");
 c2->Print("ETAratio3.pdf","pdf");
 c3->Print("PHIratio3.pdf","pdf");

 
}