/* ASBaseballEngine.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballEngineH
#define ASBaseballEngineH

#include "ASBaseballAppOptions.h"
#include "ASBaseballObjectStore.h"
#include "ASFantasyEngine.h"

namespace asbaseball
{

/******************************************************************************/

class ASBaseballEngine : public ASFantasyEngine
{
protected:
//BOB	ASBaseballObjectStore& fBaseballStore;
	
public:
	ASBaseballEngine() : ASFantasyEngine("ASBaseball Engine Service") {}
	virtual ~ASBaseballEngine() {}

protected:
	virtual DirSpec getHomeDir() { return(ASBaseballHomeDir()); }
	virtual CStrVar getBackupDatabaseName() { return("ASBaseballBackup"); }
	virtual CStrVar getBackupFilePrefix() { return("ASBaseball"); }
	virtual CStrVar getBackupFileName() { return("ASBaseballBackup.gdb"); }
	virtual CStrVar getEmptyBackupFileName() { return("ASBaseballEmpty.gdb"); }
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

}; //asbaseball

#endif //ASBaseballEngineH
/******************************************************************************/
/******************************************************************************/
