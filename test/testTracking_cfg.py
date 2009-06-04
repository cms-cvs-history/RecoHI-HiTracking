import FWCore.ParameterSet.Config as cms
import os 

process = cms.Process("RECO")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Configuration.StandardSequences.Geometry_cff")

#global tags for conditions data: https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideFrontierConditions#22X_Releases_starting_from_CMSSW
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = 'IDEAL_V12::All' 

##################################################################################

indir = "/pnfs/cmsaf.mit.edu/hibat/cms/users/yenjie/2_2_9/QuenchedEcalTrig70"
infileroot = "QuenchedEcalTrig4TeV"
firstfile = 2
nfiles = 1
maxevents = 1

##################################################################################
# Some Services

process.load("FWCore.MessageService.MessageLogger_cfi")
			   
#process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
#                                        ignoreTotal=cms.untracked.int32(0),
#                                        oncePerEventMode = cms.untracked.bool(False)
#                                        )

#process.Timing = cms.Service("Timing")

##################################################################################
# Input Source
process.source = cms.Source('PoolSource',
	fileNames = cms.untracked.vstring(
          #'file:///home/edwenger/HYDJET_B0_4TeV_seq17.root'
		  ) 
)
							
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(maxevents)
)

# get a list of files from a specified directory and add a specified number to the list of fileNames
mylist = os.listdir(indir)
for i in range(firstfile,firstfile+nfiles):
	process.source.fileNames.append('dcache:%s/%s' % (indir,mylist[i]))

##################################################################################
#Reconstruction			
process.load("RecoHI.Configuration.Reconstruction_HI_cff")          # full heavy ion reconstruction

##############################################################################
# Output EDM File
process.load("CmsHi.Utilities.HiAnalysisEventContent_cff") #load keep/drop output commands
process.output = cms.OutputModule("PoolOutputModule",
                                  process.HIRecoObjects,
                                  compressionLevel = cms.untracked.int32(2),
                                  commitInterval = cms.untracked.uint32(1),
                                  fileName = cms.untracked.string('outputTest_RECO.root')
                                  )

##################################################################################
# Paths
process.trkreco = cms.Sequence(process.offlineBeamSpot*process.trackerlocalreco*process.heavyIonTracking)
process.reco = cms.Sequence(process.reconstruct_PbPb)

process.p = cms.Path(process.trkreco)
process.save = cms.EndPath(process.output)