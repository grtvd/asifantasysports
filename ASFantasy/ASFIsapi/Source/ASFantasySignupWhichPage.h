/* ASFantasySignupWhichPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasySignupWhichPageH
#define ASFantasySignupWhichPageH

#include "ASFantasyNewSignupPage.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasySignupWhichGetPage : public ASFantasyNewSignupBasePage
{
protected:
	TBooleanType fPrizeEligible;

protected:
	ASFantasySignupWhichGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBasePage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void initialize();

	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasySignupWhichPageH
/******************************************************************************/
/******************************************************************************/
