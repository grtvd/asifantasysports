/* ASFantasyDraftResolver.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftResolverH
#define ASFantasyDraftResolverH

#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class DraftResolver
{
public:
	TDraftResultPtr resolve(const TLeagueID leagueID,int fromRound,int toRound);

protected:
	void setUpDraftPosCountForExistingPlayers(const TLeagueID leagueID);
	bool setNextAvailablePlayer(const TLeagueID leagueID,
		const TTeamID teamID,const TDraftRankingPtr draftRankingPtr,
		TDraftPickVector& draftPickVector);
	void removePickedPlayersFromDraftRankings(const TLeagueID leagueID,
		const TTeamIDVector& teamIDVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftResolverH
/******************************************************************************/
/******************************************************************************/
