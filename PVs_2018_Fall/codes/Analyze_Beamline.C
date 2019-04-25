#define Analyze_Beamline_cxx
#include "Analyze_Beamline.h"
#include <TH2.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>

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

   double IPM2c21_minus1 = 0;
   double IPM2c21_minus2 = 0;

   double IPM2c24_minus1 = 0;
   double IPM2c24_minus2 = 0;

   TFile *file_out = new TFile("Analyze_Beamline.root", "Recreate");
   TH2D *h_2C21_FCup_Ratio_time1 = new TH2D("h_2C21_FCup_Ratio_time1", "", 1000, 0., 85., 600, 0.85, 1.15);
   TH2D *h_2C21_2C24_Ratio_time1 = new TH2D("h_2C21_2C24_Ratio_time1", "", 1000, 0., 85., 600, 0.85, 1.15);
   TH2D *h_2C21_2H01_Ratio_time1 = new TH2D("h_2C21_2H01_Ratio_time1", "", 1000, 0., 85., 600, 0.85, 1.15);
   TH2D *h_2C24_2H01_Ratio_time1 = new TH2D("h_2C24_2H01_Ratio_time1", "", 1000, 0., 85., 600, 0.85, 1.15);

   TH2D *h_fCup_Offset_time1 = new TH2D("h_fCup_Offset_time1", "", 1000, 0., 85., 600., 0., 800.);
   
   TH2D *h_2C21_FCup_Ratio_time_Zoom1 = new TH2D("h_2C21_FCup_Ratio_time_Zoom1", "", 1000, 28.6, 29.2, 600, 0.85, 1.15);
   TH2D *h_2C21_2C24_Ratio_time2 = new TH2D("h_2C21_2C24_Ratio_time2", "", 1000, 0., 85., 600, 0.85, 1.15);
   TH2D *h_2C21_2C24_Ratio_time3 = new TH2D("h_2C21_2C24_Ratio_time3", "", 1000, 0., 85., 600, 0.85, 1.15);
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      double time = double(Date - date_begin)/day_in_sec;

      bool prod_beam = IPM2C21A > 35 && IPM2C24A > 35 && IPM2H01 > 35 && scaler_calc1b > 35;

      bool No_beam = IPM2C21A < 0.1 && IPM2C24A < 0.1 && IPM2H01 < 0.1;

      if( prod_beam ){

	h_2C21_FCup_Ratio_time_Zoom1->Fill(time, IPM2C21A/scaler_calc1b);
	
	h_2C21_FCup_Ratio_time1->Fill(time, IPM2C21A/scaler_calc1b);
	h_2C21_2C24_Ratio_time1->Fill(time, IPM2C21A/IPM2C24A);
	h_2C21_2H01_Ratio_time1->Fill(time, IPM2C21A/IPM2H01);
	h_2C24_2H01_Ratio_time1->Fill(time, IPM2C24A/IPM2H01);

	if(jentry > 2){
	  h_2C21_2C24_Ratio_time2->Fill(time, IPM2C21A/IPM2c24_minus1);
	  h_2C21_2C24_Ratio_time3->Fill(time, IPM2c21_minus2/IPM2c24_minus1);
	}

	IPM2c21_minus2 = IPM2c21_minus1;
	IPM2c21_minus1 = IPM2C21A;

	IPM2c24_minus2 = IPM2c24_minus1;
	IPM2c24_minus1 = IPM2C24A;
	
      } else if( No_beam ){
	h_fCup_Offset_time1->Fill(time, scalerS2b);
      }
   }

   gDirectory->Write();
}
