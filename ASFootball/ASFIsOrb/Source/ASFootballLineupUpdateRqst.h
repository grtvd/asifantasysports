/* ASFootballLineupUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballLineupUpdateRqstH
#define ASFootballLineupUpdateRqstH

#include "ASFantasyLineupUpdateRqst.h"
#include "ASFootballMiscRqst.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballLineupUpdateRqst : public LineupUpdateRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID)
		{ return(!IsLockoutPeriodInEffect(leagueID)); }

	virtual void saveLineups(TTeamPtr teamPtr);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballLineupUpdateRqstH
/******************************************************************************/
/******************************************************************************/
