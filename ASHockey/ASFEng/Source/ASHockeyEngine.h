/* ASHockeyEngine.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyEngineH
#define ASHockeyEngineH

#include "ASHockeyAppOptions.h"
#include "ASHockeyObjectStore.h"
#include "ASFantasyEngine.h"

namespace ashockey
{

/******************************************************************************/

class ASHockeyEngine : public ASFantasyEngine
{
protected:
//BOB	ASHockeyObjectStore& fHockeyStore;
	
public:
	ASHockeyEngine() : ASFantasyEngine("ASHockey Engine Service") {}
	virtual ~ASHockeyEngine() {}

protected:
	virtual DirSpec getHomeDir() { return(ASHockeyHomeDir()); }
	virtual CStrVar getBackupDatabaseName() { return("ASHockeyBackup"); }
	virtual CStrVar getBackupFilePrefix() { return("ASHockey"); }
	virtual CStrVar getBackupFileName() { return("ASHockeyBackup.gdb"); }
	virtual CStrVar getEmptyBackupFileName() { return("ASHockeyEmpty.gdb"); }
	virtual void fillBackupDatabaseTableVector(
		TDatabaseTableVector& databaseTableVector);

	virtual void getStatFilesForLoading(
		StatFileLoaderVector& statFileLoaderVector);
	virtual bool shouldProfPlayersLastWeeksPointsBeCleared();
	virtual bool shouldStatSummariesBeCreated();
	virtual void createStatSummaries(const TDateTime asOfDate);
	virtual void getSeasonDateRangeForStatPeriod(const TStatPeriod statPeriod,
		TDateTime& fromDate,TDateTime& toDate);

	virtual void createSeasonSchedule();
	virtual void createDefaultLineup(const TLeaguePtr& leaguePtr,
		TDraftResultPtr draftResultPtr);

	virtual bool areGameResultsCreatedNextDay() const { return(false); }
	virtual void loadGameStatPlayerIDVectorForTeam(const TTeamID teamID,
		const bool isOffense,TPlayerIDVector& playerIDVector);

	// Playoffs
	virtual int getNumOfPlayoffGameStatsPerPlayerByPosition(const int position,
		const int playoffDay);

	// Team/Player Adjustments
	virtual bool isTeamsLineupStillValid(TTeamID teamID) const;
	virtual void removePlayerFromTeamsLineups(TTeamID teamID,TPlayerID playerID) const;
};

/******************************************************************************/

}; //ashockey

#endif //ASHockeyEngineH
/******************************************************************************/
/******************************************************************************/
