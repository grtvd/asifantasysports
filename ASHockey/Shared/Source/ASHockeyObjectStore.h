/* ASHockeyObjectStore.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyObjectStoreH
#define ASHockeyObjectStoreH

#include "ASFantasyObjectStore.h"
#include "ASHockeyObjectBuilder.h"

/******************************************************************************/

namespace ashockey
{

/******************************************************************************/

class ASHockeyObjectStore : public ASFantasyObjectStore
{
private:
	ASHockeyObjectStore(ASHockeyObjectBuilder& builder);

public:
	static ASHockeyObjectStore& getThe()
		{ return(dynamic_cast<ASHockeyObjectStore&>(ASFantasyObjectStore::getThe())); }
	ASHockeyObjectBuilder& getBuilder()
		{ return(dynamic_cast<ASHockeyObjectBuilder&>(fBuilder)); }

	/**************************************************************************/

	friend ObjectStore& tag::getTheObjectStore();
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyObjectStoreH
/******************************************************************************/
/******************************************************************************/
