/* ASHockeyDraftRanking.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyAppOptions.h"
#include "ASHockeyType.h"
#include "ASHockeyDraftRanking.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

void ASHockeyDraftRankingBuilder::getPosCountVector(
	TPosCountVector& posCountVector) const
{
	int maxTeams = MaxTeamsPerPrivateLeague();
	
	posCountVector.erase(posCountVector.begin(),posCountVector.end());

	posCountVector.add(pos_Winger,
		MaxDraftPlayersForPosition(pos_Winger) * maxTeams);
	posCountVector.add(pos_Center,
		MaxDraftPlayersForPosition(pos_Center) * maxTeams);
	posCountVector.add(pos_Defenseman,
		MaxDraftPlayersForPosition(pos_Defenseman) * maxTeams);
	posCountVector.add(pos_Goalie,
		MaxDraftPlayersForPosition(pos_Goalie) * maxTeams);
}

/******************************************************************************/

bool ASHockeyDraftRankingBuilder::isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const
{
	THockeyPosition pos(profPlayerPtr->getPosition());

	return(pos.isOffensive());
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
