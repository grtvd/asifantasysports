/* ASFootballLineupUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballType.h"
#include "ASFootballLineupUpdateRqst.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

void ASFootballLineupUpdateRqst::saveLineups(TTeamPtr teamPtr)
{
	if(fPlayerIDArray.size() != 1)
		throw ASIException("ASFootballLineupUpdateRqst::saveLineups: number of lineups mismatch");

	teamPtr->lineup(lut_Starting) = fPlayerIDArray[0];
}

/******************************************************************************/

}; //asfootball

/******************************************************************************/
/******************************************************************************/
