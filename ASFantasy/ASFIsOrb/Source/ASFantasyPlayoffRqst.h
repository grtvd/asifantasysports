/* ASFantasyPlayoffRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyPlayoffRqstH
#define ASFantasyPlayoffRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class PlayoffTeams : public TStreamable
{
protected:
	// Semi-Finals Game 1
	TTeamID fEastWinnerTeamID;
	byte fEastWinnerScore;
	TTeamID fWestWildCardTeamID;
	byte fWestWildCardScore;

	// Semi-Finals Game 2
	TTeamID fWestWinnerTeamID;
	byte fWestWinnerScore;
	TTeamID fEastWildCardTeamID;
	byte fEastWildCardScore;

	// Finals Game
	TTeamID fFinalistOneTeamID;
	byte fFinalistOneScore;
	TTeamID fFinalistTwoTeamID;
	byte fFinalistTwoScore;

	// League Champ
	TTeamID fLeagueChampTeamID;

public:
	PlayoffTeams(const TLeaguePtr& leaguePtr);

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/

class PlayoffRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual TStreamable* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyPlayoffRqstH
/******************************************************************************/
/******************************************************************************/
