/* ASBasketballLineupQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballType.h"
#include "ASBasketballLineupQueryRqst.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

void ASBasketballLineupQueryRqst::fillPlayerIDArray(const TTeamPtr teamPtr,
	std::vector<TPlayerIDVector>& playerIDArray)
{
	playerIDArray.push_back(teamPtr->lineupConst(lut_Starting));
}

/******************************************************************************/

}; //asbasketball

/******************************************************************************/
/******************************************************************************/
