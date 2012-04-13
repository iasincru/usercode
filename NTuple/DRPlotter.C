#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <iostream>
#include <TPaveText.h>
#include <TLegend.h>
#include <TAttLine.h>
#include <TCanvas.h>

void DRPlotter(){

  
  //Leading Jet Index distributionfor pT leading not and top
  DrawComparisons(2, 0, 1, "IndexLeadingDRDistrib", ".pdf(");
  //Leading Jet Index distributionfor pT leading not and top
  DrawComparisons(2, 1, 1, "IndexLeadingDRDistrib", ".pdf");
  
  //pT distributions for pT leading not and top jets
  DrawComparisons(0, 0, 1, "PtLeadingPtDistrib", ".pdf");
  //pT distributions for pT next-leading not and top jets
  DrawComparisons(0, 0, 0, "PtNLeadingPtDistrib", ".pdf");
  //pT distributions for DR leading not and top jets
  DrawComparisons(0, 1, 1, "DRLeadingPtDistrib", ".pdf");
  //pT distributions for DR next-leading not and top jets
  DrawComparisons(0, 1, 0, "DRNLeadingPtDistrib", ".pdf");
  
  //DR distributions for pT leading not and top jets
  DrawComparisons(1, 0, 1, "PtLeadingDRDistrib", ".pdf");
  //DR distributions for pT next-leading not and top jets
  DrawComparisons(1, 0, 0, "PtNLeadingDRDistrib", ".pdf");
  //DR distributions for DR leading not and top jets
  DrawComparisons(1, 1, 1, "DRLeadingDRDistrib", ".pdf");
  //DR distributions for DR next-leading not and top jets
  DrawComparisons(1, 1, 0, "DRNLeadingDRDistrib", ".pdf");
  
  //pT distribution for pT-leading or DR-leading jet
  DrawComparisons2(0, "LeadJet", "PtpTLeadVsDRLead", ".pdf");
  //pT distribution for pT-NLeading or DR-NLeading jets
  DrawComparisons2(0, "NLeadJet", "PtpTNLeadVsDRNLead", ".pdf");
  //pT distribution for pT-leading or DR-leading jet from top
  DrawComparisons2(0, "LeadTopJet", "PtpTLeadTopVsDRLeadTop", ".pdf");
  //pT distribution for pT-NLeading or DR-NLeading jets from top
  DrawComparisons2(0, "NLeadTopJet", "PtpTNLeadTopVsDRNLeadTop", ".pdf");
  
  //DR distribution for pT-Leading or DR-Leading jets
  DrawComparisons2(1, "LeadJet", "DRpTLeadVsDRLead", ".pdf");
  //DR distribution for pT-NLeading or DR-NLeading jets from Top
  DrawComparisons2(1, "NLeadJet", "DRpTNLeadVsDRNLead", ".pdf");
  //DR distribution for pT-Leading or DR-Leading jets
  DrawComparisons2(1, "LeadTopJet", "DRpTLeadTopVsDRLeadTop", ".pdf");
  //DR distribution for pT-NLeading or DR-NLeading jets from Top
  DrawComparisons2(1, "LeadTopJet", "DRpTNLeadTopVsDRNLeadTop", ".pdf)");
  
  return;
}


void DrawComparisons2(int quantity, TString h_name, TString filename, TString filetype, bool LogY = 0){
  
  TFile *f= TFile::Open("selectionRoot/mumu/ttbarsignalplustau.root");
  
  TH1D *h1, *h2;
  TString h1_legend, h2_legend;
  TString h1_title, h2_title;
  TString h1_Xaxis, h2_Xaxis;
  TString h1_name="", h2_name="";
  
  
  if(quantity == 0){
    h1_name="pT";
    h1_Xaxis = "p_{T} [GeV]";
    h2_Xaxis = "p_{T} [GeV]";
  }
  else if(quantity == 1){
    h1_name="DR";
    h1_Xaxis = "#DeltaR";
    h2_Xaxis = "#DeltaR";
  }
  else{
    cout<<"ERROR: you used a wrong set up: 0:pT or 1:DR"<<endl;
    return;
  };
  
  h1_name.Append(h_name);
  h2_name = h1_name;
  h2_name.Append("DR");
  
  
  h1_legend = "pT ordering";
  h2_legend = "#Delta R ordering";
  
  
  h1 = (TH1D*) f->Get(h1_name);
  h2 = (TH1D*) f->Get(h2_name);

  
  TCanvas *c1 = new TCanvas();//("", "", 0, 0, 1000, 1000);
  //h1->SetTitle(h1_title);
  h1->SetLineWidth(2);
  h1->GetXaxis()->SetTitle(h1_Xaxis);
  
  h2->SetLineColor(kRed);
  h2->SetLineStyle(5);
  h2->SetLineWidth(2);
  
  c1->SetLogy(LogY);
  h1->Draw();
  h2->Draw("same");
  
  TLegend *l = new TLegend();
  l->AddEntry(h1, h1_legend, "lp");
  l->AddEntry(h2, h2_legend, "lp");
  
  l->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.40);
  l->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
  l->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.15);
  l->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
  
  l->Draw("same");
  drawRatio(h1, h2, 0.5, 1.5, *gStyle);
  
  MakeTable(h1, h2, h1_name, h2_name);
  
  
  //c1->SaveAs(filename.Append(".").Append(filetype));
  
  TString FILE ="TESTPlot";
  c1->Print(FILE.Append(filetype));
}


//void Draw(TString h1_sample, TString h2_sample, TString quantity, TString channel, int rebin){ //for later purposes
void DrawComparisons(int quantity, int distribution, bool leading, TString filename, TString filetype, bool LogY = 0){
  
  //quantity: 0=pT, 1=DR, 2=Index or 3=size distributions
  //distributions: 0=pT-leading or 1=DR-leading selection
  //leading: 1=only leading jets    0= Next to leading jets
  //LogY: Y-axis scale type
  
  TFile *f= TFile::Open("selectionRoot/mumu/ttbarsignalplustau.root");
  
  TH1D *h1, *h2;
  TString h1_legend, h2_legend;
  TString h1_title, h2_title;
  TString h1_Xaxis, h2_Xaxis;
  TString h1_name="", h2_name="";
  
  if (quantity == 0){
    h1_name.Append("pT");
    h2_name.Append("pT");
  }
  else if(quantity == 1){
    h1_name.Append("DR");
    h2_name.Append("DR");
  }
  else if(quantity == 2){
    h1_name.Append("Index");
    h2_name.Append("Index");
  }
  else{
    cout<<"ERROR: you used a wrong set up: pT or DR"<<endl;
    return;
  };
  
  if (leading == 1){
    h1_name.Append("LeadJet");
    h2_name.Append("LeadTopJet");
    h1_title.Append("Leading Jet");
  }
  else if (leading == 0){
    h1_name.Append("NLeadJet");
    h2_name.Append("NLeadTopJet");
    h1_title.Append(" Next-leading Jets");
  }
  else {
    cout<<"ERROR: you used a wrong set up: 1 or 0"<<endl;
    return;
  }
  
  if (distribution == 0){
    h1_name.Append("");
    h2_name.Append("");
    h1_title.Prepend("pT ordered ");
  }
  else if (distribution == 1){
    h1_name.Append("DR");
    h2_name.Append("DR");
    h1_title.Prepend("DR ordered ");
  }
  else{
    cout<<"ERROR: you used a wrong set up: DR or '' "<<endl;
    return;
  }
  
  if(quantity == 0){
    h1_Xaxis = "p_{T} [GeV]";
    h2_Xaxis = "p_{T} [GeV]";
  }
  else if(quantity == 1){
    h1_Xaxis = "#DeltaR";
    h2_Xaxis = "#DeltaR";
  }
  else if(quantity == 2){
    h1_Xaxis = "Jet Index";
    h2_Xaxis = "Jet Index";
  }
  else{
    cout<<"ERROR: you used a wrong set up: 0:pT, 1:DR or 2:Index "<<endl;
    return;
  }
  
  h1 = (TH1D*) f->Get(h1_name);
  h2 = (TH1D*) f->Get(h2_name);

  h1_legend = "Not t-quark";
  h2_legend = "From t-quark";
  
  
  TCanvas *c1 = new TCanvas();//("", "", 0, 0, 1000, 1000);
  h1->SetTitle(h1_title);
  h1->SetLineWidth(2);
  h1->GetXaxis()->SetTitle(h1_Xaxis);
  
  h2->SetLineColor(kRed);
  h2->SetLineStyle(5);
  h2->SetLineWidth(2);
  
  c1->SetLogy(LogY);
  h1->Draw();
  h2->Draw("same");
  
  TLegend *l = new TLegend();
  l->AddEntry(h1, h1_legend, "lp");
  l->AddEntry(h2, h2_legend, "lp");
  
  l->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.40);
  l->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
  l->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.15);
  l->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
  
  l->Draw("same");
  drawRatio(h1, h2, 0.5, 1.5, *gStyle);
  
  MakeTable(h1, h2, h1_name, h2_name);
  
  
  //c1->SaveAs(filename.Append(".").Append(filetype));
  
  TString FILE ="TESTPlot";
  c1->Print(FILE.Append(filetype));
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


void MakeTable(TH1* h1, TH1* h2, TString h1_name, TString h2_name){
  
  cout<<"================="<<endl;
  cout<<h1_name<<" #Entries:"<<h1->GetEntries()<<endl;
  cout<<"#bin    BinCenter    BinRange     binContent"<<endl;
  for (int i=0; i< h1->GetNbinsX(); ++i){
    cout<<i<<" "<<h1->GetBinCenter(i)<<" "<<h1->GetBinLowEdge(i)<<" "<<h1->GetBinLowEdge(i+1)<<" "<<h1->GetBinContent(i)<<endl;
  }
  cout<<"-----------------"<<endl;
  
  cout<<h2_name<<" #Entries:"<<h2->GetEntries()<<endl;
  cout<<"#bin  BinCenter  BinRange   binContent"<<endl;
  for (int i=0; i< h2->GetNbinsX(); ++i){
    cout<<i<<" "<<h2->GetBinCenter(i)<<" "<<h2->GetBinLowEdge(i)<<" "<<h2->GetBinLowEdge(i+1)<<" "<<h2->GetBinContent(i)<<endl;
  }
  cout<<"-----------------"<<endl;
  
}
