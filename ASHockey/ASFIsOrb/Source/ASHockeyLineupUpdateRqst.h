/* ASHockeyLineupUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyLineupUpdateRqstH
#define ASHockeyLineupUpdateRqstH

#include "ASFantasyLineupUpdateRqst.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyLineupUpdateRqst : public LineupUpdateRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) { return(true); }

	virtual void saveLineups(TTeamPtr teamPtr);
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyLineupUpdateRqstH
/******************************************************************************/
/******************************************************************************/
