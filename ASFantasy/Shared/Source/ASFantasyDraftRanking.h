/* ASFantasyDraftRanking.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftRankingH
#define ASFantasyDraftRankingH

#include <vector.h>
#include <map.h>

#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

// Tracks how many ProfPlayers should be rank for a particular position.

class TPosCountVector : public std::map<TPosition, int, std::less<TPosition> >
{
public:
	void add(TPosition pos,int count)
		{ insert(value_type(pos,count)); }
};

/******************************************************************************/

class TProfPlayerStat
{
public:
	TProfPlayerPtr fProfPlayerPtr;
	double fStat;

	TProfPlayerStat(TProfPlayerPtr profPlayerPtr = TProfPlayerPtr(),double stat = 0.0)
		{ fProfPlayerPtr = profPlayerPtr; fStat = stat; }
};

class TProfPlayerStatVector : public std::vector<TProfPlayerStat>
{
public:
	void sort() { std::sort(begin(),end(), sortCompare() ); }
	
protected:
	struct sortCompare
	{
		bool operator() (const TProfPlayerStat& x, const TProfPlayerStat& y) const;
	};
};

/******************************************************************************/

class ASFantasyDraftRankingBuilder
{
public:
	void build();

protected:
	virtual void getPosCountVector(TPosCountVector& posCountVector) const = 0;
	
	void loadProfPlayerStatVector(TProfPlayerStatVector& profPlayerStatVector);
	void calcStatsForAllProfPlayers(TProfPlayerStatVector& profPlayerStatVector);
	virtual bool isOffensivePlayer(TProfPlayerPtr profPlayerPtr) const = 0;
	double calcStatForProfPlayer(TProfPlayerPtr profPlayerPtr);
	void removeProfPlayerByPosCount(TProfPlayerStatVector& profPlayerStatVector);
	void printDraftRanking(const TProfPlayerStatVector& profPlayerStatVector);
	
	void createDraftRanking(const TProfPlayerStatVector& profPlayerStatVector);
	void updateAllDraftRankings(const TDraftRankingPtr defaultDraftRankingPtr);
};

/******************************************************************************/

class ASFantasyDraftRankingReseter
{
public:
	static void reset(const TTeamID teamID);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftRankingH
/******************************************************************************/
/******************************************************************************/
