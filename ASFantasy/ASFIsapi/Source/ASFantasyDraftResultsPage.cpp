/* ASFantasyDraftResultsPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyDraftResultsPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyDraftResultsPageHtmlView::initialize()
{
	TLeaguePtr leaguePtr;
	TDateTime draftDate;

	TTypeGammaPageHtmlView::initialize();

	if(fPageOptions.isRqstLeagueSet())
	{
		leaguePtr = fPageOptions.getRqstLeague();
		draftDate = leaguePtr->getDraftDate();

		if(draftDate != TDateTime())
		{
			if(TDateTime::CurrentDateTime() > draftDate + NightlyProcessingTime())
				fAreResultsAvail = true;
		}
	}

	if(fAreResultsAvail)
	{
		fInstructions.copy("Draft Results are now available.");
	}
	else
	{
		if(draftDate != TDateTime())
		{
			fInstructions.copy("Draft Day 1 will take place ");
			fInstructions.concat((draftDate + NightlyProcessingTime()).FormatString(
				ASFantasyStandardDateTimeFormat()).c_str());
			fInstructions.concat(".  Results will be available shortly thereafter.");
		}
		else
			fInstructions.copy("Draft Results are currently not available.");
	}
}

/******************************************************************************/

void ASFantasyDraftResultsPageHtmlView::writeBodyViewBody()
{
	if(fAreResultsAvail)
	{
		TJavaPanelHtmlView htmlView(fPageOptions,fja_Draft,"DraftResultsApplet",
			getBodyViewWidth(),getBodyViewBodyHeight());

		fHtmlWriter.WriteView(htmlView);
	}
	else
		TTypeGammaPageHtmlView::writeBodyViewBody();
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
