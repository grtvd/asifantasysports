/* ASFantasyCreateLineup.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyCreateLineupH
#define ASFantasyCreateLineupH

#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

void CreateLineupForTeam(const TTeamPtr& teamPtr, 
	const TDraftResultPtr& draftResultPtr,
	const TPositionVector& posVector, TPlayerIDVector& lineup );
void CreateDefaultLineupForLeague(const TLeaguePtr& leaguePtr,
	const TTeamVector& teamVector,TDraftResultPtr draftResultPtr,
	const TLineup lineup);

/******************************************************************************/

}; //namespace asfantasy

#endif //CreateLineup
/******************************************************************************/
/******************************************************************************/
