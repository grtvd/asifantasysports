/* ASFantasyObjectShelf.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectShelf.h"

using namespace tag;
using namespace asfantasy;

/******************************************************************************/
/******************************************************************************/
#if 0	//BOB

ObjectShelfItemBase* TeamObjectShelf::newItem(const ObjectShelfItemKeyBase& key)
{
	const ObjectShelfItemKey<TTeamID> teamIDKey(
		dynamic_cast< const ObjectShelfItemKey<TTeamID> &>(key));
	TTeamPtr teamPtr;
	ObjectShelfItem<TTeamPtr>* pTeamPtrItem;
	
	teamPtr = static_cast<TTeam*>(fBuilder.newInstance(fobt_TTeam));
	teamPtr->setTeamID(teamIDKey);
	pTeamPtrItem = new ObjectShelfItem<TTeamPtr>(teamPtr);

	return(pTeamPtrItem);
}

#endif
/******************************************************************************/

TTeamPtr* TeamObjectShelf::newItemInstance(TTeamID key)
{
//	TTeamPtr* pTeamPtr = new TTeamPtr(
//		static_cast<TTeam*>(fBuilder.newInstance(fobt_TTeam)));
	TTeamPtr* pTeamPtr = new TTeamPtr(getBuilder().newTeam());
		
	(*pTeamPtr)->setTeamID(key);
	return(pTeamPtr);
}

/******************************************************************************/
#if 0	//BOB

void TeamObjectShelf::loadItem(const ObjectShelfItemKeyBase& key,
	ObjectShelfItemBase& item)
{
	ObjectShelfItem<TTeamPtr>& nativeItem = 
		dynamic_cast<ObjectShelfItem<TTeamPtr> &>(item);
	TTeamPtr teamPtr = nativeItem;

	teamPtr->setTeamID(25);
}

#endif
/******************************************************************************/
/******************************************************************************/

TProfPlayerPtr* ProfPlayerObjectShelf::newItemInstance(TPlayerID key)
{
	TProfPlayerPtr* pProfPlayerPtr = new TProfPlayerPtr(getBuilder().newProfPlayer());
		
	(*pProfPlayerPtr)->setPlayerID(key);
	return(pProfPlayerPtr);
}

/******************************************************************************/

void ProfPlayerObjectShelf::getIDVectorByNewPlayerDateRange(TDateTime fromDate,
	TDateTime toDate,TPlayerIDVector& playerIDVector)
{
	MapType::iterator iter;

	playerIDVector.erase(playerIDVector.begin(),playerIDVector.end());
	
	for(iter = fMap.begin(); iter != fMap.end(); iter++)
	{
		TProfPlayerPtr& profPlayerPtr = (*iter).second.getItem();

		if((profPlayerPtr->getNewPlayerDate() >= fromDate) &&
				(profPlayerPtr->getNewPlayerDate() <= toDate))
			playerIDVector.push_back(profPlayerPtr->getPlayerID());
	}
}

/******************************************************************************/
/******************************************************************************/

TProfTeamPtr ProfTeamObjectShelf::getByAbbr(TProfTeamAbbr profTeamAbbr,
	ObjectStore::GetItemMode getItemMode)
{
	ItemType nativeItem;
	MapType::iterator iter;
	TProfTeamPtr profTeamPtr;

	for(iter = fMap.begin(); iter != fMap.end(); iter++)
	{
		nativeItem = (*iter).second;
		profTeamPtr = (*iter).second.getItem();

		if(profTeamPtr->getProfTeamAbbr() == profTeamAbbr)
			return(profTeamPtr);
	}

	return(TProfTeamPtr());
}

/******************************************************************************/
/******************************************************************************/

void PlayerObjectShelf::getTeamPlayerIDVectorByTeam(TTeamID teamID,
	TPlayerIDVector& playerIDVector)
{
	MapType::const_iterator iter;

	playerIDVector.erase(playerIDVector.begin(),playerIDVector.end());
	
	for(iter = fMap.begin(); iter != fMap.end(); iter++)
	{
		const TPlayerPtr& playerPtr = (*iter).second.getItem();

		if(!playerPtr->isFreeAgent() && (playerPtr->getTeamID() == teamID))
			playerIDVector.push_back(TPlayerID(playerPtr->getPlayerID()));
	}
}

/******************************************************************************/
/******************************************************************************/

/* For each playerID in playerIDVector, fetch TOffGameStat for playerID.
	Assumes 0 or 1 TOffGameStats for each playerID. */

void OffGameStatObjectShelf::getVectorByPlayerIDVector(
	TPlayerIDVector& playerIDVector,TOffGameStatVector& offGameStatVector)
{
	MapType::const_iterator statIter;
	TPlayerIDVector::const_iterator playerIDIter;

	offGameStatVector.erase(offGameStatVector.begin(),offGameStatVector.end());
	
	for(statIter = fMap.begin(); statIter != fMap.end(); statIter++)
	{
		const TOffGameStatPtr& offGameStatPtr = (*statIter).second.getItem();

		for(playerIDIter = playerIDVector.begin();
			playerIDIter != playerIDVector.end(); playerIDIter++)
		{
			if(offGameStatPtr->getPlayerID() == *playerIDIter)
				offGameStatVector.push_back(offGameStatPtr);
		}
	}
}
		
/******************************************************************************/

/* For each playerID in playerIDVector, fetch random TOffGameStat from
	all TOffGameStats for playerID. Assumes 0 or more TOffGameStats for
	each playerID. */

void OffGameStatObjectShelf::getVectorRandomByPlayerIDVector(
	TPlayerIDVector& playerIDVector,TOffGameStatVector& offGameStatVector)
{
	TOffGameStatVector playerOffGameStatVector;
	MapType::const_iterator statIter;
	TPlayerIDVector::const_iterator playerIDIter;

	offGameStatVector.erase(offGameStatVector.begin(),offGameStatVector.end());
	
	for(playerIDIter = playerIDVector.begin();
		playerIDIter != playerIDVector.end(); playerIDIter++)
	{
		playerOffGameStatVector.erase(playerOffGameStatVector.begin(),
			playerOffGameStatVector.end());

		for(statIter = fMap.begin(); statIter != fMap.end(); statIter++)
		{
			const TOffGameStatPtr& offGameStatPtr = (*statIter).second.getItem();

			if(offGameStatPtr->getPlayerID() == *playerIDIter)
				playerOffGameStatVector.push_back(offGameStatPtr);
		}

		if(playerOffGameStatVector.size() > 0)
		{
			int pos = GetRandomFromRange(0,playerOffGameStatVector.size() - 1);
			offGameStatVector.push_back(playerOffGameStatVector[pos]);
		}
	}

}
		
/******************************************************************************/

/* For each playerID in playerIDVector, fetch TDefGameStat for playerID.
	Assumes 0 or 1 TDefGameStats for each playerID. */

void DefGameStatObjectShelf::getVectorByPlayerIDVector(
	TPlayerIDVector& playerIDVector,TDefGameStatVector& defGameStatVector)
{
	MapType::const_iterator statIter;
	TPlayerIDVector::const_iterator playerIDIter;

	defGameStatVector.erase(defGameStatVector.begin(),defGameStatVector.end());
	
	for(statIter = fMap.begin(); statIter != fMap.end(); statIter++)
	{
		const TDefGameStatPtr& defGameStatPtr = (*statIter).second.getItem();

		for(playerIDIter = playerIDVector.begin();
			playerIDIter != playerIDVector.end(); playerIDIter++)
		{
			if(defGameStatPtr->getPlayerID() == *playerIDIter)
				defGameStatVector.push_back(defGameStatPtr);
		}
	}
}

/******************************************************************************/

/* For each playerID in playerIDVector, fetch random TDefGameStat from
	all TDefGameStats for playerID. Assumes 0 or more TDefGameStats for
	each playerID. */

void DefGameStatObjectShelf::getVectorRandomByPlayerIDVector(
	TPlayerIDVector& playerIDVector,TDefGameStatVector& defGameStatVector)
{
	TDefGameStatVector playerDefGameStatVector;
	MapType::const_iterator statIter;
	TPlayerIDVector::const_iterator playerIDIter;

	defGameStatVector.erase(defGameStatVector.begin(),defGameStatVector.end());
	
	for(playerIDIter = playerIDVector.begin();
		playerIDIter != playerIDVector.end(); playerIDIter++)
	{
		playerDefGameStatVector.erase(playerDefGameStatVector.begin(),
			playerDefGameStatVector.end());

		for(statIter = fMap.begin(); statIter != fMap.end(); statIter++)
		{
			const TDefGameStatPtr& defGameStatPtr = (*statIter).second.getItem();

			if(defGameStatPtr->getPlayerID() == *playerIDIter)
				playerDefGameStatVector.push_back(defGameStatPtr);
		}

		if(playerDefGameStatVector.size() > 0)
		{
			int pos = GetRandomFromRange(0,playerDefGameStatVector.size() - 1);
			defGameStatVector.push_back(playerDefGameStatVector[pos]);
		}
	}

}

/******************************************************************************/
/******************************************************************************/
