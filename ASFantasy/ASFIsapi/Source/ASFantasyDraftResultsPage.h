/* ASFantasyDraftResultsPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyDraftResultsPageH
#define ASFantasyDraftResultsPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyDraftResultsPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	bool fAreResultsAvail;
	CStrVar fInstructions;

protected:
	ASFantasyDraftResultsPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter),
		fAreResultsAvail(false) {}
	
	virtual void initialize();

	virtual CStrVar getPageTitle(void) const { return("Draft Results"); }

	virtual int getBodyViewWidth(void) const { return(450); }
	virtual CStrVar getBodyViewInstructions(void) const
		{ return(fInstructions); }
	virtual int getBodyViewBodyHeight(void) const { return(390); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyDraftResultsPageH
/******************************************************************************/
/******************************************************************************/
