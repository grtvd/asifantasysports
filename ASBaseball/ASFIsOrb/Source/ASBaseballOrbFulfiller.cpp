/* ASBaseballOrbFulfiller.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballOrbFulfiller.h"

#include "ASBaseballPlayerScoutRqst.h"
#include "ASBaseballLineupQueryRqst.h"
#include "ASBaseballLineupUpdateRqst.h"

namespace asbaseball
{

/******************************************************************************/

TStreamable* ASBaseballOrbFulfiller::newInstance(const char* classNameStr)
{
	CStrVar className(classNameStr);

	if(className == "PlayerScoutRqst")
		return new ASBaseballPlayerScoutRqst();

	if(className == "LineupQueryRqst")
		return new ASBaseballLineupQueryRqst();

	if(className == "LineupUpdateRqst")
		return new ASBaseballLineupUpdateRqst();

	return(ASFantasyOrbFulfiller::newInstance(className));
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
