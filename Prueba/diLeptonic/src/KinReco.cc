#include <cmath>
#include <cassert>
#include <algorithm>
#include <utility>
#include <cmath>

#include <TLorentzVector.h>
#include <TMath.h>

#include "KinReco.h"
#include "utils.h"
#include "analysisUtils.h"
#include "classes.h"






TtFullLepKinSolver::TtFullLepKinSolver(const std::vector<double> &nupars, 
                                       double mW, double mB) :
mw_(mW),
mw_sqr_(mW*mW),
mb_(mB),
mb_sqr_(mB*mB),
nupars_(nupars)
{
    assert(nupars.size() == 5);
}



TtFullLepKinSolver::NeutrinoSolution
TtFullLepKinSolver::getNuSolution(const TLorentzVector& LV_antilepton, 
                                  const TLorentzVector& LV_lepton, 
                                  const TLorentzVector& LV_b, 
                                  const TLorentzVector& LV_bbar,
                                  const TLorentzVector& LV_met,
                                  const double mt)
{
    TLorentzVector maxLV_neutrino  = TLorentzVector(0,0,0,0); 
    TLorentzVector maxLV_neutrinoBar = TLorentzVector(0,0,0,0);   

    //loop on top mass parameter
    double weightmax = -1;
    double q_coeff[5], q_sol[4];
    FindCoeff(LV_antilepton, LV_lepton, LV_b, LV_bbar, mt, mt, LV_met, q_coeff);
//     std::cout << "  --> called FindCoeff(" << q_coeff[0] << "," << q_coeff[1]<< "," << q_coeff[2] << "," << q_coeff[3] << "," << q_coeff[4] << ")\n";
    int NSol = quartic(q_coeff, q_sol);
    
    //loop on all solutions
    for (int isol = 0; isol < NSol; isol++) {
        NeutrinoRec(q_sol[isol]);
        double weight = WeightSolfromShape();
//         std::cout << "  --> neutrino/nubar = " << x(LV_n) << x(LV_n_) << " weight = " << weight << "\n";

        if (weight > weightmax) {
            weightmax = weight;
            maxLV_neutrino = LV_n;
            maxLV_neutrinoBar = LV_n_;
        }
    }
    
//     if (weightmax != -1 && ( LV_n.Pt() > 3500 || LV_n_.Pt() > 3500)) {
//          std::cout << "  --> neutrino/nubar = " << x(LV_n) << x(LV_n_) << " weight = " << weightmax << "\n";
//     }

    TtFullLepKinSolver::NeutrinoSolution nuSol;
    nuSol.neutrino    = maxLV_neutrino;
    nuSol.neutrinoBar = maxLV_neutrinoBar; 
    nuSol.weight = weightmax; 
    return nuSol;
}



void
TtFullLepKinSolver::FindCoeff(const TLorentzVector& al, 
                              const TLorentzVector& l,
                              const TLorentzVector& b_al,
                              const TLorentzVector& b_l,
                              const double mt, 
                              const double mat, 
                              const TLorentzVector& met,
                              double* koeficienty)
{
  double E, apom1, apom2, apom3;
  double k11, k21, k31, k41,  cpom1, cpom2, cpom3, l11, l21, l31, l41, l51, l61, k1, k2, k3, k4, k5,k6;
  double l1, l2, l3, l4, l5, l6, k15, k25, k35, k45;

  C = met.Px();
  D = met.Py();
  // right side of first two linear equations - missing pT
  
  E = (sqr(mt)-mw_sqr_-mb_sqr_)/(2*b_al.E())-mw_sqr_/(2*al.E())-al.E()+al.Px()*b_al.Px()/b_al.E()+al.Py()*b_al.Py()/b_al.E()+al.Pz()*b_al.Pz()/b_al.E();
  F = (sqr(mat)-mw_sqr_-mb_sqr_)/(2*b_l.E())-mw_sqr_/(2*l.E())-l.E()+l.Px()*b_l.Px()/b_l.E()+l.Py()*b_l.Py()/b_l.E()+l.Pz()*b_l.Pz()/b_l.E();
  
  m1 = al.Px()/al.E()-b_al.Px()/b_al.E();
  m2 = al.Py()/al.E()-b_al.Py()/b_al.E();
  m3 = al.Pz()/al.E()-b_al.Pz()/b_al.E();
  
  n1 = l.Px()/l.E()-b_l.Px()/b_l.E();
  n2 = l.Py()/l.E()-b_l.Py()/b_l.E();
  n3 = l.Pz()/l.E()-b_l.Pz()/b_l.E();
  double n3_sqr = sqr(n3);
  
  pom = E-m1*C-m2*D;
  double alE2 = sqr(al.E());
  apom1 = sqr(al.Px())-alE2;
  apom2 = sqr(al.Py())-alE2;
  apom3 = sqr(al.Pz())-alE2;
  
  k11 = 1/alE2*(sqr(mw_sqr_)/4+sqr(C)*apom1+sqr(D)*apom2+apom3*sqr(pom)/sqr(m3)+mw_sqr_*(al.Px()*C+al.Py()*D+al.Pz()*pom/m3)+2*al.Px()*al.Py()*C*D+2*al.Px()*al.Pz()*C*pom/m3+2*al.Py()*al.Pz()*D*pom/m3);
  k21 = 1/alE2*(-2*C*m3*n3*apom1+2*apom3*n3*m1*pom/m3-mw_sqr_*m3*n3*al.Px()+mw_sqr_*m1*n3*al.Pz()-2*al.Px()*al.Py()*D*m3*n3+2*al.Px()*al.Pz()*C*m1*n3-2*al.Px()*al.Pz()*n3*pom+2*al.Py()*al.Pz()*D*m1*n3);
  k31 = 1/alE2*(-2*D*m3*n3*apom2+2*apom3*n3*m2*pom/m3-mw_sqr_*m3*n3*al.Py()+mw_sqr_*m2*n3*al.Pz()-2*al.Px()*al.Py()*C*m3*n3+2*al.Px()*al.Pz()*C*m2*n3-2*al.Py()*al.Pz()*n3*pom+2*al.Py()*al.Pz()*D*m2*n3);
  k41 = 1/alE2*(2*apom3*m1*m2*n3_sqr+2*al.Px()*al.Py()*sqr(m3)*n3_sqr-2*al.Px()*al.Pz()*m2*m3*n3_sqr-2*al.Py()*al.Pz()*m1*m3*n3_sqr);
  k51 = 1/alE2*(apom1*sqr(m3)*n3_sqr+apom3*sqr(m1)*n3_sqr-2*al.Px()*al.Pz()*m1*m3*n3_sqr);
  k61 = 1/alE2*(apom2*sqr(m3)*n3_sqr+apom3*sqr(m2)*n3_sqr-2*al.Py()*al.Pz()*m2*m3*n3_sqr);
  
  double lE_sqr = sqr(l.E());
  cpom1 = sqr(l.Px())-lE_sqr;
  cpom2 = sqr(l.Py())-lE_sqr;
  cpom3 = sqr(l.Pz())-lE_sqr;
  
  l11 = 1/lE_sqr*(sqr(mw_sqr_)/4+cpom3*sqr(F)/n3_sqr+mw_sqr_*l.Pz()*F/n3);
  l21 = 1/lE_sqr*(-2*cpom3*F*m3*n1/n3+mw_sqr_*(l.Px()*m3*n3-l.Pz()*n1*m3)+2*l.Px()*l.Pz()*F*m3);
  l31 = 1/lE_sqr*(-2*cpom3*F*m3*n2/n3+mw_sqr_*(l.Py()*m3*n3-l.Pz()*n2*m3)+2*l.Py()*l.Pz()*F*m3);
  l41 = 1/lE_sqr*(2*cpom3*n1*n2*sqr(m3)+2*l.Px()*l.Py()*sqr(m3)*n3_sqr-2*l.Px()*l.Pz()*n2*n3*sqr(m3)-2*l.Py()*l.Pz()*n1*n3*sqr(m3));
  l51 = 1/lE_sqr*(cpom1*sqr(m3)*n3_sqr+cpom3*sqr(n1)*sqr(m3)-2*l.Px()*l.Pz()*n1*n3*sqr(m3));
  l61 = 1/lE_sqr*(cpom2*sqr(m3)*n3_sqr+cpom3*sqr(n2)*sqr(m3)-2*l.Py()*l.Pz()*n2*n3*sqr(m3));
  
  k1 = k11*k61;
  k2 = k61*k21/k51;
  k3 = k31;
  k4 = k41/k51;
  k5 = k61/k51;
  k6 = 1;
  
  l1 = l11*k61;
  l2 = l21*k61/k51;
  l3 = l31;
  l4 = l41/k51;
  l5 = l51*k61/(sqr(k51));
  l6 = l61/k61;
  
  k15 = k1*l5-l1*k5;
  k25 = k2*l5-l2*k5;
  k35 = k3*l5-l3*k5;
  k45 = k4*l5-l4*k5;
  
  k16 = k1*l6-l1*k6;
  k26 = k2*l6-l2*k6;
  k36 = k3*l6-l3*k6;
  k46 = k4*l6-l4*k6;
  k56 = k5*l6-l5*k6;

  koeficienty[0] = k15*sqr(k36)-k35*k36*k16-k56*sqr(k16);
  koeficienty[1] = 2*k15*k36*k46+k25*sqr(k36)+k35*(-k46*k16-k36*k26)-k45*k36*k16-2*k56*k26*k16;
  koeficienty[2] = k15*sqr(k46)+2*k25*k36*k46+k35*(-k46*k26-k36*k56)-k56*(sqr(k26)+2*k56*k16)-k45*(k46*k16+k36*k26);
  koeficienty[3] = k25*sqr(k46)-k35*k46*k56-k45*(k46*k26+k36*k56)-2*sqr(k56)*k26;
  koeficienty[4] = -k45*k46*k56-pow(k56,3);
  
  // normalization of coefficients
  int moc=(int(std::log10(std::fabs(koeficienty[0])))+int(std::log10(std::fabs(koeficienty[4]))))/2;
  
  double normalisation = 1/TMath::Power(10,moc);
  //transform(koeficienty, koeficienty + 5, koeficienty, [=](double old){return old*normalisation;});
  koeficienty[0]*=normalisation;
  koeficienty[1]*=normalisation;
  koeficienty[2]*=normalisation;
  koeficienty[3]*=normalisation;
  koeficienty[4]*=normalisation;
}



void TtFullLepKinSolver::NeutrinoRec(const double sol)
{
    double pxp, pyp, pzp, pup, pvp, pwp;
        
    pxp = sol*(m3*n3/k51);   
    pyp = -(m3*n3/k61)*(k56*pow(sol,2) + k26*sol + k16)/(k36 + k46*sol);
    pzp = -1/n3*(n1*pxp + n2*pyp - F);
    pwp = 1/m3*(m1*pxp + m2*pyp + pom);
    pup = C - pxp;
    pvp = D - pyp;
        
    LV_n_.SetXYZM(pxp, pyp, pzp, 0.0);
    LV_n.SetXYZM(pup, pvp, pwp, 0.0);
}



double
TtFullLepKinSolver::WeightSolfromShape() const
{
    return nupars_[0] * TMath::Landau(LV_n.E(), nupars_[1], nupars_[2], 0) 
                      * TMath::Landau(LV_n_.E(), nupars_[3], nupars_[4], 0);

}



int
TtFullLepKinSolver::quartic(const double *koeficienty, double* koreny) const
{
  double w, b0, b1, b2;
  double c[4];
  double d0, d1, h, t, z;
  double *px;
 
  if (koeficienty[4]==0.0) 
    return cubic(koeficienty, koreny);
  /* quartic problem? */
  w = koeficienty[3]/(4*koeficienty[4]);
  /* offset */
  b2 = -6*sqr(w) + koeficienty[2]/koeficienty[4];
  /* koeficienty. of shifted polynomial */
  b1 = (8*sqr(w) - 2*koeficienty[2]/koeficienty[4])*w + koeficienty[1]/koeficienty[4];
  b0 = ((-3*sqr(w) + koeficienty[2]/koeficienty[4])*w - koeficienty[1]/koeficienty[4])*w + koeficienty[0]/koeficienty[4];

  c[3] = 1.0;
  /* cubic resolvent */
  c[2] = b2;
  c[1] = -4*b0;
  c[0] = sqr(b1) - 4*b0*b2;
  
  cubic(c, koreny);
  z = koreny[0];
  //double z1=1.0,z2=2.0,z3=3.0;
  //TMath::RootsCubic(c,z1,z2,z3);
  //if (z2 !=0) z = z2;
  //if (z1 !=0) z = z1;
  /* only lowermost root needed */

  int nreal = 0;
  px = koreny;
  t = std::sqrt(0.25*sqr(z) - b0);
  for(int i=-1; i<=1; i+=2) {
    d0 = -0.5*z + i*t;
    /* coeffs. of quadratic factor */
    d1 = (t!=0.0)? -i*0.5*b1/t : i*std::sqrt(-z - b2);
    h = 0.25*sqr(d1) - d0;
    if (h>=0.0) {
      h = std::sqrt(h);
      nreal += 2;
      *px++ = -0.5*d1 - h - w;
      *px++ = -0.5*d1 + h - w;
    }
  }

  //  if (nreal==4) {
    /* sort results */
//    if (koreny[2]<koreny[0]) SWAP(koreny[0], koreny[2]);
//    if (koreny[3]<koreny[1]) SWAP(koreny[1], koreny[3]);
//    if (koreny[1]<koreny[0]) SWAP(koreny[0], koreny[1]);
//    if (koreny[3]<koreny[2]) SWAP(koreny[2], koreny[3]);
//    if (koreny[2]<koreny[1]) SWAP(koreny[1], koreny[2]);
//  }
  return nreal;

}

int
TtFullLepKinSolver::cubic(const double *coeffs, double* koreny) const
{
  unsigned nreal;
  double w, p, q, dis, h, phi;
  
  if (coeffs[3]!=0.0) {
    /* cubic problem? */
    w = coeffs[2]/(3*coeffs[3]);
    p = sqr(coeffs[1]/(3*coeffs[3])-sqr(w))*(coeffs[1]/(3*coeffs[3])-sqr(w));
    q = -0.5*(2*sqr(w)*w-(coeffs[1]*w-coeffs[0])/coeffs[3]);
    dis = sqr(q)+p;
    /* discriminant */
    if (dis<0.0) {
      /* 3 real solutions */
      h = q/std::sqrt(-p);
      if (h>1.0) h = 1.0;
      /* confine the argument of */
      if (h<-1.0) h = -1.0;
      /* acos to [-1;+1] */
      phi = acos(h);
      p = 2*TMath::Power(-p, 1.0/6.0);
      for(unsigned i=0; i<3; i++) 
        koreny[i] = p*std::cos((phi+2*i*TMath::Pi())/3.0) - w;
      if (koreny[1]<koreny[0]) std::swap(koreny[0], koreny[1]);
      /* sort results */
      if (koreny[2]<koreny[1]) std::swap(koreny[1], koreny[2]);
      if (koreny[1]<koreny[0]) std::swap(koreny[0], koreny[1]);
      nreal = 3;
    }
    else {
      /* only one real solution */
      dis = std::sqrt(dis);
      h = TMath::Power(std::fabs(q+dis), 1.0/3.0);
      p = TMath::Power(std::fabs(q-dis), 1.0/3.0);
      koreny[0] = ((q+dis>0.0)? h : -h) + ((q-dis>0.0)? p : -p) -  w;
      nreal = 1;
    }

    /* Perform one step of a Newton iteration in order to minimize
       round-off errors */
    for(unsigned i=0; i<nreal; i++) {
      h = coeffs[1] + koreny[i] * (2 * coeffs[2] + 3 * koreny[i] * coeffs[3]);
      if (h != 0.0)
        koreny[i] -= (coeffs[0] + koreny[i] * (coeffs[1] + koreny[i] * (coeffs[2] + koreny[i] * coeffs[3])))/h;
    }
  }

  else if (coeffs[2]!=0.0) {
    /* quadratic problem? */
    p = 0.5*coeffs[1]/coeffs[2];
    dis = sqr(p) - coeffs[0]/coeffs[2];
    if (dis>=0.0) {
      /* two real solutions */
      dis = std::sqrt(dis);
      koreny[0] = -p - dis;
      koreny[1] = -p + dis;
      nreal = 2;
    }
    else
      /* no real solution */
      nreal = 0;
  }

  else if (coeffs[1]!=0.0) {
    /* linear problem? */
    koreny[0] = -coeffs[0]/coeffs[1];
    nreal = 1;
  }

  else
    /* no equation */
    nreal = 0;
  
  return nreal;
}



TtDilepEvtSolution 
TtFullLepKinSolver::GetKinSolution(const TLorentzVector& leptonMinus, const TLorentzVector& leptonPlus, 
                                   const TLorentzVector& b, const TLorentzVector& bbar, 
                                   const TLorentzVector& met, const double topMass)
{
    
    const auto nuSol = getNuSolution(leptonPlus, leptonMinus , b, bbar, met, topMass);
    TtDilepEvtSolution sol;
    sol.weight = nuSol.weight;
            
    // add solution to the vectors of solutions if solution exists 
    if(nuSol.weight>0){
        // add the leptons and jets indices to the vector of combinations
        sol.jetB = b;
        sol.jetBbar = bbar;
        sol.lm = leptonMinus; sol.lp = leptonPlus;
        sol.met = met;
        sol.neutrino = nuSol.neutrino;
        sol.neutrinoBar = nuSol.neutrinoBar;
        sol.weight = nuSol.weight;
        
        sol.Wplus = sol.lp + sol.neutrino;
        sol.Wminus = sol.lm + sol.neutrinoBar;
        
        sol.top = sol.Wplus + sol.jetB;
        sol.topBar = sol.Wminus + sol.jetBbar;
        
        sol.ttbar = sol.top + sol.topBar;
    }
    return sol;
}



std::vector<TtDilepEvtSolution> 
GetKinSolutions(const LV& leptonMinus, const LV& leptonPlus, 
                const VLV *jets, const std::vector<double> *btags, 
                const LV* met)
{
    std::vector<TtDilepEvtSolution> result;
    //std::vector<double> nu {30.7137,56.2880,23.0744,59.1015,24.9145}; //old defaults
    static std::vector<double> nu {30.641, 57.941, 22.344, 57.533, 22.232}; //in ntuple
    //std::vector<double> nu {35., 70., 20., 75., 21.}; //in ntuple
    
    static TtFullLepKinSolver solver(nu, 80.4, 4.8);
    
    
    TLorentzVector leptonPlus_tlv = ttbar::LVtoTLV(leptonPlus);
    TLorentzVector leptonMinus_tlv = ttbar::LVtoTLV(leptonMinus);
    TLorentzVector met_tlv = ttbar::LVtoTLV(*met);
    
    std::vector<TLorentzVector> jets_tlv;
    for (const auto& jet : *jets) {
        jets_tlv.push_back(ttbar::LVtoTLV(jet));
    }
    
    size_t max_jets = jets_tlv.size(); //run over all 'googd' jets
    
    // consider all permutations
    for (size_t ib = 0; ib < max_jets; ++ib) {
        for (size_t ibbar = 0; ibbar < max_jets; ++ibbar) {
            // avoid the diagonal: b and bbar must be distinct jets
            if (ib == ibbar) continue;
            constexpr double BtagWP = 0.244;
            int ntags = btags->at(ib) > BtagWP;
            ntags += btags->at(ibbar) > BtagWP;
            
            //only use jet combinations with at least one tag
            if (ntags == 0) continue;
            
            TtDilepEvtSolution best;
            double weightBest = 0;
            
            
            // !!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!
            //When changing this, please also make sure the SF for the KinReco 
            //is using the correct values!!
            //See prepareKinRecoSF in Analysis.C            
            // !!!!!!!!!!!!!!!!!!WARNING!!!!!!!!!!!!!!!!
            
            for(double topMass = 100; topMass < 300.5; topMass += 1) 
//             for(double topMass = 163; topMass < 183.5; topMass += 1) 
//             double topMass = 173;
            {
//                 std::cout << "input = " << x(leptonPlus_tlv) << x(leptonMinus_tlv) 
//                         << x(jets_tlv.at(ib)) << x(jets_tlv.at(ibbar)) << "\n";
                 auto sol = solver.GetKinSolution(leptonMinus_tlv, leptonPlus_tlv, 
                                                  jets_tlv.at(ib), jets_tlv.at(ibbar), met_tlv, topMass);
                 if (sol.weight > 0) {
                    sol.ntags = ntags;
                    //try to modify the weight
                    if (sol.weight > weightBest) {
                        weightBest = sol.weight;
                        best = sol;
                        best.jetB_index = ib;
                        best.jetBbar_index = ibbar;
                    }
                 }
            }
            if (weightBest > 0) {
                result.push_back(best);
            }
        }
    }           
  
    // sort vectors by weight in decreasing order
    // - actually, we only need the best element!
    // - so using nth_element instead of sort. Use sort if you need all elements sorted
    // std::sort(begin(result), end(result),          
//     result.erase(remove_if(begin(result), end(result), 
//         [](const TtDilepEvtSolution &s){
//             return abs(s.top.M() - 173) > 1;
//         }), end(result));
            
    std::nth_element(begin(result), begin(result), end(result),
        [](const TtDilepEvtSolution& a, const TtDilepEvtSolution& b){
            return  b.ntags < a.ntags
                    ||
                    (b.ntags == a.ntags && b.weight < a.weight);
        });

    return result;
}





//unused code - Haryo's implementation
/*
#ifdef run_sonnenschein
    auto solver = llsolver::DileptonAnalyticalSolver();
    
    double lp[4], lm[4], b[4], bb[4];
    double ETmiss[2], nu[4], nub[4];
    std::vector<double> pnux, pnuy, pnuz, pnubx, pnuby, pnubz;
    std::vector<double> pnuychi2, pnunubzchi2, pnuyzchi2, cd_diff;
    int cubic_single_root_cmplx;
    
    ttbar::LVtod4(leptonPlus, lp);
    ttbar::LVtod4(leptonMinus, lm);
    ttbar::LVtod4(HypBJet->at(solutionIndex), b);
    ttbar::LVtod4(HypAntiBJet->at(solutionIndex), bb);

    ETmiss[0] = met->Px();
    ETmiss[1] = met->Py();
    
    
if (HypTop->size()) {    
    std::cout << "GenMet/RecoMet" << *GenMet << " / " << *met << std::endl;
    std::printf("true level  x=%.2f, y=%.2f\n", GenNeutrino->Px(), GenNeutrino->Py());    
    std::printf("OLAANALYSIS x=%.2f, y=%.2f\n", HypNeutrino->at(solutionIndex).Px(), HypNeutrino->at(solutionIndex).Py());

    solver.solve(ETmiss, b, bb, lp, lm, 80.4, 80.4, 172.5, 172.5, 0, 0,
                 &pnux, &pnuy, &pnuz, &pnubx, &pnuby, &pnubz, &cd_diff, cubic_single_root_cmplx);
    for (size_t i=0; i<pnux.size(); ++i) {
        std::cout << "SONNENSCHEI x=" << pnux[i] << " y=" << pnuy[i]<< std::endl;
     
        h_HypTopptSonnenschein->Fill((), weight);
    }
    //exit(100);
    std::cout<<std::endl;
}

#endif
*/



