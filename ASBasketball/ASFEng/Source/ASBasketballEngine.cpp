/* ASBasketballEngine.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyCreateLineup.h"

#include "ASBasketballEngine.h"
#include "ASBasketballStatFileLoader.h"
#include "ASBasketballStatSummaryBuilder.h"
#include "ASBasketballBuildSchedule.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

TNTService& tag::getTheNTService()
{
	static asbasketball::ASBasketballEngine service;
	return(service);
}

/******************************************************************************/
/******************************************************************************/

void ASBasketballEngine::fillBackupDatabaseTableVector(
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

void ASBasketballEngine::getStatFilesForLoading(
	StatFileLoaderVector& statFileLoaderVector)
{
	TDateTime yesterday = TDateTime::CurrentDate() - 1;

	statFileLoaderVector.push_back(OffGameStatFileLoader::newInstance(
		DirSpec(),yesterday,stp_SeasonGame,true));
}

/******************************************************************************/

bool ASBasketballEngine::shouldProfPlayersLastWeeksPointsBeCleared()
{
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	int openerDOW = DayOfWeek(ConvertTDateTimetoTDate(SeasonOpener() + 1));	// day after opener

	if((todayDOW == openerDOW) && (TDateTime::CurrentDate() >= SeasonOpener()))
		return(true);

	return(false);
}

/******************************************************************************/

bool ASBasketballEngine::shouldStatSummariesBeCreated()
{
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	int openerDOW = DayOfWeek(ConvertTDateTimetoTDate(SeasonOpener()));	// same day as opener

	if((todayDOW == openerDOW) && (TDateTime::CurrentDate() >= SeasonOpener()))
		return(true);

	return(false);
}

/******************************************************************************/

void ASBasketballEngine::createStatSummaries(const TDateTime asOfDate)
{
	ASBasketballStatSummaryBuilder builder;

	builder.buildAllPlayersForThisSeason(asOfDate);
}

/******************************************************************************/

void ASBasketballEngine::getSeasonDateRangeForStatPeriod(
	const TStatPeriod statPeriod,TDateTime& fromDate,TDateTime& toDate)
{
	ASBasketballStatSummaryBuilder().getSeasonDateRangeForStatPeriod(statPeriod,
		fromDate,toDate);
}

/******************************************************************************/

void ASBasketballEngine::createSeasonSchedule()
{
	TTeamVector teamVector;
	ASBasketballBuildSchedule scheduleBuilder;
	TBuildScheduleDayVector buildScheduleDayVector;
	TBuildScheduleDayVector::const_iterator buildScheduleDayIter;
	short profGameWeek;

	fStore.getTeamVector(teamVector);	//BOB fBasebasketballStore?

	scheduleBuilder.buildTeamSchedule(teamVector,buildScheduleDayVector,
		NumProfWeeks(),2,1);
	if(cast2int(buildScheduleDayVector.size()) != NumProfWeeks())
		throw ASIException("ASBasketballEngine::createSeasonSchedule: buildScheduleDayVector.size() != NumProfWeeks()");

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

void ASBasketballEngine::createDefaultLineup(const TLeaguePtr& leaguePtr,
	TDraftResultPtr draftResultPtr)
{
	TTeamVector teamVector;
	
	fStore.getTeamVector(teamVector);

	CreateDefaultLineupForLeague(leaguePtr,teamVector,draftResultPtr,lut_Starting);
}

/******************************************************************************/

void ASBasketballEngine::loadGameStatPlayerIDVectorForTeam(const TTeamID teamID,
	const bool isOffense,TPlayerIDVector& playerIDVector)
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	if(isOffense)
		playerIDVector = teamPtr->lineupConst(lut_Starting);
	else
		playerIDVector.erase(playerIDVector.begin(),playerIDVector.end());

	playerIDVector.removeUndefined();
}

/******************************************************************************/
/******************************************************************************/

int ASBasketballEngine::getNumOfPlayoffGameStatsPerPlayerByPosition(
	const int position,const int playoffDay)
{
	if(PlayoffSeriesDays() != 4)	//sanity check
		throw ASIException("ASBasketballEngine::getNumOfPlayoffGameStatsPer"
			"PlayerByPosition: PlayoffSeriesDays() != 4");

	if(playoffDay == 0)	//total
		return(12);
	if((playoffDay >= 1) && (playoffDay <= 4))
		return(3);

	throw ASIException("ASBasketballEngine::getNumOfPlayoffGameStatsPerPlayer"
		"ByPosition: invalid playoffDay");
}

/******************************************************************************/
/******************************************************************************/

bool ASBasketballEngine::isTeamsLineupStillValid(TTeamID teamID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);
	TPlayerIDVector playerIDVector;

	fStore.getTeamPlayerIDVectorByTeam(teamID,playerIDVector);

	return(playerIDVector.contains(teamPtr->lineup(lut_Starting),true));
}

/******************************************************************************/

void ASBasketballEngine::removePlayerFromTeamsLineups(TTeamID teamID,
	TPlayerID playerID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	teamPtr->lineup(lut_Starting).replace(playerID,TPlayerID());
}

/******************************************************************************/

}; //asbasketball

/******************************************************************************/
/******************************************************************************/
