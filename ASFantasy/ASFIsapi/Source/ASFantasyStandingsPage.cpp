/* ASFantasyStandingsPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyStandingsPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyStandingsPageHtmlView::writeBodyViewBody()
{
	TJavaPanelHtmlView htmlView(fPageOptions,fja_Season,"StandingsApplet",
		getBodyViewWidth(),getBodyViewBodyHeight());

	fHtmlWriter.WriteView(htmlView);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
