/* ASFantasyDraftRanking.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDraftRanking.h"

using namespace std;

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

bool TProfPlayerStatVector::sortCompare::operator() (const TProfPlayerStat& x,
	const TProfPlayerStat& y) const
{
	if(y.fStat < x.fStat)	// decending
		return(true);
	if(y.fStat > x.fStat)	// decending
		return(false);

	if(x.fProfPlayerPtr->getPlayerID() < y.fProfPlayerPtr->getPlayerID())
		return(true);
		
	return(false);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyDraftRankingBuilder::build()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TProfPlayerStatVector profPlayerStatVector;

	try
	{
		store.addProfPlayerShelf();
		store.loadKeyProfPlayers();

		loadProfPlayerStatVector(profPlayerStatVector);
		calcStatsForAllProfPlayers(profPlayerStatVector);
		removeProfPlayerByPosCount(profPlayerStatVector);

		printDraftRanking(profPlayerStatVector);
		createDraftRanking(profPlayerStatVector);
	}
	catch(const Exception& e)
	{
		store.delProfPlayerShelf();
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		store.delProfPlayerShelf();
		throw;
	}
	
	store.delProfPlayerShelf();
}

/******************************************************************************/

void ASFantasyDraftRankingBuilder::loadProfPlayerStatVector(
	TProfPlayerStatVector& profPlayerStatVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerIDVector playerIDVector;
	TPlayerIDVector::const_iterator iter;
	TPlayerID playerID;
	TProfPlayerPtr profPlayerPtr;

	profPlayerStatVector.erase(profPlayerStatVector.begin(),
		profPlayerStatVector.end());
	
	store.getProfPlayerIDVector(playerIDVector);
	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		playerID = *iter;
		profPlayerPtr = store.getProfPlayer(playerID);
		
		profPlayerStatVector.push_back(TProfPlayerStat(profPlayerPtr));
	}
}

/******************************************************************************/

void ASFantasyDraftRankingBuilder::calcStatsForAllProfPlayers(
	TProfPlayerStatVector& profPlayerStatVector)
{
	TProfPlayerStatVector::iterator iter;
	
	for(iter = profPlayerStatVector.begin(); iter != profPlayerStatVector.end();
			iter++)
		(*iter).fStat = calcStatForProfPlayer((*iter).fProfPlayerPtr);

	profPlayerStatVector.sort();
}

/******************************************************************************/

double ASFantasyDraftRankingBuilder::calcStatForProfPlayer(TProfPlayerPtr profPlayerPtr)
{
	TPlayerStatID playerStatID(profPlayerPtr->getPlayerID(),TStatPeriod(stp_LastSeason));
	
	if(isOffensivePlayer(profPlayerPtr))
	{
		TOffGameStatPtr offGameStatPtr = TOffGameStat::createGet(playerStatID,
			cam_MayNotExist);

		if(!offGameStatPtr.isNull())
			return(offGameStatPtr->getTotalPoints());
	}
	else
	{
		TDefGameStatPtr defGameStatPtr = TDefGameStat::createGet(playerStatID,
			cam_MayNotExist);

		if(!defGameStatPtr.isNull())
			return(defGameStatPtr->getTotalPoints());
	}
	
	return(0.0);
}

/******************************************************************************/

void ASFantasyDraftRankingBuilder::removeProfPlayerByPosCount(
	TProfPlayerStatVector& profPlayerStatVector)
{
	TProfPlayerStatVector tempProfPlayerStatVector;
	TProfPlayerStatVector::iterator playerStatIter;
	TPosCountVector posCountVector;
	TPosCountVector::iterator posCountIter;
	TPosition pos;
	
	getPosCountVector(posCountVector);
	
	for(playerStatIter = profPlayerStatVector.begin();
		playerStatIter != profPlayerStatVector.end(); playerStatIter++)
	{
		pos = (*playerStatIter).fProfPlayerPtr->getPosition();

		posCountIter = posCountVector.find(pos);
		if(posCountIter != posCountVector.end())
		{
			// Slots available for Pos?
			if((*posCountIter).second > 0)
			{
				tempProfPlayerStatVector.push_back(*playerStatIter);	// Add player to temp list
				(*posCountIter).second--;	//Decrement number of slots
			}
			// else skip player
		}
		else
			throw ASIException("ASFantasyDraftRankingBuilder::removeProfPlayerByPosCount: bad pos");
	}

	profPlayerStatVector = tempProfPlayerStatVector;
}

/******************************************************************************/

void ASFantasyDraftRankingBuilder::printDraftRanking(
	const TProfPlayerStatVector& profPlayerStatVector)
{
	TProfPlayerStatVector::const_iterator iter;
	TProfPlayerPtr profPlayerPtr;
	double stat;
	int rank = 1;
	
	for(iter = profPlayerStatVector.begin(); iter != profPlayerStatVector.end();
		++iter)
	{
		profPlayerPtr = (*iter).fProfPlayerPtr;
		stat = (*iter).fStat;

		CommErrMsg(cel_Info,"Rank|%3d|%04.lf|%-2s|%-5s|%s, %s|%d",rank,stat,
			convertPositionToString(profPlayerPtr->getPosition()).c_str(),
			profPlayerPtr->getPlayerID().c_str(),
			profPlayerPtr->getName().fLastName.c_str(),
			profPlayerPtr->getName().fFirstName.c_str(),
			profPlayerPtr->getProfTeamID().getID());
		rank++;
	}
}

/******************************************************************************/

void ASFantasyDraftRankingBuilder::createDraftRanking(
	const TProfPlayerStatVector& profPlayerStatVector)
{
	TProfPlayerStatVector::const_iterator iter;
	TDraftRankingPtr draftRankingPtr;

	draftRankingPtr = TDraftRanking::newInstance();
	draftRankingPtr->setTeamID(DefaultDraftRankingTeamID);
	TPlayerIDVector& playerIDVector = draftRankingPtr->playerIDVector();

	for(iter = profPlayerStatVector.begin();
			iter != profPlayerStatVector.end(); iter++)
		playerIDVector.push_back((*iter).fProfPlayerPtr->getPlayerID());

	draftRankingPtr->update();

	updateAllDraftRankings(draftRankingPtr);
}

/******************************************************************************/

void ASFantasyDraftRankingBuilder::updateAllDraftRankings(
	const TDraftRankingPtr defaultDraftRankingPtr)
{
	TDraftRankingVector draftRankingVector;
	TDraftRankingVector::iterator iter;
	TDraftRankingPtr draftRankingPtr;

	LoadDraftRankingVectorAllButDefault(draftRankingVector);

	for(iter = draftRankingVector.begin();
		iter != draftRankingVector.end(); iter++)
	{
		draftRankingPtr = (*iter);
		draftRankingPtr->playerIDVector() = defaultDraftRankingPtr->playerIDVector();
		draftRankingPtr->update();
	}
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyDraftRankingReseter::reset(const TTeamID teamID)
{
	TDraftRankingPtr defaultDraftRankingPtr =
		TDraftRanking::createGet(DefaultDraftRankingTeamID,cam_MustExist);
	TDraftRankingPtr draftRankingPtr = TDraftRanking::createGet(teamID,cam_MustExist);

	draftRankingPtr->playerIDVector() = defaultDraftRankingPtr->playerIDVector();
	draftRankingPtr->update();
}

/******************************************************************************/
/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
