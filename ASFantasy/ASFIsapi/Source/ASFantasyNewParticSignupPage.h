/* ASFantasyNewParticSignupPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyNewParticSignupPageH
#define ASFantasyNewParticSignupPageH

#include "ASMemberDB.h"
#include "ASFantasyNewSignupPage.h"
#include "ASFantasyNewParticSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyNewParticSignupPremiumGetPage : public ASFantasyNewSignupBaseGetPage
{
protected:
	ASFantasyNewParticSignupPremiumGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBaseGetPage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual TGameLevel getGameLevel() const { return(gml_Premium); }
	virtual double getGamePrice() const
		{ return(GamePrice(fPageOptions.getRqstMemberID(),true)); }

	virtual int getPostPage() const { return(htmlNewParticSignupPostPage); }
	virtual bool isSecurePage() const { return(true); }

	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

class ASFantasyNewParticSignupStandardGetPage : public ASFantasyNewSignupBaseGetPage
{
protected:
	ASFantasyNewParticSignupStandardGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBaseGetPage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual TGameLevel getGameLevel() const { return(gml_Standard); }
	virtual double getGamePrice() const
		{ return(GamePrice(fPageOptions.getRqstMemberID(),false)); }

	virtual int getPostPage() const { return(htmlNewParticSignupPostPage); }
	virtual bool isSecurePage() const { return(true); }

	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

class ASFantasyNewParticSignupPostPage : public ASFantasyNewSignupBasePostPage
{
protected:
	ASFantasyNewParticSignupPostPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBasePostPage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void initialize();
	virtual void writeBodyRows();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasyNewParticSignupPageH
/******************************************************************************/
/******************************************************************************/
