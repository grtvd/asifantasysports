/* ASFantasyTeamsPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTeamsPageH
#define ASFantasyTeamsPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyTeamsPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	ASFantasyTeamsPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual CStrVar getPageTitle(void) const { return("Teams"); }

	virtual int getBodyViewWidth(void) const { return(550); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTeamsPageH
/******************************************************************************/
/******************************************************************************/
