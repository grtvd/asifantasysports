/* ASFantasyTradeProtestUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyTradeProtestUpdateRqst.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProtestUpdateResp : public TStreamable
{
public:
	TradeProtestUpdateResp() {}

	virtual const char* className() const { return("TradeProtestUpdateResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void TradeProtestUpdateResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProtestUpdateResp::readFromFiler: not supported");
}

/******************************************************************************/

void TradeProtestUpdateResp::writeToFiler(TDataFiler& filer)
{
	// nothing to write
}

/******************************************************************************/
/******************************************************************************/

void TradeProtestUpdateRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fTradeID = filer.readLong();
}

/******************************************************************************/

void TradeProtestUpdateRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProtestUpdateRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* TradeProtestUpdateRqst::fulfillRequest()
{
	auto_ptr<TradeProtestUpdateResp> pResponse;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TLeaguePtr leaguePtr;
	TTradePtr tradePtr;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);

	teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);
	leaguePtr = TLeague::createGet(teamPtr->getLeagueID(),cam_MustExist);

	tradePtr = TTrade::createGet(fTradeID,cam_MustExist);

	// Sanity check, verify partic is in same league as trade.
	if(find(leaguePtr->overallStandings().begin(),
			leaguePtr->overallStandings().end(),tradePtr->getTeamID())
			== leaguePtr->overallStandings().end())
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: league mismatch");

	// Trade must be in Accepted state to be protested
	if(tradePtr->getStatus() != trs_Accepted)
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: status != trs_Accepted");

	// Verify team is not involved in trade.
	if(tradePtr->isTeamInvolvedInTrade(teamPtr->getTeamID()))
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: team is involved in trade");

	// Verity team has protests remaining
	if(teamPtr->getNumTradeProtests() >= MaxTradeProtestsAllowed)
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: num protests reached");

	// Verify team has not already protested trade.
	if(find(tradePtr->protestTeamIDVector().begin(),
			tradePtr->protestTeamIDVector().end(),teamPtr->getTeamID())
			!= tradePtr->protestTeamIDVector().end())
		throw ASIException("TradeReceiveUpdateRqst::fulfillRequest: team has already protested trade");

	// Update trade protests.
	tradePtr->protestTeamIDVector().push_back(teamPtr->getTeamID());
	tradePtr->update();

	// Update team's protests.
	teamPtr->incNumTradeProtests();
	teamPtr->update();
	
	pResponse.reset(new TradeProtestUpdateResp());
	return (pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
