/* ParticUpgradePage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ParticUpgradePageH
#define ParticUpgradePageH

#include "ASMemberDB.h"
#include "NewSignupPage.h"
#include "ParticUpgradeRqst.h"

namespace asmember
{

/******************************************************************************/

class ParticUpgradeGetPage : public NewSignupBaseGetPage
{
public:
	ParticUpgradeGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		NewSignupBaseGetPage(isHtmlServer,pageOptions,htmlWriter) {}

protected:
	virtual CStrVar getPageTitle(void) const { return("Upgrade"); }

	virtual TGameLevel getGameLevel() const { return(gml_Premium); }
	virtual double getGamePrice() const
		{ return(UpgradePrice(fPageOptions.getRqstPartic())); }

	virtual int getPostPage() const { return(htmlParticUpgradePostPage); }
	virtual bool isSecurePage() const { return(true); }

	virtual void writeBodyRows();
};

/******************************************************************************/

class ParticUpgradePostPage : public NewSignupBasePostPage
{
public:
	ParticUpgradePostPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		NewSignupBasePostPage(isHtmlServer,pageOptions,htmlWriter) {}

protected:
	virtual CStrVar getPageTitle(void) const { return("Upgrade"); }

	virtual void initialize();
	virtual void writeBodyRows();
};

/******************************************************************************/

}; //namespace asmember

#endif	//ParticUpgradePageH
/******************************************************************************/
/******************************************************************************/
