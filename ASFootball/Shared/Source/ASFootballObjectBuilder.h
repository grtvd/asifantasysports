/* ASFootballObjectBuilder */

/******************************************************************************/
#ifndef ASFootballObjectBuilderH
#define ASFootballObjectBuilderH

#include "ASFantasyObjectBuilder.h"
#include "ASFootballType.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

/* ASFootballObjectBuilder Types */
const CStr31 fobt_TFootballProfTeamSchedule("TFootballProfTeamSchedule");

/******************************************************************************/

class ASFootballObjectBuilder : public ASFantasyObjectBuilder
{
protected:
	ASFootballObjectBuilder() {}
	
public:
	static ASFootballObjectBuilder& getThe()
		{ return(dynamic_cast<ASFootballObjectBuilder&>(ASFantasyObjectBuilder::getThe())); }
		
	virtual void* newInstance(const char* type);

	TFootballProfTeamSchedulePtr newFootballProfTeamSchedule()
		{ return(TFootballProfTeamSchedulePtr(
			static_cast<TFootballProfTeamSchedule*>(newInstance(fobt_TFootballProfTeamSchedule)))); }

	friend ObjectBuilder& tag::getTheObjectBuilder();
};  

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballObjectBuilderH
/******************************************************************************/
/******************************************************************************/

