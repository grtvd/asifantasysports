/* ASHockeyHtmlObjectServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyAppOptions.h"
#include "ASHockeyHtmlObjectServer.h"
#include "ASHockeyOrbFulfiller.h"

namespace ashockey
{

/******************************************************************************/

CStrVar ASHockeyHtmlObjectServer::commErrFileName()
{
	return(BuildFullFileName(ASHockeyHomeDir(),"ASHkIsOb.out"));
}

/******************************************************************************/

void ASHockeyHtmlObjectServer::fulfillRequest(TStream& inputStream)
{
	TASFantasyFulfillerNotify fulfillerNotify;
	ASHockeyOrbFulfiller fulfiller(fulfillerNotify);

	fulfiller.fulfill(inputStream,*fContent);
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
