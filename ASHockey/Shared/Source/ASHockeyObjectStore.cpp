/* ASHockeyObjectStore.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASHockeyObjectStore.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectStore.h, used to implement Singleton in derived classes.

ObjectStore& tag::getTheObjectStore()
{
	static ashockey::ASHockeyObjectStore store(
		ashockey::ASHockeyObjectBuilder::getThe());
	return(store);
}

/******************************************************************************/
/******************************************************************************/

ASHockeyObjectStore::ASHockeyObjectStore(ASHockeyObjectBuilder& builder) :
	ASFantasyObjectStore(builder)
{
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
