/* ASFantasyFreeAgentPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyFreeAgentPageH
#define ASFantasyFreeAgentPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyFreeAgentPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	bool fAreClaimsAvail;
	CStrVar fInstructions;

protected:
	ASFantasyFreeAgentPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter),
		fAreClaimsAvail(false) {}
	
	virtual void initialize();

	virtual CStrVar getPageTitle(void) const { return("Free Agents"); }

	virtual int getBodyViewWidth(void) const { return(600); }
	virtual CStrVar getBodyViewInstructions(void) const
		{ return(fInstructions); }
	virtual int getBodyViewBodyHeight(void) const { return(450); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyFreeAgentPageH
/******************************************************************************/
/******************************************************************************/
