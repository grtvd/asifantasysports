/* ASFootballLineupQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballLineupQueryRqstH
#define ASFootballLineupQueryRqstH

#include "ASFantasyLineupQueryRqst.h"
#include "ASFootballMiscRqst.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballLineupPlayer : public LineupPlayer
{
protected:
	CStr31 fOppProfTeamGame;

protected:
	ASFootballLineupPlayer(const TProfPlayerPtr profPlayerPtr,
		TFootballProfTeamSchedulePtr profTeamSchedulePtr);

public:
	static PlayerInfoPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr,
		TFootballProfTeamSchedulePtr profTeamSchedulePtr)
		{ return(PlayerInfoPtr(new ASFootballLineupPlayer(profPlayerPtr,
		profTeamSchedulePtr))); }
protected:
	virtual void clear();

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/

class ASFootballLineupQueryRqst : public LineupQueryRqst
{
protected:
	TFootballProfTeamSchedulePtr fProfTeamSchedulePtr;
	TBooleanType fIsProfTeamScheduleLoaded;

protected:
	virtual bool areChangesAllowed(TLeagueID leagueID)
		{ return(!IsLockoutPeriodInEffect(leagueID)); }

	virtual void fillPlayerIDArray(const TTeamPtr teamPtr,
		std::vector<TPlayerIDVector>& playerIDArray);

	TFootballProfTeamSchedulePtr getProfTeamSchedulePtr();

	virtual PlayerInfoPtr createNewLineupPlayer(const TProfPlayerPtr profPlayerPtr)
		{ return(ASFootballLineupPlayer::createFromProfPlayer(profPlayerPtr,
		getProfTeamSchedulePtr())); }
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballLineupQueryRqstH
/******************************************************************************/
/******************************************************************************/
