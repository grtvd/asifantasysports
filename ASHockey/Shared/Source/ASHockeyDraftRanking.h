/* ASHockeyDraftRanking.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyDraftRankingH
#define ASHockeyDraftRankingH

#include "ASFantasyDraftRanking.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyDraftRankingBuilder : public ASFantasyDraftRankingBuilder
{
protected:
	virtual void getPosCountVector(TPosCountVector& posCountVector) const;
	virtual bool isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const;
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyDraftRankingH
/******************************************************************************/
/******************************************************************************/
 
