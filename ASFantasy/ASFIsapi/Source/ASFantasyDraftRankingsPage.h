/* ASFantasyDraftRankingsPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftRankingsPageH
#define ASFantasyDraftRankingsPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyDraftRankingsPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	ASFantasyDraftRankingsPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual CStrVar getPageTitle(void) const { return("Draft Rankings"); }

	virtual int getBodyViewWidth(void) const { return(685); }
	virtual ASFantasyBodyViewTitleType getBodyViewTitleType()
		{ return(tt_Manager); }
	virtual CStrVar getBodyViewInstructions(void) const
		{ return("Set your draft rankings."); }
	virtual int getBodyViewBodyHeight(void) const { return(390); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftRankingsPageH
/******************************************************************************/
/******************************************************************************/
