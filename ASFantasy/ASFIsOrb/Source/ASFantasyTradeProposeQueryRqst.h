/* ASFantasyTradeProposeQueryRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTradeProposeQueryRqstH
#define ASFantasyTradeProposeQueryRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProposeQueryRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;
	TTradeID fTradeID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTradeProposeQueryRqstH
/******************************************************************************/
/******************************************************************************/
