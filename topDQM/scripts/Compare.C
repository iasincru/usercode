#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TAttLine.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TString.h>


void Compare(){
  std::cout<<"****************************************************************"<<std::endl;
  std::cout<<"**** Great that you choose this macro to Compare Top DQM histograms."<<std::endl;
  std::cout<<"**** Do you know which Modules are you running? And how many steps do they have?"<<std::endl;
  std::cout<<"**** If you get any error, could be because you are trying to load an UNEXISTING module or STEP directory."<<std::endl;
  std::cout<<"**** Otherwise something more delicated is going on. In this case contact ivan.asin.cruz@desy.de"<<std::endl;
  std::cout<<"**** Particle (case sensitive):"<<std::endl;
  std::cout<<"****    --> SingleMuon, SingleElectron:"<<std::endl;
  std::cout<<"****         -> WP:   Loose, Medium"<<std::endl;
  std::cout<<"****         -> Step: step0, step1, step2, step3, step4, step5"<<std::endl;
  std::cout<<"****    --> DiMuon, DiElectron, ElecMu"<<std::endl;
  std::cout<<"****         -> WP:   ''"<<std::endl;
  std::cout<<"****         -> Step: step0, step1, step2 (only ElecMu)"<<std::endl;
  std::cout<<"****************************************************************"<<std::endl;
  
  TString particle, WP, step, outname, f1_name, f2_name;
  TString leg1="" , leg2="";
  TFile *f1, *f2;
  double Lumi1, Lumi2;

  f1 = TFile::Open("week23/DQM_V0001_R000000001__TopVal__195017-195396__DoubleElectron_Run2012B-PromptReco-v1_week23.root"); leg1.Append("195017-195396");   Lumi1 = 1.0;
  f2 = TFile::Open("week23/DQM_V0001_R000000001__TopVal__195397-195870__DoubleElectron_Run2012B-PromptReco-v1_DCSONLY_week23.root"); leg2.Append("195397-195870");   Lumi2 = 1.0;
  particle.Clear();     particle.Append("DiElectron");
  WP.Clear();           WP.Append("");
  step.Clear();         step.Append("step0");

  f1_name = f1->GetName(); f1_name.Remove(6);
  f2_name = f2->GetName(); f2_name.Remove(6);

  outname.Clear();      outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname, leg1, leg2, Lumi1, Lumi2);

  
  f1->Close();
  f2->Close();
  
  /*
  TString leg1, leg2, leg3, leg4, leg5, leg6;
  TString directory="DQMData/Run\ 1/Physics/Run\ summary/Top/TopSingleMuonMediumDQM/step5";
  TString particle;
  
  TFile *f1 = TFile::Open("week15/DQM_V0001_R000000001__TopVal__190456-190688__SingleMu_Run2012A-PromptReco-v1_week15.root");
  leg1.Clear(); leg1.Append("Week15: 190456-190688");
  TFile *f2 = TFile::Open("week16/DQM_V0001_R000000001__TopVal__190689-191276__SingleMu_Run2012A-PromptReco-v1_week16.root");
  leg2.Clear(); leg2.Append("Week16: 190689-191276");
  TFile *f3 = TFile::Open("week17/DQM_V0001_R000000001__TopVal__191277-191859__SingleMu_Run2012A-PromptReco-v1_week17.root");
  leg3.Clear(); leg3.Append("Week17: 191277-191859");
  TFile *f4 = TFile::Open("week19/DQM_V0001_R000000001__TopVal__191860-193557__SingleMu_Run2012A-PromptReco-v1_week19.root");
  leg4.Clear(); leg4.Append("Week19: 191860-193557");
  TFile *f5 = TFile::Open("week20/DQM_V0001_R000000001__TopVal__193358-194076__SingleMu_Run2012AB-PromptReco-v1_week20.root");
  leg5.Clear(); leg5.Append("Week20: 193358-194076");
  TFile *f6 = TFile::Open("week21/DQM_V0001_R000000001__TopVal__194077-194479__SingleMu__Run2012B-PromptReco-v1_week21.root");
  leg6.Clear(); leg6.Append("Week21: 194077-194479");
  particle.Clear();       particle.Append("SingleMuon");
  
  CompareAllWeeks(f1, f2, f3, f4, f5, f6, "PvMult", directory, leg1, leg2, leg3, leg4, leg5, leg6);
  */
  
}


void Compare2Files(TFile* f1, TFile* f2, TString particle, TString WP="", TString step, TString output, TString leg1, TString leg2, double Lumi1=1.0, double Lumi2=1.0){

  TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/Top";

  if(particle.Contains("SingleElectron") != 1 && particle.Contains("SingleMuon") != 1 && particle.Contains("DiMuon") != 1 && particle.Contains("DiElectron") != 1 && particle.Contains("ElecMu") != 1){
    std::cout<<"WARNING: You use NON valid 'Particle'. Choose between: SingleElectron, SingleMuon, SingleLepton, DiMuon, DiElectron or ElecMu"<<std::endl;
    return;
  }
  
  if(particle.Contains("Single") == 1 && (WP.Contains("Loose") != 1 && WP.Contains("Medium") != 1) ){
    std::cout<<"WARNING: You use NON valid 'Working Point'."<<std::endl;
    std::cout<<"Choose between: Loose, Medium for SingleElectron/SingleMuon"<<std::endl;
    std::cout<<"or '' for DiMuon/DiElectron/ElecMu"<<std::endl;
    return;
  }
  
  if (step.Contains("step0") != 1 && step.Contains("step1") != 0 && step.Contains("step2") != 0 && step.Contains("step3") != 0 && step.Contains("step4") != 0){
    std::cout<<"WARNING: You use NON valid selection 'Step'. Choose between: Step0, Step1, Step2, Step3, Step4"<<std::endl;
    return;
  }
  
  dirstr.Append(particle).Append(WP).Append("DQM/").Append(step);
  
  if (particle.Contains("Single") == 1){
    
    Plot1D(f1, f2, "ElecCalIso",        output.Copy().Append("("), dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "ElecEta",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "ElecMult",          output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "ElecMultIso",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "ElecPt",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "ElecRelIso",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "ElecTrkIso",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
//     Plot1D(f1, f2, "InstLumi",          output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet1Eta",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet1Pt",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet1PtRaw",         output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet2Eta",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet2Pt",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet2PtRaw",         output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet3Eta",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet3Pt",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet3PtRaw",         output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet4Eta",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet4Pt",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "Jet4PtRaw",         output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "JetDiscCSV",        output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
    Plot1D(f1, f2, "JetBDiscEff",       output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
    Plot1D(f1, f2, "JetBDiscPur",       output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
    Plot1D(f1, f2, "JetBDiscVtx",       output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
    Plot1D(f1, f2, "JetMult",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "JetMultCSV",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "JetMultBEff",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "JetMultBPur",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "JetMultBVtx",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "METCalo",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "METPflow",          output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "METTC",             output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MassBTop",          output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MassTop",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MassW",             output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonCalIso",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonDelZ",          output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonEta",           output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonMult",          output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonMultIso",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonPt",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonRelIso",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "MuonTrkIso",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "PvMult",            output, dirstr, leg1, leg2, Lumi1, Lumi2);
    Plot1D(f1, f2, "RunNumber",         output.Copy().Append(")"), dirstr, leg1, leg2, Lumi1, Lumi2, 0, 1);
  }
  else if( particle.Contains("Di") || particle.Contains("ElecMu")){
    if (f1->GetName() == f2->GetName()){
        Plot1D(f1, "DEtaJet1Jet2",  output.Copy().Append("("), dirstr, leg1);
        Plot1D(f1, "DEtaJet1Lep1",  output, dirstr, leg1);
        Plot1D(f1, "DEtaJet1MET",   output, dirstr, leg1);
        Plot1D(f1, "DEtaL1L2",      output, dirstr, leg1);
        Plot1D(f1, "DEtaLep1MET",   output, dirstr, leg1);
        Plot1D(f1, "DPhiJet1Jet2",  output, dirstr, leg1);
        Plot1D(f1, "DPhiJet1Lep1",  output, dirstr, leg1);
        Plot1D(f1, "DPhiJet1MET",   output, dirstr, leg1);
        Plot1D(f1, "DPhiL1L2",      output, dirstr, leg1);
        Plot1D(f1, "DPhiLep1MET",   output, dirstr, leg1);
        Plot1D(f1, "DecayChannel",  output, dirstr, leg1);
        Plot1D(f1, "DiElecLogger",  output, dirstr, leg1);
        Plot1D(f1, "DiMuonEff",     output, dirstr, leg1);
        Plot1D(f1, "DiMuonLogger",  output, dirstr, leg1);
        Plot1D(f1, "DiMuonMon",     output, dirstr, leg1);
        Plot1D(f1, "ElecCalIso",    output, dirstr, leg1);
        Plot1D(f1, "ElecMuEff",     output, dirstr, leg1);
        Plot1D(f1, "ElecMuLogger",  output, dirstr, leg1);
        Plot1D(f1, "ElecMuMon",     output, dirstr, leg1);
        Plot1D(f1, "ElecMultIso",   output, dirstr, leg1);
        Plot1D(f1, "ElecMultIso",   output, dirstr, leg1);
        Plot1D(f1, "ElecPt",        output, dirstr, leg1);
        Plot1D(f1, "ElecRelIso",    output, dirstr, leg1);
        Plot1D(f1, "ElecTrkIso",    output, dirstr, leg1);
        Plot1D(f1, "InvMass",       output, dirstr, leg1);
        Plot1D(f1, "InvMassLog",    output, dirstr, leg1);
        Plot1D(f1, "InvMassLogWC",  output, dirstr, leg1);
        Plot1D(f1, "InvMassWC",     output, dirstr, leg1);
        Plot1D(f1, "Jet1Eta",       output, dirstr, leg1);
        Plot1D(f1, "Jet1Pt",        output, dirstr, leg1);
        Plot1D(f1, "Jet1PtRaw",     output, dirstr, leg1);
        Plot1D(f1, "Jet2Eta",       output, dirstr, leg1);
        Plot1D(f1, "Jet2Pt",        output, dirstr, leg1);
        Plot1D(f1, "Jet2PtRaw",     output, dirstr, leg1);
        Plot1D(f1, "JetMult",       output, dirstr, leg1);
        Plot1D(f1, "Lep1Pt",        output, dirstr, leg1);
        Plot1D(f1, "Lep2Pt",        output, dirstr, leg1);
        Plot1D(f1, "LepMultIso",    output, dirstr, leg1);
        Plot1D(f1, "METCalo",       output, dirstr, leg1);
        Plot1D(f1, "METPflow",      output, dirstr, leg1);
        Plot1D(f1, "METTC",         output, dirstr, leg1);
        Plot1D(f1, "MuonCalIso",    output, dirstr, leg1);
        Plot1D(f1, "MuonDelZ",      output, dirstr, leg1);
        Plot1D(f1, "MuonDelXY",     output, dirstr, leg1);
        Plot1D(f1, "MuonMultIso",   output, dirstr, leg1);
        Plot1D(f1, "MuonPt",        output, dirstr, leg1);
        Plot1D(f1, "MuonRelIso",    output, dirstr, leg1);
        Plot1D(f1, "MuonTrkIso",    output, dirstr, leg1);
        Plot1D(f1, "SumEtaL1L2",    output.Copy().Append(")"), dirstr, leg1);
    }
    else if (f1->GetName() != f2->GetName()){
        Plot1D(f1, f2, "DEtaJet1Jet2",  output.Copy().Append("("), dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DEtaJet1Lep1",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DEtaJet1MET",   output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DEtaL1L2",      output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DEtaLep1MET",   output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DPhiJet1Jet2",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DPhiJet1Lep1",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DPhiJet1MET",   output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DPhiL1L2",      output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DPhiLep1MET",   output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "DecayChannel",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "DiElecLogger",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "DiMuonEff",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "DiMuonLogger",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "DiMuonMon",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "ElecCalIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "ElecMuEff",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "ElecMuLogger",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "ElecMuMon",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "ElecMultIso",   output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "ElecPt",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "ElecRelIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "ElecTrkIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "InvMass",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "InvMass",       output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
        Plot1D(f1, f2, "InvMassLog",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "InvMassLog",    output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
        Plot1D(f1, f2, "InvMassLogWC",  output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "InvMassLogWC",  output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
        Plot1D(f1, f2, "InvMassWC",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "InvMassWC",     output, dirstr, leg1, leg2, Lumi1, Lumi2, 1);
        Plot1D(f1, f2, "Jet1Eta",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Jet1Pt",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Jet1PtRaw",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Jet2Eta",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Jet2Pt",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Jet2PtRaw",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "JetMult",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Lep1Pt",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "Lep2Pt",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "LepMultIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "METCalo",       output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "METPflow",      output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "METTC",         output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "MuonCalIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "MuonDelZ",      output, dirstr, leg1, leg2, Lumi1, Lumi2);
//         Plot1D(f1, f2, "MuonDelXY",     output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "MuonMultIso",   output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "MuonPt",        output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "MuonRelIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "MuonTrkIso",    output, dirstr, leg1, leg2, Lumi1, Lumi2);
        Plot1D(f1, f2, "SumEtaL1L2",    output.Copy().Append(")"), dirstr, leg1, leg2, Lumi1, Lumi2);
    }
  }
  
}



//Plot out all the histograms in a ROOT file
void Plot1D(TFile *f1, TString hist, TString filename, TString dirstr, TString leg){
  
  TDirectoryFile *dir1 = (TFile*) f1->Get(dirstr);
  TH1* h1 = (TH1*)dir1->Get(hist); h1->Sumw2();
  
  h1->SetLineColor(kBlue);
  h1->SetLineWidth(2);
  
  TCanvas *c1 = new TCanvas();
  h1->Draw();
  gPad->Update();
  TPaveStats* sb1=(TPaveStats*)(h1->FindObject("stats"));
  sb1->SetX1NDC(0.825);
  sb1->SetX2NDC(0.975);
  sb1->SetY1NDC(0.825);
  sb1->SetY2NDC(0.975);
  sb1->SetTextColor(h1->GetLineColor());
 // gPad->Modified();
  
  TString h1_legend=""; h1_legend.Append(leg);
  TLegend *l = new TLegend();
  l->SetFillStyle(0);   l->SetBorderSize(0);
  l->SetX1NDC(0.05);    l->SetX2NDC(0.25);
  l->SetY1NDC(0.91);    l->SetY2NDC(0.99);
  l->AddEntry(h1, h1_legend, "lp");
  
  h1->Draw("h");
  l->Draw("same");

  TString singlename="";
  if (dirstr.Contains("Electron") == 1){
    singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(16, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
  }
  else if (dirstr.Contains("Muon") == 1 || dirstr.Contains("ElecMu")){
    singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(12, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
  }
  c1->Print(singlename);
  c1->Print(filename);

}




//Function to compare 2 files' histograms and plot also the Ratio plot
void Plot1D(TFile *f1, TFile *f2, TString hist, TString filetype, TString dirstr, TString leg1, TString leg2, double Lumi1=1.0, double Lumi2=1.0, int LogY=0, int LogX=0){
  
  TDirectoryFile *dir1 = (TFile*) f1->Get(dirstr);
  TDirectoryFile *dir2 = (TFile*) f2->Get(dirstr);
  
  if (!dir1->GetKey(hist))      {std::cout<<"The histogram "<<hist<<" is not contained in "<<f1->GetName()<<std::endl;continue;}
  
  TString outfilename = "Compare2Files";
  
  TH1* h1 = (TH1*)dir1->Get(hist); h1->Sumw2();
  TH1* h2 = (TH1*)dir2->Get(hist); h2->Sumw2();

  if ( (Lumi1 != 1.0 || Lumi2 != 1.0) && (Lumi1>0. && Lumi2>0.)){
    h1->Scale(1.0);
    h2->Scale(Lumi1/Lumi2);
}
  else{
    double h1_scale = h1->Integral();       h1->Scale(1./h1_scale);
    double h2_scale = h2->Integral();       h2->Scale(1./h2_scale);
  }

  h1->SetLineWidth(2.0);        h1->SetLineColor(kBlue);
  h2->SetLineWidth(2.0);        h2->SetLineColor(kRed);

  TString h1_legend=""; h1_legend.Append(leg1);
  TString h2_legend=""; h2_legend.Append(leg2);
  
  TCanvas *c1 = new TCanvas();
  
  if(LogY == 1){c1->SetLogy(1);}
  else {c1->SetLogy(0);}
  
  if(LogX == 1){c1->SetLogx(1);}
  else {c1->SetLogx(0);}
  
  h1->Draw();
  gStyle->SetOptStat("nemr");  //gStyle->SetOptStat("nemri");
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
  
  double h1_max = h1->GetMaximum();
  double h2_max = h2->GetMaximum();

  if (h1_max >= h2_max){
    h1->SetMaximum(h1_max*1.3);
  }
  else{
    h1->SetMaximum(h2_max*1.3);
  }

  h1->Draw("h");
  h2->Draw("h, same");

  TLegend *l = new TLegend();
  l->SetFillStyle(0);   l->SetBorderSize(0);
  l->SetX1NDC(0.05);    l->SetX2NDC(0.25);
  l->SetY1NDC(0.91);    l->SetY2NDC(0.99);

  l->AddEntry(h1, h1_legend, "lp");
  l->AddEntry(h2, h2_legend, "lp");
  
  l->Draw("same");
  
  drawRatio(h1, h2, 0.5, 1.5, *gStyle);

  //New naming for the single plot files: Quite hardcoded.
  //A new naming convention should be found (take into account the directory structure for the GUI).
  TString singlename="";
  if (dirstr.Contains("SingleElectron") == 1 ){
    if (dirstr.Contains("Medium") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(26, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
    else if(dirstr.Contains("Loose") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(25, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
  }
  else if (dirstr.Contains("SingleMuon") == 1 ){
    if (dirstr.Contains("Medium") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(22, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
    else if(dirstr.Contains("Loose") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(21, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
  }
  else if (dirstr.Contains("Di") == 1 || dirstr.Contains("ElecMu") == 1){
    if (dirstr.Contains("Electron") == 1){
        singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(16, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
    else if (dirstr.Contains("Muon") == 1 || dirstr.Contains("ElecMu")){
        singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(12, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
}
  
  c1->Print(singlename);
  c1->Print(outfilename.Append(filetype));
  
}


//Function to compare 2 files' histograms and plot also the Ratio plot
void CompareAllWeeks(TFile *f1, TFile *f2, TFile *f3, TFile *f4, TFile *f5, TFile *f6, TString hist, TString dirstr, TString leg1, TString leg2, TString leg3, TString leg4, TString leg5, TString leg6, int LogY=0, int LogX=0){
  
  TDirectoryFile *dir1 = (TFile*) f1->Get(dirstr);
  TDirectoryFile *dir2 = (TFile*) f2->Get(dirstr);
  TDirectoryFile *dir3 = (TFile*) f3->Get(dirstr);
  TDirectoryFile *dir4 = (TFile*) f4->Get(dirstr);
  TDirectoryFile *dir5 = (TFile*) f5->Get(dirstr);
  TDirectoryFile *dir6 = (TFile*) f6->Get(dirstr);
  
  TString outfilename = "Compare2Files";
  
  TH1* h1 = (TH1*)dir1->Get(hist);
  TH1* h2 = (TH1*)dir2->Get(hist);
  TH1* h3 = (TH1*)dir3->Get(hist);
  TH1* h4 = (TH1*)dir4->Get(hist);
  TH1* h5 = (TH1*)dir5->Get(hist);
  TH1* h6 = (TH1*)dir6->Get(hist);
  
  h1->SetLineColor(kBlue);
  h2->SetLineColor(kRed);
  h3->SetLineColor(kBlack);
  h4->SetLineColor(kGreen);
  h5->SetLineColor(kCyan);
  h6->SetLineColor(kMagenta);
  /*
  h1->Sumw2();
  h2->Sumw2();
  h3->Sumw2();
  h4-Sumw2();
  */

  TString h1_legend=""; h1_legend.Append(leg1);
  TString h2_legend=""; h2_legend.Append(leg2);
  TString h3_legend=""; h3_legend.Append(leg3);
  TString h4_legend=""; h4_legend.Append(leg4);
  TString h5_legend=""; h5_legend.Append(leg5);
  TString h6_legend=""; h6_legend.Append(leg6);
  
  double h1_scale = h1->Integral();
  double h2_scale = h2->Integral();
  double h3_scale = h3->Integral();
  double h4_scale = h4->Integral();
  double h5_scale = h5->Integral();
  double h6_scale = h6->Integral();
  
  h1->Scale(1./h1_scale);
  h2->Scale(1./h2_scale);
  h3->Scale(1./h3_scale);
  h4->Scale(1./h4_scale);
  h5->Scale(1./h5_scale);
  h6->Scale(1./h6_scale);
  
  TCanvas *c1 = new TCanvas();
  
  if(LogY == 1){c1->SetLogy(1);}
  else {c1->SetLogy(0);}
  
  /*
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
  
  h3->Draw();
  gPad->Update();
  TPaveStats* sb3=(TPaveStats*)(h3->FindObject("stats"));
  sb3->SetX1NDC(0.825);
  sb3->SetX2NDC(0.975);
  sb3->SetY1NDC(0.725);
  sb3->SetY2NDC(0.575);
  sb3->SetTextColor(h3->GetLineColor());
  gPad->Modified();
  
  h4->Draw();
  gPad->Update();
  TPaveStats* sb4=(TPaveStats*)(h4->FindObject("stats"));
  sb4->SetX1NDC(0.825);
  sb4->SetX2NDC(0.975);
  sb4->SetY1NDC(0.675);
  sb4->SetY2NDC(0.525);
  sb4->SetTextColor(h4->GetLineColor());
  gPad->Modified();
  */
  
  h1->SetMaximum(h1->GetMaximum() * 1.25);
  h1->SetStats(0);
  h1->Draw("h");
  h2->Draw("h, same");
  h3->Draw("h, same");
  h4->Draw("h, same");
  h5->Draw("h, same");
  h6->Draw("h, same");
  
  TLegend *l = new TLegend(0.1,0.7,0.48,0.9);
  /*
  l->SetFillStyle(0);
  l->SetBorderSize(0);
  l->SetX1NDC(0.05);
  l->SetX2NDC(0.25);
  l->SetY1NDC(0.91);
  l->SetY2NDC(0.99);
*/
/*  l->SetX1NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-1.0);
  l->SetY1NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength()-0.15);
  l->SetX2NDC(1.0-gStyle->GetPadRightMargin()-gStyle->GetTickLength()-0.5);
  l->SetY2NDC(1.0-gStyle->GetPadTopMargin()-gStyle->GetTickLength());
*/
  l->AddEntry(h1, h1_legend, "lp");
  l->AddEntry(h2, h2_legend, "lp");
  l->AddEntry(h3, h3_legend, "lp");
  l->AddEntry(h4, h4_legend, "lp");
  l->AddEntry(h5, h5_legend, "lp");
  l->AddEntry(h6, h6_legend, "lp");  
  
  l->Draw("same");
  /*
  //New naming for the single plot files
  TString singlename="";
  if (dirstr.Contains("Electron") == 1 ){
    if (dirstr.Contains("Medium") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(26, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
    else if(dirstr.Contains("Loose") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(25, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
  }
  else if (dirstr.Contains("Muon") == 1 ){
    if (dirstr.Contains("Medium") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(22, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
    else if(dirstr.Contains("Loose") == 1){
      singlename.Append(dirstr); singlename.Remove(0, 38);singlename.Replace(21, 1, "_");singlename.Append(hist).Append(".pdf");//.png");
    }
  }
  
  c1->Print(singlename);
  c1->Print(outfilename.Append(filetype));
  */
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
/*
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
  */
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
  ratio->SetFillColor(kBlack);
  //ratio->SetLineColor(kBlack);
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
  ratio->SetMarkerSize(0.5);
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
