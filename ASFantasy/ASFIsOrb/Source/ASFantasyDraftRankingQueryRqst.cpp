/* ASFantasyDraftRankingQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CBldComm.h"

#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDraftRankingQueryRqst.h"

namespace asfantasy
{

/******************************************************************************/

class DraftRankingQueryResp : public TStreamable
{
private:
	TGameLevel fGameLevel;
	DraftRankingPlayerVector fPlayerVector;

public:
	DraftRankingQueryResp(TGameLevel gameLevel,
		DraftRankingPlayerVector& playerVector) : fGameLevel(gameLevel),
		fPlayerVector(playerVector) {}
	
	virtual const char* className() const { return("DraftRankingQueryResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void DraftRankingQueryResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DraftRankingQueryResp::readFromFiler: not supported");
}

/******************************************************************************/

void DraftRankingQueryResp::writeToFiler(TDataFiler& filer)
{
	DraftRankingPlayerPtr playerPtr;
	int i,numItems = fPlayerVector.size();

	filer.writeByte((byte)fGameLevel);

	filer.writeShort((short)numItems);
	for(i = 0; i < numItems; i++)
	{
		playerPtr = fPlayerVector[i];
		playerPtr->writeToFiler(filer);
	}
}

/******************************************************************************/
/******************************************************************************/

void DraftRankingQueryRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
}

/******************************************************************************/

void DraftRankingQueryRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DraftRankingQueryRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* DraftRankingQueryRqst::fulfillRequest()
{
	auto_ptr<DraftRankingQueryResp> pResponse;
	DraftRankingPlayerVector playerVector;
	
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	fullPlayerVector(particPtr,playerVector);
	
	// update LastTransDateTime
	particPtr->setLastTransDateTime(TDateTime::CurrentDateTime());
	particPtr->update();

	pResponse.reset(new DraftRankingQueryResp(particPtr->getGameLevel(),playerVector));
	return(pResponse.release());
}

/******************************************************************************/

void DraftRankingQueryRqst::fullPlayerVector(TParticPtr& particPtr,
	DraftRankingPlayerVector& playerVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TDraftRankingPtr draftRankingPtr =
		TDraftRanking::createGet(particPtr->getTeamID(),cam_MustExist);
	const TPlayerIDVector& playerIDVector = draftRankingPtr->playerIDVector();
	TProfPlayerPtr profPlayerPtr;
	DraftRankingPlayerPtr draftRankingPlayerPtr;
	TPlayerID playerID;
	TPlayerIDVector::const_iterator iter;
	
	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		playerID = *iter;
		profPlayerPtr = store.getProfPlayer(playerID);

		draftRankingPlayerPtr = DraftRankingPlayer::createFromProfPlayer(
			profPlayerPtr);
		playerVector.push_back(draftRankingPlayerPtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
