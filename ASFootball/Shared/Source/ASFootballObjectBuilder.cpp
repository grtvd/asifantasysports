/* ASFootballObjectBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballObjectBuilder.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectBuilder.h, used to implement Singleton in derived classes.

ObjectBuilder& tag::getTheObjectBuilder()
{
	static asfootball::ASFootballObjectBuilder builder;
	return(builder);
}

/******************************************************************************/

void* ASFootballObjectBuilder::newInstance(const char* type)
{
	if(fobt_TTeam == type)
		return(new TFootballTeam);
		
	if(fobt_TProfPlayer == type)
		return(new TFootballProfPlayer);
		
	if(fobt_TOffGameStat == type)
		return(new TFootballOffGameStat);
		
	if(fobt_TDefGameStat == type)
		return(new TFootballDefGameStat);
		
	if(fobt_TFootballProfTeamSchedule == type)
		return(new TFootballProfTeamSchedule);
		
	return(ASFantasyObjectBuilder::newInstance(type));
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
