/* ASFantasyNewSignupPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"

#include "ASMemberDB.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyNewSignupPage.h"
#include "ASFantasySignupErrorPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewSignupBasePage::initialize()
{
	if(fPageOptions.isRqstMemberSet())
		fMemberPtr = TMember::createGet(fPageOptions.getRqstMemberID(),cam_MustExist);
	else
		fMemberPtr = TMember::newInstance();

	fSignupSource = fIsHtmlServer.getStringField("Source");
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeHeaderView()
{
	CStrVar str;

	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(getPageWidth()));
	fHtmlWriter.TableRowStart();

	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(171),THtmlHeight(114),ahLeft,avTop);
	writeHeaderViewLogo();
	fHtmlWriter.TableCellEnd();
	
	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(getPageWidth() - 171),
		THtmlHeight(),ahCenter,avMiddle);
	TTypeBetaPageTitleHtmlView::build(fHtmlWriter,getPageTitle());
	fHtmlWriter.TableCellEnd();
	
	fHtmlWriter.TableRowEnd();
	fHtmlWriter.TableEnd(); 
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodyView()
{
	writeBodyFormStart();

	fHtmlWriter.TableStart(0,THtmlWidthValue(getPageWidth()));
	fHtmlWriter.TableRowStart();

	TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,
		THtmlWidthValue(120));

	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(getPageWidth() - 120));

	fHtmlWriter.TableStart(0);
	if(areSignupsOpen())
		writeBodyRows();
	else
		ASFantasyNewSignupBasePage::writeBodyRows();
	fHtmlWriter.TableEnd();

	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableRowEnd();
	fHtmlWriter.TableEnd();

	writeBodyFormEnd();
}

/******************************************************************************/

bool ASFantasyNewSignupBasePage::areSignupsOpen() const
{
	TDateTime today = TDateTime::CurrentDate();

	if((today >= SignupStartDate()) && (today <= SignupEndDate()))
		return(true);

	return(false);
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodyRows()
{
	CStrVar signupClosedFile;

	if(areSignupsOpen())
		throw ASIException("ASFantasyNewSignupBasePage::writeBodyRows: must be overriddern during sign-up period");

	writeBodyLineRow();
	writeBodySignupClosed();

	signupClosedFile = BuildFullFileName(ASMemberHomeDir(),"SignupClosed.html");
	if(FileExists(signupClosedFile.c_str()))
	{
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);

		fHtmlWriter.InsertFile(signupClosedFile);

		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();

		writeBodyEmptyRow(50);
	}
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodyLineRow()
{
	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeightValue(35),
		ahCenter,avMiddle);
	fHtmlWriter.Image(fPageOptions.buildImagePath("line.gif").c_str(),
		"","",aiDefault,THtmlWidthValue(getPageWidth() - 120),THtmlHeightValue(13));
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodyEmptyRow(int height)
{
	fHtmlWriter.TableRowStart();
	TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,
		THtmlWidth(),THtmlHeightValue(height));
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionTitleFontStart()
{
	fHtmlWriter.FontStart(4,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efBold);
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionTitleFontEnd()
{
	fHtmlWriter.TextEffectEnd(efBold);
	fHtmlWriter.FontEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionTitleRow(const char* title)
{
	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),
		ahCenter,avMiddle);
	#if 1	//BOB
	writeBodySectionTitleFontStart();
	fHtmlWriter.TextParagraph(title);
	writeBodySectionTitleFontEnd();
	#else
	TTypeBetaSectionTitleHtmlView::build(fHtmlWriter,title);
	#endif
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodyEmptyRow(10);
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionTextFontStart()
{
	fHtmlWriter.FontStart(2,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efBold);
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionTextFontEnd()
{
	fHtmlWriter.TextEffectEnd(efBold);
	fHtmlWriter.FontEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionTextRow(const char* text)
{
	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	#if 1	//BOB
	writeBodySectionTextFontStart();
	fHtmlWriter.TextParagraph(text);
	writeBodySectionTextFontEnd();
	#else
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,text));
	#endif
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySectionDataPairRow(const char* descrip,
	THtmlView& htmlView)
{
	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,descrip));
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(htmlView);
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBasePage::writeBodySignupClosed()
{
	TDateTime today = TDateTime::CurrentDate();
	CStrVar str;

	if(today < SignupStartDate())
		str.copyVarg("Sign-ups will open on %s.",FormatDateOnlyStr(
			SignupStartDate(),ASFantasyStandardDateFormat()).c_str());
	else if(today > SignupEndDate())
		str.copy("Sign-ups are closed for the season.");
	else
		throw ASIException("ASFantasyNewSignupBasePage::writeBodySignupClosed: invalid dates");

	writeBodySectionTextRow(str);
	writeBodyEmptyRow(50);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::initialize()
{
	ASFantasyNewSignupBasePage::initialize();

	fPrizeEligible = fIsHtmlServer.getBooleanField("PrizeEligible");
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyFormStart()
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(getPostPage()));
	char tempStr[FLOAT_LEN];

	fHtmlWriter.FormStart(isSecurePage() ? fPageOptions.getIsapiDll().c_str() :
		fPageOptions.getIsapiDllNS().c_str(),fmPost);
	fHtmlWriter.HiddenField(gURLPageFieldStr,pageLinkInfo.GetName().c_str());

	fHtmlWriter.HiddenField("Source",fSignupSource);
	fHtmlWriter.HiddenField("PrizeEligible",fPrizeEligible.c_str());

	fHtmlWriter.HiddenField("GameLevel",getGameLevel().c_str());

	FloatToString(getGamePrice(),tempStr,FTF_STANDARD,2,0,0);
	fHtmlWriter.HiddenField("GamePrice",tempStr);
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyFormEnd()
{
	fHtmlWriter.FormEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyAnotherTeamNote()
{
	CStrVar tempStr;

	tempStr.copyVarg("You have selected to add a new team to your %s "
		"member account. Please verify and update any information below.",
		fMemberPtr->getMemberID().c_str());
	writeBodySectionTextRow(tempStr);
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyAccountInfomation()
{
	CStrVar str;

	writeBodySectionTitleRow("Account Information");

	writeBodySectionTextRow("Please provide a user name and password so that "
		"we can protect your privacy and keep your information confidential.");

	writeBodyEmptyRow(10);

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.TableStart(0);

	writeBodySectionDataPairRow("User Name:",
		TTextFieldStringHtmlView(fPageOptions,"",false,"UserNameTxt",15,15));
	str.copyVarg("(%d character minimum, no spaces)",(int)MinMemberIDLen);
	writeBodySectionDataPairRow("",TTypeBetaTinyTextHtmlView(fPageOptions,str));

	writeBodySectionDataPairRow("Password:",
		TTextFieldPasswordHtmlView(fPageOptions,"",false,"UserPasswordTxt",10,10));
	str.copyVarg("(%d character minimum, no spaces)",(int)MinMemberPasswordLen);
	writeBodySectionDataPairRow("",TTypeBetaTinyTextHtmlView(fPageOptions,str));
	writeBodySectionDataPairRow("Re-Enter Password:",
		TTextFieldPasswordHtmlView(fPageOptions,"",false,"UserRePasswordTxt",10,10));

	fHtmlWriter.TableEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyPersonalInfomation()
{
	writeBodySectionTitleRow("Personal Information");

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.TableStart(0);

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,"First Name:"));
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTextFieldStringHtmlView(fPageOptions,
		fMemberPtr->getName().fFirstName,false,"FirstNameTxt",10,15));
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions," Last Name:"));
	fHtmlWriter.WriteView(TTextFieldStringHtmlView(fPageOptions,
		fMemberPtr->getName().fLastName,false,"LastNameTxt",15,25));
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	writeBodySectionDataPairRow("Street Address:",
		TTextFieldStringHtmlView(fPageOptions,fMemberPtr->getAddrStreet1(),
		false,"Street1Txt",35,35));
	writeBodySectionDataPairRow("",
		TTextFieldStringHtmlView(fPageOptions,fMemberPtr->getAddrStreet2(),
		false,"Street2Txt",35,35));
	writeBodySectionDataPairRow("City:",
		TTextFieldStringHtmlView(fPageOptions,fMemberPtr->getAddrCity(),
		false,"CityTxt",25,25));

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,"State/Region:"));
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTextFieldStringHtmlView(fPageOptions,
		fMemberPtr->getAddrState(),false,"StateTxt",20,25));
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions," Postal Code:"));
	fHtmlWriter.WriteView(TTextFieldStringHtmlView(fPageOptions,
		fMemberPtr->getAddrZip(),false,"ZipCodeTxt",5,10));
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	writeBodySectionDataPairRow("Country:",
		TTextFieldStringHtmlView(fPageOptions,fMemberPtr->getAddrCountry(),
		false,"CountryTxt",25,35));

	writeBodySectionDataPairRow("Email Address:",
		TTextFieldStringHtmlView(fPageOptions,fMemberPtr->getEmail(),false,
		"EmailTxt",30,50));

	fHtmlWriter.TableEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyTeamInfomation(bool showNote)
{
	writeBodySectionTitleRow("Your Team's Information");

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.TableStart(0);

	/**************************************************************************/

	writeBodySectionDataPairRow("Owner Name:",
		TTextFieldStringHtmlView(fPageOptions,"",false,"ManagerNameTxt",15,15));

	writeBodySectionDataPairRow("Team City:",
		TTextFieldStringHtmlView(fPageOptions,"",false,"RegionNameTxt",15,15));

	writeBodySectionDataPairRow("Team Nickname:",
		TTextFieldStringHtmlView(fPageOptions,"",false,"TeamNameTxt",15,15));

	/**************************************************************************/

	fHtmlWriter.TableEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	if(showNote)
	{
		writeBodyEmptyRow(10);

		writeBodySectionTextRow("Note: If you are planning to manage more than "
			"one team, the information above pertains to your first team only, "
			"the remainder of your teams will be established once you have signed "
			"up initially.");
	}
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodyCreditCardInfomation()
{
	CStrVar tempStr;
	CStrVar tempStr2;
	int i;
	char monthStr[32];
	int year = DateYear(GetSystemDate());

	writeBodySectionTitleRow("Credit Card Billing Information");

	tempStr.copyVarg("Your information will be sent to us using a secure-link "
		"(SSL protocol). If you are uncomfortable with sending your credit card "
		"information via the internet, we will be glad to take it over the "
		"phone. Give us a call at %s. (Be sure to check the box below in "
		"order to continue the signing process.)",
		TechSupportPhoneNumber().c_str());
	writeBodySectionTextRow(tempStr);

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.TableStart(0);
	fHtmlWriter.TableRowStart();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,
		"DO NOT EMAIL US YOUR CREDIT CARD INFORMATION!!!",clRed));
	fHtmlWriter.TableCellEnd();

//	TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,THtmlWidthValue(10));
	fHtmlWriter.TableCellString("");

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,
		"EMAIL IS NOT A SECURE METHOD OF TRANSFER.",clRed));
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
	fHtmlWriter.Image(fPageOptions.buildImagePath("seal.gif").c_str());
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableRowEnd();
	fHtmlWriter.TableEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.TableStart(0);

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,"Card Type:"));
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.SelectStart("CCardTypeSel",1,false);
	fHtmlWriter.SelectOption("Visa","VS",true /*fMemberPtr->getCCardType() == cct_Visa*/);
	fHtmlWriter.SelectOption("Mastercard","MC",false /*fMemberPtr->getCCardType() == cct_Mastercard*/);
	fHtmlWriter.SelectEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodySectionDataPairRow("Card Number:",
		TTextFieldStringHtmlView(fPageOptions,"" /*fMemberPtr->getCCardNumber()*/,
		false,"CCardNumberTxt",19,19));

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,"Exp. Date:"));
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avMiddle);
	fHtmlWriter.SelectStart("CCardExpDateMonSel",1,false);
	for(i = 0; i <= 12; i++)
	{
		if(i == 0)
			fHtmlWriter.SelectOption("","",true);
		else
		{
			tempStr.copyVarg("(%02d) %s",i,MonthToString((short)i,monthStr,
				sizeof(monthStr),MF_MON));
			tempStr2.copyVarg("%d",i);
			fHtmlWriter.SelectOption(tempStr,tempStr2,false);
		}
	}
	fHtmlWriter.SelectEnd();
	fHtmlWriter.SelectStart("CCardExpDateYearSel",1,false);
	for(i = 0; i <= 10; i++)
	{
		if(i == 0)
			fHtmlWriter.SelectOption("","",true);
		else
		{
			tempStr.copyVarg("%d",year + i - 1);
			fHtmlWriter.SelectOption(tempStr,tempStr,false);
		}
	}
	fHtmlWriter.SelectEnd();
	/*BOB fHtmlWriter.WriteView(TTextFieldStringHtmlView(fPageOptions,"",false,
		"CCardExpDateTxt",6,6));	// Don't default - always require user entry
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions," (MM/YY)")); */
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	writeBodySectionDataPairRow("Name on the card:",
		TTextFieldStringHtmlView(fPageOptions,"" /*fMemberPtr->getCCardNameOn()*/,
		false,"CCardNameOnTxt",30,40));

	fHtmlWriter.TableEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);

	fHtmlWriter.CheckboxField(false,false,"CCardViaFaxPhoneChk");
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,"I will "
		"contact you with my credit card information instead of filling out "
		"the above fields."));

	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/

void ASFantasyNewSignupBaseGetPage::writeBodySubmitLine()
{
	double gamePrice = getGamePrice();
	CStrVar str;
	char tempStr[DOLLAR_LEN];

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahRight,avTop);
	fHtmlWriter.TableStart(0);
	fHtmlWriter.TableRowStart();

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
	if(gamePrice > 0.0)
	{
		DollarToString(getGamePrice(),tempStr,2);
		str.copyVarg("I understand that I will be charged %s",tempStr);
	}
	fHtmlWriter.WriteView(TTypeBetaSectionTextHtmlView(fPageOptions,str));
	fHtmlWriter.TableCellEnd();

	TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,THtmlWidthValue(10));

	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
	fHtmlWriter.SubmitField(gSubmitButtonNameStr,"Sign Me Up");
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableRowEnd();
	fHtmlWriter.TableEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewSignupBasePostPage::initialize()
{
	ASFantasyNewSignupBasePage::initialize();

	fPrizeEligible = fIsHtmlServer.getBooleanField("PrizeEligible");
}

/******************************************************************************/

void ASFantasyNewSignupBasePostPage::readRequestAddressData(
	ASFantasyNewSignupRqst& request)
{
	/* Personal Info */
	request.getName().fFirstName = fIsHtmlServer.getStringField("FirstNameTxt",cam_MayNotExist).c_str();
	request.getName().fLastName = fIsHtmlServer.getStringField("LastNameTxt",cam_MayNotExist).c_str();

	request.setAddrStreet1(fIsHtmlServer.getStringField("Street1Txt",cam_MayNotExist).c_str());
	request.setAddrStreet2(fIsHtmlServer.getStringField("Street2Txt",cam_MayNotExist).c_str());
	request.setAddrCity(fIsHtmlServer.getStringField("CityTxt",cam_MayNotExist).c_str());
	request.setAddrState(fIsHtmlServer.getStringField("StateTxt",cam_MayNotExist).c_str());
	request.setAddrZip(fIsHtmlServer.getStringField("ZipCodeTxt",cam_MayNotExist).c_str());
	
	request.setAddrCountry(fIsHtmlServer.getStringField("CountryTxt",cam_MayNotExist).c_str());
	request.setEmail(fIsHtmlServer.getStringField("EmailTxt",cam_MayNotExist).c_str());

}

/******************************************************************************/

void ASFantasyNewSignupBasePostPage::readRequestTeamData(
	ASFantasyNewSignupRqst& request)
{
	/* Team Info */
	request.setRegionName(fIsHtmlServer.getStringField("RegionNameTxt",cam_MayNotExist).c_str());
	request.setTeamName(fIsHtmlServer.getStringField("TeamNameTxt",cam_MayNotExist).c_str());
	request.setManagerName(fIsHtmlServer.getStringField("ManagerNameTxt",cam_MayNotExist).c_str());
}

/******************************************************************************/

void ASFantasyNewSignupBasePostPage::readRequestCreditCardData(
	ASFantasyNewSignupRqst& request)
{
	CStrVar str;

	/* Credit Card Info */
	request.setCCardViaFaxPhone(fIsHtmlServer.getCheckboxField("CCardViaFaxPhoneChk"));
	request.setCCardType(fIsHtmlServer.getStringField("CCardTypeSel",cam_MayNotExist).c_str());
	request.setCCardNumber(fIsHtmlServer.getStringField("CCardNumberTxt",cam_MayNotExist).c_str());

	if(fIsHtmlServer.doesFieldHaveValue("CCardExpDateMonSel",cam_MayNotExist) &&
			fIsHtmlServer.doesFieldHaveValue("CCardExpDateYearSel",cam_MayNotExist))
		str.copyVarg("%s/%s",fIsHtmlServer.getStringField("CCardExpDateMonSel",
			cam_MayNotExist).c_str(),fIsHtmlServer.getStringField(
			"CCardExpDateYearSel",cam_MayNotExist).c_str());
	request.setCCardExpDate(str);

	request.setCCardNameOn(fIsHtmlServer.getStringField("CCardNameOnTxt",cam_MayNotExist).c_str());
}

/******************************************************************************/

void ASFantasyNewSignupBasePostPage::readRequestData(
	ASFantasyNewSignupRqst& request,bool isPartic)
{
	TGameLevel gameLevel;
	double gamePrice;

	/* Game Info */
	request.setPrizeEligible(fPrizeEligible);

	gameLevel = fIsHtmlServer.getStringField("GameLevel").c_str();
	gamePrice = GamePrice(fPageOptions.isRqstMemberSet() && isPartic ?
		fPageOptions.getRqstMemberID() : TMemberID(),gameLevel == gml_Premium);

	if(!EQUAL_DOLLARS(gamePrice,fIsHtmlServer.getFloatField("GamePrice")))
		throw ASIException("ASFantasyNewSignupBasePostPage::process: game price mismatch");

	request.setGameLevel(gameLevel);
	request.setGamePrice(gamePrice);

	readRequestAddressData(request);
	readRequestTeamData(request);
	readRequestCreditCardData(request);
}

/******************************************************************************/

void ASFantasyNewSignupBasePostPage::write()
{
	if(fNewSignupResp->getSuccess())
	{
		ASFantasyNewSignupBasePage::write();
	}
	else
	{
		ASFantasyBasePageHtmlViewPtr pageHtmlViewPtr =
			ASFantasySignupErrorGetPage::newInstance(fIsHtmlServer,
				fPageOptions,fHtmlWriter,fNewSignupResp->getReasonFailed());

		pageHtmlViewPtr->process();
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
