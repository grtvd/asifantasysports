/* ASFantasyCustomPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyCustomPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyCustomPageHtmlView::initialize()
{
	fPageTitle = fIsHtmlServer.getStringField("CustomPageTitle",cam_MayNotExist);
	fBodyViewWidth = fIsHtmlServer.getNumericField("CustomBodyViewWidth",
		cam_MayNotExist);
	fFileName = fIsHtmlServer.getStringField("CustomFileName",cam_MayNotExist);
}

/******************************************************************************/

void ASFantasyCustomPageHtmlView::writeBodyViewBody()
{
	fHtmlWriter.InsertFile(BuildFullFileName(AppHomeDir(),fFileName));
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
