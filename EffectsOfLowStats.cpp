{
    TF1 *fExp = new TF1("fExp","TMath::Exp(-x*[0])",0,100);
    
    fExp->SetParameter(0,2.);
    
    TCanvas *c1 = new TCanvas();
    
    fExp->Draw();
    
    c1->SetLogy();
    
    TH1F *hExpLots = new TH1F("hExpLots","",1000,0,10);
    
    hExpLots->FillRandom("fExp",100000);
    
    hExpLots->Draw("E");
    
    TF1 *fFit1 = new TF1("fFit1","[1]*TMath::Exp(-x*[0])",0,100);
    TF1 *fFit2 = new TF1("fFit2","[1]*TMath::Exp(-x*[0])",0,100);
    TF1 *fFit3 = new TF1("fFit3","[1]*TMath::Exp(-x*[0])",0,100);
    TF1 *fFit4 = new TF1("fFit4","[1]*TMath::Exp(-x*[0])",0,100);
    
    fFit1->SetParameters(2,2000);
    fFit2->SetParameters(2,2000);
    
    hExpLots->Fit(fFit1,"BRMEN");
    hExpLots->Fit(fFit2,"BRMELN");
    hExpLots->SetLineColor(1);
    
    fFit1->Draw("same");
    fFit2->SetLineColor(4);
    fFit2->SetLineStyle(2);
    fFit2->Draw("same");
    
    std::cout << "Percentage difference for the decay constant is....." << abs(fFit1->GetParameter(0)-fFit2->GetParameter(0))/(fFit1->GetParameter(0))*100. << std::endl;
    
    TCanvas *c2 = new TCanvas();
    
    TH1F *hExpFew = new TH1F("hExpFew","",1000,0,10);
    hExpFew->FillRandom("fExp",500);
    hExpFew->Draw("E");
    hExpFew->SetLineColor(1);
    c2->SetLogy();
    
    fFit3->SetParameters(2,20);
    fFit4->SetParameters(2,20);
    
    hExpFew->Fit(fFit3,"BRMEN");
    hExpFew->Fit(fFit4,"BRMELN");
    hExpLots->SetLineColor(1);
    
    fFit3->Draw("same");
    fFit4->SetLineColor(3);
//     fFit4->SetLineStyle(2);
    fFit4->Draw("same");
    
    std::cout << "Percentage difference for the decay constant is....." << abs(fFit3->GetParameter(0)-fFit4->GetParameter(0))/(fFit3->GetParameter(0))*100. << std::endl;
}
