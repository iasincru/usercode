#ifndef smoothSystematic_h
#define smoothSystematic_h



#include <vector>
#include "TString.h"
class TH1;
class TF1;

class SmoothSyst{

    public:
        SmoothSyst (TString indir, TString outdir, int npoints = 5);
        void SetVariable (TString variable);
        void SetChannel (TString channel);
        bool SetSystematicAndCreateSingleHistograms(TString systematic);
        void FitToTxt();
        void FillSingleHistoFitAndText (TString outbasedir);

    private:

        void ReadAndCreateSingleRoot();
        void FillFilesList (std::vector<TString> files);
        void FitBins(int bins);
        void ReadFiles();
        void FillHisto();
        void SaveHisto();
        double CalculateFitError(TF1 *f, double x);

        TString basedir_, outbasedir_;
        TString variable_, channel_, systematic_;
        int nbinsDistribution_;

        std::vector<double> results, statError;
        std::vector<double> valUp, valDown, errUp, errDown;
        std::vector<TString> fileList_;

        TH1 *histo, *singleHisto;
        TF1 *fit;
        int npoints_;
        bool debug_;
};

#endif