/* ASFantasyDraftResultRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftResultRqstH
#define ASFantasyDraftResultRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyType.h"
#include "ASFantasyMiscRqst.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class DraftResultPlayer;	//forward reference
typedef RefCountPtr<DraftResultPlayer> DraftResultPlayerPtr;

class DraftResultPlayer : public RefCountObject, TStreamable
{
protected:
	byte		fRound;
	byte		fPick;
	TFullName	fName;
	TPosition	fPosition;
	TTeamID		fTeamID;
	
	DraftResultPlayer(byte round, byte pick, TTeamID teamID,
		const TProfPlayerPtr profPlayerPtr);
public:
	static DraftResultPlayerPtr createFromProfPlayer(byte round, byte pick,
		TTeamID teamID, const TProfPlayerPtr profPlayerPtr)
		{ return(DraftResultPlayerPtr(new DraftResultPlayer(
		round,pick,teamID,profPlayerPtr))); }
	void clear() { fRound = 0; fPick = 0; fName.clear(); fPosition = 0; fTeamID.clear(); }
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	friend class RefCountPtr<DraftResultPlayer>;
};

/******************************************************************************/

typedef std::vector<DraftResultPlayerPtr> DraftResultPlayerVector;

/******************************************************************************/

class DraftResultRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual TStreamable* fulfillRequest();

protected:
	void validateRequest(TParticPtr& particPtr,TTeamPtr& teamPtr);
	void fillPlayerVector(TParticPtr& particPtr,TTeamPtr& teamPtr,
		DraftResultPlayerVector& playerVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftResultRqstH
/******************************************************************************/
/******************************************************************************/
