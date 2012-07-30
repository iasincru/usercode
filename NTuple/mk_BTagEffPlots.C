#include <TFile.h>
#include <TH1.h>
#include <TAxis.h>
#include <TString.h>
#include <TAttFill.h>
#include <TCanvas.h>
#include <TStyle.h>



void mk_EffPlots(){

    setHHStyle(*gStyle);
    TString channel = TString("emu");
    TCanvas *c1 = new TCanvas();
    TFile *f = TFile::Open("BTagEff_Ivan/"+channel+"/ttbarsignalplustau.root");
    TH1D *h_temp;
    h_temp = (TH1D*)f->Get("BEffPt");
    h_temp = HistoStyle(h_temp, 2, "", "p_{T}^{b-jet} (GeV/c)", "#epsilon", 30, 600, 0.25, 1.);
    Draw(h_temp);
    c1->SaveAs("EffBJet_Pt.eps");
    c1->SaveAs("JetEfficiencies.eps(");
    h_temp->Clear();
    c1->Clear();
    
    h_temp = (TH1D*)f->Get("BEffEta");
    h_temp = HistoStyle(h_temp, 2, "", "|#eta^{b-jet}|", "#epsilon",0.0, 2.0, 0.85, 0.9);
    Draw(h_temp);
    c1->SaveAs("EffBJet_Eta.eps");
    c1->SaveAs("JetEfficiencies.eps");
    h_temp->Clear();
    c1->Clear();
    
    h_temp = (TH1D*)f->Get("CEffPt");
    h_temp = HistoStyle(h_temp, 2, "", "p_{T}^{c-jet} (GeV/c)", "#epsilon", 30, 600, 0.15, 0.6);
    Draw(h_temp);
    c1->SaveAs("EffCJet_Pt.eps");
    c1->SaveAs("JetEfficiencies.eps");
    h_temp->Clear();
    c1->Clear();
    
    h_temp = (TH1D*)f->Get("CEffEta");
    h_temp = HistoStyle(h_temp, 2, "", "|#eta_{T}^{c-jet}|", "#epsilon",0.0, 2.0, 0.0, 0.75);
    Draw(h_temp);
    c1->SaveAs("EffCJet_Eta.eps");
    c1->SaveAs("JetEfficiencies.eps");
    h_temp->Clear();
    c1->Clear();
    
    h_temp = (TH1D*)f->Get("LEffPt");
    h_temp = HistoStyle(h_temp, 2, "", "p_{T}^{l-jet} (GeV/c)", "#epsilon", 30, 600, 0.1, 0.3);
    Draw(h_temp);
    c1->SaveAs("EffLJet_Pt.eps");
    c1->SaveAs("JetEfficiencies.eps");
    h_temp->Clear();
    c1->Clear();

    h_temp = (TH1D*)f->Get("LEffEta");
    h_temp = HistoStyle(h_temp, 2, "", "|#eta^{l-jet}|", "#epsilon",0.0, 2.0, 0.0, 0.4);
    Draw(h_temp);
    c1->SaveAs("EffLJet_Eta.eps");
    c1->SaveAs("JetEfficiencies.eps)");
    h_temp->Clear();
    
    f->Close();
    c1->Close();
}


TH1D * HistoStyle(TH1D * histo, int color=1, TString title="", TString Xaxis="", TString Yaxis="",
                  double xmin=0, double xmax=0, double ymin=0, double ymax=0){
         
    histo->SetTitle(title);
    histo->GetXaxis()->SetTitle(Xaxis);
    histo->GetYaxis()->SetTitle(Yaxis);
    histo->GetYaxis()->SetTitleOffset(1.6);
    histo->SetFillColor(color);
    if(ymin!=0)histo->SetMinimum(ymin);
    if(ymax!=0)histo->SetMaximum(ymax);
    histo->GetXaxis()->SetRangeUser(xmin, xmax);
    
    return histo;
}

void Draw(TH1D *histo){
    
    histo->Draw("E3");
    histo->Draw("same");
}

void setHHStyle(TStyle& HHStyle)
{
  HHStyle.SetPalette(1);
    
  // ==============
  //  Canvas
  // ==============
        
  HHStyle.SetCanvasBorderMode(0);
  HHStyle.SetCanvasColor(kWhite);
  HHStyle.SetCanvasDefH(600); //Height of canvas
  HHStyle.SetCanvasDefW(600); //Width of canvas
  HHStyle.SetCanvasDefX(0);   //Position on screen
  HHStyle.SetCanvasDefY(0);
        
  // ==============
  //  Pad
  // ==============
        
  HHStyle.SetPadBorderMode(0);
  // HHStyle.SetPadBorderSize(Width_t size = 1);
  HHStyle.SetPadColor(kWhite);
  HHStyle.SetPadGridX(false);
  HHStyle.SetPadGridY(false);
  HHStyle.SetGridColor(0);
  HHStyle.SetGridStyle(3);
  HHStyle.SetGridWidth(1);
        
  // ==============
  //  Frame
  // ==============
        
  HHStyle.SetFrameBorderMode(0);
  HHStyle.SetFrameBorderSize(1);
  HHStyle.SetFrameFillColor(0);
  HHStyle.SetFrameFillStyle(0);
  HHStyle.SetFrameLineColor(1);
  HHStyle.SetFrameLineStyle(1);
  HHStyle.SetFrameLineWidth(1);

  // =====================
  //  Statistics Box
  // =====================
        
  HHStyle.SetOptFile(0);
  HHStyle.SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  HHStyle.SetStatColor(kWhite);
  //HHStyle.SetStatFont(fontstyle);
  HHStyle.SetStatFontSize(0.025);
  HHStyle.SetStatTextColor(1);
  HHStyle.SetStatFormat("6.4g");
  HHStyle.SetStatBorderSize(1);
  HHStyle.SetStatH(0.1);
  HHStyle.SetStatW(0.15);
        
  // ==============
  //  Margins
  // ==============

  HHStyle.SetPadTopMargin(0.1);
  HHStyle.SetPadBottomMargin(0.15);
  HHStyle.SetPadLeftMargin(0.20);
  HHStyle.SetPadRightMargin(0.05);
       
  // ==============
  //  Axis
  // ==============
        
  HHStyle.SetAxisColor(1, "XYZ");
  HHStyle.SetStripDecimals(kTRUE);
  HHStyle.SetTickLength(0.03, "XYZ");
  HHStyle.SetNdivisions(510, "XYZ");
  HHStyle.SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  HHStyle.SetPadTickY(1);

        
  // =====================
  //  Postscript options:
  // =====================
        
  HHStyle.SetPaperSize(20.,20.);

}