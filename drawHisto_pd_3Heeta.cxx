/***********************************************
* Software developement for WASA-at-COSY
* (c) 2005-2021 The WASA-at-COSY Collaboration
* Aleksander K.                 2021-02
* This software is distributed under the terms
  of the GNU General Public Licence v3.0
***********************************************/

//Comparison of the differential cross sections for the pd->3He eta reaction

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

void drawHisto_pd_3Heeta() {

  TH1F *hist = new TH1F("hCrossSection","",1000000,-1.,12.);

  FILE *file_ANKE;
  FILE *file_COSY11;

  file_ANKE = fopen("input/pd_3Heeta_ANKE.dat","r");
  file_COSY11 = fopen("input/pd_3Heeta_COSY11.dat","r");

  TGraphErrors* gXS[2];
  gXS[0] = new TGraphErrors(198);
  gXS[1] = new TGraphErrors(19);

  Float_t Q[2];
  Float_t XS[2];
  Float_t XSerr[2];

  //ANKE
  Q[0] = 0.;
  XS[0] = 0.;
  XSerr[0] = 0.;

  Int_t i = -1;
  while (!feof(file_ANKE)) {
    i++;
    fscanf(file_ANKE, "%f %f %f\n", &Q[0], &XS[0], &XSerr[0]);
    gXS[0]->SetPoint(i,Q[0],XS[0]);
    gXS[0]->SetPointError(i,0.,XSerr[0]);
  }

  //COSY-11
  Q[1] = 0.;
  XS[1] = 0.;
  XSerr[1] = 0.;

  Int_t j = -1;
  while (!feof(file_COSY11)) {
    j++;
    fscanf(file_COSY11,"%f %f %f\n",&Q[1],&XS[1],&XSerr[1]);
    gXS[1]->SetPoint(j,Q[1],XS[1]);
    gXS[1]->SetPointError(j,0.,XSerr[1]);
  }

//////////////////////////////////////////////////////

  TGraphErrors* XS_graph[2];

  //COSY-11 (Adam et al.)
  Double_t x_0[] = {5,10.8};
  Double_t y_0[] = {574,462};
  //total error (stat+syst)
  Double_t y_err_0[] = {62,47};

  XS_graph[0] = new TGraphErrors(2,x_0,y_0,0,y_err_0);

  //SPES-2 (Mayer et al.)
  Double_t x_1[] = {0.22,0.93,1.99,3.32,4.90,6.90,8.80,11.02};
  Double_t y_1[] = {225,351,409,424,429,431,404,404};
  //total error (stat+syst)
  Double_t y_err_1[] = {40,12,11,12,15,15,18,18};

  XS_graph[1] = new TGraphErrors(8,x_1,y_1,0,y_err_1);

//////////////////////////////////////////////////////

  //set no statistics on gXSograms and pallette
  gStyle->SetOptStat(kFALSE);
  gStyle->SetPalette(1,0);
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadRightMargin(0.1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.15);

  TCanvas* MyCanvas01 = new TCanvas;

  hist->GetXaxis()->SetTitle("\\hbox{energia dostępna [GeV/c]}");
  hist->GetYaxis()->SetTitle("#sigma [nb]");
  hist->GetXaxis()->SetTitleSize(0.06);
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->SetLabelSize(0.05);
  hist->GetYaxis()->SetTitleSize(0.06);
  hist->GetYaxis()->SetTitleOffset(1.);
  hist->GetYaxis()->SetLabelSize(0.05);
  hist->GetXaxis()->SetRangeUser(-1.0,12.0);
  hist->GetYaxis()->SetRangeUser(-50.,700.0);

  hist->SetLineColor(0);
  hist->Draw();

  gXS[0]->SetMarkerStyle(24);
  gXS[0]->SetMarkerSize(0.8);
  gXS[0]->SetMarkerColor(2);
  gXS[0]->SetLineColor(2);

  gXS[1]->SetMarkerStyle(21);
  gXS[1]->SetMarkerSize(0.8);
  gXS[1]->SetMarkerColor(1);
  gXS[1]->SetLineColor(1);

  XS_graph[0]->SetMarkerStyle(22);
  XS_graph[0]->SetMarkerSize(1.0);
  XS_graph[0]->SetMarkerColor(kMagenta+2);
  XS_graph[0]->SetLineColor(kMagenta+2);

  XS_graph[1]->SetMarkerStyle(33);
  XS_graph[1]->SetMarkerSize(1.4);
  XS_graph[1]->SetMarkerColor(kAzure);
  XS_graph[1]->SetLineColor(kAzure);

  gXS[0]->Draw("same p");
  gXS[1]->Draw("same p");
  XS_graph[0]->Draw("same p");
  XS_graph[1]->Draw("same p");

  TLegend *MyLegend01 = new TLegend(0.590, 0.220, 0.890, 0.465);
  MyLegend01->SetFillStyle(1001); MyLegend01->SetFillColor(19); MyLegend01->SetLineColor(1); MyLegend01->SetBorderSize(5);
  MyLegend01->SetTextSize(0.04);
  MyLegend01->AddEntry(XS_graph[1], "SPES-2 [33]", "pE");
  MyLegend01->AddEntry(gXS[0], "COSY-ANKE [34]", "pE");
  MyLegend01->AddEntry(gXS[1], "COSY-11 [35]", "pE");
  MyLegend01->AddEntry(XS_graph[0], "COSY-11 [127]", "pE");
  MyLegend01->Draw();

  MyCanvas01->Print("plots/hCrossSections_pd.png","png");
  MyCanvas01->Print("plots/hCrossSections_pd.eps","eps");

}
