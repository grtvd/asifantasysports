/* ASFootballHubPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballHubPage.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

bool ASFootballLineupMessageHtmlView::show()
{
	TScheduleDayGame scheduleDayGame;
	
	fScheduleDayPtr = fScheduleDayVector.getInProgressScheduleDay();
	if(!fScheduleDayPtr.isNull())
		fLineupIsLocked = true;
	else
	{
		fScheduleDayPtr = fScheduleDayVector.getFirstNotStartedScheduleDay();
		if(!fScheduleDayPtr.isNull())
		{
			TDateTime lineupLockoutTime = fScheduleDayPtr->getEarlyProfGameDate()
				+ fScheduleDayPtr->getEarlyProfGameTime();

			if(TDateTime::CurrentDateTime() > lineupLockoutTime)
				fLineupIsLocked = true;
		}
	}

	if(!fScheduleDayPtr.isNull())
	{
		if(fScheduleDayPtr->getScheduleDayGameByTeamID(
			fPageOptions.getRqstTeam()->getTeamID(),scheduleDayGame))
		{
			return(true);
		}
	}

	return(false);
}

/******************************************************************************/
/******************************************************************************/

void ASFootballHubPageHtmlView::buildLineupMessage(
	const TScheduleDayVector& scheduleDayVector)
{
	writeItemRow(ASFootballLineupMessageHtmlView(fPageOptions,scheduleDayVector));
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
