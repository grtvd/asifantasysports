/* ASFantasyDraftRankingUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CBldComm.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDraftRankingUpdateRqst.h"

namespace asfantasy
{

/******************************************************************************/

class DraftRankingUpdateResp : public TStreamable
{
public:
	virtual const char* className() const { return("DraftRankingUpdateResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void DraftRankingUpdateResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DraftRankingUpdateResp::readFromFiler: not supported");
}

/******************************************************************************/

void DraftRankingUpdateResp::writeToFiler(TDataFiler& filer)
{
}

/******************************************************************************/
/******************************************************************************/

void DraftRankingUpdateRqst::readFromFiler(TDataFiler& filer)
{
	int i,numPlayers;

	fEncodedParticID = filer.readString().c_str();
	
	numPlayers = filer.readShort();
	for(i = 0; i < numPlayers; i++)
		fPlayerIDVector.push_back(TPlayerID(filer.readLong()));
}

/******************************************************************************/

void DraftRankingUpdateRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DraftRankingUpdateRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* DraftRankingUpdateRqst::fulfillRequest()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	auto_ptr<DraftRankingUpdateResp> pResponse;
	
	TParticPtr particPtr;
	TDraftRankingPtr draftRankingPtr;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	draftRankingPtr = TDraftRanking::createGet(particPtr->getTeamID(),cam_MustExist);
	
	if(cast2int(fPlayerIDVector.size()) > MaxDraftRankingPlayers())
		throw ASIException("DraftRankingUpdateRqst::fulfillRequest: too many TPlayerID");

	if(fPlayerIDVector.doesContainDups())
		throw ASIException("DraftRankingUpdateRqst::fulfillRequest: duplicate TPlayerID");
		
	if(!store.isPlayerIDVectorValidForProfPlayers(fPlayerIDVector,false))
		throw ASIException("DraftRankingUpdateRqst::fulfillRequest: invalid TPlayerID");
	
	draftRankingPtr->playerIDVector() = fPlayerIDVector;
	draftRankingPtr->update();

	// update LastTransDateTime
	particPtr->setLastTransDateTime(TDateTime::CurrentDateTime());
	particPtr->update();
	
	pResponse.reset(new DraftRankingUpdateResp());
	return(pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
