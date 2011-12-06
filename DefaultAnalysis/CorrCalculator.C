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
#include "TPaletteAxis.h"
#include "TPad.h"


//****** Different Selection Cuts Sources ********
//================================================
//****** Default analysis: Mll>12 GeV  ***********
//TString inpath=TString("/scratch/hh/current/cms/user/wbehrenh/Oct25default/standard"); TString outpath=TString("CorrelationPlots/Default/");

//Mll>20 GeV Cut
TString inpath= TString("/scratch/hh/current/cms/user/asincruz/njs/M20Inf/"); TString outpath=TString("CorrelationPlots/M20Inf/");

//Mll>40 GeV
//TString inpath=TString("/scratch/hh/current/cms/user/asincruz/njs/M40Inf/"); TString outpath=TString("CorrelationPlots/M40Inf/");

//Mll>50 GeV
//TString inpath=TString("/scratch/hh/current/cms/user/asincruz/njs/M50Inf/"); TString outpath=TString("CorrelationPlots/M50Inf/");




//*****  OUTPUT Format*****
TString outformat=TString(".eps");
//TString outformat=TString(".png");

void PurityAndStability(TH2F* histo_, TString channel_,TString particle_,  TString outname)
{


  TH1 *gen, *reco, *genReco;
  TH1 *eff, *purity, *stability;
  
  gen=((TH2F*)histo_)->ProjectionX();
  reco=((TH2F*)histo_)->ProjectionY();
  genReco=(TH1F*)gen->Clone();
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
  leg2->SetBorderSize(1.5);
  leg2->AddEntry(gen, "Generated", "p");
  leg2->AddEntry(reco,"Reconstructed", "p");
  leg2->AddEntry(genReco, "Gen&Reco", "p");


  TLatex *text=new TLatex(); text->SetNDC(1);


  TCanvas c11;
  //  c11.SetLogy(1);
  reco->Draw("p");reco->SetStats(0);
  genReco->Draw("pSAME");
  gen->Draw("pSAME");
  leg2->Draw("SAME");
  text->DrawLatex(0.46, 0.91, channel_.Copy().Append(" channel"));
  c11.SaveAs(outname.Copy().Append(particle_).Append(channel_).Append("Gen&Reco&Genreco").Append(outformat));
  c11.Clear();

  TLegend *leg=new TLegend(0.8, 0.8, 0.95, 0.95);
  leg->SetBorderSize(1.5);
  //  leg->AddEntry(eff, "Efficiency", "p");
  leg->AddEntry(purity, "Purity", "p");
  leg->AddEntry(stability, "Stability", "p");

  purity->SetMaximum(1.15);
  purity->SetMinimum(0);
  purity->SetStats(0);
  purity->Draw("p");
  stability->Draw("pSAME");
  leg->Draw("SAME");
  text->DrawLatex(0.46, 0.91, channel_.Copy().Append(" channel"));
  c11.SaveAs(outname.Copy().Append(histo_->GetName()).Append(channel_).Append("EPS").Append(outformat)); 
  c11.Clear();
  c11.Close();
  

}



void CorrelationCalculator(TString variable, TString particle, TString step, int rebin_)
{


  TString channel[4];
  channel[0]=TString("EE");
  channel[1]=TString("EM");
  channel[2]=TString("MM");
  channel[3]=TString("Combined");

  TString directory= TString("analyzeKinSolution"); 
  directory.Append(step);

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
 
  TDirectory *d[3];
  for (int i=0; i<3; i++)
    {
      if (f[i]->IsZombie())
	{
	  std::cout<<f[i]->GetName()<<" doesn't exist"<<std::endl; 
	  return;
	};

      d[i]=(TDirectoryFile*)f[i]->Get(directory);
      if(d[i]->IsZombie()) 
	{
	  std::cout<<d[i]->GetName()<<" doesn't exist in file "<<f[i]->GetName()<<std::endl; 
	  return;
	};
    };


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

  for (int i=0; i<4; i++){h[i]->Rebin2D(rebin_, rebin_);};

 

 //Purity, stability and efficiency calculation
  PurityAndStability(h[0],channel[0], particle, outpath);
  PurityAndStability(h[1],channel[1], particle, outpath);
  PurityAndStability(h[2],channel[2], particle, outpath);
  PurityAndStability(h[3],channel[3], particle, outpath);

  




  TLatex *text=new TLatex();
  text->SetNDC(1);

  TCanvas c1;
  gStyle->SetPalette(1);

  TPaletteAxis *palette[4];

  for (int i=0; i<4; i++)
    {
      h[i]->Draw("COLZ");
      gPad->Update();
      palette[i] = (TPaletteAxis*) h[i]->GetListOfFunctions()->FindObject("palette");
      palette[i]->SetX2NDC(0.93);
      h[i]->SetStats(0);
      h[i]->Draw("COLZ");
      text->DrawLatex(0.46, 0.91, channel[i].Copy().Append(" channel"));
      c1.SaveAs(outpath.Copy().Append(h[i]->GetName()).Append(channel[i]).Append(outformat));
      c1.Clear();
    };
  c1.Close();

}


void CorrCalculator()
{
  int rebin=1;//number of bins to be merged together
  CorrelationCalculator("Pt", "B", "7", rebin);
  CorrelationCalculator("Pt", "BBar", "7", rebin);

  rebin=1;
  CorrelationCalculator("Eta", "B", "7", rebin);
  CorrelationCalculator("Eta", "BBar", "7", rebin);

  rebin=1;
  CorrelationCalculator("Rapidity", "B","7", rebin);
  CorrelationCalculator("Rapidity", "BBar", "7", rebin);

  rebin=1;
  CorrelationCalculator("Phi", "B", "7", rebin);
  CorrelationCalculator("Phi", "BBar", "7", rebin);

}

int main()
{

  CorrCalculator();
 
}
