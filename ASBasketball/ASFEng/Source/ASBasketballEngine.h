/* ASBasketballEngine.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballEngineH
#define ASBasketballEngineH

#include "ASBasketballAppOptions.h"
#include "ASBasketballObjectStore.h"
#include "ASFantasyEngine.h"

namespace asbasketball
{

/******************************************************************************/

class ASBasketballEngine : public ASFantasyEngine
{
protected:
//BOB	ASBasketballObjectStore& fBasketballStore;
	
public:
	ASBasketballEngine() : ASFantasyEngine("ASBasketball Engine Service") {}
	virtual ~ASBasketballEngine() {}

protected:
	virtual DirSpec getHomeDir() { return(ASBasketballHomeDir()); }
	virtual CStrVar getBackupDatabaseName() { return("ASBasketballBackup"); }
	virtual CStrVar getBackupFilePrefix() { return("ASBasketball"); }
	virtual CStrVar getBackupFileName() { return("ASBasketballBackup.gdb"); }
	virtual CStrVar getEmptyBackupFileName() { return("ASBasketballEmpty.gdb"); }
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

}; //asbasketball

#endif //ASBasketballEngineH
/******************************************************************************/
/******************************************************************************/
