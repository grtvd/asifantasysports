/* ASFantasyOrbFulfiller.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommType.h"
#include "CommDB.h"

#include "ASFantasyOrbFulfiller.h"

#include "ASFantasyLeagueSignupRqst.h"
#include "ASFantasySignupLeagueListRqst.h"

#include "ASFantasyDraftRankingQueryRqst.h"
#include "ASFantasyDraftRankingUpdateRqst.h"
#include "ASFantasyDraftResultRqst.h"
#include "ASFantasyScheduleRqst.h"
#include "ASFantasyGameResultsRqst.h"
#include "ASFantasyStandingsRqst.h"
#include "ASFantasyFreeAgentQueryRqst.h"
#include "ASFantasyFreeAgentUpdateRqst.h"

#include "ASFantasyTradeProposeQueryRqst.h"
#include "ASFantasyTradeProposeTeamRqst.h"
#include "ASFantasyTradeProposeUpdateRqst.h"
#include "ASFantasyTradeReceiveUpdateRqst.h"
#include "ASFantasyTradeProtestUpdateRqst.h"

#include "ASFantasyPlayoffRqst.h"

namespace asfantasy
{

/******************************************************************************/

TStreamable* ASFantasyOrbFulfiller::newInstance(const char* classNameStr)
{
	CStrVar className(classNameStr);
	
	if (className == "LeagueSignupRqst")
		return new LeagueSignupRqst();

	if (className == "SignupLeagueListRqst")
		return new SignupLeagueListRqst();
		
	if (className == "DraftRankingQueryRqst")
		return new DraftRankingQueryRqst();
		
	if (className == "DraftRankingUpdateRqst")
		return new DraftRankingUpdateRqst();

	if (className == "DraftResultRqst")
		return new DraftResultRqst();
		
	if (className == "ScheduleRqst")
		return new ScheduleRqst();

	if (className == "GameResultsRqst")
		return new GameResultsRqst();
		
	if (className == "StandingsRqst")
		return new StandingsRqst();
		
	if (className == "FreeAgentQueryRqst")
		return new FreeAgentQueryRqst();
		
	if (className == "FreeAgentUpdateRqst")
		return new FreeAgentUpdateRqst();
		
	if (className == "TradeProposeQueryRqst")
		return new TradeProposeQueryRqst();

	if (className == "TradeProposeTeamRqst")
		return new TradeProposeTeamRqst();

	if (className == "TradeProposeUpdateRqst")
		return new TradeProposeUpdateRqst();

	if (className == "TradeReceiveUpdateRqst")
		return new TradeReceiveUpdateRqst();

	if (className == "TradeProtestUpdateRqst")
		return new TradeProtestUpdateRqst();

	if (className == "PlayoffRqst")
		return new PlayoffRqst();
		
	throw ASIException("ASFantasyOrbFulfiller::newInstance: unknown class(%s)",
		classNameStr);
}

/******************************************************************************/

void ASFantasyOrbFulfiller::dbStartTransaction()
{
	try
	{
		GetOpenDatabase(MemberDatabaseName())->StartTransaction();
		GetOpenDatabase(MemberMiscDatabaseName())->StartTransaction();
		GetOpenDatabase(PrimaryDatabaseName())->StartTransaction();
	}
	catch(const Exception& e)
	{
		dbRollbackTransaction();
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		dbRollbackTransaction();
		throw;
	}
}

/******************************************************************************/

void ASFantasyOrbFulfiller::dbCommitTransaction()
{
	GetOpenDatabase(MemberDatabaseName())->Commit();
	GetOpenDatabase(MemberMiscDatabaseName())->Commit();
	GetOpenDatabase(PrimaryDatabaseName())->Commit();
}

/******************************************************************************/

void ASFantasyOrbFulfiller::dbRollbackTransaction()
{
	try { GetOpenDatabase(PrimaryDatabaseName())->Rollback(); } catch(...) {}
	try { GetOpenDatabase(MemberDatabaseName())->Rollback(); } catch(...) {}
	try { GetOpenDatabase(MemberMiscDatabaseName())->Rollback(); } catch(...) {}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
