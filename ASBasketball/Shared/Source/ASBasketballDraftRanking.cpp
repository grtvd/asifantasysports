/* ASBasketballDraftRanking.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballAppOptions.h"
#include "ASBasketballType.h"
#include "ASBasketballDraftRanking.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

void ASBasketballDraftRankingBuilder::getPosCountVector(
	TPosCountVector& posCountVector) const
{
	int maxTeams = MaxTeamsPerPrivateLeague();
	
	posCountVector.erase(posCountVector.begin(),posCountVector.end());

#if 1	//BOB
	for(int i = pos_FirstKeyPos; i <= pos_LastKeyPos; ++i)
		posCountVector.add(i,MaxDraftPlayersForPosition(i) * maxTeams);

#else	//BOB
	posCountVector.add(pos_PointGuard,
		MaxDraftPlayersForPosition(pos_PointGuard) * maxTeams);
	posCountVector.add(pos_ShootingGuard,
		MaxDraftPlayersForPosition(pos_ShootingGuard) * maxTeams);
	posCountVector.add(pos_SmallForward,
		MaxDraftPlayersForPosition(pos_SmallForward) * maxTeams);
	posCountVector.add(pos_PowerForward,
		MaxDraftPlayersForPosition(pos_PowerForward) * maxTeams);
	posCountVector.add(pos_Center,
		MaxDraftPlayersForPosition(pos_Center) * maxTeams);
	posCountVector.add(pos_Center,
		MaxDraftPlayersForPosition(pos_Center) * maxTeams);
	posCountVector.add(pos_Defenseman,
		MaxDraftPlayersForPosition(pos_Defenseman) * maxTeams);
	posCountVector.add(pos_Goalie,
		MaxDraftPlayersForPosition(pos_Goalie) * maxTeams);
#endif	//BOB
}

/******************************************************************************/

bool ASBasketballDraftRankingBuilder::isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const
{
	TBasketballPosition pos(profPlayerPtr->getPosition());

	return(pos.isOffensive());
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
