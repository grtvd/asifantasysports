/* ASHockeyOrbFulfiller.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyOrbFulfillerH
#define ASHockeyOrbFulfillerH

#include "ASFantasyOrbFulfiller.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyOrbFulfiller : public ASFantasyOrbFulfiller
{
public:
	ASHockeyOrbFulfiller(TFulfillerNotify &fulfillerNotify) :
		ASFantasyOrbFulfiller(fulfillerNotify) {}

	virtual TStreamable *newInstance(const char* className);
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyOrbFulfillerH
/******************************************************************************/
/******************************************************************************/
