#include "FWCore/Framework/interface/MakerMacros.h"

#include "PhysicsTools/UtilAlgos/interface/ObjectSelector.h"
#include "RecoHI/HiTracking/plugins/HITrackSelector.h"

namespace reco
{
	namespace modules
	{
		
		// define your producer name
		typedef ObjectSelector<HITrackSelector> HITrackSelection;
		
		// declare the module as plugin
		DEFINE_FWK_MODULE( HITrackSelection );
	}
}
