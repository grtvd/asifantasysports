/* ASBasketballOrbFulfiller.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballOrbFulfiller.h"

#include "ASBasketballPlayerScoutRqst.h"
#include "ASBasketballLineupQueryRqst.h"
#include "ASBasketballLineupUpdateRqst.h"

namespace asbasketball
{

/******************************************************************************/

TStreamable* ASBasketballOrbFulfiller::newInstance(const char* classNameStr)
{
	CStrVar className(classNameStr);

	if(className == "PlayerScoutRqst")
		return new ASBasketballPlayerScoutRqst();

	if(className == "LineupQueryRqst")
		return new ASBasketballLineupQueryRqst();

	if(className == "LineupUpdateRqst")
		return new ASBasketballLineupUpdateRqst();

	return(ASFantasyOrbFulfiller::newInstance(className));
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
