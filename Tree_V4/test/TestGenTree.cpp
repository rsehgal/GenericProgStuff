/*
 * TestGenTree.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: rsehgal
 */

#include "Tree.h"
#include "base/Global.h"
#include "base/Vector3D.h"
#include "Track.h"
#include <iostream>
#include "TFile.h"
#include "TH1F.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TSystem.h"


int main() {
 	  gSystem->Load("libtrack.so");
	  std::cout<<"========= Entered main ======== " << std::endl;
	  Tracking::Tree *tree = Tracking::Tree::instance();
#if(0)
	  tree->SetTreeDefaultParameters();
	  tree->InitializeTreeForWriting();

	  Tracking::Vector3D<double> p1,p2;
	  Tomography::Track t;
	  tree->CreateBranch<Tracking::Vector3D<double>>("P1", p1);
	  tree->CreateBranch<Tracking::Vector3D<double>>("P2", p2);
	  tree->CreateBranch<Tomography::Track>("Track",t);

      std::vector<unsigned int>* td;
      tree->CreateBranch<std::vector<unsigned int>*>("TestData",td);


	  for(int i = 0 ; i< 100; i++){
		  p1.Set(1*i,2*i,3*i);
		  p2.Set(4*i,5*i,6*i);
		  t.SetP1(p1);
		  t.SetP2(p2);
		  tree->Fill();
	  }

	  tree->WriteToFile();
#endif

#if(0)
	  //Doing some read test using TTreeReader
	  tree->ReadTree("hello.root","BSC_DATA_TREE");
	  std::cout<<"========= reached here ======== " << std::endl;
	  //tree->GetEntry(tree->ConnectToBranch<Tomography::Track>("Track"),1);//.Print();
      for(int i = 0 ; i < 100 ; i++){
	  (tree->GetEntry<Tomography::Track>("Track",i)).Print();
      }
	  //std::cout << "size : " << (tree->GetEntry2<Tomography::Track>("Track",12)).size() << std::endl;
	  //std::cout<< "Value : " << (tree->GetEntry<double>("ScatteringAngle",11)) << std::endl;//.Print();
#endif

#if(1)
      tree->ReadTree("6928.root","BSC_DATA_TREE");
      std::cout<<"========= reached here ======== " << std::endl;
      for(int i = 0 ; i < 100 ; i++){
      //std::cout <<
       (tree->GetEntry<std::vector<unsigned int>>("Module2_LE_CH31",i));
      }
#endif

#if(0)
   TFile *myFile = TFile::Open("6928.root");
   TTreeReader myReader("BSC_DATA_TREE", myFile);
   //TTreeReaderValue<Tomography::Track> myTrack(myReader, "Track");
   //TTreeReaderValue<Tracking::Vector3D<double>> myVec(myReader, "P1");
   TTreeReaderValue<Tracking::Channel> myVec(myReader, "Module2_LE_CH31");
   
   for(int i = 0 ; i < 100 ; i++){
   myReader.SetEntry(i);
   //(*myTrack).Print();
   std::cout << "zeroth entry : " << (*myVec)[0] << std::endl;
   }

   //(*(myTrack+1)).Print();
   //myTrack.SetEntry(1);
   //myReader.Next();
   //(*myTrack).Print();
   /*while (myReader.Next()) {
      //myHist->Fill(*myPx + *myPy);
      (*myTrack).Print();
   }*/

#endif
	  return 0;
}




