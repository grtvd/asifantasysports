/* ASBaseballObjectBuilder */

/******************************************************************************/
#ifndef ASBaseballObjectBuilderH
#define ASBaseballObjectBuilderH

#include "ASFantasyObjectBuilder.h"
#include "ASBaseballType.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

/* ASBaseballObjectBuilder Types */
//BOB const CStr31 fobt_TBaseballProfTeamSchedule("TBaseballProfTeamSchedule");

/******************************************************************************/

class ASBaseballObjectBuilder : public ASFantasyObjectBuilder
{
protected:
	ASBaseballObjectBuilder() {}
	
public:
	static ASBaseballObjectBuilder& getThe()
		{ return(dynamic_cast<ASBaseballObjectBuilder&>(ASFantasyObjectBuilder::getThe())); }
		
	virtual void* newInstance(const char* type);

//BOB 	TBaseballProfTeamSchedulePtr newBaseballProfTeamSchedule()
//BOB 		{ return(TBaseballProfTeamSchedulePtr(
//BOB 			static_cast<TBaseballProfTeamSchedule*>(newInstance(fobt_TBaseballProfTeamSchedule)))); }

	friend ObjectBuilder& tag::getTheObjectBuilder();
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballObjectBuilderH
/******************************************************************************/
/******************************************************************************/
