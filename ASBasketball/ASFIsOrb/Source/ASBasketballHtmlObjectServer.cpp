/* ASBasketballHtmlObjectServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballAppOptions.h"
#include "ASBasketballHtmlObjectServer.h"
#include "ASBasketballOrbFulfiller.h"

namespace asbasketball
{

/******************************************************************************/

CStrVar ASBasketballHtmlObjectServer::commErrFileName()
{
	return(BuildFullFileName(ASBasketballHomeDir(),"ASBkIsOb.out"));
}

/******************************************************************************/

void ASBasketballHtmlObjectServer::fulfillRequest(TStream& inputStream)
{
	TASFantasyFulfillerNotify fulfillerNotify;
	ASBasketballOrbFulfiller fulfiller(fulfillerNotify);

	fulfiller.fulfill(inputStream,*fContent);
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
