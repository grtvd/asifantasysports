/* ASBaseballBuildSchedule.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballBuildScheduleH
#define ASBaseballBuildScheduleH

#include "ASFantasyBuildSchedule.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballBuildSchedule : public TBuildSchedule
{
protected:
	virtual StaticBuildScheduleGame* getStaticScheduleGameList(int numTeams,
		int& numGames);
};

/******************************************************************************/

}; //asbaseball

#endif //ASBaseballBuildScheduleH
/******************************************************************************/
/******************************************************************************/
