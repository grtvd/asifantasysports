/* ASFantasyStandingsPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyStandingsPageH
#define ASFantasyStandingsPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyStandingsPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	ASFantasyStandingsPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual CStrVar getPageTitle(void) const { return("Standings"); }

	virtual int getBodyViewWidth(void) const { return(510); }
	virtual int getBodyViewBodyHeight(void) const { return(415); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyStandingsPageH
/******************************************************************************/
/******************************************************************************/
