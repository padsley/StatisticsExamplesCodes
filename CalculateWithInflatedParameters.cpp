#include <TGraphErrors.h>
#include <vector>
#include <TCanvas.h>

vector<double> Values, Uncertainties;

//this code is to calculate new weighted means and uncertainties for data which has a reduced chi squared of >1 - it's a bit naughty and there's good reasons NOT to do this but I don't care

//calculate the weighted mean from the results
double fWeightedMean(double ExtraSigma)
{
  double SumTop = 0;
  double SumWeights = 0;
    
  for(unsigned int i=0;i<Values.size();i++)
    {
      double Sigma = sqrt(pow(Uncertainties.at(i),2.) + pow(ExtraSigma,2.));
        
      SumTop += Values.at(i)/pow(Sigma,2.);
      SumWeights += 1./pow(Sigma,2.);
    }
    
  return SumTop/SumWeights;
}

//weighted uncertainty
double fWeightedSigma(double ExtraSigma)
{
  double SumWeights = 0;
    
  for(unsigned int i=0;i<Values.size();i++)
    {
      double Sigma = sqrt(pow(Uncertainties.at(i),2.) + pow(ExtraSigma,2.));
      SumWeights += 1./pow(Sigma,2.);
    }
    
  return sqrt(1./SumWeights);
}


//calculating the chi square
double fChiSquare(double *x, double *pars)
{
  double result = 0;
    
  double WeightedMean = fWeightedMean(x[0]);
    
  for(unsigned int i=0;i<Values.size();i++)
    {
      double Sigma = sqrt(pow(Uncertainties.at(i),2.) + pow(x[0],2.));
      result += pow(Values.at(i)-WeightedMean,2.)/pow(Sigma,2.);
    }
    
  return result;
}

//main function
void CalculateWithInflatedParameters()
{
  TCanvas *c1 = new TCanvas();
  //these are some resonance strengths, innit
  Values.push_back(2.5); Uncertainties.push_back(0.9);
  Values.push_back(5.7); Uncertainties.push_back(0.4);

    
    
  if(Values.size()==Uncertainties.size())
    {
      TGraphErrors *ge = new TGraphErrors();
         
      ge->SetName("gData");
         
      for(unsigned int i=0;i<Values.size();i++)
	{
	  ge->SetPoint(ge->GetN(),ge->GetN()+1,Values.at(i));
	  ge->SetPointError(ge->GetN()-1,0,Uncertainties.at(i));
	}
        
      TF1 *fChiSq = new TF1("fChiSq",fChiSquare,0,10);

      std::cout << "Weighted Mean: " << fWeightedMean(0) << std::endl;
      std::cout << "Uncertainty on the weighted mean: " << fWeightedSigma(0) << std::endl;
        
      std::cout << "Reduced ChiSquare: " << fChiSq->Eval(0)/(Values.size()-1.) << std::endl;
        
      std::cout << "Additional Uncertainty: " << fChiSq->GetX(1) << std::endl;
      std::cout << "Weighted Mean: " << fWeightedMean(fChiSq->GetX(1)) << std::endl;
      std::cout << "Uncertainty on the weighted mean: " << fWeightedSigma(fChiSq->GetX(1)) << std::endl;
        
      std::cout << "Reduced ChiSquare: " << fChiSq->Eval(fChiSq->GetX(1))/(Values.size()-1.) << std::endl;

      ge->Draw("AP");
      ge->SetMarkerStyle(8);
      ge->GetXaxis()->SetTitle("Data Point");
      ge->GetYaxis()->SetTitle("#omega#gamma [eV]");
      ge->GetXaxis()->CenterTitle();
      ge->GetYaxis()->CenterTitle();
      TLine *lEstimator = new TLine(1,fWeightedMean(0),ge->GetN(),fWeightedMean(0));
      TLine *lUpper = new TLine(1,fWeightedMean(0)+fWeightedSigma(0),ge->GetN(),fWeightedMean(0)+fWeightedSigma(0));
      TLine *lLower = new TLine(1,fWeightedMean(0)-fWeightedSigma(0),ge->GetN(),fWeightedMean(0)-fWeightedSigma(0));
      lEstimator->Draw("same");
      lEstimator->SetLineColor(2);
      lUpper->Draw("same");
      lLower->Draw("same");
      lUpper->SetLineColor(2);
      lLower->SetLineColor(2);
      lUpper->SetLineStyle(2);
      lLower->SetLineStyle(2);

      TLine *lEstimator2 = new TLine(1,fWeightedMean(fChiSq->GetX(1)),ge->GetN(),fWeightedMean(fChiSq->GetX(1)));
      TLine *lUpper2 = new TLine(1,fWeightedMean(fChiSq->GetX(1))+fWeightedSigma(fChiSq->GetX(1)),ge->GetN(),fWeightedMean(fChiSq->GetX(1))+fWeightedSigma(fChiSq->GetX(1)));
      TLine *lLower2 = new TLine(1,fWeightedMean(fChiSq->GetX(1))-fWeightedSigma(fChiSq->GetX(1)),ge->GetN(),fWeightedMean(fChiSq->GetX(1))-fWeightedSigma(fChiSq->GetX(1)));
      lEstimator2->Draw("same");
      lEstimator2->SetLineColor(4);
      lUpper2->Draw("same");
      lLower2->Draw("same");
      lUpper2->SetLineColor(4);
      lLower2->SetLineColor(4);
      lUpper2->SetLineStyle(2);
      lLower2->SetLineStyle(2);
    }
  else
    {
      std::cout << "Don't have the same amount of data and uncertainties!" << std::endl;
    }

    
}
