/* ASFantasyHtmlObjectServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommType.h"
#include "CommDB.h"
//BOB #include "HtmlWriter.h"
#include "BinaryFiler.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyHtmlObjectServer.h"

namespace asfantasy
{

/******************************************************************************/

TDateTime ASFantasyHtmlObjectServer::fLastStatLoadDate = 0;
bool ASFantasyHtmlObjectServer::fStoreIsSetup = false;

/******************************************************************************/
/******************************************************************************/

void TASFantasyFulfillerNotify::notify(const AnsiString &msg)
{
}

/******************************************************************************/
/******************************************************************************/

ASFantasyHtmlObjectServer::~ASFantasyHtmlObjectServer()
{
//BOB	CloseDatabase(fDatabase);
}

/******************************************************************************/

void ASFantasyHtmlObjectServer::formBuild()
{
	auto_ptr<TStream> pInputStream;

	fContent->Position = 0;

	setup();

	pInputStream.reset(new TMemoryStream);
	getFormDataStream(*pInputStream);
	fulfillRequest(*pInputStream);
}

/******************************************************************************/

void ASFantasyHtmlObjectServer::setup()
{
	if(InSystemMaintMode())
		throw ASIException("Currently in system maintenance mode.");

	try
	{
		OpenDatabase(MemberDatabaseName());
		OpenDatabase(MemberMiscDatabaseName());
		OpenDatabase(PrimaryDatabaseName());
		
		if(!fStoreIsSetup)
		{
			addAllShelves();
			fStoreIsSetup = true;
		}

		if(fLastStatLoadDate != LastStatLoadDate())
		{
			CommErrMsg(cel_Info,"ASFantasyHtmlObjectServer::setup: loading all shelves");
			loadAllShelves();
			fLastStatLoadDate = LastStatLoadDate();
		}

	}
	catch(const Exception& e)
	{
		fStoreIsSetup = false;
		fLastStatLoadDate = TDateTime();
		delAllShelves();
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		fStoreIsSetup = false;
		fLastStatLoadDate = TDateTime();
		delAllShelves();
		throw;
	}
}

/******************************************************************************/

void ASFantasyHtmlObjectServer::addAllShelves()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	store.addProfPlayerShelf();
	store.addProfTeamShelf();
	//BOB store.addProfTeamScheduleShelf();
}

/******************************************************************************/

void ASFantasyHtmlObjectServer::delAllShelves()
{
	#if 0	//BOB
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	//BOB come up with better way, need to use GetShelfMode for get[Specific]Shelf
	//BOB This causes problems
	//BOB try { store.delProfTeamScheduleShelf(); } catch(...) {}
	try { store.delProfTeamShelf(); } catch(...) {}
	try { store.delProfPlayerShelf(); } catch(...) {}
	#endif
}

/******************************************************************************/

void ASFantasyHtmlObjectServer::loadAllShelves()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	store.delAllProfPlayerShelfItems();
	store.delAllProfTeamShelfItems();

	store.loadKeyProfPlayers();
	store.loadAllProfTeams();
	//BOB store.loadAllProfTeamSchedules();
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
