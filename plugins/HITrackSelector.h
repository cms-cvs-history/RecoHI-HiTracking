#ifndef HITrackSelection_h
#define HITrackSelection_h

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "TMath.h"

#include <algorithm>
#include <iostream>
using namespace std;
using namespace edm;

/**
 Selector to select final tracks that pass certain kinematic cuts based on best vertex
 **/

class HITrackSelector
	{
		
	public:
		// input collection type
		typedef reco::TrackCollection collection;
		
		// output collection type
		typedef vector<const reco::Track *> container;
		
		// iterator over result collection type.
		typedef container::const_iterator const_iterator;
		
		// constructor from parameter set configurability
		HITrackSelector(const edm::ParameterSet & iConfig) : 
		  vertexCollection_(iConfig.getParameter<string>("VertexCollection")),
		  ptMin_(iConfig.getParameter<double>("ptMin")), 	
		  nSigmaZ_(iConfig.getParameter<double>("nSigmaZ")),
		  minZCut_(iConfig.getParameter<double>("minZCut")),
		  maxD0Significance_(iConfig.getParameter<double>("maxD0Significance")),
		  minValidHits_(iConfig.getParameter<double>("minValidHits")),
		  minChi2Prob_(iConfig.getParameter<double>("minChi2Prob"))
		{};
		
		// select object from a collection and possibly event content
		void select( edm::Handle<reco::TrackCollection>& TCH, const edm::Event & iEvent, const edm::EventSetup & iSetup)
		{
			selected_.clear();
			
			const collection & c = *(TCH.product());
			
			// Get best reco vertex 
			edm::Handle<reco::VertexCollection> vc;
			iEvent.getByLabel(vertexCollection_, vc);
			const reco::VertexCollection * vertices = vc.product();

			math::XYZPoint vtxPoint(0.0,0.0,0.0);
			double vzErr =0.0;

			if(vertices->size()>0) {
				vtxPoint=vertices->begin()->position();
				vzErr=vertices->begin()->zError();
				LogInfo("HeavyIonVertexing") << "Select tracks compatible with best vertex"
							     << "\n   vz = " << vtxPoint.Z()  
							     << "\n   vz sigma = " << vzErr;
			} else {
				LogError("HeavyIonVertexing") << "No vertex found in collection '" << vertexCollection_ << "'";
			}
			
			
			// Do selection
			int nSelected=0;
			int nRejected=0;
			double d0=0.0; 
			double d0sigma=0.0;
			double dzsigma=0.0;
			for (reco::TrackCollection::const_iterator trk = c.begin(); trk != c.end(); ++ trk)
			{
				
			  d0 = -1.*trk->dxy(vtxPoint);
			  d0sigma = sqrt(trk->d0Error()*trk->d0Error());
			  dzsigma = sqrt(trk->dzError()*trk->dzError()+vzErr*vzErr);
			  if ( trk->pt() > ptMin_ && // keep only tracks above ptMin
			       fabs(d0/d0sigma) < maxD0Significance_ && // keep only tracks with D0 significance less than cut
			       fabs(trk->dz(vtxPoint)) <  max(dzsigma*nSigmaZ_,minZCut_) && // keep all tracks within minZCut or within nSigmaZ sigmas of vertex
			       trk->numberOfValidHits() >= minValidHits_  && // keep tracks with more than minValidHits_
			       TMath::Prob(trk->chi2(),(int)trk->ndof()) > minChi2Prob_ // keep tracks with chi2 probability above minChi2Prob_
			       ) 
			    {
			      LogTrace("HeavyIonVertexing") << "SELECTED: dz=" << trk->dz(vtxPoint) << "\t d0/d0err=" << d0/d0sigma  << "\t pt=" << trk->pt();
			      nSelected++;
			      selected_.push_back( & * trk );
			    } else {
			      LogTrace("HeavyIonVertexing") << "\t REJECTED: dz=" << trk->dz(vtxPoint) << "\t d0/d0err=" << d0/d0sigma << "\t pt=" << trk->pt();
			      nRejected++;
			    }
			  
			}
			
			LogInfo("HeavyIonVertexing") << "selected " << nSelected << " tracks out of " << nRejected+nSelected << endl;
			
		}
		
		// iterators over selected objects: collection begin
		const_iterator begin() const { return selected_.begin(); }
		
		// iterators over selected objects: collection end
		const_iterator end() const { return selected_.end(); }
		
		// true if no object has been selected
		size_t size() const { return selected_.size(); }
		
		
private:
		container selected_;		
		string vertexCollection_; 
		double ptMin_; 
		double nSigmaZ_;
		double minZCut_; 
		double maxD0Significance_;
		double minValidHits_;
		double minChi2Prob_;
		
	};


#endif
