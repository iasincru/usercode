#include "iostream"
#include "cmath"
#include <fstream>

#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TPaveStats.h>
#include <TError.h>





/*
 *
 *  run this macro via:
 *  root -l -b -q compareTrees.cc++
 *
*/



std::string dir1 = "2014_02_10_TAG_N004";
std::string dir2 = "2014_03_14_TAG_N005";

int nrEntries(TTree *tree, TString variable)
{
//     TH1I *histo = new TH1I("histo", "histo", 100, 0, 100);
//     tree->Draw(variable+">>histo");
//     TH1I *h0 = (TH1I*)histo->Clone("h0");
//     delete histo;
//     return h0->GetEntries();
    TH1I histo = TH1I("histo", "histo", 100, 0, 100);
    tree->Draw(variable+">>histo");
    return histo.GetEntries();
}




void compareTrees()
{

    gErrorIgnoreLevel = 1001;

    std::string samples_array[] = {"ee_run2012A", "ee_run2012B", "ee_run2012C","ee_run2012D", 
                                      "emu_run2012A","emu_run2012B","emu_run2012C","emu_run2012D", 
                                      "mumu_run2012A","mumu_run2012B","mumu_run2012C","mumu_run2012D",
                                      "dy1050",
                                      "qcdbcem2030","qcdbcem3080","qcdbcem80170","qcdem2030","qcdem3080","qcdem80170","qcdmu15",
                                      "singleantitop_tw","singletop_tw",
                                      "wtolnu",
                                      "wwtoall","wztoall","zztoall",
                                      "ttbarsignalplustau", 
                                      "ttbarbg_matchingup", "ttbarbg_matchingdown", 
                                      "ttbarsignalplustau_matchingup", "ttbarsignalplustau_matchingdown",
                                      "ttbarbg_scaleup", "ttbarbg_scaledown", 
                                      "ttbarsignalplustau_scaleup", "ttbarsignalplustau_scaledown", 
//                                       "ttbarbg_166_massdown", "ttbarsignalplustau_166_massdown",
//                                       "ttbarbg_169_massdown", "ttbarsignalplustau_169_massdown",
                                      "ttbarbg_massup", "ttbarsignalplustau_massup", 
//                                       "ttbarbg_175_massup", "ttbarsignalplustau_175_massup", 
//                                       "ttbarbg_178_massup", "ttbarsignalplustau_178_massup", 
                                      "ttbarbg_massdown", "ttbarsignalplustau_massdown",
                                      "ttbarH125inclusive","ttbarH125tobbbar",
                                      "ttbarZ"
    };

    std::vector<std::string> samples (samples_array, samples_array+ sizeof(samples_array) / sizeof(samples_array[0]));
    std::string basedir ("/data/group/top/DiffXS/");
    
    printf("Sample  %s   %s    diff(%%)  variable: %s\n", dir1.c_str(), dir2.c_str(), "met.pt()");
    for (size_t iter = 0 ; iter<samples.size(); iter++){
        TString file0=basedir+dir1+"/"+samples.at(iter)+".root";
        TString file1=basedir+dir2+"/"+samples.at(iter)+".root";
        ifstream _file0(file0), _file1(file1);

        if(!_file0.is_open() || !_file1.is_open()){
            std::cout<<"File: "<<file0<<std::endl;
            std::cout<<"  or: "<<file1<<std::endl;
            std::cout<<" doesn't exist or cannot be opened. Continue"<<std::endl;
            continue;
        }
        _file0.close(); _file1.close();

        TFile *f0 = new TFile(file0);
        TFile *f1 = new TFile(file1);

        TTree *t0 = (TTree*)f0->Get("writeNTuple/NTuple");
        TTree *t1 = (TTree*)f1->Get("writeNTuple/NTuple");

        int nrEvents_old = nrEntries(t0, "met.pt()");
        int nrEvents_new = nrEntries(t1, "met.pt()");

        printf("%s %10i %10i %2.3e \n", samples.at(iter).c_str(), nrEvents_old, nrEvents_new, 100*(1.*nrEvents_old-nrEvents_new)/nrEvents_old);
        delete t0; delete t1;
        f0->Close(); f1->Close();
        delete f0;   delete f1;
    }
    printf("--------------------------------------------------------------------------------------\n");
    printf("Sample  %s   %s    diff(%%)  variable: %s\n", dir1.c_str(), dir2.c_str(), "unweightedEvents");
    for (size_t iter = 0 ; iter<samples.size(); iter++){
        TString file0=basedir+dir1+"/"+samples.at(iter)+".root";
        TString file1=basedir+dir2+"/"+samples.at(iter)+".root";
        ifstream _file0(file0), _file1(file1);

        if(!_file0.is_open() || !_file1.is_open()){
            std::cout<<"File: "<<file0<<std::endl;
            std::cout<<"  or: "<<file1<<std::endl;
            std::cout<<" doesn't exist or cannot be opened. Continue"<<std::endl;
            continue;
        }
        _file0.close(); _file1.close();

        TFile *f0 = new TFile(file0);
        TFile *f1 = new TFile(file1);

        TH1I *t0 = (TH1I*)f0->Get("EventsBeforeSelection/unweightedEvents");
        TH1I *t1 = (TH1I*)f1->Get("EventsBeforeSelection/unweightedEvents");

        int nrEvents_old = t0->GetEntries();
        int nrEvents_new = t1->GetEntries();

        printf("%s %10i %10i %2.3e \n", samples.at(iter).c_str(), nrEvents_old, nrEvents_new, 100*(1.*nrEvents_old-nrEvents_new)/nrEvents_old);
        delete t0; delete t1;
        f0->Close(); f1->Close();
        delete f0;   delete f1;
    }

    
    
}