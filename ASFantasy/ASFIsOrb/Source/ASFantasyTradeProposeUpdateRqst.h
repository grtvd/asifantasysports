/* ASFantasyTradeProposeUpdateRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTradeProposeUpdateRqstH
#define ASFantasyTradeProposeUpdateRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProposeUpdateRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;
	TTradeID fTradeID;
	TTeamID fProposeToTeamID;
	TPlayerIDVector fGetPlayerIDVector;
	TPlayerIDVector fGivePlayerIDVector;
	TPlayerIDVector fReleasePlayerIDVector;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();
protected:
	void sendEmailNotification(const TTradePtr tradePtr);
	CStrVar sendEmailNotificationPlayers(
		const TPlayerIDVector& playerIDVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTradeProposeUpdateRqstH
/******************************************************************************/
/******************************************************************************/
