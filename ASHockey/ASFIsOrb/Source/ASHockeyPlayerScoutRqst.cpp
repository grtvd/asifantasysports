/* ASHockeyPlayerScoutRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyType.h"
#include "ASHockeyPlayerScoutRqst.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

PlayerStatValue ASHockeyPlayerScoutRqst::getDefaultPlayerStatValue(
	int playerStatType)
{
	if(isPlayerStatTypeOffensive(playerStatType))
		return(THockeyOffGameStat::getDefaultStatStr(playerStatType).c_str());

	return(THockeyDefGameStat::getDefaultStatStr(playerStatType).c_str());
}

/******************************************************************************/

bool ASHockeyPlayerScoutRqst::isPlayerStatTypeOffensive(int playerStatType)
{
	THockeyPlayerStatType hockeyPlayerStatType(playerStatType);

	if((hockeyPlayerStatType == pst_TotalPoints) ||
			(hockeyPlayerStatType == pst_GamesPlayed))
		return(true);

	return(hockeyPlayerStatType.isOffensive());
}

/******************************************************************************/

bool ASHockeyPlayerScoutRqst::isPlayerStatTypeDefensive(int playerStatType)
{
	THockeyPlayerStatType hockeyPlayerStatType(playerStatType);

	if((hockeyPlayerStatType == pst_TotalPoints) ||
			(hockeyPlayerStatType == pst_GamesPlayed))
		return(true);

	return(!hockeyPlayerStatType.isOffensive());
}

/******************************************************************************/

}; // ashockey

/******************************************************************************/
/******************************************************************************/
