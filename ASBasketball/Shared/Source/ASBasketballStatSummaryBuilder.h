/* ASBasketballStatSummaryBuilder */

/******************************************************************************/
#ifndef ASBasketballStatSummaryBuilderH
#define ASBasketballStatSummaryBuilderH

#include "ASFantasyStatSummaryBuilder.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballStatSummaryBuilder : public StatSummaryBuilder
{
public:
	ASBasketballStatSummaryBuilder() {}
	
protected:
	virtual void getEarliestPossibleStatMonthDay(int& month,int& day)
		{ month = 9; day = 1; }
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballStatSummaryBuilderH
/******************************************************************************/
/******************************************************************************/
