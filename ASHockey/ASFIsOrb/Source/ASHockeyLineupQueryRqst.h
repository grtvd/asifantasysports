/* ASHockeyLineupQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyLineupQueryRqstH
#define ASHockeyLineupQueryRqstH

#include "ASFantasyLineupQueryRqst.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyLineupQueryRqst : public LineupQueryRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) { return(true); }
	virtual void fillPlayerIDArray(const TTeamPtr teamPtr,
		std::vector<TPlayerIDVector>& playerIDArray);

	virtual PlayerInfoPtr createNewLineupPlayer(const TProfPlayerPtr profPlayerPtr)
		{ return(LineupPlayer::createFromProfPlayer(profPlayerPtr)); }
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyLineupQueryRqstH
/******************************************************************************/
/******************************************************************************/
