/* ASFootballStatSummaryBuilder */

/******************************************************************************/
#ifndef ASFootballStatSummaryBuilderH
#define ASFootballStatSummaryBuilderH

#include "ASFantasyStatSummaryBuilder.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballStatSummaryBuilder : public StatSummaryBuilder
{
public:
	ASFootballStatSummaryBuilder() {}
	
protected:
	virtual void getEarliestPossibleStatMonthDay(int& month,int& day)
		{ month = 7; day = 1; }
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballStatSummaryBuilderH
/******************************************************************************/
/******************************************************************************/
