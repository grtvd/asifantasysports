/* ASFootballDraftRanking.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballAppOptions.h"
#include "ASFootballType.h"
#include "ASFootballDraftRanking.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

void ASFootballDraftRankingBuilder::getPosCountVector(
	TPosCountVector& posCountVector) const
{
	int maxTeams = MaxTeamsPerPrivateLeague();

	posCountVector.erase(posCountVector.begin(),posCountVector.end());

	posCountVector.add(pos_Quarterback,
		MaxDraftPlayersForPosition(pos_Quarterback) * maxTeams);

	posCountVector.add(pos_WideReceiver,
		MaxDraftPlayersForPosition(pos_WideReceiver) * maxTeams);
	posCountVector.add(pos_RunningBack,
		MaxDraftPlayersForPosition(pos_RunningBack) * maxTeams);
	posCountVector.add(pos_TightEnd,
		MaxDraftPlayersForPosition(pos_TightEnd) * maxTeams);
		
	posCountVector.add(pos_Kicker,
		MaxDraftPlayersForPosition(pos_Kicker) * maxTeams);
	posCountVector.add(pos_Defense,
		MaxDraftPlayersForPosition(pos_Defense) * maxTeams);
}

/******************************************************************************/

bool ASFootballDraftRankingBuilder::isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const
{
	TFootballPosition pos(profPlayerPtr->getPosition());

	return(pos.isOffensive());
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
