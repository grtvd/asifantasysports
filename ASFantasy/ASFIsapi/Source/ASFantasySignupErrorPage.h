/* ASFantasySignupErrorPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasySignupErrorPageH
#define ASFantasySignupErrorPageH

#include "ASFantasyNewSignupPage.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasySignupErrorGetPage : public ASFantasyNewSignupBasePage
{
protected:
	CStrVar fErrorMsg;

protected:
	ASFantasySignupErrorGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,
		const char* errorMsg) : ASFantasyNewSignupBasePage(isHtmlServer,
		pageOptions,htmlWriter),fErrorMsg(errorMsg) {}

public:
	static ASFantasyBasePageHtmlViewPtr newInstance(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,
		const char* errorMsg)
		{ return(ASFantasyBasePageHtmlViewPtr(new ASFantasySignupErrorGetPage(
			isHtmlServer,pageOptions,htmlWriter,errorMsg))); }

protected:
	virtual void writeBodyRows();
};

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasySignupErrorPageH
/******************************************************************************/
/******************************************************************************/
