/* ASBaseballOrbFulfiller.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballOrbFulfillerH
#define ASBaseballOrbFulfillerH

#include "ASFantasyOrbFulfiller.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballOrbFulfiller : public ASFantasyOrbFulfiller
{
public:
	ASBaseballOrbFulfiller(TFulfillerNotify &fulfillerNotify) :
		ASFantasyOrbFulfiller(fulfillerNotify) {}
		
	virtual TStreamable *newInstance(const char* className);
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballOrbFulfillerH
/******************************************************************************/
/******************************************************************************/
