/* ASBasketballObjectBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballObjectBuilder.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectBuilder.h, used to implement Singleton in derived classes.

ObjectBuilder& tag::getTheObjectBuilder()
{
	static asbasketball::ASBasketballObjectBuilder builder;
	return(builder);
}

/******************************************************************************/

void* ASBasketballObjectBuilder::newInstance(const char* type)
{
	if(fobt_TTeam == type)
		return(new TBasketballTeam);
		
	if(fobt_TProfPlayer == type)
		return(new TBasketballProfPlayer);
		
	if(fobt_TOffGameStat == type)
		return(new TBasketballOffGameStat);
		
	//BOB if(fobt_TDefGameStat == type)
	//BOB 	return(new TBasketballDefGameStat);
		
	return(ASFantasyObjectBuilder::newInstance(type));
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
