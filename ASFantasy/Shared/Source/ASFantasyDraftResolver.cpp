/* ASFantasyDraftResolver.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDraftResolver.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

/* Resolves Draft for specified rounds. 

	Assumes Teams and Players (for league) and ProfPlayers (key) have been
	loaded into Store.

	Assumes TDraftOrder and TDraftResult already exist for League.
*/

TDraftResultPtr DraftResolver::resolve(const TLeagueID leagueID,int fromRound,
	int toRound)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TTeamIDVector teamIDVector;
	TDraftOrderPtr draftOrderPtr;
	TDraftResultPtr draftResultPtr;
	TPositionVector posVector;

	try
	{
		store.addDraftRankingShelf();
		store.addDraftPosCountShelf();

		store.loadDraftRankingsForLeague(leagueID);

		store.getTeamIDVector(teamIDVector);    // get vector of TTeamIDs in Store
		loadKeyPositionVector(posVector);

		store.createDraftPosCountsForTeamIDVector(teamIDVector,posVector);
		setUpDraftPosCountForExistingPlayers(leagueID);

		draftOrderPtr = TDraftOrder::createGet(leagueID,cam_MustExist);
		draftResultPtr = TDraftResult::createGet(leagueID,cam_MustExist);


		for(int i = fromRound; i <= toRound; i++)
		{
			const TTeamIDVector& draftTeamIDVector =
				draftOrderPtr->draftRoundVector()[i - 1];
			TTeamIDVector::const_iterator teamIDIter;
			TDraftPickVector draftPickVector;

			for(teamIDIter = draftTeamIDVector.begin();
				teamIDIter != draftTeamIDVector.end(); teamIDIter++)
			{
				const TTeamID teamID = *teamIDIter;
				const TDraftRankingPtr draftRankingPtr = store.getDraftRanking(teamID);

				// Draft Next Available Player from Draft Ranking
				if(!setNextAvailablePlayer(leagueID,teamID,
					store.getDraftRanking(teamID),draftPickVector))
				{
					// If Team's Draft Ranking could not fulfill "balance lineup"
					//  then use default Draft Ranking.
					if(!setNextAvailablePlayer(leagueID,teamID,
							store.getDefaultDraftRanking(),draftPickVector))
						throw ASIException("DraftResolver::resolve: unable to set next player");
				}

			}
		
			draftResultPtr->draftPickRoundVector().push_back(draftPickVector);
		}

		removePickedPlayersFromDraftRankings(leagueID,teamIDVector);
		
		draftResultPtr->update();
	
		store.delDraftRankingShelf();
		store.delDraftPosCountShelf();
	}
	catch(const Exception& e)
	{
		store.delDraftRankingShelf();
		store.delDraftPosCountShelf();
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		store.delDraftRankingShelf();
		store.delDraftPosCountShelf();
		throw;
	}

	return(draftResultPtr);
}

/******************************************************************************/

void DraftResolver::setUpDraftPosCountForExistingPlayers(const TLeagueID leagueID)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerVector playerVector;
	TPlayerVector::iterator playerIter;

	store.getPlayerVector(playerVector);
	
	for(playerIter = playerVector.begin();
		playerIter != playerVector.end(); playerIter++)
	{
		const TPlayerPtr playerPtr = *playerIter;
		const TProfPlayerPtr profPlayerPtr = store.getProfPlayer(
			playerPtr->getPlayerID());
		const TPosition pos = profPlayerPtr->getPosition();

		TDraftPosCount draftPosCount = store.getDraftPosCount(
			TDraftPosCountKey(playerPtr->getTeamID(),pos));
		
		draftPosCount.fCount++;
		
		if(draftPosCount.fCount > MaxDraftPlayersForPosition(pos))
			throw ASIException("DraftResolver::setUpDraftPosCountForExistingPlayers: "
				"count excedes MaxDraftPlayersForPosition");
		
		store.storeDraftPosCount(draftPosCount);
	}
}

/******************************************************************************/

bool DraftResolver::setNextAvailablePlayer(const TLeagueID leagueID,
	const TTeamID teamID,const TDraftRankingPtr draftRankingPtr,
	TDraftPickVector& draftPickVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	const TPlayerIDVector& draftPlayerIDVector = draftRankingPtr->playerIDVector();

	TPlayerIDVector::const_iterator playerIDIter;

	// Loop through the players in the draft ranking.
	for(playerIDIter = draftPlayerIDVector.begin();
		playerIDIter != draftPlayerIDVector.end(); playerIDIter++)
	{
		const TPlayerID playerID = *playerIDIter;

		// Has Player already be drafted?
		if(store.getPlayer(leagueID,playerID,ObjectStore::gim_MayNotExist).isNull())
		{
			const TProfPlayerPtr profPlayerPtr = store.getProfPlayer(playerID);
			const TPosition pos = profPlayerPtr->getPosition();

			TDraftPosCount draftPosCount = store.getDraftPosCount(
				TDraftPosCountKey(teamID,pos));

			// Are open slots available a position?
			if(draftPosCount.fCount < MaxDraftPlayersForPosition(pos))
			{
				// Create new player
				TPlayerPtr playerPtr = store.newPlayer(leagueID,playerID);
				playerPtr->setTeamID(teamID);
				playerPtr->update();

				// Update Draft Pos Count
				draftPosCount.fCount++;
				store.storeDraftPosCount(draftPosCount);

				draftPickVector.push_back(TDraftPick(teamID,playerID));
				return(true);
			}
		}
	}

	return(false);
}

/******************************************************************************/

void DraftResolver::removePickedPlayersFromDraftRankings(const TLeagueID leagueID,
	const TTeamIDVector& teamIDVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TTeamIDVector::const_iterator teamIDIter;
	
	// Loop through all teams
	for(teamIDIter = teamIDVector.begin();
		teamIDIter != teamIDVector.end(); teamIDIter++)
	{
		const TTeamID teamID = *teamIDIter;
		TDraftRankingPtr draftRankingPtr = store.getDraftRanking(teamID);
		
		TPlayerIDVector& draftPlayerIDVector =
			draftRankingPtr->playerIDVector();
		TPlayerIDVector::iterator playerIDIter;
			
		TPlayerIDVector newPlayerIDVector;
			
		// Loop through all players in draft ranking
		for(playerIDIter = draftPlayerIDVector.begin();
			playerIDIter != draftPlayerIDVector.end(); playerIDIter++)
		{
			const TPlayerID playerID = *playerIDIter;
			
			// If player has been drafted, then don't add player to new vector			
			if(store.getPlayer(leagueID,playerID,ObjectStore::gim_MayNotExist).isNull())
				newPlayerIDVector.push_back(playerID);
		}

		// Update draft ranking with new player vector
		draftRankingPtr->playerIDVector() = newPlayerIDVector;
		draftRankingPtr->update();
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
