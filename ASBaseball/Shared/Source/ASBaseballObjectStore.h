/* ASBaseballObjectStore.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballObjectStoreH
#define ASBaseballObjectStoreH

#include "ASFantasyObjectStore.h"
#include "ASBaseballObjectBuilder.h"

/******************************************************************************/

namespace asbaseball
{

/******************************************************************************/

class ASBaseballObjectStore : public ASFantasyObjectStore
{
private:
	ASBaseballObjectStore(ASBaseballObjectBuilder& builder);

public:
	static ASBaseballObjectStore& getThe()
		{ return(dynamic_cast<ASBaseballObjectStore&>(ASFantasyObjectStore::getThe())); }
	ASBaseballObjectBuilder& getBuilder()
		{ return(dynamic_cast<ASBaseballObjectBuilder&>(fBuilder)); }

	/**************************************************************************/

	friend ObjectStore& tag::getTheObjectStore();
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballObjectStoreH
/******************************************************************************/
/******************************************************************************/
