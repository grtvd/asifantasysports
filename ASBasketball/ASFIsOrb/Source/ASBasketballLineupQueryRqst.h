/* ASBasketballLineupQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballLineupQueryRqstH
#define ASBasketballLineupQueryRqstH

#include "ASFantasyLineupQueryRqst.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballLineupQueryRqst : public LineupQueryRqst
{
protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) { return(true); }
	virtual void fillPlayerIDArray(const TTeamPtr teamPtr,
		std::vector<TPlayerIDVector>& playerIDArray);

	virtual PlayerInfoPtr createNewLineupPlayer(const TProfPlayerPtr profPlayerPtr)
		{ return(LineupPlayer::createFromProfPlayer(profPlayerPtr)); }
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballLineupQueryRqstH
/******************************************************************************/
/******************************************************************************/
