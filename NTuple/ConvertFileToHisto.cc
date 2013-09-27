///
/// Compile this macro via adding into the CMakeLists.txt the next 4 lines
///
// add_executable(ConvertFileToHisto
//     ConvertFileToHisto
// )
// TARGET_LINK_LIBRARIES(ConvertFileToHisto ${ROOT_LIBRARIES}) 


#include <iostream>
#include <fstream>
#include <vector>

#include "TH1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TFile.h"

const char *inputfilename = "Mtt_8000_172.5_Mtt_fin.dat";
const char *outputfilename = "mttAhrens_8Tev_1725.root";

void iterate(std::vector<double> vec)
{
    
    for (auto it : vec)
    {
        std::cout<<it<<std::endl;
    }
}

void ConvertFileToHisto()
{
    
    ifstream file (inputfilename);
    std::vector<double> bins, xsec;
    while(!file.eof())
    {
        double tmp_bin = 0.0, tmp_xsec = 0.0, dummy = 0.0;
        file>>tmp_bin>>tmp_xsec>>dummy>>dummy>>dummy>>dummy>>dummy>>dummy;
        if(file.eof()) break;
        bins.push_back(tmp_bin);
        xsec.push_back(tmp_xsec);
    }

    int nbins = bins.size();
    TH1D *histo = new TH1D ("ahrens", "Ahrens m_{tt} prediction for 8TeV", nbins, bins.at(0), bins.at(nbins-1));

    for (int i=0;i<nbins; i++)
    {
        histo->Fill(bins.at(i), xsec.at(i));
    }

    double integral = histo->Integral("width");
    histo->Scale(1./integral);

    TGraph *graph = new TGraph(histo);

    TFile *f = new TFile(outputfilename, "RECREATE");
    histo->Write("mttbar");
    graph->Write("mttbar_graph");
    f->Close();
}



int main()
{
    
    ConvertFileToHisto();
    
}