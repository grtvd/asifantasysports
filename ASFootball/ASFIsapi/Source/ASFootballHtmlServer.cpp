/* ASFootballHtmlServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDir.h"

#include "ASFootballAppOptions.h"
#include "ASFootballHtmlServer.h"

#include "ASFootballHubPage.h"

namespace asfootball
{

/******************************************************************************/

CStrVar ASFootballHtmlServer::commErrFileName()
{
	return(BuildFullFileName(ASFootballHomeDir(),"ASFbIsa.out"));
}

/******************************************************************************/

ASFantasyBasePageHtmlViewPtr ASFootballHtmlServer::createNewPage(int htmlPage,
	THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter)
{
	if(htmlPage == htmlHubPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFootballHubPageHtmlView(*this,
			pageOptions,htmlWriter)));

	return(ASFantasyHtmlServer::createNewPage(htmlPage,pageOptions,htmlWriter));
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
