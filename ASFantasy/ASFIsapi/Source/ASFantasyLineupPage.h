/* ASFantasyLineupPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyLineupPageH
#define ASFantasyLineupPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyLineupPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	ASFantasyLineupPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual CStrVar getPageTitle(void) const { return("Lineups"); }

	virtual int getBodyViewWidth(void) const { return(600); }
	virtual CStrVar getBodyViewInstructions(void) const
		{ return("Set your lineup."); }
	virtual int getBodyViewBodyHeight(void) const { return(410); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyLineupPageH
/******************************************************************************/
/******************************************************************************/
