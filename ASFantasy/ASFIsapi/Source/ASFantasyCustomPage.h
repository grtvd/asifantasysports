/* ASFantasyCustomPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyCustomPageH
#define ASFantasyCustomPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyCustomPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	CStrVar fPageTitle;
	int fBodyViewWidth;
	CStrVar fFileName;

protected:
	ASFantasyCustomPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter),
		fBodyViewWidth(550) {}

	virtual void initialize();

	virtual CStrVar getPageTitle(void) const { return(fPageTitle); }

	virtual int getBodyViewWidth(void) const { return(fBodyViewWidth); }
	virtual ASFantasyBodyViewTitleType getBodyViewTitleType()
		{ return(tt_None); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyCustomPageH
/******************************************************************************/
/******************************************************************************/
