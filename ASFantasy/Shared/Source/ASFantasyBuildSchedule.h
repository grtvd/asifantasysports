/* ASFantasyBuildSchedule.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyBuildScheduleH
#define ASFantasyBuildScheduleH

#include <stdexcep.h>
#include <algorith.h>
#include <vector.h>
#include "ASFantasyType.h"

using namespace std;

namespace asfantasy
{

/******************************************************************************/

// Build Schedule Error List
enum tbse_Error
{
	tbse_MemErr,
	tbse_Setup,
	tbse_GameCount,
	tbse_TeamGameCount,
	tbse_NoOpponent,
	tbse_GamesRemain,
	tbse_GameListFull,
	tbse_HomeAwayDiff,
	tbse_AssignSchedule
};

/******************************************************************************/

class BuildScheduleError : public ASIException
{
protected:
	tbse_Error	fError;

public:
	BuildScheduleError(const char* message, tbse_Error error) :
		ASIException("BuildScheduleError: message(%s), error(%d)",message,
		(int)error) { fError = error; }

	tbse_Error getError( void ) { return (fError); }
};

/******************************************************************************/

struct StaticBuildScheduleGame
{
	byte fHomeOffset;
	byte fVisitOffset;
};

/******************************************************************************/

class TBuildScheduleGame
{
private:
	TTeamID		fHomeTeamID;
	TTeamID		fVisitTeamID;

public:
	TBuildScheduleGame()
	{
		fHomeTeamID = 0;
		fVisitTeamID = 0;
	}

	TTeamID		getHomeTeamID( void ) const { return (fHomeTeamID); }
	void		setHomeTeamID( TTeamID teamID ) { fHomeTeamID = teamID; }
	TTeamID		getVisitTeamID( void ) const { return (fVisitTeamID); }
	void		setVisitTeamID( TTeamID teamID ) { fVisitTeamID = teamID; }

	void print() const;
};

typedef vector<TBuildScheduleGame> TBuildScheduleGameVector;

/******************************************************************************/

class TBuildScheduleDay
{
protected:
	TBuildScheduleGameVector fGameVector;

public:
	TBuildScheduleDay() { clear(); }

	void clear() { fGameVector.erase(fGameVector.begin(), fGameVector.end()); }
	
	TBuildScheduleGameVector& gameVector() { return(fGameVector); }
	const TBuildScheduleGameVector& gameVector() const { return(fGameVector); }
	
	void print() const;
};

class TBuildScheduleDayVector : public vector<TBuildScheduleDay>
{
public:
	void print() const;
};

/******************************************************************************/

class TBuildScheduleTeam
{
private:
	TTeamID		fTeamID;			// team ID (unique for each team in the league)
	TDivision	fDivision;			// east or west division
	short		fHomeGames;			// number of home games assigned
	short		fAwayGames;			// number of away games assigned
	short		fGamesAvailable;	// games left to be assigned
	TTeamID		fLastOpponent;		// team ID of last assigned opponent

public:
	TBuildScheduleTeam();

	void		fillTeamInfo( TTeamPtr team, short games );

	short		getGamesAvailable( void ) { return (fGamesAvailable); }
	void		setGamesAvailable( short games ) { fGamesAvailable = games; }

	bool		addHomeGame( void );
	bool		addAwayGame( void );
	void		adjustGame( short amount ) { fHomeGames += amount; fAwayGames -= amount; }
	short		getHomeGameDifference( void ) { return((short)(fHomeGames - fAwayGames)); }

	TTeamID		getTeamID( void ) { return (fTeamID); };
	void		setTeamID( TTeamID teamID ) { fTeamID = teamID; }
	TTeamID		getLastOpponentID( void ) { return (fLastOpponent); };
	void		setLastOpponentID( TTeamID teamID ) { fLastOpponent = teamID; }
	TDivision	getDivision( void ) { return (fDivision); }
	void		setDivision( TDivision division ) { fDivision = division; }

	void print( void );
};

typedef std::vector<TBuildScheduleTeam> TBuildScheduleTeamVector;

/******************************************************************************/

class TBuildSchedule
{
private:
	static bool					fSeed;				// was srand() called

protected:
	TTeamVector *				fTeamList;			// array of teams (do not deallocate)
	short						fGamesPerTeam;		// games each team must play

	TBuildScheduleTeamVector	fEastTeamList;		// array of eastern division teams
	short						fEastCount;			// number of teams in the east
	TBuildScheduleTeamVector	fWestTeamList;		// array of western division teams
	short						fWestCount;			// number of teams in the west

	short						fDivisionFactor;	// ratio of division to non-division games
	short						fNonDivisionFactor;

	TBuildScheduleGameVector	fGameList;			// array of all games on the schedule
	short						fTotalGameCount;	// total number of games in schedule

protected:
	TBuildSchedule();
	TBuildSchedule( TTeamVector& teamList, short gamesPerTeam,
		short divisionFactor = 1, short nonDivisionFactor = 1 );

public:
	void buildTeamSchedule( TTeamVector& teamList,
		TBuildScheduleDayVector& scheduleDayVector, short gamesPerTeam,
		short divisionFactor = 1, short nonDivisionFactor = 1 );

protected:
	void	newSchedule( TTeamVector& teamList, short gamesPerTeam,
				short divisionFactor = 1, short nonDivisionFactor = 1 );
	void 	clear( void );
	void	initialize( void );
	void	buildSchedule( TBuildScheduleDayVector& scheduleDayVector );

	void	getDivisionCount( short& eastCount, short& westCount );
	void	assignDivisionGames( TBuildScheduleTeamVector& divisionList );
	void	assignNonDivisionGames( void );
	void	assignRemainingGames( TBuildScheduleTeamVector& divisionList,
				TBuildScheduleTeamVector& nonDivisionList );

	TBuildScheduleTeam *	findOpponent( TBuildScheduleTeam& baseTeam,
				TBuildScheduleTeamVector& nonDivisionList );

	short	calcDivGamesPerTeam( short divisionCount );
	short	calcNonDivGamesPerTeam( void );
	short	calcRatioMultiplier( short divisionCount );

	void	addGameBalanced( TBuildScheduleTeam& teamOne, TBuildScheduleTeam& teamTwo,
				short index, short maxIndex );
	void	addGameRandom( TBuildScheduleTeam& teamOne, TBuildScheduleTeam& teamTwo );
	void	addGame( TBuildScheduleTeam& homeTeam, TBuildScheduleTeam& visitTeam );

	void	fixHomeAwaySchedule( TBuildScheduleTeamVector& divisionList,
				TBuildScheduleTeamVector& nonDivisionList );
	void	fixOneHomeGame( TBuildScheduleTeam& homeTeam, TBuildScheduleTeam& visitTeam );

	void	assignGamesToScheduleDays(TBuildScheduleDayVector& scheduleDayVector);
	void	validateScheduleDays(TBuildScheduleDayVector& scheduleDayVector);

	void	createGameListFromStaticSchedule();
	virtual StaticBuildScheduleGame* getStaticScheduleGameList(int numTeams,
		int& numGames) = 0;
};

/******************************************************************************/

};	//namespace asfantasy

#endif	//ASFantasyBuildScheduleH
/******************************************************************************/
/******************************************************************************/

