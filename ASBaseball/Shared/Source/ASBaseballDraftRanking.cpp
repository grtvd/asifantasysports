/* ASBaseballDraftRanking.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballAppOptions.h"
#include "ASBaseballType.h"
#include "ASBaseballDraftRanking.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

void ASBaseballDraftRankingBuilder::getPosCountVector(
	TPosCountVector& posCountVector) const
{
	int maxTeams = MaxTeamsPerPrivateLeague();
	
	posCountVector.erase(posCountVector.begin(),posCountVector.end());

	posCountVector.add(pos_FirstBaseman,
		MaxDraftPlayersForPosition(pos_FirstBaseman) * maxTeams);
	posCountVector.add(pos_SecondBaseman,
		MaxDraftPlayersForPosition(pos_SecondBaseman) * maxTeams);
	posCountVector.add(pos_ShortStop,
		MaxDraftPlayersForPosition(pos_ShortStop) * maxTeams);
	posCountVector.add(pos_ThirdBaseman,
		MaxDraftPlayersForPosition(pos_ThirdBaseman) * maxTeams);

	posCountVector.add(pos_Catcher,
		MaxDraftPlayersForPosition(pos_Catcher) * maxTeams);
	posCountVector.add(pos_Outfielder,
		MaxDraftPlayersForPosition(pos_Outfielder) * maxTeams);
	posCountVector.add(pos_DesignatedHitter,
		MaxDraftPlayersForPosition(pos_DesignatedHitter) * maxTeams);
		
	posCountVector.add(pos_StartingPitcher,
		MaxDraftPlayersForPosition(pos_StartingPitcher) * maxTeams);
	posCountVector.add(pos_ReliefPitcher,
		MaxDraftPlayersForPosition(pos_ReliefPitcher) * maxTeams);
}

/******************************************************************************/

bool ASBaseballDraftRankingBuilder::isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const
{
	TBaseballPosition pos(profPlayerPtr->getPosition());

	return(pos.isOffensive());
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
