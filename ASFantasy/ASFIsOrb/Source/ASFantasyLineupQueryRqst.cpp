/* ASFantasyLineupQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDB.h"
#include "ASFantasyLineupQueryRqst.h"

namespace asfantasy
{

/******************************************************************************/

class LineupQueryResp : public TStreamable
{
private:
	TGameLevel fGameLevel;
	TTeamID fShowTeamID;
	TeamInfoNameVector fTeamNameVector;
	bool fEnableChanges;
	std::vector<TPlayerIDVector> fPlayerIDArray;
	PlayerInfoVector fLineupPlayerVector;

public:
	LineupQueryResp(TGameLevel gameLevel,TTeamID showTeamID,
		TeamInfoNameVector& teamNameVector,bool enableChanges,
		std::vector<TPlayerIDVector>& playerIDArray,
		PlayerInfoVector& lineupPlayerVector);

	virtual const char* className() const { return("LineupQueryResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

LineupQueryResp::LineupQueryResp(TGameLevel gameLevel,TTeamID showTeamID,
	TeamInfoNameVector& teamNameVector,bool enableChanges,
	std::vector<TPlayerIDVector>& playerIDArray,PlayerInfoVector& lineupPlayerVector)
{
	fGameLevel = gameLevel;
	fShowTeamID = showTeamID;
	fTeamNameVector = teamNameVector;
	fEnableChanges = enableChanges;
	fPlayerIDArray = playerIDArray;
	fLineupPlayerVector = lineupPlayerVector;
}

/******************************************************************************/

void LineupQueryResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("LineupQueryResp::readFromFiler: not supported");
}

/******************************************************************************/

void LineupQueryResp::writeToFiler(TDataFiler& filer)
{
	std::vector<TPlayerIDVector>::iterator iter;

	filer.writeByte((byte)fGameLevel);
	filer.writeLong(fShowTeamID.getID());
	fTeamNameVector.writeToFiler(filer);
	
	filer.writeBoolean(fEnableChanges);
	
	// write lineup players information
	filer.writeShort((short)fPlayerIDArray.size());
	for(iter = fPlayerIDArray.begin(); iter != fPlayerIDArray.end(); ++iter)
		(*iter).writeToFiler(filer);

	// write all team player information
	fLineupPlayerVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

LineupPlayer::LineupPlayer(const TProfPlayerPtr profPlayerPtr) :
	PlayerInfoExt(profPlayerPtr)
{
}

/******************************************************************************/

void LineupPlayer::clear()
{
	PlayerInfoExt::clear();
}

/******************************************************************************/

void LineupPlayer::readFromFiler(TDataFiler& filer)
{
	throw ASIException("LineupPlayer::readFromFiler: not supported");
}

/******************************************************************************/

void LineupPlayer::writeToFiler(TDataFiler& filer)
{
	PlayerInfoExt::writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

void LineupQueryRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fShowTeamID = filer.readLong();
}

/******************************************************************************/

void LineupQueryRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("LineupQueryRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* LineupQueryRqst::fulfillRequest()
{
	auto_ptr<LineupQueryResp> pResponse;
	TeamInfoNameVector teamNameVector;
	bool enableChanges;
	std::vector<TPlayerIDVector> playerIDArray;
	PlayerInfoVector lineupPlayerVector;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);

	if((particPtr->getGameLevel() == gml_Standard) ||
		fShowTeamID.isUndefined() || (fShowTeamID == particPtr->getTeamID()))
	{
		fShowTeamID = particPtr->getTeamID();
		teamPtr = TTeam::createGet(fShowTeamID, cam_MustExist);
		enableChanges = areChangesAllowed(teamPtr->getLeagueID());
	}
	else
	{
		teamPtr = TTeam::createGet(fShowTeamID, cam_MustExist);
		enableChanges = false;
	}
	
	teamNameVector.fillByLeagueID(teamPtr->getLeagueID());
	fillPlayerIDArray(teamPtr,playerIDArray);
	fillLineupPlayerVector(teamPtr,lineupPlayerVector);

	pResponse.reset(new LineupQueryResp(particPtr->getGameLevel(),fShowTeamID,
		teamNameVector,enableChanges,playerIDArray,lineupPlayerVector));
	return (pResponse.release());
}

/******************************************************************************/

void LineupQueryRqst::fillLineupPlayerVector(const TTeamPtr teamPtr,
	PlayerInfoVector& lineupPlayerVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerVector playerVector;
	TPlayerVector::const_iterator iter;
	TProfPlayerPtr profPlayerPtr;
	PlayerInfoPtr lineupPlayerPtr;

	LoadPlayerVectorByTeamID(teamPtr->getTeamID(), playerVector);
	for (iter =playerVector.begin(); iter != playerVector.end(); ++iter)
	{
		profPlayerPtr = store.getProfPlayer( (*iter)->getPlayerID() );
		lineupPlayerPtr = createNewLineupPlayer(profPlayerPtr);
		lineupPlayerVector.push_back(lineupPlayerPtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
