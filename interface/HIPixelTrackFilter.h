#ifndef _HIPixelTrackFilter_h_
#define _HIPixelTrackFilter_h_

#include "RecoPixelVertexing/PixelLowPtUtilities/interface/ClusterShapeTrackFilter.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

namespace edm { class ParameterSet; class EventSetup; class Event;}

class HIPixelTrackFilter : public ClusterShapeTrackFilter {
public:
	HIPixelTrackFilter(const edm::ParameterSet& ps, const edm::EventSetup& es);
	virtual ~HIPixelTrackFilter();
	virtual bool operator() (const reco::Track*, const PixelTrackFilter::Hits & hits, const edm::Event& ev) const;
	void getEventInfo(const edm::Event& ev) const;

private:
	double theTIPMax, theNSigmaTipMaxTolerance;
	double theLIPMax, theNSigmaLipMaxTolerance;
	double theChi2Max;
	bool useClusterShape;
	std::string theVertexCollection; 

	// members of the filter that may be changed for new events
	mutable reco::VertexCollection *theVertices;
	mutable unsigned int theEventNo;
	mutable unsigned int theRunNo;

};

#endif
