/* ASFootballOrbFulfiller.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballOrbFulfillerH
#define ASFootballOrbFulfillerH

#include "ASFantasyOrbFulfiller.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballOrbFulfiller : public ASFantasyOrbFulfiller
{
public:
	ASFootballOrbFulfiller(TFulfillerNotify &fulfillerNotify) :
		ASFantasyOrbFulfiller(fulfillerNotify) {}
		
	virtual TStreamable *newInstance(const char* className);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFOrbFulfillerH
/******************************************************************************/
/******************************************************************************/
