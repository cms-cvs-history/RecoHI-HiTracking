#ifndef _HIPixelTrackFilter_h_
#define _HIPixelTrackFilter_h_

#include "RecoPixelVertexing/PixelLowPtUtilities/interface/ClusterShapeTrackFilter.h"

namespace edm { class ParameterSet; class EventSetup; }
namespace reco { class Vertex; }

class HIPixelTrackFilter : public ClusterShapeTrackFilter {
public:
	HIPixelTrackFilter(const edm::ParameterSet& ps, const edm::EventSetup& es);
	virtual ~HIPixelTrackFilter();
	virtual bool operator() (const reco::Track*, const PixelTrackFilter::Hits & hits) const;
private:
	double theTIPMax, theNSigmaTipMaxTolerance;
	//double theLIPMax, theNSigmaLipMaxTolerance;
	double theChi2Max;	
	//std::string theVertexCollection; 	
	//reco::Vertex theVertex;

};

#endif
