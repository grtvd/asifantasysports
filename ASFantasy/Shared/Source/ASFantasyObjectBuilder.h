/* ASFantasyObjectBuilder.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyObjectBuilderH
#define ASFantasyObjectBuilderH

#include "ASMemberObjectBuilder.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

/* ASFantasyObjectBuilder Types */
const CStr31 fobt_TLeague("TLeague");
const CStr31 fobt_TTeam("TTeam");
const CStr31 fobt_TProfPlayer("TProfPlayer");
const CStr31 fobt_TProfTeam("TProfTeam");
const CStr31 fobt_TPlayer("TPlayer");
const CStr31 fobt_TOffGameStat("TOffGameStat");
const CStr31 fobt_TDefGameStat("TDefGameStat");

const CStr31 fobt_TDraftOrder("TDraftOrder");
const CStr31 fobt_TDraftRanking("TDraftRanking");
const CStr31 fobt_TDraftResult("TDraftResult");

const CStr31 fobt_TScheduleDay("TScheduleDay");
const CStr31 fobt_TGameResult("TGameResult");
const CStr31 fobt_TFreeAgentClaim("TFreeAgentClaim");
const CStr31 fobt_TTrade("TTrade");

/******************************************************************************/

class ASFantasyObjectBuilder : public ASMemberObjectBuilder
{
protected:
	ASFantasyObjectBuilder() {}
	
public:
	static ASFantasyObjectBuilder& getThe()
		{ return(dynamic_cast<ASFantasyObjectBuilder&>(ObjectBuilder::getThe())); }

	virtual void* newInstance(const char* type);

	/* Helper Functions */
	TMemberPtr newMember()
		{ return(TMemberPtr(static_cast<TMember*>(newInstance(mobt_TMember)))); }
		
	TParticPtr newPartic()
		{ return(TParticPtr(static_cast<TPartic*>(newInstance(mobt_TPartic)))); }
		
	TLeaguePtr newLeague() 
		{ return(TLeaguePtr(static_cast<TLeague*>(newInstance(fobt_TLeague)))); }
		
	TTeamPtr newTeam()
		{ return(TTeamPtr(static_cast<TTeam*>(newInstance(fobt_TTeam)))); }
		
	TProfPlayerPtr newProfPlayer()
		{ return(TProfPlayerPtr(static_cast<TProfPlayer*>(newInstance(fobt_TProfPlayer)))); }

	TProfTeamPtr newProfTeam()
		{ return(TProfTeamPtr(static_cast<TProfTeam*>(newInstance(fobt_TProfTeam)))); }
		
	TPlayerPtr newPlayer()
		{ return(TPlayerPtr(static_cast<TPlayer*>(newInstance(fobt_TPlayer)))); }
		
	TOffGameStatPtr newOffGameStat()
		{ return(TOffGameStatPtr(static_cast<TOffGameStat*>(newInstance(fobt_TOffGameStat)))); }
		
	TDefGameStatPtr newDefGameStat()
		{ return(TDefGameStatPtr(static_cast<TDefGameStat*>(newInstance(fobt_TDefGameStat)))); }
		
	TDraftOrderPtr newDraftOrder()
		{ return(TDraftOrderPtr(static_cast<TDraftOrder*>(newInstance(fobt_TDraftOrder)))); }
		
	TDraftRankingPtr newDraftRanking()
		{ return(TDraftRankingPtr(static_cast<TDraftRanking*>(newInstance(fobt_TDraftRanking)))); }
		
	TDraftResultPtr newDraftResult()
		{ return(TDraftResultPtr(static_cast<TDraftResult*>(newInstance(fobt_TDraftResult)))); }

	TScheduleDayPtr newScheduleDay()
		{ return(TScheduleDayPtr(static_cast<TScheduleDay*>(newInstance(fobt_TScheduleDay)))); }
		
	TGameResultPtr newGameResult()
		{ return(TGameResultPtr(static_cast<TGameResult*>(newInstance(fobt_TGameResult)))); }
		
	TFreeAgentClaimPtr newFreeAgentClaim()
		{ return(TFreeAgentClaimPtr(static_cast<TFreeAgentClaim*>(newInstance(fobt_TFreeAgentClaim)))); }

	TTradePtr newTrade()
		{ return(TTradePtr(static_cast<TTrade*>(newInstance(fobt_TTrade)))); }
};

/******************************************************************************/

}; //namespace tag

#endif //ASFantasyObjectBuilderH
/******************************************************************************/
/******************************************************************************/

