#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "TH1F.h"
#include "TTree.h"
#include "TFile.h"


using namespace std;


void lhe2root(const string infilename,
	      const string outfilename)
{

  ifstream file;
  
  file.open(infilename.c_str());
  
  int evt;
  unsigned int n;
  int pid;
  int status;
  int mo1;
  int mo2;
  int dummy1;
  int dummy2;
  float px;
  float py;
  float pz;
  float energy;
  float mass;
  float decaytime;
  float spin;
  TTree* tree = new TTree("tree","tree");
  tree->Branch("evt",&evt);
  tree->Branch("n",&n);
  tree->Branch("pid",&pid);
  tree->Branch("status",&status);
  tree->Branch("mo1",&mo1);
  tree->Branch("mo2",&mo2);
  tree->Branch("px",&px);
  tree->Branch("py",&py);
  tree->Branch("pz",&pz);
  tree->Branch("energy",&energy);
  tree->Branch("mass",&mass);
  tree->Branch("decaytime",&decaytime);
  tree->Branch("spin",&spin);

  // Temporary variables
  float dummy[5];


  unsigned int counter = 0; // at some point, give up reading the file
  const unsigned int MAX = 4000000;
  if (file) {

    evt = 0;
    // read file line into string store
    while (!file.eof() && counter < MAX ) {
      string store;
      file >> store;
      
      // here I found the beginning of one event
      if (store.find("<event>") == 0) {

	++evt;

	if (evt % 1000 == 0)
	  cout << "Working on event " << evt << endl;
	
	// the first line contains event info
	// the next variables need to be identified, for the moment
	// I will throw them away
	file >> n >> dummy[0] >> dummy[1] >> dummy[2] >> dummy[3] >> dummy[4];
	
	// Loop on particles
	for (unsigned int i=0;i<n;i++) {
	  pid = 0;
	  status = 0;
	  mo1 = 0;
	  mo2 = 0;
	  dummy1 = 0;
	  dummy2 = 0;
	  px = 0.;
	  py = 0.;
	  pz = 0.;
	  mass = 0.;
	  energy = 0.;
	  decaytime = 0.;
	  spin = 0.;

	  file >> pid >> status >> mo1 >> mo2 >> dummy1 >> dummy2
	       >> px >> py >> pz >> energy >> mass >> decaytime >> spin;
	  
	  // I need to fill the tree at each particle...
	  tree->Fill();

	}
      }//if store
    }//while
    ++counter;
  }//if file
  
  TFile *f = new TFile(outfilename.c_str(),"RECREATE");
  
  tree->Write();
  
  f->Close();
  
  
}

int main(int argc,char *argv[])
{
  lhe2root(argc>1?argv[1]:"cmsgrid_final_10k.lhe",
	   argc>2?argv[2]:"out.root");
}
