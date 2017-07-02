#include "Tree.h"
#include <TFile.h>
#include <TBranch.h>
#include <iostream>

namespace Tracking{

Tree *Tree::s_instance = 0;
Tree* Tree::instance() {
        if (!s_instance)
          s_instance = new Tree;
        return s_instance;
    }


void Tree::ReadTree(std::string rootFl, std::string treeName){
  std::cout<<"----------- Entered NewReadTree-2 ---------------" << std::endl;
  d = new ROOT::Experimental::TDataFrame(treeName.c_str(), rootFl.c_str());
  f = TFile::Open(rootFl.c_str(), "READ");
  f->GetObject(treeName.c_str(), t);
  numOfEvents = t->GetEntries();
  //numOfEvents = d->Count();

}


Tree::Tree(){
	numOfEvents = 100;
	//rootFile = "test.root";
	//sRootFile = rootFile;
}

Tree::Tree(std::string rootFl){

  rootFile = rootFl;
  f = TFile::Open(rootFile.c_str(),"READ");
  if (!f) { return; }
  f->GetObject("BSC_DATA_TREE",t);
  numOfEvents = t->GetEntries();
  //f->Close();

}


Tree::Tree(std::string rootFl, std::string treeName, int rw){

  rootFile = rootFl;
  fTreeName = treeName;
  //t = new TTree(treeName.c_str(),"A Tree with STL vectors");
  if (rw)
    f = TFile::Open(rootFile.c_str(), "RECREATE");
  else {
    f = TFile::Open(rootFile.c_str(), "READ");
    if (!f) {
      return;
    }
    f->GetObject(treeName.c_str(), t);
    numOfEvents = t->GetEntries();
  }
  //f->Close();

}


Tree::~Tree(){ f->Close(); }

void Tree::TreeW(){

	//TFile f(rootFile.c_str(),"RECREATE");
#if(0)
	f = TFile::Open(rootFile.c_str(), "RECREATE");
	Channel ch;
	TTree t(fTreeName.c_str(),"A Tree with STL vectors");
    t.Branch("channel",&ch);

    numOfEvents =10;
    for(int i= 0 ; i < numOfEvents ; i++){
    	ch.clear(); // clearing the vector
    	ch.push_back(1);
    	ch.push_back(8);
   		ch.push_back(3);

    	t.Fill();
    }

    f->Write();
#endif

    //Using modified tree
    InitializeTreeForWriting();
    Channel ch;
    CreateBranch<Channel>("channel",ch);
    numOfEvents =10;
        for(int i= 0 ; i < numOfEvents ; i++){
        	ch.clear(); // clearing the vector
        	ch.push_back(1);
        	ch.push_back(8);
       		ch.push_back(3);
       		Fill();
        }

     WriteToFile();

 
}


void Tree::WriteToFile(){
	f->Write();
}


void Tree::FillBranchNamesVector(){
  TObjArray *listOfBranches = t->GetListOfBranches();
  TIter iObj(listOfBranches);
  while (TObject *obj = iObj()) {
	  std::string name = (std::string)obj->GetName();
      fBranchNamesVector.push_back(name);
  }
}

void Tree::PrintBranchNames() {
  for (int i = 0; i < fBranchNamesVector.size(); i++) {
    std::cout << fBranchNamesVector[i] << std::endl;
  }
}
} /*end of Tomography namespace*/
