/* ASFantasyLineupPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyLineupPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyLineupPageHtmlView::writeBodyViewBody()
{
	TJavaPanelHtmlView htmlView(fPageOptions,fja_Season,"LineupApplet",
		getBodyViewWidth(),getBodyViewBodyHeight());

	fHtmlWriter.WriteView(htmlView);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
