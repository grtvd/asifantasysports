/* ASFantasyDraftRankingQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftRankingQueryRqstH
#define ASFantasyDraftRankingQueryRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyType.h"
#include "ASFantasyMiscRqst.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/
//MOVE to separate "type" file

class DraftRankingPlayer;	//forward reference
typedef RefCountPtr<DraftRankingPlayer> DraftRankingPlayerPtr;

class DraftRankingPlayer : public PlayerInfo
{
protected:
	DraftRankingPlayer(const TProfPlayerPtr profPlayerPtr) :
		PlayerInfo(profPlayerPtr) {}

public:
	static DraftRankingPlayerPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr)
		{ return(DraftRankingPlayerPtr(new DraftRankingPlayer(profPlayerPtr))); }
	
	friend class RefCountPtr<DraftRankingPlayer>;
};

/******************************************************************************/

typedef std::vector<DraftRankingPlayerPtr> DraftRankingPlayerVector;

/******************************************************************************/

class DraftRankingQueryRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;

protected:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
public:
	virtual TStreamable* fulfillRequest();

protected:
	void fullPlayerVector(TParticPtr& particPtr,
		DraftRankingPlayerVector& playerVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftRankingQueryRqstH
/******************************************************************************/
/******************************************************************************/
