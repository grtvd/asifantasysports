/* ASFantasyLineupUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CBldComm.h"

#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyLineupUpdateRqst.h"

namespace asfantasy
{

/******************************************************************************/

class LineupUpdateResp : public TStreamable
{
public:
	virtual const char* className() const { return("LineupUpdateResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void LineupUpdateResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("LineupUpdateResp::readFromFiler: not supported");
}

/******************************************************************************/

void LineupUpdateResp::writeToFiler(TDataFiler& filer)
{
}

/******************************************************************************/
/******************************************************************************/

void LineupUpdateRqst::readFromFiler(TDataFiler& filer)
{
	int i,numLineups;

	fEncodedParticID = filer.readString().c_str();

	numLineups = filer.readShort();
	for(i = 0; i < numLineups; ++i)
	{
		TPlayerIDVector playerIDVector;

		playerIDVector.readFromFiler(filer);
		fPlayerIDArray.push_back(playerIDVector);
	}
}

/******************************************************************************/

void LineupUpdateRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("LineupUpdateRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* LineupUpdateRqst::fulfillRequest()
{
	auto_ptr<LineupUpdateResp> pResponse;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	std::vector<TPlayerIDVector>::iterator iter;
	int whichLineup;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(), cam_MustExist);

	if(!areChangesAllowed(teamPtr->getLeagueID()))
		throw ASIException("LineupUpdateRqst::fulfillRequest: changes not allowed");

	LoadPlayerIDVectorByTeamID(particPtr->getTeamID(),fTeamPlayerIDVector);

	// validate lineups
	for(iter = fPlayerIDArray.begin(),whichLineup = 0;
			iter != fPlayerIDArray.end(); ++iter,++whichLineup)
		LineupUpdateRqst::validateLineup(whichLineup,*iter);

	// update the lineup
	saveLineups(teamPtr);
	teamPtr->update();
	
	// update LastTransDateTime
	particPtr->setLastTransDateTime(TDateTime::CurrentDateTime());
	particPtr->update();

	pResponse.reset(new LineupUpdateResp());
	return (pResponse.release());
}

/******************************************************************************/

void LineupUpdateRqst::validateLineup(int whichLineup,
	const TPlayerIDVector& playerIDVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	// verifies no duplicates
	if (playerIDVector.doesContainDups(true))
		throw ASIException("LineupUpdateRqst::validateLineup: duplicate TPlayerID");

	// verify player IDs
	if(!store.isPlayerIDVectorValidForProfPlayers(playerIDVector,true))
		throw ASIException("LineupUpdateRqst::validateLineup: invalid TPlayerID");

	// verifies that players are on the specified team
	if(!fTeamPlayerIDVector.contains(playerIDVector,true))
		throw ASIException("LineupUpdateRqst::validateLineup: player not on specified team");
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
