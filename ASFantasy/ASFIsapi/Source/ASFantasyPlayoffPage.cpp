/* ASFantasyPlayoffPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyPlayoffPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyPlayoffPageHtmlView::writeBodyViewBody()
{
	TJavaPanelHtmlView htmlView(fPageOptions,fja_Season,"PlayoffApplet",
		getBodyViewWidth(),getBodyViewBodyHeight());

	fHtmlWriter.WriteView(htmlView);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
