/* ASFantasyNewMemberSignupPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef NewMemberSignupPageProcH
#define NewMemberSignupPageProcH

#include "ASMemberDB.h"
#include "ASFantasyNewSignupPage.h"
#include "ASFantasyNewMemberSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyNewMemberSignupPremiumGetPage : public ASFantasyNewSignupBaseGetPage
{
protected:
	ASFantasyNewMemberSignupPremiumGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBaseGetPage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual TGameLevel getGameLevel() const { return(gml_Premium); }
	virtual double getGamePrice() const { return(GamePrice(TMemberID(),true)); }

	virtual int getPostPage() const { return(htmlNewMemberSignupPostPage); }
	virtual bool isSecurePage() const { return(false); }

	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

class ASFantasyNewMemberSignupStandardGetPage : public ASFantasyNewSignupBaseGetPage
{
protected:
	ASFantasyNewMemberSignupStandardGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBaseGetPage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual TGameLevel getGameLevel() const { return(gml_Standard); }
	virtual double getGamePrice() const { return(GamePrice(TMemberID(),false)); }

	virtual int getPostPage() const { return(htmlNewMemberSignupPostPage); }
	virtual bool isSecurePage() const { return(false); }

	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

class ASFantasyNewMemberSignupPostPage : public ASFantasyNewSignupBasePostPage
{
protected:
	ASFantasyNewMemberSignupPostPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBasePostPage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void initialize();
	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasyNewMemberSignupPageH
/******************************************************************************/
/******************************************************************************/
