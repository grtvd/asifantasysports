/* ASFootballMiscRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFootballMiscRqst.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

bool IsLockoutPeriodInEffect(const TLeagueID leagueID)
{
	TScheduleDayPtr scheduleDayPtr =
		GetNextScheduleDayForLeagueID(leagueID,
		TDateTime::CurrentTime() > NightlyProcessingTime());

	if(scheduleDayPtr.isNull())	// This should only happen after the last game of the season.
		return(false);

	// If current date/time is before first game of week or after last game of week.
	if((TDateTime::CurrentDateTime() <
				(scheduleDayPtr->getEarlyProfGameDate() +
					scheduleDayPtr->getEarlyProfGameTime())) ||
			(TDateTime::CurrentDateTime() >
				(scheduleDayPtr->getLateProfGameDate() +
					NightlyProcessingTime() + 1.0)))
		return(false);

	return(true);
}

/******************************************************************************/

};	// namespace asfootball

/******************************************************************************/
/******************************************************************************/
