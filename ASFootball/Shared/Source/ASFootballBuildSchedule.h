/* ASFootballBuildSchedule.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballBuildScheduleH
#define ASFootballBuildScheduleH

#include "ASFantasyBuildSchedule.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballBuildSchedule : public TBuildSchedule
{
protected:
	virtual StaticBuildScheduleGame* getStaticScheduleGameList(int numTeams,
		int& numGames);
};

/******************************************************************************/

}; //asfootball

#endif //ASFootballBuildScheduleH
/******************************************************************************/
/******************************************************************************/
