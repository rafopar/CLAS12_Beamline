#include <TF1.h>
#include <cmath>
#include <TH1D.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TCanvas.h>

#include <iostream>

using namespace std;

void Fit_and_MakePlots(){

  TCanvas *c1 = new TCanvas("c1", "", 600., 1000.);
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->SetBottomMargin(0.11);
  static const int n_counters = 15;
  TGraph *gr_[n_counters];

  TLatex *lat1 = new TLatex();
  lat1->SetNDC();
  lat1->SetTextSize(0.06);
  lat1->SetTextFont(42);


  //================================================= 2C21 ========================================
  string fname = "harp_2c21_02-18-19_13:11:44.txt";
  
  gr_[0] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %lg");
  gr_[1] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %lg");
  gr_[2] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %lg");
  gr_[3] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %lg");
  gr_[4] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %lg");
  gr_[5] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %lg");
  gr_[6] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[7] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[8] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[9] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[10] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[11] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[12] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[13] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[14] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");


  gr_[4]->SetMarkerColor(4);
  gr_[4]->SetMarkerStyle(20);
  gr_[4]->SetMarkerSize(0.7);
  
  gr_[4]->Draw("AP");
  TF1 *f_1st_peak = new TF1("f_1st_peak", "[0]*TMath::Gaus(x, [1], [2]) + [3]"); f_1st_peak->SetNpx(2500);
  TF1 *f_2nd_peak = new TF1("f_2nd_peak", "[0]*TMath::Gaus(x, [1], [2]) + [3]"); f_2nd_peak->SetNpx(2500);
  double x_1 = 25.;
  double x_2 = 30.;
  gr_[4]->GetXaxis()->SetLimits(x_1, x_2);
  f_1st_peak->SetParLimits(3, 0., 1.);
  f_1st_peak->SetParameters(350., 27.5, 0.2, 0.2);
  gr_[4]->Fit(f_1st_peak, "MeV", "", x_1, x_2);
  double mean_1st_peak = f_1st_peak->GetParameter(1);


  double x_2_1 = 50.;
  double x_2_2 = 54.;
  gr_[4]->GetXaxis()->SetLimits(x_2_1, x_2_2);
  f_2nd_peak->SetParLimits(3, 0., 1.);
  f_2nd_peak->SetParameters(450., 52., 0.1, 0.2);
  gr_[4]->Fit(f_2nd_peak, "MeV", "", x_2_1, x_2_2);
  double mean_2nd_peak = f_2nd_peak->GetParameter(1);

  
  
  TGraphErrors *gr_2c21_1st_Peak = new TGraphErrors();
  TGraphErrors *gr_2c21_2nd_Peak = new TGraphErrors();

  int n_2c21 = gr_[4]->GetN();

  for( int i = 0; i < n_2c21; i++ ){
    double x_orig, y_orig;

    gr_[4]->GetPoint(i, x_orig, y_orig);

    gr_2c21_1st_Peak->SetPoint(i, (x_orig - mean_1st_peak)/sqrt(2.),  y_orig);
    gr_2c21_1st_Peak->SetPointError(i, 0,  sqrt(y_orig));

    gr_2c21_2nd_Peak->SetPoint(i, (x_orig - mean_2nd_peak)/sqrt(2.),  y_orig);
    gr_2c21_2nd_Peak->SetPointError(i, 0,  sqrt(y_orig));
  }
  


  c1->Clear();

  c1->Divide(1, 2, 0., 0.);
  c1->cd(1)->SetLogy();
  
  TF1 *f_final = new TF1("f_final", "[0]*TMath::Gaus(x, [1], [2]) + [3]", -3., 3.); f_1st_peak->SetNpx(2500);
  f_final->SetParLimits(1, -0.2, 0.2);
  f_final->SetParLimits(2, 0., 2.);

  gr_2c21_1st_Peak->SetMarkerStyle(20);
  gr_2c21_1st_Peak->SetMarkerSize(0.9);
  gr_2c21_1st_Peak->GetXaxis()->SetLimits( -1.7, 1.7);
  gr_2c21_1st_Peak->GetYaxis()->SetLabelSize(0.06);
  gr_2c21_1st_Peak->Draw("AP");
  f_final->SetParameters(gr_2c21_1st_Peak->GetMaximum(), 0., 0.1, 0.5);
  gr_2c21_1st_Peak->Fit(f_final, "MeV", "", (x_1 - mean_1st_peak)/sqrt(2), (x_2 - mean_1st_peak)/sqrt(2) );
  double sigma_2c21_1stpeak = f_final->GetParameter(2);
  lat1->DrawLatex(0.14, 0.93, "X Profile");
  lat1->DrawLatex(0.64, 0.93, Form("#sigma = %1.3f mm", sigma_2c21_1stpeak));

  c1->cd(2)->SetLogy();
  gr_2c21_2nd_Peak->SetTitle("; Beam Profile [mm]");
  gr_2c21_2nd_Peak->SetMarkerStyle(20);
  gr_2c21_2nd_Peak->SetMarkerSize(0.9);
  gr_2c21_2nd_Peak->GetXaxis()->SetLimits( -1.7, 1.7 );
  gr_2c21_2nd_Peak->GetYaxis()->SetLabelSize(0.06);
  gr_2c21_2nd_Peak->GetXaxis()->SetLabelSize(0.06);
  gr_2c21_2nd_Peak->GetXaxis()->SetTitleSize(0.06);
  gr_2c21_2nd_Peak->GetXaxis()->CenterTitle();
  gr_2c21_2nd_Peak->Draw("AP");
  gr_2c21_2nd_Peak->Fit(f_final, "MeV", "", (x_2_1 - mean_2nd_peak)/sqrt(2), (x_2_2 - mean_2nd_peak)/sqrt(2) );
  double sigma_2c21_2ndpeak = f_final->GetParameter(2);
  lat1->DrawLatex(0.14, 0.93, "Y Profile");
  lat1->DrawLatex(0.64, 0.93, Form("#sigma = %1.3f mm", sigma_2c21_2ndpeak));

  c1->Modified();
  c1->Update();
  c1->Print("Figs/2C21_Fits.eps");
  c1->Print("Figs/2C21_Fits.pdf");
  c1->Print("Figs/2C21_Fits.png");


  //================================================= Tgr ========================================
  fname = "harp_tagger_02-18-19_13:15:58.txt";
  
  gr_[0] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %lg");
  gr_[1] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %lg");
  gr_[2] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %lg");
  gr_[3] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %lg");
  gr_[4] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %lg");
  gr_[5] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %lg");
  gr_[6] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[7] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[8] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[9] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[10] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[11] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[12] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[13] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[14] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");


  c1->Clear();
  
  gr_[4]->SetMarkerColor(4);
  gr_[4]->SetMarkerStyle(20);
  gr_[4]->SetMarkerSize(0.7);
  gr_[4]->Draw("AP");

  TF1 *f_3rd_peak = new TF1("f_rd_peak", "[0]*TMath::Gaus(x, [1], [2]) + [3]"); f_3rd_peak->SetNpx(2500);
  double x_2_1_tgr = 25.;
  double x_2_2_tgr = 35.;
  gr_[4]->GetXaxis()->SetLimits(x_2_1_tgr, x_2_2_tgr);
  f_2nd_peak->SetParLimits(3, 0., 1.);
  f_2nd_peak->SetParameters(4650., 29.3, 0.2, 0.2);
  gr_[4]->Fit(f_2nd_peak, "MeV", "", x_2_1_tgr, x_2_2_tgr);
  double mean_2nd_peak_tgr = f_2nd_peak->GetParameter(1);


  double x_3_1_tgr = 45.;
  double x_3_2_tgr = 55.;
  gr_[4]->GetXaxis()->SetLimits(x_3_1_tgr, x_3_2_tgr);
  f_3rd_peak->SetParLimits(3, 0., 1.);
  f_3rd_peak->SetParameters(2400., 50.5, 0.4, 0.2);
  gr_[4]->Fit(f_3rd_peak, "MeV", "", x_3_1_tgr, x_3_2_tgr);
  double mean_3rd_peak_tgr = f_3rd_peak->GetParameter(1);


  TGraphErrors *gr_tgr_2nd_Peak = new TGraphErrors();
  TGraphErrors *gr_tgr_3rd_Peak = new TGraphErrors();

  int n_tgr = gr_[4]->GetN();

  for( int i = 0; i < n_tgr; i++ ){
    double x_orig, y_orig;

    gr_[4]->GetPoint(i, x_orig, y_orig);

    gr_tgr_2nd_Peak->SetPoint(i, (x_orig - mean_2nd_peak_tgr)/sqrt(2.),  y_orig);
    gr_tgr_2nd_Peak->SetPointError(i, 0,  sqrt(y_orig));

    gr_tgr_3rd_Peak->SetPoint(i, (x_orig - mean_3rd_peak_tgr)/sqrt(2.),  y_orig);
    gr_tgr_3rd_Peak->SetPointError(i, 0,  sqrt(y_orig));
  }


  c1->Clear();
  c1->SetBottomMargin(0.11);
  c1->Divide(1, 2, 0., 0.);
  c1->cd(2)->SetLogy();
  
  // TF1 *f_final = new TF1("f_final", "[0]*TMath::Gaus(x, [1], [2]) + [3]", -3., 3.); f_1st_peak->SetNpx(2500);
  // f_final->SetParLimits(2, 0., 2.);

  gr_tgr_2nd_Peak->SetTitle("; Beam Profile [mm]");
  gr_tgr_2nd_Peak->SetMarkerStyle(20);
  gr_tgr_2nd_Peak->SetMarkerSize(0.9);
  gr_tgr_2nd_Peak->GetXaxis()->SetLimits( -2.9, 2.9);
  gr_tgr_2nd_Peak->GetYaxis()->SetLabelSize(0.06);
  gr_tgr_2nd_Peak->GetXaxis()->SetLabelSize(0.06);
  gr_tgr_2nd_Peak->GetXaxis()->SetTitleSize(0.06);
  gr_tgr_2nd_Peak->GetXaxis()->CenterTitle();
  gr_tgr_2nd_Peak->SetMinimum(0.4);
  gr_tgr_2nd_Peak->Draw("AP");
  f_final->SetParameters(gr_tgr_2nd_Peak->GetMaximum(), 0., 0.1, 0.5);
  gr_tgr_2nd_Peak->Fit(f_final, "MeV", "", (x_2_1_tgr - mean_2nd_peak_tgr)/sqrt(2), (x_2_2_tgr - mean_2nd_peak_tgr)/sqrt(2) );
  double sigma_tgr_2ndpeak = f_final->GetParameter(2);
  lat1->DrawLatex(0.14, 0.93, "Y Profile");
  lat1->DrawLatex(0.64, 0.93, Form("#sigma = %1.3f mm", sigma_tgr_2ndpeak));

  c1->cd(1)->SetLogy();
  gr_tgr_3rd_Peak->SetMarkerStyle(20);
  gr_tgr_3rd_Peak->SetMarkerSize(0.9);
  gr_tgr_3rd_Peak->GetXaxis()->SetLimits( -2.9, 2.9);
  gr_tgr_3rd_Peak->GetYaxis()->SetLabelSize(0.06);
  gr_tgr_3rd_Peak->GetXaxis()->SetLabelSize(0.06);
  gr_tgr_3rd_Peak->GetXaxis()->SetTitleSize(0.06);

  gr_tgr_3rd_Peak->SetMinimum(0.4);
  gr_tgr_3rd_Peak->Draw("AP");
  gr_tgr_3rd_Peak->Fit(f_final, "MeV", "", (x_3_1_tgr - mean_3rd_peak_tgr)/sqrt(2), (x_3_2_tgr - mean_3rd_peak_tgr)/sqrt(2) );
  double sigma_tgr_3rdpeak = f_final->GetParameter(2);
  lat1->DrawLatex(0.14, 0.93, "X Profile");
  lat1->DrawLatex(0.64, 0.93, Form("#sigma = %1.3f mm", sigma_tgr_3rdpeak));
  c1->Print("Figs/tgr_Fits.eps");
  c1->Print("Figs/tgr_Fits.pdf");
  c1->Print("Figs/tgr_Fits.png");
  

  
  //================================================= 2H01 ========================================
  fname = "harp_2H01_04-08-19_22:11:15.txt";
  
  gr_[0] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %lg");
  gr_[1] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %lg");
  gr_[2] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %lg");
  gr_[3] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %lg");
  gr_[4] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %lg");
  gr_[5] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %lg");
  gr_[6] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[7] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[8] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[9] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[10] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[11] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[12] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[13] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");
  gr_[14] = new TGraph(Form("%s", fname.c_str() ), "%lg %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %lg");


  c1->Clear();
  
  gr_[13]->SetMarkerColor(4);
  gr_[13]->SetMarkerStyle(20);
  gr_[13]->SetMarkerSize(0.7);
  gr_[13]->Draw("AP");

  double x_1_1_2H01 = 6.1;
  double x_1_2_2H01 = 6.95;
  gr_[13]->GetXaxis()->SetLimits(x_1_1_2H01, x_1_2_2H01);
  f_1st_peak->SetParLimits(3, 0., 1.);
  f_1st_peak->SetParameters(235., 6.53, 0.02, 0.2);
  gr_[13]->Fit(f_1st_peak, "MeV", "", x_1_1_2H01, x_1_2_2H01);
  double mean_1st_peak_2H01 = f_1st_peak->GetParameter(1);

  double x_2_1_2H01 = 7.6;
  double x_2_2_2H01 = 8.5;
  gr_[13]->GetXaxis()->SetLimits(x_2_1_2H01, x_2_2_2H01);
  f_2nd_peak->SetParLimits(3, 0., 1.);
  f_2nd_peak->SetParameters(190., 8.05, 0.02, 0.2);
  gr_[13]->Fit(f_2nd_peak, "MeV", "", x_2_1_2H01, x_2_2_2H01);
  double mean_2nd_peak_2H01 = f_2nd_peak->GetParameter(1);


  TGraphErrors *gr_2H01_1st_Peak = new TGraphErrors();
  TGraphErrors *gr_2H01_2nd_Peak = new TGraphErrors();

  int n_2H01 = gr_[13]->GetN();
  const double scale_2H01 = 10.; // 2H01 motor position is in cm, we convert to mm
  
  for( int i = 0; i < n_2H01; i++ ){
    double x_orig, y_orig;

    gr_[13]->GetPoint(i, x_orig, y_orig);

    gr_2H01_1st_Peak->SetPoint(i, scale_2H01*(x_orig - mean_1st_peak_2H01)/sqrt(2.),  y_orig);
    gr_2H01_1st_Peak->SetPointError(i, 0,  sqrt(y_orig));

    gr_2H01_2nd_Peak->SetPoint(i, scale_2H01*(x_orig - mean_2nd_peak_2H01)/sqrt(2.),  y_orig);
    gr_2H01_2nd_Peak->SetPointError(i, 0,  sqrt(y_orig));
  }


  c1->Clear();
  c1->SetBottomMargin(0.11);
  c1->Divide(1, 2, 0., 0.);
  c1->cd(1)->SetLogy();

  gr_2H01_1st_Peak->SetMarkerStyle(20);
  gr_2H01_1st_Peak->SetMarkerSize(0.9);
  gr_2H01_1st_Peak->GetXaxis()->SetLimits( -2.1, 2.1);
  gr_2H01_1st_Peak->GetYaxis()->SetLabelSize(0.06);
  gr_2H01_1st_Peak->Draw("AP");
  f_final->SetParameters(TMath::Abs(gr_2H01_1st_Peak->GetMaximum()), 0., 0.18, 0.5);
  gr_2H01_1st_Peak->Fit(f_final, "MeV", "", scale_2H01*(x_1_1_2H01 - mean_1st_peak_2H01)/sqrt(2.), scale_2H01*(x_1_2_2H01 - mean_1st_peak_2H01)/sqrt(2) );
  double sigma_2H01_1stpeak = f_final->GetParameter(2);
  lat1->DrawLatex(0.14, 0.93, "X Profile");
  lat1->DrawLatex(0.64, 0.93, Form("#sigma = %1.3f mm", sigma_2H01_1stpeak));

  c1->cd(2)->SetLogy();

  gr_2H01_2nd_Peak->SetTitle("; Beam Profile [mm]");
  gr_2H01_2nd_Peak->SetMarkerStyle(20);
  gr_2H01_2nd_Peak->SetMarkerSize(0.9);
  gr_2H01_2nd_Peak->GetXaxis()->SetLimits( -2.1, 2.1);
  gr_2H01_2nd_Peak->GetYaxis()->SetLabelSize(0.06);
  gr_2H01_2nd_Peak->GetXaxis()->SetLabelSize(0.06);
  gr_2H01_2nd_Peak->GetXaxis()->SetTitleSize(0.06);
  gr_2H01_2nd_Peak->GetXaxis()->CenterTitle();
  gr_2H01_2nd_Peak->Draw("AP");
  f_final->SetParameters(TMath::Abs(gr_2H01_2nd_Peak->GetMaximum()), 0., 0.18, 0.5);
  gr_2H01_2nd_Peak->Fit(f_final, "MeV", "", scale_2H01*(x_2_1_2H01 - mean_2nd_peak_2H01)/sqrt(2.), scale_2H01*(x_2_2_2H01 - mean_2nd_peak_2H01)/sqrt(2) );
  double sigma_2H01_2ndpeak = f_final->GetParameter(2);
  lat1->DrawLatex(0.14, 0.93, "Y Profile");
  lat1->DrawLatex(0.64, 0.93, Form("#sigma = %1.3f mm", sigma_2H01_2ndpeak));
  c1->Print("Figs/2H01_Fits.eps");
  c1->Print("Figs/2H01_Fits.pdf");
  c1->Print("Figs/2H01_Fits.png");
  
}
