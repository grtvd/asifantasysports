/* ASBasketballPlayerScoutRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballType.h"
#include "ASBasketballPlayerScoutRqst.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

PlayerStatValue ASBasketballPlayerScoutRqst::getDefaultPlayerStatValue(
	int playerStatType)
{
//BOB	if(isPlayerStatTypeOffensive(playerStatType))
		return(TBasketballOffGameStat::getDefaultStatStr(playerStatType).c_str());

//BOB	return(TBasketballDefGameStat::getDefaultStatStr(playerStatType).c_str());
}

/******************************************************************************/

bool ASBasketballPlayerScoutRqst::isPlayerStatTypeOffensive(int playerStatType)
{
#if 1	//BOB
	TBasketballPlayerStatType basketballPlayerStatType(playerStatType);	//validate playerStatType

	return(true);
#else	//BOB
	TBasketballPlayerStatType basketballPlayerStatType(playerStatType);

	if((basketballPlayerStatType == pst_TotalPoints) ||
			(basketballPlayerStatType == pst_GamesPlayed))
		return(true);

	return(basketballPlayerStatType.isOffensive());
#endif	//BOB
}

/******************************************************************************/

bool ASBasketballPlayerScoutRqst::isPlayerStatTypeDefensive(int playerStatType)
{
#if 1	//BOB
	return(false);
#else	//BOB
	TBasketballPlayerStatType basketballPlayerStatType(playerStatType);

	if((basketballPlayerStatType == pst_TotalPoints) ||
			(basketballPlayerStatType == pst_GamesPlayed))
		return(true);

	return(!basketballPlayerStatType.isOffensive());
#endif	//BOB
}

/******************************************************************************/

}; // asbasketball

/******************************************************************************/
/******************************************************************************/
