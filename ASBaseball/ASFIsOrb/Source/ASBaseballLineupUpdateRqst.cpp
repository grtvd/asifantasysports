/* ASBaseballLineupUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballType.h"
#include "ASBaseballLineupUpdateRqst.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

void ASBaseballLineupUpdateRqst::saveLineups(TTeamPtr teamPtr)
{
	if(fPlayerIDArray.size() != 2)
		throw ASIException("ASBaseballLineupUpdateRqst::saveLineups: number of lineups mismatch");

	teamPtr->lineup(lut_Batter) = fPlayerIDArray[0];
	teamPtr->lineup(lut_Pitcher) = fPlayerIDArray[1];
}

/******************************************************************************/

}; //asbaseball

/******************************************************************************/
/******************************************************************************/
