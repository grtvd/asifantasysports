/* ASFantasyOrbFulfiller.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyOrbFulfillerH
#define ASFantasyOrbFulfillerH

#include "StreamFulfiller.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class ASFantasyOrbFulfiller : public TStreamFulfiller
{
public:
	ASFantasyOrbFulfiller(TFulfillerNotify &fulfillerNotify)
		: TStreamFulfiller(fulfillerNotify) {}
		
	virtual TStreamable *newInstance(const char* className);

	virtual void dbStartTransaction();
	virtual void dbCommitTransaction();
	virtual void dbRollbackTransaction();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyOrbFulfillerH
/******************************************************************************/
/******************************************************************************/

