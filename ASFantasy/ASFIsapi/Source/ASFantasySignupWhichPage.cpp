/* ASFantasySignupWhichPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasySignupWhichPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasySignupWhichGetPage::initialize()
{
	ASFantasyNewSignupBasePage::initialize();

	fPrizeEligible = fIsHtmlServer.getBooleanField("PrizeEligible");
}

/******************************************************************************/

void ASFantasySignupWhichGetPage::writeBodyRows()
{
	CStrVar str;
	CStrVar linkParams;
	char tempStr[DOLLAR_LEN];

	linkParams.copyVarg("Source=%s&PrizeEligible=%s",fSignupSource.c_str(),
		fPrizeEligible.c_str());

	writeBodyLineRow();

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	writeBodySectionTitleFontStart();

	fHtmlWriter.TextString("Current Members, ");
	writeTextLink(htmlNewParticSignupPremiumGetPage,"",linkParams);
	DollarToString(GamePriceParticPremium(),tempStr,2);
	str.copyVarg(" a new team for %s.",tempStr);
	fHtmlWriter.TextString(str);

	writeBodySectionTitleFontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodyEmptyRow(30);

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	writeBodySectionTitleFontStart();

	fHtmlWriter.TextString("New Members, ");
	writeTextLink(htmlNewMemberSignupPremiumGetPage,"",linkParams);
	DollarToString(GamePriceMemberPremium(),tempStr,2);
	str.copyVarg(" a new team for %s.",tempStr);
	fHtmlWriter.TextString(str);

	writeBodySectionTitleFontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodyEmptyRow(50);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
