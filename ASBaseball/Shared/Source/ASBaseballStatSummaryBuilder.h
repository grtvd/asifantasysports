/* ASBaseballStatSummaryBuilder */

/******************************************************************************/
#ifndef ASBaseballStatSummaryBuilderH
#define ASBaseballStatSummaryBuilderH

#include "ASFantasyStatSummaryBuilder.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballStatSummaryBuilder : public StatSummaryBuilder
{
public:
	ASBaseballStatSummaryBuilder() {}
	
protected:
	virtual void getEarliestPossibleStatMonthDay(int& month,int& day)
		{ month = 2; day = 1; }
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballStatSummaryBuilderH
/******************************************************************************/
/******************************************************************************/
