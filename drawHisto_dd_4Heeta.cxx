/***********************************************
* Software developement for WASA-at-COSY
* (c) 2005-2021 The WASA-at-COSY Collaboration
* Aleksander K.                 2021-02
* This software is distributed under the terms
  of the GNU General Public Licence v3.0
***********************************************/

//Comparison of the differential cross sections for the dd->4He eta reaction

#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TPaveLabel.h>
#include <TFrame.h>
#include <TSystem.h>
#include <TNtuple.h>
#include <TPaveText.h>
#include <TInterpreter.h>
#include <TStyle.h>
#include <TROOT.h>
#include <Riostream.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFitResultPtr.h>
#include <TFitResult.h>
#include <TLegend.h>
#include "TString.h"
#include <iostream>
#include <fstream>

void drawHisto_dd_4Heeta() {

  TH1F *hist = new TH1F("hCrossSection","",100,0.,130.);

  TGraphErrors* XS_graph[5];

  //SPES-4 (Frascaria et al.)
  Double_t x_0[] = {14.4,24.7,32.0,38.0};
  Double_t y_0[] = {4.42,8.25,9.85,11.0};
  //total error (stat+syst)
  Double_t y_err_0[] = {1.41,0.41,0.97,0.57};

  XS_graph[0] = new TGraphErrors(4,x_0,y_0,0,y_err_0);

  XS_graph[0]->SetMarkerStyle(33);
  XS_graph[0]->SetMarkerSize(1.4);
  XS_graph[0]->SetMarkerColor(kAzure);
  XS_graph[0]->SetLineColor(kAzure);

  //SPES-3 (Willis et al.)
  Double_t x_1[] = {9.87,23.68,25.60,47.35,73.00,90.76};
  Double_t y_1[] = {4.73,8.8,9.73,12.8,13.73,14.93};
  //total error (stat+syst)
  Double_t y_err_1[] = {1.,0.6,0.4,1.06,1.,1.06};

  XS_graph[1] = new TGraphErrors(6,x_1,y_1,0,y_err_1);

  XS_graph[1]->SetMarkerStyle(20);
  XS_graph[1]->SetMarkerSize(1.0);
  XS_graph[1]->SetMarkerColor(2);
  XS_graph[1]->SetLineColor(2);

  //ANKE (Wronska et al.)
  Double_t x_2[] = {48.0,86.0};
  Double_t y_2[] = {13.1,16.4};
  //total error (stat+syst)
  Double_t y_err_2[] = {1.93,2.32};

  XS_graph[2] = new TGraphErrors(2,x_2,y_2,0,y_err_2);

  XS_graph[2]->SetMarkerStyle(21);
  XS_graph[2]->SetMarkerSize(0.8);
  XS_graph[2]->SetMarkerColor(1);
  XS_graph[2]->SetLineColor(1);

  //GEM
  Double_t x_3[] = {125.};
  Double_t y_3[] = {16.0};
  //total error (stat+syst)
  Double_t y_err_3[] = {1.6};

  XS_graph[3] = new TGraphErrors(1,x_3,y_3,0,y_err_3);

  XS_graph[3]->SetMarkerStyle(22);
  XS_graph[3]->SetMarkerSize(1.0);
  XS_graph[3]->SetMarkerColor(kMagenta+2);
  XS_graph[3]->SetLineColor(kMagenta+2);

//////////////////////////////////////////////////////

  //set no statistics on histograms and pallette
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPalette(1,0);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);

  TCanvas* MyCanvas01 = new TCanvas;

  hist->GetXaxis()->SetTitle("p_{#eta}, GeV/c");
  hist->GetYaxis()->SetTitle("#sigma, nb");
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetTitleOffset(0.7);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetXaxis()->SetRangeUser(0.,130.);
  hist->GetYaxis()->SetRangeUser(0.,20.0);

  hist->Draw();

  XS_graph[0]->Draw("same p");
  XS_graph[1]->Draw("same p");
  XS_graph[2]->Draw("same p");
  XS_graph[3]->Draw("same p");

  TLegend *MyLegend01 = new TLegend(0.590, 0.220, 0.890, 0.465);
  MyLegend01->SetFillStyle(1001); MyLegend01->SetFillColor(19); MyLegend01->SetLineColor(1); MyLegend01->SetBorderSize(5);
  MyLegend01->SetTextSize(0.04);
  MyLegend01->AddEntry(XS_graph[0], "SPES-4 [123]", "pE");
  MyLegend01->AddEntry(XS_graph[1], "SPES-3 [124]", "pE");
  MyLegend01->AddEntry(XS_graph[2], "COSY-ANKE [125]", "pE");
  MyLegend01->AddEntry(XS_graph[3], "GEM [126]", "pE");
  MyLegend01->Draw();

  MyCanvas01->Print("plots/hCrossSections_dd.png","png");
  MyCanvas01->Print("plots/hCrossSections_dd.eps","eps");

}
