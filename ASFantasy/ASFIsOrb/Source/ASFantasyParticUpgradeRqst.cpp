/* ParticUpgradeRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ParticUpgradeRqst.h"

using namespace asfantasy;

/******************************************************************************/
/******************************************************************************/

void ParticUpgradeRqst::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ParticUpgradeRqst::readFromFiler: not supported");
}

/******************************************************************************/

void ParticUpgradeRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ParticUpgradeRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
NewSignupResp* ParticUpgradeRqst::fulfillRequest()
{
	TDatabase* memdb = NULL;
	TDatabase* db = NULL;

	TMemberPtr memberPtr;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	
	bool success = false;
	asmember::TMemberID memberID;
	TEncodedParticID encodedParticID;
	TRegionName regionName;
	TTeamName teamName;
	TManagerName managerName;
	CStrVar reasonFailed;
	
	try
	{
		validateRequest();
	
		memdb = GetOpenDatabase(MemberDatabaseName);
		db = GetOpenDatabase(PrimaryDatabaseName);

		memdb->StartTransaction();
		db->StartTransaction();
		try
		{
			particPtr = TPartic::createGet(fParticID,cam_MustExist);
			if(particPtr->getUpgradeStatus() != pus_Undefined)
				throw ASIException("ParticUpgradeRqst::fulfillRequest: partic cannot be upgraded");
			if(particPtr->getGameLevel() != gml_Standard)
				CommErrMsg(cel_Error,"ParticUpgradeRqst::fulfillRequest: upgrading Premium account");
		
			memberPtr = TMember::createGet(particPtr->getMemberID(),cam_MustExist);
			updateMember(memberPtr);
		
			particPtr->setUpgradeDate(TDateTime::CurrentDate());
			particPtr->setUpgradePrice(fGamePrice);
			particPtr->setUpgradeStatus(fCCardViaFaxPhone ? pus_NeedCCInfo : pus_WaitingApproval);
			particPtr->update();

			memberID = particPtr->getMemberID();
			encodedParticID = particPtr->encodeParticID();
			
			teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);
			regionName = teamPtr->getRegionName();
			teamName = teamPtr->getTeamName();
			managerName = teamPtr->getManagerName();
			
			db->Commit();
			memdb->Commit();
			success = true;
		}
		catch(const Exception& e)
		{
			memdb->Rollback();
			db->Rollback();
			throw ASIException(e.Message.c_str());
		}
		catch(...)
		{
			memdb->Rollback();
			db->Rollback();
			throw;
		}
	}
	catch(const TRequesterError& e)
	{
		reasonFailed.copy(e.getMessage());
	}
	catch(const Exception& e)
	{
		reasonFailed.copyVarg("Internal Error: %s",e.Message.c_str());
	}
	catch(const ASIException& e)
	{
		reasonFailed.copyVarg("Internal Error: %s",e.getMsg());
	}
	catch(const exception& e)
	{
		reasonFailed.copyVarg("Internal Error: %s",e.what());
	}
	catch(...)
	{
		reasonFailed.copy("Internal Error: Unknown");
	}

	if(!success)
		CommErrMsg(cel_Info,"NewMemberSignupRqst::ParticUpgradeRqst: "
			"signup failed, reason: %s",reasonFailed.c_str());

	return(new NewSignupResp(success, memberID, encodedParticID,
		regionName.c_str(), teamName.c_str(), managerName.c_str(),
		reasonFailed.c_str()));
}

/******************************************************************************/

void ParticUpgradeRqst::validateRequest()
{
	validateRequestAddress();

	if(fGamePrice > 0.0)
		validateRequestCreditCard();
}

/******************************************************************************/
/******************************************************************************/
