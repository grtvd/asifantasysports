/* ASHockeyEngine.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyCreateLineup.h"

#include "ASHockeyEngine.h"
#include "ASHockeyStatFileLoader.h"
#include "ASHockeyStatSummaryBuilder.h"
#include "ASHockeyBuildSchedule.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

TNTService& tag::getTheNTService()
{
	static ashockey::ASHockeyEngine service;
	return(service);
}

/******************************************************************************/
/******************************************************************************/

void ASHockeyEngine::fillBackupDatabaseTableVector(
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

void ASHockeyEngine::getStatFilesForLoading(
	StatFileLoaderVector& statFileLoaderVector)
{
	TDateTime yesterday = TDateTime::CurrentDate() - 1;

	statFileLoaderVector.push_back(OffGameStatFileLoader::newInstance(
		DirSpec(),yesterday,stp_SeasonGame,true));
	statFileLoaderVector.push_back(DefGameStatFileLoader::newInstance(
		DirSpec(),yesterday,stp_SeasonGame,true));
}

/******************************************************************************/

bool ASHockeyEngine::shouldProfPlayersLastWeeksPointsBeCleared()
{
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	int openerDOW = DayOfWeek(ConvertTDateTimetoTDate(SeasonOpener() + 1));	// day after opener

	if((todayDOW == openerDOW) && (TDateTime::CurrentDate() >= SeasonOpener()))
		return(true);

	return(false);
}

/******************************************************************************/

bool ASHockeyEngine::shouldStatSummariesBeCreated()
{
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	int openerDOW = DayOfWeek(ConvertTDateTimetoTDate(SeasonOpener()));	// same day as opener

	if((todayDOW == openerDOW) && (TDateTime::CurrentDate() >= SeasonOpener()))
		return(true);

	return(false);
}

/******************************************************************************/

void ASHockeyEngine::createStatSummaries(const TDateTime asOfDate)
{
	ASHockeyStatSummaryBuilder builder;

	builder.buildAllPlayersForThisSeason(asOfDate);
}

/******************************************************************************/

void ASHockeyEngine::getSeasonDateRangeForStatPeriod(
	const TStatPeriod statPeriod,TDateTime& fromDate,TDateTime& toDate)
{
	ASHockeyStatSummaryBuilder().getSeasonDateRangeForStatPeriod(statPeriod,
		fromDate,toDate);
}

/******************************************************************************/

void ASHockeyEngine::createSeasonSchedule()
{
	TTeamVector teamVector;
	ASHockeyBuildSchedule scheduleBuilder;
	TBuildScheduleDayVector buildScheduleDayVector;
	TBuildScheduleDayVector::const_iterator buildScheduleDayIter;
	short profGameWeek;

	fStore.getTeamVector(teamVector);	//BOB fBasebaseballStore?

	scheduleBuilder.buildTeamSchedule(teamVector,buildScheduleDayVector,
		cast2short(NumProfWeeks()),2,1);
	if(cast2int(buildScheduleDayVector.size()) != NumProfWeeks())
		throw ASIException("ASHockeyEngine::createSeasonSchedule: buildScheduleDayVector.size() != NumProfWeeks()");

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

void ASHockeyEngine::createDefaultLineup(const TLeaguePtr& leaguePtr,
	TDraftResultPtr draftResultPtr)
{
	TTeamVector teamVector;
	
	fStore.getTeamVector(teamVector);

	CreateDefaultLineupForLeague(leaguePtr,teamVector,draftResultPtr,lut_Skater);
	CreateDefaultLineupForLeague(leaguePtr,teamVector,draftResultPtr,lut_Goalie);
}

/******************************************************************************/

void ASHockeyEngine::loadGameStatPlayerIDVectorForTeam(const TTeamID teamID,
	const bool isOffense,TPlayerIDVector& playerIDVector)
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	if(isOffense)
		playerIDVector = teamPtr->lineupConst(lut_Skater);
	else
		playerIDVector = teamPtr->lineupConst(lut_Goalie);

	playerIDVector.removeUndefined();
}

/******************************************************************************/
/******************************************************************************/

int ASHockeyEngine::getNumOfPlayoffGameStatsPerPlayerByPosition(
	const int position,const int playoffDay)
{
	if(PlayoffSeriesDays() != 4)	//sanity check
		throw ASIException("ASHockeyEngine::getNumOfPlayoffGameStatsPer"
			"PlayerByPosition: PlayoffSeriesDays() != 4");

	if(playoffDay == 0)	//total
		return(12);
	if((playoffDay >= 1) && (playoffDay <= 4))
		return(3);

	throw ASIException("ASHockeyEngine::getNumOfPlayoffGameStatsPerPlayer"
		"ByPosition: invalid playoffDay");
}

/******************************************************************************/
/******************************************************************************/

bool ASHockeyEngine::isTeamsLineupStillValid(TTeamID teamID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);
	TPlayerIDVector playerIDVector;

	fStore.getTeamPlayerIDVectorByTeam(teamID,playerIDVector);

	if(!playerIDVector.contains(teamPtr->lineup(lut_Skater),true))
		return(false);

	if(!playerIDVector.contains(teamPtr->lineup(lut_Goalie),true))
		return(false);

	return(true);
}

/******************************************************************************/

void ASHockeyEngine::removePlayerFromTeamsLineups(TTeamID teamID,
	TPlayerID playerID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	teamPtr->lineup(lut_Skater).replace(playerID,TPlayerID());
	teamPtr->lineup(lut_Goalie).replace(playerID,TPlayerID());
}

/******************************************************************************/

}; //ashockey

/******************************************************************************/
/******************************************************************************/
