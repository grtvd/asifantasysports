/* ASHockeyLineupUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyType.h"
#include "ASHockeyLineupUpdateRqst.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

void ASHockeyLineupUpdateRqst::saveLineups(TTeamPtr teamPtr)
{
	if(fPlayerIDArray.size() != 2)
		throw ASIException("ASHockeyLineupUpdateRqst::saveLineups: number of lineups mismatch");

	teamPtr->lineup(lut_Skater) = fPlayerIDArray[0];
	teamPtr->lineup(lut_Goalie) = fPlayerIDArray[1];
}

/******************************************************************************/

}; //ashockey

/******************************************************************************/
/******************************************************************************/
