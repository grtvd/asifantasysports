/* ParticPremiumTrialPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ParticPremiumTrialPageH
#define ParticPremiumTrialPageH

#include "ASMemberDB.h"
#include "NewSignupPage.h"

namespace asmember
{

/******************************************************************************/

class ParticPremiumTrialGetPage : public NewSignupBaseGetPage
{
public:
	ParticPremiumTrialGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		NewSignupBaseGetPage(isHtmlServer,pageOptions,htmlWriter) {}

protected:
	virtual CStrVar getPageTitle(void) const { return("Trial"); }

	virtual TGameLevel getGameLevel() const { return(gml_Premium); }
	virtual double getGamePrice() const { return(0.0); }

	virtual int getPostPage() const { return(htmlParticPremiumTrialPostPage); }
	virtual bool isSecurePage() const { return(true); }

	virtual void writeBodyRows();
};

/******************************************************************************/

class ParticPremiumTrialPostPage : public NewSignupBasePage	/*BOB NewSignupBasePostPage*/
{
public:
	ParticPremiumTrialPostPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		NewSignupBasePage(isHtmlServer,pageOptions,htmlWriter) {}

protected:
	virtual CStrVar getPageTitle(void) const { return("Trial"); }

	virtual void initialize();
	virtual void writeBodyRows();
};

/******************************************************************************/

}; //namespace asmember

#endif	//ParticPremiumTrialPageH
/******************************************************************************/
/******************************************************************************/
