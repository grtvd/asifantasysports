/* ASBasketballObjectStore.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballObjectStoreH
#define ASBasketballObjectStoreH

#include "ASFantasyObjectStore.h"
#include "ASBasketballObjectBuilder.h"

/******************************************************************************/

namespace asbasketball
{

/******************************************************************************/

class ASBasketballObjectStore : public ASFantasyObjectStore
{
private:
	ASBasketballObjectStore(ASBasketballObjectBuilder& builder);

public:
	static ASBasketballObjectStore& getThe()
		{ return(dynamic_cast<ASBasketballObjectStore&>(ASFantasyObjectStore::getThe())); }
	ASBasketballObjectBuilder& getBuilder()
		{ return(dynamic_cast<ASBasketballObjectBuilder&>(fBuilder)); }

	/**************************************************************************/

	friend ObjectStore& tag::getTheObjectStore();
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballObjectStoreH
/******************************************************************************/
/******************************************************************************/
