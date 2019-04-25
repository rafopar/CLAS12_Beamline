#define Analyze_Harp_Scans_cxx
#include "Analyze_Harp_Scans.h"
#include <TH2.h>
#include <TFile.h>
#include <fstream>
#include <TGraph.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTimeStamp.h>

using namespace std;

void SaveFormatGraph(TGraph *gr, string name, int style, int col);

void Analyze_Harp_Scans::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyze_Harp_Scans.C
//      root> Analyze_Harp_Scans t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TTimeStamp *tmstmp = new TTimeStamp();

   string harp_name = "2H01";
   
   TFile *file_out = new TFile(Form("Harp_%s_hists.root", harp_name.c_str()), "Recreate");
   
   TGraph *gr_sigm_x = new TGraph();

   TGraph *gr_sigm_x_Acceptable = new TGraph();

   TH1D *h_sigmX_Spr2019_1 = new TH1D("h_sigmX_Spr2019_1", "", 10, 0.15, 0.35);
   TH1D *h_sigmY_Spr2019_1 = new TH1D("h_sigmY_Spr2019_1", "", 10, 0.15, 0.35);

   TGraph *gr_sigm_y_Acceptable_Spr_2019 = new TGraph();
   TGraph *gr_sigm_x_Acceptable_Spr_2019 = new TGraph();

   TGraph *gr_mean_y_Acceptable_Spr_2019 = new TGraph();
   TGraph *gr_mean_x_Acceptable_Spr_2019 = new TGraph();
   
   // In Harp scans the time is calculated from the following offset (Not from the epoch)
   tmstmp->Set(2014, 9, 1, 0, 0, 0, 0, true, 0);

   Long64_t offset = tmstmp->GetSec();

   Long64_t prev_time = 0;
   int i_Acceptable = 0;

   double sigm_y_prev;
   double sigm_x_prev;

   int spr_2019_counter = 0;
   
   ofstream out_dat("2H01_scan_parameters.dat");
   //ofstream out_dat("2C21_scan_parameters.dat");
   //ofstream out_dat("tagger_scan_parameters.dat");
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      Long64_t time_since_epoch = time + offset;
      tmstmp->SetSec(time_since_epoch);

      unsigned int Date = tmstmp->GetDate();
      int year = int(Date/10000);
      int Mon_Day = Date%10000;
      int Month = int(Mon_Day/100);
      int day = Mon_Day%100;
      
      unsigned int time_of_Day = tmstmp->GetTime();
      int hour = int(time_of_Day/10000);
      int min_sec = time_of_Day%10000;
      int min = int(min_sec/100);
      int sec = min_sec%100;

      // cout<<tmstmp->AsString()<<endl;
      // cout<<year<<", "<<Month<<","<<day<<"   "<<hour<<":"<<min<<":"<<sec<<endl;

      double day_Dirty = (time - 100012801)/(24.*3600.);

      gr_sigm_x->SetPoint(jentry, time_since_epoch, sigma_x);
      
	
      if(jentry == 0 ){
	prev_time = time;
      }

      Long64_t delt_t = time - prev_time;
      cout<<"delt_t = "<<delt_t<<endl;
      if( delt_t > 36000 ){
	i_Acceptable = i_Acceptable + 1;

	// The period after February 19 2019, when broken harp wire got fixed
	if( year == 2019 && ((Month == 2 && day > 19) || Month > 2)){
	  h_sigmX_Spr2019_1->Fill(sigm_x_prev);
	  h_sigmY_Spr2019_1->Fill(sigm_y_prev);

	  gr_sigm_y_Acceptable_Spr_2019->SetPoint(spr_2019_counter, time_since_epoch, sigma_y);
	  gr_sigm_x_Acceptable_Spr_2019->SetPoint(spr_2019_counter, time_since_epoch, sigma_x);

	  gr_mean_y_Acceptable_Spr_2019->SetPoint(spr_2019_counter, time_since_epoch, mean_y);
	  gr_mean_x_Acceptable_Spr_2019->SetPoint(spr_2019_counter, time_since_epoch, mean_x);
	  
	  spr_2019_counter = spr_2019_counter + 1;
	}
	
      }
      gr_sigm_x_Acceptable->SetPoint(i_Acceptable, time_since_epoch, sigma_x);

      

      prev_time = time;
      sigm_y_prev = sigma_y;
      sigm_x_prev = sigma_x;
      
      out_dat<<time_since_epoch<<setw(10)<<year<<setw(10)<<Month<<setw(10)<<day<<setw(10)<<hour<<setw(10)<<min<<setw(10)<<sec<<setw(12)<<mean_x<<setw(12)<<mean_y<<setw(12)<<mean_45<<
	setw(12)<<sigma_x<<setw(12)<<sigma_y<<setw(12)<<sigma_45<<setw(12)<<peak_x<<setw(12)<<peak_y<<setw(14)<<peak_45<<setw(14)<<bgr_to_peak_x<<setw(14)<<bgr_to_peak_y<<setw(14)
	     <<bgr_to_peak_45<<setw(10)<<setw(12)<<counter<<setw(12)<<a<<setw(12)<<b<<setw(12)<<alpha<<endl;
      
   }

   gr_sigm_x->SetMarkerStyle(20);
   gr_sigm_x->SetMarkerSize(1.2);
   gr_sigm_x->Draw("AP");
   gr_sigm_x->GetXaxis()->SetTimeDisplay(1);
   gr_sigm_x->GetXaxis()->SetNdivisions(503);
   gr_sigm_x->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
   gr_sigm_x->GetXaxis()->SetTimeOffset(0,"gmt");
   gr_sigm_x->Write("gr_sigm_x");

   
   gr_sigm_x_Acceptable->SetMarkerStyle(22);
   gr_sigm_x_Acceptable->SetMarkerSize(1.2);
   gr_sigm_x_Acceptable->SetMarkerColor(4);
   gr_sigm_x_Acceptable->Draw("AP");
   gr_sigm_x_Acceptable->GetXaxis()->SetTimeDisplay(1);
   gr_sigm_x_Acceptable->GetXaxis()->SetNdivisions(503);
   gr_sigm_x_Acceptable->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
   gr_sigm_x_Acceptable->GetXaxis()->SetTimeOffset(0,"gmt");
   gr_sigm_x_Acceptable->Write("gr_sigm_x_Acceptable");

   gDirectory->Write();

   SaveFormatGraph(gr_sigm_y_Acceptable_Spr_2019, "gr_sigm_y_Acceptable_Spr_2019", 20, 4);
   SaveFormatGraph(gr_sigm_x_Acceptable_Spr_2019, "gr_sigm_x_Acceptable_Spr_2019", 21, 2);

   SaveFormatGraph(gr_mean_y_Acceptable_Spr_2019, "gr_mean_y_Acceptable_Spr_2019", 22, 4);
   SaveFormatGraph(gr_mean_x_Acceptable_Spr_2019, "gr_mean_x_Acceptable_Spr_2019", 23, 2);
}


void SaveFormatGraph(TGraph *gr, string name, int style, int col){

  gr->SetMarkerStyle(style);
  gr->SetMarkerSize(1.2);
  gr->SetMarkerColor(col);
  gr->Draw("AP");
  gr->GetXaxis()->SetTimeDisplay(1);
  gr->GetXaxis()->SetNdivisions(508);
  gr->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
  gr->GetXaxis()->SetTimeOffset(0,"gmt");
  gr->Write(name.c_str());
  
}
