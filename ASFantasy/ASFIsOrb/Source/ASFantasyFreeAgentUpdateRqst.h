/* ASFantasyFreeAgentUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyFreeAgentUpdateRqstH
#define ASFantasyFreeAgentUpdateRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class FreeAgentUpdateRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;
	TPlayerID fClaimPlayerID;
	TPlayerID fReleasePlayerID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyFreeAgentUpdateRqstH
/******************************************************************************/
/******************************************************************************/
