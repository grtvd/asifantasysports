/* ASBaseballPlayerScoutRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballType.h"
#include "ASBaseballPlayerScoutRqst.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

PlayerStatValue ASBaseballPlayerScoutRqst::getDefaultPlayerStatValue(
	int playerStatType)
{
	if(isPlayerStatTypeOffensive(playerStatType))
		return(TBaseballOffGameStat::getDefaultStatStr(playerStatType).c_str());

	return(TBaseballDefGameStat::getDefaultStatStr(playerStatType).c_str());
}

/******************************************************************************/

bool ASBaseballPlayerScoutRqst::isPlayerStatTypeOffensive(int playerStatType)
{
	TBaseballPlayerStatType baseballPlayerStatType(playerStatType);

	if((baseballPlayerStatType == pst_TotalPoints) ||
			(baseballPlayerStatType == pst_GamesPlayed) ||
			(baseballPlayerStatType == pst_GamesStarted) ||
			(baseballPlayerStatType == pst_Errors))
		return(true);
		
	return(baseballPlayerStatType.isOffensive());
}

/******************************************************************************/

bool ASBaseballPlayerScoutRqst::isPlayerStatTypeDefensive(int playerStatType)
{
	TBaseballPlayerStatType baseballPlayerStatType(playerStatType);

	if((baseballPlayerStatType == pst_TotalPoints) ||
			(baseballPlayerStatType == pst_GamesPlayed) ||
			(baseballPlayerStatType == pst_GamesStarted) ||
			(baseballPlayerStatType == pst_Errors))
		return(true);
		
	return(!baseballPlayerStatType.isOffensive());
}

/******************************************************************************/

}; // asbaseball

/******************************************************************************/
/******************************************************************************/
