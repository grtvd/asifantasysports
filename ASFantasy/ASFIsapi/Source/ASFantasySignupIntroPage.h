/* ASFantasySignupIntroPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasySignupIntroPageH
#define ASFantasySignupIntroPageH

#include "ASFantasyNewSignupPage.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasySignupIntroGetPage : public ASFantasyNewSignupBasePage
{
protected:
	ASFantasySignupIntroGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBasePage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void writeBodyRows();
	void writeBodyAgreementRow();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasySignupIntroPageH
/******************************************************************************/
/******************************************************************************/
