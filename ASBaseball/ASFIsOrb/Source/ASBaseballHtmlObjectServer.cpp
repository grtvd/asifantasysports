/* ASBaseballHtmlObjectServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballAppOptions.h"
#include "ASBaseballHtmlObjectServer.h"
#include "ASBaseballOrbFulfiller.h"

namespace asbaseball
{

/******************************************************************************/

CStrVar ASBaseballHtmlObjectServer::commErrFileName()
{
	return(BuildFullFileName(ASBaseballHomeDir(),"ASBbIsOb.out"));
}

/******************************************************************************/

void ASBaseballHtmlObjectServer::fulfillRequest(TStream& inputStream)
{
	TASFantasyFulfillerNotify fulfillerNotify;
	ASBaseballOrbFulfiller fulfiller(fulfillerNotify);

	fulfiller.fulfill(inputStream,*fContent);
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
