#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>
#include <TAttLine.h>


void Compare(){
  cout<<"****************************************************************"<<endl;
  cout<<"**** Great that you choose this macro to Compare Top DQM histograms."<<endl;
  cout<<"**** Do you know which Modules are you running? And how many steps do they have?"<<endl;
  cout<<"**** If you get any error, could be because you are trying to load an UNEXISTING module or STEP directory."<<endl;
  cout<<"**** Otherwise something more delicated is going on. In this case contact ivan.asin.cruz@desy.de"<<endl;
  cout<<"****************************************************************"<<endl;
  
  TString particle, WP, step, outname, f1_name, f2_name;
  
  TFile *f1, *f2;
  
  /*
  //*********     Plotting out all the Histograms from a file **********************
  f1 = TFile::Open("DQM_V0001_R000000001__TopVal__CMSSW_5_2_1__GEN-SIM-RECO.root");
  
  
  
  f1_name = f1->GetName();
  int size = f1_name.Sizeof();
  f1_name.Remove(size-6, 5);//Remove .root extension
  f1_name.Remove(0, 22); //Remove DQM_V0001_R000000001__ extension
  
  //******** DiLetponDQM/step0 *******
  particle.Append("DiLepton");
  WP.Append("Medium");
  step.Append("step0");
  outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** DiLetponDQM/step1 *******
  step.Clear();		step.Append("step1");
  outname.Clear();	outname	= f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** SingleMuonLooseDQM/step0 *******
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Medium");
  step.Clear();		step.Append("step0");
  outname.Clear();	outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** SingleMuonLooseDQM/step1 *******
  step.Clear();		step.Append("step1");
  outname.Clear();	outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** SingleMuonLooseDQM/step2 *******
  step.Clear();		step.Append("step2");
  outname.Clear();	outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** SingleMuonLooseDQM/step2 *******
  step.Clear();		step.Append("step2");
  outname.Clear();	outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** SingleMuonLooseDQM/step3 *******
  step.Clear();		step.Append("step3");
  outname.Clear();	outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  //******** SingleMuonLooseDQM/step4 *******
  step.Clear();		step.Append("step4");
  outname.Clear();	outname = f1_name.Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Plot1File(f1, particle, WP, step, outname);
  
  
  */
  // ********************** Compare the histograms from 2 different files ***************************************

  
  
  f1 = TFile::Open("Week15/DQM_V0001_R000000001__TopVal__190456-190688__SingleMu_Run2012A-PromptReco-v1_week15.root");
  f2 = TFile::Open("Week16/DQM_V0001_R000000001__TopVal__190689-191276__SingleMu_Run2012A-PromptReco-v1_week16.root");
  
  
  
  
  f1_name = f1->GetName();
  int size = f1_name.Sizeof();
  f1_name.Remove(6);
/*  
  f1_name.Remove(size-6, 5); //Remove .root extension
  f1_name.Remove(0, 22); //Remove DQM_V0001_R000000001__ extension
  */
  f2_name = f2->GetName();
  int size = f2_name.Sizeof();
  f2_name.Remove(6);
/*  
  f2_name.Remove(size-6, 5); //Remove .root extension
  f2_name.Remove(0, 22); //Remove DQM_V0001_R000000001__ extension
  */

  //********  SingleMuonLooseDQM/step0 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Loose");
  step.Clear();		step.Append("step0");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

  //********  SingleMuonLooseDQM/step1 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Loose");
  step.Clear();		step.Append("step1");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

  //********  SingleMuonLooseDQM/step2 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Loose");
  step.Clear();		step.Append("step2");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

    //********  SingleMuonLooseDQM/step3 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Loose");
  step.Clear();		step.Append("step3");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

  //********  SingleMuonMediumDQM/step0 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Medium");
  step.Clear();		step.Append("step0");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

  //********  SingleMuonMediumDQM/step1 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Medium");
  step.Clear();		step.Append("step1");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

  //********  SingleMuonMediumDQM/step2 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Medium");
  step.Clear();		step.Append("step2");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);

    //********  SingleMuonMediumDQM/step3 ***************
  particle.Clear();	particle.Append("SingleMuon");
  WP.Clear();		WP.Append("Medium");
  step.Clear();		step.Append("step3");
  outname.Clear();	outname = f1_name.Copy().Append("---VS---").Append(f2_name).Copy().Append("__").Append(particle).Append(WP).Append("__").Append(step).Append(".pdf");
  Compare2Files(f1, f2, particle, WP, step, outname);



  
}

void Plot1File(TFile* f1, TString particle, TString WP, TString step, TString output){

  TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/Top";

  if(particle.Contains("SingleElectron") != 1 && particle.Contains("SingleMuon") != 1 && particle.Contains("DiLepton") != 1){
    cout<<"WARNING: You use NON valid 'Particle'. Choose between: SingleElectron, SingleMuon, SingleLepton, DiLepton"<<endl;
    return;
  }
  
  if(WP.Contains("Loose") != 1 && WP.Contains("Medium") != 1 ){
    cout<<"WARNING: You use NON valid 'Working Point'. Choose between: Loose, Medium"<<endl;
    return;
  }
  
  if (step.Contains("step0") != 1 && step.Contains("step1") != 0 && step.Contains("step2") != 0 && step.Contains("step3") != 0 && step.Contains("step4") != 0){
    cout<<"WARNING: You use NON valid selection 'Step'. Choose between: Step0, Step1, Step2, Step3, Step4"<<endl;
    return;
  }
  if (particle.Contains("DiLepton") == 1){
    dirstr.Append(particle).Append("DQM/").Append(step);
  }
  else {
    dirstr.Append(particle).Append(WP).Append("DQM/").Append(step);
  }
  
  if (particle.Contains("Single") == 1){
    
    Plot1D(f1, "ElecCalIso", output.Copy().Append("("), dirstr);
    Plot1D(f1, "ElecEta", output, dirstr);
    Plot1D(f1, "ElecMult", output, dirstr);
    Plot1D(f1, "ElecMultIso", output, dirstr);
    Plot1D(f1, "ElecPt", output, dirstr);
    Plot1D(f1, "ElecRelIso", output, dirstr);
    Plot1D(f1, "ElecTrkIso", output, dirstr);
    Plot1D(f1, "Jet1Pt", output, dirstr);
    Plot1D(f1, "Jet1PtRaw", output, dirstr);
    Plot1D(f1, "Jet2Pt", output, dirstr);
    Plot1D(f1, "Jet2PtRaw", output, dirstr);
    Plot1D(f1, "Jet3Pt", output, dirstr);
    Plot1D(f1, "Jet3PtRaw", output, dirstr);
    Plot1D(f1, "Jet4Pt", output, dirstr);
    Plot1D(f1, "Jet4PtRaw", output, dirstr);
    Plot1D(f1, "JetBDiscEff", output, dirstr);
    Plot1D(f1, "JetBDiscPur", output, dirstr);
    Plot1D(f1, "JetBDiscVtx", output, dirstr);
    Plot1D(f1, "JetMult", output, dirstr);
    Plot1D(f1, "JetMultBEff", output, dirstr);
    Plot1D(f1, "JetMultBPur", output, dirstr);
    Plot1D(f1, "JetMultBVtx", output, dirstr);
    Plot1D(f1, "METCalo", output, dirstr);
    Plot1D(f1, "METPflow", output, dirstr);
    Plot1D(f1, "METTC", output, dirstr);
    Plot1D(f1, "MassTop", output, dirstr);
    Plot1D(f1, "MassW", output, dirstr);
    Plot1D(f1, "MuonCalIso", output, dirstr);
    Plot1D(f1, "MuonDelZ", output, dirstr);
    Plot1D(f1, "MuonEta", output, dirstr);
    Plot1D(f1, "MuonMult", output, dirstr);
    Plot1D(f1, "MuonMultIso", output, dirstr);
    Plot1D(f1, "MuonPt", output, dirstr);
    Plot1D(f1, "MuonRelIso", output, dirstr);
    Plot1D(f1, "MuonTrkIso", output, dirstr);
    Plot1D(f1, "PvMult", output, dirstr);
    Plot1D(f1, "TriggerEff", output, dirstr);
    //Plot1D(f1, "TriggerMon", output, dirstr);
    Plot1D(f1, "TriggerMon", output.Copy().Append(")"), dirstr);
  }
  else if( particle.Contains("DiLepton")){
    
    Plot1D(f1, "DEtaJet1Jet2", output.Copy().Append("("), dirstr);
    Plot1D(f1, "DEtaJet1Lep1", output, dirstr);
    Plot1D(f1, "DEtaJet1MET", output, dirstr);
    Plot1D(f1, "DEtaL1L2", output, dirstr);
    Plot1D(f1, "DEtaLep1MET", output, dirstr);
    Plot1D(f1, "DPhiJet1Jet2", output, dirstr);
    Plot1D(f1, "DPhiJet1Lep1", output, dirstr);
    Plot1D(f1, "DPhiJet1MET", output, dirstr);
    Plot1D(f1, "DPhiL1L2", output, dirstr);
    Plot1D(f1, "DPhiLep1MET", output, dirstr);
    Plot1D(f1, "DecayChannel", output, dirstr);
    Plot1D(f1, "DiElecLogger", output, dirstr);
    Plot1D(f1, "DiMuonEff", output, dirstr);
    Plot1D(f1, "DiMuonLogger", output, dirstr);
    Plot1D(f1, "DiMuonMon", output, dirstr);
    Plot1D(f1, "ElecCalIso", output, dirstr);
    Plot1D(f1, "ElecMuEff", output, dirstr);
    Plot1D(f1, "ElecMuLogger", output, dirstr);
    Plot1D(f1, "ElecMuMon", output, dirstr);
    Plot1D(f1, "ElecMultIso", output, dirstr);
    Plot1D(f1, "ElecMultIso", output, dirstr);
    Plot1D(f1, "ElecPt", output, dirstr);
    Plot1D(f1, "ElecRelIso", output, dirstr);
    Plot1D(f1, "ElecTrkIso", output, dirstr);
    Plot1D(f1, "InvMass", output, dirstr);
    Plot1D(f1, "InvMassLog", output, dirstr);
    Plot1D(f1, "InvMassLogWC", output, dirstr);
    Plot1D(f1, "InvMassWC", output, dirstr);
    Plot1D(f1, "Jet1Eta", output, dirstr);
    Plot1D(f1, "Jet1Pt", output, dirstr);
    Plot1D(f1, "Jet1PtRaw", output, dirstr);
    Plot1D(f1, "Jet2Eta", output, dirstr);
    Plot1D(f1, "Jet2Pt", output, dirstr);
    Plot1D(f1, "Jet2PtRaw", output, dirstr);
    Plot1D(f1, "JetMult", output, dirstr);
    Plot1D(f1, "Lep1Pt", output, dirstr);
    Plot1D(f1, "Lep2Pt", output, dirstr);
    Plot1D(f1, "LepMultIso", output, dirstr);
    Plot1D(f1, "METCalo", output, dirstr);
    Plot1D(f1, "METPflow", output, dirstr);
    Plot1D(f1, "METTC", output, dirstr);
    Plot1D(f1, "MuonCalIso", output, dirstr);
    Plot1D(f1, "MuonDelZ", output, dirstr);
    Plot1D(f1, "MuonDelXY", output, dirstr);
    Plot1D(f1, "MuonMultIso", output, dirstr);
    Plot1D(f1, "MuonPt", output, dirstr);
    Plot1D(f1, "MuonRelIso", output, dirstr);
    Plot1D(f1, "MuonTrkIso", output, dirstr);
    Plot1D(f1, "SumEtaL1L2", output.Copy().Append(")"), dirstr);
  }

  
  
}


void Compare2Files(TFile* f1, TFile* f2, TString particle, TString WP, TString step, TString output){

  TString dirstr = "DQMData/Run\ 1/Physics/Run\ summary/Top/Top";

  if(particle.Contains("SingleElectron") != 1 && particle.Contains("SingleMuon") != 1 && particle.Contains("DiLepton") != 1){
    cout<<"WARNING: You use NON valid 'Particle'. Choose between: SingleElectron, SingleMuon, SingleLepton, DiLepton"<<endl;
    return;
  }
  
  if(WP.Contains("Loose") != 1 && WP.Contains("Medium") != 1 ){
    cout<<"WARNING: You use NON valid 'Working Point'. Choose between: Loose, Medium"<<endl;
    return;
  }
  
  if (step.Contains("step0") != 1 && step.Contains("step1") != 0 && step.Contains("step2") != 0 && step.Contains("step3") != 0 && step.Contains("step4") != 0){
    cout<<"WARNING: You use NON valid selection 'Step'. Choose between: Step0, Step1, Step2, Step3, Step4"<<endl;
    return;
  }
  if (particle.Contains("DiLepton") == 1){
    dirstr.Append(particle).Append("DQM/").Append(step);
  }
  else {
    dirstr.Append(particle).Append(WP).Append("DQM/").Append(step);
  }
  
  if (particle.Contains("Single") == 1){
    
    Plot1D(f1, f2, "ElecCalIso", output.Copy().Append("("), dirstr);
    Plot1D(f1, f2, "ElecEta", output, dirstr);
    Plot1D(f1, f2, "ElecMult", output, dirstr);
    Plot1D(f1, f2, "ElecMultIso", output, dirstr);
    Plot1D(f1, f2, "ElecPt", output, dirstr);
    Plot1D(f1, f2, "ElecRelIso", output, dirstr);
    Plot1D(f1, f2, "ElecTrkIso", output, dirstr);
    Plot1D(f1, f2, "Jet1Pt", output, dirstr);
    Plot1D(f1, f2, "Jet1PtRaw", output, dirstr);
    Plot1D(f1, f2, "Jet2Pt", output, dirstr);
    Plot1D(f1, f2, "Jet2PtRaw", output, dirstr);
    Plot1D(f1, f2, "Jet3Pt", output, dirstr);
    Plot1D(f1, f2, "Jet3PtRaw", output, dirstr);
    Plot1D(f1, f2, "Jet4Pt", output, dirstr);
    Plot1D(f1, f2, "Jet4PtRaw", output, dirstr);
    Plot1D(f1, f2, "JetBDiscEff", output, dirstr);
    Plot1D(f1, f2, "JetBDiscPur", output, dirstr);
    Plot1D(f1, f2, "JetBDiscVtx", output, dirstr);
    Plot1D(f1, f2, "JetMult", output, dirstr);
    Plot1D(f1, f2, "JetMultBEff", output, dirstr);
    Plot1D(f1, f2, "JetMultBPur", output, dirstr);
    Plot1D(f1, f2, "JetMultBVtx", output, dirstr);
    Plot1D(f1, f2, "METCalo", output, dirstr);
    Plot1D(f1, f2, "METPflow", output, dirstr);
    Plot1D(f1, f2, "METTC", output, dirstr);
    Plot1D(f1, f2, "MassTop", output, dirstr);
    Plot1D(f1, f2, "MassW", output, dirstr);
    Plot1D(f1, f2, "MuonCalIso", output, dirstr);
    Plot1D(f1, f2, "MuonDelZ", output, dirstr);
    Plot1D(f1, f2, "MuonEta", output, dirstr);
    Plot1D(f1, f2, "MuonMult", output, dirstr);
    Plot1D(f1, f2, "MuonMultIso", output, dirstr);
    Plot1D(f1, f2, "MuonPt", output, dirstr);
    Plot1D(f1, f2, "MuonRelIso", output, dirstr);
    Plot1D(f1, f2, "MuonTrkIso", output, dirstr);
    Plot1D(f1, f2, "PvMult", output, dirstr);
    Plot1D(f1, f2, "TriggerEff", output, dirstr);
    //Plot1D(f1, f2, "TriggerMon", output, dirstr);
    Plot1D(f1, f2, "TriggerMon", output.Copy().Append(")"), dirstr);
  }
  else if( particle.Contains("DiLepton")){
    
    Plot1D(f1, "DEtaJet1Jet2", output.Copy().Append("("), dirstr);
    Plot1D(f1, "DEtaJet1Lep1", output, dirstr);
    Plot1D(f1, "DEtaJet1MET", output, dirstr);
    Plot1D(f1, "DEtaL1L2", output, dirstr);
    Plot1D(f1, "DEtaLep1MET", output, dirstr);
    Plot1D(f1, "DPhiJet1Jet2", output, dirstr);
    Plot1D(f1, "DPhiJet1Lep1", output, dirstr);
    Plot1D(f1, "DPhiJet1MET", output, dirstr);
    Plot1D(f1, "DPhiL1L2", output, dirstr);
    Plot1D(f1, "DPhiLep1MET", output, dirstr);
    Plot1D(f1, "DecayChannel", output, dirstr);
    Plot1D(f1, "DiElecLogger", output, dirstr);
    Plot1D(f1, "DiMuonEff", output, dirstr);
    Plot1D(f1, "DiMuonLogger", output, dirstr);
    Plot1D(f1, "DiMuonMon", output, dirstr);
    Plot1D(f1, "ElecCalIso", output, dirstr);
    Plot1D(f1, "ElecMuEff", output, dirstr);
    Plot1D(f1, "ElecMuLogger", output, dirstr);
    Plot1D(f1, "ElecMuMon", output, dirstr);
    Plot1D(f1, "ElecMultIso", output, dirstr);
    Plot1D(f1, "ElecMultIso", output, dirstr);
    Plot1D(f1, "ElecPt", output, dirstr);
    Plot1D(f1, "ElecRelIso", output, dirstr);
    Plot1D(f1, "ElecTrkIso", output, dirstr);
    Plot1D(f1, "InvMass", output, dirstr);
    Plot1D(f1, "InvMassLog", output, dirstr);
    Plot1D(f1, "InvMassLogWC", output, dirstr);
    Plot1D(f1, "InvMassWC", output, dirstr);
    Plot1D(f1, "Jet1Eta", output, dirstr);
    Plot1D(f1, "Jet1Pt", output, dirstr);
    Plot1D(f1, "Jet1PtRaw", output, dirstr);
    Plot1D(f1, "Jet2Eta", output, dirstr);
    Plot1D(f1, "Jet2Pt", output, dirstr);
    Plot1D(f1, "Jet2PtRaw", output, dirstr);
    Plot1D(f1, "JetMult", output, dirstr);
    Plot1D(f1, "Lep1Pt", output, dirstr);
    Plot1D(f1, "Lep2Pt", output, dirstr);
    Plot1D(f1, "LepMultIso", output, dirstr);
    Plot1D(f1, "METCalo", output, dirstr);
    Plot1D(f1, "METPflow", output, dirstr);
    Plot1D(f1, "METTC", output, dirstr);
    Plot1D(f1, "MuonCalIso", output, dirstr);
    Plot1D(f1, "MuonDelZ", output, dirstr);
    Plot1D(f1, "MuonDelXY", output, dirstr);
    Plot1D(f1, "MuonMultIso", output, dirstr);
    Plot1D(f1, "MuonPt", output, dirstr);
    Plot1D(f1, "MuonRelIso", output, dirstr);
    Plot1D(f1, "MuonTrkIso", output, dirstr);
    Plot1D(f1, "SumEtaL1L2", output.Copy().Append(")"), dirstr);
  }

  
  
}



//Plot out all the histograms in a ROOT file
void Plot1D(TFile *f1, TString hist, TString filename, TString dirstr){
  
  TDirectoryFile *dir1 = (TFile*) f1->Get(dirstr);
  
  TH1* h1 = (TH1*)dir1->Get(hist);
  
  h1->SetLineColor(kBlue);
  h1->SetLineWidth(1);
  //h1->SetMarkerStyle(20);
  
//  TString h1_legend = f1->GetName(); h1_legend.Remove(7);
  
  double scaleh1 = h1->Integral();
  
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
  
  h1->Draw();
  
  /*
  TLegend *l = new TLegend();
//  l->SetFillStyle(0);
  l->SetBorderSize(1);
  l->SetX1NDC(0.15);
  l->SetY1NDC(0.91);

  l->AddEntry(h1, h1_legend, "lp");
  
  l->Draw("same");
  */
  c1->Print(filename);
  
}




//Function to compare 2 files' histograms and plot also the Ratio plot
void Plot1D(TFile *f1, TFile *f2, TString hist, TString filetype, TString dirstr){
  
  TDirectoryFile *dir1 = (TFile*) f1->Get(dirstr);
  TDirectoryFile *dir2 = (TFile*) f2->Get(dirstr);
  
  
  TString outfilename = "Compare2Files";
  
  TH1* h1 = (TH1*)dir1->Get(hist);
  TH1* h2 = (TH1*)dir2->Get(hist);
  
  h1->SetLineColor(kBlue);
  h1->SetLineWidth(2);
  //h1->SetMarkerStyle(20);
  
  h2->SetLineColor(kRed);
  h2->SetLineWidth(1);
  
  TString h1_legend = f1->GetName(); h1_legend.Remove(6);
  TString h2_legend = f2->GetName(); h2_legend.Remove(6);

  double h1_scale = h1->Integral();
  double h2_scale = h2->Integral();
  
  h1->Scale(1./h1_scale);
  h2->Scale(1./h2_scale);
  
  double h1_max = h1->GetMaximum();
  double h2_max = h2->GetMaximum();    
  
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


  h2->Draw();
  gPad->Update();
  TPaveStats* sb2=(TPaveStats*)(h2->FindObject("stats"));
  sb2->SetX1NDC(0.825);
  sb2->SetX2NDC(0.975);
  sb2->SetY1NDC(0.775);
  sb2->SetY2NDC(0.625);
  sb2->SetTextColor(h2->GetLineColor());
  gPad->Modified();
  

  if (h1_max >= h2_max){
    h1->Draw();
    h2->Draw("same");
  }
  else{
    h2->Draw();
    h1->Draw("same");
  
  }
  
  
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
