/* ASFantasyNewParticSignupRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASFantasyNewParticSignupRqst.h"

using namespace asfantasy;

/******************************************************************************/
/******************************************************************************/

void ASFantasyNewParticSignupRqst::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ASFantasyNewParticSignupRqst::readFromFiler: not supported");
}

/******************************************************************************/

void ASFantasyNewParticSignupRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ASFantasyNewParticSignupRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
ASFantasyNewSignupResp* ASFantasyNewParticSignupRqst::fulfillRequest()
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
			fMemberID.ToUpper();
			memberPtr = TMember::createGet(fMemberID,cam_MustExist);
		
			updateMember(memberPtr);

			createNewPartic(memberPtr,particPtr,teamPtr,fCCardViaFaxPhone);

			sendWelcomeEmail(memberPtr,teamPtr,false);

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
			"ASFantasyNewParticSignupRqst: signup failed, reason: %s",
			reasonFailed.c_str());

	return(new ASFantasyNewSignupResp(success, memberID, encodedParticID,
		regionName.c_str(), teamName.c_str(), managerName.c_str(),
		reasonFailed.c_str()));
}

/******************************************************************************/
/******************************************************************************/
