/* ASFantasyGameResultsPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyGameResultsPageH
#define ASFantasyGameResultsPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyGameResultsPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	CStrVar fGameDate;

protected:
	ASFantasyGameResultsPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual void initialize();

	virtual CStrVar getPageTitle(void) const { return("Game Results"); }

	virtual int getBodyViewWidth(void) const { return(550); }
	virtual int getBodyViewBodyHeight(void) const { return(325); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyGameResultsPageH
/******************************************************************************/
/******************************************************************************/
