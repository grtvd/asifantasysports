/* ASFantasyNewSignupRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "PasswordEncode.h"
#include "ASFantasyNewSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewSignupResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ASFantasyNewSignupResp::readFromFiler: not supported");
}

/******************************************************************************/

void ASFantasyNewSignupResp::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ASFantasyNewSignupResp::writeToFiler: not supported");
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewSignupRqst::validateRequestAddress()
{
	/* Validate Personal Info */
	if(fName.fFirstName.Len() == 0)
		throw TRequesterError("First Name must be entered.");
	if(fName.fLastName.Len() == 0)
		throw TRequesterError("Last Name must be entered.");

	if(fAddrStreet1.Len() == 0)
		throw TRequesterError("Street Address must be entered.");
	if(fAddrCity.Len() == 0)
		throw TRequesterError("City must be entered.");
	if(fAddrState.Len() == 0)
		throw TRequesterError("State must be entered.");
	if(fAddrZip	.Len() == 0)
		throw TRequesterError("Zip Code must be entered.");
	if(fAddrCountry.Len() == 0)
		throw TRequesterError("Country must be entered.");
	if(fEmail.Len() == 0)
		throw TRequesterError("Email must be entered.");
}

/******************************************************************************/

void ASFantasyNewSignupRqst::validateRequestTeam()
{
	/* Validate Team Info */
	if(fManagerName.Len() == 0)
		throw TRequesterError("Owner Name must be entered.");
	if(fRegionName.Len() == 0)
		throw TRequesterError("Team City must be entered.");
	if(fTeamName.Len() == 0)
		throw TRequesterError("Team Nickname must be entered.");
}

/******************************************************************************/

void ASFantasyNewSignupRqst::validateRequestCreditCard()
{
	TCCardNumber ccardNumber;
	const char* pTempStr;
	tag::TDate expDate;
	int month,day,year;

	// Validate Credit Card Info

	if(!fCCardViaFaxPhone)
	{
		if(fCCardType.Len() == 0)
			throw TRequesterError("Card Type must be entered.");
		if(fCCardNumber.Len() == 0)
			throw TRequesterError("Card Number must be entered.");
	}
	// remove all spaces from CCardNumber
	fCCardNumber.Compress(CSW_ALL);
	// remove all hyphens from CCardNumber
	for(pTempStr = fCCardNumber.c_str(); *pTempStr != '\0'; ++pTempStr)
		if(*pTempStr != '-')
			ccardNumber.NConcat(pTempStr,1);
	fCCardNumber.Copy(ccardNumber);

	// Validate Credit Card Exp. Date
	if(fCCardExpDate.Len() == 0)
	{
		if(!fCCardViaFaxPhone)
			throw TRequesterError("Exp. Date must be entered.");
	}
	else	// User entered an Exp. Date
	{
		if(StringToDate(fCCardExpDate.c_str(),DF_MM_YY,&expDate))
		{
			DateToMDY(expDate,&month,&day,&year);
			fCCardExpDate.CopyVarg("%02d%02d",year % 100,month);
		}
		else // Exp. Date is invalid. If sending via Fax/Phone, then clear, otherwise error.
		{
			if(!fCCardViaFaxPhone)
				throw TRequesterError("Exp. Date is invalid or is not in the correct format.");
			else
				fCCardExpDate.Clear();
		}
	}
	
	if(!fCCardViaFaxPhone)
	{
		if(fCCardNameOn.Len() == 0)
			throw TRequesterError("Name on the card must be entered.");
	}
}

/******************************************************************************/

void ASFantasyNewSignupRqst::validateRequest()
{
	validateRequestAddress();
	validateRequestTeam();

	if(fGamePrice > 0.0)
		validateRequestCreditCard();
}

/******************************************************************************/

void ASFantasyNewSignupRqst::updateMember(TMemberPtr memberPtr)
{
	memberPtr->getName() = fName;
	memberPtr->setAddrStreet1(fAddrStreet1);
	memberPtr->setAddrStreet2(fAddrStreet2);
	memberPtr->setAddrCity(fAddrCity);
	memberPtr->setAddrState(fAddrState);
	memberPtr->setAddrZip(fAddrZip);
	memberPtr->setAddrCountry(fAddrCountry);
	memberPtr->setEmail(fEmail);

	if(fCCardType.HasLen())
		memberPtr->setCCardType(TCreditCardType(fCCardType));
	if(fCCardNumber.HasLen())
		memberPtr->setCCardNumber(fCCardNumber);
	if(fCCardExpDate.HasLen())
		memberPtr->setCCardExpDate(fCCardExpDate);
	if(fCCardNameOn.HasLen())
		memberPtr->setCCardNameOn(fCCardNameOn);

	memberPtr->update();
}

/******************************************************************************/
	
void ASFantasyNewSignupRqst::createNewPartic(const TMemberPtr& memberPtr,
	TParticPtr& particPtr,TTeamPtr& teamPtr,bool needCreditCardInfo)
{
	teamPtr = TTeam::newInstance();
	teamPtr->setRegionName(fRegionName);
	teamPtr->setTeamName(fTeamName);
	teamPtr->setManagerName(fManagerName);
	teamPtr->update();
	
	particPtr = TPartic::newInstance();
	particPtr->setMemberID(memberPtr->getMemberID());
	particPtr->setPassword(memberPtr->getPassword());
	particPtr->setTeamID(teamPtr->getTeamID());
	particPtr->setGameLevel(fGameLevel);
	particPtr->setGamePrice(fGamePrice);
	particPtr->setPrizeEligible(fPrizeEligible);
	particPtr->setStatus(needCreditCardInfo ? pts_NeedCCInfo : pts_WaitingApproval);
	particPtr->setSignupDate(TDateTime::CurrentDate());
	particPtr->update();

	teamPtr->setParticID(particPtr->getParticID());
	teamPtr->update();
	
	setupDraftRanking(teamPtr);
}

/******************************************************************************/

void ASFantasyNewSignupRqst::setupDraftRanking(const TTeamPtr& teamPtr)
{
	TDraftRankingPtr defDraftRankingPtr;
	TDraftRankingPtr newDraftRankingPtr;

	defDraftRankingPtr = TDraftRanking::createGet(DefaultDraftRankingTeamID,
		cam_MustExist);

	newDraftRankingPtr = TDraftRanking::newInstance();
	newDraftRankingPtr->setTeamID(teamPtr->getTeamID());
	newDraftRankingPtr->playerIDVector() =
		(const TPlayerIDVector&)defDraftRankingPtr->playerIDVector();

	newDraftRankingPtr->update();
}

/******************************************************************************/

void ASFantasyNewSignupRqst::sendWelcomeEmail(const TMemberPtr memberPtr,
	const TTeamPtr teamPtr,bool isNewMember)
{
	TSendMailPtr sendMailPtr;
	CStrVar str;

	sendMailPtr = TSendMail::newInstance();
	sendMailPtr->setCreatedDateTime();
	sendMailPtr->setSender(TechSupportEmail());
	sendMailPtr->setRecipient(memberPtr->getEmail());
	str.copyVarg("Welcome to %s",AppNameFull().c_str());
	sendMailPtr->setSubject(str);

	str.copyVarg("Congratulations!  Your new %s team, the %s, has "
		"been successfully signed up!\r\n\r\n",AppNameFull().c_str(),
		teamPtr->getFullTeamName().c_str());

	if(isNewMember)
	{
		str.concatVarg("During sign up, you created a new Affinity Sports "
			"member account with the following User Name and "
			"Password:\r\n\r\n");
		str.concatVarg("    User Name: %s\r\n",memberPtr->getMemberID().c_str());
		str.concatVarg("    Password: %s\r\n\r\n",memberPtr->getPassword());

		str.concatVarg("Please make note of these.  You will need them to "
			"access your team.\r\n\r\n");
		str.concatVarg("You can access your team at "
			"http://www.affinitysports.com\r\n\r\n");
	}
	else
	{
		str.concatVarg("You can access your team at "
			"http://www.affinitysports.com using your existing member "
			"account with the User Name \"%s\".\r\n\r\n",
			memberPtr->getMemberID().c_str());
	}

	str.concatVarg("Your first order of business will be to prepare for the "
		"draft.  Watch the Front Office page for your upcoming draft date "
		"and other important messages.\r\n\r\n");

	str.concatVarg("Thank you for your interest in fantasy sports games "
		"from Affinity Sports.  Have a great season of fantasy game "
		"playing!\r\n\r\n");

	str.concatVarg("The Ref\r\nAffinity Sports\r\n");

	sendMailPtr->setBodyText(CharWordWrapString(str,MailerStandardBodyTextWidth()));
	sendMailPtr->update();
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/ 
