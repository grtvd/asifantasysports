/* ASFootballOrbFulfiller.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballOrbFulfiller.h"

#include "ASFootballPlayerScoutRqst.h"
#include "ASFootballLineupQueryRqst.h"
#include "ASFootballLineupUpdateRqst.h"

namespace asfootball
{

/******************************************************************************/

TStreamable* ASFootballOrbFulfiller::newInstance(const char* classNameStr)
{
	CStrVar className(classNameStr);

	if(className == "PlayerScoutRqst")
		return new ASFootballPlayerScoutRqst();

	if(className == "LineupQueryRqst")
		return new ASFootballLineupQueryRqst();

	if(className == "LineupUpdateRqst")
		return new ASFootballLineupUpdateRqst();

	return(ASFantasyOrbFulfiller::newInstance(className));
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
