/* ASHockeyObjectBuilder */

/******************************************************************************/
#ifndef ASHockeyObjectBuilderH
#define ASHockeyObjectBuilderH

#include "ASFantasyObjectBuilder.h"
#include "ASHockeyType.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

/* ASHockeyObjectBuilder Types */
//BOB const CStr31 fobt_THockeyProfTeamSchedule("THockeyProfTeamSchedule");

/******************************************************************************/

class ASHockeyObjectBuilder : public ASFantasyObjectBuilder
{
protected:
	ASHockeyObjectBuilder() {}
	
public:
	static ASHockeyObjectBuilder& getThe()
		{ return(dynamic_cast<ASHockeyObjectBuilder&>(ASFantasyObjectBuilder::getThe())); }
		
	virtual void* newInstance(const char* type);

//BOB 	THockeyProfTeamSchedulePtr newHockeyProfTeamSchedule()
//BOB 		{ return(THockeyProfTeamSchedulePtr(
//BOB 			static_cast<THockeyProfTeamSchedule*>(newInstance(fobt_THockeyProfTeamSchedule)))); }

	friend ObjectBuilder& tag::getTheObjectBuilder();
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyObjectBuilderH
/******************************************************************************/
/******************************************************************************/

