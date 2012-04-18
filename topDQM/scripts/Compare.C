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


  Plot1D(f1, f2, "ElecCalIso", ".pdf(", dirstr);
  Plot1D(f1, f2, "ElecEta", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMult", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "METCalo", ".pdf", dirstr);
  Plot1D(f1, f2, "METPflow", ".pdf", dirstr);
  Plot1D(f1, f2, "METTC", ".pdf", dirstr);
  Plot1D(f1, f2, "MassTop", ".pdf", dirstr);
  Plot1D(f1, f2, "MassW", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "PvMult", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", ".pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", ".pdf)", dirstr);
  
  
  TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step1";

//  Plot1D(f1, f2, "ElecCalIso", ".pdf(", dirstr);
  Plot1D(f1, f2, "ElecCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMult", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "METCalo", ".pdf", dirstr);
  Plot1D(f1, f2, "METPflow", ".pdf", dirstr);
  Plot1D(f1, f2, "METTC", ".pdf", dirstr);
  Plot1D(f1, f2, "MassTop", ".pdf", dirstr);
  Plot1D(f1, f2, "MassW", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "PvMult", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", ".pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", ".pdf)", dirstr);


TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step1";


//  Plot1D(f1, f2, "ElecCalIso", ".pdf(", dirstr);
  Plot1D(f1, f2, "ElecCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMult", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "METCalo", ".pdf", dirstr);
  Plot1D(f1, f2, "METPflow", ".pdf", dirstr);
  Plot1D(f1, f2, "METTC", ".pdf", dirstr);
  Plot1D(f1, f2, "MassTop", ".pdf", dirstr);
  Plot1D(f1, f2, "MassW", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "PvMult", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", ".pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", ".pdf)", dirstr);



TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step2";


//  Plot1D(f1, f2, "ElecCalIso", ".pdf(", dirstr);
  Plot1D(f1, f2, "ElecCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecEta", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMult", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecPt", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "ElecTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet1PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet2PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet3PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4Pt", ".pdf", dirstr);
  Plot1D(f1, f2, "Jet4PtRaw", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetBDiscVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMult", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBEff", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBPur", ".pdf", dirstr);
  Plot1D(f1, f2, "JetMultBVtx", ".pdf", dirstr);
  Plot1D(f1, f2, "METCalo", ".pdf", dirstr);
  Plot1D(f1, f2, "METPflow", ".pdf", dirstr);
  Plot1D(f1, f2, "METTC", ".pdf", dirstr);
  Plot1D(f1, f2, "MassTop", ".pdf", dirstr);
  Plot1D(f1, f2, "MassW", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonCalIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonDelZ", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonEta", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMult", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonMultIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonPt", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonRelIso", ".pdf", dirstr);
  Plot1D(f1, f2, "MuonTrkIso", ".pdf", dirstr);
  Plot1D(f1, f2, "PvMult", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerEff", ".pdf", dirstr);
//  Plot1D(f1, f2, "TriggerMon", ".pdf", dirstr);
  Plot1D(f1, f2, "TriggerMon", ".pdf)", dirstr);



  
  
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
  h1->SetMarkerStyle(20);
  
  h2->SetLineColor(kRed);
  h2->SetLineWidth(1);
  
//  TString h1_legend = "File1";
//  TString h2_legend = "File2";

  TString h1_legend = f1->GetName(); h1_legend.Remove(7);
  TString h2_legend = f2->GetName(); h2_legend.Remove(7);

  
  double maxh1 = h1->GetMaximum();
  double maxh2 = h2->GetMaximum();
  
  TCanvas *c1 = new TCanvas();
  
    
  if (maxh1 >= maxh2){
    h1->Draw("p");
    //h1->Draw("same, p");
    h2->Draw("same");
  }
  else{
    h2->Draw();
    h1->Draw("same");
    c1->SetLogy(1);
  }
  
  TLegend *l = new TLegend();
//  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.60);
  l->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
  l->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.40);
  l->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
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
  ratio->GetYaxis()->SetTitle("#frac{Non t}{t-quark}");
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
