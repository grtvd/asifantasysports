/* ASFantasyTradeProtestUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTradeProtestUpdateRqstH
#define ASFantasyTradeProtestUpdateRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProtestUpdateRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;
	TTradeID fTradeID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTradeProtestUpdateRqstH
/******************************************************************************/
/******************************************************************************/
