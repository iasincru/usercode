#include "DrawComparison.h"


#include "TString.h"
#include "TH1.h"
#include "TMath.h"
#include "TFile.h"
#include "TLegend.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TAttLine.h"
#include "TAttFill.h"
#include "TAttMarker.h"
#include "TCanvas.h"
#include "TPad.h"


void DrawComparison::DrawAndSaveHisto()
{
    TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);

    TLegend *legend = MakeLegend(h1_, TString(h1_->GetTitle()), h2_, TString(h2_->GetTitle()), h3_, TString(h3_->GetTitle()));
    h1_->SetTitle("");
    h1_->DrawNormalized();
    h2_->DrawNormalized("same");
    if(h3_) h3_->DrawNormalized("same");
    legend->Draw("same");
    drawRatio(h1_, h2_, h3_, "", 0);
    c1->Print(outputdir_+"/"+h1_->GetName()+".eps");
    delete h1_;
    delete h2_;
    if(h3_) delete h3_;
    delete legend;
    delete c1;
}


void DrawComparison::SetPlotOptions(double ratioMin, double ratioMax, TString xlabel, TString ylabel)
{
    ratioMin_ = ratioMin;
    ratioMax_ = ratioMax;
    
    xlabel_ = xlabel;
    ylabel_ = ylabel;
    
}


void DrawComparison::SetHistoOptions(TH1* histo, TString nameForLegend, int color, int marker, double markersize)
{
    histo->SetTitle(nameForLegend);
    histo->SetMarkerStyle(marker);
    histo->SetMarkerColor(color);
    histo->SetLineColor(color);

    if(markersize != 0.0) histo->SetMarkerSize(markersize);
    if(xlabel_ != "") histo->GetXaxis()->SetTitle(xlabel_);
    if(ylabel_ != "") histo->GetYaxis()->SetTitle(ylabel_);

}


void DrawComparison::SetOutputDirectory(TString outputdir)
{
    if(outputdir == ""){
        std::cout<<"DrawComparison::SetOutputDirectory: The output directory must be provided"<<std::endl;
        std::cout<<"EXITING!!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    outputdir_ = outputdir;
    gSystem->mkdir(outputdir_, true);
}

void DrawComparison::SetFiles(TString filename1, TString filename2, TString filename3)
{
    f1_ = dynamic_cast<TFile*>(TFile::Open(filename1));
    f2_ = dynamic_cast<TFile*>(TFile::Open(filename2));
    if(filename3 != "") f3_ = dynamic_cast<TFile*>(TFile::Open(filename3));

    if(!f1_ || !f2_ || (filename3 != "" && !f3_) )
    {
        std::cout<<"DrawComparison::SetFiles:Some of the files cannot be opened"<<std::endl;
        std::cout<<"EXITING!!"<<std::endl;
        exit(EXIT_FAILURE);
    }

}

void DrawComparison::SetHistos(TString distribution)
{
    if (distribution == "")
    {
        std::cout<<"DrawComparison::SetHistos: No distribution provided, so I cannot make anything"<<std::endl;
        std::cout<<"EXITING!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    distribution_ = distribution;
    h1_ = dynamic_cast<TH1D*> (f1_->Get(distribution));
    h2_ = dynamic_cast<TH1D*> (f2_->Get(distribution));
    if(f3_) h3_ = dynamic_cast<TH1D*> (f3_->Get(distribution));

    if (h1_->GetNbinsX() != h2_->GetNbinsX() && (h3_ && h1_->GetNbinsX() != h3_->GetNbinsX())){
        std::cout<<"DrawComparison::SetHistos: The distributions have different binning"<<std::endl;
        std::cout<<"EXITING!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    if (distribution_.Contains("pT") && h1_->GetNbinsX()>200){
        h1_->Rebin(10);
        h2_->Rebin(10);
        if(h3_) h3_->Rebin(10);
    }

    DrawComparison::SetHistoOptions(h1_, "Nominal", kBlack, 8);
    DrawComparison::SetHistoOptions(h2_, "Up", kRed, 23);
    DrawComparison::SetHistoOptions(h3_, "Down", kBlue, 26);
}



TLegend* DrawComparison::MakeLegend(TH1* h1, TString name1, TH1* h2, TString name2, TH1* h3, TString name3)
{
    TLegend *leg { new TLegend(0.80,0.65,0.98,0.85) };

    leg->AddEntry(h1, name1, "pl");
    leg->AddEntry(h2, name2, "pl");
    if(h3 && name3 != "") leg->AddEntry(h3, name3, "pl");

    return leg;
}


void DrawComparison::SetRatioStyle (TH1 *ratio1, TH1* histDenominator)
{
    ratio1->SetStats(kFALSE);
    ratio1->SetTitle("");
    ratio1->SetMaximum(ratioMax_);
    ratio1->SetMinimum(ratioMin_);
    ratio1->SetLineWidth(2);
    // configure axis of ratio plot
    ratio1->GetXaxis()->SetTitleSize(h1_->GetXaxis()->GetTitleSize()*scaleFactor_*1.3);
    ratio1->GetXaxis()->SetTitleOffset(h1_->GetXaxis()->GetTitleOffset()*0.9);
    ratio1->GetXaxis()->SetLabelSize(h1_->GetXaxis()->GetLabelSize()*scaleFactor_*1.4);
    ratio1->GetXaxis()->SetTitle(h1_->GetXaxis()->GetTitle());
    ratio1->GetXaxis()->SetNdivisions(h1_->GetNdivisions());
    ratio1->GetYaxis()->CenterTitle();
    ratio1->GetYaxis()->SetTitle("#frac{Nominal}{Variation}");
    ratio1->GetYaxis()->SetTitleSize(h1_->GetYaxis()->GetTitleSize()*scaleFactor_);
    ratio1->GetYaxis()->SetTitleOffset(h1_->GetYaxis()->GetTitleOffset()/scaleFactor_);
    ratio1->GetYaxis()->SetLabelSize(h1_->GetYaxis()->GetLabelSize()*scaleFactor_);
    ratio1->GetYaxis()->SetLabelOffset(h1_->GetYaxis()->GetLabelOffset()*3.3);
    ratio1->GetYaxis()->SetTickLength(0.03);
    ratio1->GetYaxis()->SetNdivisions(505);
    ratio1->GetXaxis()->SetRange(h1_->GetXaxis()->GetFirst(), h1_->GetXaxis()->GetLast());
    ratio1->GetXaxis()->SetNoExponent(true);
    
    ratio1->SetLineColor(histDenominator->GetLineColor());
    ratio1->SetMarkerStyle(histDenominator->GetMarkerStyle());
    ratio1->SetMarkerSize(histDenominator->GetMarkerSize());
    ratio1->SetMarkerColor(histDenominator->GetMarkerColor());

}


TPad* DrawComparison::MakePad()
{
    TPad *rPad = new TPad("rPad","",0,0,1,ratioSize_+0.001);
    rPad->SetFillStyle(0);
    rPad->SetFillColor(0);
    rPad->SetBorderSize(0);
    rPad->SetBorderMode(0);
    rPad->Draw();
    rPad->cd();
    rPad->SetLogy(0);
    rPad->SetLogx(logx_);
    rPad->SetTicky(1);
    rPad->SetTopMargin(0.0);
    rPad->SetBottomMargin(0.15*scaleFactor_);
    rPad->SetRightMargin(right_);

    return rPad;
}



void DrawComparison::drawRatio(const TH1* histNumerator, TH1* histDenominator, TH1* histDenominator2, TString ratioDrawOption, bool drawError)
{

    // check that histos have the same binning
    if(histNumerator->GetNbinsX()!=histDenominator->GetNbinsX() || histNumerator->GetNbinsX()!=histDenominator2->GetNbinsX()){
        std::cout<<"DrawComparison::drawRatio: Histos have different number of bins. Fix this." << std::endl;
        std::cout<<"EXITING!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    // create ratio
    TH1D* ratio1 = dynamic_cast<TH1D*> (histNumerator->Clone());
    ratio1->Divide(histDenominator);
    TH1D* ratio2 =0;
    if(histDenominator2)
    {
        ratio2 = dynamic_cast<TH1D*> (histNumerator->Clone());
        ratio2->Divide(histDenominator2);
    }
    
    
        for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
            if (drawError){
                ratio1->SetBinError(bin, TMath::Sqrt(histNumerator->GetBinContent(bin))/histDenominator->GetBinContent(bin));
                if(histDenominator2) ratio2->SetBinError(bin, TMath::Sqrt(histNumerator->GetBinContent(bin))/histDenominator2->GetBinContent(bin));
            } else {
                ratio1->SetBinError(bin, 0);
                if(histDenominator2) ratio2->SetBinError(bin, 0);
            }
        }

    myStyle  = gStyle;
    
    logx_  = myStyle->GetOptLogx();
    left_  = myStyle->GetPadLeftMargin();
    right_ = myStyle->GetPadRightMargin();
    
    // y:x size ratio for canvas
    canvAsym_ = 4./3.;
    // ratio size of pad with plot and pad with ratio
    ratioSize_ = 0.36;
    // change old pad
    gPad->SetBottomMargin(ratioSize_);
    gPad->SetRightMargin(right_);
    gPad->SetLeftMargin(left_);
    gPad->SetBorderMode(0);
    gPad->SetBorderSize(0);
    gPad->SetFillColor(10);
    // create new pad for ratio plot
    TPad *rPad = MakePad();

    scaleFactor_ = 1./(canvAsym_*ratioSize_);
    SetRatioStyle(ratio1, histDenominator);
    SetRatioStyle(ratio2, histDenominator2);
    // delete axis of initial plot

    // draw ratio plot

    ratio1->DrawClone(ratioDrawOption);
    if (ratioDrawOption == "p e X0")
    {
        ratio1->DrawClone(ratioDrawOption);
        ratio2->DrawClone(ratioDrawOption+"same");
    }
    else {
        ratio1->DrawClone("][, P");
        ratio2->DrawClone("][, P, same");
    }
    
    rPad->SetTopMargin(0.0);
    rPad->SetBottomMargin(0.15*scaleFactor_);
    rPad->SetRightMargin(right_);
    gPad->SetLeftMargin(left_);
    gPad->RedrawAxis();
    // draw grid
    rPad->SetGrid(1,1);
/*
    // draw a horizontal lines on a given histogram
    // a) at 1
    Double_t xmin = ratio1->GetXaxis()->GetXmin();
    Double_t xmax = ratio1->GetXaxis()->GetXmax();
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
*/
}


