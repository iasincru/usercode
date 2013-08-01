#ifndef plotterclass_h
#define plotterclass_h

#include <vector>
#include <set>

class TGraphErrors;
class TLegend;
class TGraphAsymmErrors;
class TH1;
class TString;
class TH1F;
class TH1D;

class RootFileReader;





class Plotter {

public:
    Plotter();
    void   setOptions(TString name_, TString specialComment_, TString YAxis_, TString XAxis_, int rebin_, bool doDYScale_, bool logX_, bool logY_, double ymin_, double ymax_, double rangemin_, double rangemax_, int bins_, std::vector<double> XAxisbins_, std::vector<double> XAxisbinCenters_);
    void   setDataSet(std::vector<TString>, std::vector<double>, std::vector<TString>, std::vector<int>, TString);
    void   setDataSet(TString, TString);
    bool   fillHisto();
    void   setStyle(TH1*, unsigned int, bool = false);
    void   unfolding(TString channel, TString systematic);
    void   preunfolding(TString Channel="", TString Systematic="");
    
    ///add addThis to addToThis (and delete it afterwards) - or assign it it to addToThis if addToThis is nullptr.
    void   addAndDelete_or_Assign(TH1*& addToThis, TH1* addThis);
    void   write(TString, TString);
    void   setLumi(double);
    
    double CalcXSec(std::vector<TString> datasetVec, double InclusiveXsectionVec[4],double InclusiveXsectionStatErrorVec[4], TString Systematic, TString Shift);
    void MakeTable(TString Channel, TString Systematic);


    void PlotXSec(TString Channel);
    //  void CalcDiffXSec(TH1* varhists[], TH1* RecoPlot, TH1* GenPlot, TH2* genReco2d, double DiffXSecVec[4][10], double DiffXSecStatErrorVec[4][10]); 
    int CalcDiffXSec(TString, TString);
    void CalcDiffSystematics(TString, TString, TString, TString, double);
    void PlotDiffXSec(TString, std::vector<TString>);
    void PlotSingleDiffXSec(TString, TString);

    void DYScaleFactor(TString);

    void PrintResultTotxtFile(TString, double[], TGraphAsymmErrors *, TGraphAsymmErrors *);
    void CalcUpDownDifference ( TString Channel, TString Syst_Up, TString Syst_Down, TString Variable);

    TLegend* getNewLegend();
    TLegend* getNewLegendpre();

    TH1* GetNloCurve(const char *particle, const char *quantity, const char *generator);
    TH1* GetNloCurve(TString NewName, TString Generator);
    TH1F* ConvertGraphToHisto(TGraphErrors *pGraph);
    double GetChi2 (TGraphAsymmErrors *data, TH1 *mc);
    TH1F* reBinTH1FIrregularNewBinning(TH1F *histoOldBinning, TString plotname, bool rescale);

    //IVAN's Scaling Code
    void ApplyFlatWeights(TH1* varhists,   const double weight);
    double SampleXSection(const TString& filename);
    double CalcLumiWeight(const TString& WhichSample);
    std::vector<TString> InputFileList(TString mode, TString Systematic);

    // DAVID
    void UnfoldingOptions(bool doSVD);
    void SetOutpath(TString path); 
    void ControlLegend(std::vector<TH1*> drawhists, std::vector<TString> legends, TLegend *leg);
    void DrawLabel(TString text, const double x1, const double y1, const double x2, const double y2, int centering, double textSize);

    void ListOfSystematics(std::set<TString>);
    std::set<TString> ListOfSyst;

private:

    TString name;

    TString specialComment;
    int bins, datafiles, rebin;
    double rangemin, rangemax, ymin, ymax;

    std::vector<TString> dataset, datasetUp, datasetDown;
    std::vector<double> scales;
    std::vector<TString> legends, legendsSyst;
    std::vector<int> colors;
    std::vector<double> XAxisbins, XAxisbinCenters;

    std::vector<double> DYScale;
    TString DYEntry;
    TString YAxis;
    TString XAxis;
    TString channel;
    int channelType; //0=ee 1==mumu 2==emu 3==combined  

    std::vector<TH1D> hists;
    std::vector<TH1D> systhistsUp;
    std::vector<TH1D> systhistsDown;

    bool initialized, logX, logY, doDYScale;
    double lumi;
    int signalHist;

    std::vector<TString> channelLabel;

    double SignalEventswithWeight;
    
    // DAVID
    bool doUnfolding; 
    bool doSystematics;
    bool drawSmoothMadgraph, drawPlotRatio;
    bool drawNLOCurves, drawMadSpinCorr, drawMCATNLO, drawKidonakis, drawPOWHEG;
    TString outpath;
    TString outpathPlots;
    TString outpathResults;
    TString subfolderChannel;
    TString subfolderSpecial;

    static const double topxsec;
    static const bool doClosureTest;
    RootFileReader *fileReader;
    void DrawDecayChLabel(TString decaychannel="", double textSize=0.04);
    void DrawCMSLabels(int cmsprelim=true, double energy=8, double textSize=0.04);

};

#endif
