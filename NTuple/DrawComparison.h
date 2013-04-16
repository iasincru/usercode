#ifndef DrawComparison_h
#define DrawComparison_h


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <functional>

#include "TString.h"

class TH1;
class TLegend;
class TFile;
class TPad;
class TStyle;

class DrawComparison {
    
    public:
        DrawComparison(){};

        TLegend *MakeLegend(TH1* h1, TString name1, TH1* h2, TString name2, TH1* h3 = 0, TString name3 = "");
        void SetFiles (TString filename1, TString filename2, TString filename3 = "");
        void SetHistos (TString distribution = "");

        void SetPlotOptions(double ratioMin = 0., double ratioMax = 2., TString xlabel = "", TString ylabel = "");
        void SetHistoOptions(TH1* histo, TString nameForLegend, int color, int marker, double markersize = 1.0);
        void SetRatioStyle (TH1 *ratio1, TH1* histDenominator);

        TPad* MakePad();
        
        void SetOutputDirectory(TString outputdir);
        
        void drawRatio(const TH1* histNumerator, TH1* histDenominator, TH1* histDenominator2 = 0, TString ratioDrawOption="p e X0", bool drawError = 0);

        void DrawAndSaveHisto();

    private:
        
                
        TFile *f1_, *f2_, *f3_;
        TH1 *h1_, *h2_, *h3_;
        double ratioMin_;
        double ratioMax_;
        TString xlabel_;
        TString ylabel_;
        TString outputdir_;
        TString distribution_;
        double scaleFactor_, canvAsym_, ratioSize_;
        TStyle *myStyle;
        Int_t logx_;
        Double_t left_, right_;
};


#endif