/* ASBaseballEngine.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyCreateLineup.h"

#include "ASBaseballEngine.h"
#include "ASBaseballStatFileLoader.h"
#include "ASBaseballStatSummaryBuilder.h"
#include "ASBaseballBuildSchedule.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

TNTService& tag::getTheNTService()
{
	static asbaseball::ASBaseballEngine service;
	return(service);
}

/******************************************************************************/
/******************************************************************************/

void ASBaseballEngine::fillBackupDatabaseTableVector(
	TDatabaseTableVector& databaseTableVector)
{
//BOB can this be moved into ASFantasy?
	databaseTableVector.erase(databaseTableVector.begin(),databaseTableVector.end());

	databaseTableVector.push_back("LeagueName");

	databaseTableVector.push_back("ProfTeam");
//BOB	databaseTableVector.push_back("ProfTeamSchedule");
	databaseTableVector.push_back("ProfPlayer");

	databaseTableVector.push_back("League");
	databaseTableVector.push_back("Team");
	databaseTableVector.push_back("Player");

	databaseTableVector.push_back("DraftRanking");
	databaseTableVector.push_back("DraftOrder");
	databaseTableVector.push_back("DraftResult");

	databaseTableVector.push_back("ScheduleDay");
	databaseTableVector.push_back("OffGameStat");
	databaseTableVector.push_back("DefGameStat");
	databaseTableVector.push_back("GameResult");

	databaseTableVector.push_back("FreeAgentClaim");
	databaseTableVector.push_back("Trade");
}

/******************************************************************************/

void ASBaseballEngine::getStatFilesForLoading(
	StatFileLoaderVector& statFileLoaderVector)
{
	TDateTime yesterday = TDateTime::CurrentDate() - 1;
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));

	statFileLoaderVector.push_back(OffGameStatFileLoader::newInstance(
		DirSpec(),yesterday,stp_SeasonGame,true));
	statFileLoaderVector.push_back(DefGameStatFileLoader::newInstance(
		DirSpec(),yesterday,stp_SeasonGame,true));

	if(todayDOW == DOW_FRIDAY)
	{
		statFileLoaderVector.push_back(InjuryFileLoader::newInstance(
			DirSpec(),yesterday));
		statFileLoaderVector.push_back(TransactionFileLoader::newInstance(
			DirSpec(),yesterday));
	}
}

/******************************************************************************/

bool ASBaseballEngine::shouldProfPlayersLastWeeksPointsBeCleared()
{
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	int openerDOW = DayOfWeek(ConvertTDateTimetoTDate(SeasonOpener() + 1));	// day after opener

	if((todayDOW == openerDOW) && (TDateTime::CurrentDate() >= SeasonOpener()))
		return(true);

	return(false);
}

/******************************************************************************/

bool ASBaseballEngine::shouldStatSummariesBeCreated()
{
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	int openerDOW = DayOfWeek(ConvertTDateTimetoTDate(SeasonOpener()));	// same day as opener

	if((todayDOW == openerDOW) && (TDateTime::CurrentDate() >= SeasonOpener()))
		return(true);

	return(false);
}

/******************************************************************************/

void ASBaseballEngine::createStatSummaries(const TDateTime asOfDate)
{
	ASBaseballStatSummaryBuilder builder;

	builder.buildAllPlayersForThisSeason(asOfDate);
}

/******************************************************************************/

void ASBaseballEngine::getSeasonDateRangeForStatPeriod(
	const TStatPeriod statPeriod,TDateTime& fromDate,TDateTime& toDate)
{
	ASBaseballStatSummaryBuilder().getSeasonDateRangeForStatPeriod(statPeriod,
		fromDate,toDate);
}

/******************************************************************************/

void ASBaseballEngine::createSeasonSchedule()
{
	TTeamVector teamVector;
	ASBaseballBuildSchedule scheduleBuilder;
	TBuildScheduleDayVector buildScheduleDayVector;
	TBuildScheduleDayVector::const_iterator buildScheduleDayIter;
	short profGameWeek;

	fStore.getTeamVector(teamVector);	//BOB fBasebaseballStore?

	scheduleBuilder.buildTeamSchedule(teamVector,buildScheduleDayVector,
		NumProfWeeks(),2,1);
	if(cast2int(buildScheduleDayVector.size()) != NumProfWeeks())
		throw ASIException("ASBaseballEngine::createSeasonSchedule: buildScheduleDayVector.size() != NumProfWeeks()");

	for(buildScheduleDayIter = buildScheduleDayVector.begin(), profGameWeek = 1;
		buildScheduleDayIter != buildScheduleDayVector.end();
		++buildScheduleDayIter,++profGameWeek)
	{
		const TBuildScheduleDay& buildScheduleDay = *buildScheduleDayIter;
		const TBuildScheduleGameVector& buildScheduleGameVector =
			buildScheduleDay.gameVector();
		TBuildScheduleGameVector::const_iterator buildScheduleGameIter;

		TScheduleDayPtr scheduleDayPtr = TScheduleDay::newInstance();
		
		scheduleDayPtr->setLeagueID(fCurLeaguePtr->getLeagueID());
		scheduleDayPtr->setGameDate(SeasonOpener() + ((profGameWeek - 1) * 7));

		scheduleDayPtr->setStatus(sdst_NotStarted);

		scheduleDayPtr->setLateProfGameDate(scheduleDayPtr->getGameDate() - 1);
		if(profGameWeek == 1)
			scheduleDayPtr->setEarlyProfGameDate(StatStartDate());
		else
			scheduleDayPtr->setEarlyProfGameDate(
				scheduleDayPtr->getLateProfGameDate() - 6);
		scheduleDayPtr->setEarlyProfGameTime(NightlyProcessingTime());

		scheduleDayPtr->setProfGameWeek(profGameWeek);

		for(buildScheduleGameIter = buildScheduleGameVector.begin();
			buildScheduleGameIter != buildScheduleGameVector.end();
			buildScheduleGameIter++)
		{
			const TBuildScheduleGame& buildScheduleGame = *buildScheduleGameIter;
			TScheduleDayGame scheduleDayGame;

			scheduleDayGame.setVisitTeamID(buildScheduleGame.getVisitTeamID());
			scheduleDayGame.setHomeTeamID(buildScheduleGame.getHomeTeamID());
		
			scheduleDayPtr->scheduleDayGameVector().push_back(scheduleDayGame);
		}

		scheduleDayPtr->update();

		fStore.addScheduleDay(scheduleDayPtr);
	}
}

/******************************************************************************/

void ASBaseballEngine::createDefaultLineup(const TLeaguePtr& leaguePtr,
	TDraftResultPtr draftResultPtr)
{
	TTeamVector teamVector;
	
	fStore.getTeamVector(teamVector);

	CreateDefaultLineupForLeague(leaguePtr,teamVector,draftResultPtr,lut_Batter);
	CreateDefaultLineupForLeague(leaguePtr,teamVector,draftResultPtr,lut_Pitcher);
}

/******************************************************************************/

void ASBaseballEngine::loadGameStatPlayerIDVectorForTeam(const TTeamID teamID,
	const bool isOffense,TPlayerIDVector& playerIDVector)
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	if(isOffense)
		playerIDVector = teamPtr->lineupConst(lut_Batter);
	else
		playerIDVector = teamPtr->lineupConst(lut_Pitcher);

	playerIDVector.removeUndefined();
}

/******************************************************************************/
/******************************************************************************/

int ASBaseballEngine::getNumOfPlayoffGameStatsPerPlayerByPosition(
	const int position,const int playoffDay)
{
	TBaseballPosition baseballPosition(position);

	if(PlayoffSeriesDays() != 4)	//sanity check
		throw ASIException("ASBaseballEngine::getNumOfPlayoffGameStatsPer"
			"PlayerByPosition: PlayoffSeriesDays() != 4");

	if(baseballPosition.isOffensive())
	{
		if(playoffDay == 0)	//total
			return(24);
		if((playoffDay >= 1) && (playoffDay <= 4))
			return(6);
	}
	else if(baseballPosition == pos_StartingPitcher)
	{
		if(playoffDay == 0)	//total
			return(5);
		if(playoffDay == 1)
			return(2);
		if((playoffDay >= 2) && (playoffDay <= 4))
			return(1);
	}
	else if(baseballPosition == pos_ReliefPitcher)
	{
		if(playoffDay == 0)	//total
			return(8);
		if((playoffDay >= 1) && (playoffDay <= 4))
			return(2);
	}
	else
		throw ASIException("ASBaseballEngine::getNumOfPlayoffGameStatsPer"
			"PlayerByPosition: unknown position");

	throw ASIException("ASBaseballEngine::getNumOfPlayoffGameStatsPerPlayer"
		"ByPosition: invalid playoffDay");
}

/******************************************************************************/
/******************************************************************************/

bool ASBaseballEngine::isTeamsLineupStillValid(TTeamID teamID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);
	TPlayerIDVector playerIDVector;

	fStore.getTeamPlayerIDVectorByTeam(teamID,playerIDVector);

	if(!playerIDVector.contains(teamPtr->lineup(lut_Batter),true))
		return(false);

	if(!playerIDVector.contains(teamPtr->lineup(lut_Pitcher),true))
		return(false);

	return(true);
}

/******************************************************************************/

void ASBaseballEngine::removePlayerFromTeamsLineups(TTeamID teamID,
	TPlayerID playerID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	teamPtr->lineup(lut_Batter).replace(playerID,TPlayerID());
	teamPtr->lineup(lut_Pitcher).replace(playerID,TPlayerID());
}

/******************************************************************************/

}; //asbaseball

/******************************************************************************/
/******************************************************************************/
