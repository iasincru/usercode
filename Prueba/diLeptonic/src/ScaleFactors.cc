#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <sstream>

#include <TSystem.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2.h>
#include <TSelectorList.h>
#include <TString.h>
#include <TObjArray.h>
#include <TRandom3.h>
#include <Rtypes.h>
#include <TMath.h>

#include "ScaleFactors.h"
#include "classes.h"
#include "utils.h"










std::string ttbar::assignFolder(const char* baseDir, const TString& channel, const TString& systematic)
{
    std::string path("");
    
    // Create all subdirectories contained in baseDir
    TObjArray* a_subDir = TString(baseDir).Tokenize("/");
    for(Int_t iSubDir = 0; iSubDir < a_subDir->GetEntriesFast(); ++iSubDir){
        const TString& subDir = a_subDir->At(iSubDir)->GetName();
        path.append(subDir);
        path.append("/");
        gSystem->MakeDirectory(path.c_str());
    }
    
    // Create subdirectories for systematic and channel
    path.append(systematic);
    path.append("/");
    gSystem->MakeDirectory(path.c_str());
    path.append(channel);
    path.append("/");
    gSystem->MakeDirectory(path.c_str());
    
    return path;
}



std::string ttbar::accessFolder(const char* baseDir, const TString& channel,
                         const TString& systematic, const bool allowNonexisting)
{
    // Build directory path
    std::string path(baseDir);
    path.append("/");
    path.append(systematic);
    path.append("/");
    path.append(channel);
    path.append("/");
    
    // Check if directory really exists
    if(!gSystem->OpenDirectory(path.c_str())){
        if(allowNonexisting){
            // It is allowed to request a folder which does not exist, so return empty string silently
            return "";
        }
        else{
            std::cerr<<"ERROR! Request to access directory is not possible, because it does not exist. Directory name: "<<path
                     <<"\n...break\n"<<std::endl;
            exit(237);
        }
    }
    
    return path;
}







double ScaleFactorHelpers::get2DSF(TH2* histo, const double x, const double y)
{
    int xbin, ybin, dummy;
    histo->GetBinXYZ(histo->FindBin(x, y), xbin, ybin, dummy);
    //overflow to last bin
    xbin = std::min(xbin, histo->GetNbinsX());
    ybin = std::min(ybin, histo->GetNbinsY());
    return histo->GetBinContent(xbin, ybin);
}



double ScaleFactorHelpers::median(TH1* h1)
{ 
   int nBin = h1->GetXaxis()->GetNbins();
   std::vector<double> x(nBin);
   h1->GetXaxis()->GetCenter(&x[0]);
   TH1D* h1D = dynamic_cast<TH1D*>(h1);
   if(!h1D){
       std::cerr << "Median needs a TH1D!\n";
       exit(7);
   }
   const double* y = h1D->GetArray(); 
   // exclude underflow/overflows from bin content array y
   return TMath::Median(nBin, &x[0], &y[1]); 
}













// --------------------------- Methods for LeptonScaleFactors ---------------------------------------------



LeptonScaleFactors::LeptonScaleFactors(const char* electronSFInputFileName,
                                       const char* muonSFInputFileName,
                                       const LeptonScaleFactors::Systematic& systematic):
h2_ElectronIDSFpteta(0),
h2_MuonIDSFpteta(0)
{
    std::cout<<"--- Beginning preparation of lepton scale factors\n";
    
    for(const auto& lepton : {electron, muon}){
        std::string inputFileName(ttbar::DATA_PATH());
        inputFileName.append("/");
        std::string histogramName;
        if(lepton == electron){
            inputFileName.append(electronSFInputFileName);
            histogramName = "ElectronSFtop12028";
            h2_ElectronIDSFpteta = this->prepareLeptonIDSF(inputFileName, histogramName, systematic);
        }
        else if(lepton == muon){
            inputFileName.append(muonSFInputFileName);
            histogramName = "MuonSFtop12028";
            h2_MuonIDSFpteta = this->prepareLeptonIDSF(inputFileName, histogramName, systematic);
        }
    }
    
    const bool electronInputFound(h2_ElectronIDSFpteta);
    const bool muonInputFound(h2_MuonIDSFpteta);
    if(electronInputFound || muonInputFound){
        std::cout<<"Found lepton Id/Iso scale factors for: ";
        if(electronInputFound) std::cout<<"electron , ";
        if(muonInputFound) std::cout<<"muon , ";
        std::cout<<std::endl;
    }
    if(!electronInputFound || !muonInputFound){
        std::cout<<"Could NOT find lepton Id/Iso scale factors for: ";
        if(!electronInputFound) std::cout<<"electron , ";
        if(!muonInputFound) std::cout<<"muon , ";
        std::cout<<std::endl;
    }
    std::cout<<"=== Finishing preparation of lepton scale factors\n\n";
}



TH2* LeptonScaleFactors::prepareLeptonIDSF(const std::string& inputFileName,
                                           const std::string& histogramName,
                                           const LeptonScaleFactors::Systematic& systematic)const
{
    // Access file containing scale factors
    TFile scaleFactorFile(inputFileName.c_str());
    if (scaleFactorFile.IsZombie()){
        std::cout<<"File containing lepton Id/Iso scale factors not found: "<<inputFileName
                 <<"\nAssuming ScaleFactor = 1.\n";
        return 0;
    }
    
    // Access histogram containing scale factors
    TH2* h_scaleFactorPtEta(0);
    h_scaleFactorPtEta = dynamic_cast<TH2*>(scaleFactorFile.Get(histogramName.c_str()));
    if(!h_scaleFactorPtEta){
        std::cout<<"TH2 for lepton Id/Iso scale factors not found: "<<histogramName
                 <<"\nAssuming ScaleFactor = 1.\n";
        return 0;
    }
    
    // Apply systematic variations
    if(systematic != nominal){
        double factor(0.);
        if(systematic == vary_up) factor = 1.;
        else if(systematic == vary_down) factor = -1.;
        else{
            std::cerr<<"ERROR in LeptonScaleFactors! Systematic with undefined behaviour requested\n...break\n"<<std::endl;
            exit(21);
        }
        
        for (int i = 1; i <= h_scaleFactorPtEta->GetNbinsX(); ++i) {
            for (int j = 1; j <= h_scaleFactorPtEta->GetNbinsY(); ++j) {
                h_scaleFactorPtEta->SetBinContent(i, j,
                    h_scaleFactorPtEta->GetBinContent(i,j) + factor*h_scaleFactorPtEta->GetBinError(i,j));
            }
        }
    }
    
    // Store histogram in memory and close file
    h_scaleFactorPtEta->SetDirectory(0);
    scaleFactorFile.Close();
    
    return h_scaleFactorPtEta;
}



double LeptonScaleFactors::getLeptonIDSF(const int leadingLeptonIndex, const int nLeadingLeptonIndex,
                                         const VLV& leptons, const std::vector<int>& lepPdgIds)const
{
    if(!h2_ElectronIDSFpteta || !h2_MuonIDSFpteta) return 1.;
    
    const LV& leadingLepton(leptons.at(leadingLeptonIndex));
    const LV& nLeadingLepton(leptons.at(nLeadingLeptonIndex));
    const int leadingPdgId(std::abs(lepPdgIds.at(leadingLeptonIndex)));
    const int nLeadingPdgId(std::abs(lepPdgIds.at(nLeadingLeptonIndex)));
    
    if(leadingPdgId==11 && nLeadingPdgId==11)
        return ScaleFactorHelpers::get2DSF(h2_ElectronIDSFpteta, leadingLepton.Eta(), leadingLepton.pt()) *
               ScaleFactorHelpers::get2DSF(h2_ElectronIDSFpteta, nLeadingLepton.Eta(), nLeadingLepton.pt());
    if(leadingPdgId==13 && nLeadingPdgId==13)
        return ScaleFactorHelpers::get2DSF(h2_MuonIDSFpteta, leadingLepton.Eta(), leadingLepton.pt()) *
               ScaleFactorHelpers::get2DSF(h2_MuonIDSFpteta, nLeadingLepton.Eta(), nLeadingLepton.pt());
    if(leadingPdgId==13 && nLeadingPdgId==11)
        return ScaleFactorHelpers::get2DSF(h2_MuonIDSFpteta, leadingLepton.Eta(), leadingLepton.pt()) *
               ScaleFactorHelpers::get2DSF(h2_ElectronIDSFpteta, nLeadingLepton.Eta(), nLeadingLepton.pt());
    if(leadingPdgId==11 && nLeadingPdgId==13)
        return ScaleFactorHelpers::get2DSF(h2_ElectronIDSFpteta, leadingLepton.Eta(), leadingLepton.pt()) *
               ScaleFactorHelpers::get2DSF(h2_MuonIDSFpteta, nLeadingLepton.Eta(), nLeadingLepton.pt());
    std::cout<<"WARNING in method getLeptonIDSF! LeptonPdgIds are not as expected (pdgId1, pdgId2): "
             <<leadingPdgId<<" , "<<nLeadingPdgId<<"\n...will return scale factor = 1.\n";
    return 1.;
}













// --------------------------- Methods for TriggerScaleFactors ---------------------------------------------



TriggerScaleFactors::TriggerScaleFactors(const char* inputFileSuffix,
                                         const std::vector<std::string>& channels,
                                         const Systematic& systematic):
h2_eeTrigSFeta(0),
h2_emuTrigSFeta(0),
h2_mumuTrigSFeta(0)
{
    std::cout<<"--- Beginning preparation of trigger scale factors\n";
    
    bool someChannelFound(false);
    bool someChannelNotFound(false);
    std::stringstream channelsFound;
    std::stringstream channelsNotFound;
    
    std::vector<TString> triggerInputFileNames;
    for(const auto& channel : channels){
        TString fullName(ttbar::DATA_PATH());
        fullName.Append("/triggerSummary_");
        fullName.Append(channel);
        fullName.Append(inputFileSuffix);
        triggerInputFileNames.push_back(fullName);
        TH2* h2_triggerSF = this->prepareTriggerSF(fullName, systematic);
        if(channel == "ee") h2_eeTrigSFeta = h2_triggerSF;
        else if(channel == "emu") h2_emuTrigSFeta = h2_triggerSF;
        else if(channel == "mumu") h2_mumuTrigSFeta = h2_triggerSF;
        else{
            std::cerr<<"ERROR in TriggerScaleFactors! Invalid channel requested: "<<channel<<"\n...break\n"<<std::endl;
            exit(23);
        }
        if(h2_triggerSF){
            someChannelFound = true;
            channelsFound<<channel<<" , ";
        }
        else{
            someChannelNotFound = true;
            channelsNotFound<<channel<<" , ";
        }
    }
    
    if(someChannelFound) std::cout<<"Found trigger scale factors for requested channels: "<<channelsFound.str()<<"\n";
    if(someChannelNotFound)  std::cout<<"Could NOT find trigger scale factors for requested channels: "<<channelsNotFound.str()<<"\n";
    std::cout<<"=== Finishing preparation of trigger scale factors\n\n";
}



TH2* TriggerScaleFactors::prepareTriggerSF(const TString& fileName, const Systematic& systematic)const
{
    TFile trigEfficiencies(fileName);
    if(trigEfficiencies.IsZombie()){
        std::cout << "Trigger efficiencies not found. Assuming ScaleFactor = 1.\n";
        std::cout << "Currently triggerEfficieny files can be found in diLeptonic/data folder\n\n";
        return 0;
    }
    
    //Right now pT efficiency flat ==> Not used
    TH2* h_TrigSFeta(0);
    h_TrigSFeta = dynamic_cast<TH2*>(trigEfficiencies.Get("scalefactor eta2d with syst"));
    if(!h_TrigSFeta){
        std::cout<<"TH2 >>TH scalefactor eta<< is not in the file "<<trigEfficiencies.GetName()<<"\n";
        return 0;
    }
    
    if(systematic != nominal){
        double factor(0.);
        if(systematic == vary_up) factor = 1.;
        else if(systematic == vary_down) factor = -1.;
        else{
            std::cerr<<"ERROR in TriggerScaleFactors! Systematic with undefined behaviour requested\n...break\n"<<std::endl;
            exit(24);
        }
        
        for (int i = 1; i <= h_TrigSFeta->GetNbinsX(); ++i) {
            for (int j = 1; j <= h_TrigSFeta->GetNbinsY(); ++j) {
                h_TrigSFeta->SetBinContent(i, j,
                    h_TrigSFeta->GetBinContent(i,j) + factor*h_TrigSFeta->GetBinError(i,j));
            }
        }
    }
    
    h_TrigSFeta->SetDirectory(0);
    trigEfficiencies.Close();
    
    return h_TrigSFeta;
}



double TriggerScaleFactors::getTriggerSF(const int leptonXIndex, const int leptonYIndex,
                                         const VLV& leptons, const TString& channel)const
{
    TH2* h_TrigSFeta(0);
    if(channel == "ee") h_TrigSFeta = h2_eeTrigSFeta;
    else if(channel == "emu") h_TrigSFeta = h2_emuTrigSFeta;
    else if(channel == "mumu") h_TrigSFeta = h2_mumuTrigSFeta;
    else{
        std::cerr<<"ERROR in TriggerScaleFactors! Invalid channel requested: "<<channel<<"\n...break\n"<<std::endl;
        exit(25);
    }
    if (!h_TrigSFeta) return 1.;
    
    //For 'ee' and 'mumu' channels Xaxis of the 2D plots is the highest pT lepton
    // for the 'emu' channel Xaxis is the electron and Y axis muon
    const LV& leptonX(leptons.at(leptonXIndex));
    const LV& leptonY(leptons.at(leptonYIndex));
    return ScaleFactorHelpers::get2DSF(h_TrigSFeta, std::fabs(leptonX.eta()), std::fabs(leptonY.eta()));
}















// --------------------------- Methods for BtagScaleFactors ---------------------------------------------




BtagScaleFactors::ChannelStruct::ChannelStruct():
inputFileName_(""),
outputFileName_(""),
btag_ptmedian_(-999.),
btag_etamedian_(-999.),
h2_bEff(0),
h2_cEff(0),
h2_lEff(0),
h2_bjets(0),
h2_cjets(0),
h2_ljets(0),
h2_btaggedjets(0),
h2_ctaggedjets(0),
h2_ltaggedjets(0),
selectorList_(0)
{}



BtagScaleFactors::ChannelStruct::ChannelStruct(const std::string& inputFileName, const std::string& outputFileName):
inputFileName_(inputFileName),
outputFileName_(outputFileName),
btag_ptmedian_(-999.),
btag_etamedian_(-999.),
h2_bEff(0),
h2_cEff(0),
h2_lEff(0),
h2_bjets(0),
h2_cjets(0),
h2_ljets(0),
h2_btaggedjets(0),
h2_ctaggedjets(0),
h2_ltaggedjets(0),
selectorList_(0)
{}




BtagScaleFactors::BtagScaleFactors(const char* btagEfficiencyInputDir,
                                   const char* btagEfficiencyOutputDir,
                                   const std::vector<std::string>& channels,
                                   TString systematic):
makeEfficiencies_(false),
systematic_(nominal)
{
    std::cout<<"--- Beginning preparation of b-tagging scale factors\n";
    if (systematic == "") systematic = "Nominal";
    // Check if all relevant input files are available
    bool allInputFilesAvailable(true);
    for(const auto& channel : channels){
        std::string btagInputFile = ttbar::accessFolder(btagEfficiencyInputDir, channel, systematic, true);
        if(btagInputFile == "") allInputFilesAvailable = false;
        btagInputFile.append(channel + "_ttbarsignalplustau.root");
        
        ifstream inputFileStream;
        if(allInputFilesAvailable) inputFileStream.open(btagInputFile);
        if(!inputFileStream.is_open()){
            std::cout<< "******************************************************\n"
                     << "File " << btagInputFile << " does not exist. Running without btagsf!!!\n"
                     << "To create the file, run (for each systematic 'SYST'):\n" 
                     << "\t> ./build/load_Analysis -f ttbarsignalplustau.root -c emu -s SYST\n"
                     << "\t> ./build/load_Analysis -f ttbarsignalplustau.root -c ee -s SYST\n"
                     << "\t> ./build/load_Analysis -f ttbarsignalplustau.root -c mumu -s SYST\n"
                     << " and move the selectionRoot/BTagEff directory to the cwd:\n"
                     << "\t> mv selectionRoot/BTagEff .\n"
                     << "This error is NOT fatal, not applying any b-tag rescaling\n"
                     << "*******************************************************\n";
            allInputFilesAvailable = false;
            break;
        }
    }
    if(!allInputFilesAvailable){
        std::cout<<"Not all input files for b-tagging efficiencies available\n"
                 <<"\t-->  Efficiencies will not be used, but produced in Analysis\n";
        makeEfficiencies_ = true;
    }
    
    // Depending on whether all input files are available, assign folders for efficiency input or output
    m_channelChannelStruct_.clear();
    for(const auto& channel : channels){
        std::string btagInputFile("");
        std::string btagOutputFile("");
        
        if(!makeEfficiencies_){
            btagInputFile = ttbar::accessFolder(btagEfficiencyInputDir, channel, systematic, true);
            if(btagInputFile != "") btagInputFile.append(channel + "_ttbarsignalplustau.root");
        }
        else{
            btagOutputFile = ttbar::assignFolder(btagEfficiencyOutputDir, channel, systematic);
            if(btagOutputFile != "") btagOutputFile.append(channel + "_ttbarsignalplustau.root");
        }
        
        const ChannelStruct channelStruct(btagInputFile, btagOutputFile);
        m_channelChannelStruct_[channel] = channelStruct;
    }
    
    if(!makeEfficiencies_){
        for(const auto& channel : channels){
            ChannelStruct& channelStruct = this->getChannelStruct(channel);
            this->prepareBtagSF(channelStruct);
            int stringSize = channel.size();
            stringSize = std::max(stringSize, 4);
            std::string channelName = channel;
            channelName.resize(stringSize, ' ');
            printf("Using medians for channel %s: pt = %.0f , eta = %.2f\n", channelName.c_str(), channelStruct.btag_ptmedian_, channelStruct.btag_etamedian_);
        }
    }
    
    // Set systematic if it is an allowed one for btag efficiencies, else set to nominal
    if(systematic == "BTAG_UP") systematic_ = BtagScaleFactors::btag_up;
    else if(systematic == "BTAG_DOWN") systematic_ = BtagScaleFactors::btag_down;
    else if(systematic == "BTAG_PT_UP") systematic_ = BtagScaleFactors::btagPt_up;
    else if(systematic == "BTAG_PT_DOWN") systematic_ = BtagScaleFactors::btagPt_down;
    else if(systematic == "BTAG_ETA_UP") systematic_ = BtagScaleFactors::btagEta_up;
    else if(systematic == "BTAG_ETA_DOWN") systematic_ = BtagScaleFactors::btagEta_down;
    else if(systematic == "BTAG_LJET_UP") systematic_ = BtagScaleFactors::btagLjet_up;
    else if(systematic == "BTAG_LJET_DOWN") systematic_ = BtagScaleFactors::btagLjet_down;
    else if(systematic == "BTAG_LJET_PT_UP") systematic_ = BtagScaleFactors::btagLjetPt_up;
    else if(systematic == "BTAG_LJET_PT_DOWN") systematic_ = BtagScaleFactors::btagLjetPt_down;
    else if(systematic == "BTAG_LJET_ETA_UP") systematic_ = BtagScaleFactors::btagLjetEta_up;
    else if(systematic == "BTAG_LJET_ETA_DOWN") systematic_ = BtagScaleFactors::btagLjetEta_down;
    else if(systematic == "BTAG_BEFF_UP") systematic_ = BtagScaleFactors::btagBeff_up;
    else if(systematic == "BTAG_BEFF_DOWN") systematic_ = BtagScaleFactors::btagBeff_down;
    else if(systematic == "BTAG_CEFF_UP") systematic_ = BtagScaleFactors::btagCeff_up;
    else if(systematic == "BTAG_CEFF_DOWN") systematic_ = BtagScaleFactors::btagCeff_down;
    else if(systematic == "BTAG_LEFF_UP") systematic_ = BtagScaleFactors::btagLeff_up;
    else if(systematic == "BTAG_LEFF_DOWN") systematic_ = BtagScaleFactors::btagLeff_down;
    else systematic_= BtagScaleFactors::nominal;
    
    std::cout<<"=== Finishing preparation of b-tagging scale factors\n\n";
}



bool BtagScaleFactors::makeEfficiencies()const
{
    return makeEfficiencies_;
}



void BtagScaleFactors::prepareBtagSF(ChannelStruct& channelStruct)
{
    //some defaults for the median, overwritten if b-/c-/l-tag histograms exist
    channelStruct.btag_ptmedian_ = 75.;
    channelStruct.btag_etamedian_ = 0.75;
    
    // Load per-jet efficiencies file
    TFile* bEfficiencyFile(0);
    bEfficiencyFile = TFile::Open(channelStruct.inputFileName_.c_str());
    
    // Access the histograms holding the scale factors
    const TString beffHistoName("BEffPerJet");
    channelStruct.h2_bEff = dynamic_cast<TH2*>(bEfficiencyFile->Get(beffHistoName));
    if(!channelStruct.h2_bEff){
        std::cerr<<"Cannot find histogram for b-jet tagging efficiency with name: "<<beffHistoName
                 <<"\n...break\n"<<std::endl;
        exit(30);
    }
    const TString ceffHistoName("CEffPerJet");
    channelStruct.h2_cEff = dynamic_cast<TH2*>(bEfficiencyFile->Get(ceffHistoName));
    if(!channelStruct.h2_cEff){
        std::cerr<<"Cannot find histogram for c-jet tagging efficiency with name: "<<ceffHistoName
                 <<"\n...break\n"<<std::endl;
        exit(31);
    }
    const TString leffHistoName("LEffPerJet");
    channelStruct.h2_lEff = dynamic_cast<TH2*>(bEfficiencyFile->Get(leffHistoName));
    if(!channelStruct.h2_lEff){
        std::cerr<<"Cannot find histogram for l-jet tagging efficiency with name: "<<leffHistoName
                 <<"\n...break\n"<<std::endl;
        exit(32);
    }
    
    const TString medianHistoName("Medians");
    const TH1* medians = dynamic_cast<TH1*>(bEfficiencyFile->Get(medianHistoName));
    if(!medians){
        std::cerr<<"Cannot find histogram for medians of b-jet tagging efficiency with name: "<<medianHistoName
                 <<"\n...break\n"<<std::endl;
        exit(33);
    }
    channelStruct.btag_ptmedian_ = medians->GetBinContent(1);
    channelStruct.btag_etamedian_ = medians->GetBinContent(2);
    
    //load the histograms in memory, to avoid memory leaks
    channelStruct.h2_bEff->SetDirectory(0);
    channelStruct.h2_cEff->SetDirectory(0);
    channelStruct.h2_lEff->SetDirectory(0);
    bEfficiencyFile->Close();
    bEfficiencyFile->Delete();
}



void BtagScaleFactors::indexOfBtags(std::vector<int>& bjetIndices,
                                    const std::vector<int>& jetIndices,
                                    const VLV& jets,
                                    const std::vector<int>& jetPartonFlavours,
                                    const std::vector<double>& btagDiscriminants,
                                    const double tagCut,
                                    const std::string& channel)const
{
    bjetIndices.clear();
    
    std::vector<int> tagged_indices;
    for(const int index : jetIndices){
        //Skip jets where there is no partonFlavour
        if(jetPartonFlavours.at(index) == 0) continue;
        
        if(isTagged(jets.at(index), btagDiscriminants.at(index), jetPartonFlavours.at(index), tagCut, channel))
            tagged_indices.push_back(index);
    }
    bjetIndices = tagged_indices;
}



bool BtagScaleFactors::isTagged(const LV& jet, const double tagValue, const int flavour,
                                const double tagCut, const std::string& channel)const
{
    const ChannelStruct& channelStruct = m_channelChannelStruct_.at(channel);
    
    const bool isBTagged = tagValue > tagCut;
    const double Btag_eff = getEfficiency(jet, flavour, channelStruct);
    const double Btag_SF = getSF(jet.Pt(), std::fabs(jet.Eta()), flavour, channelStruct);
    
    // Throw die
    // The seed is choosen as in https://twiki.cern.ch/twiki/pub/CMS/BTagSFUtil/test.C
    const UInt_t seed = std::abs(static_cast<int>(1.e6 * sin(1.e6*jet.Phi())));
    const float coin = TRandom3(seed).Uniform(1.0);
    
    // Flip the b-tag decision based on random number
    if ( Btag_SF > 1. ) {  // use this if SF>1
        if ( !isBTagged ) {
            // fraction of jets that need to be upgraded
            const float mistagPercent = (1.0 - Btag_SF) / (1.0 - (1.0/Btag_eff) );

            //upgrade to tagged
            if( coin < mistagPercent ) return true;
        }
    }
    else if ( Btag_SF < 1. ) {  // use this if SF<1
        // downgrade tagged to untagged
        if ( isBTagged && coin > Btag_SF ) return false;
    }
    else {  // no change if exactly SF==1
        return isBTagged;
    }
    
    // If nothing is changed, return original value
    return isBTagged;
}



double BtagScaleFactors::getEfficiency(const LV& jet, const int partonFlavour,
                                       const ChannelStruct& channelStruct)const
{
    if (std::abs(partonFlavour) == 0)
    {
        std::cout<<"BtagScaleFactors::GetEfficiency: the jet parton flavour is 0"<<std::endl;
        std::cout<<"              Returning efficiency 1.0"<<std::endl;
        return 1;
    }

    double pt = jet.Pt();
    double eta = std::fabs(jet.Eta());
    int ptbin = -1, etabin = -1, dummy = -1;

    if (std::abs(partonFlavour) == 5 )
    {
        channelStruct.h2_bEff->GetBinXYZ(channelStruct.h2_bEff->FindBin(pt, eta), ptbin, etabin, dummy);
        return channelStruct.h2_bEff->GetBinContent(ptbin, etabin);
    } else if (std::abs(partonFlavour) == 4 ) {
        channelStruct.h2_cEff->GetBinXYZ(channelStruct.h2_cEff->FindBin(pt, eta), ptbin, etabin, dummy);
        return channelStruct.h2_cEff->GetBinContent(ptbin, etabin);
    } else if (std::abs(partonFlavour) != 0 ) {
        channelStruct.h2_lEff->GetBinXYZ(channelStruct.h2_lEff->FindBin(pt, eta), ptbin, etabin, dummy);
        return channelStruct.h2_lEff->GetBinContent(ptbin, etabin);
    }
    return 1.;
}



double BtagScaleFactors::getSF(const double pt, const double abs_eta,
                               const int flavour, const ChannelStruct& channelStruct)const
{
    double tmpsf = 1.;
    double tmperr=0.;
    double sign = varySF(pt, abs_eta, flavour, channelStruct.btag_ptmedian_, channelStruct.btag_etamedian_);

    if(std::abs(flavour) == 5){ //b-jets
        tmpsf = BJetSF( pt, abs_eta );
        tmperr = BJetSFAbsErr(pt);
    }
    else if(std::abs(flavour) == 4){ //c-jets
        tmpsf = CJetSF( pt, abs_eta );
        tmperr = CJetSFAbsErr(pt);
    }
    else if(std::abs(flavour) != 0){ //l-jets
        TString variation = TString("central");
        if(this->ljetSystematic()){
            if((this->ptUpSystematic() && pt>channelStruct.btag_ptmedian_) ||
               (this->ptDownSystematic() && pt<channelStruct.btag_ptmedian_) ||
               (this->etaUpSystematic() && abs_eta>channelStruct.btag_etamedian_ ) ||
               (this->etaDownSystematic() && abs_eta<channelStruct.btag_etamedian_ ) ||
               (systematic_ == btagLjet_up)){
                variation = TString("up");
            }
            else variation = TString("down");
        }
        tmpsf = LJetSF(pt, abs_eta, variation);
        tmperr = 0.;
    }

    return tmpsf + sign * tmperr;
}



double BtagScaleFactors::varySF(const double pt, const double abs_eta,
                                const int flavour,
                                const double ptmedian, const double etamedian)const
{
    // No variation for non b-tag systematic
    if(systematic_ == nominal) return 0;

    // Systematic only for l-jet but the jet is not light: no variation to be done
    if(this->ljetSystematic() && (std::abs(flavour) == 5 || std::abs(flavour) == 4)) return 0.;
    else if(!this->ljetSystematic() && std::abs(flavour) != 5 && std::abs(flavour) != 4) return 0.;
    
    if((this->ptUpSystematic() && pt>ptmedian) ||
       (this->ptDownSystematic() && pt<ptmedian) ||
       (this->etaUpSystematic() && abs_eta>etamedian) ||
       (this->etaDownSystematic() && abs_eta<etamedian))
    {
        return -0.5;
    }
    else if((this->ptUpSystematic() && pt<ptmedian) ||
            (this->ptDownSystematic() && pt>ptmedian) ||
            (this->etaUpSystematic() && abs_eta<etamedian) ||
            (this->etaDownSystematic() && abs_eta>etamedian))
    {
        return 0.5;
    }
    
    // Absolute scale up or down
    if(this->absoluteUpSystematic()) return 1.;
    else if(this->absoluteDownSystematic()) return -1.;
    
    std::cerr<<"ERROR in BtagScaleFactors::varySF! A systematic is used, but no behaviour is specified for it\n...break\n"<<std::endl;
    exit(26);
    return 0.;
}



double BtagScaleFactors::calculateBtagSF(const std::vector<int>& jetIndices,
                                         const VLV& jets,
                                         const std::vector<int>& jetPartonFlavours,
                                         const std::string& channel)const
{
    const ChannelStruct& channelStruct = m_channelChannelStruct_.at(channel);
    
    double oneMinusEfficiency = 1.;
    double oneMinusSFEfficiency = 1.;
    double efficiency = 1.;
    double perJetSF = 1.;
    for(const int index : jetIndices){
        double pt = jets.at(index).Pt();
        double eta = std::fabs(jets.at(index).Eta());
        int partonFlavour = std::abs(jetPartonFlavours.at(index)); //store absolute value
        if (partonFlavour == 0) continue;
        
        // Access the efficiency and the per-jet scale factor
        int ptbin, etabin, dummy;
        channelStruct.h2_bEff->GetBinXYZ(channelStruct.h2_bEff->FindBin(pt, eta), ptbin, etabin, dummy);
        // overflow to last bin
        ptbin = std::min(ptbin, channelStruct.h2_bEff->GetNbinsX());
        etabin = std::min(etabin, channelStruct.h2_bEff->GetNbinsY());
        // do the type-jet selection & Eff and SF obtention
        double SF_Error=0;
        if(partonFlavour == 5){ //b-quark
            efficiency = channelStruct.h2_bEff->GetBinContent(ptbin, etabin);
            if(systematic_ == btagBeff_up) efficiency += channelStruct.h2_bEff->GetBinError(ptbin, etabin);
            else if(systematic_ == btagBeff_down) efficiency -= channelStruct.h2_bEff->GetBinError(ptbin, etabin);
            perJetSF = BJetSF(pt, eta);
            SF_Error = BJetSFAbsErr(pt);
        }
        else if(partonFlavour == 4){ //c-quark
            efficiency = channelStruct.h2_cEff->GetBinContent(ptbin, etabin);
            if(systematic_ == btagCeff_up) efficiency += channelStruct.h2_cEff->GetBinError(ptbin, etabin);
            else if(systematic_ == btagCeff_down) efficiency -= channelStruct.h2_cEff->GetBinError(ptbin, etabin);
            perJetSF = CJetSF(pt, eta);
            SF_Error = CJetSFAbsErr(pt);
        }
        else if(partonFlavour != 0){ //l-quark
            efficiency = channelStruct.h2_lEff->GetBinContent ( ptbin, etabin );
            if(systematic_ == btagLeff_up) efficiency += channelStruct.h2_lEff->GetBinError(ptbin, etabin);
            else if(systematic_ == btagLeff_down) efficiency -= channelStruct.h2_lEff->GetBinError(ptbin, etabin);
            perJetSF = LJetSF(pt, eta, "central");
            if(systematic_ == btagLjet_up){   //systematic variation of l-jets for inclusive XSection measurement
                perJetSF = LJetSF(pt, eta, "up");
            }
            else if(systematic_ == btagLjet_down){ //systematic variation of l-jets for inclusive XSection measurement
                perJetSF = LJetSF(pt, eta, "down");
            }
            else if(this->ljetSystematic()){ //systematic variations for differential XSection
                if((this->ptUpSystematic() && pt>channelStruct.btag_ptmedian_) ||
                   (this->ptDownSystematic() && pt<channelStruct.btag_ptmedian_) ||
                   (this->etaUpSystematic() && eta>channelStruct.btag_etamedian_) ||
                   (this->etaDownSystematic() && eta<channelStruct.btag_etamedian_)){
                    perJetSF = LJetSF(pt, eta, "up");
                }
                else{
                    perJetSF = LJetSF(pt, eta, "down");
                }
            }
        }
        else{
            std::cerr<<"I found a jet which is not b, c nor light: "<<partonFlavour<<"\n...break\n"<<std::endl;
            exit(27);
        }
        if(efficiency <= 0) efficiency = 1;
        
        // calculate both numerator and denominator for per-event SF calculation
        // consider also the UP and DOWN variation for systematics calculation. Same procedure as PU
        oneMinusEfficiency *= 1.-efficiency;
        double perEventSFAtLeastOneTag = perJetSF;
        if(this->ljetSystematic()) SF_Error = 0; //For l-jet systematics set to 0 the b- and c-jet errors
        if(systematic_ == btag_up){
            perEventSFAtLeastOneTag = perJetSF + SF_Error;
        }
        else if(systematic_ == btag_down){
            perEventSFAtLeastOneTag = perJetSF - SF_Error;
        }
        else if(systematic_ == btagPt_up){
            if(pt>channelStruct.btag_ptmedian_) perEventSFAtLeastOneTag = perJetSF - 0.5*SF_Error;
            else perEventSFAtLeastOneTag = perJetSF + 0.5*SF_Error;
        }
        else if(systematic_ == btagPt_down){
            if(pt>channelStruct.btag_ptmedian_) perEventSFAtLeastOneTag = perJetSF + 0.5 * SF_Error;
            else perEventSFAtLeastOneTag = perJetSF - 0.5 * SF_Error;
        }
        else if(systematic_ == btagEta_up){
            if(eta>channelStruct.btag_etamedian_) perEventSFAtLeastOneTag = perJetSF - 0.5 * SF_Error;
            else perEventSFAtLeastOneTag = perJetSF + 0.5 * SF_Error;
        }
        else if(systematic_ == btagEta_down){
            if(eta>channelStruct.btag_etamedian_) perEventSFAtLeastOneTag = perJetSF + 0.5 * SF_Error;
            else perEventSFAtLeastOneTag = perJetSF - 0.5 * SF_Error;
        }
        oneMinusSFEfficiency *= 1. - efficiency*perEventSFAtLeastOneTag;
    }

    if(std::fabs(1.-oneMinusEfficiency)<1.e-8 || std::fabs(1.-oneMinusSFEfficiency)<1.e-8) return 1.;

    // per-event SF calculation (also the UP and DOWN variations)
    double scale_factor = (1.-oneMinusSFEfficiency) / (1.-oneMinusEfficiency);
    
    if(std::fabs(scale_factor-1.) > 0.05) scale_factor = 1.;
    
    return scale_factor;
}







BtagScaleFactors::ChannelStruct& BtagScaleFactors::getChannelStruct(const std::string& channel)
{
    return m_channelChannelStruct_.at(channel);
}





void BtagScaleFactors::bookBtagHistograms(TSelectorList* output, const std::string& channel)
{
    ChannelStruct& channelStruct = this->getChannelStruct(channel);
    
    // Set pointer to output, so that histograms are owned by it
    channelStruct.selectorList_ = output;
    
    constexpr int PtMax = 11;
    constexpr int EtaMax = 5;
    constexpr Double_t ptbins[PtMax+1] = {20.,30.,40.,50.,60.,70.,80.,100.,120.,160.,210.,800.};
    constexpr Double_t etabins[EtaMax+1] = {0.0,0.5,1.0,1.5,2.0,2.4};
    
    channelStruct.h2_bjets = channelStruct.store(new TH2D("bjets2D", "unTagged Bjets", PtMax, ptbins, EtaMax, etabins));
    channelStruct.h2_btaggedjets = channelStruct.store(new TH2D("bjetsTagged2D", "Tagged Bjets", PtMax, ptbins, EtaMax, etabins));
    channelStruct.h2_cjets = channelStruct.store(new TH2D("cjets2D", "unTagged Cjets", PtMax, ptbins, EtaMax, etabins));
    channelStruct.h2_ctaggedjets = channelStruct.store(new TH2D("cjetsTagged2D", "Tagged Cjets", PtMax, ptbins, EtaMax, etabins));
    channelStruct.h2_ljets = channelStruct.store(new TH2D("ljets2D", "unTagged Ljets", PtMax, ptbins, EtaMax, etabins));
    channelStruct.h2_ltaggedjets = channelStruct.store(new TH2D("ljetsTagged2D", "Tagged Ljets", PtMax, ptbins, EtaMax, etabins));
    
    channelStruct.h2_bjets->Sumw2();
    channelStruct.h2_btaggedjets->Sumw2();
    channelStruct.h2_cjets->Sumw2();
    channelStruct.h2_ctaggedjets->Sumw2();
    channelStruct.h2_ljets->Sumw2();
    channelStruct.h2_ltaggedjets->Sumw2();
}



void BtagScaleFactors::fillBtagHistograms(const std::vector<int>& jetIndices,
                                          const std::vector<int>& bjetIndices,
                                          const VLV& jets,
                                          const std::vector<int>& jetPartonFlavours,
                                          const double weight,
                                          const std::string& channel)
{
    ChannelStruct& channelStruct = this->getChannelStruct(channel);
    
    for(const int index : jetIndices){
        const double absJetEta = std::fabs(jets.at(index).eta());
        const double jetPt = jets.at(index).pt();
        const int partonFlavour = std::abs(jetPartonFlavours.at(index));
        const bool hasBTag = std::find(bjetIndices.begin(), bjetIndices.end(), index) != bjetIndices.end();
        if(partonFlavour == 5){ // b-quark
            channelStruct.h2_bjets->Fill(jetPt, absJetEta, weight);
            if(hasBTag){
                channelStruct.h2_btaggedjets->Fill(jetPt, absJetEta, weight);
            }
        }
        else if (partonFlavour == 4){ // c-quark
            channelStruct.h2_cjets->Fill(jetPt, absJetEta, weight);
            if(hasBTag){
                channelStruct.h2_ctaggedjets->Fill(jetPt, absJetEta, weight);
            }
        }
        else if (partonFlavour != 0){ // l-quark
            channelStruct.h2_ljets->Fill(jetPt, absJetEta, weight);
            if(hasBTag){
                channelStruct.h2_ltaggedjets->Fill(jetPt, absJetEta, weight);
            }
        }
    }
}



void BtagScaleFactors::produceBtagEfficiencies(const std::string& channel)
{
    ChannelStruct& channelStruct = this->getChannelStruct(channel);
    
    const std::string f_savename(channelStruct.outputFileName_);
    
    channelStruct.h2_bjets = dynamic_cast<TH2*>(channelStruct.selectorList_->FindObject("bjets2D"));
    channelStruct.h2_btaggedjets = dynamic_cast<TH2*>(channelStruct.selectorList_->FindObject("bjetsTagged2D"));
    channelStruct.h2_cjets = dynamic_cast<TH2*>(channelStruct.selectorList_->FindObject("cjets2D"));
    channelStruct.h2_ctaggedjets = dynamic_cast<TH2*>(channelStruct.selectorList_->FindObject("cjetsTagged2D"));
    channelStruct.h2_ljets = dynamic_cast<TH2*>(channelStruct.selectorList_->FindObject("ljets2D"));
    channelStruct.h2_ltaggedjets = dynamic_cast<TH2*>(channelStruct.selectorList_->FindObject("ljetsTagged2D"));
    if(!channelStruct.h2_bjets || !channelStruct.h2_btaggedjets ||
       !channelStruct.h2_cjets || !channelStruct.h2_ctaggedjets ||
       !channelStruct.h2_ljets || !channelStruct.h2_ltaggedjets){
        std::cerr << "At least one of the btag histograms is missing\n";
        exit(28);
    }
    TFile btagFile(f_savename.c_str(),"RECREATE");
    channelStruct.h2_bjets->Write();
    channelStruct.h2_btaggedjets->Write();
    channelStruct.h2_cjets->Write();
    channelStruct.h2_ctaggedjets->Write();
    channelStruct.h2_ljets->Write();
    channelStruct.h2_ltaggedjets->Write();
    
    TH1* h_btaggedPt = channelStruct.h2_btaggedjets->ProjectionX();
    TH1* h_ctaggedPt = channelStruct.h2_ctaggedjets->ProjectionX();
    TH1* h_ltaggedPt = channelStruct.h2_ltaggedjets->ProjectionX();
    TH1* h_btaggedEta = channelStruct.h2_btaggedjets->ProjectionY();
    TH1* h_ctaggedEta = channelStruct.h2_ctaggedjets->ProjectionY();
    TH1* h_ltaggedEta = channelStruct.h2_ltaggedjets->ProjectionY();

    TH1* h_bPt = channelStruct.h2_bjets->ProjectionX();
    TH1* h_cPt = channelStruct.h2_cjets->ProjectionX();
    TH1* h_lPt = channelStruct.h2_ljets->ProjectionX();
    TH1* h_bEta = channelStruct.h2_bjets->ProjectionY();
    TH1* h_cEta = channelStruct.h2_cjets->ProjectionY();
    TH1* h_lEta = channelStruct.h2_ljets->ProjectionY();
    
    //Calculate the medians and save them in a txt file
    const double ptMedian = ScaleFactorHelpers::median(h_btaggedPt);
    const double etaMedian = ScaleFactorHelpers::median(h_btaggedEta);
    printf("Estimated median for b-tagging: pt = %.0f, eta = %.2f\n", ptMedian, etaMedian);
    TH1* medianHist = new TH1D("Medians", "medians", 2, -0.5, 1.5);
    medianHist->GetXaxis()->SetBinLabel(1, "pT");
    medianHist->GetXaxis()->SetBinLabel(2, "eta");
    medianHist->SetBinContent(1, ptMedian);
    medianHist->SetBinContent(2, etaMedian);
    medianHist->Write();
    
    TH1* h_beffPt = (TH1*) h_btaggedPt->Clone("beffPt");
    TH1* h_ceffPt = (TH1*) h_ctaggedPt->Clone("ceffPt");
    TH1* h_leffPt = (TH1*) h_ltaggedPt->Clone("leffPt");
    
    TH1* h_beffEta = (TH1*) h_btaggedEta->Clone("beffEta");  
    TH1* h_ceffEta = (TH1*) h_ctaggedEta->Clone("ceffEta");  
    TH1* h_leffEta = (TH1*) h_ltaggedEta->Clone("leffEta");  
    
    //Calculate Efficiency: N_tagged/N_all
    //Calculate also the binomial error (option "B" does it)!!
    h_beffPt->Divide(h_btaggedPt, h_bPt, 1, 1, "B"); 
    h_ceffPt->Divide(h_ctaggedPt, h_cPt, 1, 1, "B"); 
    h_leffPt->Divide(h_ltaggedPt, h_lPt, 1, 1, "B");
    h_beffEta->Divide(h_btaggedEta, h_bEta, 1, 1, "B"); 
    h_ceffEta->Divide(h_ctaggedEta, h_cEta, 1, 1, "B"); 
    h_leffEta->Divide(h_ltaggedEta, h_lEta, 1, 1, "B"); 
    channelStruct.h2_btaggedjets->Divide(channelStruct.h2_btaggedjets, channelStruct.h2_bjets, 1, 1, "B"); 
    channelStruct.h2_ctaggedjets->Divide(channelStruct.h2_ctaggedjets, channelStruct.h2_cjets, 1, 1, "B"); 
    channelStruct.h2_ltaggedjets->Divide(channelStruct.h2_ltaggedjets, channelStruct.h2_ljets, 1, 1, "B"); 

    //Save histograms in ROOT file
    h_beffPt->Write("BEffPt");
    h_ceffPt->Write("CEffPt");
    h_leffPt->Write("LEffPt");
    h_beffEta->Write("BEffEta");
    h_ceffEta->Write("CEffEta");
    h_leffEta->Write("LEffEta");
    channelStruct.h2_btaggedjets->Write("BEffPerJet");
    channelStruct.h2_ctaggedjets->Write("CEffPerJet");
    channelStruct.h2_ltaggedjets->Write("LEffPerJet");
    
    // FIXME: Shouldn't these histograms been removed from fOutput,
    // FIXME: so that they are not stored in basic output?
    
    btagFile.Close();
    std::cout<<"Done with production of b-tag efficiency file: "<<f_savename
             <<"\n\n"<<std::endl;
}



double BtagScaleFactors::BJetSF(const double& pt, const double& eta)const
{
    //CSVL b-jet SF
    //From BTV-11-004 and https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-mujet_payload.tptt (ICHEP 2012 prescription)
    //From: https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFb-pt_payload_Moriond13.tptt  (Moriond 2013 prescription)
    
    if(std::fabs(eta) > 2.4){
        std::cerr<<"Jet Eta="<<eta<<" Out of the selected range (|eta|<2.4). Check it\n";
        exit(29);
    }
    
    double jetPt(pt);
    if(jetPt < 20) jetPt = 20;
    if(jetPt > 800) jetPt = 800;

    return 0.981149*((1.+(-0.000713295*jetPt))/(1.+(-0.000703264*jetPt)));
}



double BtagScaleFactors::CJetSF(const double& pt, const double& eta)const
{
    //CSVL c-jet SF
    //From BTV-11-004 and https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC (ICHEP 2012 prescription)
    //From https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC_Moriond13_presc  (Moriond 2013 prescription)

    return BJetSF(pt, eta);
}



double BtagScaleFactors::LJetSF(const double& pt, const double& eta, const TString& typevar)const
{
    //CSVL ligth jet mistag SF. Includes also the SF for variations up and down
    //From BTV-11-004 and https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs.C (ICHEP 2012 prescription)
    //From https://twiki.cern.ch/twiki/pub/CMS/BtagPOG/SFlightFuncs_Moriond2013.C  (Moriond 2013 prescription)

    const double eta_abs = std::fabs(eta);
    if(eta_abs > 2.4){
        std::cerr<<"Jet Eta="<<eta<<" Out of the selected range (|eta|<2.4). Check it\n";
        exit(30);
    }
    if(pt < 20){
        std::cerr<<"Jet pT="<<pt<<" out of the selected range. Check it\n";
        exit(31);
    }
    
    double jetPt(pt);
    if(jetPt>800 && eta_abs<=1.5) jetPt = 800;
    else if(jetPt>700 && eta_abs>1.5) jetPt = 700;
    
    if(typevar == "central"){
        if (eta_abs <= 0.5)
            return ((1.04901+(0.00152181*jetPt))+(-3.43568e-06*(jetPt*jetPt)))+(2.17219e-09*(jetPt*(jetPt*jetPt)));
        else if(eta_abs <= 1.0)
            return ((0.991915+(0.00172552*jetPt))+(-3.92652e-06*(jetPt*jetPt)))+(2.56816e-09*(jetPt*(jetPt*jetPt)));
        else if(eta_abs <= 1.5)
            return ((0.962127+(0.00192796*jetPt))+(-4.53385e-06*(jetPt*jetPt)))+(3.0605e-09*(jetPt*(jetPt*jetPt)));
        else
            return ((1.06121+(0.000332747*jetPt))+(-8.81201e-07*(jetPt*jetPt)))+(7.43896e-10*(jetPt*(jetPt*jetPt)));
    }
    else if(typevar == "up"){
        if(eta_abs <= 0.5)
            return ((1.12424+(0.00201136*jetPt))+(-4.64021e-06*(jetPt*jetPt)))+(2.97219e-09*(jetPt*(jetPt*jetPt)));
        else if(eta_abs <= 1.0)
            return ((1.06231+(0.00215815*jetPt))+(-4.9844e-06*(jetPt*jetPt)))+(3.27623e-09*(jetPt*(jetPt*jetPt)));
        else if(eta_abs <= 1.5)
            return ((1.02883+(0.00231985*jetPt))+(-5.57924e-06*(jetPt*jetPt)))+(3.81235e-09*(jetPt*(jetPt*jetPt)));
        else
            return ((1.1388+(0.000468418*jetPt))+(-1.36341e-06*(jetPt*jetPt)))+(1.19256e-09*(jetPt*(jetPt*jetPt)));
    }
    else if(typevar == "down"){
        if(eta_abs <= 0.5)
            return ((0.973773+(0.00103049*jetPt))+(-2.2277e-06*(jetPt*jetPt)))+(1.37208e-09*(jetPt*(jetPt*jetPt)));
        else if(eta_abs <= 1.0)
            return ((0.921518+(0.00129098*jetPt))+(-2.86488e-06*(jetPt*jetPt)))+(1.86022e-09*(jetPt*(jetPt*jetPt)));
        else if(eta_abs <= 1.5)
            return ((0.895419+(0.00153387*jetPt))+(-3.48409e-06*(jetPt*jetPt)))+(2.30899e-09*(jetPt*(jetPt*jetPt)));
        else
            return ((0.983607+(0.000196747*jetPt))+(-3.98327e-07*(jetPt*jetPt)))+(2.95764e-10*(jetPt*(jetPt*jetPt)));
    }
    else{
        std::cerr<<"ERROR in BtagScaleFactors::LJetSF! Type of variation not valid: "<<typevar
                 <<"\n...break\n"<<std::endl;
        exit(32);
    }
}



double BtagScaleFactors::BJetSFAbsErr(const double& pt)const
{
    //If needed go to https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagPOG#2012_Data_and_MC
    //this pt range MUST match the binning of the error array provided by the BTV in the above link

    constexpr double ptarray[] = {20, 30, 40, 50, 60, 70, 80, 100, 120, 160, 210, 260, 320, 400, 500, 600, 800};
    constexpr double SFb_error[] = { 0.0484285,  0.0126178,  0.0120027,  0.0141137, 0.0145441, 0.0131145, 0.0168479, 0.0160836, 0.0126209, 0.0136017, 0.019182, 0.0198805, 0.0386531, 0.0392831, 0.0481008, 0.0474291 };

    int ptbin = -1;
    int ptarray_Size = sizeof(ptarray) / sizeof(ptarray[0]);
    int SFb_error_array_Size = sizeof(SFb_error) / sizeof(SFb_error[0]);
    
    if( ptarray_Size != SFb_error_array_Size+1 ) {
        std::cout<<"You wrote 2 arrays with sizes that don't agree together!! Fix this.\n";
        exit(100);
    }
    for ( int i=0; i<(ptarray_Size-1); i++){
        if ( pt > ptarray[i] && pt < ptarray[i+1]) {
            ptbin = i;
            break;
        }
    }

    if ( ptbin > ptarray_Size ) {
        return 2 * SFb_error[ptarray_Size];
    } else if ( ptbin < 0){
        return 2 * SFb_error[0];
    } else {
        return SFb_error[ptbin];
    };
}



double BtagScaleFactors::CJetSFAbsErr(const double& pt)const
{
    return 2 * BJetSFAbsErr(pt);
}




bool BtagScaleFactors::ljetSystematic()const
{
    return systematic_==btagLjet_up || systematic_==btagLjet_down ||
           systematic_==btagLjetPt_up || systematic_==btagLjetPt_down ||
           systematic_==btagLjetEta_up || systematic_==btagLjetEta_down;
}



bool BtagScaleFactors::ptUpSystematic()const
{
    return systematic_==btagPt_up || systematic_==btagLjetPt_up;
}



bool BtagScaleFactors::ptDownSystematic()const
{
    return systematic_==btagPt_down || systematic_==btagLjetPt_down;
}



bool BtagScaleFactors::etaUpSystematic()const
{
    return systematic_==btagEta_up || systematic_==btagLjetEta_up;
}



bool BtagScaleFactors::etaDownSystematic() const
{
    return systematic_==btagEta_down || systematic_==btagLjetEta_down;
}



bool BtagScaleFactors::absoluteUpSystematic()const
{
    return systematic_==btag_up || systematic_==btagLjet_up;
}



bool BtagScaleFactors::absoluteDownSystematic()const
{
    return systematic_==btag_down || systematic_==btagLjet_down;
}










