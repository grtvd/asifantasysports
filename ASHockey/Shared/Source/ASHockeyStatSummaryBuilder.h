/* ASHockeyStatSummaryBuilder */

/******************************************************************************/
#ifndef ASHockeyStatSummaryBuilderH
#define ASHockeyStatSummaryBuilderH

#include "ASFantasyStatSummaryBuilder.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyStatSummaryBuilder : public StatSummaryBuilder
{
public:
	ASHockeyStatSummaryBuilder() {}
	
protected:
	virtual void getEarliestPossibleStatMonthDay(int& month,int& day)
		{ month = 8; day = 1; }
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyStatSummaryBuilderH
/******************************************************************************/
/******************************************************************************/
