/* ASFantasyCreateLineup.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectStore.h"
#include "ASFantasyType.h"
#include "ASFantasyCreateLineup.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void CreateLineupForTeam(const TTeamPtr& teamPtr,
	const TDraftResultPtr& draftResultPtr,
	const TPositionVector& posVector, TPlayerIDVector& lineup )
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	const TDraftPickRoundVector& draftRoundVector = draftResultPtr->draftPickRoundVector();
	TPlayerIDVector		 	draftPlayerIDVector;
	TProfPlayerPtr			profPlayerPtr;
	TPosition				pos;
	TPlayerID				playerID;
	bool					positionMatch;

	lineup.erase(lineup.begin(),lineup.end());
	
	// build a list of players drafted by the specified team
	for (TDraftPickRoundVector::const_iterator roundIter=draftRoundVector.begin();
		roundIter!=draftRoundVector.end(); roundIter++)
	{
		for (TDraftPickVector::const_iterator pickIter=(*roundIter).begin();
			pickIter!=(*roundIter).end(); pickIter++)
		{
			if ((*pickIter).fTeamID == teamPtr->getTeamID())
			{
				draftPlayerIDVector.push_back( (*pickIter).fPlayerID );
				break;  // each team only drafts once per round
			}
		}
	}

	// loop through all of the positions
	for (TPositionVector::const_iterator posIter=posVector.begin();
		posIter!=posVector.end(); posIter++)
	{
		// loop through the player picks
		positionMatch = false;
		for (TPlayerIDVector::const_iterator pickIter=draftPlayerIDVector.begin();
			pickIter!=draftPlayerIDVector.end(); pickIter++)
		{
			// load player from database
			playerID = *pickIter;
			profPlayerPtr = store.getProfPlayer( playerID );
			pos = profPlayerPtr->getPosition();

			// match player position
			if (pos == *posIter)
			{
				// verify that player not used
				if(!lineup.contains(playerID))
				//BOB if(std::find( lineup.begin(),lineup.end(),playerID)
				//BOB	== lineup.end())
				{
					lineup.push_back( playerID );
					positionMatch = true;
					break;
				}
			}
		}

		if (!positionMatch)
			throw ASIException( "CreateLineupForTeam() position not drafted" );
	}
}

/******************************************************************************/

void CreateDefaultLineupForLeague(const TLeaguePtr& leaguePtr,
	const TTeamVector& teamVector,TDraftResultPtr draftResultPtr,
	const TLineup lineup)
{
	TPositionVector	posVector;
	TPlayerIDVector	playerIDVector;

	loadDefaultLineupPositionVector(lineup,posVector);

	for (TTeamVector::const_iterator iter=teamVector.begin();
		iter!=teamVector.end(); iter++)
	{
		TTeamPtr teamPtr = *iter;

		CreateLineupForTeam( teamPtr, draftResultPtr, posVector, playerIDVector );
		teamPtr->lineup(lineup) = playerIDVector;
		teamPtr->update();
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
