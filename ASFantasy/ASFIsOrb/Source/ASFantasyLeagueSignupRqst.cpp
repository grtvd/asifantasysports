/* ASFantasyLeagueSignupRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommType.h"
#include "CommMisc.h"
#include "CommDB.h"
#include "PasswordEncode.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyDB.h"
#include "ASFantasyLeagueSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void LeagueSignupResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("LeagueSignupResp::readFromFiler: not supported");
}

/******************************************************************************/

void LeagueSignupResp::writeToFiler(TDataFiler& filer)
{
	filer.writeBoolean(fSuccess);
	filer.writeString(fLeagueName.c_str());
	filer.writeString(fReasonFailed.c_str());
}

/******************************************************************************/
/******************************************************************************/

void LeagueSignupRqst::readFromFiler(TDataFiler& filer)
{
	fLst = filer.readShort();

	/* Partic Info */
	fEncodedParticID.Copy(filer.readString().c_str());

	/* League Info */
	if(fLst == lst_JoinOpenPublic)
	{
		// nothing more to read
	}
	else if(fLst == lst_CreatePrivate)
	{
		fLeaguePassword.Copy(filer.readString().c_str());
	}
	else if(fLst == lst_JoinPrivate)
	{
		fLeagueID = filer.readLong();
		fLeaguePassword.Copy(filer.readString().c_str());
	}
	else
		throw ASIException("LeagueSignupRqst::readFromFiler: unknown LeagueSignupType");
}

/******************************************************************************/

void LeagueSignupRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("LeagueSignupRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* LeagueSignupRqst::fulfillRequest()
{
	auto_ptr<LeagueSignupResp> pResponse;
	
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TLeaguePtr leaguePtr;
	
	bool success = false;
	TParticID particID;
	TLeagueName leagueName;
	CStrVar reasonFailed;
	
	try
	{
		validateRequest(particPtr,teamPtr);

		if(fLst == lst_JoinOpenPublic)
		{
			joinPublicLeague(particPtr,teamPtr,leaguePtr);
		}
		else if(fLst == lst_CreatePrivate)
		{
			createPrivateLeague(teamPtr,fLeaguePassword,leaguePtr);
		}
		else if(fLst == lst_JoinPrivate)
		{
			joinPrivateLeague(teamPtr,fLeagueID,fLeaguePassword,leaguePtr);
		}
		else
			throw ASIException("LeagueSignupRqst::FulfillRequest: unknown LeagueSignupType");
		
		leagueName = leaguePtr->getName();
	
		particPtr->setStatus(pts_Active);
		//BOB particPtr->setTeamID(teamPtr->getTeamID());
		particPtr->update();
		success = true;
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

	pResponse.reset(new LeagueSignupResp(success, leagueName, reasonFailed));
	
	if(!success)
		CommErrMsg(cel_Info,"LeagueSignupRqst::FulfillRequest: reason "
			"failed(%s)",reasonFailed.c_str());

	setCommitTransaction(success);
	return(pResponse.release());
}

/******************************************************************************/

void LeagueSignupRqst::validateRequest(TParticPtr& particPtr,TTeamPtr& teamPtr)
{
	if(!fLst.isValid())
		throw ASIException("LeagueSignupRqst::validateRequest: fLst not valid");

	// Validate Partic
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);

	if(particPtr->getStatus() != pts_PaymentApproved)
		throw ASIException("LeagueSignupRqst::validateRequest: unexpected status");

	// Validate Team
	teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);

	if(!teamPtr->getLeagueID().isUndefined())
		throw TRequesterError("League has already been assigned.");
		
	// Validate League Info
	//	LeagueID and LeaguePassword will be validated during fetch of League data
}

/******************************************************************************/

TLeaguePtr LeagueSignupRqst::createNewLeague(const TPassword& password,
	bool reserved)
{
	TLeaguePtr leaguePtr = TLeague::newInstance();

	leaguePtr->setName(selectLeagueName());
	leaguePtr->setPassword(password);
	leaguePtr->setGamePhase(gmph_Enrollment);
	leaguePtr->setReserved(reserved);
	leaguePtr->setLastProcessedDate(TDateTime::CurrentDate());

	return(leaguePtr);
}

/******************************************************************************/

TLeagueName LeagueSignupRqst::selectLeagueName()
{
	TQuery *query = NULL;
	CStr255 selectStr;
	CStr31 whereStr;
	int count;
	int moveBy;
	TLeagueName leagueName;

	try
	{
		whereStr.Copy("Used = 0");
		selectStr.Copy("select * from LeagueName where ");
		selectStr.Concat(whereStr);
		
		query = OpenQuery(PrimaryDatabaseName(),selectStr.c_str());
		if (!query->Eof)
		{
			count = CountTableRecords(PrimaryDatabaseName(),"LeagueName",whereStr.c_str());
			
			moveBy = GetRandomFromRange(0,count - 1);
			if(moveBy > 0)
				query->MoveBy(moveBy);
			leagueName = query->FieldByName("Name")->AsString.c_str();
			CloseQuery(query);

			selectStr.CopyVarg("update LeagueName set Used = 1 where Name = '%s'",
				leagueName.c_str());
			ExecQuery(PrimaryDatabaseName(),selectStr.c_str());
			leagueName.Compress(CSW_TRAILING);
		}
		else
		{
			CommErrMsg(cel_Warning,"LeagueSignupRqst::selectLeagueName: "
				"no names remain");
			leagueName.Copy("NEEDS A NAME");
		}

		CloseQuery(query);
	}
	catch(const Exception& e)
	{
		CloseQuery(query);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(query);
		throw;
	}

	return leagueName;
}

/******************************************************************************/

TLeaguePtr LeagueSignupRqst::getOpenPublicLeague(const TParticPtr teamParticPtr)
{
	TLeagueVector leagueVector;
	TLeagueVector::iterator leagueIter;
	TLeaguePtr leaguePtr;

	TTeamVector teamVector;
	TParticVector particVector;
	TParticVector::iterator particIter;
	TParticPtr particPtr;

	bool found;

	LoadLeagueVectorByOpenPublic(leagueVector);
	leagueVector.sortByID();

	if(leagueVector.size() == 0)
		return(TLeaguePtr());

	// If this Member already in league as with another partic.
	for(leagueIter = leagueVector.begin(); leagueIter != leagueVector.end();
		leagueIter++)
	{
		leaguePtr = *leagueIter;

		LoadTeamVectorByLeagueID(leaguePtr->getLeagueID(),teamVector);
		LoadParticVectorByTeamVector(teamVector,particVector);

		found = false;
		for(particIter = particVector.begin();
			(particIter != particVector.end()) && !found; particIter++)
		{
			particPtr = *particIter;
			
			if(teamParticPtr->getMemberID() == particPtr->getMemberID())
			{
				found = true;
				CommErrMsg(cel_Warning,"LeagueSignupRqst::getOpenPublicLeague "
					"skipping league(%s) with duplicate Members",
					leaguePtr->getLeagueID().c_str());
			}
		}

		if(!found)
			return(leaguePtr);
	}

	return(TLeaguePtr());
}

/******************************************************************************/

void LeagueSignupRqst::addTeamToLeague(TTeamPtr teamPtr,TLeaguePtr leaguePtr)
{
	TTeamVector teamVector;
	TTeamIDVector& overallStandings = leaguePtr->overallStandings();
	int numTeams;
	bool closeLeague = false;
	
	// This should never happen for pulic leagues but may happen for private leagues.
	if(leaguePtr->getGamePhase() != gmph_Enrollment)
		throw TRequesterError("League already closed.");
		
	LoadTeamVectorByLeagueID(leaguePtr->getLeagueID(),teamVector);
	numTeams = teamVector.size();

	if(numTeams != cast2int(overallStandings.size()))
		CommErrMsg(cel_Warning,"LeagueSignupRqst::addTeamToLeague: "
			"numTeams(%d) != overallStandings.size(%d)",numTeams,
			(int)overallStandings.size());
		
	if(leaguePtr->isReserved())
	{
		if(numTeams >= MaxTeamsPerPrivateLeague())
			throw TRequesterError("League is full.");
		
		if(numTeams + 1 >= MaxTeamsPerPrivateLeague())
			closeLeague = true; 
	}
	else
	{
		// This should never happen. Bug exists if it does.
		if(numTeams >= NumTeamsPerPublicLeague())
			throw ASIException("League is full.");
	
		if(numTeams + 1 >= NumTeamsPerPublicLeague())
			closeLeague = true;
	}

	// should league be closed?
	if(closeLeague)
	{
		leaguePtr->calcDraftDate(false);
		leaguePtr->setGamePhase(gmph_PreDraft);
	}

	overallStandings.push_back(teamPtr->getTeamID());
	leaguePtr->update();
	
	teamPtr->setLeagueID(leaguePtr->getLeagueID());
	// alternate Division
	teamPtr->setDivision(((numTeams % 2) == 0) ? div_East : div_West);
	teamPtr->update();
}

/******************************************************************************/

void LeagueSignupRqst::joinPublicLeague(const TParticPtr particPtr,
	TTeamPtr teamPtr,TLeaguePtr& leaguePtr)
{
	leaguePtr = getOpenPublicLeague(particPtr);

	if(leaguePtr.isNull())
	{
		leaguePtr = createNewLeague();
		leaguePtr->update();
	}
	
	addTeamToLeague(teamPtr,leaguePtr);
}

/******************************************************************************/

void LeagueSignupRqst::createPrivateLeague(TTeamPtr teamPtr,
	const TPassword& leaguePassword,TLeaguePtr& leaguePtr)
{
	leaguePtr = createNewLeague(leaguePassword,true);
	leaguePtr->update();
	
	addTeamToLeague(teamPtr,leaguePtr);
}

/******************************************************************************/

void LeagueSignupRqst::joinPrivateLeague(TTeamPtr teamPtr,TLeagueID leagueID,
	const TPassword& leaguePassword,TLeaguePtr& leaguePtr)
{
	leaguePtr = TLeague::createGet(leagueID,cam_MayNotExist);
	if(leaguePtr.isNull())
		throw TRequesterError("Invalid League ID.");

	if(leaguePtr->getPassword() != leaguePassword)
		throw TRequesterError("Invalid League Password.");

	addTeamToLeague(teamPtr,leaguePtr);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
