/* ASFootballObjectStore.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASFootballObjectStore.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectStore.h, used to implement Singleton in derived classes.

ObjectStore& tag::getTheObjectStore()
{
	static asfootball::ASFootballObjectStore store(
		asfootball::ASFootballObjectBuilder::getThe());
	return(store);
}

/******************************************************************************/
/******************************************************************************/

ASFootballObjectStore::ASFootballObjectStore(ASFootballObjectBuilder& builder) :
	ASFantasyObjectStore(builder)
{
}

/******************************************************************************/
/******************************************************************************/

void ASFootballObjectStore::addProfTeamScheduleShelf()
{
	addShelf(dynamic_cast<PObjectShelfBase>(new ProfTeamScheduleObjectShelf(
		dynamic_cast<ASFootballObjectBuilder&>(fBuilder))));
}

/******************************************************************************/

void ASFootballObjectStore::delAllProfTeamScheduleShelfItems()
{
	ProfTeamScheduleObjectShelf* pShelf = getProfTeamScheduleShelf();
	pShelf->delAllItems();
}

/******************************************************************************/
/******************************************************************************/

void ASFootballObjectStore::addProfTeamSchedule(
	TFootballProfTeamSchedulePtr profTeamSchedulePtr)
{
	ObjectShelfKeyType shelfKey = getProfTeamScheduleShelfKey();
	ObjectShelfItemKey<TProfGameWeek> key(profTeamSchedulePtr->getProfGameWeek());
	ObjectShelfItem<TFootballProfTeamSchedulePtr> item(profTeamSchedulePtr);

	addItem(shelfKey,key,item);
}

/******************************************************************************/

TFootballProfTeamSchedulePtr ASFootballObjectStore::getProfTeamSchedule(
	TProfGameWeek profGameWeek,GetItemMode getItemMode)
{
	ObjectShelfKeyType shelfKey = getProfTeamScheduleShelfKey();
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;
	ObjectShelfItemKey<TProfGameWeek> key(profGameWeek);
	ObjectShelfItem<TFootballProfTeamSchedulePtr> item;

	if(getItem(shelfKey, key, item, getItemMode))
		profTeamSchedulePtr = item.getItem();

	return(profTeamSchedulePtr);
}

/******************************************************************************/

void ASFootballObjectStore::delProfTeamSchedule(TProfGameWeek profGameWeek)
{
	ObjectShelfKeyType shelfKey = getProfTeamScheduleShelfKey();
	ObjectShelfItemKey<TProfGameWeek> key(profGameWeek);

	delItem(shelfKey, key);
}

/******************************************************************************/
/******************************************************************************/

void ASFootballObjectStore::loadAllProfTeamSchedules()
{
	TQuery* pQuery = NULL;
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;

	// Find all Schedules
	try
	{
		pQuery = OpenQuery(PrimaryDatabaseName(),
			"select * from ProfTeamSchedule order by ProfGameWeek");
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			profTeamSchedulePtr = TFootballProfTeamSchedule::newInstance();
			profTeamSchedulePtr->load(*pQuery);
			addProfTeamSchedule(profTeamSchedulePtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
