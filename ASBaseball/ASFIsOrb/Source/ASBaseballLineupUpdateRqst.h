/* ASBaseballLineupUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballLineupUpdateRqstH
#define ASBaseballLineupUpdateRqstH

#include "ASFantasyLineupUpdateRqst.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballLineupUpdateRqst : public LineupUpdateRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) { return(true); }

	virtual void saveLineups(TTeamPtr teamPtr);
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballLineupUpdateRqstH
/******************************************************************************/
/******************************************************************************/
