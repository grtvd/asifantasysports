/* ASFantasyBuildSchedule.h */

/*
	class TBuildScedule

	This class is used to create a schedule of games between a list of teams.
	Each team is in one of two divisions.  The caller creates matchups based
	on a ratio of divisional to non-divisional games.  Additionally, this class
	attempts to balance home games and away games.
*/

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <time.h>
#include <math.h>

#include "ASFantasyBuildSchedule.h"

namespace asfantasy
{

//#define DEBUG_PRINT_ON
#if defined(DEBUG_PRINT_ON)
#define DEBUG_PRINT(x) x
#else
#define DEBUG_PRINT(x)
#endif

/******************************************************************************/

bool TBuildSchedule::fSeed = FALSE;

/******************************************************************************/
/******************************************************************************/

TBuildScheduleTeam::TBuildScheduleTeam()
{
	memset( this, 0, sizeof(TBuildScheduleTeam) );
}

/******************************************************************************/

void TBuildScheduleTeam::fillTeamInfo( TTeamPtr team, short games )
{
	setTeamID( team->getTeamID() );
	setDivision( team->getDivision() );
	setGamesAvailable( games );
}

/******************************************************************************/

bool TBuildScheduleTeam::addHomeGame( void )
{
	if (fGamesAvailable > 0)
	{
		fHomeGames++;
		fGamesAvailable--;
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/

bool TBuildScheduleTeam::addAwayGame( void )
{
	if (fGamesAvailable > 0)
	{
		fAwayGames++;
		fGamesAvailable--;
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/

void TBuildScheduleTeam::print( void )
{
#if defined(DEBUG_PRINT_ON)
	CommErrMsg(cel_Info,"Team ID: %2ld  Home Games: %d  Away Games: %d",
		fTeamID.getID(),(int)fHomeGames,(int)fAwayGames);
#endif
}

/******************************************************************************/
/******************************************************************************/

// Must call NewSchedule() before Initialize() and CreateBuildSchedule()
TBuildSchedule::TBuildSchedule()
{
	clear();
}

/******************************************************************************/

// Must call Initialize() before CreateBuildSchedule()
TBuildSchedule::TBuildSchedule( TTeamVector& teamList, short gamesPerTeam,
	short divisionFactor, short nonDivisionFactor )
{
	clear();
	fTeamList = &teamList;
	fGamesPerTeam = gamesPerTeam;
	fDivisionFactor = divisionFactor;
	fNonDivisionFactor = nonDivisionFactor;
}

/******************************************************************************/

void TBuildSchedule::buildTeamSchedule(TTeamVector& teamList,
	TBuildScheduleDayVector& scheduleDayVector, short gamesPerTeam,
	short divisionFactor, short nonDivisionFactor)
{
	const int maxBuildTries = 1;	//BOB was - 5
	int count;

	// attempt to build a schedule
	// note that the only way out of this loop is either success or an exception
	for (count = 1; count <= maxBuildTries; count++)
	{
		try
		{
			DEBUG_PRINT( if (count > 1)
				CommErrMsg(cel_Info,"\n***  Retrying...  ***\n" ); );

			newSchedule(teamList, gamesPerTeam, divisionFactor,nonDivisionFactor);
			initialize();
			buildSchedule(scheduleDayVector);

			return;
		}

		// build schedule exception
		catch (BuildScheduleError& err)
		{
			// error is not home-away game difference or too many retires; abort
			if (((err.getError() != tbse_HomeAwayDiff)
					&& (err.getError() != tbse_AssignSchedule))
					|| (count >= maxBuildTries))
				throw;
		}
	}

	throw ASIException("buildTeamSchedule: exhasted retries");
}

/******************************************************************************/

void TBuildSchedule::newSchedule( TTeamVector& teamList, short gamesPerTeam,
	short divisionFactor, short nonDivisionFactor )
{
	clear();
	fTeamList = &teamList;
	fGamesPerTeam = gamesPerTeam;
	fDivisionFactor = divisionFactor;
	fNonDivisionFactor = nonDivisionFactor;
}

/******************************************************************************/

// function ASSUMES nothing has been allocated
void TBuildSchedule::clear( void )
{
	// clear team data
	fTeamList = NULL;
	fGamesPerTeam = 0;
	fEastTeamList.erase( fEastTeamList.begin(), fEastTeamList.end() );
	fEastCount = 0;
	fWestTeamList.erase( fWestTeamList.begin(), fWestTeamList.end() );
	fWestCount = 0;

	// clear all league games
	fGameList.erase( fGameList.begin(), fGameList.end() );
	fTotalGameCount = 0;

	// ratio of divisional games to non-divisional games
	fDivisionFactor = 1;
	fNonDivisionFactor = 1;
}

/******************************************************************************/

void TBuildSchedule::initialize( void )
{
	static char *		strError = "TBuildSchedule::initialize() failure";
	TBuildScheduleTeam	tempGame;
	short				i, teamCount;

	// invalid data
	if ((fTeamList == NULL) || (fTeamList->size() < 2) || (fEastTeamList.size() != 0) ||
		(fWestTeamList.size() != 0) || (fDivisionFactor < 1) || (fNonDivisionFactor < 1))
		throw BuildScheduleError( strError, tbse_Setup );

	// initialize random number generator seed
	if (!fSeed)
	{
		srand( (unsigned) time(NULL) );
		fSeed = TRUE;
	}

	// calculate total number of games
	teamCount = fTeamList->size();
	fTotalGameCount = fGamesPerTeam * teamCount;
	if (fTotalGameCount & 0x0001)	// make sure all teams play equal number of games
		throw BuildScheduleError( strError, tbse_GameCount );
	fTotalGameCount /= 2;			// two teams per game

	// count teams in each division
	getDivisionCount( fEastCount, fWestCount );

	// fill team info
	for (i=0; i<teamCount; i++)
	{
		tempGame.fillTeamInfo( (*fTeamList)[i], fGamesPerTeam );
		if (((*fTeamList)[i])->getDivision() == div_East)
			fEastTeamList.insert( fEastTeamList.end(), tempGame );
		else
			fWestTeamList.insert( fWestTeamList.end(), tempGame );
	}

	// verify all teams saved
	if ((fEastTeamList.size() != fEastCount) || (fWestTeamList.size() != fWestCount))
		throw BuildScheduleError( strError, tbse_MemErr );

	// create list of games
	fGameList.reserve(fTotalGameCount);
	if (fGameList.capacity() < fTotalGameCount)
		throw BuildScheduleError( strError, tbse_MemErr );
}

/******************************************************************************/

void TBuildSchedule::buildSchedule( TBuildScheduleDayVector& scheduleDayVector )
{
#if 0	//BOB
	// build list of games
	assignDivisionGames( fEastTeamList );
	assignDivisionGames( fWestTeamList );
	assignNonDivisionGames();

	// must assign remaining games starting with division with fewer teams
	if (fEastCount <= fWestCount)
	{
		assignRemainingGames( fEastTeamList, fWestTeamList );
		assignRemainingGames( fWestTeamList, fEastTeamList );
	}
	else
	{
		assignRemainingGames( fWestTeamList, fEastTeamList );
		assignRemainingGames( fEastTeamList, fWestTeamList );
	}

	// fix up schedule if team has imbalance in home games vs away games
	fixHomeAwaySchedule( fEastTeamList, fWestTeamList );
	fixHomeAwaySchedule( fWestTeamList, fEastTeamList );
	
#else

	createGameListFromStaticSchedule();

#endif

	// copy games to schedule
	assignGamesToScheduleDays(scheduleDayVector);
	validateScheduleDays(scheduleDayVector);
}

/******************************************************************************/

void TBuildSchedule::getDivisionCount( short& eastCount, short& westCount )
{
	eastCount = westCount = 0;
	for (TTeamVector::iterator iter=(*fTeamList).begin(); iter!=(*fTeamList).end(); iter++)
		(((*iter)->getDivision() == div_East) ? eastCount : westCount)++;
}

/******************************************************************************/

void TBuildSchedule::assignDivisionGames( TBuildScheduleTeamVector& divisionList )
{
	short	  divisionCount, divisionGames, i, j, k;

	// get number of games against each team in the division
	divisionCount = divisionList.size();
	if ((divisionGames = calcDivGamesPerTeam( divisionCount )) <= 0)
		return;

	// loop through all teams in division
	for (i=0; i<(divisionCount-1); i++)
	{
		TBuildScheduleTeam&	baseTeam = divisionList[i];

		// play game against all other teams in the division
		for (j=i+1; j<divisionCount; j++)
		{
			TBuildScheduleTeam&	otherTeam = divisionList[j];

			// number of games to play
			for (k=0; k<divisionGames; k++)
				addGameBalanced( baseTeam, otherTeam, k, divisionGames );
		}
	}
}

/******************************************************************************/

void TBuildSchedule::assignNonDivisionGames( void )
{
	short	nonDivisionGames, i, j, k, eastCount, westCount;

	// get number of games against each team in the other division
	if ((nonDivisionGames = calcNonDivGamesPerTeam()) <= 0)
		return;

	// get team count
	eastCount = fEastTeamList.size();
	westCount = fWestTeamList.size();

	// loop through all teams in division
	for (i=0; i<eastCount; i++)
	{
		TBuildScheduleTeam&	baseTeam = fEastTeamList[i];

		// play game against all teams in the other division
		for (j=0; j<westCount; j++)
		{
			TBuildScheduleTeam&	otherTeam = fWestTeamList[j];

			// number of games to play
			for (k=0; k<nonDivisionGames; k++)
				addGameBalanced( baseTeam, otherTeam, k, nonDivisionGames );
		}
	}
}

/******************************************************************************/

/*
	This is the most difficult part of the algorithm.  It attempts to assign
	as many non-divisional games as possible while balancing home games
	and not producing duplicate games.  A secondary goal is to have each
	team play a different set of opponents.  To achieve this, one iterates
	through each team and assigns a game.  The opponent is chosen based on the
	number of games remaining (at the start of this algorithm, each team in
	the division has the same number of games remaining).  The secondary
	criteria is a difference in the home game / away game ratio.
*/
void TBuildSchedule::assignRemainingGames( TBuildScheduleTeamVector& divisionList,
	TBuildScheduleTeamVector& nonDivisionList )
{
	static char *   	strError = "TBuildSchedule::assignRemainingGames() failure";
	TBuildScheduleTeam	* otherTeam;
	short				i, totalGamesLeft, divisionCount;

	// size of divisions
	divisionCount = divisionList.size();

	// iterate through each team in the division
	do
	{
		totalGamesLeft = 0;

		for (i=0; i<divisionCount; i++)
		{
			TBuildScheduleTeam&	baseTeam = divisionList[i];

			// no more games for this team
			if (!baseTeam.getGamesAvailable())
				continue;

			// search other division for opponent
			otherTeam = findOpponent( baseTeam, nonDivisionList );

			// search this division for opponent
			if (otherTeam == NULL)
				otherTeam = findOpponent( baseTeam, divisionList );

			// cannot find opponent
			if (otherTeam == NULL)
				throw BuildScheduleError( strError, tbse_NoOpponent );

			addGameRandom( baseTeam, *otherTeam );
			totalGamesLeft += baseTeam.getGamesAvailable();
		}
	} while (totalGamesLeft > 0);

	// verify all games have been assigned
	for (i=0; i<divisionCount; i++)
	{
		TBuildScheduleTeam&	baseTeam = divisionList[i];

		if (baseTeam.getGamesAvailable() != 0)
			throw BuildScheduleError( strError, tbse_GamesRemain );
	}
}

/******************************************************************************/

// try to find non-division game where home and away game count differs
TBuildScheduleTeam * TBuildSchedule::findOpponent( TBuildScheduleTeam& baseTeam,
	TBuildScheduleTeamVector& teamList )
{
	TBuildScheduleTeam	* match = NULL;
	short				i, teamCount;

	teamCount = teamList.size();
	for (i=0; i<teamCount; i++)
	{
		TBuildScheduleTeam&	elem = teamList[i];

		// cannot play against oneself
		if (baseTeam.getTeamID() == elem.getTeamID())
			continue;

		// opponent has games to be assigned
		if (elem.getGamesAvailable())
		{
			// found an opponent
			if (match == NULL)
				match = &elem;

			// this team has more games available than previous match
			else if (elem.getGamesAvailable() > match->getGamesAvailable())
				match = &elem;

			// home game to away game ratio differs
			else if (match->getHomeGameDifference() == baseTeam.getHomeGameDifference())
				match = &elem;

			// choose a different opponent than the last one
			else if (baseTeam.getLastOpponentID() == match->getTeamID())
				match = &elem;

			// everything else being the same, randomly decide
			else if ((rand() % 2) == 1)
				match = &elem;
		}
	}

	return (match);
}

/******************************************************************************/

short TBuildSchedule::calcDivGamesPerTeam( short divisionCount )
{
	short	nonDivisionGames, remainGames, divisionGames;

	// total games against each non-divisional team
	nonDivisionGames = calcNonDivGamesPerTeam();

	// number of remaining games after removing non-divisional games
	remainGames = fGamesPerTeam - (nonDivisionGames * (fTeamList->size() - divisionCount));

	// total games against each divisional team (do not count ourselves)
	divisionCount--;
	divisionGames = (divisionCount > 0) ? (remainGames / divisionCount) : 0;
	return (divisionGames);
}

/******************************************************************************/

/*
	This function must account for the possibility of a different number
	of teams per division.  We calculate the number of non-divisional ganes
	strictly based on the ratio of divisional to non-divisional games.  This
	is done for each division.  Since the divisions may have a different number
	of teams, and the number of non-divisional games per team must match between
	divisions, we use the minimum of these two calculations.
*/
short TBuildSchedule::calcNonDivGamesPerTeam( void )
{
	short	multEast, multWest, mult;

	multEast = calcRatioMultiplier( fEastCount );
	multWest = calcRatioMultiplier( fWestCount );
	mult = min(multEast,multWest);

	return (fNonDivisionFactor * mult);
}

/******************************************************************************/

short TBuildSchedule::calcRatioMultiplier( short divisionCount )
{
	short	nonDivisionCount, ratioUnit;

	nonDivisionCount = fTeamList->size() - divisionCount;
	ratioUnit = fDivisionFactor * (divisionCount - 1) + fNonDivisionFactor *
		nonDivisionCount;
	return ((ratioUnit > 0) ? (fGamesPerTeam / ratioUnit) : 0);

//BOB I tried to see if rounding was causing a side effect, but it appears not.
//BOB 	return ((ratioUnit > 0) ?
//BOB 		(short)floor(((double)fGamesPerTeam / (double)ratioUnit) + 0.5) : 0);
}

/******************************************************************************/

void TBuildSchedule::addGameBalanced( TBuildScheduleTeam& teamOne, TBuildScheduleTeam& teamTwo,
	short index, short maxIndex )
{
	// alternating home and away teams
	if ((maxIndex > 0) && ((index != (maxIndex-1)) || !(maxIndex & 0x0001)))
	{
		// odd index means team 2 is home team
		if (index & 0x0001)
			addGame( teamTwo, teamOne );
		else
			addGame( teamOne, teamTwo );
		return;
	}

	// last game of series with odd number of games is determined randomly
	addGameRandom( teamOne, teamTwo );
}

/******************************************************************************/

void TBuildSchedule::addGameRandom( TBuildScheduleTeam& teamOne, TBuildScheduleTeam& teamTwo )
{
	short	teamOneDiff, teamTwoDiff;

	// compare home games and away games played
	teamOneDiff = teamOne.getHomeGameDifference();
	teamTwoDiff = teamTwo.getHomeGameDifference();

	// team with more away games is home team
	if (teamOneDiff < teamTwoDiff)
		addGame( teamOne, teamTwo );
	else if (teamOneDiff > teamTwoDiff)
		addGame( teamTwo, teamOne );

	// randomly determine home team
	else if ((rand() % 2) == 1)
		addGame( teamTwo, teamOne );
	else
		addGame( teamOne, teamTwo );
}

/******************************************************************************/

void TBuildSchedule::addGame( TBuildScheduleTeam& homeTeam,
	TBuildScheduleTeam& visitTeam )
{
	static char *	strError = "TBuildSchedule::addGame() failure";
	TBuildScheduleGame	game;

	// programming error
	if (fGameList.size() >= fTotalGameCount)
		throw BuildScheduleError( strError, tbse_GameListFull );

	// use next game in list
//BOB not used	game.setGameNo( fGameList.size() + 1 );

	// add home team
	game.setHomeTeamID( homeTeam.getTeamID() );
	if (!homeTeam.addHomeGame())
		throw BuildScheduleError( strError, tbse_TeamGameCount );
	homeTeam.setLastOpponentID( visitTeam.getTeamID() );

	// add away team
	game.setVisitTeamID( visitTeam.getTeamID() );
	if (!visitTeam.addAwayGame())
		throw BuildScheduleError( strError, tbse_TeamGameCount );
	visitTeam.setLastOpponentID( homeTeam.getTeamID() );

	// add game to list
	fGameList.insert( fGameList.end(), game );
}

/******************************************************************************/

/*
	The scheduling algorithm is not perfect.  It sometimes leads to a difference
	between the number of home games and away games for a couple of teams.  This
	function locates those differences and adjusts the schedule to balance home
	games and away games.  This function assumes that a one game correction will
	balance the home / away game difference.
*/

void TBuildSchedule::fixHomeAwaySchedule( TBuildScheduleTeamVector& divisionList,
	TBuildScheduleTeamVector& nonDivisionList )
{
	int	i, j, diff, divisionCount, nonDivisionCount;

	// Ignore if odd number of games per team since home game count always differs
	// from away game count.
	if (fGamesPerTeam & 0x0001)
		return;

	// teams per division
	divisionCount = divisionList.size();
	nonDivisionCount = nonDivisionList.size();

	// find team with game imbalance
	for (i=0; i<divisionCount; i++)
	{
		TBuildScheduleTeam&	baseTeam = divisionList[i];

		// find team with difference between home and away games
		if ((diff = baseTeam.getHomeGameDifference()) != 0)
		{
			DEBUG_PRINT( if(abs(diff) != 2)
				CommErrMsg(cel_Info,"Difference = %d",(int)diff); );

			// search non-division list for team to adjust
			for (j=0; j<nonDivisionCount; j++)
			{
				TBuildScheduleTeam&	otherTeam = nonDivisionList[j];

				if ((diff > 0) && (otherTeam.getHomeGameDifference() < 0))
				{
					fixOneHomeGame( baseTeam, otherTeam );
					break;
				}
				else if ((diff < 0) && (otherTeam.getHomeGameDifference() > 0))
				{
					fixOneHomeGame( otherTeam, baseTeam );
					break;
				}
			}
		}

		// no match in non-division adjustment
		if ((diff = baseTeam.getHomeGameDifference()) != 0)
		{
			// search division list for team to adjust
			for (j=0; j<divisionCount; j++)
			{
				TBuildScheduleTeam&	otherTeam = divisionList[j];

				// ignore this team
				if (baseTeam.getTeamID() == otherTeam.getTeamID())
					continue;

				if ((diff > 0) && (otherTeam.getHomeGameDifference() < 0))
				{
					fixOneHomeGame( baseTeam, otherTeam );
					break;
				}
				else if ((diff < 0) && (otherTeam.getHomeGameDifference() > 0))
				{
					fixOneHomeGame( otherTeam, baseTeam );
					break;
				}
			}
		}

		// The algorithm to adjust the home game count may fail if either the
		// team with more home games does not play the team with more away games
		// or the only games played between these two teams is already home games
		// for the team with less home games than away games.

		// An iterative algorithm can be applied here where we try to find common
		// opponents between the above described teams.  These games would then be
		// modified such that all teams involved have the same number of home and
		// away games.

		DEBUG_PRINT( baseTeam.print(); );
		if (baseTeam.getHomeGameDifference() != 0)
			throw BuildScheduleError( "TBuildSchedule::fixHomeAwaySchedule() failure", tbse_HomeAwayDiff );
	}
}

/******************************************************************************/

void TBuildSchedule::fixOneHomeGame( TBuildScheduleTeam& homeTeam,
	TBuildScheduleTeam& visitTeam )
{
	short	i;

	// search all games for the first home / away team match
	for (i=0; i<fTotalGameCount; i++)
	{
		// found match
		if ((fGameList[i].getHomeTeamID() == homeTeam.getTeamID()) &&
			(fGameList[i].getVisitTeamID() == visitTeam.getTeamID()))
		{
			fGameList[i].setHomeTeamID( visitTeam.getTeamID() );
			fGameList[i].setVisitTeamID( homeTeam.getTeamID() );
			homeTeam.adjustGame(-1);
			visitTeam.adjustGame(1);
			break;
		}
	}
}

/******************************************************************************/

void TBuildSchedule::assignGamesToScheduleDays(
	TBuildScheduleDayVector& scheduleDayVector)
{
	TBuildScheduleDayVector::iterator dayIter;
	TBuildScheduleGameVector::iterator gameIter;
	int gamesPerDay;

	// place games in random order
//BOB	std::random_shuffle(fGameList.begin(),fGameList.end());

	// Setup empty schedule of all game days.
	scheduleDayVector.erase(scheduleDayVector.begin(),scheduleDayVector.end());
	for(int i = 0; i < fGamesPerTeam; i++)
		scheduleDayVector.push_back(TBuildScheduleDay());

	//Loop though fGameList and assign games to schedule days must check for
	// duplicate teams.
	for(gameIter = fGameList.begin(); gameIter != fGameList.end(); gameIter++)
	{
		bool gameWasAssigned = false;

		// Find open schedule day
		for(dayIter = scheduleDayVector.begin();
			dayIter != scheduleDayVector.end(); dayIter++)
		{
			TBuildScheduleDay& scheduleDay = *dayIter;
			TBuildScheduleGameVector& dayGameVector = scheduleDay.gameVector();
			TBuildScheduleGameVector::iterator dayGameIter;
			
			bool teamAlreadyAssigned = false;
			
			for(dayGameIter = dayGameVector.begin();
				dayGameIter != dayGameVector.end(); dayGameIter++)
			{
				if((gameIter->getHomeTeamID() == dayGameIter->getHomeTeamID()) ||
					(gameIter->getHomeTeamID() == dayGameIter->getVisitTeamID()) ||
					(gameIter->getVisitTeamID() == dayGameIter->getHomeTeamID()) ||
					(gameIter->getVisitTeamID() == dayGameIter->getVisitTeamID()))
				{
					teamAlreadyAssigned = true;
					break;
				}
			}

			if(!teamAlreadyAssigned)
			{
				dayGameVector.push_back(*gameIter);
				gameWasAssigned = true;
				break;
			}
		}

		if(!gameWasAssigned)
		{
			CommErrMsg(cel_Error,"TBuildSchedule::assignGamesToScheduleDays: Could not assign game:");
			DEBUG_PRINT( (*gameIter).print(); );
			throw BuildScheduleError("TBuildSchedule::assignGamesToScheduleDays: "
				"could not assign game to any schedule day",tbse_AssignSchedule);
		}
	}

	// Randomize resulting schedlueDays
	//BOB std::random_shuffle(scheduleDayVector.begin(),scheduleDayVector.end());

	DEBUG_PRINT( scheduleDayVector.print(); );
	
	// Validate resulting schedule day vector.
	gamesPerDay = fTotalGameCount / fGamesPerTeam;
	for(dayIter = scheduleDayVector.begin();
		dayIter != scheduleDayVector.end(); dayIter++)
	{
		TBuildScheduleDay& scheduleDay = *dayIter;
			
		if(scheduleDay.gameVector().size() != gamesPerDay)
			throw BuildScheduleError("TBuildSchedule::assignGamesToScheduleDays: "
				"scheduleDay.gameVector().size() != gamesPerDay",tbse_AssignSchedule);
	}
}

/******************************************************************************/

//BOB add code to TTeamByIDVector to copy from a TTeamVector
	struct teamSortCompare
	{
		bool operator() (const TTeamPtr& x, const TTeamPtr& y) const
			{ return x->getTeamID() < y->getTeamID(); }
	};

	struct teamIDSearch
	{
		bool operator()(const TTeamPtr& x, const TTeamID& y) const
			{ return x->getTeamID() < y; }
	};
	
	TTeamPtr teamGetByID(const TTeamVector& teamVector,TTeamID teamID)
	{
		TTeamVector::const_iterator iter = std::lower_bound(
			teamVector.begin(),teamVector.end(),teamID,teamIDSearch());
		
		if(iter != teamVector.end())
			return(*iter);
		
		return(NULL);
	}
//BOB add code to TTeamByIDVector to copy from a TTeamVector
	
void TBuildSchedule::validateScheduleDays(
	TBuildScheduleDayVector& scheduleDayVector)
{
	TTeamVector::const_iterator teamIter;
	TBuildScheduleDayVector::const_iterator dayIter;
	int homeGames, awayGames, divGames, nonDivGames;

	sort(fTeamList->begin(),fTeamList->end(),teamSortCompare());
	
	for(teamIter = fTeamList->begin(); teamIter != fTeamList->end(); teamIter++)
	{
		const TTeamPtr& teamPtr = *teamIter;
		homeGames = awayGames = divGames = nonDivGames = 0;
		
		DEBUG_PRINT( CommErrMsg(cel_Info,"TeamID: %5s",teamPtr->getTeamID().c_str()); );

		for(dayIter = scheduleDayVector.begin();
			dayIter != scheduleDayVector.end(); dayIter++)
		{
			const TBuildScheduleGameVector& dayGameVector = (*dayIter).gameVector();
			TBuildScheduleGameVector::const_iterator dayGameIter;
			
			for(dayGameIter = dayGameVector.begin();
				dayGameIter != dayGameVector.end(); dayGameIter++)
			{
				bool isInGame = false;
				TTeamID oppTeamID;
				
				if(teamPtr->getTeamID() == dayGameIter->getHomeTeamID())
				{
					homeGames++;
					isInGame = true;
					oppTeamID = dayGameIter->getVisitTeamID();

					DEBUG_PRINT( CommErrMsg(cel_Info,"  vs. %s",oppTeamID.c_str()); );
				}
				else if(teamPtr->getTeamID() == dayGameIter->getVisitTeamID())
				{
					awayGames++;
					isInGame = true;
					oppTeamID = dayGameIter->getHomeTeamID();

					DEBUG_PRINT( CommErrMsg(cel_Info,"  at  %s",oppTeamID.c_str()); );
				}
				
				if(isInGame)
				{
					TTeamPtr oppTeamPtr = teamGetByID(*fTeamList,oppTeamID);
					
					if(teamPtr->getDivision() == oppTeamPtr->getDivision())
						divGames++;
					else
						nonDivGames++;
				}
			}
		}

		DEBUG_PRINT( CommErrMsg(cel_Info,"  H: %2d  A: %2d  D: %2d  N: %2d",
			homeGames,awayGames,divGames,nonDivGames); );
	}
}

/******************************************************************************/

void TBuildSchedule::createGameListFromStaticSchedule()
{
	TBuildScheduleTeamVector teamVector;
	StaticBuildScheduleGame* gameList;
	int i,numGames;

	gameList = getStaticScheduleGameList(fTeamList->size(),numGames);

	if(numGames != fTotalGameCount)
		throw ASIException("TBuildSchedule::createGameListFromStaticSchedule: numGames != fTotalGameCount");

	teamVector.resize(fEastTeamList.size() + fWestTeamList.size());
	copy(fEastTeamList.begin(),fEastTeamList.end(),teamVector.begin());
	copy(fWestTeamList.begin(),fWestTeamList.end(),
		teamVector.begin() + fEastTeamList.size());

	DEBUG_PRINT( for(int i = 0; i < teamVector.size(); i++)
		CommErrMsg(cel_Info,"teamVector[%d] = %s",i,teamVector[i].getTeamID().c_str()); );

		
	for(i = 0; i < numGames; i++)
	{		
		TBuildScheduleGame game;

		game.setHomeTeamID(teamVector[gameList[i].fHomeOffset].getTeamID());
		game.setVisitTeamID(teamVector[gameList[i].fVisitOffset].getTeamID());

		fGameList.push_back(game);
	}
}

/******************************************************************************/
/******************************************************************************/

void TBuildScheduleGame::print() const
{
#if defined(DEBUG_PRINT_ON)
	CStr127 msg;

//	msg.CopyVarg("Game %3d  ",fGameNo);
	msg.ConcatVarg("Home Team ID: %5s  ",fHomeTeamID.c_str());
	msg.ConcatVarg("Visit Team ID: %5s",fVisitTeamID.c_str());
	
	CommErrMsg(cel_Info,msg);
#endif
}

/******************************************************************************/
/******************************************************************************/

void TBuildScheduleDay::print() const
{
#if defined(DEBUG_PRINT_ON)
	TBuildScheduleGameVector::const_iterator iter;
	CStr127 msg;

	for(iter = fGameVector.begin(); iter != fGameVector.end(); iter++)
	{
		msg.ConcatVarg("  %5s at ",(*iter).getVisitTeamID().c_str());
		msg.ConcatVarg("%5s",(*iter).getHomeTeamID().c_str());
		msg.Concat("    ");
		
	}
	
	CommErrMsg(cel_Info,msg);
#endif
}

/******************************************************************************/

void TBuildScheduleDayVector::print() const
{
#if defined(DEBUG_PRINT_ON)
	TBuildScheduleDayVector::const_iterator iter;
	int day = 1;

	for(iter = begin(); iter != end(); iter++)
	{
		CommErrMsg(cel_Info,"Day: %d",day++);
		(*iter).print();
	}
#endif
}

/******************************************************************************/

};

/******************************************************************************/
/******************************************************************************/

