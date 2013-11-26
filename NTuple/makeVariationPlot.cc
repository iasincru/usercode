////////////////////////////////////////////////////////////
////
////   Execute this macro with the next sequence of commands
////
////    root -l
////    .L src/makeVariationPlot.cc++
////     makeVariationPlot("HypToppT")
////     makeVariationPlot("HypTopRapidity")
////     makeVariationPlot("HypTTBarMass")
////     makeVariationPlot("HypLeptonpT")
////     ...
////
////     Results are stored in the directory 'ComparisonPlots'
////
////
////////////////////////////////////////////////////////////





#include <TH1.h>
#include <TString.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>
#include <TMath.h>
#include <TStyle.h>
#include <TSystem.h>

#include "fstream"
#include "iostream"
#include "cstdio"


TH1* getHistoFromFile(TString filename, TString variable)
{
    TString histogram = TString(variable);
    TFile *f = TFile::Open(filename);
    if(!filename) {
        std::cout<<"File '"<<filename<<"' not valid"<<std::endl;
        return 0;
    };

    TH1* histo = (TH1*)f->Get(histogram);
    if(!histo){
        std::cout<<"Histogram '"<<histogram<<"' not valid"<<std::endl;
        return 0;
    };
    return histo;
}

TGraphAsymmErrors* getGraphFromFile(TString filename, TString variable)
{
    TString histogram = TString(variable);
    TFile *f = TFile::Open(filename);
    if(!filename) {
        std::cout<<"File '"<<filename<<"' not valid"<<std::endl;
        return 0;
    };
    TGraphAsymmErrors* gr = (TGraphAsymmErrors*)f->Get(histogram);
    if(!gr){
        std::cout<<"Histogram '"<<gr<<"' not valid"<<std::endl;
        return 0;
    };
    return gr;
}


TH1* divideVariations(TH1* h, TGraphAsymmErrors *gr0, TGraphAsymmErrors *gr1)
{
    for (Int_t iter = 0; iter<(Int_t)gr0->GetN(); iter++){
        double value = gr0->GetY()[iter] / gr1->GetY()[iter];
        double error = value * TMath::Sqrt((gr0->GetErrorY(iter) / gr0->GetY()[iter])*(gr0->GetErrorY(iter) / gr0->GetY()[iter]) + (gr1->GetErrorY(iter) / gr1->GetY()[iter])*(gr1->GetErrorY(iter) / gr1->GetY()[iter]) );
        h->SetBinContent(h->FindBin(gr0->GetX()[iter]), value);
        h->SetBinError(h->FindBin(gr0->GetX()[iter]), error);
    }
    return (TH1*)h->Clone("tmp");
}


void setHHStyle(TStyle& HHStyle)
{
    const int fontstyle=42;
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

    // ==============
    //  Margins
    // ==============
    HHStyle.SetPadTopMargin(0.1);
    HHStyle.SetPadBottomMargin(0.15);
    HHStyle.SetPadLeftMargin(0.20);
    HHStyle.SetPadRightMargin(0.05);

    // =====================
    //  Statistics Box
    // =====================
    HHStyle.SetOptFile(0);
    HHStyle.SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
    HHStyle.SetStatColor(kWhite);
    HHStyle.SetStatFont(fontstyle);
    HHStyle.SetStatFontSize(0.025);
    HHStyle.SetStatTextColor(1);
    HHStyle.SetStatFormat("6.4g");
    HHStyle.SetStatBorderSize(1);
    HHStyle.SetStatH(0.1);
    HHStyle.SetStatW(0.15);
}


void makeVariationPlot(TString variable)
{
    setHHStyle(*gStyle);

    const TString basedir[] = {"Plots_FullAnalysis/Nominal/", "Nominal_PU_LessEq5/Plots_PUleq5/Nominal/", "Nominal_PULessEq10/Plots_LowPU/Nominal/", "Nominal_PUMore10_LessEq16/Plots_MediumPU_SVD/Nominal/", 
                         "Nominal_PUMore16/Plots_HighPU_SVD/Nominal/", "Nominal_TightMuon_Selection/Plots_TightMuons/Nominal/", "Nominal_TightMuon_Selection/Plots_TightMuonsCSVT_FullSVD/Nominal/", 
                         "Nominal_2CSVLoose/Plots_2bTags/Nominal/", "Nominal_CSVT/Plots_CSVT/Nominal/"};
    const TString xTitles[] = {"Nominal", "PU #leq 5", "PU #leq 10", "10 #leq PU #leq 16", "PU #geq 16", "Tight #mu", "Tight #mu + CSVT", "2 CSVL", "1 CSVT"};

    const std::vector<TString>vec_baseDir (basedir, basedir + sizeof(basedir)/sizeof(basedir[0]));
    const std::vector<TString>vec_xTitles (xTitles, xTitles + sizeof(xTitles)/sizeof(xTitles[0]));

    std::vector<TH1*> vec_histo, tmp_vec_histo;
    std::vector<TGraphAsymmErrors*> vec_graphs;

    for(unsigned int iter= 0 ; iter<vec_baseDir.size(); iter++){
        TString dir = vec_baseDir.at(iter).Copy().Append("emu/DiffXS_").Append(variable).Append("_source.root");
        vec_graphs.push_back(getGraphFromFile(dir, "data_staterror_only"));
        vec_histo.push_back(getHistoFromFile(dir, "mc"));
    }
    for(unsigned int iter= 0; iter<vec_graphs.size(); iter++){
        TH1* h_tmp = divideVariations(vec_histo.at(0), vec_graphs.at(iter), vec_graphs.at(0));
        tmp_vec_histo.push_back(h_tmp);
    }
    vec_histo.clear();
    vec_histo = tmp_vec_histo;

    const unsigned int nrBins = vec_histo.at(0)->GetNbinsX();
    const int nRows = (nrBins %3 == 0 ) ? (nrBins/3) : (1+(int)nrBins/3);
    TString yTitle = TString("#frac{Var.}{Default}");
    TH1D *histo = 0;

    TCanvas *c = new TCanvas("c", "c", 0, 0, 900, 750);
    c->Divide(3,nRows, 0.01, 0.01, 0);
    for (unsigned int nbins = 1; nbins<=nrBins; nbins++){
        /// Need to conver int to TString for the title of the hsitogram
        char buffer[10];
        sprintf(buffer, "%d", nbins);

        histo = new TH1D("histo", "", vec_histo.size(), -0.5, -0.5+vec_histo.size());
        histo->SetTitle(variable+" bin "+buffer);
        for(unsigned int iter=0 ; iter<vec_histo.size(); iter++){
            histo->SetBinContent(iter+1, vec_histo.at(iter)->GetBinContent(nbins));
            histo->SetBinError(iter+1, vec_histo.at(iter)->GetBinError(nbins));
            histo->GetXaxis()->SetBinLabel(iter+1, vec_xTitles.at(iter));
        }
        c->cd(nbins);
        histo->Draw();
    }
    TString outdir = TString("ComparisonPlots/");
    gSystem->mkdir(outdir);
    c->Print(outdir.Copy()+variable+".eps");
    c->Print(outdir.Copy()+variable+".C");
}