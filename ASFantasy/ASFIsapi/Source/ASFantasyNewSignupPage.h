/* ASFantasyNewSignupPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyNewSignupPageH
#define ASFantasyNewSignupPageH

#include "ASFantasyHTMLPageBuilder.h"
#include "ASFantasyNewSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyNewSignupBasePage : public TTypeGammaPageHtmlView
{
protected:
	TMemberPtr fMemberPtr;
	CStrVar fSignupSource;

protected:
	ASFantasyNewSignupBasePage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void initialize();

	virtual CStrVar getPageTitle(void) const { return("Sign-Up"); }
	virtual int getPageWidth(void) const { return(ASFantasySlimPageWidth()); }
	virtual CStrVar getBackgroundImage() const { return("YellowPaper.gif"); }

	virtual void writeHeaderView();
	virtual bool showHeaderViewNavButtonBar() const { return(false); }

	virtual void writeBodyView();
	bool areSignupsOpen() const;
	virtual void writeBodyFormStart() {}
	virtual void writeBodyFormEnd() {}
	virtual void writeBodyRows();

	virtual void writeBodyLineRow();
	virtual void writeBodyEmptyRow(int height);
	virtual void writeBodySectionTitleFontStart();
	virtual void writeBodySectionTitleFontEnd();
	virtual void writeBodySectionTitleRow(const char* title);
	virtual void writeBodySectionTextFontStart();
	virtual void writeBodySectionTextFontEnd();
	virtual void writeBodySectionTextRow(const char* text);
	virtual void writeBodySectionDataPairRow(const char* descrip,
		THtmlView& htmlView);
	void writeBodySignupClosed();

	virtual bool showFooterViewIconsCompanyOnly() const { return(true); }
};

/******************************************************************************/

class ASFantasyNewSignupBaseGetPage : public ASFantasyNewSignupBasePage
{
protected:
	TBooleanType fPrizeEligible;

protected:
	ASFantasyNewSignupBaseGetPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBasePage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void initialize();

	virtual TGameLevel getGameLevel() const = 0;
	virtual double getGamePrice() const = 0;

	virtual int getPostPage() const = 0;
	virtual bool isSecurePage() const = 0;

	virtual bool canCachePage() const { return(true); }

	virtual void writeBodyFormStart();
	virtual void writeBodyFormEnd();

	void writeBodyAnotherTeamNote();
	void writeBodyAccountInfomation();
	void writeBodyPersonalInfomation();
	void writeBodyTeamInfomation(bool showNote);
	void writeBodyCreditCardInfomation();
	void writeBodySubmitLine();
};

/******************************************************************************/

class ASFantasyNewSignupBasePostPage : public ASFantasyNewSignupBasePage
{
protected:
	auto_ptr<ASFantasyNewSignupResp> fNewSignupResp;
	TBooleanType fPrizeEligible;

protected:
	ASFantasyNewSignupBasePostPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyNewSignupBasePage(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void initialize();

	void readRequestAddressData(ASFantasyNewSignupRqst& request);
	void readRequestTeamData(ASFantasyNewSignupRqst& request);
	void readRequestCreditCardData(ASFantasyNewSignupRqst& request);
	void readRequestData(ASFantasyNewSignupRqst& request,bool isPartic);
	virtual void write();
};

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasyNewSignupPageH
/******************************************************************************/
/******************************************************************************/
