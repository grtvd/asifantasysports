/* ASFantasyStatSummaryBuilder.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyStatSummaryBuilderH
#define ASFantasyStatSummaryBuilderH

#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class StatSummaryBuilder
{
protected:
	StatSummaryBuilder() {}
	virtual ~StatSummaryBuilder() {}

public:
	void standAloneBuildAllPlayersForStatPeriod(const TStatPeriod statPeriod);
	void buildAllPlayersForStatPeriod(const TStatPeriod statPeriod);

	void standAloneBuildAllPlayersForThisSeason(const TDateTime asOfDate);
	void buildAllPlayersForThisSeason(const TDateTime asOfDate);

protected:
	void getOffGamesStatsInDateRange(const TOffGameStatVector& offGameStatVector,
		const TDateTime fromDate,const TDateTime toDate,
		TOffGameStatVector& subSetOffGameStatVector);
	void getDefGamesStatsInDateRange(const TDefGameStatVector& defGameStatVector,
		const TDateTime fromDate,const TDateTime toDate,
		TDefGameStatVector& subSetDefGameStatVector);

public:
	// Month/Day prior to first stat available for game (ever, including
	// all historical years).  Can be months prior to be safe.
	virtual void getEarliestPossibleStatMonthDay(int& month,int& day) = 0;

	void getSeasonDateRangeForStatPeriod(const TStatPeriod statPeriod,
		TDateTime& fromDate,TDateTime& toDate);
	void getDateRangeForStatPeriodAsOfDate(const TStatPeriod statPeriod,
		const TDateTime asOfDate,TDateTime& fromDate,TDateTime& toDate);
	
protected:
	void sumPlayerIDVectorForStatPeriodDateRange(
		const TPlayerIDVector& playerIDVector,const TStatPeriod statPeriod,
		const TDateTime fromDate,const TDateTime toDate);

	void sumOffStatsForProfPlayerStatPeriod(const TPlayerID playerID,
		const TStatPeriod statPeriod,const TOffGameStatVector& offGameStatVector);
	void sumOffStatsForProfPlayerDateRange(const TProfPlayerPtr profPlayerPtr,
		const TStatPeriod statPeriod,const TDateTime fromDate,
		const TDateTime toDate);

	void sumDefStatsForProfPlayerStatPeriod(const TPlayerID playerID,
		const TStatPeriod statPeriod,const TDefGameStatVector& defGameStatVector);
	void sumDefStatsForProfPlayerDateRange(const TProfPlayerPtr profPlayerPtr,
		const TStatPeriod statPeriod,const TDateTime fromDate,
		const TDateTime toDate);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyStatSummaryBuilderH
/******************************************************************************/
/******************************************************************************/
 
