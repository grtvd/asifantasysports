/* ASFantasyDB.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASMemberDB.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDB.h"

namespace asfantasy
{

/******************************************************************************/

static CStrVar BuildStatPeriodVectorStr(const TStatPeriodVector& statPeriodVector);

static void LoadLeagueVectorByWhereStr(const char* whereStr,
	TLeagueVector& leagueVector);

static void LoadProfPlayerVectorByWhereStr(const char* whereStr,
	TProfPlayerVector& profPlayerVector);

static void LoadOffGameStatVectorByWhereStr(const char* whereStr,
	TOffGameStatVector& offGameStatVector);
static void PurgeOffGameStatByWhereStr(const char* whereStr);

static void PurgeDefGameStatByWhereStr(const char* whereStr);
static void LoadDefGameStatVectorByWhereStr(const char* whereStr,
	TDefGameStatVector& defGameStatVector);

static void LoadDraftRankingVectorByWhereStr(const char* whereStr,
	TDraftRankingVector& draftRankingVector);

static void LoadScheduleDayVectorByWhereStr(const char* whereStr,
	TScheduleDayVector& scheduleDayVector);
static TScheduleDayPtr GetScheduleDayByWhereStr(const char* whereStr);

static void LoadGameResultVectorByWhereStr(const char* whereStr,
	TGameResultVector& gameResultVector);

static void LoadFreeAgentClaimVectorByWhereStr(const char* whereStr,
	TFreeAgentClaimVector& freeAgentClaimVector);

/******************************************************************************/
/******************************************************************************/

CStrVar BuildStatPeriodVectorStr(const TStatPeriodVector& statPeriodVector)
{
	CStrVar str;
	int i,numItems = statPeriodVector.size();

	str.copy("(StatPeriod in (");
	for(i = 0; i < numItems; ++i)
	{
		if(i > 0)
			str.concat(",");
		str.concatVarg("\"%s\"",statPeriodVector[i].c_str());
	}
	str.concat("))");

	return(str);
}

/******************************************************************************/

// This function updates the ProfPlayer table and NOT any ProfPlayers in
//	memory.  This function should not be called if the ProfPlayerShelf is
//	currently loaded.

void ClearLastWeeksPointsForAllProfPlayers()
{
	ExecQuery(PrimaryDatabaseName(),"update ProfPlayer set LastWeeksPoints = 0");
}

/******************************************************************************/

void LoadParticVectorByTeamVector(const TTeamVector& teamVector,
	TParticVector& particVector)
{
	TParticIDVector particIDVector;
	TTeamVector::const_iterator iter;

	for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
		particIDVector.push_back((*iter)->getParticID());

	LoadParticVectorByParticIDVector(particIDVector,particVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadLeagueVectorByWhereStr(const char* whereStr,TLeagueVector& leagueVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TLeaguePtr leaguePtr;

	// Find all Leagues
	try
	{
		leagueVector.erase(leagueVector.begin(),leagueVector.end());
		
		str.copy("select * from League");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str);
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			leaguePtr = TLeague::newInstance();
			leaguePtr->load(*pQuery);
			leagueVector.push_back(leaguePtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadLeagueVectorByOpenPublic(TLeagueVector& leagueVector)
{
	CStrVar str;

	str.copyVarg("((GamePhase = \"%s\") and (Reserved = 0))",
		TGamePhase(gmph_Enrollment).c_str());

	LoadLeagueVectorByWhereStr(str,leagueVector);
}

/******************************************************************************/

void LoadLeagueVectorByEnrollPrivatePartialName(const char* partialLeagueName,
	TLeagueVector& leagueVector)
{
	CStrVar str;
	TLeagueName partialName(partialLeagueName);

	str.copyVarg("(GamePhase = \"%s\") and (Reserved != 0)",
		TGamePhase(gmph_Enrollment).c_str());

	if(partialName.HasLen())
	{
		partialName.ToUpper();
		str.concatVarg(" and (upper(Name) starts with \"%s\")",
			partialName.c_str());
	}

	LoadLeagueVectorByWhereStr(str,leagueVector);
}

/******************************************************************************/

void LoadLeagueVectorByNotLastProcessedDate(TDateTime lastProcessedDate,
	TLeagueVector& leagueVector)
{
	CStrVar str;

	str.copyVarg("(LastProcessedDate <> \"%s\")",
		FormatDateOnlyStr(lastProcessedDate).c_str());

	LoadLeagueVectorByWhereStr(str,leagueVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadTeamVectorByLeagueID(TLeagueID leagueID,TTeamVector& teamVector)
{
	TQuery* pQuery = NULL;
	CStr511 str;
	TTeamPtr teamPtr;

	// Find all Teams for a particular League.
	try
	{
		teamVector.erase(teamVector.begin(),teamVector.end());
		
		str.CopyVarg("select * from Team where (LeagueID = \"%s\")",
			leagueID.c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			teamPtr = TTeam::newInstance();
			teamPtr->load(*pQuery);
			teamVector.push_back(teamPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/
/******************************************************************************/

void LoadProfPlayerVectorByWhereStr(const char* whereStr,
	TProfPlayerVector& profPlayerVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TProfPlayerPtr profPlayerPtr;

	// Find all ProfPlayers
	try
	{
		profPlayerVector.erase(profPlayerVector.begin(),profPlayerVector.end());
		
		str.copy("select * from ProfPlayer");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str);
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			profPlayerPtr = TProfPlayer::newInstance();
			profPlayerPtr->load(*pQuery);
			profPlayerVector.push_back(profPlayerPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadProfPlayerVectorByGameStatus(const TProfPlayerGameStatus gameStatus,
	TProfPlayerVector& profPlayerVector)
{
	CStrVar str;

	if(!gameStatus.isUndefined())
		str.copyVarg("GameStatus = \"%s\"",gameStatus.c_str());

	LoadProfPlayerVectorByWhereStr(str,profPlayerVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadPlayerVectorByTeamID( TTeamID teamID, TPlayerVector& playerVector )
{
	TQuery *	pQuery = NULL;
	CStr255		str;
	TPlayerPtr	playerPtr;

	// Find all Teams for a particular League.
	try
	{
		playerVector.erase(playerVector.begin(), playerVector.end());

		str.CopyVarg("select * from Player where (TeamID = \"%s\")",teamID.c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());

		pQuery->First();
		while(!pQuery->Eof)
		{
			playerPtr = TPlayer::newInstance();
			playerPtr->load(*pQuery);
			playerVector.push_back(playerPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadPlayerIDVectorByTeamID(TTeamID teamID, TPlayerIDVector& playerIDVector)
{
	TPlayerVector playerVector;

	LoadPlayerVectorByTeamID(teamID, playerVector);
	playerIDVector.fillFromPlayerVector(playerVector);
}

/******************************************************************************/

void LoadPlayerVectorByLeagueID(TLeagueID leagueID,short playerTypeFlag,
	TPlayerVector& playerVector)
{
	TQuery *	pQuery = NULL;
	CStr255		str;
	TPlayerPtr	playerPtr;

	// Find all Players for a particular League.
	try
	{
		playerVector.erase(playerVector.begin(), playerVector.end());

		str.CopyVarg("select * from Player where (LeagueID = \"%s\")",leagueID.c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());

		pQuery->First();
		while(!pQuery->Eof)
		{
			playerPtr = TPlayer::newInstance();
			playerPtr->load(*pQuery);

			if((GETFLAG(playerTypeFlag,ptf_FreeAgent) && playerPtr->isFreeAgent()) ||
					(GETFLAG(playerTypeFlag,ptf_TeamPlayer) && !playerPtr->isFreeAgent()))
				playerVector.push_back(playerPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadPlayerIDVectorByLeagueID(TLeagueID leagueID,short playerTypeFlag,
	TPlayerIDVector& playerIDVector)
{
	TPlayerVector playerVector;

	LoadPlayerVectorByLeagueID(leagueID, playerTypeFlag, playerVector);
	playerIDVector.fillFromPlayerVector(playerVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadOffGameStatVectorByWhereStr(const char* whereStr,
	TOffGameStatVector& offGameStatVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TOffGameStatPtr offGameStatPtr;

	// Find all OffGameStats
	try
	{
		offGameStatVector.erase(offGameStatVector.begin(),offGameStatVector.end());

		str.copyVarg("select * from OffGameStat");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());

		pQuery->First();
		while(!pQuery->Eof)
		{
			offGameStatPtr = TOffGameStat::newInstance();
			offGameStatPtr->load(*pQuery);
			offGameStatVector.push_back(offGameStatPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadOffGameStatVectorByStatPeriod(const TStatPeriod statPeriod,
	TOffGameStatVector& offGameStatVector)
{
	CStrVar str;

	if(statPeriod.isUndefined())
		throw ASIException("LoadOffGameStatVectorByStatPeriod: statPeriod.isUndefined()");

	str.copyVarg("StatPeriod = \"%s\"",statPeriod.c_str());
	LoadOffGameStatVectorByWhereStr(str,offGameStatVector);
}

/******************************************************************************/

// Assumes a StatPeriod of stp_SeasonGame because no other TStatPeriods have
// dates.

void LoadOffGameStatVectorByPlayerIDDateRange(const TPlayerID playerID,
	const TDateTime fromDate,const TDateTime toDate,
	TOffGameStatVector& offGameStatVector)
{
	CStrVar str;

	str.copyVarg("(PlayerID = \"%s\") and ",playerID.c_str());
	if(fromDate != TDateTime())
		str.concatVarg("(StatDate >= \"%s\") and ",FormatDateOnlyStr(fromDate).c_str());
	if(toDate != TDateTime())
		str.concatVarg("(StatDate <= \"%s\") and ",FormatDateOnlyStr(toDate).c_str());
	str.concatVarg("(StatPeriod = \"%s\")",TStatPeriod(stp_SeasonGame).c_str());

	LoadOffGameStatVectorByWhereStr(str,offGameStatVector);
}

/******************************************************************************/

void PurgeOffGameStatByWhereStr(const char* whereStr)
{
	CStrVar str;

	str.copyVarg("delete from OffGameStat");
	if(tStrHasLen(whereStr))
		str.concatVarg(" where %s",whereStr);
	
	ExecQuery(PrimaryDatabaseName(),str);
}

/******************************************************************************/

void PurgeOffGameStatByStatPeriod(const TStatPeriod statPeriod)
{
	TStatPeriodVector statPeriodVector;

	if(statPeriod.isUndefined())
		throw ASIException("PurgeOffGameStatByStatPeriod: statPeriod.isUndefined()");

	statPeriodVector.push_back(statPeriod);
	PurgeOffGameStatByStatPeriodVector(statPeriodVector);
}

/******************************************************************************/

void PurgeOffGameStatByStatPeriodVector(
	const TStatPeriodVector& statPeriodVector)
{
	PurgeOffGameStatByWhereStr(BuildStatPeriodVectorStr(statPeriodVector));
}

/******************************************************************************/
/******************************************************************************/

void LoadDefGameStatVectorByWhereStr(const char* whereStr,
	TDefGameStatVector& defGameStatVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TDefGameStatPtr defGameStatPtr;

	// Find all DefGameStats
	try
	{
		defGameStatVector.erase(defGameStatVector.begin(),defGameStatVector.end());

		str.copyVarg("select * from DefGameStat");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());

		pQuery->First();
		while(!pQuery->Eof)
		{
			defGameStatPtr = TDefGameStat::newInstance();
			defGameStatPtr->load(*pQuery);
			defGameStatVector.push_back(defGameStatPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadDefGameStatVectorByStatPeriod(const TStatPeriod statPeriod,
	TDefGameStatVector& defGameStatVector)
{
	CStrVar str;

	if(statPeriod.isUndefined())
		throw ASIException("LoadDefGameStatVectorByStatPeriod: statPeriod.isUndefined()");

	str.copyVarg("StatPeriod = \"%s\"",statPeriod.c_str());
	LoadDefGameStatVectorByWhereStr(str,defGameStatVector);
}

/******************************************************************************/

// Assumes a StatPeriod of stp_SeasonGame because no other TStatPeriods have
// dates.

void LoadDefGameStatVectorByPlayerIDDateRange(const TPlayerID playerID,
	const TDateTime fromDate,const TDateTime toDate,
	TDefGameStatVector& defGameStatVector)
{
	CStrVar str;

	str.copyVarg("(PlayerID = \"%s\") and ",playerID.c_str());
	if(fromDate != TDateTime())
		str.concatVarg("(StatDate >= \"%s\") and ",FormatDateOnlyStr(fromDate).c_str());
	if(toDate != TDateTime())
		str.concatVarg("(StatDate <= \"%s\") and ",FormatDateOnlyStr(toDate).c_str());
	str.concatVarg("(StatPeriod = \"%s\")",TStatPeriod(stp_SeasonGame).c_str());

	LoadDefGameStatVectorByWhereStr(str,defGameStatVector);
}

/******************************************************************************/

void PurgeDefGameStatByWhereStr(const char* whereStr)
{
	CStrVar str;

	str.copyVarg("delete from DefGameStat");
	if(tStrHasLen(whereStr))
		str.concatVarg(" where %s",whereStr);
	
	ExecQuery(PrimaryDatabaseName(),str);
}

/******************************************************************************/

void PurgeDefGameStatByStatPeriod(const TStatPeriod statPeriod)
{
	TStatPeriodVector statPeriodVector;

	if(statPeriod.isUndefined())
		throw ASIException("PurgeDefGameStatByStatPeriod: statPeriod.isUndefined()");

	statPeriodVector.push_back(statPeriod);
	PurgeDefGameStatByStatPeriodVector(statPeriodVector);
}

/******************************************************************************/

void PurgeDefGameStatByStatPeriodVector(
	const TStatPeriodVector& statPeriodVector)
{
	PurgeDefGameStatByWhereStr(BuildStatPeriodVectorStr(statPeriodVector));
}

/******************************************************************************/
/******************************************************************************/

void LoadDraftRankingVectorByWhereStr(const char* whereStr,
	TDraftRankingVector& draftRankingVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TDraftRankingPtr draftRankingPtr;

	// Find all DraftRankings
	try
	{
		draftRankingVector.erase(draftRankingVector.begin(),draftRankingVector.end());

		str.copy("select * from DraftRanking");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			draftRankingPtr = TDraftRanking::newInstance();
			draftRankingPtr->load(*pQuery);
			draftRankingVector.push_back(draftRankingPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadDraftRankingVectorAllButDefault(TDraftRankingVector& draftRankingVector)
{
	CStrVar str;

	str.copyVarg("TeamID > %s",DefaultDraftRankingTeamID.c_str());

	LoadDraftRankingVectorByWhereStr(str,draftRankingVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadScheduleDayVectorByWhereStr(const char* whereStr,
	TScheduleDayVector& scheduleDayVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TScheduleDayPtr scheduleDayPtr;

	// Find all Teams for a particular League.
	try
	{
		scheduleDayVector.erase(scheduleDayVector.begin(),scheduleDayVector.end());

		str.copy("select * from ScheduleDay");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			scheduleDayPtr = TScheduleDay::newInstance();
			scheduleDayPtr->load(*pQuery);
			scheduleDayVector.push_back(scheduleDayPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

/* BOB convert this to use the Vector function then take the first entry. */

TScheduleDayPtr GetScheduleDayByWhereStr(const char* whereStr)
{
	TQuery* pQuery = NULL;
	AnsiString str;
	TScheduleDayPtr scheduleDayPtr;

	// Find all Teams for a particular League.
	try
	{
		str = AnsiString("select * from ScheduleDay where ") + whereStr;
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		if(!pQuery->Eof)
		{
			scheduleDayPtr = TScheduleDay::newInstance();
			scheduleDayPtr->load(*pQuery);
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}

	return(scheduleDayPtr);
}

/******************************************************************************/

TScheduleDayPtr GetNextScheduleDayForLeagueID(TLeagueID leagueID,bool afterToday)
{
	TQuery* pQuery = NULL;
	CStr511 str;
	TScheduleDayPtr scheduleDayPtr;

	// Find all Teams for a particular League.
	try
	{
		str.CopyVarg("select * from ScheduleDay where (LeagueID = \"%s\") "
			"and (GameDate %s \"%s\") order by GameDate",leagueID.c_str(),
			(afterToday ? ">" : ">=" ),
			TDateTime::CurrentDate().FormatString("m/d/yyyy").c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		if(!pQuery->Eof)
		{
			scheduleDayPtr = TScheduleDay::newInstance();
			scheduleDayPtr->load(*pQuery);
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}

	return(scheduleDayPtr);
}

/******************************************************************************/

TScheduleDayPtr GetNextNotStartedScheduleDayForLeagueID(TLeagueID leagueID,
	bool afterToday)
{
	TQuery* pQuery = NULL;
	CStr511 str;
	TScheduleDayPtr scheduleDayPtr;

	// Find all Teams for a particular League.
	try
	{
		str.CopyVarg("select * from ScheduleDay where (LeagueID = \"%s\") "
			"and (EarlyProfGameDate %s \"%s\") order by GameDate",leagueID.c_str(),
			(afterToday ? ">" : ">=" ),
			TDateTime::CurrentDate().FormatString("m/d/yyyy").c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		if(!pQuery->Eof)
		{
			scheduleDayPtr = TScheduleDay::newInstance();
			scheduleDayPtr->load(*pQuery);
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}

	return(scheduleDayPtr);
}

/******************************************************************************/

TScheduleDayPtr GetLastCompleteScheduleDayForLeagueID(TLeagueID leagueID,bool beforeToday)
{
	CStrVar str;

	str.copyVarg("(LeagueID = \"%s\") and (GameDate %s \"%s\") "
		"order by GameDate desc",leagueID.c_str(),(beforeToday ? "<" : "<=" ),
		TDateTime::CurrentDate().FormatString("m/d/yyyy").c_str());

	return(GetScheduleDayByWhereStr(str));
}

/******************************************************************************/

void LoadScheduleDayVectorByLeagueID(TLeagueID leagueID,
	TScheduleDayVector& scheduleDayVector)
{
#if 1	//BOB
	CStrVar str;

	str.copyVarg("(LeagueID = \"%s\")",leagueID.c_str());
	LoadScheduleDayVectorByWhereStr(str,scheduleDayVector);
#else	//BOB
	TQuery* pQuery = NULL;
	CStr511 str;
	TScheduleDayPtr scheduleDayPtr;

	// Find all Teams for a particular League.
	try
	{
		scheduleDayVector.erase(scheduleDayVector.begin(),scheduleDayVector.end());
		
		str.CopyVarg("select * from ScheduleDay where (LeagueID = \"%s\") "
			"order by GameDate",leagueID.c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			scheduleDayPtr = TScheduleDay::newInstance();
			scheduleDayPtr->load(*pQuery);
			scheduleDayVector.push_back(scheduleDayPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
#endif	//BOB
}

/******************************************************************************/
#if 0	//BOB remove

void GetActiveScheduleDaysForLeague(const TLeagueID leagueID,
	const bool inNightlyProcessing,TScheduleDayPtr& lastScheduleDayPtr,
	TScheduleDayPtr& thisScheduleDayPtr)
{
	TScheduleDayVector scheduleDayVector;
	TDateTime today = TDateTime::CurrentDate();
	CStrVar str;

	if(!inNightlyProcessing &&
			(TDateTime::CurrentTime() < NightlyProcessingTime()))
		--today;

	str.copyVarg("(LeagueID = \"%s\") and ",leagueID.c_str());
	str.concatVarg("(GameDate > \"%s\") and ",FormatDateOnlyStr(today - 7).c_str());

	// If the first game more than a week ago, not records would be found.
	if(SeasonOpener() > today + 7)
		str.concatVarg("(GameDate <= \"%s\")",FormatDateOnlyStr(SeasonOpener()).c_str());
	else
		str.concatVarg("(GameDate <= \"%s\")",FormatDateOnlyStr(today + 7).c_str());

	LoadScheduleDayVectorByWhereStr(str,scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	if((scheduleDayVector.size() != 1) && (scheduleDayVector.size() != 2))
		throw ASIException("GetActiveScheduleDaysForLeague: unexpected results from search");

	if(scheduleDayVector.size() == 1)
	{
		lastScheduleDayPtr = NULL;
		thisScheduleDayPtr = scheduleDayVector[0];
	}
	else
	{
		lastScheduleDayPtr = scheduleDayVector[0];
		thisScheduleDayPtr = scheduleDayVector[1];
	}
}

#endif	//BOB remove
/******************************************************************************/
/******************************************************************************/

void LoadGameResultVectorByWhereStr(const char* whereStr,
	TGameResultVector& gameResultVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TGameResultPtr gameResultPtr;

	// Find all GameResults
	try
	{
		gameResultVector.erase(gameResultVector.begin(),gameResultVector.end());
		
		str.copy("select * from GameResult");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str);
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			gameResultPtr = TGameResult::newInstance();
			gameResultPtr->load(*pQuery);
			gameResultVector.push_back(gameResultPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadGameResultVectorByTeamIDVectorGameDate(const TTeamIDVector& teamIDVector,
	const TDateTime gameDate,TGameResultVector& gameResultVector)
{
	CStrVar str;
	int i,numItems = teamIDVector.size();

	if(numItems == 0)
	{
		gameResultVector.erase(gameResultVector.begin(),gameResultVector.end());
		return;
	}

	str.copy("(TeamID in (");
	for(i = 0; i < numItems; ++i)
	{
		if(i > 0)
			str.concat(",");
		str.concatVarg("\"%s\"",teamIDVector[i].c_str());
	}
	str.concat(")) and ");
	str.concatVarg("(GameDate = \"%s\")",FormatDateOnlyStr(gameDate).c_str());

	LoadGameResultVectorByWhereStr(str,gameResultVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadFreeAgentClaimVectorByWhereStr(const char* whereStr,
	TFreeAgentClaimVector& freeAgentClaimVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TFreeAgentClaimPtr freeAgentClaimPtr;

	try
	{
		freeAgentClaimVector.erase(freeAgentClaimVector.begin(),freeAgentClaimVector.end());

		str.copy("select * from FreeAgentClaim");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			freeAgentClaimPtr = TFreeAgentClaim::newInstance();
			freeAgentClaimPtr->load(*pQuery);
			freeAgentClaimVector.push_back(freeAgentClaimPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadPendingFreeAgentClaimVectorByTeamIDVector(
	const TTeamIDVector& teamIDVector,
	TFreeAgentClaimVector& freeAgentClaimVector)
{
	CStrVar str;
	TFreeAgentClaimVector::iterator iter;
	TTeamIDVector foundTeamIDVector;
	int i,numItems = teamIDVector.size();

	if(numItems == 0)
	{
		freeAgentClaimVector.erase(freeAgentClaimVector.begin(),freeAgentClaimVector.end());
		return;
	}

	str.copy("(TeamID in (");
	for(i = 0; i < numItems; ++i)
	{
		if(i > 0)
			str.concat(",");
		str.concatVarg("\"%s\"",teamIDVector[i].c_str());
	}
	str.concat(")) and ");
	str.concatVarg("(Status = \"%s\")",
		TFreeAgentClaimStatus(facs_Pending).c_str());

	LoadFreeAgentClaimVectorByWhereStr(str,freeAgentClaimVector);

	// Sanity Check - verify only one pending claim per team.
	for(iter = freeAgentClaimVector.begin();
		iter != freeAgentClaimVector.end(); ++iter)
	{
		if(foundTeamIDVector.contains((*iter)->getTeamID()))
			throw ASIException("LoadPendingFreeAgentClaimVectorByLeagueID: multiple pending claims for team");

		foundTeamIDVector.push_back((*iter)->getTeamID());
	}
}

/******************************************************************************/

TFreeAgentClaimPtr GetPendingFreeAgentClaimByTeamID(const TTeamID teamID)
{
	TFreeAgentClaimVector freeAgentClaimVector;
	CStrVar str;

	str.copyVarg("(TeamID = \"%s\") and ",teamID.c_str());
	str.concatVarg("(Status = \"%s\")",
		TFreeAgentClaimStatus(facs_Pending).c_str());

	LoadFreeAgentClaimVectorByWhereStr(str,freeAgentClaimVector);
	if(freeAgentClaimVector.size() == 0)
		return(NULL);
	if(freeAgentClaimVector.size() == 1)
		return(*freeAgentClaimVector.begin());

	throw ASIException("GetPendingFreeAgentClaimByTeamID: found multiple pending claims");
}

/******************************************************************************/

void LoadRecentFreeAgentClaimVectorByTeamID(const TTeamID teamID,int recentDays,
	TFreeAgentClaimVector& freeAgentClaimVector)
{
	CStrVar str;

	str.copyVarg("(TeamID = \"%s\") and ",teamID.c_str());
	str.concatVarg("((Status = \"%s\") or ",
		TFreeAgentClaimStatus(facs_Pending).c_str());
	str.concatVarg("(ProcessedDate > \"%s\"))",
		FormatDateOnlyStr(TDateTime::CurrentDate() - recentDays).c_str());

	LoadFreeAgentClaimVectorByWhereStr(str,freeAgentClaimVector);
}

/******************************************************************************/
/******************************************************************************/

void LoadOpenTradesByTeamID(TTeamID teamID,TTradeVector& tradeVector)
{
	TQuery* pQuery = NULL;
	CStr511 str;
	TTradePtr tradePtr;

	// Find all Trades for a particular Team.
	try
	{
		tradeVector.erase(tradeVector.begin(),tradeVector.end());
		
		str.CopyVarg("select * from Trade where (TeamID = \"%s\") and "
			"((Status = \"%s\") or (Status = \"%s\")) "
			"order by ProposedDate",
			teamID.c_str(),TTradeStatus(trs_Proposed).c_str(),
			TTradeStatus(trs_Accepted).c_str());
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			tradePtr = TTrade::newInstance();
			tradePtr->load(*pQuery);
			tradeVector.push_back(tradePtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadRecentTradesByLeagueID(TLeagueID leagueID,TTradeVector& tradeVector)
{
	TQuery* pQuery = NULL;
	CStr511 str;
	TTradePtr tradePtr;

	// Find all Trades for a particular League where
	//	the ProposedDate is within (MaxTradeProposeDays + MaxTradeProtestDays)
	//	days or the status is Accepted or Proposed
	try
	{
		tradeVector.erase(tradeVector.begin(),tradeVector.end());
		
		str.Copy("select * from Trade where (");

		str.ConcatVarg("(ProposedDate >= \"%s\")",(TDateTime::CurrentDateTime() - 
			(MaxTradeProposeDays + MaxTradeProtestDays)).FormatString(
			"m/d/yyyy").c_str());

		str.Concat(" or ");

		str.ConcatVarg("(Status = \"%s\") or (Status = \"%s\")",
			TTradeStatus(trs_Proposed).c_str(),
			TTradeStatus(trs_Accepted).c_str());

		str.Concat(") and ");

		str.ConcatVarg("(TeamID in "
			"(select TeamID from Team where LeagueID = \"%s\")) ",
			leagueID.c_str());

		str.Concat("order by ProposedDate");

		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			tradePtr = TTrade::newInstance();
			tradePtr->load(*pQuery);
			tradeVector.push_back(tradePtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

};	// namespace asfantasy

/******************************************************************************/
/******************************************************************************/
