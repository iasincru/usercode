/// To be able to run this program couple of things are needed:
/// The files: compare.cc, DrawComparison.cc and DrawComparison.h in the same directory
/// Add to the CMakeLists.txt the next sentences:
///
///    add_executable(compare
///    compare
///    DrawComparison
///    )
///    TARGET_LINK_LIBRARIES(compare ${ROOT_LIBRARIES})
///
/// In case you want to use the 'make' command
/// please create a 'Makefile' adding in it
///
///  ROOTLIBS=`root-config --ldflags --libs` -Wl,--no-as-needed -lGenVector
///  COMPFLAGS=`root-config --cflags` -Wall -Wextra -pedantic -Wno-vla -O2 -g -std=c++0x -DSTANDALONE_COMPILE
///
///  compare: src/compare.cc
///        g++ -o compare src/compare.cc src/DrawComparison.cc $(COMPFLAGS) $(ROOTLIBS) 




#include <TString.h>
#include <TFile.h>
#include <TH1.h>


#include "DrawComparison.h"


std::vector<TString> SetAxisLabels(TString name)
{
    std::vector<TString> axislabels;
    TString xaxis = "";
    TString yaxis = "";
    if(name.BeginsWith("Hyp")) name.Remove(0,3);

    if (name.BeginsWith("Top"))          yaxis = "Top-quarks";
    else if (name.BeginsWith("TTBar"))   yaxis = "Top-quark Pair";
    else if (name.BeginsWith("BJet"))    yaxis = "b-jets";
    else if (name.BeginsWith("Lepton"))  yaxis = "Leptons";
    else if (name.BeginsWith("LLBar"))   yaxis = "Lepton Pair";

    if (name.Contains("pT"))            xaxis = "p_{T} [GeV/c]";
    else if (name.Contains("Eta"))      xaxis = "#eta";
    else if (name.Contains("Mass"))     xaxis = "M [GeV/c^{2}]";

    axislabels.push_back(xaxis);
    axislabels.push_back(yaxis);
    return axislabels;
}



int main()
{


    std::vector<TString> channel {"mumu", "emu", "ee"};
    std::vector<TString> variation {"BTAG_", "BTAG_PT_", "BTAG_ETA_", "BTAG_LJET_PT_", "BTAG_LJET_ETA_"};
    std::vector<TString> distributions {"HypToppT", "HypTopRapidity", "HypLeptonpT"};


    DrawComparison *comparison = new DrawComparison();

    TString filename1, filename2, filename3;

    for (size_t i=0; i<channel.size(); ++i)
    {
        for (size_t j=0; j<variation.size(); ++j)
        {
            comparison->SetOutputDirectory("comparisons/"+variation.at(j)+"/"+channel.at(i));

            for (size_t k=0; k<distributions.size(); ++k)
            {
                filename1 = TString ("selectionRoot_switch_True/Nominal/"+channel.at(i)+"/"+channel.at(i)+"_ttbarsignalplustau.root");
                filename2 = TString ("selectionRoot_switch_True/"+variation.at(j)+"UP/"+channel.at(i)+"/"+channel.at(i)+"_ttbarsignalplustau.root");
                filename3 = TString ("selectionRoot_switch_True/"+variation.at(j)+"DOWN/"+channel.at(i)+"/"+channel.at(i)+"_ttbarsignalplustau.root");

                comparison->SetFiles(filename1, filename2, filename3);
                std::vector<TString> axislabels = SetAxisLabels(distributions.at(k));
                comparison->SetPlotOptions(0.9, 1., axislabels.at(0), axislabels.at(1));
                comparison->SetHistos(distributions.at(k));
                comparison->DrawAndSaveHisto();
            }
        }
    }

    return 0;

}
