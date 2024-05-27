#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "TH1F.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"


using namespace std;

void beautify(TH1F* &hist,
	      int color,
	      string xaxis,
	      string yaxis) {

  hist->SetTitle(0);
  hist->SetStats(0);
  hist->SetLineColor(color);
  hist->SetLineWidth(2);
  hist->GetXaxis()->SetTitleFont(42);
  hist->GetXaxis()->SetTitleSize(0.05);
  hist->GetXaxis()->SetTitle(xaxis.c_str());
  hist->GetYaxis()->SetTitleFont(42);
  hist->GetYaxis()->SetTitleSize(0.05);
  hist->GetYaxis()->SetLabelOffset(1.2);
  hist->GetYaxis()->SetTitle(yaxis.c_str());

}


void makeSomePlots(const string variable,
		   const string cuts,
		   const float xlow,
		   const float xhigh,
		   const int nbins,
		   const string xaxistitle,
		   const string plotfilename,
		   const string infilename)
{
  TTree* t = dynamic_cast<TTree*>(TFile::Open(infilename.c_str())->Get("tree"));

  // PT plots - when there is a W in the event...
  TH1F* h_e = new TH1F("h_e","h_e",nbins,xlow, xhigh);
  TH1F* h_m = new TH1F("h_m","h_m",nbins,xlow, xhigh);
  TH1F* h_t = new TH1F("h_t","h_t",nbins,xlow, xhigh);
  
  h_e->Sumw2();
  h_m->Sumw2();
  h_t->Sumw2();

  cout << "Variable: " << variable.c_str() << endl;
  cout << "Cuts: " << cuts.c_str() << endl;
  
  t->Project("h_e",variable.c_str(),Form("%s&&abs(pid)==11",cuts.c_str()));
  t->Project("h_m",variable.c_str(),Form("%s&&abs(pid)==13",cuts.c_str()));
  t->Project("h_t",variable.c_str(),Form("%s&&abs(pid)==15",cuts.c_str()));

  cout << "Chi2 probability: ele vs muo " << h_e->Chi2Test(h_m) << endl;
  cout << "Chi2 probability: muo vs tau " << h_m->Chi2Test(h_t) << endl;
  cout << "Chi2 probability: tau vs ele " << h_t->Chi2Test(h_e) << endl;

  h_e->Scale(1./h_e->Integral());
  h_m->Scale(1./h_m->Integral());
  h_t->Scale(1./h_t->Integral());

  beautify(h_e,kBlue,xaxistitle.c_str(),"Entries");
  beautify(h_m,kRed,xaxistitle.c_str(),"Entries");
  beautify(h_t,kGreen,xaxistitle.c_str(),"Entries");
  
  TLegend* leg = new TLegend(0.8,0.60,0.9,0.89);
  leg->SetEntrySeparation(-0.25);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->AddEntry(h_e,"e","l");
  leg->AddEntry(h_m,"#mu","l");
  leg->AddEntry(h_t,"#tau","l");

  TCanvas *canv = new TCanvas("canvas","canvas",600,500);
  canv->Draw();
  h_e->Draw();
  h_m->Draw("same");
  h_t->Draw("same");
  leg->Draw("same");

  canv->Print((plotfilename+".png").c_str());

}

int main(int argc,char *argv[])
{
  if (argc<=1)
    cout << "Ah, provide at least the name of the variable to plot!" << endl
	 << "Usage: " << endl << endl
	 << "./makeSomePlots \"VAR\" \"CUTS\" \"LOWBIN\" \"HIGHBIN\" \"NBINS\""
	 << " \"XAXISTITLE\" \"PLOTFILENAME\" \"TREEFILENAME\" " << endl
	 << endl
	 << "E.g.: " << endl << endl
	 << "./makeSomePlots \"-(pz)/abs(pz)*log(tan(atan2(sqrt(px*px+py*py)"
	 << ",abs(pz))/2))\" \"mo1==3\" 30 \"-3\" \"3\" \"#eta\" eta"
	 << " out_long.root"
	 << endl << endl;
  else
    makeSomePlots(argv[1],
		  argc>2?argv[2]:"1",
		  argc>3?::strtod(argv[3],0):0.,
		  argc>4?::strtod(argv[4],0):200.,
		  argc>5?::stoi(argv[5],0):40.,
		  argc>6?argv[6]:"p_{T} [GeV]",
		  argc>7?argv[7]:"plots",
		  argc>8?argv[8]:"out_long.root");
}
