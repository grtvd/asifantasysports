/* ASFantasyTradeProposeTeamRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTradeProposeTeamRqstH
#define ASFantasyTradeProposeTeamRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProposeTeamRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;
	TTeamID fProposeToTeamID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTradeProposeTeamRqstH
/******************************************************************************/
/******************************************************************************/
