/* ASBaseballDraftRanking.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballDraftRankingH
#define ASBaseballDraftRankingH

#include "ASFantasyDraftRanking.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballDraftRankingBuilder : public ASFantasyDraftRankingBuilder
{
protected:
	virtual void getPosCountVector(TPosCountVector& posCountVector) const;
	virtual bool isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const;
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballDraftRankingH
/******************************************************************************/
/******************************************************************************/
 
