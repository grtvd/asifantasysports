/* ASFantasySignupIntroPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasySignupIntroPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasySignupIntroGetPage::writeBodyRows()
{
	writeBodyLineRow();
	writeBodyAgreementRow();
}

/******************************************************************************/

void ASFantasySignupIntroGetPage::writeBodyAgreementRow()
{
	CStrVar str;
	CStrVar linkParams;

	str.copyVarg("Welcome to the\r\n%s Sign Up!",
		fPageOptions.getAppNameFull().c_str());
	writeBodySectionTitleRow(str);

	writeBodySectionTextRow("Before signing up, you must agree to all of "
		"the following:");
	writeBodyEmptyRow(10);

	writeBodySectionTextRow("1. I have valid email address. A sign up "
		"confirmation email letter will be sent to the email address you "
		"specify. Please be sure it is correct.");
	writeBodyEmptyRow(10);

	writeBodySectionTextRow("2. I have a valid Master Card or VISA "
		"credit card.");
	writeBodyEmptyRow(10);

	writeBodySectionTextRow("3. I have read and understood the full "
		"official rules governing this Contest and I agree to be bound by "
		"those rules.");
	writeBodyEmptyRow(10);

	writeBodySectionTextRow("To be eligible for the Contest Prizes, you must "
		"be 18 years old or older, a U.S. Citizen, and eligible for Contest "
		"Prizes in your area of residence.  If you do not meet these "
		"requirements, you can still sign up by forfeiting your Prize "
		"eligibility.");
	writeBodyEmptyRow(10);


	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	writeBodySectionTextFontStart();
	fHtmlWriter.TextParagraph("If you agree to the items above and are "
		"eligible to receive Prizes,\r\nplease ");

	linkParams.copyVarg("Source=%s&PrizeEligible=%s",fSignupSource.c_str(),
		TBooleanType(true).c_str());
	writeIconLink(htmlSignupWhichGetPage,"ClickHereButton.gif","click here",
		linkParams);
	fHtmlWriter.TextString(".");
	writeBodySectionTextFontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodyEmptyRow(10);
	writeBodyLineRow();
	writeBodyEmptyRow(10);
							  
	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	writeBodySectionTextFontStart();
	fHtmlWriter.TextParagraph("If you agree to the items above and would "
		"still like to sign up but are NOT eligible to receive "
		"Prizes,\r\nplease ");

	linkParams.copyVarg("Source=%s&PrizeEligible=%s",fSignupSource.c_str(),
		TBooleanType(false).c_str());
	writeIconLink(htmlSignupWhichGetPage,"ClickHereButton.gif","click here",
		linkParams);
	fHtmlWriter.TextString(".");
	writeBodySectionTextFontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodyEmptyRow(50);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
