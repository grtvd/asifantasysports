/* ASFantasyAppOptions.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <stdexcep.h>

#include "RegistryExt.h"
#include "ASFantasyAppOptions.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

THoldProcessing::THoldProcessing(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "NO")
		fT = hpr_NoHold;
	else if(value == "AFTERBEGIN")
		fT = hpr_HoldAfterBegin;
	else if(value == "DONTBEGIN")
		fT = hpr_HoldDontBegin;
	else
		throw ASIException("THoldProcessing::THoldProcessing: invalid str");
}

/******************************************************************************/

const char* THoldProcessing::c_str() const
{
	switch(fT)
	{
		case hpr_NoHold:
			return("NO");
		case hpr_HoldAfterBegin:
			return("AFTERBEGIN");
		case hpr_HoldDontBegin:
			return("DONTBEGIN");
		default:
			break;
	};

	throw ASIException("THoldProcessing::c_str: invalid fT");
}

/******************************************************************************/

// Load Registry entries that won't change while program is running.

void ASFantasyAppOptions::loadAllStatics()
{
	ASMemberAppOptions::loadAllStatics();

	fRegistryHost = TRegistryExt::KeyReadString(getRegistryRoot(),
		"RegistryHost").c_str();

	auto_ptr<TRegistryExt> pReg(new TRegistryExt());
	const char* root = getRegistryRoot();

	if(pReg->OpenKey(root,false))
	{
		fGameID = pReg->ReadString("GameID").c_str();
		fGamePriceMemberPremium = pReg->ReadFloatAsString("GamePriceMemberPremium");
		fGamePriceMemberStandard = pReg->ReadFloatAsString("GamePriceMemberStandard");
		fGamePriceParticPremium = pReg->ReadFloatAsString("GamePriceParticPremium");
		fGamePriceParticStandard = pReg->ReadFloatAsString("GamePriceParticStandard");

		fNightlyProcessingTime = pReg->ReadTimeAsString("NightlyProcessingTime");

		fSignupStartDate = pReg->ReadDateAsString("SignupStartDate");
		fSignupEndDate = pReg->ReadDateAsString("SignupEndDate");
		fUpgradeAvailable = pReg->ReadBoolAsString("UpgradeAvailable");
		fPremiumTrialAvailable = pReg->ReadBoolAsString("PremiumTrialAvailable");
		
		fStatStartDate = pReg->ReadDateAsString("StatStartDate");
		fStatEndDate = pReg->ReadDateAsString("StatEndDate");

		fRegularStartDate = pReg->ReadDateAsString("RegularStartDate");
		fDropDeadDate = pReg->ReadDateAsString("DropDeadDate");
		fSeasonOpener = pReg->ReadDateAsString("SeasonOpener");
		fTradingStartDate = pReg->ReadDateAsString("TradingStartDate");
		fTradingEndDate = pReg->ReadDateAsString("TradingEndDate");
		fPlayoffStartDate = pReg->ReadDateAsString("PlayoffStartDate");
		
		pReg->CloseKey();
	}
	else
		throw ASIException("ASFantasyAppOptions::loadAllStatics: invalid "
			"getRegistryRoot(%s)",root);
}

/******************************************************************************/

DirSpec ASFantasyAppOptions::getStatHomeDir() const
{
	DirSpec dirSpec;

	dirSpec.SetFromString(TRegistryExt::RemoteKeyReadString(fRegistryHost,
		getRegistryRoot(),"StatHomeDir"));

	return(dirSpec);
}

/******************************************************************************/

bool ASFantasyAppOptions::getInManualSystemMaintMode()
{
	return(TRegistryExt::KeyReadBoolAsString(getRegistryRoot(),
		"InManualSystemMaintMode"));
}

/******************************************************************************/

bool ASFantasyAppOptions::getInNightlyProcessing()
{
	return(TRegistryExt::KeyReadBoolAsString(getRegistryRoot(),
		"InNightlyProcessing"));
}

/******************************************************************************/

void ASFantasyAppOptions::setInNightlyProcessing(bool set)
{
	TRegistryExt::KeyWriteBoolAsString(getRegistryRoot(),
		"InNightlyProcessing",set);
}

/******************************************************************************/

THoldProcessing ASFantasyAppOptions::getHoldNightlyProcessing()
{
	return(THoldProcessing(TRegistryExt::KeyReadString(getRegistryRoot(),
		"HoldNightlyProcessing").c_str()));
}

/******************************************************************************/
#if 0	//BOB

void ASFantasyAppOptions::setHoldNightlyProcessing(THoldProcessing holdProcessing)
{
	TRegistryExt::KeyWriteString(getRegistryRoot(),
		"HoldNightlyProcessing",holdProcessing.c_str());
}

#endif
/******************************************************************************/

TDateTime ASFantasyAppOptions::getLastProcessingDate()
{
	return(TRegistryExt::KeyReadDateAsString(getRegistryRoot(),
		"LastProcessingDate"));
}

/******************************************************************************/

void ASFantasyAppOptions::setLastProcessingDate(TDateTime date)
{
	TRegistryExt::KeyWriteDateAsString(getRegistryRoot(),
		"LastProcessingDate",date);
}

/******************************************************************************/

TDateTime ASFantasyAppOptions::getLastBackupDate() const
{
	return(TRegistryExt::KeyReadDateAsString(getRegistryRoot(),"LastBackupDate"));
}

/******************************************************************************/

void ASFantasyAppOptions::setLastBackupDate(const TDateTime date)
{
	TRegistryExt::KeyWriteDateAsString(getRegistryRoot(),"LastBackupDate",date);
}

/******************************************************************************/

TDateTime ASFantasyAppOptions::getLastStatLoadDate() const
{
	return(TRegistryExt::KeyReadDateAsString(getRegistryRoot(),"LastStatLoadDate"));
}

/******************************************************************************/

void ASFantasyAppOptions::setLastStatLoadDate(const TDateTime date)
{
	TRegistryExt::KeyWriteDateAsString(getRegistryRoot(),"LastStatLoadDate",date);
}

/******************************************************************************/
/******************************************************************************/

TDateTime NextProcessingDateTime(TDateTime fromDateTime,int plusDays)
{
	TDateTime next = floor(fromDateTime + plusDays) + NightlyProcessingTime();
	TDateTime fromTime = fromDateTime - floor(fromDateTime);

	if(fromTime > NightlyProcessingTime())
		next++;

	return(next);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/

