/* ASFantasyFreeAgentQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyFreeAgentQueryRqstH
#define ASFantasyFreeAgentQueryRqstH

#include "Requestable.h"
#include "ASFantasyType.h"
#include "ASFantasyMiscRqst.h"

//using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class FreeAgentQueryRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
	void getClaimReleasePlayers(TTeamPtr teamPtr,
		PlayerInfoPtr& claimPlayerInfoPtr,TPlayerID& releasePlayerID);
	void fillRosterPlayerVector(TTeamPtr teamPtr,
		PlayerInfoVector& rosterPlayerVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyFreeAgentQueryRqstH
/******************************************************************************/
/******************************************************************************/
