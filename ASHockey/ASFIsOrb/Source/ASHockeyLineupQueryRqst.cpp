/* ASHockeyLineupQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyType.h"
#include "ASHockeyLineupQueryRqst.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

void ASHockeyLineupQueryRqst::fillPlayerIDArray(const TTeamPtr teamPtr,
	std::vector<TPlayerIDVector>& playerIDArray)
{
	playerIDArray.push_back(teamPtr->lineupConst(lut_Skater));
	playerIDArray.push_back(teamPtr->lineupConst(lut_Goalie));
}

/******************************************************************************/

}; //ashockey

/******************************************************************************/
/******************************************************************************/
