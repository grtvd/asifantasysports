/* ASFantasyObjectBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectBuilder.h"
#include "ASFantasyType.h"

using namespace asfantasy;

/******************************************************************************/
/******************************************************************************/

void* ASFantasyObjectBuilder::newInstance(const char* type)
{
	if(fobt_TLeague == type)
		return(new TLeague);

	if(fobt_TProfTeam == type)
		return(new TProfTeam);
				
	if(fobt_TPlayer == type)
		return(new TPlayer);

	if(fobt_TDraftOrder == type)
		return(new TDraftOrder);
		
	if(fobt_TDraftRanking == type)
		return(new TDraftRanking);

	if(fobt_TDraftResult == type)
		return(new TDraftResult);

	if(fobt_TScheduleDay == type)
		return(new TScheduleDay);

	if(fobt_TGameResult == type)
		return(new TGameResult);

	if(fobt_TFreeAgentClaim == type)
		return(new TFreeAgentClaim);

	if(fobt_TTrade == type)
		return(new TTrade);

	return(ASMemberObjectBuilder::newInstance(type));
}

/******************************************************************************/
/******************************************************************************/
