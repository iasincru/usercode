#include <stdlib.h>
#include <iostream>
#include "TFile.h"
#include "TH2.h"
#include "TString.h"
#include <cstring>
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"


//int newNbin=100;

TString inpath= TString("/scratch/hh/current/cms/user/asincruz/njs/M20Inf/");
TString outpath=TString("CorrelationPlots/M20Inf/");


void PurityAndStability(TH2F* histo_, TString channel_,TString particle_,  TString outname)
{

  //  int binX=histo_->GetNbinsX(); //The 2D histograms MUST have the same number of bins in the X&Y axis

  TH1 *gen, *reco, *genReco;
  TH1 *eff, *purity, *stability;
  
  //  std::cout<<"#binX"<<binX<<std::endl;
  gen=((TH2F*)histo_)->ProjectionX();//std::cout<<"gen #bins= "<<gen->GetNbinsX()<<std::endl;
  reco=((TH2F*)histo_)->ProjectionY();//std::cout<<"reco #bins= "<<reco->GetNbinsX()<<std::endl;
  genReco=(TH1F*)gen->Clone();//std::cout<<"gen&reco #bins= "<<genReco->GetNbinsX()<<std::endl;
  genReco->SetEntries(0);
  for (int i=0; i<genReco->GetNbinsX(); i++)
    {
      genReco->SetBinContent(i, histo_->GetBinContent(i, i));
    };

  purity=(TH1F*)genReco->Clone();
  purity->Divide(reco);

  stability=(TH1F*)genReco->Clone();
  stability->Divide(gen);

  
  eff=(TH1F*)reco->Clone();
  eff->Divide(gen);

  eff->SetMarkerStyle(21); eff->SetMarkerColor(3);
  purity->SetMarkerStyle(23); purity->SetMarkerColor(4);
  stability->SetMarkerStyle(22); stability->SetMarkerColor(2);

  genReco->SetMarkerStyle(21); genReco->SetMarkerColor(3);
  gen->SetMarkerStyle(23); gen->SetMarkerColor(4);
  reco->SetMarkerStyle(22); reco->SetMarkerColor(2);
    
  TLegend *leg2=new TLegend(0.8, 0.8, 0.95, 0.95);
  leg2->AddEntry(gen, "Generated", "p");
  leg2->AddEntry(reco,"Reconstructed", "p");
  leg2->AddEntry(genReco, "Gen&Reco", "p");


  TLatex *text=new TLatex();


  TCanvas c11;
  //  c11.SetLogy(1);
  reco->Draw("p");reco->SetStats(0);
  genReco->Draw("pSAME");
  gen->Draw("pSAME");
  leg2->Draw("SAME");
  text->DrawLatex(0.46, 0.91, channel_.Copy().Append(" channel"));
  c11.SaveAs(outname.Copy().Append(particle_).Append(channel_).Append("Gen&Reco&Genreco.eps"));
  c11.Clear();

  TLegend *leg=new TLegend(0.8, 0.8, 0.95, 0.95);
  leg->AddEntry(eff, "Efficiency", "p");
  leg->AddEntry(purity, "Purity", "p");
  leg->AddEntry(stability, "Stability", "p");

  purity->Draw("p");purity->SetStats(0);
  stability->Draw("pSAME");
  leg->Draw("SAME");
  text->DrawLatex(0.46, 0.91, channel_.Copy().Append(" channel"));
  c11.SaveAs(outname.Copy().Append(histo_->GetName()).Append(channel_).Append("EPS.eps")); 
  c11.Clear();
  c11.Close();
  

}



void CorrelationCalculator(TString variable, TString particle, TString step)
{


  TString channel[4];
  channel[0]=TString("EE");
  channel[1]=TString("EM");
  channel[2]=TString("MM");
  channel[3]=TString("Combined");


  if ( variable!="Pt" && variable!="Eta" && variable!="Rapidity" && variable!="Phi")
    { std::cout<<"Bad variable. Choose between: Pt=0, Eta=1, Rapidity=2 or Phi=3"<<std::endl; 
      return;
    };
  if (particle!="B" && particle!="BBar")
    {
      std::cout<<"Bad particle. Choose between: 'B' or 'BBar'. Implement other particles yourself"<<std::endl;
      return;
    };

  std::cout<<"Good variables"<<std::endl;

  TFile *f[3];
  f[0]=new TFile(inpath.Copy().Append("ee_ttbarsignal.root"));
  f[1]=new TFile(inpath.Copy().Append("emu_ttbarsignal.root"));
  f[2]=new TFile(inpath.Copy().Append("mumu_ttbarsignal.root"));
  for (int i=0; i<3; i++)
    {
      if (f[i]->IsZombie())
	{
	  std::cout<<f[i]->GetName()<<" doesn't exist"<<std::endl; 
	  return;
	};
    };
  std::cout<<"good files"<<std::endl;

  TString directory= TString("analyzeKinSolution");
  directory.Append(step);

  TDirectory *d[3];
  for (int i=0; i<3; i++)
    {
      d[i]=(TDirectoryFile*)f[i]->Get(directory);
      if(d[i]->IsZombie()) 
	{
	  std::cout<<d[i]->GetName()<<" doesn't exist in file "<<f[i]->GetName()<<std::endl; 
	  return;
	};
    };
  std::cout<<"good directories"<<std::endl;


  TH2F *h[4];
  TString hist=TString("2D_");
  hist.Append(particle).Append(variable);
 
  for(int i=0; i<3; i++)
    {
      h[i]=(TH2F*)d[i]->Get(hist);
      if (h[i]->IsZombie())
	{
	  std::cout<<h[i]->GetName()<<" doesn't exist in directory "<<d[i]->GetName()<<" from file "<<f[i]->GetName()<<std::endl;
	 return;
	};
    };
  
  std::cout<<"Good histograms"<<std::endl;
  
  h[3]=(TH2F*)h[0]->Clone();
  h[3]->SetEntries(0);
  for(int i=0; i<h[3]->GetNbinsX(); i++)
    {
      for (int j=0; j<h[3]->GetNbinsY(); j++)
	{
	  double weight=h[0]->GetBinContent(i, j)+h[1]->GetBinContent(i, j)+h[2]->GetBinContent(i, j);
	  h[3]->SetBinContent(i, j, weight);
	};
    };

 

 //Purity, stability and efficiency calculation
  PurityAndStability(h[0],channel[0], particle, outpath);
  PurityAndStability(h[1],channel[1], particle, outpath);
  PurityAndStability(h[2],channel[2], particle, outpath);
  PurityAndStability(h[3],channel[2], particle, outpath);

  




  TLatex *text=new TLatex();
  text->SetNDC(1);

  TCanvas c1;
  gStyle->SetPalette(1);

  for (int i=0; i<4; i++)
    {
      h[i]->SetStats(0);
      h[i]->Draw("COLZ");
      text->DrawLatex(0.46, 0.91, channel[i].Copy().Append(" channel"));
      c1.SaveAs(outpath.Copy().Append(h[i]->GetName()).Append(channel[i]).Append(".eps"));
      c1.Clear();
    };
  c1.Close();

  std::cout<<"he llgado al final sin errores"<<std::endl;
}


void CorrCalculator()
{

  CorrelationCalculator("Pt", "B", "7");
  CorrelationCalculator("Pt", "BBar", "7");
  CorrelationCalculator("Eta", "B", "7");
  CorrelationCalculator("Eta", "BBar", "7");
  CorrelationCalculator("Rapidity", "B","7");
  CorrelationCalculator("Rapidity", "BBar", "7");
  CorrelationCalculator("Phi", "B", "7");
  CorrelationCalculator("Phi", "BBar", "7");

}

int main()
{

  CorrCalculator();
 
}
