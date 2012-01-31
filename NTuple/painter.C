#include <TSystem.h>
#include <iostream>
#include <TString.h>

void painter(){
  
  for (int i=0; i<3 ; i++){
    for (int j=0; j<5; j++){
      PainterMacro(i, j);
    }
  }

}


void PainterMacro(int chn=0, int algoNr=0)
{
  
  if (chn ==0)  {TString channel= TString("ee/");}
  else if (chn == 1){TString channel= TString("emu/");}
  else if (chn == 2){TString channel= TString("mumu/");}
  else {
    std::cout<<"Channel not valid, choose between: ee -> 0, emu -> 1, mumu -> 2"<<std::endl;
    return;
  };
  
  if (algoNr == 0) {TString algo=TString("TCHEL");}
  else if (algoNr == 1) {TString algo=TString("TCHEM");}
  else if (algoNr == 2) {TString algo=TString("TCHET");}
  else if (algoNr == 3) {TString algo=TString("SSVHEM");}
  else if (algoNr == 4) {TString algo=TString("SSVHET");}
  else {
    std::cout<<"b-Tagging algorithm NOT valid, choose between: TCHEL -> 0, TCHEM -> 1, TCHET -> 2, SSVHEM -> 3 or SSVHET -> 4"<<std::endl;
    return;
  }

  TString inpath=TString("selectionRoot/");	inpath.Append(algo).Append("/").Append(channel);
  TString outpath=TString("bMatchingPlots/");	gSystem->MakeDirectory(outpath);
  outpath.Append(algo);				gSystem->MakeDirectory(outpath);
  outpath.Append("/").Append(channel); 		gSystem->MakeDirectory(outpath);
 
  
  
  
 TFile *f=TFile::Open(inpath.Copy().Append("ttbarsignalplustau.root"));
 TCanvas c1;
 HypBToGenB->Draw();			HypBToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypBToGenB.eps"));
 HypBToGenAntiB->Draw();		HypBToGenAntiB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypBToGenAntiB.eps"));
 HypAntiBToGenB->Draw();		HypAntiBToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypAntiBToGenB.eps"));
 HypAntiBToGenAntiB->Draw();		HypAntiBToGenAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiBToGenAntiB.eps"));
 GenJetToGenB->Draw();			GenJetToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("GenJetToGenB.eps"));
 GenJetToGenAntiB->Draw();		GenJetToGenAntiB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("GenJetToGenAntiB.eps"));
 HypBToGenJet->Draw();			HypBToGenJet->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypBToGenJet.eps"));
 HypBToGenJetToGenB->Draw();		HypBToGenJetToGenB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypBToGenJetToGenB.eps"));
 HypBToGenJetToGenAntiB->Draw();	HypBToGenJetToGenAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypBToGenJetToGenAntiB.eps"));
 HypAntiBToGenJet->Draw();		HypAntiBToGenJet->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypAntiBToGenJet.eps"));
 HypAntiBToGenJetToGenB->Draw();	HypAntiBToGenJetToGenB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiBToGenJetToGenB.eps"));
 HypAntiBToGenJetToGenAntiB->Draw();	HypAntiBToGenJetToGenAntiB->Draw("SAME, TEXT00");c1.SaveAs(outpath.Copy().Append("HypAntiBToGenJetToGenAntiB.eps"));

 RecoJetToHypB->Draw();			RecoJetToHypB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("RecoJetToHypB.eps"));
 RecoJetToHypAntiB->Draw();		RecoJetToHypAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("RecoJetToHypAntiB.eps"));

 RecoJetToGenB->Draw();			RecoJetToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("RecoJetToGenB.eps"));
 RecoJetToGenAntiB->Draw();		RecoJetToGenAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("RecoJetToGenAntiB.eps"));
 RecoJetToGenJet->Draw();		RecoJetToGenJet->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("RecoJetToGenJet.eps"));
 HypLepToGenLep->Draw();		HypLepToGenLep->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypLepToGenLep.eps"));
 HypAntiLepToGenLep->Draw();		HypAntiLepToGenLep->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiLepToGenLep.eps"));
 HypLepToGenAntiLep->Draw();		HypLepToGenAntiLep->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypLepToGenAntiLep.eps"));
 HypAntiLepToGenAntiLep->Draw();	HypAntiLepToGenAntiLep->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiLepToGenAntiLep.eps"));
 
 
 DeltarGenJetToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarGenJetToGenB.eps"));
 DeltarGenJetToGenAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarGenJetToGenAntiB.eps"));
 DeltarHypBToGenJet->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToGenJet.eps"));
 DeltarHypAntiBToGenJet->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarHypAntiBToGenJet.eps"));
 DeltarHypBToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToGenB.eps"));
 DeltarHypBToGenAntiB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToGenAntiB.eps"));
 DeltarHypAntiBToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypAntiBToGenB.eps"));
 DeltarHypAntiBToGenAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarHypAntiBToGenAntiB.eps"));
 DeltarRecoJetToHypB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToHypB.eps"));
 DeltarRecoJetToHypAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToHypAntiB.eps"));
 DeltarRecoJetToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToGenB.eps"));
 DeltarRecoJetToGenAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToGenAntiB.eps"));
 DeltarRecoJetToGenJet->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToGenJet.eps"));
 DeltarGenBToGenAntiB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarGenBToGenAntiB.eps"));
 DeltarGenJetToGenJet->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarGenJetToGenJet.eps"));
 DeltarRecoJetToRecoJet->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToRecoJet.eps"));
 DeltarHypBToHypAntiB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToHypAntiB.eps"));
 
 //Quark property plots!!!!!
 HypBpT->Draw();	c1.SaveAs(outpath.Copy().Append("HypBpT.eps"));
 HypBEta->Draw();	c1.SaveAs(outpath.Copy().Append("HypBEta.eps"));
// HypBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("HypBPhi.eps"));
 HypBE->Draw();		c1.SaveAs(outpath.Copy().Append("HypBE.eps"));
 HypAntiBpT->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBpT.eps"));
 HypAntiBEta->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBEta.eps"));
// HypAntiBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBPhi.eps"));
 HypAntiBE->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBE.eps"));
//  RecoJetpT->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetpT.eps"));
//  RecoJetEta->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetEta.eps"));
//  RecoJetPhi->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetPhi.eps"));
//  RecoJetE->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetE.eps"));
 GenBpT->Draw();	c1.SaveAs(outpath.Copy().Append("GenBpT.eps"));
 GenBEta->Draw();	c1.SaveAs(outpath.Copy().Append("GenBEta.eps"));
// GenBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("GenBPhi.eps"));
 GenBE->Draw();		c1.SaveAs(outpath.Copy().Append("GenBE.eps"));
 GenAntiBpT->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBpT.eps"));
 GenAntiBEta->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBEta.eps"));
// GenAntiBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBPhi.eps"));
 GenAntiBE->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBE.eps"));
//  GenJetpT->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetpT.eps"));
//  GenJetEta->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetEta.eps"));
//  GenJetPhi->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetPhi.eps"));
//  GenJetE->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetE.eps"));

 
 HypAntiBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBpTNotMatching.eps"));
 HypAntiBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBpTMatching.eps"));
 HypBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBpTNotMatching.eps"));
 HypBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBpTMatching.eps"));

 GenAntiBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBpTNotMatching.eps"));
 GenAntiBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBpTMatching.eps"));
 GenBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBpTNotMatching.eps"));
 GenBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBpTMatching.eps"));
 
 HypAntiBEtaNotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("HypAntiBEtaNotMatching.eps"));
 HypAntiBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBEtaMatching.eps"));
 HypBEtaNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBEtaNotMatching.eps"));
 HypBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBEtaMatching.eps"));

 GenAntiBEtaNotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("GenAntiBEtaNotMatching.eps"));
 GenAntiBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBEtaMatching.eps"));
 GenBEtaNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBEtaNotMatching.eps"));
 GenBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBEtaMatching.eps"));

 HypAntiBENotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("HypAntiBENotMatching.eps"));
 HypAntiBEMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBEMatching.eps"));
 HypBENotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBENotMatching.eps"));
 HypBEMatching->Draw();	        	c1.SaveAs(outpath.Copy().Append("HypBEMatching.eps"));

 GenAntiBENotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("GenAntiBENotMatching.eps"));
 GenAntiBEMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBEMatching.eps"));
 GenBENotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBENotMatching.eps"));
 GenBEMatching->Draw();	        	c1.SaveAs(outpath.Copy().Append("GenBEMatching.eps"));


 c1.SetLogy();
 
 HypBToGenB->Draw();			HypBToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypBToGenBLog.eps"));
 HypBToGenAntiB->Draw();		HypBToGenAntiB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypBToGenAntiBLog.eps"));
 HypAntiBToGenB->Draw();		HypAntiBToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypAntiBToGenBLog.eps"));
 HypAntiBToGenAntiB->Draw();		HypAntiBToGenAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiBToGenAntiBLog.eps"));
 GenJetToGenB->Draw();			GenJetToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("GenJetToGenBLog.eps"));
 GenJetToGenAntiB->Draw();		GenJetToGenAntiB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("GenJetToGenAntiBLog.eps"));
 HypBToGenJet->Draw();			HypBToGenJet->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypBToGenJetLog.eps"));
 HypBToGenJetToGenB->Draw();		HypBToGenJetToGenB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypBToGenJetToGenBLog.eps"));
 HypBToGenJetToGenAntiB->Draw();	HypBToGenJetToGenAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypBToGenJetToGenAntiBLog.eps"));
 HypAntiBToGenJet->Draw();		HypAntiBToGenJet->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypAntiBToGenJetLog.eps"));
 HypAntiBToGenJetToGenB->Draw();	HypAntiBToGenJetToGenB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiBToGenJetToGenBLog.eps"));
 HypAntiBToGenJetToGenAntiB->Draw();	HypAntiBToGenJetToGenAntiB->Draw("SAME, TEXT00");c1.SaveAs(outpath.Copy().Append("HypAntiBToGenJetToGenAntiBLog.eps"));

 RecoJetToHypB->Draw();			RecoJetToHypB->Draw("SAME, TEXT00");			c1.SaveAs(outpath.Copy().Append("RecoJetToHypBLog.eps"));
 RecoJetToHypAntiB->Draw();			RecoJetToHypAntiB->Draw("SAME, TEXT00");			c1.SaveAs(outpath.Copy().Append("RecoJetToHypAntiBLog.eps"));

 RecoJetToGenB->Draw();			RecoJetToGenB->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("RecoJetToGenBLog.eps"));
 RecoJetToGenAntiB->Draw();		RecoJetToGenAntiB->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("RecoJetToGenAntiBLog.eps"));
 RecoJetToGenJet->Draw();		RecoJetToGenJet->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("RecoJetToGenJetLog.eps"));
 HypLepToGenLep->Draw();		HypLepToGenLep->Draw("SAME, TEXT00");		c1.SaveAs(outpath.Copy().Append("HypLepToGenLepLog.eps"));
 HypAntiLepToGenLep->Draw();		HypAntiLepToGenLep->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiLepToGenLepLog.eps"));
 HypLepToGenAntiLep->Draw();		HypLepToGenAntiLep->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypLepToGenAntiLepLog.eps"));
 HypAntiLepToGenAntiLep->Draw();	HypAntiLepToGenAntiLep->Draw("SAME, TEXT00");	c1.SaveAs(outpath.Copy().Append("HypAntiLepToGenAntiLepLog.eps"));
 
 
 DeltarGenJetToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarGenJetToGenBLog.eps"));
 DeltarGenJetToGenAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarGenJetToGenAntiBLog.eps"));
 DeltarHypBToGenJet->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToGenJetLog.eps"));
 DeltarHypAntiBToGenJet->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarHypAntiBToGenJetLog.eps"));
 DeltarHypBToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToGenBLog.eps"));
 DeltarHypBToGenAntiB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToGenAntiBLog.eps"));
 DeltarHypAntiBToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypAntiBToGenBLog.eps"));
 DeltarHypAntiBToGenAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarHypAntiBToGenAntiBLog.eps"));
 DeltarRecoJetToHypB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToHypBLog.eps"));
 DeltarRecoJetToHypAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToHypAntiBLog.eps"));
 DeltarRecoJetToGenB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToGenBLog.eps"));
 DeltarRecoJetToGenAntiB->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToGenAntiBLog.eps"));
 DeltarRecoJetToGenJet->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToGenJetLog.eps"));
 DeltarGenBToGenAntiB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarGenBToGenAntiBLog.eps"));
 DeltarGenJetToGenJet->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarGenJetToGenJetLog.eps"));
 DeltarRecoJetToRecoJet->Draw();	c1.SaveAs(outpath.Copy().Append("DeltarRecoJetToRecoJetLog.eps"));
 DeltarHypBToHypAntiB->Draw();		c1.SaveAs(outpath.Copy().Append("DeltarHypBToHypAntiBLog.eps"));
 
 //Quark property plots!!!!!
 HypBpT->Draw();	c1.SaveAs(outpath.Copy().Append("HypBpTLog.eps"));
 HypBEta->Draw();	c1.SaveAs(outpath.Copy().Append("HypBEtaLog.eps"));
 //HypBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("HypBPhiLog.eps"));
 HypBE->Draw();		c1.SaveAs(outpath.Copy().Append("HypBELog.eps"));
 HypAntiBpT->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBpTLog.eps"));
 HypAntiBEta->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBEtaLog.eps"));
 //HypAntiBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBPhiLog.eps"));
 HypAntiBE->Draw();	c1.SaveAs(outpath.Copy().Append("HypAntiBELog.eps"));
//  RecoJetpT->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetpTLog.eps"));
//  RecoJetEta->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetEtaLog.eps"));
//  RecoJetPhi->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetPhiLog.eps"));
//  RecoJetE->Draw();	c1.SaveAs(outpath.Copy().Append("RecoJetELog.eps"));
 GenBpT->Draw();	c1.SaveAs(outpath.Copy().Append("GenBpTLog.eps"));
 GenBEta->Draw();	c1.SaveAs(outpath.Copy().Append("GenBEtaLog.eps"));
 //GenBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("GenBPhiLog.eps"));
 GenBE->Draw();		c1.SaveAs(outpath.Copy().Append("GenBELog.eps"));
 GenAntiBpT->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBpTLog.eps"));
 GenAntiBEta->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBEtaLog.eps"));
 //GenAntiBPhi->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBPhiLog.eps"));
 GenAntiBE->Draw();	c1.SaveAs(outpath.Copy().Append("GenAntiBELog.eps"));
//  GenJetpT->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetpTLog.eps"));
//  GenJetEta->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetEtaLog.eps"));
//  GenJetPhi->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetPhiLog.eps"));
//  GenJetE->Draw();	c1.SaveAs(outpath.Copy().Append("GenJetELog.eps"));

 HypAntiBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBpTNotMatchingLog.eps"));
 HypAntiBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBpTMatchingLog.eps"));
 HypBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBpTNotMatchingLog.eps"));
 HypBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBpTMatchingLog.eps"));

 GenAntiBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBpTNotMatchingLog.eps"));
 GenAntiBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBpTMatchingLog.eps"));
 GenBpTNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBpTNotMatchingLog.eps"));
 GenBpTMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBpTMatchingLog.eps"));
 
 HypAntiBEtaNotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("HypAntiBEtaNotMatchingLog.eps"));
 HypAntiBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBEtaMatchingLog.eps"));
 HypBEtaNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBEtaNotMatchingLog.eps"));
 HypBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBEtaMatchingLog.eps"));

 GenAntiBEtaNotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("GenAntiBEtaNotMatchingLog.eps"));
 GenAntiBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBEtaMatchingLog.eps"));
 GenBEtaNotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBEtaNotMatchingLog.eps"));
 GenBEtaMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBEtaMatchingLog.eps"));


 HypAntiBENotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("HypAntiBENotMatchingLog.eps"));
 HypAntiBEMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypAntiBEMatchingLog.eps"));
 HypBENotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("HypBENotMatchingLog.eps"));
 HypBEMatching->Draw();	        	c1.SaveAs(outpath.Copy().Append("HypBEMatchingLog.eps"));

 GenAntiBENotMatching->Draw();       	c1.SaveAs(outpath.Copy().Append("GenAntiBENotMatchingLog.eps"));
 GenAntiBEMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenAntiBEMatchingLog.eps"));
 GenBENotMatching->Draw();		c1.SaveAs(outpath.Copy().Append("GenBENotMatchingLog.eps"));
 GenBEMatching->Draw();	        	c1.SaveAs(outpath.Copy().Append("GenBEMatchingLog.eps"));

 
 
 
 c1.Close();
 f->Close();


 

 TFile *f=TFile::Open(inpath.Copy().Append("ttbarsignalplustau.root"));
 TCanvas c1;
 
 c1.SetLogy();
 DeltarHypBToGenB->Scale(1.0/DeltarHypBToGenB->Integral());                DeltarHypBToGenB->SetLineColor(kGreen);       DeltarHypBToGenB->SetMarkerStyle(20);        DeltarHypBToGenB->SetMarkerColor(kGreen);
 DeltarHypBToGenAntiB->Scale(1.0/DeltarHypBToGenAntiB->Integral());        DeltarHypBToGenAntiB->SetLineColor(kRed);     DeltarHypBToGenAntiB->SetMarkerStyle(21);    DeltarHypBToGenAntiB->SetMarkerColor(kRed);
 DeltarHypAntiBToGenB->Scale(1.0/DeltarHypAntiBToGenB->Integral());        DeltarHypAntiBToGenB->SetLineColor(kBlack);   DeltarHypAntiBToGenB->SetMarkerStyle(22);    DeltarHypAntiBToGenB->SetMarkerColor(kBlack);
 DeltarHypAntiBToGenAntiB->Scale(1.0/DeltarHypAntiBToGenAntiB->Integral());DeltarHypAntiBToGenAntiB->SetLineColor(kBlue);DeltarHypAntiBToGenAntiB->SetMarkerStyle(34);DeltarHypAntiBToGenAntiB->SetMarkerColor(kBlue);
 
 TLegend *l1=new TLegend(0.65, 0.65, 0.95, 0.95);
 l1->AddEntry(DeltarHypBToGenB, "HypBToGenB", "pl");
 l1->AddEntry(DeltarHypBToGenAntiB, "HypBToGenAntiB", "pl");
 l1->AddEntry(DeltarHypAntiBToGenB, "HypAntiBToGenB", "pl");
 l1->AddEntry(DeltarHypAntiBToGenAntiB, "HypAntiBToGenAntiB", "pl");

 DeltarHypBToGenB->Draw("");    DeltarHypBToGenAntiB->Draw("same");    l1->Draw("same");c1.SaveAs(outpath.Copy().Append("DeltaRComp1Log.eps"));
 DeltarHypAntiBToGenAntiB->SetMaximum(1.0);
 DeltarHypAntiBToGenAntiB->Draw("");DeltarHypAntiBToGenB->Draw("same");l1->Draw("same");c1.SaveAs(outpath.Copy().Append("DeltaRComp2Log.eps"));
 DeltarHypBToGenAntiB->Draw("");DeltarHypAntiBToGenB->Draw("same");    l1->Draw("same");c1.SaveAs(outpath.Copy().Append("DeltaRComp3Log.eps"));
 DeltarHypBToGenB->Draw("");    DeltarHypAntiBToGenAntiB->Draw("same");l1->Draw("same");c1.SaveAs(outpath.Copy().Append("DeltaRComp4Log.eps"));

 GenBpT->Scale(1.0/GenBpT->Integral());        GenBpT->SetLineColor(kRed);
 GenAntiBpT->Scale(1.0/GenAntiBpT->Integral());GenAntiBpT->SetLineColor(kGreen);
 HypBpT->Scale(1.0/HypBpT->Integral());        HypBpT->SetLineColor(kBlack);
 HypAntiBpT->Scale(1.0/HypAntiBpT->Integral()); HypAntiBpT->SetLineColor(kBlue);

 GenBEta->Scale(1.0/GenBEta->Integral());        GenBEta->SetLineColor(kRed);
 GenAntiBEta->Scale(1.0/GenAntiBEta->Integral());GenAntiBEta->SetLineColor(kGreen);
 HypBEta->Scale(1.0/HypBEta->Integral());        HypBEta->SetLineColor(kBlack);
 HypAntiBEta->Scale(1.0/HypAntiBEta->Integral()); HypAntiBEta->SetLineColor(kBlue);

/*
 GenBPhi->Scale(1.0/GenBPhi->Integral());        GenBPhi->SetLineColor(kRed);
 GenAntiBPhi->Scale(1.0/GenAntiBPhi->Integral());GenAntiBPhi->SetLineColor(kGreen);
 HypBPhi->Scale(1.0/HypBPhi->Integral());        HypBPhi->SetLineColor(kBlack);
 HypAntiBPhi->Scale(1.0/HypAntiBPhi->Integral()); HypAntiBPhi->SetLineColor(kBlue);
*/

 GenBE->Scale(1.0/GenBE->Integral());        GenBE->SetLineColor(kRed);
 GenAntiBE->Scale(1.0/GenAntiBE->Integral());GenAntiBE->SetLineColor(kGreen);
 HypBE->Scale(1.0/HypBE->Integral());        HypBE->SetLineColor(kBlack);
 HypAntiBE->Scale(1.0/HypAntiBE->Integral()); HypAntiBE->SetLineColor(kBlue);


 TLegend *l2= new TLegend(0.8, 0.8, 0.975, 0.975);
 l2->AddEntry(GenBpT, "GenB", "l");
 l2->AddEntry(GenAntiBpT, "GenAntiB", "l");
 l2->AddEntry(HypBpT, "HypB", "l");
 l2->AddEntry(HypAntiBpT, "HypAntiB", "l");

 GenBpT->Draw(); GenAntiBpT->Draw("same"); HypBpT->Draw("same"); HypAntiBpT->Draw("same"), l2->Draw("same");
 c1.SaveAs(outpath.Copy().Append("QuarkComparisonPt.eps"));

 GenBE->Draw();  GenAntiBE->Draw("same");  HypBE->Draw("same");  HypAntiBE->Draw("same"), l2->Draw("same");
 c1.SaveAs(outpath.Copy().Append("QuarkComparisonE.eps"));

 c1.SetLogy(0);
 
 GenBEta->SetMaximum(0.085);
 GenBEta->Draw();GenAntiBEta->Draw("same");HypBEta->Draw("same");HypAntiBEta->Draw("same"), l2->Draw("same");
 c1.SaveAs(outpath.Copy().Append("QuarkComparisonEta.eps"));

// GenBPhi->Draw();GenAntiBPhi->Draw("same");HypBPhi->Draw("same");HypAntiBPhi->Draw("same"), l2->Draw("same");
// c1.SaveAs(outpath.Copy().Append("QuarkComparisonPhi.eps"));

 TH1D *h1=(TH1D*)f->Get("HypAntiBpTNotMatching");	h1->SetLineStyle(2);	h1->SetMarkerStyle(20);	double sh1 = h1->Integral(); h1->Scale(1./sh1);
 TH1D *h2=(TH1D*)f->Get("HypBpTNotMatching");		h2->SetLineStyle(2);	h2->SetMarkerStyle(20);	double sh2 = h2->Integral(); h2->Scale(1./sh2);
 TH1D *h3=(TH1D*)f->Get("HypAntiBpTMatching");		h3->SetLineStyle(1);	h3->SetMarkerStyle(21);	double sh3 = h3->Integral(); h3->Scale(1./sh3);
 TH1D *h4=(TH1D*)f->Get("HypBpTMatching");		h4->SetLineStyle(1);	h4->SetMarkerStyle(21);	double sh4 = h4->Integral(); h4->Scale(1./sh4);
 
 TLegend *l3= new TLegend(0.7, 0.7, 0.975, 0.975);
 l3->AddEntry(h1, "Not Matching Distr.", "l");
 l3->AddEntry(h3, "Matching Distr.", "l");

 c1.SetLogy(0);
 h1->Draw("");	 h3->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("HypAntiBpTDiffMatching.eps"));
 h1->Scale(sh1); h3->Scale(sh3);
 h1->Divide(h3); h1->SetMaximum(1.5);	h1->Draw();	  c1.SaveAs(outpath.Copy().Append("HypAntiBpTDiffMatchingRatio.eps"));
 h2->Draw("");	 h4->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("HypBpTDiffMatching.eps"));
 h2->Scale(sh2); h4->Scale(sh4);
 h2->Divide(h4); h2->SetMaximum(1.5);	h2->Draw();	  c1.SaveAs(outpath.Copy().Append("HypBpTDiffMatchingRatio.eps"));


 h1 = (TH1D*)f->Get("GenAntiBpTNotMatching");	h1->SetLineStyle(2);	h1->SetMarkerStyle(20);	double sh1 = h1->Integral(); h1->Scale(1./sh1);
 h2 = (TH1D*)f->Get("GenBpTNotMatching");	h2->SetLineStyle(2);	h2->SetMarkerStyle(20);	double sh2 = h2->Integral(); h2->Scale(1./sh2);
 h3 = (TH1D*)f->Get("GenAntiBpTMatching");	h3->SetLineStyle(1);	h3->SetMarkerStyle(21);	double sh3 = h3->Integral(); h3->Scale(1./sh3);
 h4 = (TH1D*)f->Get("GenBpTMatching");		h4->SetLineStyle(1);	h4->SetMarkerStyle(21);	double sh4 = h4->Integral(); h4->Scale(1./sh4);

 h1->Draw();	 h3->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("GenAntiBpTDiffMatching.eps"));
 h1->Scale(sh1); h3->Scale(sh3);
 h1->Divide(h3); h1->SetMaximum(1.5);	h1->Draw();	  c1.SaveAs(outpath.Copy().Append("GenAntiBpTDiffMatchingRatio.eps"));
 h2->Draw();	 h4->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("GenBpTDiffMatching.eps"));
 h2->Scale(sh2); h4->Scale(sh4);
 h2->Divide(h4); h2->SetMaximum(1.5);	h2->Draw();	  c1.SaveAs(outpath.Copy().Append("GenBpTDiffMatchingRatio.eps"));


 h1 = (TH1D*)f->Get("HypAntiBEtaNotMatching"); h1->SetLineStyle(2); double sh1 = h1->Integral(); h1->Scale(1./sh1);
 h2 = (TH1D*)f->Get("HypBEtaNotMatching");     h2->SetLineStyle(2); double sh2 = h2->Integral(); h2->Scale(1./sh2);
 h3 = (TH1D*)f->Get("HypAntiBEtaMatching");    h3->SetLineStyle(1);  double sh3 = h3->Integral(); h3->Scale(1./sh3);
 h4 = (TH1D*)f->Get("HypBEtaMatching");        h4->SetLineStyle(1);  double sh4 = h4->Integral(); h4->Scale(1./sh4);

 h1->Draw();	 h3->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("HypAntiBEtaDiffMatching.eps"));
 h1->Scale(sh1); h3->Scale(sh3);
 h1->Divide(h3); h1->SetMaximum(1.5);	h1->Draw();	  c1.SaveAs(outpath.Copy().Append("HypAntiBEtaDiffMatchingRatio.eps"));
 h2->Draw();	 h4->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("HypBEtaDiffMatching.eps"));
 h2->Scale(sh2); h4->Scale(sh4);
 h2->Divide(h4); h2->SetMaximum(1.5);	h2->Draw();	  c1.SaveAs(outpath.Copy().Append("HypBEtaDiffMatchingRatio.eps"));


 
 h1 = (TH1D*)f->Get("GenAntiBEtaNotMatching"); h1->SetLineStyle(2); double sh1 = h1->Integral(); h1->Scale(1./sh1);
 h2 = (TH1D*)f->Get("GenBEtaNotMatching");     h2->SetLineStyle(2); double sh2 = h2->Integral(); h2->Scale(1./sh2);
 h3 = (TH1D*)f->Get("GenAntiBEtaMatching");    h3->SetLineStyle(1);  double sh3 = h3->Integral(); h3->Scale(1./sh3);
 h4 = (TH1D*)f->Get("GenBEtaMatching");        h4->SetLineStyle(1);  double sh4 = h4->Integral(); h4->Scale(1./sh4);

 h3->Draw();	 h1->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("GenAntiBEtaDiffMatching.eps"));
 h1->Scale(sh1); h3->Scale(sh3);
 h1->Divide(h3); h1->SetMaximum(1.5);	h1->Draw();	  c1.SaveAs(outpath.Copy().Append("GenAntiBEtaDiffMatchingRatio.eps"));
 h4->Draw();	 h2->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("GenBEtaDiffMatching.eps"));
 h2->Scale(sh2); h4->Scale(sh4);
 h2->Divide(h4); h2->SetMaximum(1.5);	h2->Draw();	  c1.SaveAs(outpath.Copy().Append("GenBEtaDiffMatchingRatio.eps"));




 h1 = (TH1D*)f->Get("HypAntiBENotMatching"); h1->SetLineStyle(2); double sh1 = h1->Integral(); h1->Scale(1./sh1);
 h2 = (TH1D*)f->Get("HypBENotMatching");     h2->SetLineStyle(2); double sh2 = h2->Integral(); h2->Scale(1./sh2);
 h3 = (TH1D*)f->Get("HypAntiBEMatching");    h3->SetLineStyle(1);  double sh3 = h3->Integral(); h3->Scale(1./sh3);
 h4 = (TH1D*)f->Get("HypBEMatching");        h4->SetLineStyle(1);  double sh4 = h4->Integral(); h4->Scale(1./sh4);

 h1->Draw();	 h3->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("HypAntiBEDiffMatching.eps"));
 h1->Scale(sh1); h3->Scale(sh3);
 h1->Divide(h3); h1->SetMaximum(1.5);	h1->Draw();	  c1.SaveAs(outpath.Copy().Append("HypAntiBEDiffMatchingRatio.eps"));
 h2->Draw();	 h4->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("HypBEDiffMatching.eps"));
 h2->Scale(sh2); h4->Scale(sh4);
 h2->Divide(h4); h2->SetMaximum(1.5);	h2->Draw();	  c1.SaveAs(outpath.Copy().Append("HypBEDiffMatchingRatio.eps"));



 
 h1 = (TH1D*)f->Get("GenAntiBENotMatching"); h1->SetLineStyle(2); double sh1 = h1->Integral(); h1->Scale(1./sh1);
 h2 = (TH1D*)f->Get("GenBENotMatching");     h2->SetLineStyle(2); double sh2 = h2->Integral(); h2->Scale(1./sh2);
 h3 = (TH1D*)f->Get("GenAntiBEMatching");    h3->SetLineStyle(1);  double sh3 = h3->Integral(); h3->Scale(1./sh3);
 h4 = (TH1D*)f->Get("GenBEMatching");        h4->SetLineStyle(1);  double sh4 = h4->Integral(); h4->Scale(1./sh4);

 h1->Draw();	 h3->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("GenAntiBEDiffMatching.eps"));
 h1->Scale(sh1); h3->Scale(sh3);
 h1->Divide(h3); h1->SetMaximum(1.5);	h1->Draw();	  c1.SaveAs(outpath.Copy().Append("GenAntiBEDiffMatchingRatio.eps"));
 h2->Draw();	 h4->Draw("same");	l3->Draw("same"); c1.SaveAs(outpath.Copy().Append("GenBEDiffMatching.eps"));
 h2->Scale(sh2); h4->Scale(sh4);
 h2->Divide(h4); h2->SetMaximum(1.5);	h2->Draw();	  c1.SaveAs(outpath.Copy().Append("GenBEDiffMatchingRatio.eps"));

 
 c1.Close();
 f->Close();

 
}
