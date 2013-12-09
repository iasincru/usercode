//////////////////////////////////////////////////////////////////
////
////     root -l -b -q macros/compareTrees.cc++
////
//////////////////////////////////////////////////////////////////

#include <TFile.h>
#include <TLegend.h>
#include <TH1.h>
#include <TTree.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "iostream"

void compareTrees(){

    TFile *_file0 = TFile::Open("/data/group/top/DiffXS/2013_11_04_TAG_N002_45M/ttbarsignalplustau.root");
    TFile *_file1 = TFile::Open("/data/group/top/DiffXS/2013_11_04_TAG_N002_MadSpin_FullStats62M/ttbarsignalplustau.root");

    TTree *tree0 = (TTree*)_file0->Get("writeNTuple/NTuple");
    TTree *tree1 = (TTree*)_file1->Get("writeNTuple/NTuple");

    gStyle->SetOptStat(0);

    TH1D* h0 = new TH1D("h0", "h0", 60, -0.5, 59.5);   h0->SetLineColor(kRed);
    TH1D* h1 = new TH1D("h1", "h1", 60, -0.5, 59.5);   h1->SetLineColor(kBlue);

    TCanvas *c1 = new TCanvas();
    tree0->Draw("@allGenJets.size()>>h0", "", "norm");
    tree1->Draw("@allGenJets.size()>>h1", "", "norm,same");

    h0->Scale(1./h0->Integral());
    h1->Scale(1./h1->Integral());
    TLegend *leg = new TLegend(0.75, 0.75, 0.9, 0.9);
    leg->AddEntry(h0, "Madgraph", "l");
    leg->AddEntry(h1, "MadSpin", "l");

    h0->Draw();
    h1->Draw("same");
    leg->Draw("same");

    c1->Print("compareTree.eps");

}
