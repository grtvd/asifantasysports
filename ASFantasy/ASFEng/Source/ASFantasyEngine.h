/* ASFantasyEngine.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyEngineH
#define ASFantasyEngineH

#include "CommDB.h"
#include "NTService.h"

#include "ASFantasyType.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyStatFileLoader.h"
#include "ASFantasyEngineNotify.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyEngine : public TNTService
{
protected:
	ASFantasyObjectStore& fStore;

	TLeaguePtr fCurLeaguePtr;
	
protected:
	ASFantasyEngine(const char* serviceName) : TNTService(serviceName),
		fStore(ASFantasyObjectStore::getThe()) {}
	virtual ~ASFantasyEngine() {}

	void run();
	#if defined(TEST_SERVICE)
	virtual DWORD runIdleWaitTenths() { return(20); }
	#endif

	virtual DirSpec getHomeDir() = 0;
	virtual CStrVar getBackupDatabaseName() = 0;
	virtual CStrVar getBackupFilePrefix() = 0;
	virtual CStrVar getBackupFileName() = 0;
	virtual CStrVar getEmptyBackupFileName() = 0;
	virtual void fillBackupDatabaseTableVector(
		TDatabaseTableVector& databaseTableVector) = 0;
	void backupDatabase();
	void waitForASMemberBackup();

	virtual void addAllShelves();
	virtual void delAllShelves();
	virtual void loadShelvesForStatLoad();
	virtual void unloadShelvesForStatLoad();
	virtual void loadShelvesForProcessing();
	virtual void unloadShelvesForProcessing();
	
	bool beginProcessing();
	void endProcessing();

	void processStatFiles();
	virtual void getStatFilesForLoading(
		StatFileLoaderVector& statFileLoaderVector) = 0;
	void waitForStatFiles(const StatFileLoaderVector& statFileLoaderVector);
	virtual bool shouldProfPlayersLastWeeksPointsBeCleared() = 0;
	void clearAllProfPlayersLastWeeksPoints();
	void loadSingleStatFile(StatFileLoaderPtr loader);
	virtual bool shouldStatSummariesBeCreated() = 0;
	virtual void createStatSummaries(const TDateTime asOfDate) = 0;
	virtual void getSeasonDateRangeForStatPeriod(const TStatPeriod statPeriod,
		TDateTime& fromDate,TDateTime& toDate) = 0;

	void processAllLeagues();
	void processOneLeague(TLeaguePtr& leaguePtr);
	void processEnrollmentLeague(TLeaguePtr& leaguePtr);
	void processPreDraftLeague(TLeaguePtr& leaguePtr);
	void processDraftLeague(TLeaguePtr& leaguePtr);
	void processPreSeasonLeague(TLeaguePtr& leaguePtr);
	void processSeasonLeague(TLeaguePtr& leaguePtr);
	void processPlayoffLeague(TLeaguePtr& leaguePtr);

	void getPremiumParticVector(TParticVector& particVector);

	virtual void createSeasonSchedule() = 0;
	void calcSeasonDate();
	virtual void createDefaultLineup(const TLeaguePtr& leaguePtr,
		TDraftResultPtr draftResultPtr) = 0;

	virtual bool areGameResultsCreatedNextDay() const = 0;
	void startGames(TLeaguePtr leaguePtr,TScheduleDayPtr scheduleDayPtr,
		TGameResultVector& gameResultVector);
	TGameResultPtr createNewGameResultForTeam(TLeaguePtr leaguePtr,
		TScheduleDayPtr scheduleDayPtr,const TTeamID teamID,const TTeamID oppTeamID);
	virtual void loadGameStatPlayerIDVectorForTeam(const TTeamID teamID,
		const bool isOffense,TPlayerIDVector& playerIDVector) = 0;

	void updateGames(TLeaguePtr leaguePtr,TScheduleDayPtr scheduleDayPtr,
		TGameResultVector& gameResultVector,const bool inPlayoffs);
	void updateGameResultWithGameStatsFromObjectStore(
		TGameResultPtr gameResultPtr,const bool inPlayoffs);

	virtual void resolveGames(TLeaguePtr& leaguePtr,
		TScheduleDayPtr& scheduleDayPtr,const bool inPlayoffs);
	void updateTeamStats(const TScheduleDayGame& scheduleDayGame);
	void calcLeagueStandings();

	// Playoffs
	void setupForSemiFinalPlayoffs();
	void setupForFinalPlayoffs(TScheduleDayPtr scheduleDayPtr);
	void setPlayoffsLeagueChamp(TScheduleDayPtr scheduleDayPtr);
	void setSemiFinalPlayoffSchedule();
	void setFinalPlayoffSchedule();

	void determinePlayoffGameStats(const TGameResultVector& gameResultVector,const int playoffDay);
	void determinePlayoffOffGameStatsForGameResult(
		TGameResultPtr gameResultPtr,const int playoffDay);
	void determinePlayoffDefGameStatsForGameResult(
		TGameResultPtr gameResultPtr,const int playoffDay);
	virtual int getNumOfPlayoffGameStatsPerPlayerByPosition(const int position,
		const int playoffDay = 0) = 0;

	// Team/Player Adjustments
	void verifyRosters();
	virtual bool isTeamsLineupStillValid(TTeamID teamID) const = 0;
	bool isPlayerInGameResultLineup(TTeamID teamID,TPlayerID playerID,
		const TGameResultVector& gameResultVector) const;
	virtual bool isAnyPlayerIDFromVectorInTeamsGameResultLineups(TTeamID teamID,
		const TGameResultVector& gameResultVector,
		const TPlayerIDVector& playerIDVector) const;

	virtual void removePlayerFromTeamsLineups(TTeamID teamID,
		TPlayerID playerID) const = 0;
	virtual void movePlayerToTeam(TPlayerID playerID,TTeamID teamID) const;
	virtual void movePlayerIDVectorToTeam(const TPlayerIDVector& playerIDVector,
		TTeamID teamID) const;
	virtual void releasePlayerToFreeAgency(TPlayerID playerID) const;
	virtual void releasePlayerIDVectorToFreeAgency(
		const TPlayerIDVector& playerIDVector,int numToRelease) const;

	// Trade Processing
	void processTrades(TTradeVector& tradeVector,
		const TGameResultVector& gameResultVector) const;
	void validateTrades(TTradeVector& tradeVector) const;
	bool isTradeStillValid(TTradePtr tradePtr) const;
	bool hasTradeExpired(TTradePtr tradePtr) const;
	bool hasTradeBeenProtested(TTradePtr tradePtr) const;
	bool hasTradeProtestPeriodPast(TTradePtr tradePtr) const;
	bool isPlayerActiveInTrade(const TPlayerPtr& playerPtr,
		const TTradePtr& tradePtr) const;
	bool isPlayerActiveInAnyTrade(TPlayerID playerID,
		TTradeVector& tradeVector) const;
	bool areAnyTradePlayersLocked(TTradePtr tradePtr,
		const TGameResultVector& gameResultVector) const;
	void performActualTrade(TTradePtr tradePtr) const;

	// Free Agent Claim Processing
	void addNewPlayersToFreeAgency(TLeaguePtr& leaguePtr,bool includePrevious);

	void processFreeAgentClaims(TTradeVector& tradeVector,
		const TGameResultVector& gameResultVector);
	void validateFreeAgentClaims() const;
	bool isFreeAgentClaimStillValid(TFreeAgentClaimPtr freeAgentClaimPtr) const;
	bool isFreeAgentReleasePlayerLocked(TFreeAgentClaimPtr freeAgentClaimPtr,
		const TGameResultVector& gameResultVector) const;

	// Emails
	void sendDraftUpcomingEmail();
	void sendNewFreeAgentsEmail();
	void sendGameResultsEmail(TScheduleDayPtr& scheduleDayPtr);
	void sendLeagueChampEmail();
};

/******************************************************************************/

}; //asfantasy

#endif //ASFantasyEngineH
/******************************************************************************/
/******************************************************************************/
