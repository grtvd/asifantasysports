/* ASFootballEngine.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballEngineH
#define ASFootballEngineH

#include "ASFootballAppOptions.h"
#include "ASFootballObjectStore.h"
#include "ASFantasyEngine.h"

namespace asfootball
{

/******************************************************************************/

class ASFootballEngine : public ASFantasyEngine
{
protected:
	ASFootballObjectStore& fFootballStore;
	
public:
	ASFootballEngine() : ASFantasyEngine("ASFootball Engine Service"),
		fFootballStore(ASFootballObjectStore::getThe()) {}
	virtual ~ASFootballEngine() {}

protected:
	virtual DirSpec getHomeDir() { return(ASFootballHomeDir()); }
	virtual CStrVar getBackupDatabaseName() { return("ASFootballBackup"); }
	virtual CStrVar getBackupFilePrefix() { return("ASFootball"); }
	virtual CStrVar getBackupFileName() { return("ASFootballBackup.gdb"); }
	virtual CStrVar getEmptyBackupFileName() { return("ASFootballEmpty.gdb"); }
	virtual void fillBackupDatabaseTableVector(
		TDatabaseTableVector& databaseTableVector);

	virtual void addAllShelves();
	virtual void delAllShelves();
	virtual void loadShelvesForStatLoad();
	virtual void unloadShelvesForStatLoad();
	virtual void loadShelvesForProcessing();
	virtual void unloadShelvesForProcessing();
	
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

	virtual bool areGameResultsCreatedNextDay() const { return(true); }
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

}; //asfootball

#endif //ASFootballEngineH
/******************************************************************************/
/******************************************************************************/
