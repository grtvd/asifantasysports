/* ASBaseballObjectStore.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASBaseballObjectStore.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectStore.h, used to implement Singleton in derived classes.

ObjectStore& tag::getTheObjectStore()
{
	static asbaseball::ASBaseballObjectStore store(
		asbaseball::ASBaseballObjectBuilder::getThe());
	return(store);
}

/******************************************************************************/
/******************************************************************************/

ASBaseballObjectStore::ASBaseballObjectStore(ASBaseballObjectBuilder& builder) :
	ASFantasyObjectStore(builder)
{
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
