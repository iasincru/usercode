#include "smoothSystematic.h"

#include <fstream>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <istream>
#include <cmath>

#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TSystem.h"
#include "TString.h"





SmoothSyst::SmoothSyst(TString indir, TString outdir, int npoints) :
histo(NULL), singleHisto(NULL)
{
    this->basedir_ = indir;
    this->outbasedir_ = outdir;
    if (npoints != 5 && npoints != 7)
    {
        std::cout<<"ERROR!!\nThe number of points to be used for removing the statistical fluctuation on the syst. unceratinty estimation must be:"<<std::endl;
        std::cout<<"  5: Nominal + 2 variations up + 2 variations down "<<std::endl;
        std::cout<<"  7: Nominal + 3 variations up + 3 variations down "<<std::endl;
        exit(12);
    }
    this->npoints_ = npoints;
}


void SmoothSyst::SetChannel(TString channel)
{
    this->channel_ = channel;
}


void SmoothSyst::SetVariable(TString variable)
{
    if(!variable.Contains("Hyp")){
        std::cout<<"The variable '"<<variable<<"' doesn't match the naming convention: Hyp...\nPlease fix it\n";
        exit(11);
    }
    this->variable_ = variable;
}

bool SmoothSyst::SetSystematicAndCreateSingleHistograms(TString systematic)
{
    std::vector<TString> expSyst = {"JER", "JES", "LEPT", "TRIG", "BTAG"};
    for (auto syst :  expSyst){
        if (systematic.Contains(syst)) break;
        else return 0;
    }

    if (systematic.Contains("UP")) systematic.Resize(systematic.First("UP"));

    std::vector<TString> systematics = {systematic.Copy().Append("DOWN_M2SIGMA"), 
                                        systematic.Copy().Append("DOWN_M1SIGMA"),
                                        "Nominal",
                                        systematic.Copy().Append("UP_P1SIGMA"),
                                        systematic.Copy().Append("UP_P2SIGMA")
                                        };

    if (this->npoints_ == 7)
    {
        systematics.insert(systematics.begin()+1, systematic.Copy().Append("DOWN_M15SIGMA"));
        systematics.insert(systematics.end()-1, systematic.Copy().Append("UP_P15SIGMA"));
    }

    std::vector<TString> files;
    for (auto syst : systematics){
        this->systematic_ = syst;
        this->ReadAndCreateSingleRoot();
        files.push_back(outbasedir_.Copy().Append("/"+syst+"/"+channel_+"/"+variable_+".root"));
    }
    this->FillFilesList(files);
    return 1;
}


void SmoothSyst::ReadAndCreateSingleRoot()
{
    SmoothSyst::ReadFiles();
    SmoothSyst::FillHisto();
    SmoothSyst::SaveHisto();
}


void SmoothSyst::ReadFiles()
{

    TString filename = basedir_+"/"+systematic_+"/"+channel_+"/"+variable_+"Results.txt";
    std::ifstream file(filename);

    if (file.fail()){
        std::cout<<"File '"<<filename<<"' not found.\nExiting!!"<<std::endl;
        exit(111);
    }

    std::string dummy = "";
    double binCenter, lowBin, highBin, result, errorStat, theoryValue;

    while(!file.eof()){
        file>>dummy>>binCenter>>dummy>>lowBin>>dummy>>highBin>>dummy>>result>>dummy>>errorStat>>dummy>>theoryValue;
        this->results.push_back(result);
        this->statError.push_back(errorStat);
    }

    ///stupid need to remove the double entry from the last line of the file
    this->results.resize(results.size()-1);
    this->statError.resize(statError.size()-1);
    file.close();

}

void SmoothSyst::FillHisto()
{
    size_t nbins = this->results.size() == this->statError.size() ? this->results.size() : 0;
    if(!nbins){
        std::cout<<"Results and stat error of differents length\nEXITING"<<std::endl;
        exit(999);
    }

    if(!histo) histo = new TH1D("histo", "Result for a given variation", nbins, 0, nbins);

    for (size_t i = 0; i<this->results.size(); i++){
        this->histo->Fill(i, this->results.at(i));
        this->histo->SetBinError(i+1, this->statError.at(i));
    };

    this->results.clear();
    this->statError.clear();
}



void SmoothSyst::SaveHisto()
{
    if(!histo)
    {
        std::cout<<"Not saving histogram: histogram not defined or not filled"<<std::endl;
        exit(112);
    }

    TString outdir = this->outbasedir_+"/"+this->systematic_+"/"+this->channel_;
    if (gSystem->AccessPathName(outdir)) gSystem->mkdir(outdir, 1);

    TFile *f = TFile::Open(outdir+"/"+this->variable_+".root","RECREATE");
    histo->Write("UnfResult");
    f->Close();

    delete f;
    histo =NULL;
}


void SmoothSyst::FillFilesList(std::vector<TString> files)
{
    fileList_.clear();
    this->fileList_ = files;
}


void SmoothSyst::FillSingleHistoFitAndText(TString outbasedir)
{
    size_t nfiles = fileList_.size();
    TFile *f = NULL;
    TH1D *histogram = NULL;

    int nBins = -1;
    for (size_t iter = 0; iter<nfiles; iter++)
    {
        /// Open each systematic file
        f=TFile::Open(fileList_.at(iter));
        if(!f){
            std::cout<<"File '"<<fileList_.at(iter)<<"' cannot be opened\nEXITING"<<std::endl;
            exit(110);
        }

        /// Read the histogram from each systematic file
        histogram = (TH1D*) f->Get("UnfResult");
        if(!histogram){
            std::cout<<"Histogram 'UnfResult' cannot be read\nEXITING"<<std::endl;
            exit(111);
        }

        nBins = histogram->GetNbinsX();
        if (nBins>0 && nBins != histogram->GetNbinsX())
        {
            std::cout<<"2 histograms have different nBins"<<std::endl;
            exit(89);
        }
        /// Initialize the histogram containing all the variations if not initialized yet
        if (!singleHisto){
            Int_t nbins = nfiles * nBins;
            singleHisto = new TH1D("variableSingleHisto", "All Variations of Single Variable in Single Histo", nbins, -0.5, nbins-0.5);
        }

        /// Fill the single histogram
        for (int bin = 0; bin < nBins; bin++)
        {
            singleHisto->Fill(nfiles*bin+iter, histogram->GetBinContent(bin+1));
            singleHisto->SetBinError(nfiles*bin+iter+1, histogram->GetBinError(bin+1));
        }
    }

    systematic_.Resize(systematic_.First("_")+1);
    TString outdir = outbasedir+"/"+systematic_+"/"+channel_+"/";
    if(gSystem->AccessPathName(outdir)) gSystem->mkdir(outdir, 1);

    TFile *g = new TFile(outdir+variable_+".root", "RECREATE");
    singleHisto->Write("singleHisto");

    this->valUp.clear(); this->valDown.clear();
    this->errUp.clear(); this->errDown.clear();
    /// Fit the bin variation and return the +- 1sigma variation
    for (int iter = 0; iter<(int)nBins; iter++){
        this->FitBins(iter);
        char name[100];
        sprintf(name, "fit_%i", iter);
        fit->Write(name);

        double xdown = nBins*iter-0.5+1.5;
        double xup = nBins*(iter+1)-0.5-1.5;
        this->valDown.push_back(fit->Eval(xdown) - fit->Eval(xdown + (xup -xdown)/2));
        this->valUp.push_back(fit->Eval(xup) - fit->Eval(xdown + (xup -xdown)/2));
        this->errUp.push_back(SmoothSyst::CalculateFitError(fit, xup));
        this->errDown.push_back(SmoothSyst::CalculateFitError(fit, xdown));
    }
    g->Close();
    SmoothSyst::FitToTxt();
    delete g;
    singleHisto = NULL;
    histogram = NULL;
}


double SmoothSyst::CalculateFitError(TF1 *f, double x)
{
    /// Evaluate the error of the corresponding fit function: f(x) = par0 + par1 * x + par2 * x**2
    /// delta_f**2 = delta_par0**2 + delta_par1**2 * x**2 + delta_par2**2 * x**4;

//     double par0 = f->GetParameter(0);
//     double par1 = f->GetParameter(1);
//     double par2 = f->GetParameter(2);

    double err0 = 0., err1 = 0., err2 = 0.;
    if (f->GetNpar()>0) err0 = f->GetParError(0);
    if (f->GetNpar()>1) err1 = f->GetParError(1);
    if (f->GetNpar()>2) err2 = f->GetParError(2);

    return sqrt( pow(err0,2) + std::pow(x,2) * pow(err1, 2) + std::pow(x,4) * pow(err2,2));
}

void SmoothSyst::FitToTxt()
{


    ifstream nominal("UnfoldingResults/Nominal/"+channel_+"/"+variable_+"Results.txt");
    if(!nominal.is_open())
    {
        std::cout<<"Cannot read "<<nominal<<std::endl;
        exit(887);
    }

    TString dummy= "";
    std::vector<double> bincenter, binlow, binup, XSec, thXSec;
    while (!nominal.eof())
    {
        double center, low, up, theory;
        double xsec, staterr;
        nominal>>dummy>>center>>dummy>>low>>dummy>>up>>dummy>>xsec>>dummy>>staterr>>dummy>>theory;

        binlow.push_back(low);  binup.push_back(up);  bincenter.push_back(center);
        XSec.push_back(xsec);   thXSec.push_back(theory);
    }

    TString syst = systematic_;
    syst.Resize(syst.First("_")+1);

    TString fileup = outbasedir_.Copy()+"/"+syst.Copy().Append("UP")+"/"+channel_+"/";
    TString filedown = outbasedir_.Copy()+"/"+syst.Copy().Append("DOWN")+"/"+channel_+"/";

    if(gSystem->AccessPathName(fileup)) gSystem->mkdir(fileup, 1);
    if(gSystem->AccessPathName(filedown)) gSystem->mkdir(filedown, 1);

    fileup.Append(variable_).Append("Results.txt");
    filedown.Append(variable_).Append("Results.txt");

    std::ofstream fileUp (fileup);
    std::ofstream fileDown (filedown);
    if (!fileUp.is_open() || !fileDown.is_open()){
        std::cout<<"Files not opened: \n"<<"    "<<fileUp<<"\n"<<"    "<<fileDown<<"\n";
        exit(888);
    }

    for (size_t iter = 0; iter<valUp.size(); iter++)
    {
        fileUp<<"XAxisbinCenters[bin]: "<<bincenter.at(iter)<<" bin: "<<binlow.at(iter)<<" to "<<binup.at(iter)<<" DiffXsec: "<<XSec.at(iter) + valUp.at(iter)<<" StatError: "<<errUp.at(iter)<<" GenDiffXsec: "<<thXSec.at(iter)<<std::endl;
        fileDown<<"XAxisbinCenters[bin]: "<<bincenter.at(iter)<<" bin: "<<binlow.at(iter)<<" to "<<binlow.at(iter)<<" DiffXsec: "<<XSec.at(iter) + valDown.at(iter)<<" StatError: "<<errDown.at(iter)<<" GenDiffXsec: "<<thXSec.at(iter)<<std::endl;
    }
    fileUp.close();
    fileDown.close();

}

void SmoothSyst::FitBins(int bin)
{
    /// This function will fit the bin-th bin of the variable of all variations nfiles

    if (bin >= (int)fileList_.size())
    {
        std::cout<<"You are trying to fit a not valid bin"<<std::endl;
        exit(890);
    }

    double xmin = (double)fileList_.size() * bin-0.5;
    double xmax = (double)fileList_.size() * (bin+1)-0.5;

//     TF1 *function = new TF1("function", "pol2", xmin, xmax);
    TF1 *function = new TF1("function", "pol1", xmin, xmax);

    if (function->GetNpar()>0){
        function->SetParName(0, "origin");
        function->SetParameter("origin", 0);
    }
    if (function->GetNpar()>1){
        function->SetParName(1, "slope");
        function->SetParameter("slope", 1);
    }
    if (function->GetNpar()>2){
        function->SetParName(2, "curvature");
        function->SetParameter("curvature", 0);
    }

    singleHisto->Fit(function, "E,R,F,B,Q");   /// Fit: proper error treatment (E), in the specified range (R), using Minuit (F), using the userdefined parameters (B), quiet (Q)
    fit = (TF1*) function->Clone();

}