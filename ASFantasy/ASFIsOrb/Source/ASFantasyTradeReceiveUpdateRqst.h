/* ASFantasyTradeReceiveUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTradeReceiveUpdateRqstH
#define ASFantasyTradeReceiveUpdateRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class TradeReceiveUpdateRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;
	TTradeID fTradeID;
	bool fAccept;
	TPlayerIDVector fReleasePlayerIDVector;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTradeReceiveUpdateRqstH
/******************************************************************************/
/******************************************************************************/
