/* ASFantasyFreeAgentPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyFreeAgentPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyFreeAgentPageHtmlView::initialize()
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();

	TTypeGammaPageHtmlView::initialize();

	if((leaguePtr->getGamePhase() == gmph_PreSeason) ||
		(leaguePtr->getGamePhase() == gmph_Season))
	{
		fInstructions.copy("You may have only one free agent claim pending at "
			"a time.  Submitting a second claim overwrites any previous "
			"pending claim.");

		fAreClaimsAvail = true;
	}
	else
	{
		fInstructions.copy("Free Agent claims are no longer available.");
	}
}

/******************************************************************************/

void ASFantasyFreeAgentPageHtmlView::writeBodyViewBody()
{
	if(fAreClaimsAvail)
	{
		TJavaPanelHtmlView htmlView(fPageOptions,fja_Season,"FreeAgentApplet",
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
