import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
	#Atention, this file can be found in the '/afs/cern.ch/user/i/iasincru/CMSSW_4_2_5/src/Exer4/Exer04'
        'file:patTuple.root'
    )
)

process.demo = cms.EDAnalyzer('Ivan',
                              photonSrc   = cms.untracked.InputTag("cleanPatPhotons"),
                              electronSrc = cms.untracked.InputTag("cleanPatElectrons"),
                              muonSrc     = cms.untracked.InputTag("cleanPatMuons"),
                              tauSrc      = cms.untracked.InputTag("cleanPatTaus"),
                              jetSrc      = cms.untracked.InputTag("cleanPatJets"),
                              metSrc      = cms.untracked.InputTag("patMETs")
)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('analyzePatBasics.root')
)

process.p = cms.Path(process.demo)
