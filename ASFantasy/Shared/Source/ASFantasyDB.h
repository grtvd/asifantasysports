/* ASFantasyDB.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDBH
#define ASFantasyDBH

#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

void ClearLastWeeksPointsForAllProfPlayers();

void LoadParticVectorByTeamVector(const TTeamVector& teamVector,
	TParticVector& particVector);

void LoadLeagueVectorByOpenPublic(TLeagueVector& leagueVector);
void LoadLeagueVectorByEnrollPrivatePartialName(const char* partialLeagueName,
	TLeagueVector& leagueVector);
void LoadLeagueVectorByNotLastProcessedDate(TDateTime lastProcessedDate,
	TLeagueVector& leagueVector);

void LoadTeamVectorByLeagueID(TLeagueID leagueID,TTeamVector& teamVector);

void LoadProfPlayerVectorByGameStatus(const TProfPlayerGameStatus gameStatus,
	TProfPlayerVector& profPlayerVector);

void LoadPlayerVectorByTeamID(TTeamID teamID, TPlayerVector& playerVector);
void LoadPlayerIDVectorByTeamID(TTeamID teamID, TPlayerIDVector& playerIDVector);

void LoadPlayerVectorByLeagueID(TLeagueID leagueID,short playerTypeFlag,
	TPlayerVector& playerVector);
void LoadPlayerIDVectorByLeagueID(TLeagueID leagueID,short playerTypeFlag,
	TPlayerIDVector& playerIDVector);

void LoadOffGameStatVectorByStatPeriod(const TStatPeriod statPeriod,
	TOffGameStatVector& offGameStatVector);
void LoadOffGameStatVectorByPlayerIDDateRange(const TPlayerID playerID,
	const TDateTime fromDate,const TDateTime toDate,
	TOffGameStatVector& offGameStatVector);
void PurgeOffGameStatByStatPeriod(const TStatPeriod statPerid);
void PurgeOffGameStatByStatPeriodVector(
	const TStatPeriodVector& statPeriodVector);

void LoadDefGameStatVectorByStatPeriod(const TStatPeriod statPeriod,
	TDefGameStatVector& defGameStatVector);
void LoadDefGameStatVectorByPlayerIDDateRange(const TPlayerID playerID,
	const TDateTime fromDate,const TDateTime toDate,
	TDefGameStatVector& defGameStatVector);
void PurgeDefGameStatByStatPeriod(const TStatPeriod statPeriod);
void PurgeDefGameStatByStatPeriodVector(
	const TStatPeriodVector& statPeriodVector);

void LoadDraftRankingVectorAllButDefault(TDraftRankingVector& draftRankingVector);

TScheduleDayPtr GetNextScheduleDayForLeagueID(TLeagueID leagueID,
	bool afterToday = true);
TScheduleDayPtr GetNextNotStartedScheduleDayForLeagueID(TLeagueID leagueID,
	bool afterToday = true);
TScheduleDayPtr GetLastCompleteScheduleDayForLeagueID(TLeagueID leagueID,bool beforeToday);
void LoadScheduleDayVectorByLeagueID(TLeagueID leagueID,
	TScheduleDayVector& scheduleDayVector);

void LoadGameResultVectorByTeamIDVectorGameDate(const TTeamIDVector& teamIDVector,
	const TDateTime gameDate,TGameResultVector& gameResultVector);

void LoadPendingFreeAgentClaimVectorByTeamIDVector(
	const TTeamIDVector& teamIDVector,
	TFreeAgentClaimVector& freeAgentClaimVector);
TFreeAgentClaimPtr GetPendingFreeAgentClaimByTeamID(const TTeamID teamID);
void LoadRecentFreeAgentClaimVectorByTeamID(const TTeamID teamID,int recentDays,
	TFreeAgentClaimVector& freeAgentClaimVector);

void LoadOpenTradesByTeamID(TTeamID teamID,TTradeVector& tradeVector);
void LoadRecentTradesByLeagueID(TLeagueID leagueID,TTradeVector& tradeVector);

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDBH
/******************************************************************************/
/******************************************************************************/
