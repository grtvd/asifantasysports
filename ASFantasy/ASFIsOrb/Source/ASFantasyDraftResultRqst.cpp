/* ASFantasyDraftResultRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyMiscRqst.h"
#include "ASFantasyDraftResultRqst.h"

namespace asfantasy
{

/******************************************************************************/

class DraftResultResp : public TStreamable
{
private:
	DraftResultPlayerVector fPlayerVector;
	TeamInfoNameVector		fTeamNameVector;

public:
	DraftResultResp(DraftResultPlayerVector& playerVector,
		TeamInfoNameVector& teamNameVector);
	
	virtual const char* className() const { return("DraftResultResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

DraftResultResp::DraftResultResp(DraftResultPlayerVector& playerVector,
	TeamInfoNameVector& teamNameVector)
{
	fPlayerVector = playerVector;
	fTeamNameVector = teamNameVector;
}

/******************************************************************************/

void DraftResultResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DraftResultResp::readFromFiler: not supported");
}

/******************************************************************************/

void DraftResultResp::writeToFiler(TDataFiler& filer)
{
	DraftResultPlayerPtr	playerPtr;
	int 					i, numItems;

	// write player information
	numItems = fPlayerVector.size();
	filer.writeShort((short)numItems);
	for (i=0; i<numItems; i++)
	{
		playerPtr = fPlayerVector[i];
		playerPtr->writeToFiler(filer);
	}

	// write team information
#if 1	//BOB
	fTeamNameVector.writeToFiler(filer);
#else
	TeamInfoNamePtr			teamNamePtr;
	numItems = fTeamNameVector.size();
	filer.writeShort((short)numItems);
	for (i=0; i<numItems; i++)
	{
		teamNamePtr = fTeamNameVector[i];
		teamNamePtr->writeToFiler(filer);
	}
#endif
}

/******************************************************************************/
/******************************************************************************/

DraftResultPlayer::DraftResultPlayer(byte round, byte pick, TTeamID teamID,
	const TProfPlayerPtr profPlayerPtr )
{
	clear();

	fRound = round;
	fPick = pick;
	fName = profPlayerPtr->getName();
	fPosition = profPlayerPtr->getPosition();
	fTeamID = teamID;
}

/******************************************************************************/

void DraftResultPlayer::readFromFiler(TDataFiler& filer)
{
	throw ASIException("DraftResultPlayer::readFromFiler: not supported");
}

/******************************************************************************/

void DraftResultPlayer::writeToFiler(TDataFiler& filer)
{
	filer.writeByte(fRound);
	filer.writeByte(fPick);
	fName.writeToFiler(filer);
	filer.writeByte((byte)fPosition);
	filer.writeLong(fTeamID.getID());
}

/******************************************************************************/
/******************************************************************************/

void DraftResultRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
}

/******************************************************************************/

void DraftResultRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DraftResultRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* DraftResultRqst::fulfillRequest()
{
	auto_ptr<DraftResultResp> pResponse;
	DraftResultPlayerVector playerVector;
	TeamInfoNameVector teamNameVector;
	TParticPtr particPtr;
	TTeamPtr teamPtr;

	validateRequest(particPtr,teamPtr);
	fillPlayerVector(particPtr,teamPtr,playerVector);
	teamNameVector.fillByLeagueID(teamPtr->getLeagueID());

	pResponse.reset(new DraftResultResp(playerVector,teamNameVector));
	return(pResponse.release());
}

/******************************************************************************/

void DraftResultRqst::validateRequest(TParticPtr& particPtr,TTeamPtr& teamPtr)
{
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);
}

/******************************************************************************/

void DraftResultRqst::fillPlayerVector(TParticPtr& particPtr,TTeamPtr& teamPtr,
	DraftResultPlayerVector& playerVector)
{
	ASFantasyObjectStore&	store = ASFantasyObjectStore::getThe();
	DraftResultPlayerPtr	draftResultPlayerPtr;
	TProfPlayerPtr 			profPlayerPtr;
	TPlayerID 				playerID;
	short					round, pick;

	TDraftResultPtr draftResultPtr =
		TDraftResult::createGet(teamPtr->getLeagueID(),cam_MustExist);
		
	TDraftPickRoundVector::const_iterator	roundIter;
	TDraftPickRoundVector&	draftRoundVector = draftResultPtr->draftPickRoundVector();

	// loop through all rounds of the draft
	for (roundIter=draftRoundVector.begin(), round=1; roundIter!=draftRoundVector.end();
		roundIter++, round++)
	{
		const TDraftPickVector&				draftPickVector = *roundIter;
		TDraftPickVector::const_iterator	playerIter;

		// loop through each team pick in the round
		for (playerIter=draftPickVector.begin(), pick=1; playerIter!=draftPickVector.end();
			playerIter++, pick++)
		{
			const TDraftPick& draftPick = *playerIter;
			profPlayerPtr = store.getProfPlayer(draftPick.fPlayerID);
			draftResultPlayerPtr = DraftResultPlayer::createFromProfPlayer(
				round, pick, draftPick.fTeamID, profPlayerPtr);
			playerVector.push_back(draftResultPlayerPtr);
		}
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
