/* ASBasketballDraftRanking.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballDraftRankingH
#define ASBasketballDraftRankingH

#include "ASFantasyDraftRanking.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballDraftRankingBuilder : public ASFantasyDraftRankingBuilder
{
protected:
	virtual void getPosCountVector(TPosCountVector& posCountVector) const;
	virtual bool isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const;
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballDraftRankingH
/******************************************************************************/
/******************************************************************************/
 
