/* ASBasketballBuildSchedule.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballBuildScheduleH
#define ASBasketballBuildScheduleH

#include "ASFantasyBuildSchedule.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballBuildSchedule : public TBuildSchedule
{
protected:
	virtual StaticBuildScheduleGame* getStaticScheduleGameList(int numTeams,
		int& numGames);
};

/******************************************************************************/

}; //asbasketball

#endif //ASBasketballBuildScheduleH
/******************************************************************************/
/******************************************************************************/
