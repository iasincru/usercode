import FWCore.ParameterSet.Config as cms

writeNTuple = cms.EDAnalyzer('NTupleWriter',
                       PUSource = cms.InputTag("addPileupInfo"),
                       genParticles = cms.InputTag("genParticles"),
                       genMET = cms.InputTag("genMET"),
                       src = cms.InputTag("genEvt"),
                       genEventHiggs = cms.InputTag("genEvtHiggs"),
                       genZDecay = cms.InputTag("genZDecay"),
                       muons = cms.InputTag("muons"),
                       elecs = cms.InputTag("elecs"),
                       jets      = cms.InputTag("jets"),
                       jetProperties = cms.InputTag("jetProperties"),
                       jetsForMET      = cms.InputTag("jetsForMET"),
                       jetsForMETuncorr      = cms.InputTag("jetsForMETuncorr"),
                       met       = cms.InputTag("met"),
                       mvamet    = cms.InputTag("mvamet"),
                       vertices  = cms.InputTag('goodOfflinePrimaryVertices'),
                       genJets       = cms.InputTag("ak5GenJets", "", "SIM"),
                       BJetIndex     = cms.InputTag("produceHadronLevelBJets", "BJetIndex"),
                       AntiBJetIndex = cms.InputTag("produceHadronLevelBJets", "AntiBJetIndex"),
                       BHadJetIndex = cms.InputTag("produceGenLevelBJets", "BHadJetIndex"),
                       AntiBHadJetIndex = cms.InputTag("produceGenLevelBJets", "AntiBHadJetIndex"),
                       BHadrons = cms.InputTag("produceGenLevelBJets", "BHadrons"),
                       AntiBHadrons = cms.InputTag("produceGenLevelBJets", "AntiBHadrons"),
                       BHadronFromTopB = cms.InputTag("produceGenLevelBJets", "BHadronFromTopB"),
                       AntiBHadronFromTopB = cms.InputTag("produceGenLevelBJets", "AntiBHadronFromTopB"),
                       BHadronVsJet = cms.InputTag("produceGenLevelBJets", "BHadronVsJet"),
                       AntiBHadronVsJet = cms.InputTag("produceGenLevelBJets", "AntiBHadronVsJet"),
                       genBHadPlusMothers = cms.InputTag("matchGenHFHadronJets","genBHadPlusMothers"),
                       genBHadPlusMothersIndices = cms.InputTag("matchGenHFHadronJets","genBHadPlusMothersIndices"),
                       genBHadIndex = cms.InputTag("matchGenHFHadronJets","genBHadIndex"),
                       genBHadFlavour = cms.InputTag("matchGenHFHadronJets","genBHadFlavour"),
                       genBHadJetIndex = cms.InputTag("matchGenHFHadronJets","genBHadJetIndex"),
                       genBHadLeptonIndex = cms.InputTag("matchGenHFHadronJets","genBHadLeptonIndex"),
                       genBHadLeptonHadronIndex = cms.InputTag("matchGenHFHadronJets","genBHadLeptonHadronIndex"),
                       genBHadFromTopWeakDecay = cms.InputTag("matchGenHFHadronJets","genBHadFromTopWeakDecay"),
                       genBHadFromBHadron = cms.InputTag("matchGenHFCHadronJets","genBHadFromBHadron"),
                       genCHadPlusMothers = cms.InputTag("matchGenHFHadronJets","genCHadPlusMothers"),
                       genCHadPlusMothersIndices = cms.InputTag("matchGenHFHadronJets","genCHadPlusMothersIndices"),
                       genCHadIndex = cms.InputTag("matchGenHFHadronJets","genCHadIndex"),
                       genCHadFlavour = cms.InputTag("matchGenHFHadronJets","genCHadFlavour"),
                       genCHadJetIndex = cms.InputTag("matchGenHFHadronJets","genCHadJetIndex"),
                       genCHadLeptonIndex = cms.InputTag("matchGenHFHadronJets","genCHadLeptonIndex"),
                       genCHadLeptonHadronIndex = cms.InputTag("matchGenHFHadronJets","genCHadLeptonHadronIndex"),
                       genCHadFromTopWeakDecay = cms.InputTag("matchGenHFHadronJets","genCHadFromTopWeakDecay"),
                       genCHadFromBHadron = cms.InputTag("matchGenHFCHadronJets","genCHadFromBHadron"),
                       saveHadronMothers = cms.bool(False),
                       includeTrigger = cms.bool(False),
                       triggerResults = cms.InputTag('TriggerResults','','HLT'),
                       decayMode = cms.InputTag("generatorTopFilter", "decayMode"),
                       higgsDecayMode = cms.InputTag("generatorHiggsFilter", "higgsDecayMode"),
                       isTtBarSample = cms.bool(True),
                       isHiggsSample = cms.bool(False),
                       isZSample = cms.bool(False),
                       isMC = cms.bool(True),
                       sampleName = cms.string("please give sampleName"),
                       channelName = cms.string("please give channelName"),
                       systematicsName = cms.string("please give systematicsName"),
                       includePDFWeights = cms.bool(False),
                       pdfWeights = cms.InputTag('pdfWeights:cteq66'),
                       includeZdecay = cms.bool(False),
                       Zdecay = cms.InputTag('ZDecayProducer','zDecayMode'),
                       #maybe remove/change these two in the future?
                       hypoKey = cms.InputTag("ttFullLepHypKinSolution","Key"),
                       FullLepEvent = cms.InputTag("ttFullLepEvent"),
)
