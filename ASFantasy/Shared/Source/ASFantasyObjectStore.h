/* ASFantasyObjectStore.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyObjectStoreH
#define ASFantasyObjectStoreH

#include "ObjectStore.h"
#include "ASFantasyType.h"
#include "ASDraftType.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectShelf.h"

/******************************************************************************/

namespace asfantasy
{

/******************************************************************************/

class ASFantasyObjectStore : public ObjectStore
{
protected:
	ASFantasyObjectStore(ASFantasyObjectBuilder& builder);

public:
	static ASFantasyObjectStore& getThe()
		{ return(dynamic_cast<ASFantasyObjectStore&>(ObjectStore::getThe())); }
	ASFantasyObjectBuilder& getBuilder()
		{ return(dynamic_cast<ASFantasyObjectBuilder&>(fBuilder)); }

	/**************************************************************************/
	
	// Functions to retrieve ObjectShelfKeys
//	virtual ObjectShelfKeyType getLeagueShelfKey(void) = 0;
	virtual ObjectShelfKeyType getTeamShelfKey(void)
		{ return(typeid(TTeamPtr).name()); }
	virtual ObjectShelfKeyType getProfPlayerShelfKey(void)
		{ return(typeid(TProfPlayerPtr).name()); }
	virtual ObjectShelfKeyType getProfTeamShelfKey(void)
		{ return(typeid(TProfTeamPtr).name()); }
	virtual ObjectShelfKeyType getPlayerShelfKey(void)
		{ return(typeid(TPlayerPtr).name()); }
	virtual ObjectShelfKeyType getOffGameStatShelfKey(void)
		{ return(typeid(TOffGameStatPtr).name()); }
	virtual ObjectShelfKeyType getDefGameStatShelfKey(void)
		{ return(typeid(TDefGameStatPtr).name()); }
	virtual ObjectShelfKeyType getDraftRankingShelfKey(void)
		{ return(typeid(TDraftRankingPtr).name()); }
	virtual ObjectShelfKeyType getDraftPosCountShelfKey(void)
		{ return(typeid(TDraftPosCount).name()); }
	virtual ObjectShelfKeyType getScheduleDayShelfKey(void)
		{ return(typeid(TScheduleDayPtr).name()); }
		
	// ObjectShelf Functions
	TeamObjectShelf* getTeamShelf()
		{ return(dynamic_cast<TeamObjectShelf*>(getShelfByKey(getTeamShelfKey(),
			gsm_MustExist))); }
	void addTeamShelf();
	void delTeamShelf() { delShelf(getTeamShelfKey()); }
	void saveAndDelAllTeamShelfItems();

	ProfPlayerObjectShelf* getProfPlayerShelf()
		{ return(dynamic_cast<ProfPlayerObjectShelf*>(
			getShelfByKey(getProfPlayerShelfKey(),gsm_MustExist))); }
	void addProfPlayerShelf();
	void delProfPlayerShelf() { delShelf(getProfPlayerShelfKey()); }
	void delAllProfPlayerShelfItems();

	ProfTeamObjectShelf* getProfTeamShelf()
		{ return(dynamic_cast<ProfTeamObjectShelf*>(
			getShelfByKey(getProfTeamShelfKey(),gsm_MustExist))); }
	void addProfTeamShelf();
	void delProfTeamShelf() { delShelf(getProfTeamShelfKey()); }
	void delAllProfTeamShelfItems();
		
	PlayerObjectShelf* getPlayerShelf()
		{ return(dynamic_cast<PlayerObjectShelf*>(getShelfByKey(getPlayerShelfKey(),
			gsm_MustExist))); }
	void addPlayerShelf();
	void delPlayerShelf() { delShelf(getPlayerShelfKey()); }
	void saveAndDelAllPlayerShelfItems();

	OffGameStatObjectShelf* getOffGameStatShelf()
		{ return(dynamic_cast<OffGameStatObjectShelf*>(getShelfByKey(
			getOffGameStatShelfKey(),gsm_MustExist))); }
	void addOffGameStatShelf();
	void delOffGameStatShelf() { delShelf(getOffGameStatShelfKey()); }
	void delAllOffGameStatShelfItems() { getOffGameStatShelf()->delAllItems(); }

	DefGameStatObjectShelf* getDefGameStatShelf()
		{ return(dynamic_cast<DefGameStatObjectShelf*>(getShelfByKey(
			getDefGameStatShelfKey(),gsm_MustExist))); }
	void addDefGameStatShelf();
	void delDefGameStatShelf() { delShelf(getDefGameStatShelfKey()); }
	void delAllDefGameStatShelfItems() { getDefGameStatShelf()->delAllItems(); }

	void addDraftRankingShelf();
	void delDraftRankingShelf() { delShelf(getDraftRankingShelfKey()); }

	void addDraftPosCountShelf();
	void delDraftPosCountShelf() { delShelf(getDraftPosCountShelfKey()); }

	ScheduleDayObjectShelf* getScheduleDayShelf()
		{ return(dynamic_cast<ScheduleDayObjectShelf*>(getShelfByKey(
			getScheduleDayShelfKey(),gsm_MustExist))); }
	void addScheduleDayShelf();
	void delScheduleDayShelf() { delShelf(getScheduleDayShelfKey()); }
	void saveAndDelAllScheduleDayShelfItems();

	/**************************************************************************/

	// Team Retrieval Functions
	void addTeam(TTeamPtr teamPtr);
	TTeamPtr getTeam(TTeamID teamID,GetItemMode getItemMode = gim_LoadOnCall);
	void delTeam(TTeamID teamID);

	TTeamPtr newTeam();
	void saveTeam(TTeamID teamID);

	// ProfPlayer Retrieval Functions
	void addProfPlayer(TProfPlayerPtr profPlayerPtr);
	TProfPlayerPtr getProfPlayer(TPlayerID playerID,
		GetItemMode getItemMode = gim_MustExist);
	void saveProfPlayer(TPlayerID playerID);
	
	// ProfTeam Retrieval Functions
	void addProfTeam(TProfTeamPtr profTeamPtr);
	TProfTeamPtr getProfTeam(TProfTeamID profTeamID,
		GetItemMode getItemMode = gim_MustExist);
	TProfTeamPtr getProfTeamAbbr(TProfTeamAbbr profTeamAbbr,
		GetItemMode getItemMode = gim_MustExist);
	
	// Player Retrieval Functions
	void addPlayer(TPlayerPtr playerPtr);
	TPlayerPtr getPlayer(TLeagueID leagueID,TPlayerID playerID,
		GetItemMode getItemMode = gim_MustExist);

	TPlayerPtr newPlayer(TLeagueID leagueID,TPlayerID playerID);

	// OffGameStat Retrieval Functions
	void addOffGameStat(TOffGameStatPtr offGameStatPtr);
	
	// DefGameStat Retrieval Functions
	void addDefGameStat(TDefGameStatPtr defGameStatPtr);
	
	// DraftRanking Retrieval Functions
	void addDraftRanking(TDraftRankingPtr draftRankingPtr);
	TDraftRankingPtr getDraftRanking(TTeamID teamID,
		GetItemMode getItemMode = gim_MustExist);
	TDraftRankingPtr getDefaultDraftRanking(GetItemMode getItemMode = gim_MustExist)
		{ return(getDraftRanking(DefaultDraftRankingTeamID,getItemMode)); }

	// DraftPosCount Retrieval Functions
	void storeDraftPosCount(TDraftPosCount& draftPosCount);
	TDraftPosCount getDraftPosCount(TDraftPosCountKey draftPosCountKey);

	// ScheduleDay Retrieval Functions
	void addScheduleDay(TScheduleDayPtr scheduleDayPtr);
	
	/**************************************************************************/
	// Utility Methods

	void loadTeamsForLeague(TLeagueID leagueID);
	void loadProfPlayersByPositionGameStatus(const TPositionVector& posVector,
		const TProfPlayerGameStatus gameStatus);
	void loadKeyProfPlayers();
	void loadAllProfPlayers();
	void loadAllProfTeams();
	void loadPlayersForLeague(TLeagueID leagueID);

	void loadOffGameStatVectorByWhereStr(const char* whereStr);
	void loadOffGameStatVectorByDatePeriod(TDateTime fromStatDate,
		TDateTime toStatDate,TStatPeriod statPeriod);

	void loadDefGameStatVectorByWhereStr(const char* whereStr);
	void loadDefGameStatVectorByDatePeriod(TDateTime fromStatDate,
		TDateTime toStatDate,TStatPeriod statPeriod);

	void loadDraftRankingsForLeague(TLeagueID leagueID);
	void createDraftPosCountsForTeamIDVector(
		const TTeamIDVector& teamIDVector,const TPositionVector& posVector);

	void getTeamIDVector(TTeamIDVector& teamIDVector)
		{ getTeamShelf()->getItemKeyVector(teamIDVector); }
	void getTeamVector(TTeamVector& teamVector)
		{ getTeamShelf()->getItemVector(teamVector); }

	void getProfPlayerIDVector(TPlayerIDVector& playerIDVector)
		{ getProfPlayerShelf()->getItemKeyVector(playerIDVector); }
	void getProfPlayerIDVectorByNewPlayerDateRange(TDateTime fromDate,
		TDateTime toDate,TPlayerIDVector& playerIDVector)
			{ getProfPlayerShelf()->getIDVectorByNewPlayerDateRange(fromDate,toDate,
				playerIDVector); }
	void getProfPlayerVector(TProfPlayerVector& profPlayerVector)
		{ getProfPlayerShelf()->getItemVector(profPlayerVector); }
		
	void getPlayerIDVector(TLeaguePlayerIDVector& leaguePlayerIDVector)
		{ getPlayerShelf()->getItemKeyVector(leaguePlayerIDVector); }
	void getPlayerVector(TPlayerVector& playerVector)
		{ getPlayerShelf()->getItemVector(playerVector); }

	void getTeamPlayerIDVectorByTeam(TTeamID teamID,TPlayerIDVector& playerIDVector)
		{ getPlayerShelf()->getTeamPlayerIDVectorByTeam(teamID,playerIDVector); }

	void getOffGameStatVectorByPlayerIDVector(TPlayerIDVector& playerIDVector,
			TOffGameStatVector& offGameStatVector)
		{ getOffGameStatShelf()->getVectorByPlayerIDVector(playerIDVector,offGameStatVector); }
	void getOffGameStatVectorRandomByPlayerIDVector(TPlayerIDVector& playerIDVector,
			TOffGameStatVector& offGameStatVector)
		{ getOffGameStatShelf()->getVectorRandomByPlayerIDVector(playerIDVector,offGameStatVector); }
	void getDefGameStatVectorByPlayerIDVector(TPlayerIDVector& playerIDVector,
			TDefGameStatVector& defGameStatVector)
		{ getDefGameStatShelf()->getVectorByPlayerIDVector(playerIDVector,defGameStatVector); }
	void getDefGameStatVectorRandomByPlayerIDVector(TPlayerIDVector& playerIDVector,
			TDefGameStatVector& defGameStatVector)
		{ getDefGameStatShelf()->getVectorRandomByPlayerIDVector(playerIDVector,defGameStatVector); }

	bool isPlayerIDVectorValidForProfPlayers(const TPlayerIDVector& playerIDVector,
		bool undefinedIDsAllowed = false);

	void loadScheduleDayVectorByLeagueID(TLeagueID leagueID);
	void getScheduleDayVector(TScheduleDayVector& scheduleDayVector)
		{ getScheduleDayShelf()->getItemVector(scheduleDayVector); }
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyObjectStoreH
/******************************************************************************/
/******************************************************************************/
