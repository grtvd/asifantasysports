/* ASBaseballObjectBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballObjectBuilder.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectBuilder.h, used to implement Singleton in derived classes.

ObjectBuilder& tag::getTheObjectBuilder()
{
	static asbaseball::ASBaseballObjectBuilder builder;
	return(builder);
}

/******************************************************************************/

void* ASBaseballObjectBuilder::newInstance(const char* type)
{
	if(fobt_TTeam == type)
		return(new TBaseballTeam);
		
	if(fobt_TProfPlayer == type)
		return(new TBaseballProfPlayer);
		
	if(fobt_TOffGameStat == type)
		return(new TBaseballOffGameStat);
		
	if(fobt_TDefGameStat == type)
		return(new TBaseballDefGameStat);
		
	return(ASFantasyObjectBuilder::newInstance(type));
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
