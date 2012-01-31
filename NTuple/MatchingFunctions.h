//==============================================
//  How to use MatchingFunctions tools:
//   -> It provides the number of matches for LV, vector<LV>: Matching( ,  , Deltar_max)
//   -> It gives also the DeltaR size
//   -> be careful with the order:
//   ConeSize(LV1, LV2)= LV1.DeltaR(LV2)
//==============================================



#include <vector>
#include <iostream>
#include "TLorentzVector.h"
#include "TMath.h"





// double ConeSize(TLorentzVector LV1, TLorentzVector LV2){
// 	double deltar_=-10.0;
// 	deltar_=LV1.DeltaR(LV2);
// 	return deltar_;
// 	
// }



// //Still work in progress

int Matching(TLorentzVector LV1, std::vector<TLorentzVector>LV2, TLorentzVector LV3, double deltar=0.5){

	if (deltar<=0.0){
		std::cout<<"WARNING: With DeltaR= "<<deltar<<" can't do the matching !!!!!!!!!!"<<std::endl;
		return -1;
	};
	if (LV2.size()<1){
		std::cout<<"WARNING: Some TLorentzVector VECTOR's have no entries !!!!!!!!!!!!"<<std::endl;
		return -1;
	};

	int counter=0;
	for (int i=0; i<(int)LV2.size(); i++){
	  double size1=LV1.DeltaR(LV2[i]);
	  double size2=LV3.DeltaR(LV2[i]);
	  if (size1<deltar && size1>0.0){
	    if (size2<deltar && size2>0.0) counter++;
	  }
	}
	
	return counter;


};


int Matching(std::vector<TLorentzVector> LV1, std::vector<TLorentzVector> LV2, double deltar=0.5)
{
  //	std::cout<<"Matching TLorentzVector VECTOR to a TLorentzVector VECTOR"<<std::endl;
	if (deltar<=0.0){
		std::cout<<"WARNING: With DeltaR= "<<deltar<<" can't do the matching !!!!!!!!!!"<<std::endl;
		return -1;
	};
	if (LV1.size()<1 || LV2.size()<1 ) {
		std::cout<<"WARNING: The TLorentzVector VECTOR's have no entries !!!!!!!!!!!!"<<std::endl;
		return -1;
	};
		
	if (LV1.size()>=1 && LV2.size()>=1){
		int counter=0;
		for (int i=0; i<(int)LV1.size(); i++){
			for (int j=0; j<(int)LV2.size(); j++){
			  double size=LV1[i].DeltaR(LV2[j]);
			  if (size<deltar && size>0.0)	counter++;
			};
		};
		return counter;
	}
	else return -1;
}



int Matching(std::vector<TLorentzVector> LV1, TLorentzVector LV2, double deltar=0.5)
{
  //	std::cout<<"Matching TLorentzVector to a TLorentzVector VECTOR"<<std::endl;
	if (deltar<=0.0){
		std::cout<<"WARNING: With DeltaR= "<<deltar<<" can't do the matching !!!!!!!!!!"<<std::endl;
		return -1;
		};
	if (LV1.size()<1 ) {
		std::cout<<"WARNING: The TLorentzVector VECTOR's have no entries !!!!!!!!!!!!"<<std::endl;
		return -1;
	};
		
	if (LV1.size()>=1){
		int counter=0;
		for (int i=0; i<(int)LV1.size(); i++){
		  double size=LV1[i].DeltaR(LV2);
		  if (size<deltar && size>0.0)	counter++;
		};
		return counter;
	}
	else return -1;
};



int Matching(TLorentzVector LV1, std::vector<TLorentzVector> LV2, double deltar=0.5)
{
  //	std::cout<<"Matching TLorentzVector to a TLorentzVector VECTOR"<<std::endl;
	if (deltar<=0.0){
		std::cout<<"WARNING: With DeltaR= "<<deltar<<" can't do the matching !!!!!!!!!!"<<std::endl;
		return -1;
		};
	if (LV2.size()<1 ) {
		std::cout<<"WARNING: The TLorentzVector VECTOR's have no entries !!!!!!!!!!!!"<<std::endl;
		return -1;
	};
		
	if (LV2.size()>=1){
		int counter=0;
		for (int i=0; i<(int)LV2.size(); i++){
		  double size=LV1.DeltaR(LV2[i]);
		  if (size<deltar && size>0.0)	counter++;
		};
		return counter;
	}
	else return -1;
};


int Matching(TLorentzVector LV1, TLorentzVector LV2, double deltar=0.5)
{
  //	std::cout<<"Matching TLorentzVector to a TLorentzVector"<<std::endl;
	if (deltar<=0.0){
		std::cout<<"WARNING: With DeltaR= "<<deltar<<" can't do the matching !!!!!!!!!!"<<std::endl;
		return -1;
	};
		
	int counter=0;
	double size=LV1.DeltaR(LV2);
	if (size<deltar && size>0.0)	counter++;

	return counter;
};

