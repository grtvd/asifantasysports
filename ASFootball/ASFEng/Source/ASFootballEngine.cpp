/* ASFootballEngine.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyCreateLineup.h"

#include "ASFootballEngine.h"
#include "ASFootballStatFileLoader.h"
#include "ASFootballStatSummaryBuilder.h"
#include "ASFootballBuildSchedule.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

TNTService& tag::getTheNTService()
{
	static asfootball::ASFootballEngine service;
	return(service);
}

/******************************************************************************/
/******************************************************************************/

void ASFootballEngine::fillBackupDatabaseTableVector(
	TDatabaseTableVector& databaseTableVector)
{
	databaseTableVector.erase(databaseTableVector.begin(),databaseTableVector.end());

	databaseTableVector.push_back("LeagueName");

	databaseTableVector.push_back("ProfTeam");
	databaseTableVector.push_back("ProfTeamSchedule");
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

void ASFootballEngine::addAllShelves()
{
	ASFantasyEngine::addAllShelves();

	fFootballStore.addProfTeamScheduleShelf();
}

/******************************************************************************/

void ASFootballEngine::delAllShelves()
{
	ASFantasyEngine::delAllShelves();
	
	fFootballStore.delProfTeamScheduleShelf();
}

/******************************************************************************/

void ASFootballEngine::loadShelvesForStatLoad()
{
	ASFantasyEngine::loadShelvesForStatLoad();
	
	fFootballStore.loadAllProfTeamSchedules();
}

/******************************************************************************/

void ASFootballEngine::unloadShelvesForStatLoad()
{
	ASFantasyEngine::unloadShelvesForStatLoad();

	fFootballStore.delAllProfTeamScheduleShelfItems();
}

/******************************************************************************/

void ASFootballEngine::loadShelvesForProcessing()
{
	ASFantasyEngine::loadShelvesForProcessing();
	
	fFootballStore.loadAllProfTeamSchedules();
}

/******************************************************************************/

void ASFootballEngine::unloadShelvesForProcessing()
{
	ASFantasyEngine::unloadShelvesForProcessing();

	fFootballStore.delAllProfTeamScheduleShelfItems();
}

/******************************************************************************/

void ASFootballEngine::getStatFilesForLoading(
	StatFileLoaderVector& statFileLoaderVector)
{
	TDateTime yesterday = TDateTime::CurrentDate() - 1;
	int todayDOW = DayOfWeek(ConvertTDateTimetoTDate(TDateTime::CurrentDate()));
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;

	// Any PlayerInfo file to load?
	if(todayDOW == DOW_SATURDAY)
	{
		statFileLoaderVector.push_back(PlayerInfoStatFileLoader::newInstance(
			DirSpec(),yesterday));
	}

	// Any Offensive/Defensive files to load?
	profTeamSchedulePtr = fFootballStore.findProfTeamScheduleByContainsGameDate(
		yesterday,cam_MayNotExist);

	if(!profTeamSchedulePtr.isNull() &&
		profTeamSchedulePtr->anyGamesForDate(yesterday))
	{
		statFileLoaderVector.push_back(OffGameStatFileLoader::newInstance(
			DirSpec(),yesterday,stp_SeasonGame,true));
		statFileLoaderVector.push_back(DefGameStatFileLoader::newInstance(
			DirSpec(),yesterday,stp_SeasonGame,true));
	}
}

/******************************************************************************/

bool ASFootballEngine::shouldProfPlayersLastWeeksPointsBeCleared()
{
	TDateTime yesterday = TDateTime::CurrentDate() - 1;
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;

	profTeamSchedulePtr = fFootballStore.findProfTeamScheduleByContainsGameDate(
		yesterday,cam_MayNotExist);

	if(!profTeamSchedulePtr.isNull() &&
			(profTeamSchedulePtr->findEarliestGameDate() == yesterday))
		return(true);

	return(false);
}

/******************************************************************************/

bool ASFootballEngine::shouldStatSummariesBeCreated()
{
	TDateTime yesterday = TDateTime::CurrentDate() - 1;
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;

	profTeamSchedulePtr = fFootballStore.findProfTeamScheduleByContainsGameDate(
		yesterday,cam_MayNotExist);

	if(!profTeamSchedulePtr.isNull() &&
			(profTeamSchedulePtr->findLatestGameDate() == yesterday))
		return(true);

	return(false);
}

/******************************************************************************/

void ASFootballEngine::createStatSummaries(const TDateTime asOfDate)
{
	ASFootballStatSummaryBuilder builder;

	builder.buildAllPlayersForThisSeason(asOfDate);
}

/******************************************************************************/

void ASFootballEngine::getSeasonDateRangeForStatPeriod(
	const TStatPeriod statPeriod,TDateTime& fromDate,TDateTime& toDate)
{
	ASFootballStatSummaryBuilder().getSeasonDateRangeForStatPeriod(statPeriod,
		fromDate,toDate);
}

/******************************************************************************/

void ASFootballEngine::createSeasonSchedule()
{
#if 1	//BOB
	TTeamVector teamVector;
	TFootballProfTeamScheduleVector profTeamScheduleVector;
	TFootballProfTeamScheduleVector::const_iterator profTeamScheduleIter;
	ASFootballBuildSchedule scheduleBuilder;
	TBuildScheduleDayVector buildScheduleDayVector;
	TBuildScheduleDayVector::const_iterator buildScheduleDayIter;
	short profGameWeek;

	fStore.getTeamVector(teamVector);	//BOB fBasebaseballStore?
	fFootballStore.getProfTeamScheduleVector(profTeamScheduleVector);
	profTeamScheduleVector.sortByProfGameWeek();

	scheduleBuilder.buildTeamSchedule(teamVector,buildScheduleDayVector,
		cast2short(NumProfWeeks()),2,1);

	if(cast2int(buildScheduleDayVector.size()) != NumProfWeeks())
		throw ASIException("ASFootballEngine::createSeasonSchedule: buildScheduleDayVector.size() != NumProfWeeks()");
	if(cast2int(profTeamScheduleVector.size()) != NumProfWeeks())
		throw ASIException("ASFootballEngine::createSeasonSchedule: profTeamScheduleVector.size() != NumProfWeeks()");

	profTeamScheduleIter = profTeamScheduleVector.begin();

	for(buildScheduleDayIter = buildScheduleDayVector.begin(), profGameWeek = 1;
		buildScheduleDayIter != buildScheduleDayVector.end();
		++buildScheduleDayIter,++profTeamScheduleIter,++profGameWeek)
	{
		const TBuildScheduleDay& buildScheduleDay = *buildScheduleDayIter;
		const TBuildScheduleGameVector& buildScheduleGameVector =
			buildScheduleDay.gameVector();
		TBuildScheduleGameVector::const_iterator buildScheduleGameIter;

		TScheduleDayPtr scheduleDayPtr = TScheduleDay::newInstance();
		
		scheduleDayPtr->setLeagueID(fCurLeaguePtr->getLeagueID());
		scheduleDayPtr->setEarlyProfGameDate(
			(*profTeamScheduleIter)->findEarliestGameDate());
		scheduleDayPtr->setEarlyProfGameTime(
			(*profTeamScheduleIter)->findEarliestGameTime());
		scheduleDayPtr->setLateProfGameDate(
			(*profTeamScheduleIter)->findLatestGameDate());
		scheduleDayPtr->setGameDate(scheduleDayPtr->getLateProfGameDate() + 1);

		scheduleDayPtr->setStatus(sdst_NotStarted);
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
#else
	TTeamVector teamVector;
	TFootballProfTeamScheduleVector profTeamScheduleVector;
	TFootballProfTeamScheduleVector::const_iterator profTeamScheduleIter;
	TBuildScheduleDayVector buildScheduleDayVector;
	TBuildScheduleDayVector::const_iterator buildScheduleDayIter;
	TProfGameWeek skipNFLWeek = GetRandomFromRange(ScheduleByeWeekEarly,
		ScheduleByeWeekLate);

	fFootballStore.getTeamVector(teamVector);
	fFootballStore.getProfTeamScheduleVector(profTeamScheduleVector);

	// Some sanity checks
//BOB	#if IsEven(NumProfWeeks())
//BOB		// An even number of NFL weeks means an odd number of games in
//BOB		// ASFootball (includes Bye week). ASF assumes even number of ASF games.
//BOB		#error ASFootballEngine::createSeasonSchedule: NumNFLWeeks is even
//BOB		//if(IsEven(NumNFLWeeks))
//BOB		// throw ASIException("ASFootballEngine::createSeasonSchedule: NumNFLWeeks is even");
//BOB	#endif
		
	if(profTeamScheduleVector.size() != NumProfWeeks())
		throw ASIException("ASFootballEngine::createSeasonSchedule: profTeamScheduleVector.size() != NumNFLWeeks");

	// Get schedule template, 
	buildTeamSchedule(teamVector,buildScheduleDayVector,NumNFLWeeks - 1,1,1);

	if(buildScheduleDayVector.size() != (NumNFLWeeks - 1))
		throw ASIException("ASFootballEngine::createSeasonSchedule: buildScheduleDayVector.size() != (NumNFLWeeks - 1)");
	
	// Create ASFootball specific schedule
	buildScheduleDayIter = buildScheduleDayVector.begin();
	
	for(profTeamScheduleIter = profTeamScheduleVector.begin();
		profTeamScheduleIter != profTeamScheduleVector.end();
		profTeamScheduleIter++)
	{
		//const TProfTeamGameVector& profTeamGameVector =
		//	(*profTeamScheduleIter)->profTeamGameVector();
		TFootballScheduleDayPtr scheduleDayPtr;

		scheduleDayPtr = TFootballScheduleDayPtr(TScheduleDay::newInstance());
		
		scheduleDayPtr->setLeagueID(fCurLeaguePtr->getLeagueID());
		scheduleDayPtr->setEarlyProfGameDate(
			(*profTeamScheduleIter)->findEarliestGameDate());
		scheduleDayPtr->setLateProfGameDate(
			(*profTeamScheduleIter)->findLatestGameDate());
		scheduleDayPtr->setGameDate(scheduleDayPtr->getLateProfGameDate() + 1);
		scheduleDayPtr->setNFLWeek((*profTeamScheduleIter)->getNFLWeek());

		// Copy games for day if not Bye week.
		if(scheduleDayPtr->getNFLWeek() != skipNFLWeek)
		{
			// Have build schdule day games been exhasted?
			if(buildScheduleDayIter == buildScheduleDayVector.end())
				throw ASIException("ASFootballEngine::createSeasonSchedule: buildScheduleDayIter == buildScheduleDayVector.end()");
		
			const TBuildScheduleDay& buildScheduleDay = *buildScheduleDayIter;
			const TBuildScheduleGameVector& buildScheduleGameVector =
				buildScheduleDay.gameVector();
			TBuildScheduleGameVector::const_iterator buildScheduleGameIter;

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

			buildScheduleDayIter++;
		}
		
		scheduleDayPtr->update();
	}

	// All of build schedule day games should have been used.
	if(buildScheduleDayIter != buildScheduleDayVector.end())
		throw ASIException("ASFootballEngine::createSeasonSchedule: buildScheduleDayIter != buildScheduleDayVector.end()");
#endif
}

/******************************************************************************/

void ASFootballEngine::createDefaultLineup(const TLeaguePtr& leaguePtr,
	TDraftResultPtr draftResultPtr)
{
	TTeamVector teamVector;
	
	fFootballStore.getTeamVector(teamVector);
	CreateDefaultLineupForLeague(leaguePtr,teamVector,draftResultPtr,lut_Starting);
}

/******************************************************************************/

void ASFootballEngine::loadGameStatPlayerIDVectorForTeam(const TTeamID teamID,
	const bool isOffense,TPlayerIDVector& playerIDVector)
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);
	const TPlayerIDVector& lineup = teamPtr->lineupConst(lut_Starting);
	TPlayerIDVector::const_iterator iter;
	TPlayerID playerID;
	TProfPlayerPtr profPlayerPtr;

	playerIDVector.erase(playerIDVector.begin(),playerIDVector.end());

	for(iter = lineup.begin(); iter != lineup.end(); ++iter)
	{
		playerID = *iter;
		if(!playerID.isUndefined())
		{
			profPlayerPtr = fStore.getProfPlayer(playerID);
			if(TFootballPosition(profPlayerPtr->getPosition()).isOffensive())
			{
				if(isOffense)
					playerIDVector.push_back(playerID);
			}
			else
			{
				if(!isOffense)
					playerIDVector.push_back(playerID);
			}
		}
	}
}

/******************************************************************************/
/******************************************************************************/

int ASFootballEngine::getNumOfPlayoffGameStatsPerPlayerByPosition(
	const int position,const int playoffDay)
{
	if(PlayoffSeriesDays() != 4)	//sanity check
		throw ASIException("ASFootballEngine::getNumOfPlayoffGameStatsPer"
			"PlayerByPosition: PlayoffSeriesDays() != 4");

	if(playoffDay == 0)	//total
		return(4);
	if((playoffDay >= 1) && (playoffDay <= 4))
		return(1);

	throw ASIException("ASFootballEngine::getNumOfPlayoffGameStatsPerPlayer"
		"ByPosition: invalid playoffDay");
}

/******************************************************************************/
/******************************************************************************/

bool ASFootballEngine::isTeamsLineupStillValid(TTeamID teamID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);
	TPlayerIDVector playerIDVector;

	fStore.getTeamPlayerIDVectorByTeam(teamID,playerIDVector);

	return(playerIDVector.contains(teamPtr->lineup(lut_Starting),true));
}

/******************************************************************************/

void ASFootballEngine::removePlayerFromTeamsLineups(TTeamID teamID,
	TPlayerID playerID) const
{
	TTeamPtr teamPtr = fStore.getTeam(teamID);

	teamPtr->lineup(lut_Starting).replace(playerID,TPlayerID());
}

/******************************************************************************/

}; //asfootball

/******************************************************************************/
/******************************************************************************/
