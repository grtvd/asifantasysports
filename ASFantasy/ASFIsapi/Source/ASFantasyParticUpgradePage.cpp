/* ParticUpgradePage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"

#include "ASFantasyAppOptions.h"	//BOB refering to ASFantasy
#include "ParticUpgradePage.h"

/******************************************************************************/
/******************************************************************************/

void ParticUpgradeGetPage::writeBodyRows()
{
	CStrVar tempStr;

	if(!UpgradeAvailable())
		throw ASIException("ParticUpgradeGetPage::writeBodyRows: upgrades are not available");

	fHtmlWriter.HiddenField(gURLUserFieldStr,
		fPageOptions.getPagePartic()->encodeParticID().c_str());

	writeBodyLineRow();
	tempStr.copyVarg("You have selected to upgrade your team to the "
		"premium version. Please verify and update any information below.",
		fMemberPtr->getMemberID().c_str());
	writeBodySectionTextRow(tempStr);

	writeBodyLineRow();
	writeBodyPersonalInfomation();

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

void ParticUpgradePostPage::initialize()
{
	ParticUpgradeRqst request;
	double gamePrice;

	if(!UpgradeAvailable())
		throw ASIException("ParticUpgradePostPage::initialize: upgrades are not available");

	NewSignupBasePostPage::initialize();

	gamePrice = UpgradePrice(fPageOptions.getRqstPartic());

	if(!EQUAL_DOLLARS(gamePrice,fIsHtmlServer.getFloatField("GamePrice")))
		throw ASIException("ParticUpgradePostPage::process: game price mismatch (%0.4lf != %0.4lf",
			gamePrice,fIsHtmlServer.getFloatField("GamePrice"));
	
	request.setGamePrice(gamePrice);

	request.setMemberID(fPageOptions.getRqstMemberID());
	request.setParticID(fPageOptions.getRqstPartic()->getParticID());

	readRequestAddressData(request);
	readRequestCreditCardData(request);

	fNewSignupResp.reset(request.fulfillRequest());
}

/******************************************************************************/

void ParticUpgradePostPage::writeBodyRows()
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlHubPage));
	CStrVar tempStr;

	writeBodyLineRow();

//	tempStr.copyVarg("Congratulations!  %s",fNewSignupResp->getManagerName());
//	writeBodySectionTitleRow(tempStr);

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efStrong);

	fHtmlWriter.TextString("Your upgrade request has been received.  The ");

	tempStr.copyVarg("%s %s",fNewSignupResp->getRegionName(),
		fNewSignupResp->getTeamName());
	fHtmlWriter.Font(tempStr,4,fcAbsolute,ASFantasyStandardFont());
	
	fHtmlWriter.TextString(" will be updated to the premium version as soon "
		"as your payment is processed.");

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

	fHtmlWriter.TextString("Return to the ");
	fHtmlWriter.Link(pageLinkInfo.GetAbsoluteLinkURLToEncodedParticID(0,
		fPageOptions,fNewSignupResp->getEncodedParticID()).c_str(), "",
		pageLinkInfo.GetLinkDesc().c_str());
	fHtmlWriter.TextString(".");

	fHtmlWriter.TextEffectEnd(efStrong);
	fHtmlWriter.FontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/
/******************************************************************************/
