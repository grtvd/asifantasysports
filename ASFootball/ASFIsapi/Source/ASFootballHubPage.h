/* ASFootballHubPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballHubPageH
#define ASFootballHubPageH

#include "ASFantasyHubPage.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballLineupMessageHtmlView : public ASFantasyLineupMessageHtmlView
{
public:
	ASFootballLineupMessageHtmlView(THtmlPageOptions& pageOptions,
		const TScheduleDayVector& scheduleDayVector) : 
		ASFantasyLineupMessageHtmlView(pageOptions,scheduleDayVector) {}
	
	virtual bool show();
};

/******************************************************************************/

class ASFootballHubPageHtmlView : public ASFantasyHubPageHtmlView
{
protected:
	ASFootballHubPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyHubPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}
	
	virtual void buildLineupMessage(
		const TScheduleDayVector& scheduleDayVector);

	friend class ASFootballHtmlServer;
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballHubPageH
/******************************************************************************/
/******************************************************************************/
