/* ASBasketballObjectStore.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASBasketballObjectStore.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectStore.h, used to implement Singleton in derived classes.

ObjectStore& tag::getTheObjectStore()
{
	static asbasketball::ASBasketballObjectStore store(
		asbasketball::ASBasketballObjectBuilder::getThe());
	return(store);
}

/******************************************************************************/
/******************************************************************************/

ASBasketballObjectStore::ASBasketballObjectStore(ASBasketballObjectBuilder& builder) :
	ASFantasyObjectStore(builder)
{
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
