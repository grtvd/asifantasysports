/* ASFantasyFreeAgentQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectStore.h"
#include "ASFantasyDB.h"
#include "ASFantasyMiscRqst.h"
#include "ASFantasyFreeAgentQueryRqst.h"

namespace asfantasy
{

/******************************************************************************/

class FreeAgentQueryResp : public TStreamable
{
private:
	TGameLevel fGameLevel;
	PlayerInfoPtr fClaimPlayerInfoPtr;
	TPlayerID fReleasePlayerID;
	PlayerInfoVector fRosterPlayerVector;

public:
	FreeAgentQueryResp(TGameLevel gameLevel,PlayerInfoPtr claimPlayerInfoPtr,
		TPlayerID releasePlayerID,PlayerInfoVector rosterPlayerVector);
	
	virtual const char* className() const { return("FreeAgentQueryResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

FreeAgentQueryResp::FreeAgentQueryResp(TGameLevel gameLevel,
	PlayerInfoPtr claimPlayerInfoPtr,TPlayerID releasePlayerID,
	PlayerInfoVector rosterPlayerVector)
{
	fGameLevel = gameLevel;
	fClaimPlayerInfoPtr = claimPlayerInfoPtr;
	fReleasePlayerID = releasePlayerID;
	fRosterPlayerVector = rosterPlayerVector;
}

/******************************************************************************/

void FreeAgentQueryResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("FreeAgentQueryResp::readFromFiler: not supported");
}

/******************************************************************************/

void FreeAgentQueryResp::writeToFiler(TDataFiler& filer)
{
	filer.writeByte((byte)fGameLevel);
	
	// write player information
	fClaimPlayerInfoPtr->writeToFiler(filer);
	filer.writeLong(fReleasePlayerID.getID());

	// write team information
	fRosterPlayerVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

void FreeAgentQueryRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
}

/******************************************************************************/

void FreeAgentQueryRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("FreeAgentQueryRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* FreeAgentQueryRqst::fulfillRequest()
{
	auto_ptr<FreeAgentQueryResp> pResponse;
	PlayerInfoPtr claimPlayerInfoPtr;
	TPlayerID releasePlayerID;
	PlayerInfoVector rosterPlayerVector;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(), cam_MustExist);
	
	getClaimReleasePlayers(teamPtr,claimPlayerInfoPtr,releasePlayerID);
	fillRosterPlayerVector(teamPtr,rosterPlayerVector);

	pResponse.reset(new FreeAgentQueryResp(particPtr->getGameLevel(),
		claimPlayerInfoPtr,releasePlayerID,rosterPlayerVector));
	return (pResponse.release());
}

/******************************************************************************/

void FreeAgentQueryRqst::getClaimReleasePlayers(TTeamPtr teamPtr,
	PlayerInfoPtr& claimPlayerInfoPtr,TPlayerID& releasePlayerID)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TProfPlayerPtr profPlayerPtr;
	TFreeAgentClaimPtr freeAgentClaimPtr = GetPendingFreeAgentClaimByTeamID(
		teamPtr->getTeamID());

	if(!freeAgentClaimPtr.isNull())
	{
		profPlayerPtr = store.getProfPlayer(freeAgentClaimPtr->getClaimPlayerID());
		claimPlayerInfoPtr = PlayerInfo::createFromProfPlayer(profPlayerPtr);

		releasePlayerID = freeAgentClaimPtr->getReleasePlayerID();
	}
	else
	{
		claimPlayerInfoPtr = PlayerInfo::createFromProfPlayer(NULL);
		releasePlayerID.clear();
	}
}

/******************************************************************************/

void FreeAgentQueryRqst::fillRosterPlayerVector(TTeamPtr teamPtr,
	PlayerInfoVector& rosterPlayerVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerVector playerVector;
	TProfPlayerPtr profPlayerPtr;
	PlayerInfoPtr playerInfoPtr;
	TPlayerVector::const_iterator iter;

	LoadPlayerVectorByTeamID( teamPtr->getTeamID(), playerVector );
	for(iter = playerVector.begin(); iter != playerVector.end(); iter++)
	{
		profPlayerPtr = store.getProfPlayer( (*iter)->getPlayerID() );
		playerInfoPtr = PlayerInfo::createFromProfPlayer(profPlayerPtr);
		rosterPlayerVector.push_back(playerInfoPtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
