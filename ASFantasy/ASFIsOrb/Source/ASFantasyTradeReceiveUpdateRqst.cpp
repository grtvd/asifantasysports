/* ASFantasyTradeReceiveUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyTradeReceiveUpdateRqst.h"

namespace asfantasy
{

/******************************************************************************/

class TradeReceiveUpdateResp : public TStreamable
{
public:
	TradeReceiveUpdateResp() {}

	virtual const char* className() const { return("TradeReceiveUpdateResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void TradeReceiveUpdateResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeReceiveUpdateResp::readFromFiler: not supported");
}

/******************************************************************************/

void TradeReceiveUpdateResp::writeToFiler(TDataFiler& filer)
{
	// nothing to write
}

/******************************************************************************/
/******************************************************************************/

void TradeReceiveUpdateRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fTradeID = filer.readLong();
	fAccept = filer.readBoolean();
	fReleasePlayerIDVector.readFromFiler(filer);
}

/******************************************************************************/

void TradeReceiveUpdateRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeReceiveUpdateRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* TradeReceiveUpdateRqst::fulfillRequest()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	auto_ptr<TradeReceiveUpdateResp> pResponse;
	TPlayerIDVector teamPlayerIDVector;
	TParticPtr particPtr;
	TTradePtr tradePtr;
	int newRosterSize;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);

	tradePtr = TTrade::createGet(fTradeID,cam_MustExist);

	// Verify requesting team is the proposed to team.
	if(tradePtr->getProposeToTeamID() != particPtr->getTeamID())
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: requesting team is not proposed to team");

	// Trade must be in Proposed stat to be accepted or declined.
	if(tradePtr->getStatus() != trs_Proposed)
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: status != trs_Proposed");

	if(fAccept)
	{
		// verifies no duplicates
		if(fReleasePlayerIDVector.doesContainDups(true))
			throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: duplicate TPlayerID");

		// verify player IDs
		if(!store.isPlayerIDVectorValidForProfPlayers(fReleasePlayerIDVector,true))
			throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: invalid TPlayerID");

		// verity players being released are not involved in trade
		if(tradePtr->getPlayerIDVector().containsAny(fReleasePlayerIDVector))
			throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: release players involved in trade");

		// verifies that players are on the specified team
		LoadPlayerIDVectorByTeamID( tradePtr->getProposeToTeamID(), teamPlayerIDVector );
		if(!teamPlayerIDVector.contains( fReleasePlayerIDVector, true ))
			throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: player not on specified team");

		// verify new roster size - fail if new size > normal or
		//	new size < normal but players are being released. Always use
		//	max roster size since roster size could change before trade
		//	is processed.
		newRosterSize = MaxPlayersPerTeam() /*teamPlayerIDVector.size()*/
			+ tradePtr->givePlayerIDVector().size()
			- tradePtr->getPlayerIDVector().size() - fReleasePlayerIDVector.size();
		if((newRosterSize > MaxPlayersPerTeam()) ||
				((newRosterSize < MaxPlayersPerTeam()) &&
				(fReleasePlayerIDVector.size() > 0)))
			throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: invalid new roster size");

		// save the trade info
		tradePtr->setAcceptedDate(TDateTime::CurrentDateTime());
		tradePtr->setStatus(trs_Accepted);

		tradePtr->acceptRelPlayerIDVector() = fReleasePlayerIDVector;
	}
	else
	{
		tradePtr->setStatus(trs_Declined);
	}

	tradePtr->update();
	
	pResponse.reset(new TradeReceiveUpdateResp());
	return (pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
