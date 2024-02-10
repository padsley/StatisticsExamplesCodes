{
    int nevents = 5000;
    
    TCanvas *c1 = new TCanvas();
    
    //going to make 10 different random numbers which we're going to add together to get a distribution
    
//     TRandom3 **randy = new TRandom3[10];
    TRandom3 *randy = new TRandom3(0);
    
    TH1F *hCLM = new TH1F("hCLM","hCLM",1000,0,10);
    TH1F *hCLM_LOG = new TH1F("hCLM_LOG","hCLM_LOG",1000,0,0.01);
    TH1F *hCLM_LOG_2 = new TH1F("hCLM_LOG_2","hCLM_LOG_2",1000,-20,0);
    
    for(int i=0;i<nevents;i++)
    {
        double sum = 0, product = 0;
        for(int j=0;j<10;j++)
        {
            sum+=randy->Rndm();
            if(j==0)product = randy->Rndm();
            else product *= randy->Rndm();
        }
        hCLM->Fill(sum);
        hCLM_LOG->Fill(product);
        hCLM_LOG_2->Fill(TMath::Log(product));
    }
    
    hCLM->Draw();
    
    TCanvas *c2 = new TCanvas();
    hCLM_LOG->Draw();
    c2->SetLogy();
    
    TCanvas *c3 = new TCanvas();
    hCLM_LOG_2->Draw();
}
