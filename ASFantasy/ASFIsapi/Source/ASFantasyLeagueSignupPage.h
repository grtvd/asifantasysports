/* ASFantasyLeagueSignupPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyLeagueSignupPageH
#define ASFantasyLeagueSignupPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyLeagueSignupPageHtmlView : public TTypeGammaPageHtmlView
{
public:
	ASFantasyLeagueSignupPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
		
	virtual CStrVar getPageTitle(void) const { return("League Sign-Up"); }

	virtual int getBodyViewWidth(void) const { return(450); }
	virtual ASFantasyBodyViewTitleType getBodyViewTitleType()
		{ return(tt_None); }
	virtual CStrVar getBodyViewInstructions(void) const
		{ return("Follow the instructions below:"); }
	virtual int getBodyViewBodyHeight(void) const { return(305); }
	virtual void writeBodyViewBody();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyLeagueSignupPageH
/******************************************************************************/
/******************************************************************************/
