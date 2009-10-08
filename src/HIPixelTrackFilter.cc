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
theChi2Max( ps.getParameter<double>("chi2") ),
useClusterShape( ps.getParameter<bool>("useClusterShape") )
{ 
}

/*****************************************************************************/
HIPixelTrackFilter::~HIPixelTrackFilter()
{ }

/*****************************************************************************/
bool HIPixelTrackFilter::operator() (const reco::Track* track,const PixelTrackFilter::Hits & recHits) const
{

	if (!track) return false; 
	if (track->chi2() > theChi2Max) return false; 

	double d0=0.0, d0sigma=0.0;
	d0 = -1.*track->dxy(/*vtx*/);
	d0sigma = track->d0Error();
	
	if (theTIPMax>0 && fabs(d0)>theTIPMax) return false;
	if (theNSigmaTipMaxTolerance>0 && (fabs(d0)/d0sigma)>theNSigmaTipMaxTolerance) return false;
	
	bool ok = true;
	if(useClusterShape) ok = ClusterShapeTrackFilter::operator() (track,recHits);
	
	return ok;
}

