void icarus_alp_analysis_draw()
{
  const int nfiles = 8;
  const char* input_filename_char[nfiles] = 
  {"result_icarus_FHC_1M_nue_analysis.root",
   "result_icarus_FHC_1M_nuebar_analysis.root",
   "result_icarus_FHC_1M_numu_analysis.root",
   "result_icarus_FHC_1M_numubar_analysis.root",
   "result_icarus_RHC_1M_nue_analysis.root",
   "result_icarus_RHC_1M_nuebar_analysis.root",
   "result_icarus_RHC_1M_numu_analysis.root",
   "result_icarus_RHC_1M_numubar_analysis.root"};
  TString input_filename_tstring[nfiles];
  TFile* input_file[nfiles];
  for(int i = 0; i < nfiles; i++)
  {
    input_filename_tstring[i].Append(input_filename_char[i]);
    input_file[i] = new TFile(input_filename_tstring[i]);
    if( input_file[i]->IsOpen() )
    {
      std::cout << input_filename_tstring[i] << " is opened." << std::endl;
    }
    else
    {
      std::cerr << input_filename_tstring[i] << " can not be opened!" << std::endl;
      return 1;
    }
  }

  TH1D* h_pi0[nfiles];
  TH1D* h_elec[nfiles];
  TH1D* h_digamma[nfiles];

  const char* hist_name_pi0[nfiles] =
  {
    "icarus_nue_pi0",
    "icarus_nuebar_pi0",
    "icarus_numu_pi0",
    "icarus_numubar_pi0",
    "icarus_nue_pi0",
    "icarus_nuebar_pi0",
    "icarus_numu_pi0",
    "icarus_numubar_pi0"
  };
  const char* hist_title_pi0[nfiles] =
  {
    "#pi^{0} / Beam: #nu_{e}, FHC",
    "#pi^{0} / Beam: #bar{#nu}_{e}, FHC",
    "#pi^{0} / Beam: #nu_{#mu}, FHC",
    "#pi^{0} / Beam: #bar{#nu}_{#mu}, FHC",
    "#pi^{0} / Beam: #nu_{e}, RHC",
    "#pi^{0} / Beam: #bar{#nu}_{e}, RHC",
    "#pi^{0} / Beam: #nu_{#mu}, RHC",
    "#pi^{0} / Beam: #bar{#nu}_{#mu}, RHC"
  };
  const char* hist_name_elec[nfiles] =
  {
    "icarus_nue_single_elec_E",
    "icarus_nuebar_single_elec_E",
    "icarus_numu_single_elec_E",
    "icarus_numubar_single_elec_E",
    "icarus_nue_single_elec_E",
    "icarus_nuebar_single_elec_E",
    "icarus_numu_single_elec_E",
    "icarus_numubar_single_elec_E"
  };
  const char* hist_title_elec[nfiles] =
  {
    "e^{-} / Beam: #nu_{e}, FHC",
    "e^{-} / Beam: #bar{#nu}_{e}, FHC",
    "e^{-} / Beam: #nu_{#mu}, FHC",
    "e^{-} / Beam: #bar{#nu}_{#mu}, FHC",
    "e^{-} / Beam: #nu_{e}, RHC",
    "e^{-} / Beam: #bar{#nu}_{e}, RHC",
    "e^{-} / Beam: #nu_{#mu}, RHC",
    "e^{-} / Beam: #bar{#nu}_{#mu}, RHC"
  };
  const char* hist_name_digamma[nfiles] =
  {
    "icarus_nue_digamma",
    "icarus_nuebar_digamma",
    "icarus_numu_digamma",
    "icarus_numubar_digamma",
    "icarus_nue_digamma",
    "icarus_nuebar_digamma",
    "icarus_numu_digamma",
    "icarus_numubar_digamma"
  };
  const char* hist_title_digamma[nfiles] =
  {
    "#gamma#gamma / Beam: #nu_{e}, FHC",
    "#gamma#gamma / Beam: #bar{#nu}_{e}, FHC",
    "#gamma#gamma / Beam: #nu_{#mu}, FHC",
    "#gamma#gamma / Beam: #bar{#nu}_{#mu}, FHC",
    "#gamma#gamma / Beam: #nu_{e}, RHC",
    "#gamma#gamma / Beam: #bar{#nu}_{e}, RHC",
    "#gamma#gamma / Beam: #nu_{#mu}, RHC",
    "#gamma#gamma / Beam: #bar{#nu}_{#mu}, RHC"
  };

  // Retrieve histograms
  for(int i = 0; i < nfiles; i++)
  {
    h_pi0[i]     = (TH1D*)input_file[i]->Get(hist_name_pi0[i]);
    h_elec[i]    = (TH1D*)input_file[i]->Get(hist_name_elec[i]);
    h_digamma[i] = (TH1D*)input_file[i]->Get(hist_name_digamma[i]);

    // histogram decoration
    // nue,    FHC - red filled circle
    // nuebar, FHC - red opened circle
    // numu,   FHC - violet filled circle
    // numubar,FHC - violet opened circle
    // nue,    RHC - blue filled circle
    // nuebar, RHC - blue opened circle
    // numu,   RHC - cyan filled circle
    // numubar,RHC - cyan opened circle
    if( i % 2 == 1 )
    {
      h_pi0[i]->SetMarkerStyle(4);
      h_elec[i]->SetMarkerStyle(4);
      h_digamma[i]->SetMarkerStyle(4);
    }
    else
    {
      h_pi0[i]->SetMarkerStyle(20);
      h_elec[i]->SetMarkerStyle(20);
      h_digamma[i]->SetMarkerStyle(20);
    }
    if( i == 0 || i == 1 )
    {
      h_pi0[i]->SetMarkerColor(kRed);
      h_elec[i]->SetMarkerColor(kRed);
      h_digamma[i]->SetMarkerColor(kRed);
      h_pi0[i]->SetLineColor(kRed);
      h_elec[i]->SetLineColor(kRed);
      h_digamma[i]->SetLineColor(kRed);
    }
    else if( i == 2 || i == 3 )
    {
      h_pi0[i]->SetMarkerColor(kViolet);
      h_elec[i]->SetMarkerColor(kViolet);
      h_digamma[i]->SetMarkerColor(kViolet);
      h_pi0[i]->SetLineColor(kViolet);
      h_elec[i]->SetLineColor(kViolet);
      h_digamma[i]->SetLineColor(kViolet);
    }
    else if( i == 4 || i == 5 )
    {
      h_pi0[i]->SetMarkerColor(kBlue);
      h_elec[i]->SetMarkerColor(kBlue);
      h_digamma[i]->SetMarkerColor(kBlue);
      h_pi0[i]->SetLineColor(kBlue);
      h_elec[i]->SetLineColor(kBlue);
      h_digamma[i]->SetLineColor(kBlue);
    }
    else if( i == 6 || i == 7 )
    {
      h_pi0[i]->SetMarkerColor(kCyan);
      h_elec[i]->SetMarkerColor(kCyan);
      h_digamma[i]->SetMarkerColor(kCyan);
      h_pi0[i]->SetLineColor(kCyan);
      h_elec[i]->SetLineColor(kCyan);
      h_digamma[i]->SetLineColor(kCyan);
    }
    h_pi0[i]->GetXaxis()->SetTitle("#pi^{0} Energy (GeV)");
    h_elec[i]->GetXaxis()->SetTitle("e^{-} Energy (GeV)");
    h_digamma[i]->GetXaxis()->SetTitle("#gamma Energy (GeV)");
  }

  // Construct TCanvas'es
  // 6 canvases:
  // c1 : pi0 from nue and nuebar beams (FHC & RHC side-by-side)
  // c2 : e- from nue and nuebar beams
  // c3 : gamma from nue and nuebar beams
  // same three canvases for numu beams
  TCanvas* c1 = new TCanvas("c1");
  c1->Divide(2, 1);
  c1->cd(1);
  h_pi0[0]->Draw("e1p");
  h_pi0[1]->Draw("e1psame");
  c1->cd(2);
  h_pi0[4]->Draw("e1p");
  h_pi0[5]->Draw("e1psame");

  TCanvas* c2 = new TCanvas("c2");
  c2->Divide(2, 1);
  c2->cd(1);
  h_elec[0]->Draw("e1p");
  h_elec[1]->Draw("e1psame");
  c2->cd(2);
  h_elec[4]->Draw("e1p");
  h_elec[5]->Draw("e1psame");

  TCanvas* c3 = new TCanvas("c3");
  c3->Divide(2, 1);
  c3->cd(1);
  h_digamma[0]->Draw("e1p");
  h_digamma[1]->Draw("e1psame");
  c3->cd(2);
  h_digamma[4]->Draw("e1p");
  h_digamma[5]->Draw("e1psame");


  TCanvas* c4 = new TCanvas("c4");
  c4->Divide(2, 1);
  c4->cd(1);
  h_pi0[2]->Draw("e1p");
  h_pi0[3]->Draw("e1psame");
  c4->cd(2);
  h_pi0[6]->Draw("e1p");
  h_pi0[7]->Draw("e1psame");

  TCanvas* c5 = new TCanvas("c5");
  c5->Divide(2, 1);
  c5->cd(1);
  h_elec[2]->Draw("e1p");
  h_elec[3]->Draw("e1psame");
  c5->cd(2);
  h_elec[6]->Draw("e1p");
  h_elec[7]->Draw("e1psame");

  TCanvas* c6 = new TCanvas("c6");
  c6->Divide(2, 1);
  c6->cd(1);
  h_digamma[2]->Draw("e1p");
  h_digamma[3]->Draw("e1psame");
  c6->cd(2);
  h_digamma[6]->Draw("e1p");
  h_digamma[7]->Draw("e1psame");

  TFile* fOutput = new TFile("analysis_draw_output.root", "recreate");
  c1->Write();
  c2->Write();
  c3->Write();
  c4->Write();
  c5->Write();
  c6->Write();
  fOutput->Close();
}
