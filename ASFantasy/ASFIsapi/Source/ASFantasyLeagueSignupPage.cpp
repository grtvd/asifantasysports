/* ASFantasyLeagueSignupPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyLeagueSignupPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyLeagueSignupPageHtmlView::writeBodyViewBody()
{
	TJavaPanelHtmlView htmlView(fPageOptions,fja_Draft,"LeagueSignupApplet",
		getBodyViewWidth(),getBodyViewBodyHeight());

	fHtmlWriter.WriteView(htmlView);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
