

void Draw_Atten(){

  TCanvas *c1 = new TCanvas("c1", "",  1800, 900);
  
  const int n_CLAS12_points = 7;
  const int n_old_points = 2;
  const int n_GEANT_points = 3;

  double Eb_CLAS12[n_CLAS12_points] = {6.4, 6.6, 10.7, 7.54, 10.2, 10.19, 10.21};
  double atten_CLAS12[n_CLAS12_points] = {16.9726, 16.23795, 9.80875, 14.895650, 9.96025, 9.9193, 9.99085 };
  double E_Beam_Err[n_CLAS12_points] = {0., 0., 0., 0., 0., 0., 0.};
  double atten_Err_CLAS12[n_CLAS12_points] = {0.0095, 0.00675, 0.00055, 0.02115, 0.00795, 0.0135, 0.00635};

  double Eb_old[n_old_points] = {2.3, 6.};
  double atten_old[n_old_points] = {1./0.015, 1./0.049};

  double Eb_G3[n_GEANT_points] = {2.3, 6., 11.};
  double atten_G3[n_GEANT_points] = {1./0.009, 1./0.042, 1./0.09};

  TLatex *lat1 = new TLatex();
  lat1->SetNDC();

  TGraphErrors *gr_CL12 = new TGraphErrors(n_CLAS12_points, Eb_CLAS12, atten_CLAS12, E_Beam_Err, atten_Err_CLAS12);
  gr_CL12->SetMarkerColor(4);
  gr_CL12->SetMarkerStyle(22);
  gr_CL12->SetMarkerSize(1.2);

  TGraph *gr_old = new TGraph(n_old_points, Eb_old, atten_old);
  gr_old->SetMarkerColor(2);
  gr_old->SetMarkerStyle(23);
  gr_old->SetMarkerSize(2);

  TGraph *gr_G3 = new TGraph(n_GEANT_points, Eb_G3, atten_G3);
  gr_G3->SetMarkerColor(95);
  gr_G3->SetMarkerStyle(21);
  gr_G3->SetMarkerSize(2);

  // Extrapolated value
  TGraph *gr_7p5 = new TGraph();
  gr_7p5->SetPoint(0, 7.5, 14.626775);
  gr_7p5->SetMarkerColor(1);
  gr_7p5->SetMarkerStyle(29);
  gr_7p5->SetMarkerSize(2);

  TMultiGraph *mtgr1 = new TMultiGraph();
  mtgr1->Add(gr_CL12);
  mtgr1->Add(gr_old);
  mtgr1->Add(gr_G3);
  mtgr1->Add(gr_7p5);

  mtgr1->Draw("AP");
  mtgr1->SetTitle("; Beam energy [GeV]; attenuation");


  c1->Clear();
  c1->SetTopMargin(0.02);
  c1->SetRightMargin(0.02);
  c1->SetLeftMargin(0.05);
  TMultiGraph *mtgr_Data = new TMultiGraph();
  mtgr_Data->Add(gr_CL12);
  mtgr_Data->Add(gr_old);
  mtgr_Data->Draw("AP");
  mtgr_Data->SetTitle("; E_{b} [GeV]; Attenuation");
  mtgr_Data->GetYaxis()->SetTitleOffset(0.6);
  c1->Print("Atten_Measurements.eps");
  c1->Print("Atten_Measurements.pdf");
  c1->Print("Atten_Measurements.png");

  mtgr_Data->GetXaxis()->SetLimits(6.2, 11);
  mtgr_Data->SetMaximum(17.2);
  mtgr_Data->SetMinimum(9.6);
  lat1->SetTextColor(4);
  lat1->SetTextSize(0.03);
  lat1->DrawLatex(0.105, 0.94, "Dec 13 2018");
  lat1->DrawLatex(0.145, 0.86, "Feb 7 2018");
  lat1->DrawLatex(0.33, 0.704, "Dec 3 2018");
  lat1->DrawLatex(0.76, 0.26, "Mar 19 2019");
  lat1->DrawLatex(0.76, 0.22, "Apr 7 2019");
  lat1->DrawLatex(0.76, 0.18, "Apr 12 2019");

  lat1->DrawLatex(0.88, 0.14, "Jan 30 2018");
  c1->Print("CLAS12_Atten_Measurements.eps");
  c1->Print("CLAS12_Atten_Measurements.pdf");
  c1->Print("CLAS12_Atten_Measurements.png");

  


}
