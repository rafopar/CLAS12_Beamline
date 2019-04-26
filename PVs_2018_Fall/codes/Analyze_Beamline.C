#define Analyze_Beamline_cxx
#include "Analyze_Beamline.h"
#include <TH2.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <vector>
#include <iostream>

using namespace std;

void TimeFormatHist(TH2D*);

void Analyze_Beamline::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyze_Beamline.C
//      root> Analyze_Beamline t
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

   const Long64_t date_begin = 1538136000;
   const Long64_t date_end = 1546077599;
   const double day_in_sec = 3600.*24.;
   const double fcup_slope = 906.2; // Hz/nA

   const int n_samples = 15;
   const int n_atten_change = 7;

   Long64_t atten_change_times_[n_atten_change + 1] = {1537659119, 1543451519, 1543900630, 1544619897, 1544738853, 1544739089, 1544741051, 1546059600};
   double attenuation_[n_atten_change] = {9.8088, 16.283, 14.8956, 16.283, 17.3029, 17.0398, 16.9726};
   
   //   TH1D *h_Atten_varbins = new TH1D("h_Atten_varbins", "", n_atten_change, &atten_change_times_[0]);

   vector<Long64_t> v_atten_changes;

   
   for( int i = 0; i < n_atten_change + 1; i++ ){
     //h_Atten_varbins->SetBinContent(i+1, attenuation_[i]);
     v_atten_changes.push_back(atten_change_times_[i]);
   }
   
   double IPM2c21_minus1 = 0;
   double IPM2c21_minus2 = 0;

   double IPM2c24_minus1 = 0;
   double IPM2c24_minus2 = 0;

   TFile *file_out = new TFile("Analyze_Beamline.root", "Recreate");
   TH2D *h_2C21_FCup_Ratio_time1 = new TH2D("h_2C21_FCup_Ratio_time1", "", 5000, date_begin, date_end, 600, 0.85, 1.15);
   TH2D *h_2C21_FCup_Ratio_time2 = new TH2D("h_2C21_FCup_Ratio_time2", "", 5000, date_begin, date_end, 600, 0.85, 1.15);
   TH2D *h_2C21_2C24_Ratio_time1 = new TH2D("h_2C21_2C24_Ratio_time1", "", 5000, date_begin, date_end, 600, 0.85, 1.15);
   TH2D *h_2C21_2H01_Ratio_time1 = new TH2D("h_2C21_2H01_Ratio_time1", "", 5000, date_begin, date_end, 600, 0.85, 1.15);
   TH2D *h_2C24_2H01_Ratio_time1 = new TH2D("h_2C24_2H01_Ratio_time1", "", 5000, date_begin, date_end, 600, 0.85, 1.15);

   TH2D *h_fCup_Offset_time1 = new TH2D("h_fCup_Offset_time1", "", 5000, date_begin, date_end, 600., 0., 800.);
   
   TH2D *h_2C21_FCup_Ratio_time_Zoom1 = new TH2D("h_2C21_FCup_Ratio_time_Zoom1", "", 1000, 28.6, 29.2, 600, 0.85, 1.15);
   TH2D *h_2C21_2C24_Ratio_time2 = new TH2D("h_2C21_2C24_Ratio_time2", "", 5000, date_begin, date_end, 600, 0.85, 1.15);
   TH2D *h_2C21_2C24_Ratio_time3 = new TH2D("h_2C21_2C24_Ratio_time3", "", 5000, date_begin, date_end, 600, 0.85, 1.15);

   double S2b_[n_samples] = {0};
   double I2C21_[n_samples] = {0};
   double I2C24_[n_samples] = {0};
   double I2H01_[n_samples] = {0};
   
   Long64_t nentries = fChain->GetEntriesFast();

   double calc_offset = 337;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      double time = double(Date - date_begin)/day_in_sec;

      bool prod_beam = IPM2C21A > 35 && IPM2C24A > 35 && IPM2H01 > 35 && scaler_calc1b > 35;

      bool No_beam = IPM2C21A < 0.1 && IPM2C24A < 0.1 && IPM2H01 < 0.1;

      //      vector<int>::iterator it = upper_bound(aa.begin(), aa.end(), 11)
      vector<Long64_t>::iterator it = upper_bound(v_atten_changes.begin(), v_atten_changes.end(), Date);

      int atten_bin = (it - v_atten_changes.begin()) - 1;
      
      double atten = attenuation_[atten_bin];

      double calc_current = atten*(scalerS2b - calc_offset)/fcup_slope;

      if( prod_beam ){

	h_2C21_FCup_Ratio_time_Zoom1->Fill(Date, IPM2C21A/scaler_calc1b);
	
	h_2C21_FCup_Ratio_time1->Fill(Date, IPM2C21A/scaler_calc1b);
	h_2C21_FCup_Ratio_time2->Fill(Date, IPM2C21A/calc_current);
	h_2C21_2C24_Ratio_time1->Fill(Date, IPM2C21A/IPM2C24A);
	h_2C21_2H01_Ratio_time1->Fill(Date, IPM2C21A/IPM2H01);
	h_2C24_2H01_Ratio_time1->Fill(Date, IPM2C24A/IPM2H01);

	if(jentry > 2){
	  h_2C21_2C24_Ratio_time2->Fill(Date, IPM2C21A/IPM2c24_minus1);
	  h_2C21_2C24_Ratio_time3->Fill(Date, IPM2c21_minus2/IPM2c24_minus1);
	}

	IPM2c21_minus2 = IPM2c21_minus1;
	IPM2c21_minus1 = IPM2C21A;

	IPM2c24_minus2 = IPM2c24_minus1;
	IPM2c24_minus1 = IPM2C24A;
	
      } else if( No_beam ){
	h_fCup_Offset_time1->Fill(time, scalerS2b);
      }


      
      
      S2b_[0] = scalerS2b;
      I2C21_[0] = IPM2C21A;
      I2C24_[0] = IPM2C24A;
      I2H01_[0] = IPM2H01;
      for( int ii = 0; ii < n_samples - 1; ii++ ){
	S2b_[n_samples - ii - 1] = S2b_[n_samples - ii - 2];
      }


      if( abs(I2C21_[0]) < 0.1 && abs(I2C21_[1]) < 0.1 && abs(I2C21_[2]) < 0.1 && abs(I2C21_[3]) < 0.1 && abs(I2C21_[4]) < 0.1 &&
	  abs(I2C21_[n_samples - 1]) < 0.1 && abs(I2C21_[n_samples - 2]) < 0.1 && abs(I2C21_[n_samples - 3]) < 0.1 && abs(I2C21_[n_samples - 4]) < 0.1 && abs(I2C21_[n_samples - 4]) < 0.1 &&
	  abs(I2C24_[0]) < 0.1 && abs(I2C24_[1]) < 0.1 && abs(I2C24_[2]) < 0.1 && abs(I2C24_[3]) < 0.1 && abs(I2C24_[4]) < 0.1 &&
	  abs(I2C24_[n_samples - 1]) < 0.1 && abs(I2C24_[n_samples - 2]) < 0.1 && abs(I2C24_[n_samples - 3]) < 0.1 && abs(I2C24_[n_samples - 4]) < 0.1 && abs(I2C24_[n_samples - 4]) < 0.1 ){

	calc_offset = (S2b_[5] + S2b_[6] + S2b_[7] + S2b_[8] + S2b_[9])/5.;
      }
   }

   TimeFormatHist(h_2C21_FCup_Ratio_time1);
   TimeFormatHist(h_2C21_FCup_Ratio_time2);
   
   gDirectory->Write();
}

void TimeFormatHist(TH2D* h){
  h->Draw("colz");
  h->GetXaxis()->SetTimeDisplay(1);
  h->GetXaxis()->SetNdivisions(508);
  h->GetXaxis()->SetTimeFormat("%Y-%m-%d %H:%M");
  h->GetXaxis()->SetTimeOffset(0, "local");
  //  h;
}
