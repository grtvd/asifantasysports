/* ASFantasyNewMemberSignupPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyNewMemberSignupPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewMemberSignupPremiumGetPage::writeBodyRows()
{
	writeBodyLineRow();
	writeBodyAccountInfomation();

	writeBodyLineRow();
	writeBodyPersonalInfomation();

	writeBodyLineRow();
	writeBodyTeamInfomation(true);

	writeBodyLineRow();
	writeBodyCreditCardInfomation();

	writeBodyLineRow();
	writeBodySubmitLine();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewMemberSignupStandardGetPage::writeBodyRows()
{
	writeBodyLineRow();
	writeBodyAccountInfomation();

	writeBodyLineRow();
	writeBodyPersonalInfomation();

	writeBodyLineRow();
	writeBodyTeamInfomation(true);

	writeBodyLineRow();
	writeBodySubmitLine();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewMemberSignupPostPage::initialize()
{
	TDateTime today = TDateTime::CurrentDate();
	ASFantasyNewMemberSignupRqst request;

	if((today < SignupStartDate()) || (today > SignupEndDate()))
		throw ASIException("ASFantasyNewMemberSignupPostPage::initialize: sign-ups are closed");

	ASFantasyNewSignupBasePostPage::initialize();

	request.setSignupSource(fSignupSource);

	request.setMemberID(fIsHtmlServer.getStringField("UserNameTxt",cam_MayNotExist).c_str());
	request.setPassword(fIsHtmlServer.getStringField("UserPasswordTxt",cam_MayNotExist).c_str());
	request.setReEnteredPassword(fIsHtmlServer.getStringField("UserRePasswordTxt",cam_MayNotExist).c_str());

	readRequestData(request,false);

	fNewSignupResp.reset(request.fulfillRequest());
}

/******************************************************************************/

void ASFantasyNewMemberSignupPostPage::writeBodyRows()
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlHubPage));
	CStrVar tempStr;

	writeBodyLineRow();

	tempStr.copyVarg("Congratulations!  %s",fNewSignupResp->getManagerName());
	writeBodySectionTitleRow(tempStr);

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efStrong);

	fHtmlWriter.TextString("The ");

	tempStr.copyVarg("%s %s",fNewSignupResp->getRegionName(),
		fNewSignupResp->getTeamName());
	fHtmlWriter.Font(tempStr,4,fcAbsolute,ASFantasyStandardFont());
	
	tempStr.copyVarg(" have been successfully signed up with a User Name of \"%s\".",
		fNewSignupResp->getMemberID().c_str());
	fHtmlWriter.TextString(tempStr);

	fHtmlWriter.TextEffectEnd(efStrong);
	fHtmlWriter.FontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	writeBodyEmptyRow(20);

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efStrong);

	fHtmlWriter.Link(pageLinkInfo.GetAbsoluteLinkURLToEncodedParticID(0,
		fPageOptions,fNewSignupResp->getEncodedParticID()).c_str(), "",
		"Logon");
	tempStr.copyVarg(" as \"%s\" to start playing.  Good Luck!",
		fNewSignupResp->getMemberID().c_str());
	fHtmlWriter.TextString(tempStr);

	fHtmlWriter.TextEffectEnd(efStrong);
	fHtmlWriter.FontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	if(fPageOptions.isRqstMemberSet() &&
		(fPageOptions.getRqstMemberID() == DemoMemberID()))
	{
		writeBodyEmptyRow(20);

		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
		fHtmlWriter.FontStart(2,fcAbsolute,ASFantasyStandardFont());
		fHtmlWriter.TextEffectStart(efStrong);

		tempStr.copyVarg("Warning:  If you have logged into the demo using the "
			"\"%s\" User Name, you will need to restart your browser to "
			"login as \"%s\".",DemoMemberID().c_str(),
			fNewSignupResp->getMemberID().c_str());
		fHtmlWriter.TextString(tempStr);

		fHtmlWriter.TextEffectEnd(efStrong);
		fHtmlWriter.FontEnd();
		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();
	}

	writeBodyEmptyRow(50);
}

/******************************************************************************/

}; //asfantasy

/******************************************************************************/
/******************************************************************************/
