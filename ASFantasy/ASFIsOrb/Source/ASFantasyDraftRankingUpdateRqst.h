/* ASFantasyDraftRankingUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftRankingUpdateRqstH
#define ASFantasyDraftRankingUpdateRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class DraftRankingUpdateRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;
	TPlayerIDVector fPlayerIDVector;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftRankingUpdateRqstH
/******************************************************************************/
/******************************************************************************/
