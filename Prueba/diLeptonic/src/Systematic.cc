#include "smoothSystematic.h"

#include <iostream>

#include "TString.h"
#include "TSystem.h"



int main()
{
    /// List of systematics, please keep the order: maximum down variation -> maximum up variation
//     std::vector<std::string> syst= {"JER_DOWN_M2SIGMA", "JER_DOWN_M1SIGMA",
//                                     "Nominal",
//                                     "JER_UP_P1SIGMA", "JER_UP_P2SIGMA"};
    std::vector<std::string> syst= {"JER_UP", "JER_DOWN"};

    std::vector<std::string> channel = {"ee"};//,  "emu"};//, "mumu", "combined"};

    std::vector<std::string> vars = {"HypToppT"};//, "HypTopRapidity"};
//                                      "HypTTBarpT", "HypTTBarMass", 
//                                      "HypTTBarRapidity",
//                                      "HypLeptonpT", "HypLeptonEta", 
//                                      "HypLLBarpT", "HypLLBarMass",
//                                      "HypBJetpT", "HypBJetEta"};

    TString inputdir = "UnfoldingResults";
//     TString outdir = "SmoothSyst";
    TString outdir = inputdir;

    SmoothSyst *smooth = new SmoothSyst(inputdir, outdir);

    for (auto variable : vars){
        for (auto chann : channel){ /// Iterate in the channels
            for (auto systematic : syst){ /// Iterate in the systematics
                smooth->SetChannel(chann);
                smooth->SetVariable(variable);
                smooth->SetSystematicAndCreateSingleHistograms(systematic);
                smooth->FillSingleHistoFitAndText("SmoothSingleHisto");
            }/// iteration in systematic
        }/// iteration in channels
    }/// iteration in variables

    delete smooth;


}
