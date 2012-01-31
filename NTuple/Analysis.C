#define Analysis_cxx

#include "Analysis.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include "TLorentzVector.h"
#include <fstream>
#include <iostream>
#include <TMath.h>
#include <TSystem.h>
#include "MatchingFunctions.h"



TString algo = TString("TCHEL");
//TString algo = TString("TCHEM");
//TString algo = TString("TCHET");
//TString algo = TString("SSVHEM");
//TString algo = TString("SSVHET");



void Analysis::Begin(TTree * /*tree*/)
{

  TString option = GetOption();
  //  totalEventCount=0;

  

  ///init counters
  //  ifstream insample("samples.txt",std::ios::in);
  //insample>>sample;

  //TString dataset="mumu";

  
  /*   AllDIM.setDataSet(dataset);
       AllDIM.setOptions("AllDIM","AllDIM","Events",50,0,400,1);
       InDIM.setDataSet(dataset);
       InDIM.setOptions("InDIM","InDIM","Events",50,0,400,1);
       OutDIM.setDataSet(dataset);
       OutDIM.setOptions("OutDIM","OutDIM","Events",50,0,400,1);
  */
  gStyle->SetOptStat(0);

  h_jetMultiAll = new TH1D("jetMultiAll", "Jet Multiplicity (AllJets)", 10, 0, 10);
  h_jetMultiXSec = new TH1D("jetMultiXSec", "Jet Multiplicity (for cross-section)", 10, 0, 10);
  h_jetMulti = new TH1D("jetMulti", "Jet Multiplicity", 10, 0, 10);
  h_jetMultiNoPU = new TH1D("jetMultiNoPU", "Jet Multiplicity (No Pileup or lumi weight)", 10, 0, 10);
  h_jetMultiVisTop = new TH1D("jetMultiVisTop", "Jet Multiplicity for Visible Top (No Pileup or lumi Weight)", 10, 0, 10);
  h_BjetMulti = new TH1D("BjetMulti", "B-Jet Multiplicity", 10, 0, 10);

  h_HypTTBarRapidity = new TH1D("HypTTBarRapidity","Rapidity of TTbar System (HYP)",50,-5,5);
  h_HypTTBarpT = new TH1D("HypTTBarpT","pT of TTbar System (HYP)",50,0,500);
  h_HypTTBarMass = new TH1D("HypTTBarMass","Mass of TTbar System (HYP)",100,0,2000);
  h_HypLLBarMass = new TH1D("HypLLBarMass","Mass of LLbar System (HYP)",100,0,2000);
  h_HypLLBarpT = new TH1D("HypLLBarpT","pT of LLbar System (HYP)",100,0,2000);

  h_GenTTBarMass = new TH1D("GenTTBarMass","Mass of TTbar System(GEN)",240,0,1200);
  h_GenTTBarRapidity = new TH1D("GenTTBarRapidity","Rapidity of TTbar System(GEN)",50,-5,5);
  h_GenTTBarpT = new TH1D("GenTTBarpT","pT of TTbar System(GEN)",240,0,1200);
  h_GenLLBarpT = new TH1D("GenLLBarpT","pT of LLbar System(GEN)",240,0,1200);
  h_GenLLBarMass = new TH1D("GenLLBarMass","Mass of LLbar System(GEN)",240,0,1200);

  h_VisGenTTBarMass = new TH1D("VisGenTTBarMass","Mass of TTbar System(VisGEN)",240,0,1200);
  h_VisGenTTBarRapidity = new TH1D("VisGenTTBarRapidity","Rapidity of TTbar System(VisGEN)",50,-5,5);
  h_VisGenTTBarpT = new TH1D("VisGenTTBarpT","pT of TTbar System(VisGEN)",240,0,1200);
  h_VisGenTopRapidity = new TH1D("VisGenTopRapidity","Rapidity of Top(VisGEN)",50,-5,5);
  h_VisGenAntiTopRapidity = new TH1D("VisGenAntiTopRapidity","Rapidity of AntiTop(VisGEN)",50,-5,5);

  h_VisGenLLBarpT = new TH1D("VisGenLLBarpT","Rapidity of LLbar System(VisGEN)",50,-5,5);
  h_VisGenLLBarMass = new TH1D("VisGenLLBarMass","Mass of LLbar System(VisGEN)",240,0,1200);

  h_RecoTTBarMass = new TH1D("RecoTTBarMass","Mass of TTbar System (HYP)",240,0,1200);
  h_RecoTTBarRapidity = new TH1D("RecoTTBarRapidity","Rapidity of TTbar System (HYP)",50,-5,5);
  h_RecoTTBarpT = new TH1D("RecoTTBarpT","pT of TTbar System (HYP)",240,0,1200);
  h_RecoToppT = new TH1D("RecoToppT","pT of Top (HYP)",240,0,1200);
  h_RecoAntiToppT = new TH1D("RecoAntiToppT","pT of AntiTop (HYP)",240,0,1200);
  h_RecoTopRapidity = new TH1D("RecoTopRapidity","Rapidity of Top (HYP)",50,-5,5);
  h_RecoAntiTopRapidity = new TH1D("RecoAntiTopRapidity","Rapidity of AntiTop (HYP)",50,-5,5);

  h_RecoLLBarMass = new TH1D("RecoLLBarMass","Mass of LLbar System (HYP)",240,0,1200);
  h_RecoLLBarpT = new TH1D("RecoLLBarpT","pT of LLbar System (HYP)",240,0,1200);
  h_RecoLeptonpT = new TH1D("RecoLeptonpT","pT of Lepton (HYP)",240,0,1200);
  h_RecoAntiLeptonpT = new TH1D("RecoAntiLeptonpT","pT of AntiLepton (HYP)",240,0,1200);
  h_RecoLeptonEta = new TH1D("RecoLeptonEta","Eta of Lepton (HYP)",240,0,1200);
  h_RecoAntiLeptonEta = new TH1D("RecoAntiLeptonEta","Eta of AntiLepton (HYP)",240,0,1200);

  h_VisGenAll = new TH1D("VisGenAll","All Visible Generated particles (IM)",40,0,400);
  h_GenAll = new TH1D("GenAll","AllGenerated particles (IM)",40,0,400);
  Allh1 = new TH1D("Allh1","DiLepton Mass",40,0,400);
  h_diLepMassFull = new TH1D("DIMFull","DiLepton Mass (Full Range)",100,0,300);
  Looseh1 = new TH1D("Looseh1","DiLepton Mass",40,0,400);
  Zh1 = new TH1D("Zh1","DiLepton Mass in Z Window",40,0,400);
  TTh1 = new TH1D("TTh1","DiLepton Mass out of Z Window",40,0,400);

  h_vertMulti = new TH1D("vertMulti", "Primary Vertex Multiplicity", 30, 0, 30);
  h_MET = new TH1D("MET", "Missing Transverse Energy", 40, 0, 400);
  h_jetpT = new TH1D("jetpT", "jet pT", 40, 0, 400);  
  h_jetHT = new TH1D("jetHT", "jet HT", 40, 0, 1000);  

  h_MuonpT = new TH1D("MuonpT","Muon pT (emu channel)",40,0,400);
  h_MuonEta = new TH1D("MuonEta","Muon Eta (emu channel)",40,-4,4);
  h_ElectronpT = new TH1D("ElectronpT","Electron pT (emu channel)",40,0,400);
  h_ElectronEta = new TH1D("ElectronEta","Electron Eta (emu channel)",40,-4,4);

  h_LeptonpT = new TH1D("LeptonpT","Lepton pT",40,0,400);
  h_LeptonEta = new TH1D("LeptonEta","Lepton Eta",40,-4,4);
  h_LeptonE = new TH1D("LeptonE","Lepton Energy",40,0,400);

  h_AntiLeptonpT = new TH1D("AntiLeptonpT","AntiLepton pT",40,0,400);
  h_AntiLeptonEta = new TH1D("AntiLeptonEta","AntiLepton Eta",40,-4,4);
  h_AntiLeptonE = new TH1D("AntiLeptonE","AntiLepton Energy",40,0,400);

  h_HypToppT = new TH1D("HypToppT","Top pT",40,0,400);
  h_HypTopEta = new TH1D("HypTopEta","Top pT",40,-4,4);
  h_HypTopE = new TH1D("HypTopE","Top Eneregy",40,0,400);
  h_HypTopMass = new TH1D("HypTopMass","Top Mass",40,0,400);
  h_HypTopRapidity = new TH1D("HypTopRapidity","Top Rapidity",50,-5,5);

  h_HypAntiToppT = new TH1D("HypAntiToppT","AntiTop pT",40,0,400);
  h_HypAntiTopEta = new TH1D("HypAntiTopEta","AntiTop pT",40,-4,4);
  h_HypAntiTopE = new TH1D("HypAntiTopE","AntiTop Energy",40,0,400);
  h_HypAntiTopMass = new TH1D("HypAntiTopMass","AntiTop Mass",40,0,400);
  h_HypAntiTopRapidity = new TH1D("HypAntiTopRapidity","Top Rapidity",50,-5,5);

  h_HypLeptonpT = new TH1D("HypLeptonpT","Lepton Hypothesis pT",40,0,400);
  h_HypLeptonEta = new TH1D("HypLeptonEta","Lepton Eta",40,-4,4);
  h_HypLeptonE = new TH1D("HypLeptonE","Lepton Energy",40,0,400);

  h_HypAntiLeptonpT = new TH1D("HypAntiLeptonpT","AntiLepton Hypothesis pT",40,0,400);
  h_HypAntiLeptonEta = new TH1D("HypAntiLeptonEta","AntiLepton Hypothesis Eta",40,-4,4);
  h_HypAntiLeptonE = new TH1D("HypAntiLeptonE","AntiLepton Hypothesis Energy",40,0,400);

  h_HypBpT = new TH1D("HypBpT","B Hypothesis pT",40,0,400);
  h_HypBEta = new TH1D("HypBEta","B Eta",40,-4,4);
  h_HypBE = new TH1D("HypBE","B Energy",40,0,400);

  h_HypAntiBpT = new TH1D("HypAntiBpT","AntiB Hypothesis pT",40,0,400);
  h_HypAntiBEta = new TH1D("HypAntiBEta","AntiB Hypothesis Eta",40,-4,4);
  h_HypAntiBE = new TH1D("HypAntiBE","AntiB Hypothesis Energy",40,0,400);

  h_HypNeutrinopT = new TH1D("HypNeutrinopT","Neutrino Hypothesis pT",40,0,400);
  h_HypNeutrinoEta = new TH1D("HypNeutrinoEta","Neutrino Eta",40,-4,4);
  h_HypNeutrinoE = new TH1D("HypNeutrinoE","Neutrino Energy",40,0,400);

  h_HypAntiNeutrinopT = new TH1D("HypAntiNeutrinopT","AntiNeutrino Hypothesis pT",40,0,400);
  h_HypAntiNeutrinoEta = new TH1D("HypAntiNeutrinoEta","AntiNeutrino Hypothesis Eta",40,-4,4);
  h_HypAntiNeutrinoE = new TH1D("HypAntiNeutrinoE","AntiNeutrino Hypothesis Energy",40,0,400);

 
  
  h_VisGenToppT = new TH1D("VisGenToppT","Top pT (VisGen)",40,0,400);
  h_VisGenTopEta = new TH1D("VisGenTopEta","Top Eta (VisGen)",40,-4,4);
  h_VisGenTopE = new TH1D("VisGenTopE","Top E (VisGen)",40,0,400);

  h_VisGenAntiToppT = new TH1D("VisGenAntiToppT","AntiTop pT (VisGen)",40,0,400);
  h_VisGenAntiTopEta = new TH1D("VisGenAntiTopEta","AntiTop pT (VisGen)",40,-4,4);
  h_VisGenAntiTopE = new TH1D("VisGenAntiTopE","AntiTop pT (VisGen)",40,0,400);

  h_VisGenLeptonpT = new TH1D("VisGenLeptonpT","Lepton VisGenothesis pT",80,0,400);
  h_VisGenLeptonEta = new TH1D("VisGenLeptonEta","Lepton Eta",40,-4,4);
  h_VisGenLeptonE = new TH1D("VisGenLeptonE","Lepton Energy",40,0,400);

  h_VisGenAntiLeptonpT = new TH1D("VisGenAntiLeptonpT","AntiLepton VisGenothesis pT",80,0,400);
  h_VisGenAntiLeptonEta = new TH1D("VisGenAntiLeptonEta","AntiLepton VisGenothesis Eta",40,-4,4);
  h_VisGenAntiLeptonE = new TH1D("VisGenAntiLeptonE","AntiLepton VisGenothesis Energy",40,0,400);

  h_VisGenBpT = new TH1D("VisGenBpT","B VisGenothesis pT",40,0,400);
  h_VisGenBEta = new TH1D("VisGenBEta","B Eta",40,-4,4);
  h_VisGenBE = new TH1D("VisGenBE","B Energy",40,0,400);

  h_VisGenAntiBpT = new TH1D("VisGenAntiBpT","AntiB VisGenothesis pT",40,0,400);
  h_VisGenAntiBEta = new TH1D("VisGenAntiBEta","AntiB VisGenothesis Eta",40,-4,4);
  h_VisGenAntiBE = new TH1D("VisGenAntiBE","AntiB VisGenothesis Energy",40,0,400);

  h_VisGenNeutrinopT = new TH1D("VisGenNeutrinopT","Neutrino VisGenothesis pT",40,0,400);
  h_VisGenNeutrinoEta = new TH1D("VisGenNeutrinoEta","Neutrino Eta",40,-4,4);
  h_VisGenNeutrinoE = new TH1D("VisGenNeutrinoE","Neutrino Energy",40,0,400);

  h_VisGenAntiNeutrinopT = new TH1D("VisGenAntiNeutrinopT","AntiNeutrino VisGenothesis pT",40,0,400);
  h_VisGenAntiNeutrinoEta = new TH1D("VisGenAntiNeutrinoEta","AntiNeutrino VisGenothesis Eta",40,-4,4);
  h_VisGenAntiNeutrinoE = new TH1D("VisGenAntiNeutrinoE","AntiNeutrino VisGenothesis Energy",40,0,400);

  h_GenToppT = new TH1D("GenToppT","Top pT (Gen)",40,0,400);
  h_GenTopEta = new TH1D("GenTopEta","Top Eta (Gen)",40,-4,4);
  h_GenTopE = new TH1D("GenTopE","Top E (Gen)",40,0,400);
  h_GenTopRapidity = new TH1D("GenTopRapidity","Top Rapidity (Gen)",50,-5,5);
  
  h_GenAntiToppT = new TH1D("GenAntiToppT","AntiTop pT (Gen)",40,0,400);
  h_GenAntiTopEta = new TH1D("GenAntiTopEta","AntiTop Eta (Gen)",40,-4,4);
  h_GenAntiTopE = new TH1D("GenAntiTopE","AntiTop E (Gen)",40,0,400);
  h_GenAntiTopRapidity = new TH1D("GenAntiTopRapidity","AntiTop (Gen)",50,-5,5);

  h_GenLeptonpT = new TH1D("GenLeptonpT","Lepton Genothesis pT",40,0,400);
  h_GenLeptonEta = new TH1D("GenLeptonEta","Lepton Eta",40,-4,4);
  h_GenLeptonE = new TH1D("GenLeptonE","Lepton Energy",40,0,400);

  h_GenAntiLeptonpT = new TH1D("GenAntiLeptonpT","AntiLepton Genothesis pT",40,0,400);
  h_GenAntiLeptonEta = new TH1D("GenAntiLeptonEta","AntiLepton Genothesis Eta",40,-4,4);
  h_GenAntiLeptonE = new TH1D("GenAntiLeptonE","AntiLepton Genothesis Energy",40,0,400);

  h_GenBpT = new TH1D("GenBpT","B Genothesis pT",40,0,400);
  h_GenBEta = new TH1D("GenBEta","B Eta",40,-4,4);
  h_GenBE = new TH1D("GenBE","B Energy",40,0,400);

  h_GenAntiBpT = new TH1D("GenAntiBpT","AntiB Genothesis pT",40,0,400);
  h_GenAntiBEta = new TH1D("GenAntiBEta","AntiB Genothesis Eta",40,-4,4);
  h_GenAntiBE = new TH1D("GenAntiBE","AntiB Genothesis Energy",40,0,400);

  h_GenNeutrinopT = new TH1D("GenNeutrinopT","Neutrino Genothesis pT",40,0,400);
  h_GenNeutrinoEta = new TH1D("GenNeutrinoEta","Neutrino Eta",40,-4,4);
  h_GenNeutrinoE = new TH1D("GenNeutrinoE","Neutrino Energy",40,0,400);

  h_GenAntiNeutrinopT = new TH1D("GenAntiNeutrinopT","AntiNeutrino Genothesis pT",40,0,400);
  h_GenAntiNeutrinoEta = new TH1D("GenAntiNeutrinoEta","AntiNeutrino Genothesis Eta",40,-4,4);
  h_GenAntiNeutrinoE = new TH1D("GenAntiNeutrinoE","AntiNeutrino Genothesis Energy",40,0,400);

  //   h1 = new TH1D("h1","h1",60,-3,3);
  //h1 = new TH1D("h1","h1",100,0,400);
   
  h_2DMatching = new TH2D("GenRecoMatching", "Gen/Reco Matching", 500,0,500,500,0,500);
  h_NJetMatching = new TH1D("NJetMatching", "NJet Gen/Reco Matching",5,0,5);
  
  
  
  //**************************************************************************************
  //bJet matching. By now no separation between Prompt or Tau decay signal.
  
  h_hypleptogenlep = new TH1D ("HypLepToGenLep", "HypLep Matched to GenLep", 10,  0, 10);
  h_hypantileptogenantilep = new TH1D ("HypAntiLepToGenAntiLep", "HypAntiLep Matched to GenAntiLep", 10, 0, 10);
  h_hypantileptogenlep = new TH1D ("HypAntiLepToGenLep", "HypAntiLep Matched to GenLep", 10, 0, 10);
  h_hypleptogenantilep = new TH1D ("HypLepToGenAntiLep", "HypLep Matched to GenAntiLep", 10, 0, 10);

  h_genjettogenb= new TH1D ("GenJetToGenB", "Gen Jet matched to Gen B", 5, 0, 5);
  h_genjettogenantib= new TH1D ("GenJetToGenAntiB", "Gen Jet matched to Gen AntiB", 5, 0, 5);

  h_hypbtogenb = new TH1D("HypBToGenB", "Hyp B matched to Gen B", 6, 0, 6);//15, 0, 15);
  h_hypbtogenantib = new TH1D("HypBToGenAntiB", "Hyp B matched to Gen Anti B",6, 0, 6);// 15, 0, 15);
  h_hypantibtogenb = new TH1D("HypAntiBToGenB", "Hyp AntiB matched to Gen B", 6, 0, 6);//15, 0, 15);
  h_hypantibtogenantib = new TH1D("HypAntiBToGenAntiB", "Hyp AntiB matched to Gen AntiB", 6, 0, 6);// 15, 0, 15);
  
  h_recojettohypb =new TH1D("RecoJetToHypB", "Jets matched to Hyp B", 30, 0, 30);
  h_recojettohypantib =new TH1D("RecoJetToHypAntiB", "Jets matched to Hyp AntiB", 30, 0, 30);

  h_recojettogenb =new TH1D("RecoJetToGenB", "Jets matched to Gen B", 30, 0, 30);
  h_recojettogenantib =new TH1D("RecoJetToGenAntiB", "Jets matched to Gen AntiB", 30, 0, 30);
  h_recojettogenjet=new TH1D ("RecoJetToGenJet", "Jets matched to Gen Jets", 30, 0, 30);
  
  h_hypbtogenjet = new TH1D("HypBToGenJet", "Matching: HypB To GenJet", 5, 0, 5);
  h_hypbtogenjettogenb=new TH1D("HypBToGenJetToGenB", "Matching: HypB To GenJet To GenB", 5, 0, 5);
  h_hypbtogenjettogenantib=new TH1D("HypBToGenJetToGenAntiB", "Matching: HypB To GenJet To GenAntiB", 5, 0, 5);

  h_hypantibtogenjet=new TH1D("HypAntiBToGenJet", "Matching: HypAntiB To GenJet", 5, 0, 5);
  h_hypantibtogenjettogenb=new TH1D("HypAntiBToGenJetToGenB", "Matching: HypAntiB To GenJet To GenB", 5, 0, 5);
  h_hypantibtogenjettogenantib=new TH1D("HypAntiBToGenJetToGenAntiB", "Matching: HypAntiB To GenJet To GenAntiB", 5, 0, 5);
  
  //------- DeltaR histograms definition
  h_deltargenjettogenb=new TH1D("DeltarGenJetToGenB", "DeltaR: GenJet To GenB", 200, 0, 10);// 14);
  h_deltargenjettogenantib=new TH1D("DeltarGenJetToGenAntiB", "DeltaR: GenJet To GenAntiB", 200, 0, 10);// 14);

  h_deltarhypbtogenjet=new TH1D("DeltarHypBToGenJet", "DeltaR: HypB To GenJet", 200, 0, 10);// 14);
  h_deltarhypantibtogenjet=new TH1D("DeltarHypAntiBToGenJet", "DeltaR: HypAntiB To GenJet", 200, 0, 10);// 14);

  h_deltarhypbtogenb= new TH1D("DeltarHypBToGenB", "DeltaR: HypB To GenB", 200, 0, 10);// 14);
  h_deltarhypbtogenantib= new TH1D("DeltarHypBToGenAntiB", "DeltaR: HypB To GenAntiB", 200, 0, 10);// 14);
  h_deltarhypantibtogenb= new TH1D("DeltarHypAntiBToGenB", "DeltaR: HypAntiB To GenB", 200, 0, 10);// 14);
  h_deltarhypantibtogenantib= new TH1D("DeltarHypAntiBToGenAntiB", "DeltaR: HypAntiB To GenAntiB", 200, 0, 10);// 14);

  h_deltarrecojettohypb=new TH1D("DeltarRecoJetToHypB", "DeltaR: Jet To HypB", 200, 0, 10);// 14);
  h_deltarrecojettohypantib=new TH1D("DeltarRecoJetToHypAntiB", "DeltaR: Jet To HypAntiB", 200, 0, 10);// 14);

  h_deltarrecojettogenb=new TH1D("DeltarRecoJetToGenB", "DeltaR: Jet To GenB", 200, 0, 10);// 14);
  h_deltarrecojettogenantib=new TH1D("DeltarRecoJetToGenAntiB", "DeltaR: Jet To GenAntiB", 200, 0, 10);// 14);
  h_deltarrecojettogenjet=new TH1D("DeltarRecoJetToGenJet", "DeltaR: Jet to GenJet", 200, 0, 10);// 14);

  h_deltargenbtogenantib=new TH1D("DeltarGenBToGenAntiB", "DeltaR: GenB To GenAntiB", 200, 0, 10);// 14);
  h_deltargenjettogenjet=new TH1D("DeltarGenJetToGenJet", "DeltaR: GenJet To GenJet", 200, 0, 10);// 14);
  h_deltarhypbtohypantib=new TH1D("DeltarHypBToHypAntiB", "DeltaR: HypB To HypAntiB", 200, 0, 10);// 14);
  h_deltarrecojettorecojet=new TH1D("DeltarRecoJetToRecoJet", "DeltaR: RecoJet To RecoJet", 200, 0, 10);// 14);

  //----- Differential distributions for matching and mismatching
  h_hypbptmatching 		= new TH1D("HypBpTMatching","B Hypothesis pT Matched",40,0,400);
  h_hypbptnotmatching 		= new TH1D("HypBpTNotMatching","B Hypothesis pT Not Matched",40,0,400);
  h_hypantibptmatching 		= new TH1D("HypAntiBpTMatching","AntiB Hypothesis pT Matched",40,0,400);
  h_hypantibptnotmatching 	= new TH1D("HypAntiBpTNotMatching","AntiB Hypothesis pT Not Matched",40,0,400);

  h_genbptmatching 		= new TH1D("GenBpTMatching","B Genothesis pT Matched",40,0,400);
  h_genbptnotmatching 		= new TH1D("GenBpTNotMatching","B Genothesis pT Not Matched",40,0,400);
  h_genantibptmatching 		= new TH1D("GenAntiBpTMatching","AntiB Genothesis pT Matched",40,0,400);
  h_genantibptnotmatching 	= new TH1D("GenAntiBpTNotMatching","AntiB Genesis pT Not Matched",40,0,400);

  h_hypbetamatching 		= new TH1D("HypBEtaMatching","B Hypothesis Eta Matched",40,-4,4);
  h_hypbetanotmatching 		= new TH1D("HypBEtaNotMatching","B Hypothesis Eta Not Matched",40,-4,4);
  h_hypantibetamatching       	= new TH1D("HypAntiBEtaMatching","AntiB Hypothesis Eta Matched",40,-4,4);
  h_hypantibetanotmatching 	= new TH1D("HypAntiBEtaNotMatching","AntiB Hypothesis Eta Not Matched",40,-4,4);

  h_genbetamatching 		= new TH1D("GenBEtaMatching","B Genothesis Eta Matched",40,-4,4);
  h_genbetanotmatching 		= new TH1D("GenBEtaNotMatching","B Genothesis Eta Not Matched",40,-4,4);
  h_genantibetamatching 	= new TH1D("GenAntiBEtaMatching","AntiB Genothesis Eta Matched",40,-4,4);
  h_genantibetanotmatching 	= new TH1D("GenAntiBEtaNotMatching","AntiB Genesis Eta Not Matched",40,-4,4);

  h_hypbematching 		= new TH1D("HypBEMatching","B Hypothesis E Matched",40,0,400);
  h_hypbenotmatching 		= new TH1D("HypBENotMatching","B Hypothesis E Not Matched",40,0,400);
  h_hypantibematching       	= new TH1D("HypAntiBEMatching","AntiB Hypothesis E Matched",40,0,400);
  h_hypantibenotmatching 	= new TH1D("HypAntiBENotMatching","AntiB Hypothesis E Not Matched",40,0,400);

  h_genbematching 		= new TH1D("GenBEMatching","B Genothesis Energy Matched",40,0,400);
  h_genbenotmatching 		= new TH1D("GenBENotMatching","B Genothesis Energy Not Matched",40,0,400);
  h_genantibematching    	= new TH1D("GenAntiBEMatching","AntiB Genothesis Energy Matched",40,-0,400);
  h_genantibenotmatching 	= new TH1D("GenAntiBENotMatching","AntiB Genesis Energy Not Matched",40,0,400);

  //end of matching section
  //***************************************************************************************

  //*************************************************************************************
  //Tau separation histograms
  h_HypToppTTau = new TH1D("HypToppTTau", "Tau decay HypTop Pt", 40, 0, 400);
  h_HypToppTPrompt = new TH1D("HypToppTPrompt", "Prompt HypTop Pt", 40, 0, 400);

  h_GenLeptonpTViaTau = new TH1D("GenLeptonpTViaTau","Lepton Genothesis pT via Tau",80,0,400);
  h_GenAntiLeptonpTViaTau = new TH1D("GenAntiLeptonpTViaTau","AntiLepton Genothesis pT Via Tau",80,0,400);
  h_HypLeptonpTViaTau = new TH1D("HypLeptonpTViaTau","Lepton Genothesis pT Via Tau",80,0,400);
  h_HypAntiLeptonpTViaTau = new TH1D("HypAntiLeptonpTViaTau","AntiLepton Genothesis pT Via Tau",80,0,400);

  h_GenLeptonpTViaTauNC = new TH1D("GenLeptonpTViaTauNC","Lepton Genothesis pT via Tau No Cut",80,0,400);
  h_GenAntiLeptonpTViaTauNC = new TH1D("GenAntiLeptonpTViaTauNC","AntiLepton Genothesis pT Via Tau No Cut",80,0,400);
  h_HypLeptonpTViaTauNC = new TH1D("HypLeptonpTViaTauNC","Lepton Hypothesis pT Via Tau No Cut",80,0,400);
  h_HypAntiLeptonpTViaTauNC = new TH1D("HypAntiLeptonpTViaTauNC","AntiLepton Hypothesis pT Via Tau No Cut",80,0,400);

  h_GenLeptonpTNC = new TH1D("GenLeptonpTNC","Lepton Genothesis pT No Cut",80,0,400);
  h_GenAntiLeptonpTNC = new TH1D("GenAntiLeptonpTNC","AntiLepton Genothesis pT No Cut",80,0,400);
  h_HypLeptonpTNC = new TH1D("HypLeptonpTNC","Lepton Hypothesis pT No Cut",80,0,400);
  h_HypAntiLeptonpTNC = new TH1D("HypAntiLeptonpTNC","AntiLepton Hypothesis pT No Cut",80,0,400);
  

  h_GenBMRoot = new TH1D ("GenBMRoot", "GenB.M()", 50, 2, 8);
  h_GenAntiBMRoot = new TH1D ("GenAntiBMRoot", "GenAntiB.M()", 50, 2, 8);
  h_HypBMRoot = new TH1D ("HypBMRoot", "HypB.M()", 100, 0, 100);
  h_HypAntiBMRoot = new TH1D ("HypAntiBMRoot", "HypAntiB.M()", 100, 0, 100);


  h_GenBM = new TH1D ("GenBM", "GenB Mass = sqrt(E^2-p^2)", 50, 2, 8);
  h_GenAntiBM = new TH1D ("GenAntiBM", "GenAntiB Mass=sqrt(E^2-p^2)", 50, 2, 8);
  h_HypBM = new TH1D ("HypBM", "HypB Mass = sqrt(E^2-p^2)", 100, 0, 100);
  h_HypAntiBM = new TH1D ("HypAntiBM", "HypAntiB Mass=sqrt(E^2-p^2)", 100, 0, 100);

}

void Analysis::SlaveBegin(TTree * /*tree*/)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).

  TString option = GetOption();

}

Bool_t Analysis::Process(Long64_t entry)
{
  Analysis::GetAllBranches(entry);
  if(MCSample->find("ttbarsignal")!=string::npos){ Analysis::GetSignalBranches(entry);}

  else if(MCSample->find("ttbarviatau")!=string::npos){ Analysis::GetSignalBranches(entry);}

  
  float dimass=0;
  double btagSFuse=1.0;//only use the btag SF when applying b-tagging
  //  trigEFF=1.0;
  double weightKinFituse = 1.0;//only use the kin fit SF when using the kinematic reconstruction
  std::vector<float> VLepton;

  std::vector<TLorentzVector> LVlepton;
  std::vector<TLorentzVector> LVjet;

  std::vector<TLorentzVector> LVHypTop;
  std::vector<TLorentzVector> LVHypAntiTop;
  std::vector<TLorentzVector> LVHypNeutrino;
  std::vector<TLorentzVector> LVHypAntiNeutrino;
  std::vector<TLorentzVector> LVHypB;
  std::vector<TLorentzVector> LVHypAntiB;
  std::vector<TLorentzVector> LVHypLepton;
  std::vector<TLorentzVector> LVHypAntiLepton;

  for(int i=0; i<jet_; i++){
    TLorentzVector jettemp(jetpX[i],jetpY[i],jetpZ[i],jetE[i]);
    LVjet.push_back(jettemp);
  }

  for(int i=0; i<HypTop_;i++){ 
    TLorentzVector antitoptemp(HypAntiToppX[i], HypAntiToppY[i], HypAntiToppZ[i], HypAntiTopE[i]);
    LVHypAntiTop.push_back(antitoptemp);
    TLorentzVector toptemp(HypToppX[i], HypToppY[i], HypToppZ[i], HypTopE[i]);
    LVHypTop.push_back(toptemp);
    TLorentzVector antineutrinotemp(HypAntiNeutrinopX[i], HypAntiNeutrinopY[i], HypAntiNeutrinopZ[i], HypAntiNeutrinoE[i]);
    LVHypAntiNeutrino.push_back(antineutrinotemp);
    TLorentzVector neutrinotemp(HypNeutrinopX[i], HypNeutrinopY[i], HypNeutrinopZ[i], HypNeutrinoE[i]);
    LVHypNeutrino.push_back(neutrinotemp);
    TLorentzVector antibtemp(HypAntiBpX[i], HypAntiBpY[i], HypAntiBpZ[i], HypAntiBE[i]);
    LVHypAntiB.push_back(antibtemp);
    TLorentzVector btemp(HypBpX[i], HypBpY[i], HypBpZ[i], HypBE[i]);
    LVHypB.push_back(btemp);
    TLorentzVector antileptontemp(HypAntiLeptonpX[i], HypAntiLeptonpY[i], HypAntiLeptonpZ[i], HypAntiLeptonE[i]);
    LVHypAntiLepton.push_back(antileptontemp);
    TLorentzVector leptontemp(HypLeptonpX[i], HypLeptonpY[i], HypLeptonpZ[i], HypLeptonE[i]);
    LVHypLepton.push_back(leptontemp);
  }


  TLorentzVector LVGenAntiTop(GenAntiToppX, GenAntiToppY, GenAntiToppZ, GenAntiTopE);
  TLorentzVector LVGenTop(GenToppX, GenToppY, GenToppZ, GenTopE);    
  TLorentzVector LVGenAntiNeutrino(GenAntiNeutrinopX, GenAntiNeutrinopY, GenAntiNeutrinopZ, GenAntiNeutrinoE);    
  TLorentzVector LVGenNeutrino(GenNeutrinopX, GenNeutrinopY, GenNeutrinopZ, GenNeutrinoE);    
  TLorentzVector LVGenAntiB(GenAntiBpX, GenAntiBpY, GenAntiBpZ, GenAntiBE);    
  TLorentzVector LVGenB(GenBpX, GenBpY, GenBpZ, GenBE);    
  TLorentzVector LVGenAntiLepton(GenAntiLeptonpX, GenAntiLeptonpY, GenAntiLeptonpZ, GenAntiLeptonE);    
  TLorentzVector LVGenLepton(GenLeptonpX, GenLeptonpY, GenLeptonpZ, GenLeptonE);    
  
  
  std::vector<TLorentzVector> LVGenJet;
  for (int i=0; i<genJet_; i++){
    TLorentzVector genjettemp(genJetpX[i], genJetpY[i], genJetpZ[i], genJetE[i]);
    LVGenJet.push_back(genjettemp);
  };

  
  
  for(int i=0; i<lepton_;i++){
    TLorentzVector leptemp(leptonpX[i], leptonpY[i], leptonpZ[i], leptonE[i]);
    LVlepton.push_back(leptemp);
  }
  
  for(int i=0; i<jet_;i++){
    TLorentzVector jettemp(jetpX[i], jetpY[i], jetpZ[i], jetE[i]);
    LVjet.push_back(jettemp);
  }
  
  bool useSSVHE = 0;
  double BtagWP = 1.7;
  
  if (algo.CompareTo("TCHEL") == 0)		{ useSSVHE = false;	 BtagWP = 1.7; }
  else if (algo.CompareTo("TCHEM") == 0)	{ useSSVHE = false;	 BtagWP = 3.3; }
  else if (algo.CompareTo("TCHET") == 0)	{ useSSVHE = false;	 BtagWP = 10.2; }
  else if (algo.CompareTo("SSVHEM") == 0)	{ useSSVHE = true;	 BtagWP = 1.74; }
  else if (algo.CompareTo("SSVHET") == 0)	{ useSSVHE = true;	 BtagWP = 3.05; }
  else {
    std::cout<<"b-Tagging algorithm not valid. Using default TCHEL"<<std::endl;
    useSSVHE = false;
    BtagWP = 1.7;
  };
   
  
  int NJets =0;
  vector<int> BJetIndex;
  
  if (useSSVHE == false){
    for(vector<double>::iterator it = jetBTagTCHE->begin(); it<jetBTagTCHE->end(); it++){
      if(*it > 0)NJets++;
      if(*it > BtagWP){
	BJetIndex.push_back(*it);
      }
    };
  }
  else if (useSSVHE == true){
    for(vector<double>::iterator it = jetBTagSSVHE->begin(); it<jetBTagSSVHE->end(); it++){
      if(*it > 0)NJets++;
      if(*it > BtagWP){
	BJetIndex.push_back(*it);
      }
    };
  }
  
  //*****************************************
  // KinFit solution selection
  
  //  BtagWP = 0;
  //Should we just look for two Bjets above 1.7 or the two highest bjets?:: Make this a function
  int solutionIndex = 0;
  bool oneTag = false;
  for(int i =0; i<HypTop_; i++){
    //TCHE bTagging
    if(useSSVHE == false){
      if((*jetBTagTCHE)[(*HypJet0index)[i]] > BtagWP && (*jetBTagTCHE)[(*HypJet1index)[i]]>BtagWP){
	solutionIndex = i; 
	break;
      }
      if(oneTag == false && ((*jetBTagTCHE)[(*HypJet0index)[i]] > BtagWP || (*jetBTagTCHE)[(*HypJet1index)[i]]>BtagWP)){solutionIndex = i; oneTag=true;} 
    }
   //SSVHE bTagging
    else if (useSSVHE == true){
      if((*jetBTagSSVHE)[(*HypJet0index)[i]] > BtagWP && (*jetBTagSSVHE)[(*HypJet1index)[i]]>BtagWP){
	solutionIndex = i; 
	break;
      }
      if(oneTag == false && ((*jetBTagSSVHE)[(*HypJet0index)[i]] > BtagWP || (*jetBTagSSVHE)[(*HypJet1index)[i]]>BtagWP)){solutionIndex = i; oneTag=true;}
    }
   }
  
  //****************************************************


  if (decayMode/10 == 5 || decayMode/10 == 6 || decayMode%10 == 5 || decayMode%10 == 6){//leptons from tau decays
    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4 && LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
      h_GenLeptonpTViaTauNC->Fill(LVGenLepton.Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
      h_GenAntiLeptonpTViaTauNC->Fill(LVGenAntiLepton.Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    }
    if (HypTop_){
    h_HypLeptonpTViaTauNC->Fill(LVHypLepton[solutionIndex].Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    h_HypAntiLeptonpTViaTauNC->Fill(LVHypAntiLepton[solutionIndex].Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    }
  }
  else{
    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4 && LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
      h_GenLeptonpTNC->Fill(LVGenLepton.Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
      h_GenAntiLeptonpTNC->Fill(LVGenAntiLepton.Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    }
    if (HypTop_){
    h_HypLeptonpTNC->Fill(LVHypLepton[solutionIndex].Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    h_HypAntiLeptonpTNC->Fill(LVHypAntiLepton[solutionIndex].Pt(),1);//weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
    }
  }

  
  
  
  
  if(MCSample->find("ttbarsignal")!=string::npos){  
    h_GenAll->Fill(LVGenTop.M(),1);
    if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
      if (LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
	
	h_VisGenAll->Fill(LVGenTop.M(),1); 
        double VisGenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	h_VisGenTTBarMass->Fill(VisGenTTBarMass,1);
	h_VisGenTTBarRapidity->Fill((LVGenTop+ LVGenAntiTop).Rapidity(),1);
	h_VisGenTTBarpT->Fill((LVGenTop+ LVGenAntiTop).Pt(),1);
	h_VisGenTopRapidity->Fill(LVGenTop.Rapidity(),1);
	h_VisGenAntiTopRapidity->Fill(LVGenAntiTop.Rapidity(),1);

	h_VisGenLLBarpT->Fill((LVGenLepton+ LVGenAntiLepton).Pt(),1);
	h_VisGenLLBarMass->Fill((LVGenLepton+ LVGenAntiLepton).M(),1);
	h_VisGenLeptonpT->Fill(LVGenLepton.Pt(),1);
	h_VisGenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),1);

	h_VisGenToppT->Fill(LVGenTop.Pt(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiToppT->Fill(LVGenAntiTop.Pt(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenBpT->Fill(LVGenB.Pt(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiBpT->Fill(LVGenAntiB.Pt(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenNeutrinopT->Fill(LVGenNeutrino.Pt(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiNeutrinopT->Fill(LVGenAntiNeutrino.Pt(),weightLepSF*btagSF*trigEFF*weightKinFit);
	
	h_VisGenTopEta->Fill(LVGenTop.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenBEta->Fill(LVGenB.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiBEta->Fill(LVGenAntiB.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenLeptonEta->Fill(LVGenLepton.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenNeutrinoEta->Fill(LVGenNeutrino.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiNeutrinoEta->Fill(LVGenAntiNeutrino.Eta(),weightLepSF*btagSF*trigEFF*weightKinFit);
	
	h_VisGenTopE->Fill(LVGenTop.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiTopE->Fill(LVGenAntiTop.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenBE->Fill(LVGenB.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiBE->Fill(LVGenAntiB.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenLeptonE->Fill(LVGenLepton.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenNeutrinoE->Fill(LVGenNeutrino.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
	h_VisGenAntiNeutrinoE->Fill(LVGenAntiNeutrino.E(),weightLepSF*btagSF*trigEFF*weightKinFit);
      }    
    }
  }//for visible top events	  



  if(lepton_>1){
    dimass = (LVlepton[0]+LVlepton[1]).M();
    h_vertMulti->Fill(vertMulti,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
  }

  //Cross-section Plots
  if(lepton_>1 && ((*lepQ)[0]!=(*lepQ)[1])&& dimass>12 && jet_>1 && BJetIndex.size()>0 && HypTop_){
    if(channel->find("emu")!=string::npos){//quick and DIRTY!
      h_jetMultiXSec->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF*weightKinFit);
      h_jetMultiNoPU->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit);
    }else{
      if(*(metEt->begin()) > 30 && (dimass < 76 || dimass >116)){
	h_jetMultiXSec->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSF*trigEFF*weightKinFit);
	h_jetMultiNoPU->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit);
      }  
    }
  }
  
  
  //Control plots
  //  if(lepton_>1&& jet_>1){  //two isolated leptons create dimass out of highest pt pair
  if(lepton_>1){  //two isolated leptons create dimass out of highest pt pair
    if(dimass>12 && ((*lepQ)[0]!=(*lepQ)[1])){
      h_diLepMassFull->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
      if(channel->find("emu")!=string::npos){//quick and DIRTY!
	if(dimass>12 && jet_>1){
	  h_BjetMulti->Fill(BJetIndex.size(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  double jetHT = 0;
	  for(int i=0; i<jet_;i++){	    
	    jetHT+=LVjet[i].Pt();
	  }
	  h_jetHT->Fill(jetHT,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  for(int i=0; i<2;i++){
	    h_jetpT->Fill(LVjet[i].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  
	  if((*lepQ)[0]==1){
	    h_LeptonpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[1].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[0].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }else{
	    h_LeptonpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[0].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[1].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }	
	  h_MET->Fill(*(metEt->begin()),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  if((*lepType)[0]==-1){
	    h_ElectronpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_ElectronEta->Fill(LVlepton[0].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepType)[1]==-1){
	    h_ElectronpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_ElectronEta->Fill(LVlepton[1].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepType)[0]==1){
	    h_MuonpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_MuonEta->Fill(LVlepton[0].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepType)[1]==1){
	    h_MuonpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_MuonEta->Fill(LVlepton[1].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	}
      }else{
	if (dimass> 12 && (dimass<76 || dimass > 106) && jet_>1 && *(metEt->begin()) > 30){
	  h_BjetMulti->Fill(BJetIndex.size(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  double jetHT = 0;
	  for(int i=0; i<jet_;i++){	    
	    jetHT+=LVjet[i].Pt();
	  }
	  h_jetHT->Fill(jetHT,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  for(int i=0; i<2;i++){
	    h_jetpT->Fill(LVjet[i].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  if((*lepQ)[0]==1){
	    h_LeptonpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[1].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[0].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  else{
	    h_LeptonpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_LeptonEta->Fill(LVlepton[0].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    h_AntiLeptonEta->Fill(LVlepton[1].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }	
	  h_MET->Fill(*(metEt->begin()),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  if(*(metEt->begin()) > 30){
	    if((*lepType)[0]==-1)h_ElectronpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    if((*lepType)[1]==-1)h_ElectronpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    if((*lepType)[0]==1)h_MuonpT->Fill(LVlepton[0].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	    if((*lepType)[1]==1)h_MuonpT->Fill(LVlepton[1].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  } 
	}
      }      
    } //
    if (dimass>76 && dimass < 106)Looseh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
   
 
    //if(dimass>12 && (lepQ[0]!=lepQ[1])){//Analysis step 6
    //if(dimass>12 && jet_>1 && (lepQ[0]!=lepQ[1])){//Analysis step 6
    //if(dimass>12 && jet_>1 && BJetIndex.size()>0 && (lepQ[0]!=lepQ[1])){btagSFuse=btagSF;//Analysis step 8?
    if(dimass>12 && jet_>1 && BJetIndex.size()>0 && HypTop_ && (lepQ[0]!=lepQ[1])){btagSFuse=btagSF; weightKinFituse=weightKinFit;//Analysis step 9?

      if(*(metEt->begin()) > 30){//for DY Scale Factor
	Allh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	if (dimass < 106 && dimass > 76 ){
	  Zh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
	else{TTh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);}
      }
    
      if(channel->find("emu")!=string::npos){//quick and DIRTY!
	if(MCSample->find("ttbarsignal")!=string::npos){
	  
	  if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
	    if (LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
	      h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit); 
	    }
	  }//for visible top events
	  double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	  h_GenTTBarMass->Fill(GenTTBarMass,1);
	  h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBpT->Fill(LVGenB.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBpT->Fill(LVGenAntiB.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenNeutrinopT->Fill(LVGenNeutrino.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiNeutrinopT->Fill(LVGenAntiNeutrino.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBEta->Fill(LVGenB.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBEta->Fill(LVGenAntiB.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenNeutrinoEta->Fill(LVGenNeutrino.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiNeutrinoEta->Fill(LVGenAntiNeutrino.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_GenTopE->Fill(LVGenTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiTopE->Fill(LVGenAntiTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBE->Fill(LVGenB.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBE->Fill(LVGenAntiB.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonE->Fill(LVGenLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenNeutrinoE->Fill(LVGenNeutrino.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiNeutrinoE->Fill(LVGenAntiNeutrino.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}	  
	if(HypTop_){
	  //h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  //	  cout<<"SolutionIndex: "<<solutionIndex<<endl;
	  //cout<< "BJetTCHE[HypJet0index[solutionIndex]]: "<<(*jetBTagTCHE)[(*HypJet0index)[solutionIndex]]<<endl;
	  //cout<< "BJetTCHE[HypJet1index[solutionIndex]]: "<<(*jetBTagTCHE)[(*HypJet1index)[solutionIndex]]<<endl<<endl;
	  double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	  h_RecoTTBarMass->Fill(HypTTBarMass,1);
	  h_RecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),1);
	  h_RecoTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),1);
	  h_RecoToppT->Fill(LVHypTop[solutionIndex].Pt(),1);
	  h_RecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),1);
	  h_RecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),1);
	  h_RecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),1);

	  h_RecoLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),1);
	  h_RecoLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),1);
	  h_RecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),1);
	  h_RecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),1);
	  h_RecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),1);
	  h_RecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),1);

	  h_HypTTBarMass->Fill(HypTTBarMass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTopMass->Fill(LVHypTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopMass->Fill(LVHypAntiTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBpT->Fill(LVHypB[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBpT->Fill(LVHypAntiB[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypNeutrinopT->Fill(LVHypNeutrino[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiNeutrinopT->Fill(LVHypAntiNeutrino[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  h_HypTopEta->Fill(LVHypTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopEta->Fill(LVHypAntiTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBEta->Fill(LVHypB[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBEta->Fill(LVHypAntiB[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypNeutrinoEta->Fill(LVHypNeutrino[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiNeutrinoEta->Fill(LVHypAntiNeutrino[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	     
	  h_HypTopE->Fill(LVHypTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopE->Fill(LVHypAntiTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBE->Fill(LVHypB[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBE->Fill(LVHypAntiB[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonE->Fill(LVHypLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonE->Fill(LVHypAntiLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypNeutrinoE->Fill(LVHypNeutrino[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiNeutrinoE->Fill(LVHypAntiNeutrino[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  //This 2 histograms will help in the calulation of the amount of singal events coming from prompt or Tau decay leptons
	  if (decayMode/10 == 5 || decayMode/10 == 6 || decayMode%10 == 5 || decayMode%10 == 6){
	    h_HypToppTTau->Fill(LVHypTop[solutionIndex].Pt(), weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  else{
	    h_HypToppTPrompt->Fill(LVHypTop[solutionIndex].Pt(), weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  
	  if(MCSample->find("ttbarsignal")!=string::npos){
	    //Only do the bMatching studies if the MC sample is ttbarsignal or ttbarsignalplustau. (this should be modified if the ttbarviatau sample is used)
	    //***************   bMatching studies **********************
	    //*******   No Cuts on GenB, GenAntiB, GenJets *************
	    //*** ONLY Evts passing the whole analysis are considered ***


	    //Selection step: 9. Hyp top exists-> KinFit Solution exists
	    
	    double deltar=0.5;

	    h_hypleptogenlep		->Fill(Matching(LVHypLepton[solutionIndex], LVGenLepton, deltar), 1);
	    h_hypantileptogenlep	->Fill(Matching(LVHypLepton[solutionIndex], LVGenAntiLepton, deltar), 1);
	    h_hypleptogenantilep	->Fill(Matching(LVHypAntiLepton[solutionIndex], LVGenLepton, deltar), 1);
	    h_hypantileptogenantilep	->Fill(Matching(LVHypAntiLepton[solutionIndex], LVGenAntiLepton, deltar), 1);
	    h_genjettogenb		->Fill(Matching(LVGenJet, LVGenB, deltar), 1);
	    h_genjettogenantib		->Fill(Matching(LVGenJet, LVGenAntiB, deltar), 1);
	    h_recojettogenb		->Fill(Matching(LVjet, LVGenB, deltar), 1);
	    h_recojettogenantib		->Fill(Matching(LVjet, LVGenAntiB, deltar), 1);
	    h_recojettogenjet		->Fill(Matching(LVjet, LVGenJet, deltar), 1);
	    h_hypbtogenjet		->Fill(Matching(LVHypB[solutionIndex], LVGenJet, deltar), 1);
	    h_hypantibtogenjet		->Fill(Matching(LVHypAntiB[solutionIndex], LVGenJet, deltar), 1);
	    h_recojettohypb		->Fill(Matching(LVjet, LVHypB[solutionIndex], deltar), 1);
	    h_recojettohypantib		->Fill(Matching(LVjet, LVHypAntiB[solutionIndex], deltar), 1);
	    h_hypbtogenb		->Fill(Matching(LVHypB[solutionIndex], LVGenB, deltar), 1);
	    h_hypbtogenantib		->Fill(Matching(LVHypB[solutionIndex], LVGenAntiB, deltar), 1);
	    h_hypantibtogenb		->Fill(Matching(LVHypAntiB[solutionIndex], LVGenB, deltar), 1);
	    h_hypantibtogenantib	->Fill(Matching(LVHypAntiB[solutionIndex], LVGenAntiB, deltar), 1);

	    //triple matching
	    h_hypbtogenjettogenb	->Fill(Matching(LVHypB[solutionIndex], LVGenJet, LVGenB), 1);
	    h_hypbtogenjettogenantib	->Fill(Matching(LVHypB[solutionIndex], LVGenJet, LVGenAntiB), 1);
	    h_hypantibtogenjettogenb	->Fill(Matching(LVHypAntiB[solutionIndex], LVGenJet, LVGenB), 1);
	    h_hypantibtogenjettogenantib->Fill(Matching(LVHypAntiB[solutionIndex], LVGenJet, LVGenAntiB), 1);

	    

	    h_deltargenbtogenantib->Fill(LVGenB.DeltaR(LVGenAntiB), 1);
	    h_deltarhypbtohypantib->Fill(LVHypB[solutionIndex].DeltaR(LVHypAntiB[solutionIndex]), 1);

	    h_deltarhypbtogenb		->Fill(LVHypB[solutionIndex].DeltaR(LVGenB), 1);
	    h_deltarhypbtogenantib	->Fill(LVHypB[solutionIndex].DeltaR(LVGenAntiB), 1);
	    h_deltarhypantibtogenb	->Fill(LVHypAntiB[solutionIndex].DeltaR(LVGenB), 1);
	    h_deltarhypantibtogenantib	->Fill(LVHypAntiB[solutionIndex].DeltaR(LVGenAntiB), 1);

	    for (int i=0; i<(int)LVGenJet.size(); i++){

	      h_deltargenjettogenb->Fill(LVGenJet[i].DeltaR(LVGenB), 1);
	      h_deltargenjettogenantib->Fill(LVGenJet[i].DeltaR(LVGenAntiB), 1);

	      h_deltarhypbtogenjet->Fill(LVHypB[solutionIndex].DeltaR(LVGenJet[i]), 1);
	      h_deltarhypantibtogenjet->Fill(LVHypAntiB[solutionIndex].DeltaR(LVGenJet[i]), 1);
	    
	      for (int j=i+1; j<(int)LVGenJet.size(); j++){
		h_deltargenjettogenjet->Fill(LVGenJet[i].DeltaR(LVGenJet[j]), 1);
	      };
	    };
	    
	    //Differential distribution's matching or mismatching
            h_GenBMRoot->Fill(LVGenB.M(), 1);
	    h_HypBMRoot->Fill(LVHypB[solutionIndex].M(), 1);
            double genbmass= TMath::Sqrt(LVGenB.E()*LVGenB.E()-LVGenB.Px()*LVGenB.Px()-LVGenB.Py()*LVGenB.Py()-LVGenB.Pz()*LVGenB.Pz());
            double hypbmass= TMath::Sqrt(LVHypB[solutionIndex].E()*LVHypB[solutionIndex].E()-LVHypB[solutionIndex].Px()*LVHypB[solutionIndex].Px()-LVHypB[solutionIndex].Py()*LVHypB[solutionIndex].Py()-LVHypB[solutionIndex].Pz()*LVHypB[solutionIndex].Pz());
            h_GenBM->Fill(genbmass, 1);
	    h_HypBM->Fill(hypbmass, 1);
	    
	    h_GenAntiBMRoot->Fill(LVGenAntiB.M(), 1);
	    h_HypAntiBMRoot->Fill(LVHypAntiB[solutionIndex].M(), 1);
            double genantibmass=TMath::Sqrt(LVGenAntiB.E()*LVGenAntiB.E()-LVGenAntiB.Px()*LVGenAntiB.Px()-LVGenAntiB.Py()*LVGenAntiB.Py()-LVGenAntiB.Pz()*LVGenAntiB.Pz());
            double hypantibmass=TMath::Sqrt(LVHypAntiB[solutionIndex].E()*LVHypAntiB[solutionIndex].E()-LVHypAntiB[solutionIndex].Px()*LVHypAntiB[solutionIndex].Px()-LVHypAntiB[solutionIndex].Py()*LVHypAntiB[solutionIndex].Py()-LVHypAntiB[solutionIndex].Pz()*LVHypAntiB[solutionIndex].Pz());
            h_GenAntiBM->Fill(genantibmass, 1);
	    h_HypAntiBM->Fill(hypantibmass, 1);
	    
	    if (Matching(LVHypB[solutionIndex], LVGenJet, LVGenB, deltar) == 1 ){
	      h_hypbptmatching->Fill(LVHypB[solutionIndex].Pt(), 1);  
              h_hypbetamatching->Fill(LVHypB[solutionIndex].Eta(), 1); 
              h_hypbematching->Fill(LVHypB[solutionIndex].E(), 1);
                
              h_genbptmatching->Fill(LVGenB.Pt(), 1);                 
              h_genbetamatching->Fill(LVGenB.Eta(), 1); 
              h_genbematching->Fill(LVGenB.E(), 1);

	    }
	    else {
	      h_hypbptnotmatching->Fill(LVHypB[solutionIndex].Pt(), 1);
              h_hypbetanotmatching->Fill(LVHypB[solutionIndex].Eta(), 1); 
              h_hypbenotmatching->Fill(LVHypB[solutionIndex].E(), 1);

              h_genbptnotmatching->Fill(LVGenB.Pt(), 1);
              h_genbetanotmatching->Fill(LVGenB.Eta(), 1);
              h_genbenotmatching->Fill(LVGenB.E(), 1);
	    };

	    if (Matching(LVHypAntiB[solutionIndex], LVGenJet, LVGenAntiB, deltar) == 1){
	      h_hypantibptmatching->Fill(LVHypAntiB[solutionIndex].Pt(), 1);    
              h_hypantibetamatching->Fill(LVHypAntiB[solutionIndex].Eta(), 1);
              h_hypantibematching->Fill(LVHypAntiB[solutionIndex].E(), 1);

              h_genantibptmatching->Fill(LVGenAntiB.Pt(), 1);
              h_genantibetamatching->Fill(LVGenAntiB.Eta(), 1);
              h_genantibematching->Fill(LVGenAntiB.E(), 1);
	    }
	    else{
	      h_hypantibptnotmatching->Fill(LVHypAntiB[solutionIndex].Pt(), 1);
              h_hypantibetanotmatching->Fill(LVHypAntiB[solutionIndex].Eta(), 1);
              h_hypantibenotmatching->Fill(LVHypAntiB[solutionIndex].E(), 1);

              h_genantibptnotmatching->Fill(LVGenAntiB.Pt(), 1);
              h_genantibetanotmatching->Fill(LVGenAntiB.Eta(), 1);
              h_genantibenotmatching->Fill(LVGenAntiB.E(), 1);
	     };
	
	     
	    for (int i=0; i<(int)LVjet.size(); i++){
	      h_deltarrecojettohypb->Fill(LVjet[i].DeltaR(LVHypB[solutionIndex]), 1);
	      h_deltarrecojettohypantib->Fill(LVjet[i].DeltaR(LVHypAntiB[solutionIndex]), 1);
	      h_deltarrecojettogenb->Fill(LVjet[i].DeltaR(LVGenB), 1);
	      h_deltarrecojettogenantib->Fill(LVjet[i].DeltaR(LVGenAntiB), 1);
	
	      for(int k=i+1; k<(int)LVjet.size(); k++){
		h_deltarrecojettorecojet->Fill(LVjet[i].DeltaR(LVjet[k]), 1);
	      };

	      for(int j=0; j<(int)LVGenJet.size(); j++){
		h_deltarrecojettogenjet->Fill(LVjet[i].DeltaR(LVGenJet[j]), 1);
	      };
	    };
	  }//end of matching section

	}
      }else if(*(metEt->begin()) > 30 && (dimass<76 || dimass>106)){ //ee and mumu decay channels: no MET or DY peak cut

	//h_jetMulti->Fill(jet_,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	//TTh1->Fill(dimass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	if(MCSample->find("ttbarsignal")!=string::npos){

	  if (LVGenLepton.Pt()>20 && LVGenAntiLepton.Pt()>20 && abs(LVGenLepton.Eta())<2.4 && abs(LVGenAntiLepton.Eta())<2.4){
	    if (LVGenB.Pt()>30 && LVGenAntiB.Pt()>30 && abs(LVGenB.Eta())<2.4 && abs(LVGenAntiB.Eta())<2.4){
	      h_jetMultiVisTop->Fill(jet_,weightLepSF*btagSF*trigEFF*weightKinFit); 
	    }
	  }//for visible top events


	  double GenTTBarMass = (LVGenTop+ LVGenAntiTop).M();
	  h_GenTTBarMass->Fill(GenTTBarMass,1);
	  h_GenToppT->Fill(LVGenTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiToppT->Fill(LVGenAntiTop.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBpT->Fill(LVGenB.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBpT->Fill(LVGenAntiB.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonpT->Fill(LVGenLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonpT->Fill(LVGenAntiLepton.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenNeutrinopT->Fill(LVGenNeutrino.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiNeutrinopT->Fill(LVGenAntiNeutrino.Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  h_GenTopEta->Fill(LVGenTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiTopEta->Fill(LVGenAntiTop.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBEta->Fill(LVGenB.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBEta->Fill(LVGenAntiB.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonEta->Fill(LVGenLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonEta->Fill(LVGenAntiLepton.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenNeutrinoEta->Fill(LVGenNeutrino.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiNeutrinoEta->Fill(LVGenAntiNeutrino.Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_GenTopE->Fill(LVGenTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiTopE->Fill(LVGenAntiTop.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenBE->Fill(LVGenB.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiBE->Fill(LVGenAntiB.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenLeptonE->Fill(LVGenLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiLeptonE->Fill(LVGenAntiLepton.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenNeutrinoE->Fill(LVGenNeutrino.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_GenAntiNeutrinoE->Fill(LVGenAntiNeutrino.E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	}
	   
	if(HypTop_){
	  int NJetMatching=0;

	  h_NJetMatching->Fill(NJetMatching);

	  double HypTTBarMass = (LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).M();
	  h_RecoTTBarMass->Fill(HypTTBarMass,1);
	  h_RecoTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),1);
	  h_RecoTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),1);
	  h_RecoToppT->Fill(LVHypTop[solutionIndex].Pt(),1);
	  h_RecoAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),1);
	  h_RecoTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),1);
	  h_RecoAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),1);

	  h_RecoLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),1);
	  h_RecoLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),1);
	  h_RecoLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),1);
	  h_RecoAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),1);
	  h_RecoLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),1);
	  h_RecoAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),1);

	  h_HypLLBarMass->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLLBarpT->Fill((LVHypLepton[solutionIndex]+ LVHypAntiLepton[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTTBarMass->Fill(HypTTBarMass,weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypTTBarRapidity->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypTTBarpT->Fill((LVHypTop[solutionIndex]+ LVHypAntiTop[solutionIndex]).Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTopMass->Fill(LVHypTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopMass->Fill(LVHypAntiTop[solutionIndex].M(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypToppT->Fill(LVHypTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiToppT->Fill(LVHypAntiTop[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBpT->Fill(LVHypB[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBpT->Fill(LVHypAntiB[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonpT->Fill(LVHypLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonpT->Fill(LVHypAntiLepton[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypNeutrinopT->Fill(LVHypNeutrino[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiNeutrinopT->Fill(LVHypAntiNeutrino[solutionIndex].Pt(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);

	  h_HypTopRapidity->Fill(LVHypTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopRapidity->Fill(LVHypAntiTop[solutionIndex].Rapidity(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  h_HypTopEta->Fill(LVHypTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopEta->Fill(LVHypAntiTop[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBEta->Fill(LVHypB[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBEta->Fill(LVHypAntiB[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonEta->Fill(LVHypLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonEta->Fill(LVHypAntiLepton[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypNeutrinoEta->Fill(LVHypNeutrino[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiNeutrinoEta->Fill(LVHypAntiNeutrino[solutionIndex].Eta(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	     
	  h_HypTopE->Fill(LVHypTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiTopE->Fill(LVHypAntiTop[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypBE->Fill(LVHypB[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiBE->Fill(LVHypAntiB[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypLeptonE->Fill(LVHypLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiLeptonE->Fill(LVHypAntiLepton[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypNeutrinoE->Fill(LVHypNeutrino[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  h_HypAntiNeutrinoE->Fill(LVHypAntiNeutrino[solutionIndex].E(),weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  
	  
	  //This 2 histograms will help in the calulation of the amount of singal events coming from prompt or Tau decay leptons
	  if (decayMode/10 == 5 || decayMode/10 == 6 || decayMode%10 == 5 || decayMode%10 == 6){
	    h_HypToppTTau->Fill(LVHypTop[solutionIndex].Pt(), weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  else{
	    h_HypToppTPrompt->Fill(LVHypTop[solutionIndex].Pt(), weightPU*weightLepSF*lumiWeight*btagSFuse*trigEFF*weightKinFituse);
	  }
	  
	  if(MCSample->find("ttbarsignal")!=string::npos){
	    //Only do the bMatching studies if the MC sample is ttbarsignal or ttbarsignalplustau. (this should be modified if the ttbarviatau sample is used)
	    //***************   bMatching studies **********************
	    //*******   No Cuts on GenB, GenAntiB, GenJets *************
	    //*** ONLY Evts passing the whole analysis are considered ***


	    //Selection step: 9. Hyp top exists-> KinFit Solution exists
	    
	    double deltar=0.5; //0.5; //0.3; //0.75;

	    h_hypleptogenlep		->Fill(Matching(LVHypLepton[solutionIndex], LVGenLepton, deltar), 1);
	    h_hypantileptogenlep	->Fill(Matching(LVHypLepton[solutionIndex], LVGenAntiLepton, deltar), 1);
	    h_hypleptogenantilep	->Fill(Matching(LVHypAntiLepton[solutionIndex], LVGenLepton, deltar), 1);
	    h_hypantileptogenantilep	->Fill(Matching(LVHypAntiLepton[solutionIndex], LVGenAntiLepton, deltar), 1);
	    h_genjettogenb		->Fill(Matching(LVGenJet, LVGenB, deltar), 1);
	    h_genjettogenantib		->Fill(Matching(LVGenJet, LVGenAntiB, deltar), 1);
	    h_recojettogenb		->Fill(Matching(LVjet, LVGenB, deltar), 1);
	    h_recojettogenantib		->Fill(Matching(LVjet, LVGenAntiB, deltar), 1);
	    h_recojettogenjet		->Fill(Matching(LVjet, LVGenJet, deltar), 1);
	    h_hypbtogenjet		->Fill(Matching(LVHypB[solutionIndex], LVGenJet, deltar), 1);
	    h_hypantibtogenjet		->Fill(Matching(LVHypAntiB[solutionIndex], LVGenJet, deltar), 1);
	    h_recojettohypb		->Fill(Matching(LVjet, LVHypB[solutionIndex], deltar), 1);
	    h_recojettohypantib		->Fill(Matching(LVjet, LVHypAntiB[solutionIndex], deltar), 1);
	    h_hypbtogenb		->Fill(Matching(LVHypB[solutionIndex], LVGenB, deltar), 1);
	    h_hypbtogenantib		->Fill(Matching(LVHypB[solutionIndex], LVGenAntiB, deltar), 1);
	    h_hypantibtogenb		->Fill(Matching(LVHypAntiB[solutionIndex], LVGenB, deltar), 1);
	    h_hypantibtogenantib	->Fill(Matching(LVHypAntiB[solutionIndex], LVGenAntiB, deltar), 1);

	    //triple matching
	    h_hypbtogenjettogenb	->Fill(Matching(LVHypB[solutionIndex], LVGenJet, LVGenB), 1);
	    h_hypbtogenjettogenantib	->Fill(Matching(LVHypB[solutionIndex], LVGenJet, LVGenAntiB), 1);
	    h_hypantibtogenjettogenb	->Fill(Matching(LVHypAntiB[solutionIndex], LVGenJet, LVGenB), 1);
	    h_hypantibtogenjettogenantib->Fill(Matching(LVHypAntiB[solutionIndex], LVGenJet, LVGenAntiB), 1);

	    

	    h_deltargenbtogenantib->Fill(LVGenB.DeltaR(LVGenAntiB), 1);
	    h_deltarhypbtohypantib->Fill(LVHypB[solutionIndex].DeltaR(LVHypAntiB[solutionIndex]), 1);

	    h_deltarhypbtogenb		->Fill(LVHypB[solutionIndex].DeltaR(LVGenB), 1);
	    h_deltarhypbtogenantib	->Fill(LVHypB[solutionIndex].DeltaR(LVGenAntiB), 1);
	    h_deltarhypantibtogenb	->Fill(LVHypAntiB[solutionIndex].DeltaR(LVGenB), 1);
	    h_deltarhypantibtogenantib	->Fill(LVHypAntiB[solutionIndex].DeltaR(LVGenAntiB), 1);

	    for (int i=0; i<(int)LVGenJet.size(); i++){

	      h_deltargenjettogenb->Fill(LVGenJet[i].DeltaR(LVGenB), 1);
	      h_deltargenjettogenantib->Fill(LVGenJet[i].DeltaR(LVGenAntiB), 1);

	      h_deltarhypbtogenjet->Fill(LVHypB[solutionIndex].DeltaR(LVGenJet[i]), 1);
	      h_deltarhypantibtogenjet->Fill(LVHypAntiB[solutionIndex].DeltaR(LVGenJet[i]), 1);



	      for (int j=i+1; j<(int)LVGenJet.size(); j++){
		h_deltargenjettogenjet->Fill(LVGenJet[i].DeltaR(LVGenJet[j]), 1);
	      };
	    };
	      
	    //Differential distribution's matching or mismatching
	    
	    h_GenAntiBMRoot->Fill(LVGenAntiB.M(), 1);
	    h_HypAntiBMRoot->Fill(LVHypAntiB[solutionIndex].M(), 1);
            double genantibmass=TMath::Sqrt(LVGenAntiB.E()*LVGenAntiB.E()-LVGenAntiB.Px()*LVGenAntiB.Px()-LVGenAntiB.Py()*LVGenAntiB.Py()-LVGenAntiB.Pz()*LVGenAntiB.Pz());
            double hypantibmass=TMath::Sqrt(LVHypAntiB[solutionIndex].E()*LVHypAntiB[solutionIndex].E()-LVHypAntiB[solutionIndex].Px()*LVHypAntiB[solutionIndex].Px()-LVHypAntiB[solutionIndex].Py()*LVHypAntiB[solutionIndex].Py()-LVHypAntiB[solutionIndex].Pz()*LVHypAntiB[solutionIndex].Pz());
            h_GenAntiBM->Fill(genantibmass, 1);
	    h_HypAntiBM->Fill(hypantibmass, 1);
	    
            h_GenBMRoot->Fill(LVGenB.M(), 1);
	    h_HypBMRoot->Fill(LVHypB[solutionIndex].M(), 1);
            double genbmass= TMath::Sqrt(LVGenB.E()*LVGenB.E()-LVGenB.Px()*LVGenB.Px()-LVGenB.Py()*LVGenB.Py()-LVGenB.Pz()*LVGenB.Pz());
            double hypbmass= TMath::Sqrt(LVHypB[solutionIndex].E()*LVHypB[solutionIndex].E()-LVHypB[solutionIndex].Px()*LVHypB[solutionIndex].Px()-LVHypB[solutionIndex].Py()*LVHypB[solutionIndex].Py()-LVHypB[solutionIndex].Pz()*LVHypB[solutionIndex].Pz());
            h_GenBM->Fill(genbmass, 1);
	    h_HypBM->Fill(hypbmass, 1);
	    
	    if (Matching(LVHypB[solutionIndex], LVGenJet, LVGenB, deltar) == 1 ){
	      h_hypbptmatching->Fill(LVHypB[solutionIndex].Pt(), 1);  
              h_hypbetamatching->Fill(LVHypB[solutionIndex].Eta(), 1); 
              h_hypbematching->Fill(LVHypB[solutionIndex].E(), 1);
                
              h_genbptmatching->Fill(LVGenB.Pt(), 1);                 
              h_genbetamatching->Fill(LVGenB.Eta(), 1); 
              h_genbematching->Fill(LVGenB.E(), 1);
	    }
	    else {
	      h_hypbptnotmatching->Fill(LVHypB[solutionIndex].Pt(), 1);
              h_hypbetanotmatching->Fill(LVHypB[solutionIndex].Eta(), 1); 
              h_hypbenotmatching->Fill(LVHypB[solutionIndex].E(), 1);

              h_genbptnotmatching->Fill(LVGenB.Pt(), 1);
              h_genbetanotmatching->Fill(LVGenB.Eta(), 1);
              h_genbenotmatching->Fill(LVGenB.E(), 1);
	    };


	    
	    if (Matching(LVHypAntiB[solutionIndex], LVGenJet, LVGenAntiB, deltar) == 1){
	      h_hypantibptmatching->Fill(LVHypAntiB[solutionIndex].Pt(), 1);
              h_hypantibetamatching->Fill(LVHypAntiB[solutionIndex].Eta(), 1);
              h_hypantibematching->Fill(LVHypAntiB[solutionIndex].E(), 1);

              h_genantibptmatching->Fill(LVGenAntiB.Pt(), 1);
              h_genantibetamatching->Fill(LVGenAntiB.Eta(), 1);
              h_genantibematching->Fill(LVGenAntiB.E(), 1);

              
	    }
	    else{
	      h_hypantibptnotmatching->Fill(LVHypAntiB[solutionIndex].Pt(), 1);
              h_hypantibetanotmatching->Fill(LVHypAntiB[solutionIndex].Eta(), 1);
              h_hypantibenotmatching->Fill(LVHypAntiB[solutionIndex].E(), 1);

              h_genantibptnotmatching->Fill(LVGenAntiB.Pt(), 1);
              h_genantibetanotmatching->Fill(LVGenAntiB.Eta(), 1);
              h_genantibenotmatching->Fill(LVGenAntiB.E(), 1);
	    };

	    for (int i=0; i<(int)LVjet.size(); i++){
	
	      h_deltarrecojettohypb->Fill(LVjet[i].DeltaR(LVHypB[solutionIndex]), 1);
	      h_deltarrecojettohypantib->Fill(LVjet[i].DeltaR(LVHypAntiB[solutionIndex]), 1);
	      h_deltarrecojettogenb->Fill(LVjet[i].DeltaR(LVGenB), 1);
	      h_deltarrecojettogenantib->Fill(LVjet[i].DeltaR(LVGenAntiB), 1);
	
	      for(int k=i+1; k<(int)LVjet.size(); k++){
		h_deltarrecojettorecojet->Fill(LVjet[i].DeltaR(LVjet[k]), 1);
	      };

	      for(int j=0; j<(int)LVGenJet.size(); j++){
		h_deltarrecojettogenjet->Fill(LVjet[i].DeltaR(LVGenJet[j]), 1);
	      };
	    };
	  }//end of matching section

	}
      }
    }
  } 
  
  return kTRUE;
}


void Analysis::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.

}

void Analysis::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.


  TString f_savename = TString("selectionRoot/");
  gSystem->MakeDirectory(f_savename);
  f_savename.Append(algo);
  gSystem->MakeDirectory(f_savename);
  f_savename.Append("/");
  f_savename.Append(*channel); 
  gSystem->MakeDirectory(f_savename);
  f_savename.Append("/");
  f_savename.Append(*MCSample);
  f_savename.Append(".root");
  

  std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!Finishing: "<<*MCSample<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl<<std:: endl;

  TFile *f = new TFile(f_savename,"RECREATE");

  //AllDIM.write();
  //InDIM.writeone();
  //OutDIM.writeone();

  h_2DMatching->Write();
  h_NJetMatching->Write();
  h_diLepMassFull->Write();
  Allh1->Write();
  Looseh1->Write();
  h_GenAll->Write();
  h_VisGenAll->Write();
  h_vertMulti->Write();
  h_jetMulti->Write();
  h_BjetMulti->Write();
  h_jetMultiXSec->Write();
  h_jetMultiNoPU->Write();
  Zh1->Write();
  TTh1->Write();

  h_HypTTBarpT->Write();
  h_HypTTBarRapidity->Write();
  h_HypTTBarMass->Write();
  h_HypLLBarpT->Write();
  h_HypLLBarMass->Write();

  h_GenTTBarMass->Write();
  h_GenTTBarRapidity->Write();
  h_GenTTBarpT->Write();
  h_GenLLBarpT->Write();
  h_GenLLBarMass->Write();

  h_VisGenTTBarMass->Write();
  h_VisGenTTBarRapidity->Write();
  h_VisGenTTBarpT->Write();
  h_VisGenLLBarpT->Write();
  h_VisGenLLBarMass->Write();

  h_RecoTTBarMass->Write();
  h_RecoTTBarRapidity->Write();
  h_RecoTTBarpT->Write();
  h_RecoToppT->Write();
  h_RecoAntiToppT->Write();
  h_RecoTopRapidity->Write();
  h_RecoAntiTopRapidity->Write();

  h_RecoLLBarMass->Write();
  h_RecoLLBarpT->Write();
  h_RecoLeptonpT->Write();
  h_RecoAntiLeptonpT->Write();
  h_RecoLeptonEta->Write();
  h_RecoAntiLeptonEta->Write();

  h_jetpT->Write();
  h_jetHT->Write();
  h_MET->Write();
  h_LeptonpT->Write();
  h_LeptonEta->Write();
  h_AntiLeptonpT->Write();
  h_AntiLeptonEta->Write();
  h_ElectronpT->Write();
  h_ElectronEta->Write();
  h_MuonpT->Write();
  h_MuonEta->Write();

  h_VisGenNeutrinopT->Write();
  h_VisGenAntiNeutrinopT->Write();
  h_VisGenNeutrinoEta->Write();
  h_VisGenAntiNeutrinoEta->Write();
  h_VisGenNeutrinoE->Write();
  h_VisGenAntiNeutrinoE->Write();

  h_VisGenBpT->Write();
  h_VisGenAntiBpT->Write();
  h_VisGenBEta->Write();
  h_VisGenAntiBEta->Write();
  h_VisGenBE->Write();
  h_VisGenAntiBE->Write();

  h_VisGenLeptonpT->Write();
  h_VisGenAntiLeptonpT->Write();
  h_VisGenLeptonEta->Write();
  h_VisGenAntiLeptonEta->Write();
  h_VisGenLeptonE->Write();
  h_VisGenAntiLeptonE->Write();

  h_VisGenToppT->Write();
  h_VisGenAntiToppT->Write();
  h_VisGenTopEta->Write();
  h_VisGenAntiTopEta->Write();
  h_VisGenTopE->Write();
  h_VisGenAntiTopE->Write();
  h_VisGenTopRapidity->Write();
  h_VisGenAntiTopRapidity->Write();

  h_GenNeutrinopT->Write();
  h_GenAntiNeutrinopT->Write();
  h_GenNeutrinoEta->Write();
  h_GenAntiNeutrinoEta->Write();
  h_GenNeutrinoE->Write();
  h_GenAntiNeutrinoE->Write();

  h_GenBpT->Write();
  h_GenAntiBpT->Write();
  h_GenBEta->Write();
  h_GenAntiBEta->Write();
  h_GenBE->Write();
  h_GenAntiBE->Write();

  h_GenLeptonpT->Write();
  h_GenAntiLeptonpT->Write();
  h_GenLeptonEta->Write();
  h_GenAntiLeptonEta->Write();
  h_GenLeptonE->Write();
  h_GenAntiLeptonE->Write();

  h_GenToppT->Write();
  h_GenAntiToppT->Write();
  h_GenTopEta->Write();
  h_GenAntiTopEta->Write();
  h_GenTopE->Write();
  h_GenAntiTopE->Write();
  h_GenTopRapidity->Write();
  h_GenAntiTopRapidity->Write();

  h_HypNeutrinopT->Write();
  h_HypAntiNeutrinopT->Write();
  h_HypNeutrinoEta->Write();
  h_HypAntiNeutrinoEta->Write();
  h_HypNeutrinoE->Write();
  h_HypAntiNeutrinoE->Write();

  h_HypBpT->Write();
  h_HypAntiBpT->Write();
  h_HypBEta->Write();
  h_HypAntiBEta->Write();
  h_HypBE->Write();
  h_HypAntiBE->Write();

  h_HypLeptonpT->Write();
  h_HypAntiLeptonpT->Write();
  h_HypLeptonEta->Write();
  h_HypAntiLeptonEta->Write();
  h_HypLeptonE->Write();
  h_HypAntiLeptonE->Write();

  h_HypTopRapidity->Write();
  h_HypAntiTopRapidity->Write();

  h_HypTopMass->Write();
  h_HypAntiTopMass->Write();
  h_HypToppT->Write();
  h_HypAntiToppT->Write();
  h_HypTopEta->Write();
  h_HypAntiTopEta->Write();
  h_HypTopE->Write();
  h_HypAntiTopE->Write();

  
  h_HypToppTPrompt->Write();
  h_HypToppTTau->Write();
  
  //***********************************************************************
  
  h_hypbtogenb->GetXaxis()->SetTitle("N_{Jets}");
  h_hypbtogenb->Write();
 
  h_hypbtogenantib->GetXaxis()->SetTitle("N_{Jets}");
  h_hypbtogenantib->Write();
 
  h_hypantibtogenb->GetXaxis()->SetTitle("N_{Jets}");
  h_hypantibtogenb->Write();
  
  h_hypantibtogenantib->GetXaxis()->SetTitle("N_{Jets}");
  h_hypantibtogenantib->Write();

  h_genjettogenb->GetXaxis()->SetTitle("N_{Jets}");
  h_genjettogenb->Write();

  h_genjettogenantib->GetXaxis()->SetTitle("N_{Jets}");
  h_genjettogenantib->Write();


  h_recojettohypb->GetXaxis()->SetTitle("N_{Jets}");
  h_recojettohypb->Write();

  h_recojettohypantib->GetXaxis()->SetTitle("N_{Jets}");
  h_recojettohypantib->Write();

  h_recojettogenb->GetXaxis()->SetTitle("N_{Jets}");
  h_recojettogenb->Write();

  h_recojettogenantib->GetXaxis()->SetTitle("N_{Jets}");
  h_recojettogenantib->Write();

  h_recojettogenjet->GetXaxis()->SetTitle("N_{Jets}");
  h_recojettogenjet->Write();


  //** Triple Matching****
  h_hypbtogenjet->GetXaxis()->SetTitle("N_{Jets}");
  h_hypbtogenjet->Write();

  h_hypbtogenjettogenb->GetXaxis()->SetTitle("N_{Jets}");
  h_hypbtogenjettogenb->Write();

  h_hypbtogenjettogenantib->GetXaxis()->SetTitle("N_{Jets}");
  h_hypbtogenjettogenantib->Write();


  h_hypantibtogenjet->GetXaxis()->SetTitle("N_{Jets}");
  h_hypantibtogenjet->Write();

  h_hypantibtogenjettogenb->GetXaxis()->SetTitle("N_{Jets}");
  h_hypantibtogenjettogenb->Write();

  h_hypantibtogenjettogenantib->GetXaxis()->SetTitle("N_{Jets}");
  h_hypantibtogenjettogenantib->Write();

  h_deltargenjettogenb->GetXaxis()->SetTitle("#Delta R");
  h_deltargenjettogenb->Write();

  h_deltargenjettogenantib->GetXaxis()->SetTitle("#Delta R");
  h_deltargenjettogenantib->Write();

  h_deltarhypbtogenjet->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypbtogenjet->Write();

  h_deltarhypantibtogenjet->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypantibtogenjet->Write();

  h_deltarhypbtogenb->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypbtogenb->Write();

  h_deltarhypbtogenantib->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypbtogenantib->Write();

  h_deltarhypantibtogenb->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypantibtogenb->Write();

  h_deltarhypantibtogenantib->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypantibtogenantib->Write();
  
  h_deltarrecojettohypb->GetXaxis()->SetName("#Delta R");
  h_deltarrecojettohypb->Write();

  h_deltarrecojettohypantib->GetXaxis()->SetName("#Delta R");
  h_deltarrecojettohypantib->Write();

  h_deltarrecojettogenb->GetXaxis()->SetName("#Delta R");
  h_deltarrecojettogenb->Write();

  h_deltarrecojettogenantib->GetXaxis()->SetName("#Delta R");
  h_deltarrecojettogenantib->Write();

  h_deltarrecojettogenjet->GetXaxis()->SetTitle("#Delta R");
  h_deltarrecojettogenjet->Write();

  h_deltarrecojettorecojet->GetXaxis()->SetTitle("#Delta R");
  h_deltarrecojettorecojet->Write();

  h_deltargenjettogenjet->GetXaxis()->SetTitle("#Delta R");
  h_deltargenjettogenjet->Write();

  h_deltargenbtogenantib->GetXaxis()->SetTitle("#Delta R");
  h_deltargenbtogenantib->Write();

  h_deltarhypbtohypantib->GetXaxis()->SetTitle("#Delta R");
  h_deltarhypbtohypantib->Write();

  h_hypleptogenlep->Write();
  h_hypantileptogenlep->Write();
  h_hypleptogenantilep->Write();
  h_hypantileptogenantilep->Write();

  
  h_GenLeptonpTViaTau->Write();
  h_GenAntiLeptonpTViaTau->Write();
  h_HypLeptonpTViaTau->Write();
  h_HypAntiLeptonpTViaTau->Write();
  
  h_GenLeptonpTViaTauNC->Write();
  h_GenAntiLeptonpTViaTauNC->Write();
  h_HypLeptonpTViaTauNC->Write();
  h_HypAntiLeptonpTViaTauNC->Write();

  h_GenLeptonpTNC->Write();
  h_GenAntiLeptonpTNC->Write();
  h_HypLeptonpTNC->Write();
  h_HypAntiLeptonpTNC->Write();

  h_hypbptmatching->Write();
  h_hypbptnotmatching->Write();
  h_hypantibptmatching->Write();
  h_hypantibptnotmatching->Write();
  
  h_genbptmatching->Write();
  h_genbptnotmatching->Write();
  h_genantibptmatching->Write();
  h_genantibptnotmatching->Write();

  h_hypbetamatching->Write();
  h_hypbetanotmatching->Write();
  h_hypantibetamatching->Write();
  h_hypantibetanotmatching->Write();
  
  h_genbetamatching->Write();
  h_genbetanotmatching->Write();
  h_genantibetamatching->Write();
  h_genantibetanotmatching->Write();

  h_hypbematching->Write();
  h_hypbenotmatching->Write();
  h_hypantibematching->Write();
  h_hypantibenotmatching->Write();
  
  h_genbematching->Write();
  h_genbenotmatching->Write();
  h_genantibematching->Write();
  h_genantibenotmatching->Write();
  
  h_GenAntiBMRoot->Write();
  h_HypAntiBMRoot->Write();
  h_GenAntiBM->Write();
  h_HypAntiBM->Write();

  h_GenBMRoot->Write();
  h_HypBMRoot->Write();
  h_GenBM->Write();
  h_HypBM->Write();

  f->Close();
}
