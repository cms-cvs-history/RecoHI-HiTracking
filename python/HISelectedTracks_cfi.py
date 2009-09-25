import FWCore.ParameterSet.Config as cms

# reco track quality cuts (dca, nhits, prob) and minpt selection
#hiSelectedTracks = cms.EDFilter("TrackSelector",
#  src = cms.InputTag("hiGlobalPrimTracks"),
#  cut = cms.string('pt > 0.9 && abs(d0/d0Error)<3 && recHitsSize>12 && chi2prob(chi2,ndof)>0.01')
#)

hiSelectedTracks = cms.EDFilter("HITrackSelection",
    src = cms.InputTag("hiGlobalPrimTracks"),
	VertexCollection = cms.string("hiSelectedVertex"),
	ptMin = cms.double(0.9),
	nSigmaZ = cms.double(3.0),
	minZCut = cms.double(0.2), #one should test how much smaller this can go and be effective
	maxD0Significance = cms.double(3.0),
        minValidHits = cms.double(12),
        minChi2Prob = cms.double(0.01)
)
