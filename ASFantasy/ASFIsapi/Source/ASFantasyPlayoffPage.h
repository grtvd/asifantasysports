/* ASFantasyPlayoffPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyPlayoffPageH
#define ASFantasyPlayoffPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyPlayoffPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	ASFantasyPlayoffPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual CStrVar getPageTitle(void) const { return("Playoffs"); }

	virtual int getBodyViewWidth(void) const { return(600); }
	virtual int getBodyViewBodyHeight(void) const { return(370); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyPlayoffPageH
/******************************************************************************/
/******************************************************************************/
