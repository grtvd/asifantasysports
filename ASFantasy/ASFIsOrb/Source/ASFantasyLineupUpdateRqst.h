/* ASFantasyLineupUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyLineupUpdateRqstH
#define ASFantasyLineupUpdateRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class LineupUpdateRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;
	std::vector<TPlayerIDVector> fPlayerIDArray;

	// Not read/written
	TPlayerIDVector fTeamPlayerIDVector;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
	virtual bool areChangesAllowed(TLeagueID leagueID) = 0;

	virtual void validateLineup(int whichLineup,
		const TPlayerIDVector& playerIDVector);
	virtual void saveLineups(TTeamPtr teamPtr) = 0;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyLineupUpdateRqstH
/******************************************************************************/
/******************************************************************************/
