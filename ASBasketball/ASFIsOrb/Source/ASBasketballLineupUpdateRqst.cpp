/* ASBasketballLineupUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballType.h"
#include "ASBasketballLineupUpdateRqst.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

void ASBasketballLineupUpdateRqst::saveLineups(TTeamPtr teamPtr)
{
	if(fPlayerIDArray.size() != 1)
		throw ASIException("ASBasketballLineupUpdateRqst::saveLineups: number of lineups mismatch");

	teamPtr->lineup(lut_Starting) = fPlayerIDArray[0];
}

/******************************************************************************/

}; //asbasketball

/******************************************************************************/
/******************************************************************************/
