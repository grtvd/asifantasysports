/* ASBasketballOrbFulfiller.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballOrbFulfillerH
#define ASBasketballOrbFulfillerH

#include "ASFantasyOrbFulfiller.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballOrbFulfiller : public ASFantasyOrbFulfiller
{
public:
	ASBasketballOrbFulfiller(TFulfillerNotify &fulfillerNotify) :
		ASFantasyOrbFulfiller(fulfillerNotify) {}

	virtual TStreamable *newInstance(const char* className);
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballOrbFulfillerH
/******************************************************************************/
/******************************************************************************/
