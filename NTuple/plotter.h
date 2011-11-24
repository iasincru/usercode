#ifndef plotter_h
#define plotter_h

#include "THStack.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"
#include "TH1F.h"
#include <vector>
#include <iostream>
#include "TCanvas.h"
/*
#include "TLegend.h"
#include <sstream>
//#include <Int_t.h>
*/

class Plotter{

 public:


 Plotter:Plotter(TString, TString, int, double, double, TString, bool)
  ~Plotter();
  
  void fill( float, double);
  void Plotter::setOptions(TString, TString, TString, int, double, double);
  void write(TString);
  void write();

 private:

  TString name;
  TString title;
  int nbins;
  double rangemin;
  double rangemax;
  TString Xlabel;
  TString Ylabel;

  bool initialized;

};


Plotter:Plotter(TString title_, TString name_, int bins_, double rangemin_, double rangemax_, TString Ylabel_)
{

  title=title_;
  name=name_;
  bins=bins_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  Xlabel=name;
  Ylabel=Ylabel_;

  initialized=false;

};


Ploter::~Plotter()
{

};



void Plotter::setOptions(TString title_, TString name_,TString Xlabel_, TString Ylabel_, int nbins_, double rangemin_, double rangemax_)
{
  title=title_;
  name=name_;
  nbins=nbins_;
  rangemin=rangemin_;
  rangemax=rangemax_;
  DYScale=DYScale_;
  Xlabel=Xlabel_;
  Ylabel=Ylabel_;

}


void Plotter:setStyle(TH1F &hist)
{
  
  hist.GetXaxis()->SetTitle(name);
  hist.GetXaxis()->SetTitleSize(0.06);
  hist.GetXaxis()->SetTitleOffset(0.7);
  hist.GetYaxis()->SetTitle(Ylabel);
  hist.GetYaxis()->SetTitleSize(0.06);
  hist.GetYaxis()->SetTitleOffset(0.7);


};




void Plotter::fill(float value, double weight)
{
  if (!initialized)
  {
    TH1F histoIvan = TH1F (title, name, nbins, rangemin, rangemax);
    histoIvan.Copy(histone);
    initialized =true;
  };

  histone.Fill(value, weight);

};



void Plotter:write()
{

  if (initialized)
  {
    histone.Draw();
    histone.Write();
  };
  else std::cout<<"Histogram "<<name<<" not written."<<std::endl;

};




void Plotter:write(TString outname)
{

  if (initialized)
  {
    histone.Draw();
    histone.Write(outname);
  };
  else std::cout<<"Histogram "<<name<<" not written."<<std::endl;

};
