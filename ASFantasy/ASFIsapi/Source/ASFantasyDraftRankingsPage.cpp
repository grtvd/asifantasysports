/* ASFantasyDraftRankingsPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDraftRankingsPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyDraftRankingsPageHtmlView::writeBodyViewBody()
{
	TJavaPanelHtmlView htmlView(fPageOptions,fja_Draft,"DraftRankingsApplet",
		getBodyViewWidth(),getBodyViewBodyHeight());

	fHtmlWriter.WriteView(htmlView);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
