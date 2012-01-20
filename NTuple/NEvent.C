//This macro calculates the contribution of each sample to the final result.



#include<iostream>
#include<fstream>
#include <vector.h>
#include <string.h>


void NEvent(){

//   ifstream mumufile ("HistoFileList_mumu.txt");
//   ifstream emufile ("HistoFileList_emu.txt");
//   ifstream eefile ("HistoFileList_ee.txt");
  
  ifstream mumufile ("HistoFileList_mumu2.txt");
  ifstream emufile ("HistoFileList_emu2.txt");
  ifstream eefile ("HistoFileList_ee2.txt");
  
  TString filename;

  double total=0.;
  vector<double> evt1, evt2, evt3;
  vector<double> int1, int2, int3;
  vector<TString> name1, name2, name3;
  
  while(!mumufile.eof()){
    mumufile>>filename;
   
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TH1D *h=(TH1D*) f1->Get("HypToppT");
      
      if (filename.Contains("plus")){
	TH1D *h2=(TH1D*)f1->Get("HypToppTPrompt");	evt1.push_back(h2->GetEntries());	int1.push_back(h2->Integral());	name1.push_back(filename.Copy().Append(" (Prompt)"));
	TH1D *h1=(TH1D*)f1->Get("HypToppTTau");		evt1.push_back(h1->GetEntries());	int1.push_back(h1->Integral());	name1.push_back(filename.Copy().Append(" (Tau)"));
      }
      else{
	double evt, integral;
	evt= h->GetEntries();
	integral=h->Integral();
	if (filename.Contains("run") == 0 && filename.Contains("signal.root") == 0 && filename.Contains("viatau") ==0 ){
	  evt1.push_back(h->GetEntries()); int1.push_back(h->Integral()); name1.push_back(filename);
	}
      }
    }
  }
  double total1=0;
  std::cout<<"Integral    Fraction (%)          Sample        "<<std::endl;
  for (int i=0; i<(int)int1.size(); i++){    total1=total1+int1[i]; }
  for (int i=0; i<(int)evt1.size(); i++){    std::cout<<int1[i]<<"     "<< 100.*int1[i]/total1<<"     "<< name1[i]<<std::endl;  }

  
  while(!emufile.eof()){
    emufile>>filename;
    
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TH1D *h=(TH1D*) f1->Get("HypToppT");
      if (filename.Contains("plus")){
	TH1D *h2=(TH1D*)f1->Get("HypToppTPrompt");	evt2.push_back(h2->GetEntries());	int2.push_back(h2->Integral());	name2.push_back(filename.Copy().Append(" (Prompt)"));
	TH1D *h1=(TH1D*)f1->Get("HypToppTTau");		evt2.push_back(h1->GetEntries());	int2.push_back(h1->Integral());	name2.push_back(filename.Copy().Append(" (Tau)"));
      }
      else{
	double evt, integral;
	evt= h->GetEntries();
	integral=h->Integral();
	if (filename.Contains("run") == 0 && filename.Contains("signal.root") == 0 && filename.Contains("viatau") ==0 ){
	  evt2.push_back(h->GetEntries()); int2.push_back(h->Integral()); name2.push_back(filename);
	}
      }
    }
  }
  double total2=0;
  std::cout<<"---------------------------------------"<<std::endl;
  std::cout<<"Integral    Fraction (%)          Sample        "<<std::endl;
  for (int i=0; i<(int)int2.size(); i++){   total2=total2+int2[i];  }
  for (int i=0; i<(int)evt2.size(); i++){   std::cout<<int2[i]<<"     "<< 100.*int2[i]/total2<<"     "<< name2[i]<<std::endl;  }

  
  while(!eefile.eof()){
    eefile>>filename;
    
    if(filename!=""){
      TFile *f1 = TFile::Open(filename);
      TH1D *h=(TH1D*) f1->Get("HypToppT");
      if (filename.Contains("plus")){
	TH1D *h2=(TH1D*)f1->Get("HypToppTPrompt");	evt3.push_back(h2->GetEntries());	int3.push_back(h2->Integral());	name3.push_back(filename.Copy().Append(" (Prompt)"));
	TH1D *h1=(TH1D*)f1->Get("HypToppTTau");		evt3.push_back(h1->GetEntries());	int3.push_back(h1->Integral());	name3.push_back(filename.Copy().Append(" (Tau)"));
      }
      else{
	double evt, integral;
	evt= h->GetEntries();
	integral=h->Integral();
	if (filename.Contains("run") == 0 && filename.Contains("signal.root") == 0 && filename.Contains("viatau") ==0 ){
	  evt3.push_back(h->GetEntries()); int3.push_back(h->Integral()); name3.push_back(filename);
	}
      }
    }
  }
  double total3=0;
  std::cout<<"---------------------------------------"<<std::endl;
  std::cout<<"Integral    Fraction (%)          Sample        "<<std::endl;
  for (int i=0; i<(int)int3.size(); i++){    total3=total3+int3[i];  }
  for (int i=0; i<(int)evt3.size(); i++){    std::cout<<int3[i]<<"     "<< 100.*int3[i]/total3<<"     "<< name3[i]<<std::endl;  }



}
