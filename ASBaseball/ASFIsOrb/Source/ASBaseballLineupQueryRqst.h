/* ASBaseballLineupQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballLineupQueryRqstH
#define ASBaseballLineupQueryRqstH

#include "ASFantasyLineupQueryRqst.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballLineupQueryRqst : public LineupQueryRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) { return(true); }
	virtual void fillPlayerIDArray(const TTeamPtr teamPtr,
		std::vector<TPlayerIDVector>& playerIDArray);

	virtual PlayerInfoPtr createNewLineupPlayer(const TProfPlayerPtr profPlayerPtr)
		{ return(LineupPlayer::createFromProfPlayer(profPlayerPtr)); }
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballLineupQueryRqstH
/******************************************************************************/
/******************************************************************************/
