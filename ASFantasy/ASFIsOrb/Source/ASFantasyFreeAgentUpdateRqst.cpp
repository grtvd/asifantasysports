/* ASFantasyFreeAgentUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyFreeAgentUpdateRqst.h"

namespace asfantasy
{

/******************************************************************************/

class FreeAgentUpdateResp : public TStreamable
{
public:
	virtual const char* className() const { return("FreeAgentUpdateResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void FreeAgentUpdateResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("FreeAgentUpdateResp::readFromFiler: not supported");
}

/******************************************************************************/

void FreeAgentUpdateResp::writeToFiler(TDataFiler& filer)
{
}

/******************************************************************************/
/******************************************************************************/

void FreeAgentUpdateRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fClaimPlayerID = filer.readLong();
	fReleasePlayerID = filer.readLong();
}

/******************************************************************************/

void FreeAgentUpdateRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("FreeAgentUpdateRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* FreeAgentUpdateRqst::fulfillRequest()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	auto_ptr<FreeAgentUpdateResp> pResponse;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TFreeAgentClaimPtr freeAgentClaimPtr;
	bool createNew;
	TPlayerPtr playerPtr;
	TPlayerIDVector playerIDVector;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(), cam_MustExist);
	freeAgentClaimPtr = GetPendingFreeAgentClaimByTeamID(teamPtr->getTeamID());

	if(!fClaimPlayerID.isUndefined())
	{
		// verify player IDs
		if(store.getProfPlayer(fClaimPlayerID,ObjectStore::gim_MayNotExist).isNull())
			throw ASIException("FreeAgentUpdateRqst::fulfillRequest: invalid TPlayerID for claim");
		
		// release player must always be defined
		if(store.getProfPlayer(fReleasePlayerID,ObjectStore::gim_MayNotExist).isNull())
			throw ASIException("FreeAgentUpdateRqst::fulfillRequest: invalid TPlayerID for release");
			 
		// verify that claim player is free agent
		playerPtr = TPlayer::createGet(TLeaguePlayerID(teamPtr->getLeagueID(),
			fClaimPlayerID),cam_MustExist);
		if(!playerPtr->isFreeAgent())
			throw ASIException("FreeAgentUpdateRqst::fulfillRequest: claim player is not free agent");

		// verify that release player is on team
		playerPtr = TPlayer::createGet(TLeaguePlayerID(teamPtr->getLeagueID(),
			fReleasePlayerID),cam_MustExist);
		if(playerPtr->isFreeAgent() || (playerPtr->getTeamID() != teamPtr->getTeamID()))
			throw ASIException("FreeAgentUpdateRqst::fulfillRequest: release player is not on team");

		// clear existing FA claim
		createNew = true;
		if(!freeAgentClaimPtr.isNull())
		{
			// Did user submit identical claim?
			if((freeAgentClaimPtr->getClaimPlayerID() == fClaimPlayerID) &&
					(freeAgentClaimPtr->getReleasePlayerID() == fReleasePlayerID))
			{
				createNew = false;
				CommErrMsg(cel_Warning,"FreeAgentUpdateRqst::fulfillRequest: skipping duplicate update of FA claim(%s)",
					freeAgentClaimPtr->getFreeAgentClaimID().c_str());
			}
			else
			{
				freeAgentClaimPtr->setStatus(facs_Cleared);
				freeAgentClaimPtr->update();
			}
		}

		if(createNew)
		{
			// add new FA claim
			freeAgentClaimPtr = TFreeAgentClaim::newInstance();
			freeAgentClaimPtr->setTeamID(teamPtr->getTeamID());
			freeAgentClaimPtr->setClaimDateTime(TDateTime::CurrentDateTime());
			freeAgentClaimPtr->setStatus(facs_Pending);

			freeAgentClaimPtr->setClaimPlayerID(fClaimPlayerID);
			freeAgentClaimPtr->setReleasePlayerID(fReleasePlayerID);

			freeAgentClaimPtr->setProcessedStatus(fcps_NotProcessed);

			freeAgentClaimPtr->update();
		}
	}
	else
	{
		// clear existing FA claim
		if(!freeAgentClaimPtr.isNull())
		{
			freeAgentClaimPtr->setStatus(facs_Cleared);
			freeAgentClaimPtr->update();
		}
	}

	pResponse.reset(new FreeAgentUpdateResp());
	return (pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
