import FWCore.ParameterSet.Config as cms

# reco track quality cuts (dca, nhits, prob) and minpt selection
#hiSelectedTracks = cms.EDFilter("TrackSelector",
#  src = cms.InputTag("hiGlobalPrimTracks"),
#  cut = cms.string('pt > 0.9 && abs(d0/d0Error)<3 && recHitsSize>12 && chi2prob(chi2,ndof)>0.01')
#)


#hiSelectedTracks = cms.EDFilter("HITrackSelection",
#    src = cms.InputTag("hiGlobalPrimTracks"),
#	VertexCollection = cms.string("hiSelectedVertex"),
#	ptMin = cms.double(0.9),
#	nSigmaZ = cms.double(3.0),
#	minZCut = cms.double(0.2), #one should test how much smaller this can go and be effective
#	maxD0Significance = cms.double(3.0),
#        minValidHits = cms.double(12),
#        minChi2Prob = cms.double(0.01)
#)


hiSelectedTracks = cms.EDProducer("AnalyticalTrackSelector",
    src = cms.InputTag("hiGlobalPrimTracks"),
    keepAllTracks = cms.bool(False), ## if set to true tracks failing this filter are kept in the output
    beamspot = cms.InputTag("offlineBeamSpot"),
                           
    vertices = cms.InputTag("hiSelectedVertex"),
    vtxNumber = cms.int32(-1),
    vtxTracks = cms.uint32(2), ## at least 3 tracks by default
    vtxChi2Prob = cms.double(0.01), ## at least 1% chi2nprobability (if it has a chi2)

    copyTrajectories = cms.untracked.bool(True),  ## false by default, needed by TrackClusterRemover
    copyExtras = cms.untracked.bool(True), ## set to false on AOD
    qualityBit = cms.string(''), ## set to '' or comment out if you don't want to set the bit

    # parameters for adapted optimal cuts on chi2 and primary vertex compatibility
    chi2n_par = cms.double(0.4),         # normalizedChi2 < nLayers * chi2n_par
    res_par = cms.vdouble(0.003, 0.001),
    d0_par1 = cms.vdouble(9999, 1),      # parameterized nomd0E
    dz_par1 = cms.vdouble(9999, 1),
    d0_par2 = cms.vdouble(5.0, 0.3),     # d0E from tk.d0Error
    dz_par2 = cms.vdouble(30.0, 0.3),
    # Boolean indicating if adapted primary vertex compatibility cuts are to be applied.
    applyAdaptedPVCuts = cms.bool(True),

    # Impact parameter absolute cuts.
    max_d0 = cms.double(100.),
    max_z0 = cms.double(100.),

    # Cuts on numbers of layers with hits/3D hits/lost hits. 
    minNumberLayers = cms.uint32(7),
    minNumber3DLayers = cms.uint32(3),
    maxNumberLostLayers = cms.uint32(999)
 
)
