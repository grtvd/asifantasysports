/* ASFantasyTradePage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTradePageH
#define ASFantasyTradePageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyTradePageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	TTradeID fTradeID;
	bool fAreTradesAvail;
	CStrVar fInstructions;
	CStrVar fJavaClass;

protected:
	ASFantasyTradePageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter),
		fAreTradesAvail(false) {}
	
	virtual void initialize();

	virtual CStrVar getPageTitle(void) const { return("Trading"); }

	virtual int getBodyViewWidth(void) const { return(600); }
	virtual CStrVar getBodyViewInstructions(void) const
		{ return(fInstructions); }
	virtual int getBodyViewBodyHeight(void) const { return(450); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTradePageH
/******************************************************************************/
/******************************************************************************/
