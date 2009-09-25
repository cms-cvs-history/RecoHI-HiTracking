#include "RecoHI/HiTracking/interface/HIPixelTrackFilter.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackBase.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

using namespace std;

/*****************************************************************************/
HIPixelTrackFilter::HIPixelTrackFilter (const edm::ParameterSet& ps, const edm::EventSetup& es) :
ClusterShapeTrackFilter(ps,es),
theTIPMax( ps.getParameter<double>("tipMax") ),
theNSigmaTipMaxTolerance( ps.getParameter<double>("nSigmaTipMaxTolerance")),
//theLIPMax( ps.getParameter<double>("lipMax") ),
//theNSigmaLipMaxTolerance( ps.getParameter<double>("nSigmaLipMaxTolerance")),
theChi2Max( ps.getParameter<double>("chi2") )
//theVertexCollection( ps.getParameter<string>("VertexCollection")),
{ 
}

/*****************************************************************************/
HIPixelTrackFilter::~HIPixelTrackFilter()
{ }

/*****************************************************************************/
bool HIPixelTrackFilter::operator() (const reco::Track* track,const PixelTrackFilter::Hits & recHits) const
{
	
	
	// Get reco vertex 
	/*
	 edm::Handle<reco::VertexCollection> vc;
	 ev.getByLabel(theVertexCollection, vc);
	 const reco::VertexCollection * vertices = vc.product();
	
	 if(vertices->size()>0) {
	   theVertex=vertices->begin();
	 }
	*/

	if (!track) return false; 
	if (track->chi2() > theChi2Max) return false; 
	if ( (fabs(track->d0())-theTIPMax)/track->d0Error() > theNSigmaTipMaxTolerance) return false; 

	//if (fabs(track->d0(theVertex->position())) > theTIPMax) return false;
	//if (fabs(track->d0(theVertex->position())) / track->d0Error() > theNSigmaTipMaxTolerance) return false;
	//if (fabs(track->dz(theVertex->position())) > theLIPMax) return false;
	//if (fabs(track->dz(theVertex->position())) / track->dzError() > theNSigmaLipMaxTolerance) return false;
			
	bool ok = ClusterShapeTrackFilter::operator() (track,recHits);
	
	return ok;
}

