/* ASFootballObjectShelf.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballObjectShelfH
#define ASFootballObjectShelfH

#include "ObjectStore.h"
#include "ASFootballType.h"
#include "ASFootballObjectBuilder.h"

namespace asfootball
{

/******************************************************************************/

class ProfTeamScheduleObjectShelf : public ObjectShelf<TProfGameWeek,
	TFootballProfTeamSchedulePtr>
{
public:
	ProfTeamScheduleObjectShelf(ASFootballObjectBuilder& builder) :
		ObjectShelf<TProfGameWeek,TFootballProfTeamSchedulePtr>(builder) {}

	TFootballProfTeamSchedulePtr findByContainsGameDate(
		TDateTime gameDate,CommonAccessMode getMode);
	TFootballProfTeamSchedulePtr findCurrentAsOfToday(CommonAccessMode getMode);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballObjectShelfH
/******************************************************************************/
/******************************************************************************/


