/* ASFantasyNewParticSignupPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyNewParticSignupPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewParticSignupPremiumGetPage::writeBodyRows()
{
	writeBodyLineRow();
	writeBodyAnotherTeamNote();

	writeBodyLineRow();
	writeBodyPersonalInfomation();

	writeBodyLineRow();
	writeBodyTeamInfomation(false);

	if(getGamePrice() > 0.0)
	{
		writeBodyLineRow();
		writeBodyCreditCardInfomation();
	}

	writeBodyLineRow();
	writeBodySubmitLine();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewParticSignupStandardGetPage::writeBodyRows()
{
	writeBodyLineRow();
	writeBodyAnotherTeamNote();

	writeBodyLineRow();
	writeBodyPersonalInfomation();

	writeBodyLineRow();
	writeBodyTeamInfomation(false);

	if(getGamePrice() > 0.0)
	{
		writeBodyLineRow();
		writeBodyCreditCardInfomation();
	}

	writeBodyLineRow();
	writeBodySubmitLine();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewParticSignupPostPage::initialize()
{
	TDateTime today = TDateTime::CurrentDate();
	ASFantasyNewParticSignupRqst request;

	if((today < SignupStartDate()) || (today > SignupEndDate()))
		throw ASIException("ASFantasyNewParticSignupPostPage::initialize: sign-ups are closed");

	ASFantasyNewSignupBasePostPage::initialize();
	
	request.setMemberID(fPageOptions.getRqstMemberID());
	readRequestData(request,true);

	fNewSignupResp.reset(request.fulfillRequest());
}

/******************************************************************************/

void ASFantasyNewParticSignupPostPage::writeBodyRows()
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
	
	fHtmlWriter.TextString(" have been successfully signed up.");

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

	fHtmlWriter.TextString("Proceed to the ");
	fHtmlWriter.Link(pageLinkInfo.GetAbsoluteLinkURLToEncodedParticID(0,
		fPageOptions,fNewSignupResp->getEncodedParticID()).c_str(), "",
		pageLinkInfo.GetLinkDesc().c_str());
	fHtmlWriter.TextString(" to start playing.  Good Luck!");

	fHtmlWriter.TextEffectEnd(efStrong);
	fHtmlWriter.FontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodyEmptyRow(50);
}

/******************************************************************************/

}; //asfantasy

/******************************************************************************/
/******************************************************************************/
