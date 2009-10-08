import FWCore.ParameterSet.Config as cms

from RecoPixelVertexing.PixelTriplets.PixelTripletHLTGenerator_cfi import *
from RecoPixelVertexing.PixelLowPtUtilities.ClusterShapeHitFilterESProducer_cfi import *

hiPixel3PrimTracks = cms.EDFilter("PixelTrackProducer",

    passLabel  = cms.string('Pixel triplet primary tracks with vertex constraint'),

    # Region
    RegionFactoryPSet = cms.PSet(
	  ComponentName = cms.string("GlobalTrackingRegionWithVerticesProducer"),
	  RegionPSet = cms.PSet(
		ptMin         = cms.double(1.5),	  
		originRadius  = cms.double(0.2),
		nSigmaZ       = cms.double(3.0),		
		beamSpot      = cms.InputTag("offlineBeamSpot"),
		precise       = cms.bool(True),		
		useFoundVertices = cms.bool(True),
		VertexCollection = cms.InputTag("hiPixelAdaptiveVertex"),		
		useFixedError = cms.bool(True),
		fixedError    = cms.double(0.2),
		sigmaZVertex  = cms.double(3.0),		
	  )
    ),
     
    # Ordered Hits
    OrderedHitsFactoryPSet = cms.PSet( 
          ComponentName = cms.string( "StandardHitTripletGenerator" ),
	  SeedingLayers = cms.string( "PixelLayerTriplets" ),
          GeneratorPSet = cms.PSet( 
		PixelTripletHLTGenerator
          )
    ),
	
    # Fitter
    FitterPSet = cms.PSet( 
	  ComponentName = cms.string('PixelFitterByHelixProjections'),
	  TTRHBuilder = cms.string('TTRHBuilderWithoutAngle4PixelTriplets')
    ),
	
    # Filter
    useFilterWithES = cms.bool( True ),
    FilterPSet = cms.PSet(
          ComponentName = cms.string( "HIPixelTrackFilter" ),
          ptMin = cms.double( 1.5 ),
          chi2 = cms.double( 1000.0 ),
          useClusterShape = cms.bool( False ),
          VertexCollection = cms.string("hiSelectedVertex"),
          nSigmaTipMaxTolerance = cms.double( 6.0 ), # d0 w.r.t. (0,0)
          tipMax = cms.double( 0.3 )
    ),
	
    # Cleaner
    CleanerPSet = cms.PSet(  
	  ComponentName = cms.string( "TrackCleaner" )
    )
)
