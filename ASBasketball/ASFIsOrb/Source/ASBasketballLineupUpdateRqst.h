/* ASBasketballLineupUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballLineupUpdateRqstH
#define ASBasketballLineupUpdateRqstH

#include "ASFantasyLineupUpdateRqst.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballLineupUpdateRqst : public LineupUpdateRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) { return(true); }

	virtual void saveLineups(TTeamPtr teamPtr);
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballLineupUpdateRqstH
/******************************************************************************/
/******************************************************************************/
