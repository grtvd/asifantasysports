/* ASFootballPlayerScoutRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballType.h"
#include "ASFootballPlayerScoutRqst.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

PlayerStatValue ASFootballPlayerScoutRqst::getDefaultPlayerStatValue(
	int playerStatType)
{
	if(isPlayerStatTypeOffensive(playerStatType))
		return(TFootballOffGameStat::getDefaultStatStr(playerStatType).c_str());

	return(TFootballDefGameStat::getDefaultStatStr(playerStatType).c_str());
}

/******************************************************************************/

bool ASFootballPlayerScoutRqst::isPlayerStatTypeOffensive(int playerStatType)
{
	FootballPlayerStatType footballPlayerStatType(playerStatType);

	if(footballPlayerStatType == pst_TotalPoints)
		return(true);
		
	return(footballPlayerStatType.isOffensive());
}

/******************************************************************************/

bool ASFootballPlayerScoutRqst::isPlayerStatTypeDefensive(int playerStatType)
{
	FootballPlayerStatType footballPlayerStatType(playerStatType);

	if(footballPlayerStatType == pst_TotalPoints)
		return(true);
		
	return(!footballPlayerStatType.isOffensive());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
