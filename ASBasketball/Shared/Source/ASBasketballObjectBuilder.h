/* ASBasketballObjectBuilder */

/******************************************************************************/
#ifndef ASBasketballObjectBuilderH
#define ASBasketballObjectBuilderH

#include "ASFantasyObjectBuilder.h"
#include "ASBasketballType.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

/* ASBasketballObjectBuilder Types */
//BOB const CStr31 fobt_TBasketballProfTeamSchedule("TBasketballProfTeamSchedule");

/******************************************************************************/

class ASBasketballObjectBuilder : public ASFantasyObjectBuilder
{
protected:
	ASBasketballObjectBuilder() {}
	
public:
	static ASBasketballObjectBuilder& getThe()
		{ return(dynamic_cast<ASBasketballObjectBuilder&>(ASFantasyObjectBuilder::getThe())); }
		
	virtual void* newInstance(const char* type);

//BOB 	TBasketballProfTeamSchedulePtr newBasketballProfTeamSchedule()
//BOB 		{ return(TBasketballProfTeamSchedulePtr(
//BOB 			static_cast<TBasketballProfTeamSchedule*>(newInstance(fobt_TBasketballProfTeamSchedule)))); }

	friend ObjectBuilder& tag::getTheObjectBuilder();
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballObjectBuilderH
/******************************************************************************/
/******************************************************************************/

