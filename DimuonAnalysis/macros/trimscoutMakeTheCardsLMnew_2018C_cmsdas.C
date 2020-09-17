//#include "sumwgt.h"
#include "TFileCollection.h"
#include "TChain.h"
#include "TFile.h"
#include <TTreeReader.h>
#include "TH1D.h"
#include "TH2D.h"
#include <TTreeReaderValue.h>
#include "TLorentzVector.h"

void trimscoutMakeTheCardsLMnew_2018C_cmsdas(string treepath = "scout_2.root", const char* outfilename = "./scout_cmsdas.root", bool isMC=false) {
 
   vector<string> filesToRun;
   vector<bool> isData;
   string dirIn="/eos/cms/store/group/phys_exotica/darkPhoton/jakob/newProd/2018/ScoutingRunC/ScoutingCaloMuon/crab_20200617_174734/200617_154740/0000/";
   //string dirIn="";
   filesToRun.push_back(dirIn.append(treepath));isData.push_back(true);
   TFile* outfile = new TFile(outfilename, "RECREATE");
   
     

    TH1F* dimuonMass = new TH1F("dimuonMass","dimuonMass",2400,0.2,120.);
    //TH1F* dimuonMassJPsi = new TH1F("dimuonMassJPsi","dimuonMassJPsi",700,2.7,3.4);

    
    /*float m=0.2;
    TH1F* massforLimit_CatA[400];
    for(int j=0; j<400; j++){
      m = m+(m*0.01); 
      massforLimit_CatA[j] = new TH1F(Form("massforLimit_CatA%d",j),Form("massforLimit_CatA%d",j),100,m-(m*0.01*10.),m+(m*0.01*10.));  massforLimit_CatA[j]->Sumw2();
      }*/
    

   for(unsigned int f=0; f<filesToRun.size(); f++){

    cout<<filesToRun[f]<<endl;
    TChain* chain = new TChain("mmtree/tree");
    chain->Add((TString)filesToRun[f]);
    
    TTreeReader reader(chain);
    
    TTreeReaderValue<std::vector<float> >          mpt      (reader, "muonpt"     );
    TTreeReaderValue<std::vector<float> >          meta     (reader, "muoneta"    );
    TTreeReaderValue<std::vector<float> >          mphi     (reader, "muonphi"    );
    TTreeReaderValue<std::vector<float> >          mcharge  (reader, "muoncharge" );
    TTreeReaderValue<std::vector<char>  >          mid      (reader, "muonid"     );
    TTreeReaderValue<std::vector<float> >          chi2     (reader, "chi2"       );
    TTreeReaderValue<std::vector<float> >          dxy      (reader, "dxy"        );
    TTreeReaderValue<std::vector<float> >          dz       (reader, "dz"         );
    TTreeReaderValue<std::vector<float> >          cpiso    (reader, "cpiso"      );
    TTreeReaderValue<std::vector<float> >          chiso    (reader, "chiso"      );
    TTreeReaderValue<std::vector<float> >          phiso    (reader, "phiso"      );
    TTreeReaderValue<std::vector<float> >          nhiso    (reader, "nhiso"      );
    TTreeReaderValue<std::vector<float> >          puiso    (reader, "puiso"      );
    TTreeReaderValue<std::vector<float> >          tkiso    (reader, "tkiso"      );
    TTreeReaderValue<std::vector<bool> >           l1Result (reader, "l1Result"   );
    TTreeReaderValue<std::vector<unsigned char> >  nmhits   (reader, "nMuonHits"  );
    TTreeReaderValue<std::vector<unsigned char> >  nphits   (reader, "nPixelHits" );
    TTreeReaderValue<std::vector<unsigned char> >  ntklayers(reader, "nTkLayers"  );
    TTreeReaderValue<unsigned char>                hlt      (reader, "trig"       );
    TTreeReaderValue<unsigned>                     nverts   (reader, "nvtx"       );
    TTreeReaderValue<std::vector<float> >          vtxX     (reader, "vtxX"       );
    TTreeReaderValue<std::vector<float> >          vtxY     (reader, "vtxY"       );
    TTreeReaderValue<std::vector<float> >          vtxZ     (reader, "vtxZ"       );
    TTreeReaderValue<std::vector<float> >          vtxXError    (reader, "vtxXError"       );
    TTreeReaderValue<std::vector<float> >          vtxYError    (reader, "vtxYError"       );
    TTreeReaderValue<std::vector<float> >          vtxZError    (reader, "vtxZError"       );
    TTreeReaderValue<std::vector<float> >          vtxChi2  (reader, "vtxChi2"    );

    TTreeReaderValue<double>                       rho      (reader, "rho"        );
    TTreeReaderValue<unsigned int>                 run      (reader, "run"        );
    TTreeReaderValue<unsigned int>                 lumSec   (reader, "lumSec"     );
     	 
 
    float  m1pt    = 0.0;        
    float  m1eta   = 0.0;        
    float  m1phi   = 0.0;        
    float  m1iso   = 0.0;        
    float  m2pt    = 0.0;        
    float  m2eta   = 0.0;        
    float  m2phi   = 0.0;        
    float  m2iso   = 0.0;        
    float  mass    = 0.0;        
    float  mass4   = 0.0;        
    char   m1id    = 0;
    char   m2id    = 0;
    char   m3id    = 0;
    char   m4id    = 0;
    float  m1ch    = 0.; 
    float  m2ch    = 0.;
    float  m3ch    = 0.; 
    float  m4ch    = 0.; 
    vector<bool> l1Bools;
    unsigned nvtx  = 0;
    unsigned Run   = 0;
    unsigned LumSec   = 0;

    int p=0;
    while(reader.Next()) {
      if (((*hlt) & 2) == 0) continue;   
      bool passIso=false;
      bool passIsoLoose=false;
      bool passIsoOpt=false;
        double ea = (isMC ? 0.3 : 0.45);
        std::vector<unsigned> goodmuons;
        for (std::size_t i = 0; i < mpt->size(); i++) {
	  //if ((*nmhits)[i] == 0)     continue;
	  if ((*nphits)[i] == 0)     continue;
          if ((*ntklayers)[i] <= 5)  continue;
          if ((*chi2)[i] > 10.)      continue;
            double iso = (*cpiso)[i] + (*nhiso)[i] + (*phiso)[i] - ea*(*rho);
	   
            goodmuons.push_back(i);
        }

        if (goodmuons.size() < 2) continue;

        unsigned idx1 = goodmuons[0];
        unsigned idx2 = goodmuons[1];
    
	float isoMu1 = (*tkiso)[goodmuons[0]];
	float isoMu2 = (*tkiso)[goodmuons[1]];

	if((*tkiso)[goodmuons[0]]<0.02 && (*tkiso)[goodmuons[1]]<0.02 ) passIso=true;

        if ((*mpt)[goodmuons[0]] < (*mpt)[goodmuons[1]]) {
            idx1 = goodmuons[1];
            idx2 = goodmuons[0];
	    }
	
        TLorentzVector mm;
	
        TLorentzVector m1;
        TLorentzVector m2;
	
        
        m1.SetPtEtaPhiM((*mpt)[idx1], (*meta)[idx1], (*mphi)[idx1], 0.1057);
        m2.SetPtEtaPhiM((*mpt)[idx2], (*meta)[idx2], (*mphi)[idx2], 0.1057);

        mm += m1;
        mm += m2;
        m1pt   = m1.Pt();
        m1eta  = m1.Eta();
        m1phi  = m1.Phi();
        m1iso  = (*cpiso)[idx1] + (*phiso)[idx1] + (*nhiso)[idx1] - ea*(*rho);
        m1id   = (*mid)[idx1];
        m1ch   = (*mcharge)[idx1];

        m2pt   = m2.Pt();
        m2eta  = m2.Eta();
        m2phi  = m2.Phi();
        m2iso  = (*cpiso)[idx2] + (*phiso)[idx2] + (*nhiso)[idx2] - ea*(*rho);
        m2id   = (*mid)[idx2];
	m2ch   = (*mcharge)[idx2];
	
	Run=*run;
	LumSec=*lumSec;


	//2018
	/*
11 L1_DoubleMu4p5_SQ_OS_dR_Max1p2
7  L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18	
2  L1_DoubleMu_15_7	
6  L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4
10 L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4
13 L1_DoubleMu0er1p5_SQ_dR_Max1p4

	*/
 /*
HIGH MASS TRIGGER NO CORRELATION: ID  0 - 4 - 9
'L1_DoubleMu_12_5',
'L1_DoubleMu_12_8',
'L1_DoubleMu_13_6',
'L1_DoubleMu_15_5',
'L1_DoubleMu_15_7',

'L1_TripleMu_4_4_4',
'L1_TripleMu_5_0_0',
'L1_TripleMu_5_3_3',
'L1_TripleMu_5_5_3',
'L1_QuadMu0',

THE LOW MASS TRIGGER: ID 10
'L1_DoubleMu0er1p5_SQ_OS_dR_Max1p4',

THE LOW MASS TRIGGER WITH CORR: 11 - 17
'L1_DoubleMu4p5er2p0_SQ_OS_Mass7to18',
'L1_DoubleMu4_SQ_OS_dR_Max1p2',
'L1_DoubleMu5_SQ_OS_Mass7to18',
'L1_DoubleMu_20_2_SQ_Mass_Max20',

'L1_DoubleMu0er1p4_SQ_OS_dR_Max1p4',

'L1_DoubleMu4p5_SQ_OS_dR_Max1p2',
'L1_DoubleMu6_SQ_OS',

THE LOW MASS TRIGGER TO MEASURE FAKE: ID 18 - 20 [ONLY IN FROM RUN 305405]
'L1_DoubleMu0er1p5_SQ_dR_Max1p4',
'L1_DoubleMu0er2_SQ_dR_Max1p4',
'L1_DoubleMu0_SQ'
	*/

	//'L1_DoubleMu4_SQ_OS_dR_Max1p2', [12]
	//'L1_DoubleMu4p5_SQ_OS_dR_Max1p2', [16]
	//
        mass   = mm.M();
        nvtx = *nverts;
        	
        bool passPVconstraintAbs = false;
	bool passPVconstraintSig = false;
	float BSx = 0.092;
	float BSy = -0.06;
	float slidePt1 = 3.;	
	float slidePt2 = 3.;
	float maxEta=TMath::Max(abs(m1eta),abs(m2eta));
	
	if(nvtx==0) continue;

	if( (  sqrt( ((*vtxX)[0] - BSx)*((*vtxX)[0] - BSx) + ((*vtxY)[0] - BSy)*((*vtxY)[0] - BSy) )/sqrt( ((*vtxYError)[0]*(*vtxYError)[0]) + ((*vtxXError)[0]*(*vtxXError)[0]))  ) < 1.2 ) passPVconstraintSig = true;
	
	if(m1ch*m2ch<0. && passPVconstraintSig && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<1.9) dimuonMass->Fill(mass);
	//if(m1ch*m2ch<0. && passPVconstraintSig && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<1.9 && mass>2.7 && mass<3.4) dimuonMassJPsi->Fill(mass);

	/*float ma=0.2;
	for(int j=0; j<400.; j++){
      		ma = ma+(ma*0.01); 
     		if(mass > ma-(ma*0.01*10.) && mass < ma+(ma*0.01*10.)) 
		{
			if(m1ch*m2ch<0. && passPVconstraintSig && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<1.9){ massforLimit_CatA[j]->Fill(mass); }
	    	}     
		}*/	
	
   	}		
   }
   
    dimuonMass->Write();
    // dimuonMassJPsi->Write();
    /*for(int j=0; j<400.;j++){
	massforLimit_CatA[j]->Write();
      }*/

    outfile->Close();

}
