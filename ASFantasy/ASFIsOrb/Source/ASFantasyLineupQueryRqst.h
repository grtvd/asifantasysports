/* ASFantasyLineupQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyLineupQueryRqstH
#define ASFantasyLineupQueryRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyType.h"
#include "ASFantasyMiscRqst.h"

namespace asfantasy
{

/******************************************************************************/

class LineupPlayer : public PlayerInfoExt
{
protected:
	LineupPlayer(const TProfPlayerPtr profPlayerPtr);
public:
	static PlayerInfoPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr)
		{ return(PlayerInfoPtr(new LineupPlayer(profPlayerPtr))); }
	virtual void clear();

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/

class LineupQueryRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;
	TTeamID fShowTeamID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) = 0;
	virtual void fillPlayerIDArray(const TTeamPtr teamPtr,
		std::vector<TPlayerIDVector>& playerIDArray) = 0;

	void fillLineupPlayerVector(TTeamPtr teamPtr,
		PlayerInfoVector& lineupPlayerVector);
	virtual PlayerInfoPtr createNewLineupPlayer(
		const TProfPlayerPtr profPlayerPtr) = 0;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyLineupQueryRqstH
/******************************************************************************/
/******************************************************************************/
