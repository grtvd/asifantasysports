/* ASFootballDraftRanking.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballDraftRankingH
#define ASFootballDraftRankingH

#include "ASFantasyDraftRanking.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballDraftRankingBuilder : public ASFantasyDraftRankingBuilder
{
public:
	virtual void getPosCountVector(TPosCountVector& posCountVector) const;
	virtual bool isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const;
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballDraftRankingH
/******************************************************************************/
/******************************************************************************/
 
