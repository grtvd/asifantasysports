/* ASFantasyNewMemberSignupRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "PasswordEncode.h"
#include "ASFantasyNewMemberSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewMemberSignupRqst::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ASFantasyNewMemberSignupRqst::readFromFiler: not supported");
}

/******************************************************************************/

void ASFantasyNewMemberSignupRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ASFantasyNewMemberSignupRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
ASFantasyNewSignupResp* ASFantasyNewMemberSignupRqst::fulfillRequest()
{
	TDatabase* memdb = NULL;
	TDatabase* miscdb = NULL;
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
	
		memdb = GetOpenDatabase(MemberDatabaseName());
		miscdb = GetOpenDatabase(MemberMiscDatabaseName());
		db = GetOpenDatabase(PrimaryDatabaseName());
		
		memdb->StartTransaction();
		db->StartTransaction();
		miscdb->StartTransaction();
		try
		{
			memberPtr = TMember::newInstance();
			memberPtr->setMemberID(fMemberID);
			memberPtr->setPassword(fPassword.c_str());
			memberPtr->setSignupSource(fSignupSource);
		
			updateMember(memberPtr);

			createNewPartic(memberPtr,particPtr,teamPtr,fCCardViaFaxPhone);

			sendWelcomeEmail(memberPtr,teamPtr,true);

			memberID = memberPtr->getMemberID();
			encodedParticID = particPtr->encodeParticID();
			regionName = teamPtr->getRegionName();
			teamName = teamPtr->getTeamName();
			managerName = teamPtr->getManagerName();
			
			db->Commit();
			memdb->Commit();
			miscdb->Commit();
			success = true;
		}
		catch(const Exception& e)
		{
			memdb->Rollback();
			db->Rollback();
			miscdb->Rollback();
			throw ASIException(e.Message.c_str());
		}
		catch(...)
		{
			memdb->Rollback();
			db->Rollback();
			miscdb->Rollback();
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
		CommErrMsg(cel_Info,"ASFantasyNewMemberSignupRqst::"
			"fulfillRequest: signup failed, reason: %s",reasonFailed.c_str());

	return(new ASFantasyNewSignupResp(success, memberID, encodedParticID,
		regionName.c_str(), teamName.c_str(), managerName.c_str(),
		reasonFailed.c_str()));
}

/******************************************************************************/

void ASFantasyNewMemberSignupRqst::validateRequest()
{
	CStr255 errStr;
	
	/* Validate TMemberID/Password */
	fMemberID.ToUpper();
	if(fMemberID.Len() < MinMemberIDLen)
	{
		errStr.CopyVarg("User Name must be at least %d characters in length.",
			(int)MinMemberIDLen);
		throw TRequesterError(errStr.c_str());
	}
	if(!IsValidUserIDPassword(fMemberID))
		throw TRequesterError("User Name contains invalid characters.");
		
	if(!TMember::createGet(fMemberID,cam_MayNotExist).isNull())
		throw TRequesterError("User Name already in use.");

	if(fPassword.Len() < MinMemberPasswordLen)
	{
		errStr.CopyVarg("Password must be at least %d characters in length.",
			(int)MinMemberPasswordLen);
		throw TRequesterError(errStr.c_str());
	}
	if(!IsValidUserIDPassword(fPassword))
		throw TRequesterError("Password contains invalid characters.");

	if(fPassword != fReEnteredPassword)
		throw TRequesterError("Password does not match Re-Entered Password.");
		
	ASFantasyNewSignupRqst::validateRequest();
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
