/* ASFantasyTradeProposeQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyMiscRqst.h"
#include "ASFantasyTradeProposeQueryRqst.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProposeQueryResp : public TStreamable
{
private:
	TGameLevel fGameLevel;

	TTradeID fTradeID;
	bool fEnableChanges;

	TTeamID fTeamID;
	TTeamID fProposeToTeamID;
	TPlayerIDVector fGetPlayerIDVector;
	TPlayerIDVector fGivePlayerIDVector;
	TPlayerIDVector fReleasePlayerIDVector;

	TeamInfoNameVector fTeamNameVector;
	PlayerInfoVector fMyPlayerInfoVector;
	PlayerInfoVector fTheirPlayerInfoVector;

public:
	TradeProposeQueryResp(TGameLevel gameLevel,TTradeID tradeID,
		bool enableChanges,TTeamID teamID,TTeamID proposeToTeamID,
		TPlayerIDVector& getPlayerIDVector,TPlayerIDVector& givePlayerIDVector,
		TPlayerIDVector& releasePlayerIDVector,TeamInfoNameVector& teamNameVector,
		PlayerInfoVector& myPlayerInfoVector,PlayerInfoVector& theirPlayerInfoVector);

	virtual const char* className() const { return("TradeProposeQueryResp"); }
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

TradeProposeQueryResp::TradeProposeQueryResp(TGameLevel gameLevel,
	TTradeID tradeID,bool enableChanges,TTeamID teamID,TTeamID proposeToTeamID,
	TPlayerIDVector& getPlayerIDVector,TPlayerIDVector& givePlayerIDVector,
	TPlayerIDVector& releasePlayerIDVector,TeamInfoNameVector& teamNameVector,
	PlayerInfoVector& myPlayerInfoVector,PlayerInfoVector& theirPlayerInfoVector)
{
	fGameLevel = gameLevel;

	fTradeID = tradeID,
	fEnableChanges = enableChanges;

	fTeamID = teamID;
	fProposeToTeamID = proposeToTeamID;
	fGetPlayerIDVector = getPlayerIDVector;
	fGivePlayerIDVector = givePlayerIDVector;
	fReleasePlayerIDVector = releasePlayerIDVector;

	fTeamNameVector = teamNameVector;
	fMyPlayerInfoVector = myPlayerInfoVector;
	fTheirPlayerInfoVector = theirPlayerInfoVector;
}

/******************************************************************************/

void TradeProposeQueryResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProposeQueryResp::readFromFiler: not supported");
}

/******************************************************************************/

void TradeProposeQueryResp::writeToFiler(TDataFiler& filer)
{
	filer.writeByte((byte)fGameLevel);

	filer.writeLong(fTradeID.getID());
	filer.writeBoolean(fEnableChanges);

	filer.writeLong(fTeamID.getID());
	filer.writeLong(fProposeToTeamID.getID());
	fGetPlayerIDVector.writeToFiler(filer);
	fGivePlayerIDVector.writeToFiler(filer);
	fReleasePlayerIDVector.writeToFiler(filer);

	fTeamNameVector.writeToFiler(filer);
	fMyPlayerInfoVector.writeToFiler(filer);
	fTheirPlayerInfoVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

void TradeProposeQueryRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fTradeID = filer.readLong();
}

/******************************************************************************/

void TradeProposeQueryRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProposeQueryRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* TradeProposeQueryRqst::fulfillRequest()
{
	auto_ptr<TradeProposeQueryResp> pResponse;
	TTradeID tradeID;
	bool enableChanges;
	TTeamID teamID;
	TTeamID proposeToTeamID;
	TPlayerIDVector getPlayerIDVector;
	TPlayerIDVector givePlayerIDVector;
	TPlayerIDVector releasePlayerIDVector;

	TeamInfoNameVector teamNameVector;
	PlayerInfoVector myPlayerInfoVector;
	PlayerInfoVector theirPlayerInfoVector;
	
	TParticPtr particPtr;
	TTradePtr tradePtr;
	TTeamPtr teamPtr;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	enableChanges = false;

	if(fTradeID.isUndefined())
	{
		TTradeVector tradeVector;

		LoadOpenTradesByTeamID(particPtr->getTeamID(),tradeVector);
		if(tradeVector.size() > 0)
		{
			tradePtr = *tradeVector.begin();
			fTradeID = tradePtr->getTradeID();

			TOOLDEBUG( if(tradeVector.size() > 1)
				tErrorMsg("TradeProposeQueryRqst::fulfillRequest: tradeVector.size() > 1"); );
		}
	}
	else
		tradePtr = TTrade::createGet(fTradeID,cam_MustExist);

	if(!tradePtr.isNull())
	{
		if((tradePtr->getStatus() != trs_Proposed) &&
				(tradePtr->getStatus() != trs_Accepted))
			throw ASIException("TradeProposeQueryRqst::fulfillRequest: bad status");

		teamID = tradePtr->getTeamID();
		proposeToTeamID = tradePtr->getProposeToTeamID();

		FillPlayerInfoExtVector(proposeToTeamID,theirPlayerInfoVector);

		getPlayerIDVector = tradePtr->getPlayerIDVector();
		givePlayerIDVector = tradePtr->givePlayerIDVector();

		if(particPtr->getTeamID() == tradePtr->getTeamID())
			releasePlayerIDVector = tradePtr->proposeRelPlayerIDVector();
		else if(particPtr->getTeamID() == tradePtr->getProposeToTeamID())
			releasePlayerIDVector = tradePtr->acceptRelPlayerIDVector();

		if(tradePtr->isTeamInvolvedInTrade(particPtr->getTeamID()))
		{
			// Changes allowed if status is proposed.
			//	Changes include: initiator can clear, receiver can accept/decline.
			if(tradePtr->getStatus() == trs_Proposed)
				enableChanges = true;
		}
		else
		{
			// Protests enabled if status is accpeted.
			if(tradePtr->getStatus() == trs_Accepted)
			{
				// Verify team has not already protested trade.
				if(find(tradePtr->protestTeamIDVector().begin(),
					tradePtr->protestTeamIDVector().end(),particPtr->getTeamID())
					== tradePtr->protestTeamIDVector().end())
				{
					teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);

					// Verify team has protests remaining
					if(teamPtr->getNumTradeProtests() < MaxTradeProtestsAllowed)
						enableChanges = true;
				}
			}
		}

		tradeID = tradePtr->getTradeID();
	}
	else
	{
		tradeID.clear();
		teamID = particPtr->getTeamID();
	}

	teamPtr = TTeam::createGet(teamID,cam_MustExist);

	teamNameVector.fillByLeagueID(teamPtr->getLeagueID());
//BOB	teamNameVector.removeByID(teamPtr->getTeamID());
	
	FillPlayerInfoExtVector(teamPtr->getTeamID(),myPlayerInfoVector);


	pResponse.reset(new TradeProposeQueryResp(particPtr->getGameLevel(),
		tradeID,enableChanges,teamID,proposeToTeamID,getPlayerIDVector,
		givePlayerIDVector,releasePlayerIDVector,teamNameVector,
		myPlayerInfoVector,theirPlayerInfoVector));
	return (pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
