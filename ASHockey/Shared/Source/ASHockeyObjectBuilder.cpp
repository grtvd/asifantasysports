/* ASHockeyObjectBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyObjectBuilder.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

// Declared in ObjectBuilder.h, used to implement Singleton in derived classes.

ObjectBuilder& tag::getTheObjectBuilder()
{
	static ashockey::ASHockeyObjectBuilder builder;
	return(builder);
}

/******************************************************************************/

void* ASHockeyObjectBuilder::newInstance(const char* type)
{
	if(fobt_TTeam == type)
		return(new THockeyTeam);
		
	if(fobt_TProfPlayer == type)
		return(new THockeyProfPlayer);
		
	if(fobt_TOffGameStat == type)
		return(new THockeyOffGameStat);
		
	if(fobt_TDefGameStat == type)
		return(new THockeyDefGameStat);
		
	return(ASFantasyObjectBuilder::newInstance(type));
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
