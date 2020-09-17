#include <iostream>
#include <TLegend.h>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "TH1D.h"
#include "TH2D.h"
#include <THStack.h>
#include "TProfile.h"
#include "TGraph.h"
#include "TFile.h"
#include "TTree.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TFractionFitter.h"
#include <string>
#include <vector>
#include <math.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMarker.h>
#include <TPave.h>
#include <TPaveStats.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <TString.h>
#include "TGraphErrors.h"
#include "TF1.h"
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <RooPlot.h>
#include <RooArgSet.h>
#include <RooArgList.h>
#include <RooDataSet.h>
#include <RooDataHist.h>
#include <RooGaussian.h>
#include <RooPolynomial.h>
#include <RooRealVar.h> 
#include <RooFormulaVar.h> 
#include <RooWorkspace.h> 
#include <RooMsgService.h> 


using namespace std;

void makeCardsAndWS(){
  

  TH1F* histChi2_A=new TH1F("histChi2_A","histChi2_A",50,0.5,1.5);

  //WHICH YEAR
  	TString year="2018C";
	TString suff="IterV0";
  //INPUT FILE WITH HISTOGRAMS TO FIT BACKGROUND
  	  TFile* file=TFile::Open("/eos/cms/store/group/phys_exotica/darkPhoton/jakob/newProd/2018/ScoutingRunC/mergedHistos_v1.root");
	  //TFile* file=TFile::Open("./hists18Ccmsdas.root.root");
	
  //PREPARE EXPECTED NUMBER OF SIGNAL EVENTS PER CATEGORY

	
	//LUMINOSITY
	double luminosity = 6700;//pb-1
	//EFFICIENCY
	
	
	//scale
	double xSec = 1.;

   //LOOP OVER MASS INDICES AND MAKE THE CARDS/WORKSPACES
	double mass = 0.2;
	for(int i=0; i<400; i++){

	  
	  
	  	//get the histograms
	  	TH1D* catA=(TH1D*)file->Get(Form("massforLimit_CatA%d",i));
	  	double massLow  =  catA->GetXaxis()->GetXmin();
      		double massHigh =  catA->GetXaxis()->GetXmax();
	  

		//compute mass point and define ROOFit variables
	  	mass = mass+(mass*0.01);
		//cout<<"Spline: "<<effAgraph->Eval(mass,0,"S")<<endl;
		//cout<<"Graph : "<<effAgraph->Eval(mass)<<endl;
		RooRealVar MH    ("MH"       	, "MH"          , mass);	
		RooRealVar resA  ("resA"  	, "RFes. unc. " , mass*0.02);//to be checked
		RooRealVar m2mu  ("m2mu"  	, "m2mu " 	, massLow		, massHigh);

		//define the signal model
		RooGaussian signalModel_CatA("signalModel_CatA"	, "signalModel_CatA"		, m2mu		      ,MH	,resA);
      		RooDataHist data_obs_CatA("data_obs_CatA", "", RooArgList(m2mu), catA);
	
		RooRealVar bkg_norm("bkg_norm", "",catA->Integral());
	

		//fit and get the background PDF
		TF1 *bkfit = new TF1("bkfit","pol3",massLow,massHigh);
		catA->Fit(bkfit);
		/*TCanvas * catAc = new TCanvas("catAc", "catAc", 500, 500);
		catA->Draw();
		catAc->SaveAs(Form("catA%d"+year+".png",i));*/
		if(i>24. && (i<200. || i>240.)) {histChi2_A->Fill(bkfit->GetChisquare()/bkfit->GetNDF());}
		RooRealVar a0a("a0a","a0a",bkfit->GetParameter(0),(bkfit->GetParameter(0)-bkfit->GetParError(0)*5.),(bkfit->GetParameter(0)+bkfit->GetParError(0)*5.));
		RooRealVar a1a("a1a","a1a",bkfit->GetParameter(1),(bkfit->GetParameter(1)-bkfit->GetParError(1)*5.),(bkfit->GetParameter(1)+bkfit->GetParError(1)*5.));
      		RooRealVar a2a("a2a","a2a",bkfit->GetParameter(2),(bkfit->GetParameter(2)-bkfit->GetParError(2)*5.),(bkfit->GetParameter(2)+bkfit->GetParError(2)*5.));
		RooRealVar a3a("a3a","a3a",bkfit->GetParameter(3),(bkfit->GetParameter(3)-bkfit->GetParError(3)*5.),(bkfit->GetParameter(3)+bkfit->GetParError(3)*5.));
		RooPolynomial bkg_mass_CatA("bkg_mass_CatA","bkg_mass_CatA",m2mu,RooArgList(a0a,a1a,a2a,a3a),0);
		
		//save into ROO workspace
		RooWorkspace dpworkspace("dpworkspace", "");
      		dpworkspace.import(data_obs_CatA);
	
      		dpworkspace.import(signalModel_CatA);
	
      		dpworkspace.import(bkg_mass_CatA);
	
      		dpworkspace.writeToFile(Form("dpWorkspace"+year+suff+"_%d.root",i));

		//write the datacard
		char inputShape[200];
      		sprintf(inputShape,"dpCard_"+year+suff+"_%d.txt",i);
      		ofstream newcardShape;
      		newcardShape.open(inputShape);
      		newcardShape << Form("imax 1 number of channels\n");
      		newcardShape << Form("jmax * number of background\n");
      		newcardShape << Form("kmax * number of nuisance parameters\n");
		newcardShape << Form("shapes data_obs	CatA dpWorkspace"+year+suff+"_%d.root dpworkspace:data_obs_CatA\n",i);
		newcardShape << Form("shapes bkg_mass	CatA dpWorkspace"+year+suff+"_%d.root dpworkspace:bkg_mass_CatA\n",i);
		newcardShape << Form("shapes signalModel	CatA dpWorkspace"+year+suff+"_%d.root dpworkspace:signalModel_CatA\n",i);
      		newcardShape << Form("bin		CatA \n");
      		newcardShape << Form("observation 	-1.0\n");
      		newcardShape << Form("bin     		CatA		CatA \n");
      		newcardShape << Form("process 		signalModel  	bkg_mass\n");
      		newcardShape << Form("process 		0    		1 \n");
      		newcardShape << Form("rate    		%f  		%f	\n",
				     0.64*luminosity*xSec, catA->Integral());
		newcardShape << Form("lumi13TeV_2018 lnN 	1.023 	-\n");
		newcardShape << Form("eff_mu_13TeV_2018 lnN	1.015 	-\n");
		//newcardShape << Form("bkg_norm_cata rateParam CatA bkg_mass %f\n",catA->Integral());
		//newcardShape << Form("resA param %f %f\n",resA.getValV(),resA.getValV()*0.1);
		newcardShape.close();
		
	}
	histChi2_A->SaveAs("histAchi2_"+year+".root");

}
