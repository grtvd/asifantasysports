/* ASBaseballLineupQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballType.h"
#include "ASBaseballLineupQueryRqst.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

void ASBaseballLineupQueryRqst::fillPlayerIDArray(const TTeamPtr teamPtr,
	std::vector<TPlayerIDVector>& playerIDArray)
{
	playerIDArray.push_back(teamPtr->lineupConst(lut_Batter));
	playerIDArray.push_back(teamPtr->lineupConst(lut_Pitcher));
}

/******************************************************************************/

}; //asbaseball

/******************************************************************************/
/******************************************************************************/
