#include<iostream>
#include<fstream>

void load_Analysis2(){

  
//       TFile *f1 = TFile::Open("mergedRoot/ee/ee_ttbarsignal.root");
//       TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
//       TTree *t1 = (TTree*)d1->Get("NTuple");
//       t1->Process("Analysis.C+");

//   
//       TFile *f1 = TFile::Open("mergedRoot/ee/ee_ttbarviatau.root");
//       TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
//       TTree *t1 = (TTree*)d1->Get("NTuple");
//       t1->Process("Analysis.C+");


      TFile *f1 = TFile::Open("mergedRoot/ee/ee_ttbarsignalplustau.root");
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis2.C+");

  
      TFile *f1 = TFile::Open("mergedRoot/emu/emu_ttbarsignalplustau.root");
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis2.C+");
    
      TFile *f1 = TFile::Open("mergedRoot/mumu/mumu_ttbarsignalplustau.root");
      TDirectory *d1 = (TDirectory*)f1->Get("NTupDir");
      TTree *t1 = (TTree*)d1->Get("NTuple");
      t1->Process("Analysis2.C+");

  
}
