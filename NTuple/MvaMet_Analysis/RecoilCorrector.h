#ifndef RecoilCorrector_h
#define RecoilCorrector_h

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

class TF1;
class TH1;
class TFile;

namespace ztop{

class RecoilCorrector {

public:
    
    /// Constructor
    RecoilCorrector();
    
    /// Constructor
    RecoilCorrector(const std::string basedir, const int method = 3, const int dataset = -1, const int debug = 0);
    
    /// Destructor
    ~RecoilCorrector();
    
    /// Set input data and mc files where the fits are stored
    void setFiles(std::string fileData, std::string fileMC);
    
    /**
     *
     * Main function to correct the MET
     * @param MetPx x-component of the reconstructed MET, the actual value is modified, corrected and replaced
     * @param MetPy y-component of the reconstructed MET, the actual value is modified, corrected and replaceds
     * @param genZPx x-component of the generated Z-boson transverse momentum
     * @param genZPy y-component of the generated Z-boson transverse momentum
     * @param diLepPx x-component of the reconstructed and selected dilepton transverse momentum, it is assumed that this dilepton pair forms the Z-boson
     * @param diLepPy y-component of the reconstructed and selected dilepton transverse momentum, it is assumed that this dilepton pair forms the Z-boson
     * @param njets Number of jets in the event
     *
     */
    float correctMet(float& MetPx, float& MetPy, float genZPx, float genZPy, float diLepPx, float diLepPy, int njets);

    /// Base directory where the ROOT files with the fit results are stored
    std::string basedir_;
    
    /// Boolean to decide if we can or cannot correct the MET
    bool cannotCorrectMet_;
    
    /**
      * Decide how is the MET corrected
      *   method_ == 2 - corrections by width w(MC)=w(Data)/w(MC) * w(Process)
      *   method_ == 3 - corrections by sampling (calculations of quantiles)
     */
    int method_;
    
    /// Variable used for 2011 dataset
    int dataset_;

private:

    /** Level of debug
     *  0  -> no debug
     *  1 -> minimal
     *  2 -> verbose
     */
    int debug_;
    
    /**
     * Calculate the parallel and transverse component of the Z pt, with respect to MET
     *    U1 --> Z-pt parallel component to the MET
     *    U2 --> Z-pt orthogonal component to the MET
    */
    void CalculateU1U2FromMet(float metPx, float metPy, float genZPx, float genZPy,
                              float diLepPx, float diLepPy,
                              float& U1, float& U2, float& metU1, float& metU2);

    /**
     * Calculate the MET from the parallel and transverse component of the Z pt
     *    U1 --> Z-pt parallel component to the MET
     *    U2 --> Z-pt orthogonal component to the MET
    */
    void CalculateMetFromU1U2(float U1, float U2, float genZPx, float genZPy,
                              float diLepPx, float diLepPy, float& metPx, float& metPy);

    
    /// Correct the MET using the width of the fit
    void  U1U2CorrectionsByWidth(float& U1, float& U2, int nZptBin, int njets);
    
    /// Get the bin number to which corresponds the pt value of the Z-boson
    int getBinNumber(float x, const std::vector<int> bins)const;
    
    /// Get the fitted function
    TF1* getFuncRecoil(TF1* initFunc, bool left);

    TFile *data_, *mc_;

    /// Number of Z-boson pt bins: harcoded according to the histograms stored in the ROOT files
    std::vector<int> ZPtBins_;
    
    /// Number of jet bins: harcoded according to the histograms stored in the ROOT files
    std::vector<int> nJets_;

    /// Number of Z-pt bins, hardcoded since this should match the number of TF1's in the ROOT files
    static const int nZPtBins_ = 5;
    
    /// Number of jets, hardcoded since this should match the number of TF1's in the ROOT files
    static const int nJetsBins_ = 3;

    TF1* metZParalData_[nZPtBins_][nJetsBins_];
    TF1* metZPerpData_[nZPtBins_][nJetsBins_];
    TF1* metZParalMC_[nZPtBins_][nJetsBins_];
    TF1* metZPerpMC_[nZPtBins_][nJetsBins_];

    TH1* metZParalDataHist_[nZPtBins_][nJetsBins_];
    TH1* metZPerpDataHist_[nZPtBins_][nJetsBins_];
    TH1* metZParalMCHist_[nZPtBins_][nJetsBins_];
    TH1* metZPerpMCHist_[nZPtBins_][nJetsBins_];

    float meanMetZParalData_[nZPtBins_][nJetsBins_];
    float meanMetZParalMC_[nZPtBins_][nJetsBins_];
    float meanMetZPerpData_[nZPtBins_][nJetsBins_];
    float meanMetZPerpMC_[nZPtBins_][nJetsBins_];

    float rmsMetZParalData_[nZPtBins_][nJetsBins_];
    float rmsLeftMetZParalData_[nZPtBins_][nJetsBins_];
    float rmsRightMetZParalData_[nZPtBins_][nJetsBins_];

    float rmsMetZParalMC_[nZPtBins_][nJetsBins_];
    float rmsLeftMetZParalMC_[nZPtBins_][nJetsBins_];
    float rmsRightMetZParalMC_[nZPtBins_][nJetsBins_];

    float rmsMetZPerpData_[nZPtBins_][nJetsBins_];
    float rmsLeftMetZPerpData_[nZPtBins_][nJetsBins_];
    float rmsRightMetZPerpData_[nZPtBins_][nJetsBins_];

    float rmsMetZPerpMC_[nZPtBins_][nJetsBins_];
    float rmsLeftMetZPerpMC_[nZPtBins_][nJetsBins_];
    float rmsRightMetZPerpMC_[nZPtBins_][nJetsBins_];

    float xminMetZPerp_[nZPtBins_][nJetsBins_];
    float xmaxMetZPerp_[nZPtBins_][nJetsBins_];

    float xminMetZPerpData_[nZPtBins_][nJetsBins_];
    float xmaxMetZPerpData_[nZPtBins_][nJetsBins_];

    float xminMetZPerpMC_[nZPtBins_][nJetsBins_];
    float xmaxMetZPerpMC_[nZPtBins_][nJetsBins_];

    float xminMetZParal_[nZPtBins_][nJetsBins_];
    float xmaxMetZParal_[nZPtBins_][nJetsBins_];

    float xminMetZParalData_[nZPtBins_][nJetsBins_];
    float xmaxMetZParalData_[nZPtBins_][nJetsBins_];

    float xminMetZParalMC_[nZPtBins_][nJetsBins_];
    float xmaxMetZParalMC_[nZPtBins_][nJetsBins_];

};


}


#endif