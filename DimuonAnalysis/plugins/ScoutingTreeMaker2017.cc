// Standard C++ includes
#include <memory>
#include <vector>
#include <iostream>

// ROOT includes
#include <TTree.h>
#include <TLorentzVector.h>
#include <TPRegexp.h>

// CMSSW framework includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

// CMSSW data formats
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Scouting/interface/ScoutingMuon.h"
#include "DataFormats/Scouting/interface/ScoutingParticle.h"
#include "DataFormats/Scouting/interface/ScoutingVertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenLumiInfoHeader.h"

// Other relevant CMSSW includes
#include "CommonTools/UtilAlgos/interface/TFileService.h" 
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"


#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Scouting/interface/ScoutingMuon.h"
#include "DataFormats/Scouting/interface/ScoutingVertex.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "L1Trigger/L1TGlobal/interface/L1TGlobalUtil.h"
#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionData.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionEvaluator.h"
#include "HLTrigger/HLTcore/interface/TriggerExpressionParser.h"


class ScoutingTreeMaker2017 : public edm::one::EDAnalyzer<edm::one::SharedResources, edm::one::WatchRuns, edm::one::WatchLuminosityBlocks> {
	public:
		explicit ScoutingTreeMaker2017(const edm::ParameterSet&);
		~ScoutingTreeMaker2017();
		
		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
	
	
	private:
        virtual void beginJob() override;
        virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
        virtual void endJob() override;

        virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
        virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
        virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
        virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

        const edm::InputTag triggerResultsTag;
        const edm::EDGetTokenT<edm::TriggerResults>             triggerResultsToken;
        const edm::EDGetTokenT<std::vector<ScoutingVertex> >    verticesToken;
        const edm::EDGetTokenT<std::vector<ScoutingMuon> >      muonsToken;
  //        const edm::EDGetTokenT<std::vector<ScoutingParticle> >  pfcandsToken;
        const edm::EDGetTokenT<double>                          rhoToken;

        const edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileupInfoToken;
        const edm::EDGetTokenT<std::vector<reco::GenParticle> > gensToken;
        const edm::EDGetTokenT<GenEventInfoProduct>             genEvtInfoToken;

        std::vector<std::string> triggerPathsVector;
        std::map<std::string, int> triggerPathsMap;

        // Flags used in the analyzer
        // - isMC             : Is a Monte Carlo sample
        // - useLHEWeights    : If this is an MC sample, should we read the LHE level event weights
        // - storeReducedInfo : Only store the muon 4-vector, muon ID flag, and the total isolation 
        // - applyHLTFilter   : Fill the tree only when an event passes the set of "interesting" triggers
        // - require2Muons    : Fill the tree only when there are at least 2 muons in the event
	
	bool doL1;       
        triggerExpression::Data triggerCache_;
      
	bool isMC;
        bool useLHEWeights;
        bool storeReducedInfo;		 
        bool applyHLTFilter;		 
        bool require2Muons;		 

        // Cross-section and event weight information for MC events
        double                       xsec, wgt;

        // Generator-level information
        // Flags for the different types of triggers used in the analysis
        // For now we are interested in events passing either the single or double lepton triggers
        unsigned char                trig;
       
	edm::InputTag                algInputTag_;       
        edm::EDGetToken              algToken_;
        l1t::L1TGlobalUtil           *l1GtUtils_;
        std::vector<std::string>     l1Seeds_;
        std::vector<bool>            l1Result_;
       
	// Pileup information
        unsigned                     putrue, nvtx;
        double                       rho;

        // Collection of muon 4-vectors, muon ID abd isolation variables
	std::vector<float>           vtxX;
	std::vector<float>           vtxY;
	std::vector<float>           vtxZ;

	std::vector<float>           vtxXError;
	std::vector<float>           vtxYError;
	std::vector<float>           vtxZError;
	std::vector<float>           vtxNdof;
	std::vector<float>           vtxChi2;
	
        std::vector<float>           muonpt;
        std::vector<float>           muoneta;
        std::vector<float>           muonphi;
	std::vector<float>           muoncharge;
	std::vector<float>           muonvtxind;
        std::vector<float>           chi2;
        std::vector<float>           dxy;
        std::vector<float>           dz;
        std::vector<float>           cpiso;
        std::vector<float>           chiso;
        std::vector<float>           nhiso;
        std::vector<float>           phiso;
        std::vector<float>           puiso;
        std::vector<float>           tkiso;
        std::vector<float>           eciso;
        std::vector<float>           hciso;
        std::vector<float>           iso;
        std::vector<char>            muonid;
        std::vector<char>            muonLooseid;
        std::vector<unsigned char>   nMuonHits;       
        std::vector<unsigned char>   nPixelHits;       
        std::vector<unsigned char>   nTkLayers;       
        std::vector<unsigned char>   nStations;       

        // 4-vector of genparticles, and their PDG IDs            
        std::vector<TLorentzVector>  gens;
        std::vector<char>            gid;

        // TTree carrying the event weight information
        TTree* tree;

  //Run and lumisection
  	int run;
  	int lumSec;

};

ScoutingTreeMaker2017::ScoutingTreeMaker2017(const edm::ParameterSet& iConfig): 
    triggerResultsTag        (iConfig.getParameter<edm::InputTag>("triggerresults")),
    triggerResultsToken      (consumes<edm::TriggerResults>                    (triggerResultsTag)),
    verticesToken            (consumes<std::vector<ScoutingVertex> >           (iConfig.getParameter<edm::InputTag>("vertices"))),
    muonsToken               (consumes<std::vector<ScoutingMuon> >             (iConfig.getParameter<edm::InputTag>("muons"))), 
    //pfcandsToken             (consumes<std::vector<ScoutingParticle> >         (iConfig.getParameter<edm::InputTag>("pfcands"))), 
    rhoToken                 (consumes<double>                                 (iConfig.getParameter<edm::InputTag>("rho"))), 
    pileupInfoToken          (consumes<std::vector<PileupSummaryInfo> >        (iConfig.getParameter<edm::InputTag>("pileupinfo"))),
    gensToken                (consumes<std::vector<reco::GenParticle> >        (iConfig.getParameter<edm::InputTag>("gens"))),
    genEvtInfoToken          (consumes<GenEventInfoProduct>                    (iConfig.getParameter<edm::InputTag>("geneventinfo"))),
    
    doL1                     (iConfig.existsAs<bool>("doL1")               ?    iConfig.getParameter<bool>("doL1")             : false),
    isMC                     (iConfig.existsAs<bool>("isMC")               ?    iConfig.getParameter<bool>  ("isMC")            : false),
    useLHEWeights            (iConfig.existsAs<bool>("useLHEWeights")      ?    iConfig.getParameter<bool>  ("useLHEWeights")   : false),
    storeReducedInfo         (iConfig.existsAs<bool>("storeReducedInfo")   ?    iConfig.getParameter<bool>  ("storeReducedInfo"): false),
    applyHLTFilter           (iConfig.existsAs<bool>("applyHLTFilter")     ?    iConfig.getParameter<bool>  ("applyHLTFilter")  : false),
    require2Muons            (iConfig.existsAs<bool>("require2Muons")      ?    iConfig.getParameter<bool>  ("require2Muons")   : false),
    xsec                     (iConfig.existsAs<double>("xsec")             ?    iConfig.getParameter<double>("xsec") * 1000.0   : 1.)
{
	usesResource("TFileService");
	if (doL1) {
        	algInputTag_ = iConfig.getParameter<edm::InputTag>("AlgInputTag");
        	algToken_ = consumes<BXVector<GlobalAlgBlk>>(algInputTag_);
    		l1Seeds_ = iConfig.getParameter<std::vector<std::string> >("l1Seeds");
       	        l1GtUtils_ = new l1t::L1TGlobalUtil(iConfig,consumesCollector());	
    	}
    	else {
        	l1Seeds_ = std::vector<std::string>();
        	l1GtUtils_ = 0;
		}
}


ScoutingTreeMaker2017::~ScoutingTreeMaker2017() {
}

void ScoutingTreeMaker2017::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;
    using namespace std;
    using namespace reco;
    
    // Handles to the EDM content
    edm::Handle<edm::TriggerResults> triggerResultsH;
    iEvent.getByToken(triggerResultsToken, triggerResultsH);
   
    Handle<vector<ScoutingVertex> > verticesH;
    iEvent.getByToken(verticesToken, verticesH);
    
    Handle<vector<ScoutingMuon> > muonsH;
    iEvent.getByToken(muonsToken, muonsH);
    
    Handle<double> rhoH;
    iEvent.getByToken(rhoToken, rhoH);
    
    Handle<vector<PileupSummaryInfo> > pileupInfoH;
    if (isMC) iEvent.getByToken(pileupInfoToken, pileupInfoH);
    
    Handle<GenEventInfoProduct> genEvtInfoH;
    if (isMC && useLHEWeights) iEvent.getByToken(genEvtInfoToken, genEvtInfoH);
    
    Handle<vector<GenParticle> > gensH;
    if (isMC) iEvent.getByToken(gensToken, gensH);
    
    // Event information - MC weight, event ID (run, lumi, event) and so on
    wgt = 1.0;
    if (isMC && useLHEWeights && genEvtInfoH.isValid()) wgt = genEvtInfoH->weight(); 

    // Trigger info
    trig = 0;

    run = iEvent.eventAuxiliary().run();
    lumSec = iEvent.eventAuxiliary().luminosityBlock();

    //if(run < 305405) return;


    // Which triggers fired
    for (size_t i = 0; i < triggerPathsVector.size(); i++) {
        if (triggerPathsMap[triggerPathsVector[i]] == -1) continue;
        if (i == 0  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=   1; // DST_L1DoubleMu_CaloScouting_PFScouting
        if (i == 1  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=   2; // DST_DoubleMu3_Mass10_CaloScouting_PFScouting
        if (i == 2  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=   4; // DST_ZeroBias_CaloScouting_PFScouting
        if (i == 3  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=   8; // DST_L1HTT_CaloScouting_PFScouting
        if (i == 4  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=  16; // DST_CaloJet40_CaloScouting_PFScouting
        if (i == 5  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=  32; // DST_HT250_CaloScouting
        if (i == 6  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig +=  64; // DST_HT410_PFScouting
        if (i == 7  && triggerResultsH->accept(triggerPathsMap[triggerPathsVector[i]])) trig += 128; // DST_HT450_PFScouting
	}


    

    bool triggered = false;
    if (trig  > 0) triggered = true;
    if (applyHLTFilter && !triggered) return;

    // Pileup information
    rho = *rhoH;
    
    //if (nvtx == 0) return;
    
    putrue = 0;
    if (isMC && pileupInfoH.isValid()) {
        for (auto pileupInfo_iter = pileupInfoH->begin(); pileupInfo_iter != pileupInfoH->end(); ++pileupInfo_iter) {
            if (pileupInfo_iter->getBunchCrossing() == 0) putrue = pileupInfo_iter->getTrueNumInteractions();
        }
    }

    // Clear all the vectors for every event
    gens.clear(); 
    gid.clear();
    vtxX.clear();
    vtxY.clear();
    vtxZ.clear();
    vtxXError.clear();
    vtxYError.clear();
    vtxZError.clear();
    vtxNdof.clear();
    vtxChi2.clear();
    muonpt.clear();
    muoneta.clear();
    muonphi.clear();
    muoncharge.clear();
    muonvtxind.clear();
    chi2.clear();
    dxy.clear();
    dz.clear();
    iso.clear();
    cpiso.clear();
    chiso.clear();
    nhiso.clear();
    phiso.clear();
    puiso.clear();
    tkiso.clear();
    eciso.clear();
    hciso.clear();
    muonid.clear();       
    nMuonHits.clear();       
    nPixelHits.clear();       
    nTkLayers.clear();       
    nStations.clear();  
    l1Result_.clear(); 
    muonLooseid.clear();
    // run.clear();
    // lumSec.clear();    
    
    //Vertex Info
    nvtx = 0;
    for (auto vtx_iter = verticesH->begin(); vtx_iter != verticesH->end(); ++vtx_iter) {
        nvtx++;
	vtxX.push_back(vtx_iter->x());        
	vtxY.push_back(vtx_iter->y());        
	vtxZ.push_back(vtx_iter->z());
	vtxXError.push_back(vtx_iter->xError());        
	vtxYError.push_back(vtx_iter->yError());        
	vtxZError.push_back(vtx_iter->zError());        
	vtxChi2.push_back(vtx_iter->chi2());        
	vtxNdof.push_back(vtx_iter->ndof());        
    }

    // Muon information
    for (auto muons_iter = muonsH->begin(); muons_iter != muonsH->end(); ++muons_iter) {
        muonpt .push_back(muons_iter->pt() );
        muoneta.push_back(muons_iter->eta());
        muonphi.push_back(muons_iter->phi());
	muoncharge.push_back(muons_iter->charge());
	muonvtxind.push_back(muons_iter->vtxIndx().size());
        nMuonHits .push_back(muons_iter->nValidMuonHits());       
        nPixelHits.push_back(muons_iter->nValidPixelHits());       
        nTkLayers .push_back(muons_iter->nTrackerLayersWithMeasurement());       
        nStations .push_back(muons_iter->nMatchedStations());       
        chi2      .push_back(muons_iter->ndof() > 0. ? muons_iter->chi2() / muons_iter->ndof() : 1e4);
        dxy       .push_back(muons_iter->dxy());
        dz        .push_back(muons_iter->dz());

        double cpisoval = 0.0;
        double chisoval = 0.0;
        double nhisoval = 0.0;
        double phisoval = 0.0;
        double puisoval = 0.0;
        double tkisoval = muons_iter->trackIso();
        double ecisoval = muons_iter->ecalIso();
        double hcisoval = muons_iter->hcalIso();	        
        double isoval = tkisoval + max(0., nhisoval + phisoval - 0.5*puisoval);

        cpiso.push_back(cpisoval);
        chiso.push_back(chisoval);
        nhiso.push_back(nhisoval);
        phiso.push_back(phisoval);
        puiso.push_back(puisoval);
        tkiso.push_back(tkisoval);
        eciso.push_back(ecisoval);
        hciso.push_back(hcisoval);
        iso  .push_back(  isoval);

        char muonidval = 1;
        if (nMuonHits.back() > 0 && nPixelHits.back() > 0 && chi2.back() < 10. && nStations.back() > 1 && nTkLayers.back() > 5) muonidval += 2;
        muonidval *= char(muons_iter->charge());
        muonid.push_back(muonidval);

	char muonLooseidval = 1;
        if ( nPixelHits.back() > 0 && chi2.back() < 10. && nTkLayers.back() > 5) muonLooseidval += 2;
        muonLooseidval *= char(muons_iter->charge());
        muonLooseid.push_back(muonLooseidval);

    }

    if (doL1) {
        	l1GtUtils_->retrieveL1(iEvent,iSetup,algToken_);
		/*		for(unsigned int r = 0; r<100; r++){
		string name ("empty");
                bool algoName_ = false;
 	        algoName_ = l1GtUtils_->getAlgNameFromBit(i,name);
		cout << "getAlgNameFromBit = " << algoName_  << endl;
 	        cout << "L1 bit number = " << i << " ; L1 bit name = " << name << endl;
		}*/
		for( unsigned int iseed = 0; iseed < l1Seeds_.size(); iseed++ ) {
  	    		bool l1htbit = 0;		
	    		l1GtUtils_->getFinalDecisionByName(string(l1Seeds_[iseed]), l1htbit);
            		l1Result_.push_back( l1htbit );
    		}
    }


    if (require2Muons && muonpt.size() < 2) return;
    
    // GEN information
    if (isMC && gensH.isValid()) {
        for (auto gens_iter = gensH->begin(); gens_iter != gensH->end(); ++gens_iter) {
            if (gens_iter->pdgId() ==  23 || abs(gens_iter->pdgId()) == 24 || gens_iter->pdgId() == 25) {
                TLorentzVector g4;
                g4.SetPtEtaPhiM(gens_iter->pt(), gens_iter->eta(), gens_iter->phi(), gens_iter->mass());
                gens.push_back(g4);
                gid.push_back(char(gens_iter->pdgId()));
            }
            if (abs(gens_iter->pdgId()) > 10 && abs(gens_iter->pdgId()) < 17 && gens_iter->fromHardProcessFinalState()) {
                TLorentzVector g4;
                g4.SetPtEtaPhiM(gens_iter->pt(), gens_iter->eta(), gens_iter->phi(), gens_iter->mass());
                gens.push_back(g4);
                gid.push_back(char(gens_iter->pdgId()));
            }
        }
    }

    
	tree->Fill();
 
	
	
}


void ScoutingTreeMaker2017::beginJob() {
    // Access the TFileService
    edm::Service<TFileService> fs;


    //book Histos
    //diMuNamesHisto_ = fs_->make<TH1F>("diMuMass", "diMuMass", 500, 0, 100);


    // Create the TTree
    tree = fs->make<TTree>("tree"       , "tree");

    // Event weights
    if (isMC) {
    tree->Branch("xsec"                 , &xsec                          , "xsec/D");
    tree->Branch("wgt"                  , &wgt                           , "wgt/D");

    // Gen info
    tree->Branch("gens"                 , "std::vector<TLorentzVector>"  , &gens     , 32000, 0);
    tree->Branch("gid"                  , "std::vector<char>"            , &gid      );
    }
    tree->Branch("lumSec", &lumSec, "lumSec/i" );
    tree->Branch("run", &run, "run/i");
    tree->Branch("nvtx", &nvtx, "nvtx/i");
    
    // Triggers
    tree->Branch("trig"                 , &trig                          , "trig/b");
    tree->Branch("l1Result"		, "std::vector<bool>"             ,&l1Result_	, 32000, 0);		
    // Pileup info
    tree->Branch("nvtx"                 , &nvtx                          , "nvtx/i"       );
    tree->Branch("rho"                  , &rho                           , "rho/D"        );
    //if (isMC)
      //tree->Branch("putrue"               , &putrue                        , "putrue/i");

    // Muon info
    tree->Branch("vtxX"                 , "std::vector<float>"           , &vtxX      , 32000, 0);
    tree->Branch("vtxY"                 , "std::vector<float>"           , &vtxY      , 32000, 0);
    tree->Branch("vtxZ"                 , "std::vector<float>"           , &vtxZ      , 32000, 0);

    tree->Branch("vtxXError"                 , "std::vector<float>"           , &vtxXError      , 32000, 0);
    tree->Branch("vtxYError"                 , "std::vector<float>"           , &vtxYError      , 32000, 0);
    tree->Branch("vtxZError"                 , "std::vector<float>"           , &vtxZError      , 32000, 0);

    tree->Branch("vtxChi2"                 , "std::vector<float>"           , &vtxChi2      , 32000, 0);
    tree->Branch("vtxNdof"                 , "std::vector<float>"           , &vtxNdof      , 32000, 0);

    tree->Branch("muonpt"               , "std::vector<float>"           , &muonpt    , 32000, 0);
    tree->Branch("muoneta"              , "std::vector<float>"           , &muoneta   , 32000, 0);
    tree->Branch("muonphi"              , "std::vector<float>"           , &muonphi   , 32000, 0);
    tree->Branch("muoncharge"           , "std::vector<float>"           , &muoncharge, 32000, 0);
    tree->Branch("muonvtxind"           , "std::vector<float>"           , &muonvtxind, 32000, 0);
    if (!storeReducedInfo) {
    tree->Branch("nMuonHits"            , "std::vector<unsigned char>"   , &nMuonHits , 32000, 0);
    tree->Branch("nPixelHits"           , "std::vector<unsigned char>"   , &nPixelHits, 32000, 0);
    tree->Branch("nTkLayers"            , "std::vector<unsigned char>"   , &nTkLayers , 32000, 0);
    tree->Branch("nStations"            , "std::vector<unsigned char>"   , &nStations , 32000, 0);
    tree->Branch("chi2"                 , "std::vector<float>"           , &chi2      , 32000, 0);
    tree->Branch("dxy"                  , "std::vector<float>"           , &dxy       , 32000, 0);
    tree->Branch("dz"                   , "std::vector<float>"           , &dz        , 32000, 0);
    tree->Branch("cpiso"                , "std::vector<float>"           , &cpiso     , 32000, 0);
    tree->Branch("chiso"                , "std::vector<float>"           , &chiso     , 32000, 0);
    tree->Branch("nhiso"                , "std::vector<float>"           , &nhiso     , 32000, 0);
    tree->Branch("phiso"                , "std::vector<float>"           , &phiso     , 32000, 0);
    tree->Branch("puiso"                , "std::vector<float>"           , &puiso     , 32000, 0);
    tree->Branch("tkiso"                , "std::vector<float>"           , &tkiso     , 32000, 0);
    tree->Branch("eciso"                , "std::vector<float>"           , &eciso     , 32000, 0);
    tree->Branch("hciso"                , "std::vector<float>"           , &hciso     , 32000, 0);
    }
    else 
    tree->Branch("iso"                  , "std::vector<float>"           , &iso       , 32000, 0);
    tree->Branch("muonid"               , "std::vector<char>"            , &muonid    , 32000, 0);
    tree->Branch("muonLooseid"               , "std::vector<char>"            , &muonLooseid    , 32000, 0);
}

void ScoutingTreeMaker2017::endJob() {
}

void ScoutingTreeMaker2017::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup) {
    // HLT paths
    triggerPathsVector.push_back("DST_L1DoubleMu_CaloScouting_PFScouting_v");
    triggerPathsVector.push_back("DST_DoubleMu3_noVtx_CaloScouting_v*");
    triggerPathsVector.push_back("DST_ZeroBias_CaloScouting_PFScouting_v");
    triggerPathsVector.push_back("DST_L1HTT_CaloScouting_PFScouting_v*");
    triggerPathsVector.push_back("DST_CaloJet40_CaloScouting_PFScouting_v*");
    triggerPathsVector.push_back("DST_HT250_CaloScouting_v*");
    triggerPathsVector.push_back("DST_HT410_PFScouting_v*");
    triggerPathsVector.push_back("DST_HT450_PFScouting_v*");

    HLTConfigProvider hltConfig;
    bool changedConfig = false;
    hltConfig.init(iRun, iSetup, triggerResultsTag.process(), changedConfig);

    for (size_t i = 0; i < triggerPathsVector.size(); i++) {
        triggerPathsMap[triggerPathsVector[i]] = -1;
    }

    for(size_t i = 0; i < triggerPathsVector.size(); i++){
        TPRegexp pattern(triggerPathsVector[i]);
        for(size_t j = 0; j < hltConfig.triggerNames().size(); j++){
            std::string pathName = hltConfig.triggerNames()[j];
            if(TString(pathName).Contains(pattern)){
                triggerPathsMap[triggerPathsVector[i]] = j;
            }
        }
    }
}

void ScoutingTreeMaker2017::endRun(edm::Run const&, edm::EventSetup const&) {
}

void ScoutingTreeMaker2017::beginLuminosityBlock(edm::LuminosityBlock const& iLumi, edm::EventSetup const&) {
}

void ScoutingTreeMaker2017::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {
}

void ScoutingTreeMaker2017::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

DEFINE_FWK_MODULE(ScoutingTreeMaker2017);
