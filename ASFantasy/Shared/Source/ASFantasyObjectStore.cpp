/* ASFantasyObjectStore.cpp */

/******************************************************************************/
/******************************************************************************/

//turn off debugging and line numbers, file is too large
#pragma option -v-
#pragma option -y-

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"

using namespace tag;
using namespace asfantasy;

/******************************************************************************/
/******************************************************************************/

ASFantasyObjectStore::ASFantasyObjectStore(ASFantasyObjectBuilder& builder) :
	ObjectStore(builder)
{
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addTeamShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new TeamObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/

void ASFantasyObjectStore::saveAndDelAllTeamShelfItems()
{
	TeamObjectShelf* pShelf = getTeamShelf();
	pShelf->saveAllItems();
	pShelf->delAllItems();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addProfPlayerShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new ProfPlayerObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/

void ASFantasyObjectStore::delAllProfPlayerShelfItems()
{
	ProfPlayerObjectShelf* pShelf = getProfPlayerShelf();
	pShelf->delAllItems();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addProfTeamShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new ProfTeamObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/

void ASFantasyObjectStore::delAllProfTeamShelfItems()
{
	ProfTeamObjectShelf* pShelf = getProfTeamShelf();
	pShelf->delAllItems();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addPlayerShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new PlayerObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/

void ASFantasyObjectStore::saveAndDelAllPlayerShelfItems()
{
	PlayerObjectShelf* pShelf = getPlayerShelf();
	pShelf->saveAllItems();
	pShelf->delAllItems();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addOffGameStatShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new OffGameStatObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addDefGameStatShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new DefGameStatObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addDraftRankingShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new DraftRankingObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addDraftPosCountShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new DraftPosCountObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addScheduleDayShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new ScheduleDayObjectShelf(
		dynamic_cast<ASFantasyObjectBuilder&>(fBuilder))));
}

/******************************************************************************/

void ASFantasyObjectStore::saveAndDelAllScheduleDayShelfItems()
{
	ScheduleDayObjectShelf* pShelf = getScheduleDayShelf();
	pShelf->saveAllItems();
	pShelf->delAllItems();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addTeam(TTeamPtr teamPtr)
{
	ObjectShelfKeyType shelfKey = getTeamShelfKey();
	ObjectShelfItemKey<TTeamID> key(teamPtr->getTeamID());
	ObjectShelfItem<TTeamPtr> item(teamPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TTeamPtr ASFantasyObjectStore::getTeam(TTeamID teamID,GetItemMode getItemMode)
{
	ObjectShelfKeyType shelfKey = getTeamShelfKey();
	TTeamPtr teamPtr;
	ObjectShelfItemKey<TTeamID> key(teamID);
	ObjectShelfItem<TTeamPtr> item;

	if(getItem(shelfKey, key, item, getItemMode))
		teamPtr = item.getItem();
	 
	return(teamPtr);
}

/******************************************************************************/

void ASFantasyObjectStore::delTeam(TTeamID teamID)
{
	ObjectShelfKeyType shelfKey = getTeamShelfKey();
	ObjectShelfItemKey<TTeamID> key(teamID);

	delItem(shelfKey, key);
}

/******************************************************************************/

TTeamPtr ASFantasyObjectStore::newTeam()
{
	ObjectShelfKeyType shelfKey = getTeamShelfKey();
	TTeamPtr teamPtr(ASFantasyObjectBuilder::getThe().newTeam());
	ObjectShelfItemKey<TTeamID> key;
	ObjectShelfItem<TTeamPtr> item(teamPtr);

	newItem(shelfKey, key, item);
	 
	teamPtr = item.getItem();
	return(teamPtr);
}

/******************************************************************************/
	
void ASFantasyObjectStore::saveTeam(TTeamID teamID)
{
	ObjectShelfKeyType shelfKey = getTeamShelfKey();
	ObjectShelfItemKey<TTeamID> key(teamID);

	saveItem(shelfKey, key);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addProfPlayer(TProfPlayerPtr profPlayerPtr)
{
	ObjectShelfKeyType shelfKey = getProfPlayerShelfKey();
	ObjectShelfItemKey<TPlayerID> key(profPlayerPtr->getPlayerID());
	ObjectShelfItem<TProfPlayerPtr> item(profPlayerPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TProfPlayerPtr ASFantasyObjectStore::getProfPlayer(TPlayerID playerID,
	GetItemMode getItemMode)
{
	ObjectShelfKeyType shelfKey = getProfPlayerShelfKey();
	TProfPlayerPtr profPlayerPtr;
	ObjectShelfItemKey<TPlayerID> key(playerID);
	ObjectShelfItem<TProfPlayerPtr> item;

	if(getItem(shelfKey, key, item, getItemMode))
		profPlayerPtr = item.getItem();
	 
	return(profPlayerPtr);
}

/******************************************************************************/
	
void ASFantasyObjectStore::saveProfPlayer(TPlayerID playerID)
{
	ObjectShelfKeyType shelfKey = getProfPlayerShelfKey();
	ObjectShelfItemKey<TPlayerID> key(playerID);

	saveItem(shelfKey, key);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addProfTeam(TProfTeamPtr profTeamPtr)
{
	ObjectShelfKeyType shelfKey = getProfTeamShelfKey();
	ObjectShelfItemKey<TProfTeamID> key(profTeamPtr->getProfTeamID());
	ObjectShelfItem<TProfTeamPtr> item(profTeamPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TProfTeamPtr ASFantasyObjectStore::getProfTeam(TProfTeamID profTeamID,
	GetItemMode getItemMode)
{
	ObjectShelfKeyType shelfKey = getProfTeamShelfKey();
	TProfTeamPtr profTeamPtr;
	ObjectShelfItemKey<TProfTeamID> key(profTeamID);
	ObjectShelfItem<TProfTeamPtr> item;

	if(getItem(shelfKey, key, item, getItemMode))
		profTeamPtr = item.getItem();
	 
	return(profTeamPtr);
}

/******************************************************************************/

TProfTeamPtr ASFantasyObjectStore::getProfTeamAbbr(TProfTeamAbbr profTeamAbbr,
	GetItemMode getItemMode)
{
	ProfTeamObjectShelf* pShelf = dynamic_cast<ProfTeamObjectShelf*>(
		getShelfByKey(getProfTeamShelfKey()));

	return(pShelf->getByAbbr(profTeamAbbr,getItemMode));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addPlayer(TPlayerPtr playerPtr)
{
	ObjectShelfKeyType shelfKey = getPlayerShelfKey();
	ObjectShelfItemKey<TLeaguePlayerID> key(playerPtr->getKey());
	ObjectShelfItem<TPlayerPtr> item(playerPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TPlayerPtr ASFantasyObjectStore::getPlayer(TLeagueID leagueID,TPlayerID playerID,
	GetItemMode getItemMode)
{
	ObjectShelfKeyType shelfKey = getPlayerShelfKey();
	TPlayerPtr playerPtr;
	ObjectShelfItemKey<TLeaguePlayerID> key(TLeaguePlayerID(leagueID,playerID));
	ObjectShelfItem<TPlayerPtr> item;

	if(getItem(shelfKey, key, item, getItemMode))
		playerPtr = item.getItem();
	 
	return(playerPtr);
}

/******************************************************************************/

TPlayerPtr ASFantasyObjectStore::newPlayer(TLeagueID leagueID,TPlayerID playerID)
{
	ObjectShelfKeyType shelfKey = getPlayerShelfKey();
	TPlayerPtr playerPtr(TPlayer::newInstance());
	ObjectShelfItemKey<TLeaguePlayerID> key;
	ObjectShelfItem<TPlayerPtr> item(playerPtr);

	playerPtr->setLeagueID(leagueID);
	playerPtr->setPlayerID(playerID);
	newItem(shelfKey, key, item);
	
	return(playerPtr);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addOffGameStat(TOffGameStatPtr offGameStatPtr)
{
	ObjectShelfKeyType shelfKey = getOffGameStatShelfKey();
	ObjectShelfItemKey<TPlayerStatID> key(offGameStatPtr->getKey());
	ObjectShelfItem<TOffGameStatPtr> item(offGameStatPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addDefGameStat(TDefGameStatPtr defGameStatPtr)
{
	ObjectShelfKeyType shelfKey = getDefGameStatShelfKey();
	ObjectShelfItemKey<TPlayerStatID> key(defGameStatPtr->getKey());
	ObjectShelfItem<TDefGameStatPtr> item(defGameStatPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addDraftRanking(TDraftRankingPtr draftRankingPtr)
{
	ObjectShelfKeyType shelfKey = getDraftRankingShelfKey();
	ObjectShelfItemKey<TTeamID> key(draftRankingPtr->getTeamID());
	ObjectShelfItem<TDraftRankingPtr> item(draftRankingPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TDraftRankingPtr ASFantasyObjectStore::getDraftRanking(TTeamID teamID,
	GetItemMode getItemMode)
{
	ObjectShelfKeyType shelfKey = getDraftRankingShelfKey();
	TDraftRankingPtr draftRankingPtr;
	ObjectShelfItemKey<TTeamID> key(teamID);
	ObjectShelfItem<TDraftRankingPtr> item;

	if(getItem(shelfKey, key, item, getItemMode))
		draftRankingPtr = item.getItem();

	return(draftRankingPtr);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::storeDraftPosCount(TDraftPosCount& draftPosCount)
{
	ObjectShelfKeyType shelfKey = getDraftPosCountShelfKey();
	ObjectShelfItemKey<TDraftPosCountKey> key(draftPosCount.getKey());
	ObjectShelfItem<TDraftPosCount> item(draftPosCount);
	ObjectShelfItem<TDraftPosCount> tempItem;

	if(getItem(shelfKey, key, tempItem, gim_MayNotExist))
		delItem(shelfKey,key);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TDraftPosCount ASFantasyObjectStore::getDraftPosCount(TDraftPosCountKey
	draftPosCountKey)
{
	ObjectShelfKeyType shelfKey = getDraftPosCountShelfKey();
	ObjectShelfItemKey<TDraftPosCountKey> key(draftPosCountKey);
	ObjectShelfItem<TDraftPosCount> item;

	getItem(shelfKey, key, item, gim_MustExist);
	return(item.getItem());
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::addScheduleDay(TScheduleDayPtr scheduleDayPtr)
{
	ObjectShelfKeyType shelfKey = getScheduleDayShelfKey();
	ObjectShelfItemKey<TScheduleDayID> key(scheduleDayPtr->getScheduleDayID());
	ObjectShelfItem<TScheduleDayPtr> item(scheduleDayPtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::loadTeamsForLeague(TLeagueID leagueID)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TTeamPtr teamPtr;

	// Find all Teams
	try
	{
		str.copyVarg("select * from Team where LeagueID = %s",leagueID.c_str());

		pQuery = OpenQuery(PrimaryDatabaseName(),str);
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			teamPtr = TTeam::newInstance();
			teamPtr->load(*pQuery);
			addTeam(teamPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void ASFantasyObjectStore::loadProfPlayersByPositionGameStatus(
	const TPositionVector& posVector,const TProfPlayerGameStatus gameStatus)
{
	TProfPlayerVector profPlayerVector;
	TProfPlayerVector::iterator iter;
	TProfPlayerPtr profPlayerPtr;

	//BOB clear shelf

	LoadProfPlayerVectorByGameStatus(gameStatus,profPlayerVector);

	for(iter = profPlayerVector.begin(); iter != profPlayerVector.end(); iter++)
	{
		profPlayerPtr = (*iter);

		if(posVector.contains(profPlayerPtr->getPosition()))
			addProfPlayer(profPlayerPtr);
	}
}

/******************************************************************************/

void ASFantasyObjectStore::loadKeyProfPlayers()
{
	TPositionVector posVector;

	loadKeyPositionVector(posVector);
	loadProfPlayersByPositionGameStatus(posVector,ppgs_Active);
}

/******************************************************************************/

void ASFantasyObjectStore::loadAllProfPlayers()
{
	TPositionVector posVector;

	loadAllPositionVector(posVector);
	loadProfPlayersByPositionGameStatus(posVector,TProfPlayerGameStatus());
}

/******************************************************************************/

void ASFantasyObjectStore::loadAllProfTeams()
{
	TQuery* pQuery = NULL;
	TProfTeamPtr profTeamPtr;

	// Find all ProfTeams
	try
	{
		//BOB clear shelf
		
		pQuery = OpenQuery(PrimaryDatabaseName(),"select * from ProfTeam");
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			profTeamPtr = TProfTeam::newInstance();
			profTeamPtr->load(*pQuery);
			addProfTeam(profTeamPtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void ASFantasyObjectStore::loadPlayersForLeague(TLeagueID leagueID)
{
	TPlayerVector playerVector;
	TPlayerVector::iterator iter;
	
	LoadPlayerVectorByLeagueID(leagueID,ptf_TeamPlayer | ptf_FreeAgent,
		playerVector);

	for(iter = playerVector.begin(); iter != playerVector.end(); iter++)
		addPlayer(*iter);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::loadOffGameStatVectorByWhereStr(const char* whereStr)
{
	TQuery* pQuery = NULL;
	AnsiString str;
	TOffGameStatPtr	offGameStatPtr;

	try
	{
		str = "select * from OffGameStat";
		if(tStrHasLen(whereStr))
			str += AnsiString(" where ") + whereStr;
		
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());

		pQuery->First();
		while(!pQuery->Eof)
		{
			offGameStatPtr = TOffGameStat::newInstance();
			offGameStatPtr->load(*pQuery);
			addOffGameStat(offGameStatPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void ASFantasyObjectStore::loadOffGameStatVectorByDatePeriod(TDateTime fromStatDate,
	TDateTime toStatDate,TStatPeriod statPeriod)
{
	CStrVar str;

	str.copyVarg("(StatDate >= \"%s\") and (StatDate <= \"%s\") and "
		"(StatPeriod = \"%s\")",FormatDateOnlyStr(fromStatDate).c_str(),
		FormatDateOnlyStr(toStatDate).c_str(),statPeriod.c_str());
		
	loadOffGameStatVectorByWhereStr(str);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::loadDefGameStatVectorByWhereStr(const char* whereStr)
{
	TQuery* pQuery = NULL;
	AnsiString str;
	TDefGameStatPtr	defGameStatPtr;

	try
	{
		str = "select * from DefGameStat";
		if(tStrHasLen(whereStr))
			str += AnsiString(" where ") + whereStr;
		
		pQuery = OpenQuery(PrimaryDatabaseName(),str.c_str());

		pQuery->First();
		while(!pQuery->Eof)
		{
			defGameStatPtr = TDefGameStat::newInstance();
			defGameStatPtr->load(*pQuery);
			addDefGameStat(defGameStatPtr);

			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void ASFantasyObjectStore::loadDefGameStatVectorByDatePeriod(TDateTime fromStatDate,
	TDateTime toStatDate,TStatPeriod statPeriod)
{
	CStrVar str;

	str.copyVarg("(StatDate >= \"%s\") and (StatDate <= \"%s\") and "
		"(StatPeriod = \"%s\")",FormatDateOnlyStr(fromStatDate).c_str(),
		FormatDateOnlyStr(toStatDate).c_str(),statPeriod.c_str());
	
	loadDefGameStatVectorByWhereStr(str);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::loadDraftRankingsForLeague(TLeagueID leagueID)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TDraftRankingPtr draftRankingPtr;

	// Find all DraftRankings
	try
	{
		str.copyVarg("select * from DraftRanking where TeamID in "
			"(select TeamID from Team where LeagueID = \"%s\")",leagueID.c_str());

		pQuery = OpenQuery(PrimaryDatabaseName(),str);
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			draftRankingPtr = TDraftRanking::newInstance();
			draftRankingPtr->load(*pQuery);
			addDraftRanking(draftRankingPtr);
			
			pQuery->Next();
		}

		// Add default draft ranking to store.
		draftRankingPtr = TDraftRanking::createGet(DefaultDraftRankingTeamID,
			cam_MustExist);
		addDraftRanking(draftRankingPtr);
		
		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void ASFantasyObjectStore::createDraftPosCountsForTeamIDVector(
	const TTeamIDVector& teamIDVector,const TPositionVector& posVector)
{
	TTeamIDVector::const_iterator teamIDIter;
	TPositionVector::const_iterator posIter;

	for(teamIDIter = teamIDVector.begin(); teamIDIter != teamIDVector.end();
			teamIDIter++)
		for(posIter = posVector.begin(); posIter != posVector.end(); posIter++)
		{
			storeDraftPosCount(TDraftPosCount(
				TDraftPosCountKey(*teamIDIter,*posIter)));
		}
}

/******************************************************************************/

bool ASFantasyObjectStore::isPlayerIDVectorValidForProfPlayers(
	const TPlayerIDVector& playerIDVector,bool undefinedIDsAllowed)
{
	TPlayerIDVector::const_iterator iter;
	TPlayerID playerID;

	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		playerID = *iter;
		if(!playerID.isUndefined())
		{
			if(getProfPlayer(playerID,ObjectStore::gim_MayNotExist).isNull())
				return(false);
		}
		else if(!undefinedIDsAllowed)
			return(false);
	}

	return(true);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyObjectStore::loadScheduleDayVectorByLeagueID(TLeagueID leagueID)
{
	TScheduleDayVector scheduleDayVector;
	TScheduleDayVector::iterator iter;

	LoadScheduleDayVectorByLeagueID(leagueID,scheduleDayVector);

	for(iter = scheduleDayVector.begin(); iter != scheduleDayVector.end(); ++iter)
		addScheduleDay(*iter);
}

/******************************************************************************/
/******************************************************************************/
