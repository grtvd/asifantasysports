/* ASFantasySchedulePage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasySchedulePageH
#define ASFantasySchedulePageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasySchedulePageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	ASFantasySchedulePageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual CStrVar getPageTitle(void) const { return("Schedule"); }

	virtual int getBodyViewWidth(void) const { return(344); }
	virtual ASFantasyBodyViewTitleType getBodyViewTitleType()
		{ return(tt_Manager); }
	virtual int getBodyViewBodyHeight(void) const { return(345); }
	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasySchedulePageH
/******************************************************************************/
/******************************************************************************/
