/* ASFootballHtmlObjectServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballAppOptions.h"
#include "ASFootballObjectStore.h"
#include "ASFootballHtmlObjectServer.h"
#include "ASFootballOrbFulfiller.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

CStrVar ASFootballHtmlObjectServer::commErrFileName()
{
	return(BuildFullFileName(ASFootballHomeDir(),"ASFbIsOb.out"));
}

/******************************************************************************/

void ASFootballHtmlObjectServer::addAllShelves()
{
	ASFootballObjectStore& store = ASFootballObjectStore::getThe();

	ASFantasyHtmlObjectServer::addAllShelves();

	store.addProfTeamScheduleShelf();
}

/******************************************************************************/

void ASFootballHtmlObjectServer::delAllShelves()
{
	#if 0	//BOB
	ASFootballObjectStore& store = ASFootballObjectStore::getThe();

	ASFantasyHtmlObjectServer::delAllShelves()

	//BOB come up with better way, need to use GetShelfMode for get[Specific]Shelf
	//BOB This causes problems
	try { store.delAllProfTeamScheduleShelfItems(); } catch(...) {}
	#endif
}

/******************************************************************************/

void ASFootballHtmlObjectServer::loadAllShelves()
{
	ASFootballObjectStore& store = ASFootballObjectStore::getThe();

	ASFantasyHtmlObjectServer::loadAllShelves();

	store.delAllProfTeamScheduleShelfItems();

	store.loadAllProfTeamSchedules();
}

/******************************************************************************/

void ASFootballHtmlObjectServer::fulfillRequest(TStream& inputStream)
{
	TASFantasyFulfillerNotify fulfillerNotify;
	ASFootballOrbFulfiller fulfiller(fulfillerNotify);

	fulfiller.fulfill(inputStream,*fContent);
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
