//#include "sumwgt.h"
#include "TFileCollection.h"
#include "TChain.h"
#include "TFile.h"
#include <TTreeReader.h>
#include "TH1D.h"
#include "TH2D.h"
#include <TTreeReaderValue.h>
#include "TLorentzVector.h"

void trimscoutMakeTheCardsLMnew(string treepath = "/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/ScoutingRunD/ScoutingCaloMuon/crab_20181212_141716/181212_131724/0000/scout_2.root", const char* outfilename = "./scoutData4MuonsM70.root", bool isMC=false) {
 
   vector<string> filesToRun;
   vector<bool> isData;
   string dirIn="/eos/cms/store/group/phys_exotica/darkPhoton/jakob/2017/ScoutingRunD/ScoutingCaloMuon/crab_20181212_141716/181212_131724/0000/";
   //string dirIn="";
   filesToRun.push_back(dirIn.append(treepath));isData.push_back(true);
   TFile* outfile = new TFile(outfilename, "RECREATE");
   TTree* outtree = new TTree("tree", "tree");
     

    TH1D* massforLimit_CatA[400];
    TH1D* massforLimit_CatB[400];
    TH1D* massforLimit_CatC[400];
    
    float m=0.2;

    for(int j=0; j<400; j++){
      m = m+(m*0.01); 
      massforLimit_CatA[j] = new TH1D(Form("massforLimit_CatA%d",j),Form("massforLimit_CatA%d",j),100,m-(m*0.01*10.),m+(m*0.01*10.));  massforLimit_CatA[j]->Sumw2();
      massforLimit_CatB[j] = new TH1D(Form("massforLimit_CatB%d",j),Form("massforLimit_CatB%d",j),100,m-(m*0.01*10.),m+(m*0.01*10.));  massforLimit_CatB[j]->Sumw2();
      massforLimit_CatC[j] = new TH1D(Form("massforLimit_CatC%d",j),Form("massforLimit_CatC%d",j),100,m-(m*0.01*10.),m+(m*0.01*10.));  massforLimit_CatC[j]->Sumw2();

      //massforLimitBlind[j] = new TH1D(Form("massforLimitBlind%d",j),Form("massforLimitBlind%d",j),48,m-(m*0.01*6.),m+(m*0.01*6.));  massforLimitBlind[j]->Sumw2();
      
    }
    
    

    
    TH2F* BS = new TH2F("BS","BS",50,-1.,1.,50,-1.,1.);

    TH1F* forLimitMassZ = new TH1F("forLimitMassZ","forLimitMassZ",1200,0.2,120.);
    TH1F* forLimitMassInclZ = new TH1F("forLimitMassInclZ","forLimitMassInclZ",1200,0.2,120.);
    TH1F* forResolutionAMassZ = new TH1F("forResolutionAMassZ","forResolutionAMassZ",240,60.,120.);
    TH1F* forResolutionBMassZ = new TH1F("forResolutionBMassZ","forResolutionBMassZ",240,60.,120.);
    TH1F* forResolutionCMassZ = new TH1F("forResolutionCMassZ","forResolutionCMassZ",240,60.,120.);
    TH1F* forResolutionAMassJPsi = new TH1F("forResolutionAMassJPsi","forResolutionAMassJPsi",45,2.6,3.5);
    TH1F* forResolutionBMassJPsi = new TH1F("forResolutionBMassJPsi","forResolutionBMassJPsi",45,2.6,3.5);
    TH1F* forResolutionCMassJPsi = new TH1F("forResolutionCMassJPsi","forResolutionCMassJPsi",45,2.6,3.5);


    TH1F* massforLimitFull = new TH1F("massforLimitFull","massforLimitFull",5500,0.,11.);
    TH1F* massforLimitEta = new TH1F("massforLimitEta","massforLimitEta",260,0.490,0.620);
    TH1F* massforLimitOmega = new TH1F("massforLimitOmega","massforLimitOmega",400,0.68,0.88);
    TH1F* massforLimitPhi = new TH1F("massforLimitPhi","massforLimitPhi",480,0.90,1.14);
    TH1F* massforLimitJPsiPsi = new TH1F("massforLimitJPsiPsi","massforLimitJPsiPsi",3000,2.7,4.2);
    TH1F* massforLimitUpsilon = new TH1F("massforLimitUpsilon","massforLimitUpsilon",5000,8.5,11.);

    TH1F* massforLimitFullTight = new TH1F("massforLimitFullTight","massforLimitFullTight",5000,0.,10.);
    TH1F* massforLimitEtaTight = new TH1F("massforLimitEtaTight","massforLimitEtaTight",260,0.490,0.620);
    TH1F* massforLimitOmegaTight = new TH1F("massforLimitOmegaTight","massforLimitOmegaTight",400,0.68,0.88);
    TH1F* massforLimitPhiTight = new TH1F("massforLimitPhiTight","massforLimitPhiTight",480,0.90,1.14);
    TH1F* massforLimitJPsiPsiTight = new TH1F("massforLimitJPsiPsiTight","massforLimitJPsiPsiTight",3000,2.7,4.2);
    TH1F* massforLimitUpsilonTight = new TH1F("massforLimitUpsilonTight","massforLimitUpsilonTight",5000,8.5,11.);
 


   for(unsigned int f=0; f<filesToRun.size(); f++){


     cout<<filesToRun[f]<<endl;
    TChain* chain = new TChain("mmtree/tree");
    chain->Add((TString)filesToRun[f]);
    
    TTreeReader reader(chain);
    
    TTreeReaderValue<double>*                      wgt;
    TTreeReaderValue<double>*                      xsec;
    
    
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
    cout<<"here4"<<endl;
    TTreeReaderValue<std::vector<float> >          vtxX     (reader, "vtxX"       );
    TTreeReaderValue<std::vector<float> >          vtxY     (reader, "vtxY"       );
    TTreeReaderValue<std::vector<float> >          vtxZ     (reader, "vtxZ"       );
    //TTreeReaderValue<std::vector<float> >          vtxchi2  (reader, "vtxchi2"    );
   
    TTreeReaderValue<double>                       rho      (reader, "rho"        );
    TTreeReaderValue<unsigned int>                 run      (reader, "run"        );
    TTreeReaderValue<unsigned int>                 lumSec   (reader, "lumSec"     );
  
  //TTreeReaderValue<std::vector<int> >		   pdgid    (reader, "pdgid" );
  //TTreeReaderValue<std::vector<int> > 	   motherid (reader, "motherid");
     
    
   if (isMC || !isData[f]) {
        wgt  = new TTreeReaderValue<double>(reader, "wgt" );
        xsec = new TTreeReaderValue<double>(reader, "xsec");
	
    }
	 
 

    double wgtsum  = 1.0;//isMC ? sumwgt(treepath) : 1.0;
    float  puwgt   = 1.0;
    float  mcwgt   = 1.0;
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

    if (isMC) {
    outtree->Branch("mcwgt" , &mcwgt , "mcwgt/F" );
    outtree->Branch("puwgt" , &puwgt , "puwgt/F" );
    }
    outtree->Branch("m1pt"  , &m1pt  , "m1pt/F"  );
    outtree->Branch("m1eta" , &m1eta , "m1eta/F" );
    outtree->Branch("m1phi" , &m1phi , "m1phi/F" );
    outtree->Branch("m1iso" , &m1iso , "m1iso/F" );
    outtree->Branch("m1id"  , &m1id  , "m1id/B"  );
    outtree->Branch("m2pt"  , &m2pt  , "m2pt/F"  );
    outtree->Branch("m2eta" , &m2eta , "m2eta/F" );
    outtree->Branch("m2phi" , &m2phi , "m2phi/F" );
    outtree->Branch("m2iso" , &m2iso , "m2iso/F" );
    outtree->Branch("m2id"  , &m2id  , "m2id/B"  );
    outtree->Branch("mass"  , &mass  , "mass/F"  );
    outtree->Branch("nvtx"  , &nvtx  , "nvtx/i"  );
    outtree->Branch("Run"   , &Run   , "Run/i"  );
    outtree->Branch("LumSec", &LumSec, "LumSec/i"  );

    //outtree->Branch("l1Bools"  , &l1Bools , "l1Bools" );
    int p=0;
    while(reader.Next()) {
      //if(!isData[f]) {if(pdgid->size()<2 || motherid->size()<2) continue;}
      if (((*hlt) & 2) == 0) continue;   
      bool passIso=false;
      bool passIsoLoose=false;
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
    

	if((*tkiso)[goodmuons[0]]<0.02 && (*tkiso)[goodmuons[1]]<0.02 ) passIso=true;
	if((*tkiso)[goodmuons[0]]<0.15 && (*tkiso)[goodmuons[1]]<0.15 ) passIsoLoose=true;

        if ((*mpt)[goodmuons[0]] < (*mpt)[goodmuons[1]]) {
            idx1 = goodmuons[1];
            idx2 = goodmuons[0];
	    }
	
        TLorentzVector mm;
	
        TLorentzVector m1;
        TLorentzVector m2;
	
        
        m1.SetPtEtaPhiM((*mpt)[idx1], (*meta)[idx1], (*mphi)[idx1], 0.1057);
        m2.SetPtEtaPhiM((*mpt)[idx2], (*meta)[idx2], (*mphi)[idx2], 0.1057);
	//m3.SetPtEtaPhiM((*mpt)[idx3], (*meta)[idx3], (*mphi)[idx3], 0.1057);
        //m4.SetPtEtaPhiM((*mpt)[idx4], (*meta)[idx4], (*mphi)[idx4], 0.1057);

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
	//	mass4  = mmmm.M();
        nvtx = *nverts;
        
	
        bool passPVconstraint = false;
	bool passPVconstraintTight = false;
	float BSx = 0.084;
	float BSy = -0.03;
	if(treepath.find("_13TeV") != string::npos){ BSx = -0.029; BSy = 0.07;}
	float slidePt1 = mm.M()/3.;
	if(slidePt1<3.) slidePt1 = 3.;
	float slidePt2 = mm.M()/4.;
	if(slidePt2<3.) slidePt2 = 3.;

	float maxEta=TMath::Max(abs(m1eta),abs(m2eta));

	
	

	if(nvtx>0. ){
	  if(  sqrt( ((*vtxX)[0] - BSx)*((*vtxX)[0] - BSx) + ((*vtxY)[0] - BSy)*((*vtxY)[0] - BSy) )  < 0.2 ) passPVconstraint = true;
	  }

	if(nvtx>0. ){
	  if(  sqrt( ((*vtxX)[0] - BSx)*((*vtxX)[0] - BSx) + ((*vtxY)[0] - BSy)*((*vtxY)[0] - BSy) )  < 0.1 ) passPVconstraintTight = true;
	  }

	if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && passIsoLoose) forLimitMassInclZ->Fill(mass);
	if(!( l1Result->at(0) || l1Result->at(4) || l1Result->at(11) || l1Result->at(12))) continue;
	if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && passIsoLoose) forLimitMassZ->Fill(mass);

	if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<2.0 && passIsoLoose){ 

	massforLimitFull->Fill(mass); 
	massforLimitEta->Fill(mass);
	massforLimitOmega->Fill(mass);
	massforLimitPhi->Fill(mass);
	massforLimitJPsiPsi->Fill(mass);
	massforLimitUpsilon->Fill(mass);

	if(passPVconstraintTight){

	massforLimitFullTight->Fill(mass); 
	massforLimitEtaTight->Fill(mass);
	massforLimitOmegaTight->Fill(mass);
	massforLimitPhiTight->Fill(mass);
	massforLimitJPsiPsiTight->Fill(mass);
	massforLimitUpsilonTight->Fill(mass);

	}

	/*
	0.49 - 062 : eta
	0.68 - 0.88 : omega
	0.90 - 1.14 : phi
	2.7 - 4.2 : jpsi + psi(2s)
	8.5 - 11 : Upsilons
	*/
	
	}


	
	if(mass>60. && mass<120.){
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<0.9 && 		      passIsoLoose){ forResolutionAMassZ->Fill(mass); }
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta>=0.9 && maxEta<1.2 && passIsoLoose){ forResolutionBMassZ->Fill(mass); }
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta>=1.2 && maxEta<2.4 && passIsoLoose){ forResolutionCMassZ->Fill(mass); }

	}


	if(mass>2.6 && mass<3.5){
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<0.9 && 		      passIsoLoose){ forResolutionAMassJPsi->Fill(mass); }
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta>=0.9 && maxEta<1.2 && passIsoLoose){ forResolutionBMassJPsi->Fill(mass); }
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta>=1.2 && maxEta<2.4 && passIsoLoose){ forResolutionCMassJPsi->Fill(mass); }

	}


	float ma=0.2;
	for(int j=0; j<400.; j++){
      		ma = ma+(ma*0.01); 

     		if(mass > ma-(ma*0.01*10.) && mass < ma+(ma*0.01*10.)) {

		  	if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta<0.9 && 		      passIsoLoose){ massforLimit_CatA[j]->Fill(mass); }
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta>=0.9 && maxEta<2. && passIsoLoose){ massforLimit_CatB[j]->Fill(mass); }
			if(m1ch*m2ch<0. && passPVconstraint && m1pt>slidePt1 && m2pt>slidePt2 && maxEta>=1.2 && maxEta<2.4 && passIsoLoose){ massforLimit_CatC[j]->Fill(mass); }

		}
      
   	 }	
	
	      	

	
      }
   }

   massforLimitFull->Write();
   massforLimitEta->Write();
   massforLimitOmega->Write();
   massforLimitPhi->Write();
   massforLimitJPsiPsi->Write();
   massforLimitUpsilon->Write();

   massforLimitFullTight->Write();
   massforLimitEtaTight->Write();
   massforLimitOmegaTight->Write();
   massforLimitPhiTight->Write();
   massforLimitJPsiPsiTight->Write();
   massforLimitUpsilonTight->Write();


   for(int j=0; j<400.;j++){
	massforLimit_CatA[j]->Write();
     	massforLimit_CatB[j]->Write();
     	massforLimit_CatC[j]->Write();
     }
   forLimitMassZ->Write();
   forLimitMassInclZ->Write();
   forResolutionAMassZ->Write();
   forResolutionBMassZ->Write();
   forResolutionCMassZ->Write();
   forResolutionAMassJPsi->Write();
   forResolutionBMassJPsi->Write();
   forResolutionCMassJPsi->Write();

    outfile->Close();

}
