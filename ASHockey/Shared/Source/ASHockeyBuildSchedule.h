/* ASHockeyBuildSchedule.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyBuildScheduleH
#define ASHockeyBuildScheduleH

#include "ASFantasyBuildSchedule.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyBuildSchedule : public TBuildSchedule
{
protected:
	virtual StaticBuildScheduleGame* getStaticScheduleGameList(int numTeams,
		int& numGames);
};

/******************************************************************************/

}; //ashockey

#endif //ASHockeyBuildScheduleH
/******************************************************************************/
/******************************************************************************/
