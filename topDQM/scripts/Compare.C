#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TAttLine.h>

void Compare(){
  
  TFile *f1 = TFile::Open("DQM_V0001_R000000001__TopVal__190689-191208__SingleMu__Run2012A-PromptReco-v1_DCSONLY_week15.root");
  TFile *f2 = TFile::Open("EnriqueDQM_V0001_R000000001__TopVal__190689-191208__SingleMu_Run2012A-PromptReco-v1_DCSONLY_week15.root");

/*
  TFile *f1 = TFile::Open("DQM_V0001_R000000001__TopVal__190456-190688__SingleMu__Run2012A-PromptReco-v1_week15.root");
  TFile *f2 = TFile::Open("DQM_V0001_R000000001__TopVal__190689-191208__SingleMu__Run2012A-PromptReco-v1_DCSONLY_week15.root");
  */

  TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step0";


  Plot1D(f1, f2, "ElecCalIso", "Step0.pdf(", dirstr);
  Plot1D(f1, f2, "ElecEta", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetMult", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "METCalo", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "METPflow", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "METTC", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MassTop", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MassW", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "PvMult", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", "Step0.pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", "Step0.pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", "Step0.pdf)", dirstr);
  
  
  TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step1";

  Plot1D(f1, f2, "ElecCalIso", "Step1.pdf(", dirstr);
//  Plot1D(f1, f2, "ElecCalIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetMult", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "METCalo", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "METPflow", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "METTC", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MassTop", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MassW", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "PvMult", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", "Step1.pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", "Step1.pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", "Step1.pdf)", dirstr);


TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step2";


  Plot1D(f1, f2, "ElecCalIso", "Step2.pdf(", dirstr);
//  Plot1D(f1, f2, "ElecCalIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetMult", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "METCalo", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "METPflow", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "METTC", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MassTop", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MassW", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "PvMult", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", "Step2.pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", "Step2.pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", "Step2.pdf)", dirstr);



TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step3";


  Plot1D(f1, f2, "ElecCalIso", "Step3.pdf(", dirstr);
//  Plot1D(f1, f2, "ElecCalIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetMult", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "METCalo", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "METPflow", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "METTC", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MassTop", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MassW", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "PvMult", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", "Step3.pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", "Step3.pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", "Step3.pdf)", dirstr);


TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step4";


  Plot1D(f1, f2, "ElecCalIso", "Step4.pdf(", dirstr);
//  Plot1D(f1, f2, "ElecCalIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetMult", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "METCalo", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "METPflow", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "METTC", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MassTop", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MassW", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "PvMult", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", "Step4.pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", "Step4.pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", "Step4.pdf)", dirstr);


  
  
}

//void Plot1D( TDirectoryFile *dir1, TDirectoryFile *dir2, TString hist, TString filetype){
  void Plot1D(TFile *f1, TFile *f2, TString hist, TString filetype, TString dirstr){
  
  
 
  
  TDirectoryFile *dir1 = (TFile*) f1->Get(dirstr);
  TDirectoryFile *dir2 = (TFile*) f2->Get(dirstr);
  
  
  TString outfilename = "Compare2Files";
  
  TH1* h1 = (TH1*)dir1->Get(hist);
  TH1* h2 = (TH1*)dir2->Get(hist);
  
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(5);
  //h1->SetMarkerStyle(20);
  
  h2->SetLineColor(kRed);
  h2->SetLineWidth(1);
  
//  TString h1_legend = "File1";
//  TString h2_legend = "File2";

  TString h1_legend = f1->GetName(); h1_legend.Remove(7);
  TString h2_legend = f2->GetName(); h2_legend.Remove(7);

  
  double maxh1 = h1->GetMaximum();
  double maxh2 = h2->GetMaximum();
  
  TCanvas *c1 = new TCanvas();
  
  /*  
  if (maxh1 >= maxh2){
    h1->Draw();
    h1->Draw("same, p");
    h2->Draw("same");
  }
  else{
    h2->Draw();
    h1->Draw("same");
    c1->SetLogy(1);
  }
  */
  
  
  h1->Draw();
  gPad->Update();
  TPaveStats* sb1=(TPaveStats*)(h1->FindObject("stats"));
  sb1->SetX1NDC(0.825);
  sb1->SetX2NDC(0.975);
  sb1->SetY1NDC(0.825);
  sb1->SetY2NDC(0.975);
  sb1->SetTextColor(h1->GetLineColor());
 // gPad->Modified();


  h2->Draw();
  gPad->Update();
  TPaveStats* sb2=(TPaveStats*)(h2->FindObject("stats"));
  sb2->SetX1NDC(0.825);
  sb2->SetX2NDC(0.975);
  sb2->SetY1NDC(0.775);
  sb2->SetY2NDC(0.625);
  sb2->SetTextColor(h2->GetLineColor());
  gPad->Modified();
  
  
  h1->Draw();
  h2->Draw("same");

  
  
  TLegend *l = new TLegend();
//  l->SetFillStyle(0);
  l->SetBorderSize(1);
  l->SetX1NDC(0.15);
  l->SetX2NDC(0.35);
  l->SetY1NDC(0.91);
  l->SetY2NDC(0.99);
/*  l->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-1.0);
  l->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
  l->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.5);
  l->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
*/
  l->AddEntry(h1, h1_legend, "lp");
  l->AddEntry(h2, h2_legend, "lp");
  
  l->Draw("same");
  
  drawRatio(h1, h2, 0.5, 1.5, *gStyle);
  
  c1->Print(outfilename.Append(filetype));
  
}


void drawRatio(const TH1* histNumerator, TH1* histDenominator, const Double_t& ratioMin, const Double_t& ratioMax, TStyle myStyle, int verbose=0, const std::vector<double> err_=std::vector<double>(0))
{
  // this function draws a pad with the ratio of 'histNumerator' and 'histDenominator'
  // the range of the ratio is 'ratioMin' to 'ratioMax'
  // to the systematic variation "sys" of the enumerator "systematicVariation"
  // per default only the gaussian error of the 'histNumerator' is considered:
  // (error(bin i) = sqrt(histNumerator->GetBinContent(i))/histDenominator->GetBinContent(i))
  // if 'err_' is present and its size equals the number of bins in the histos,
  // its valus are considered as error for the ratio
  // NOTE: x Axis is transferred from histDenominator to the bottom of the canvas
  // modified quantities: none
  // used functions: none
  // used enumerators: none

  // check that histos have the same binning
  if(histNumerator->GetNbinsX()!=histDenominator->GetNbinsX()){
    std::cout << "error when calling drawRatio - histos have different number of bins" << std::endl;
    return;
  }
  if(verbose>1){
    std::cout << "building ratio plot of " << histNumerator->GetName();
    std::cout << " and " << histDenominator->GetName() << std::endl;
  }
  // create ratio
  TH1F* ratio = (TH1F*)histNumerator->Clone();
  ratio->Divide(histDenominator);
  // calculate error for ratio
  // a) from err_
  if(err_.size()==(unsigned int)histNumerator->GetNbinsX()){
    if(verbose>0) std::cout << "ratio error from vector" << std::endl;
    for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
      ratio->SetBinError(bin, err_[bin-1]);
    }
  }
  else{
    // b) default: only gaussian error of histNumerator
    if(verbose>0) std::cout << "ratio error from statistical error of " << histNumerator->GetName() << " only" << std::endl;
    for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
      //      ratio->SetBinError(bin, sqrt(histNumerator->GetBinContent(bin))/histDenominator->GetBinContent(bin));
      ratio->SetBinError(bin, 0);
    }
  }
  // get some values from old pad
  //Int_t    logx = gPad->GetLogx();
  //Double_t left = gPad->GetLeftMargin();
  //Double_t right = gPad->GetRightMargin();

  Int_t    logx  = myStyle.GetOptLogx();
  Double_t left  = myStyle.GetPadLeftMargin();
  Double_t right = myStyle.GetPadRightMargin();

  // y:x size ratio for canvas
  double canvAsym = 4./3.;
  // ratio size of pad with plot and pad with ratio
  double ratioSize = 0.36;
  // change old pad
  gPad->SetBottomMargin(ratioSize);
  gPad->SetRightMargin(right);
  gPad->SetLeftMargin(left);
  gPad->SetBorderMode(0);
  gPad->SetBorderSize(0);
  gPad->SetFillColor(10);
  // create new pad for ratio plot
  TPad *rPad;
  rPad = new TPad("rPad","",0,0,1,ratioSize+0.001);
#ifdef DILEPTON_MACRO
  rPad->SetFillColor(10);
#else
  rPad->SetFillStyle(0);
  rPad->SetFillColor(0);
#endif
  rPad->SetBorderSize(0);
  rPad->SetBorderMode(0);
  rPad->Draw();
  rPad->cd();
  rPad->SetLogy(0);
  rPad->SetLogx(logx);
  rPad->SetTicky(1);
  // configure ratio plot
  double scaleFactor = 1./(canvAsym*ratioSize);
  ratio->SetStats(kFALSE);
  ratio->SetTitle("");
  ratio->SetMaximum(ratioMax);
  ratio->SetMinimum(ratioMin);
  ratio->SetLineWidth(1);
  // configure axis of ratio plot
  ratio->GetXaxis()->SetTitleSize(histNumerator->GetXaxis()->GetTitleSize()*scaleFactor*1.3);
  ratio->GetXaxis()->SetTitleOffset(histNumerator->GetXaxis()->GetTitleOffset()*0.9);
  ratio->GetXaxis()->SetLabelSize(histNumerator->GetXaxis()->GetLabelSize()*scaleFactor*1.4);
  ratio->GetXaxis()->SetTitle(histNumerator->GetXaxis()->GetTitle());
  ratio->GetXaxis()->SetNdivisions(histNumerator->GetNdivisions());
  ratio->GetYaxis()->CenterTitle();
  ratio->GetYaxis()->SetTitle("Ratio");
  ratio->GetYaxis()->SetTitleSize(histNumerator->GetYaxis()->GetTitleSize()*scaleFactor);
  ratio->GetYaxis()->SetTitleOffset(histNumerator->GetYaxis()->GetTitleOffset()/scaleFactor);
  ratio->GetYaxis()->SetLabelSize(histNumerator->GetYaxis()->GetLabelSize()*scaleFactor);
  ratio->GetYaxis()->SetLabelOffset(histNumerator->GetYaxis()->GetLabelOffset()*3.3);
  ratio->GetYaxis()->SetTickLength(0.03);
  ratio->GetYaxis()->SetNdivisions(505);
  ratio->GetXaxis()->SetRange(histNumerator->GetXaxis()->GetFirst(), histNumerator->GetXaxis()->GetLast());
  // delete axis of initial plot
  histNumerator->GetXaxis()->SetLabelSize(0);
  histNumerator->GetXaxis()->SetTitleSize(0);
  // draw ratio plot
  ratio->DrawClone("p e X0");
  ratio->SetMarkerSize(1.2);
  ratio->SetMarkerStyle(20);
  ratio->DrawClone("p e X0 same");
  rPad->SetTopMargin(0.0);
  rPad->SetBottomMargin(0.15*scaleFactor);
  rPad->SetRightMargin(right);
  gPad->SetLeftMargin(left);
  gPad->RedrawAxis();
  // draw grid
  rPad->SetGrid(1,1);

  // draw a horizontal lines on a given histogram
  // a) at 1
  Double_t xmin = ratio->GetXaxis()->GetXmin();
  Double_t xmax = ratio->GetXaxis()->GetXmax();
  TString height = ""; height += 1;
  TF1 *f = new TF1("f", height, xmin, xmax);
  f->SetLineStyle(1);
  f->SetLineWidth(1);
  f->SetLineColor(kBlack);
  f->Draw("L same");
  // b) at upper end of ratio pad
  TString height2 = ""; height2 += ratioMax;
  TF1 *f2 = new TF1("f2", height2, xmin, xmax);
  f2->SetLineStyle(1);
  f2->SetLineWidth(1);
  f2->SetLineColor(kBlack);
  f2->Draw("L same");
}
