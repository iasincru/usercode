#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cmath>

#include <TString.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <TPad.h>
#include <TStyle.h>
#include <TAttFill.h>
#include <TAttLine.h>
#include <TAttMarker.h>
#include <TLegend.h>

using namespace std;

void drawRatio(const TH1* histNumerator, const TH1* histDenominator1, const TH1* histDenominator2,
               const Double_t ratioMin, const Double_t ratioMax, 
               const TStyle& myStyle = *gStyle)
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
    if(histNumerator->GetNbinsX()!=histDenominator1->GetNbinsX() ||
       histNumerator->GetNbinsX()!=histDenominator2->GetNbinsX()){
        std::cout << "error when calling drawRatio - histos have different number of bins" << std::endl;
        return;
    }

    // create ratio
    TH1* ratio1 = (TH1*)histNumerator->Clone();
    TH1* ratio2 = (TH1*)histNumerator->Clone();
    
    ratio1->Divide(histDenominator1);
    ratio1->SetLineStyle(histDenominator1->GetLineStyle());
    ratio1->SetLineColor(histDenominator1->GetLineColor());
    ratio1->SetMarkerStyle(histDenominator1->GetMarkerStyle());
    ratio1->SetMarkerColor(histDenominator1->GetMarkerColor());
    
    ratio2->Divide(histDenominator2);
    ratio2->SetLineStyle(histDenominator2->GetLineStyle());
    ratio2->SetLineColor(histDenominator2->GetLineColor());
    ratio2->SetMarkerStyle(histDenominator2->GetMarkerStyle());
    ratio2->SetMarkerColor(histDenominator2->GetMarkerColor());
    
    // calculate error for ratio
    // b) default: only gaussian error of histNumerator
    for(int bin=1; bin<=histNumerator->GetNbinsX(); bin++){
        ratio1->SetBinError(bin, sqrt(histNumerator->GetBinContent(bin))/histDenominator1->GetBinContent(bin));
        ratio2->SetBinError(bin, sqrt(histNumerator->GetBinContent(bin))/histDenominator2->GetBinContent(bin));
    }

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
    rPad->SetFillStyle(0);
    rPad->SetFillColor(0);
    rPad->SetBorderSize(0);
    rPad->SetBorderMode(0);
    rPad->Draw();
    rPad->cd();
    rPad->SetLogy(0);
    rPad->SetLogx(logx);
    rPad->SetTicky(1);
    // configure ratio plot
    double scaleFactor = 1./(canvAsym*ratioSize);
    ratio1->SetStats(kFALSE);
    ratio1->SetTitle("");
    ratio1->SetMaximum(ratioMax);
    ratio1->SetMinimum(ratioMin);
    ratio1->SetLineWidth(1);
    // configure axis of ratio1 plot
    ratio1->GetXaxis()->SetTitleSize(histNumerator->GetXaxis()->GetTitleSize()*scaleFactor*1.3);
    ratio1->GetXaxis()->SetTitleOffset(histNumerator->GetXaxis()->GetTitleOffset()*0.9);
    ratio1->GetXaxis()->SetLabelSize(histNumerator->GetXaxis()->GetLabelSize()*scaleFactor*1.4);
    ratio1->GetXaxis()->SetTitle(histNumerator->GetXaxis()->GetTitle());
    ratio1->GetXaxis()->SetNdivisions(histNumerator->GetNdivisions());
    ratio1->GetYaxis()->CenterTitle();
    ratio1->GetYaxis()->SetTitle("#frac{Nominal}{Variations}");
    ratio1->GetYaxis()->SetTitleSize(histNumerator->GetYaxis()->GetTitleSize()*scaleFactor);
    ratio1->GetYaxis()->SetTitleOffset(histNumerator->GetYaxis()->GetTitleOffset()/scaleFactor);
    ratio1->GetYaxis()->SetLabelSize(histNumerator->GetYaxis()->GetLabelSize()*scaleFactor);
    ratio1->GetYaxis()->SetLabelOffset(histNumerator->GetYaxis()->GetLabelOffset()*3.3);
    ratio1->GetYaxis()->SetTickLength(0.03);
    ratio1->GetYaxis()->SetNdivisions(505);
    ratio1->GetXaxis()->SetRange(histNumerator->GetXaxis()->GetFirst(), histNumerator->GetXaxis()->GetLast());

    // delete axis of initial plot
    histNumerator->GetXaxis()->SetLabelSize(0);
    histNumerator->GetXaxis()->SetTitleSize(0);
    // draw ratio plot
    ratio1->DrawClone("p");
    ratio2->DrawClone("p same");
    
    rPad->SetTopMargin(0.0);
    rPad->SetBottomMargin(0.15*scaleFactor);
    rPad->SetRightMargin(right);
    gPad->SetLeftMargin(left);
    gPad->RedrawAxis();
    
    rPad->SetGrid(1,1);
}

void DrawDecayChLabel ( TString decaychannel ) {

    TPaveText *decch = new TPaveText();

    decch->AddText(decaychannel.Append(" channel"));

    decch->SetX1NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength() + 0.55 );
    decch->SetY1NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() + 0.05 );
    decch->SetX2NDC(      gStyle->GetPadLeftMargin() + gStyle->GetTickLength() + 0.75 );
    decch->SetY2NDC(1.0 - gStyle->GetPadTopMargin()  - gStyle->GetTickLength() + 0.10 );

    decch->SetFillStyle(0);
    decch->SetBorderSize(0);
    decch->SetTextAlign(12);
    decch->Draw("same");
}

void estractor ( TString channel ) {
    
    TString filename = "selectionRoot/BTagEff/Nominal/";
    filename.Append(channel.Copy()).Append("/").Append(channel.Copy()).Append("_ttbarsignalplustau.root");

    TFile *f = TFile::Open(filename);
    
    if (!f || f->IsZombie()) {
        std::cout<<"Not valid filename"<<std::endl;
        exit(9);
    }

    TH2D *BiDEff;
    TH1D *UniDEff;
    TCanvas *c1 = new TCanvas();
    gStyle->SetOptStat(0);
    
    TString histotitle = "-jet Efficiency";
    TString xtitle = "p_{T} [GeV/c]";
    TString ytitle = "|#eta|";
    
    BiDEff = dynamic_cast<TH2D*>(f->Get("BEffPerJet"));
    BiDEff->SetTitle("b-jet Efficiency");
    BiDEff->GetXaxis()->SetTitle(xtitle);
    BiDEff->GetYaxis()->SetTitle(ytitle);
    BiDEff->Draw("COLZ");
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("BEff.eps"));
    BiDEff->Clear();

    BiDEff= dynamic_cast<TH2D*> (f->Get("CEffPerJet"));
    BiDEff->SetTitle("c-jet Efficiency");
    BiDEff->Draw("COLZ");
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("CEff.eps"));
    BiDEff->Clear();

    BiDEff= dynamic_cast<TH2D*> ( f->Get("LEffPerJet"));
    BiDEff->SetTitle("l-jet Efficiency");
    BiDEff->Draw("COLZ");
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("LEff.eps"));
    BiDEff->Clear();
    
    
    UniDEff = dynamic_cast<TH1D*> ( f->Get("BEffPt"));
    UniDEff->GetYaxis()->SetTitle("#epsilon");
    UniDEff->GetXaxis()->SetTitle(xtitle);
    UniDEff->Draw();
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("BJet_PtEff.eps"));
    UniDEff->Clear();
    
    UniDEff = dynamic_cast<TH1D*> ( f->Get("CEffPt"));
    UniDEff->GetYaxis()->SetTitle("#epsilon");
    UniDEff->GetXaxis()->SetTitle(xtitle);
    UniDEff->Draw();
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("CJet_PtEff.eps"));
    
    
    UniDEff = dynamic_cast<TH1D*> ( f->Get("LEffPt"));
    UniDEff->GetYaxis()->SetTitle("#epsilon");
    UniDEff->GetXaxis()->SetTitle(xtitle);
    UniDEff->Draw();
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("LJet_PtEff.eps"));
    
    
    UniDEff = dynamic_cast<TH1D*> ( f->Get("BEffEta"));
    UniDEff->GetYaxis()->SetTitle("#epsilon");
    UniDEff->GetXaxis()->SetTitle(ytitle);
    UniDEff->Draw();
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("BJet_EtaEff.eps"));
    UniDEff->Clear();
    
    UniDEff = dynamic_cast<TH1D*> ( f->Get("CEffEta"));
    UniDEff->GetYaxis()->SetTitle("#epsilon");
    UniDEff->GetXaxis()->SetTitle(ytitle);
    UniDEff->Draw();
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("CJet_EtaEff.eps"));
    
    
    UniDEff = dynamic_cast<TH1D*> ( f->Get("LEffEta"));
    UniDEff->GetYaxis()->SetTitle("#epsilon");
    UniDEff->GetXaxis()->SetTitle(ytitle);
    UniDEff->Draw();
    DrawDecayChLabel(channel);
    c1->Print(channel.Copy().Append("LJet_EtaEff.eps"));
    
    c1->Clear();
    delete c1;
}



void CompareVariation (TString NominalPath, TString UpPath, TString DownPath, TString histoName){

    if (NominalPath == "" || UpPath == "" || DownPath == "" || histoName == ""){
        std::cout<<"No filenames of histogram provided. Exiting"<<std::endl;
        exit(8);
    }

    TFile *f_central = TFile::Open(NominalPath);
    TFile *f_up      = TFile::Open(UpPath);
    TFile *f_down    = TFile::Open(DownPath);

    TH1D *h_Nominal = dynamic_cast<TH1D*> (f_central->Get(histoName));
    TH1D *h_Up      = dynamic_cast<TH1D*> (f_up->Get(histoName));
    TH1D *h_Down    = dynamic_cast<TH1D*> (f_down->Get(histoName));

    if (!h_Nominal || !h_Up || !h_Down){
        cout<<"Missing histogram"<<endl;
        exit(88);
    }

    h_Nominal->SetLineColor(kBlack);  h_Nominal->SetLineStyle(1); h_Nominal->SetMarkerStyle(12); h_Nominal->SetMarkerSize(1.2); h_Nominal->SetMarkerColor(kBlack);
    h_Up->SetLineColor(kRed);         h_Up->SetLineStyle(3);      h_Up->SetMarkerStyle(23);      h_Up->SetMarkerSize(1.2);      h_Up->SetMarkerColor(kRed);
    h_Down->SetLineColor(kBlue);      h_Down->SetLineStyle(7);    h_Down->SetMarkerStyle(22);    h_Down->SetMarkerSize(1.2);    h_Down->SetMarkerColor(kBlue);

    
    gStyle->SetOptStat(0);
    
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9, "");
    leg->AddEntry(h_Nominal, "Nominal", "lp");
    leg->AddEntry(h_Up, "Var. Up", "pl");
    leg->AddEntry(h_Down, "Var. Down", "lp");
    
//     h_Nominal->Rebin(10);
//     h_Up->Rebin(10);
//     h_Down->Rebin(10);

    TCanvas *c1 = new TCanvas();
    h_Nominal->Draw("hist");
    h_Up->Draw("hist same");
    h_Down->Draw("hist same");
    leg->Draw("same");
    drawRatio(h_Nominal, h_Up, h_Down, 0.95, 1.05);

    c1->Print(histoName.Copy().Append("Comparison.eps"));
    c1->Clear();
    delete c1;
}


int main (){

    //compilable via g++:
    //  g++ EffEstractor.C -o bJetEffEstractor `root-config --cflags --glibs`
    
//     TString channel = "emu";
//     estractor(channel);
//     channel = "ee";
//     estractor(channel);
//     channel = "mumu";
//     estractor(channel);
    
    
    
    TString fileNominal = "selectionRoot/Nominal/emu/emu_ttbarsignalplustau.root";
    TString fileUp      = "selectionRoot/LEPT_UP/emu/emu_ttbarsignalplustau.root";
    TString fileDown    = "selectionRoot/LEPT_DOWN/emu/emu_ttbarsignalplustau.root";
//     TString fileUp      = "selectionRoot/BTAG_UP/emu/emu_ttbarsignalplustau.root";
//     TString fileDown    = "selectionRoot/BTAG_DOWN/emu/emu_ttbarsignalplustau.root";
    CompareVariation(fileNominal, fileUp, fileDown, "HypjetMultiXSec");
    CompareVariation(fileNominal, fileUp, fileDown, "HypBJetpT");
    CompareVariation(fileNominal, fileUp, fileDown, "HypBJetEta");
    

    return 1;
    
}