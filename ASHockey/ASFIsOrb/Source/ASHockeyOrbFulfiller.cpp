/* ASHockeyOrbFulfiller.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyOrbFulfiller.h"

#include "ASHockeyPlayerScoutRqst.h"
#include "ASHockeyLineupQueryRqst.h"
#include "ASHockeyLineupUpdateRqst.h"

namespace ashockey
{

/******************************************************************************/

TStreamable* ASHockeyOrbFulfiller::newInstance(const char* classNameStr)
{
	CStrVar className(classNameStr);

	if(className == "PlayerScoutRqst")
		return new ASHockeyPlayerScoutRqst();

	if(className == "LineupQueryRqst")
		return new ASHockeyLineupQueryRqst();

	if(className == "LineupUpdateRqst")
		return new ASHockeyLineupUpdateRqst();

	return(ASFantasyOrbFulfiller::newInstance(className));
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
