/* ASFantasyPlayoffRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyMiscRqst.h"
#include "ASFantasyPlayoffRqst.h"

namespace asfantasy
{

/******************************************************************************/

class PlayoffResp : public TStreamable
{
private:
	PlayoffTeams fPlayoffTeams;
	TeamInfoNameVector fTeamNameVector;

public:
	PlayoffResp(const PlayoffTeams& playoffTeams,
		TeamInfoNameVector& teamNameVector);

	virtual const char* className() const { return("PlayoffResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

PlayoffResp::PlayoffResp(const PlayoffTeams& playoffTeams,
	TeamInfoNameVector& teamNameVector) : fPlayoffTeams(playoffTeams)
{
	fTeamNameVector = teamNameVector;
}

/******************************************************************************/

void PlayoffResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw Exception("PlayoffResp::readFromFiler: not supported");
}

/******************************************************************************/

void PlayoffResp::writeToFiler(TDataFiler& filer)
{
	fPlayoffTeams.writeToFiler(filer);

	// write team information
	fTeamNameVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

PlayoffTeams::PlayoffTeams(const TLeaguePtr& leaguePtr)
{
	fEastWinnerTeamID = leaguePtr->getEastWinnerTeamID();
	fEastWildCardTeamID = leaguePtr->getEastWildCardTeamID();

	fWestWinnerTeamID = leaguePtr->getWestWinnerTeamID();
	fWestWildCardTeamID = leaguePtr->getWestWildCardTeamID();

	fFinalistOneTeamID = leaguePtr->getFinalistOneTeamID();
	fFinalistTwoTeamID = leaguePtr->getFinalistTwoTeamID();

	fLeagueChampTeamID = leaguePtr->getLeagueChampTeamID();

	fEastWinnerScore = 0;
	fWestWildCardScore = 0;
	fWestWinnerScore = 0;
	fEastWildCardScore = 0;
	fFinalistOneScore = 0;
	fFinalistTwoScore = 0;
}

/******************************************************************************/

void PlayoffTeams::readFromFiler(TDataFiler& filer)
{
	throw Exception("PlayoffTeams::readFromFiler: not supported");
}

/******************************************************************************/

void PlayoffTeams::writeToFiler(TDataFiler& filer)
{
	// Semi-Finals Game 1
	filer.writeLong(fEastWinnerTeamID.getID());
	filer.writeByte(fEastWinnerScore);
	filer.writeLong(fWestWildCardTeamID.getID());
	filer.writeByte(fWestWildCardScore);

	// Semi-Finals Game 2
	filer.writeLong(fWestWinnerTeamID.getID());
	filer.writeByte(fWestWinnerScore);
	filer.writeLong(fEastWildCardTeamID.getID());
	filer.writeByte(fEastWildCardScore);

	// Finals Game
	filer.writeLong(fFinalistOneTeamID.getID());
	filer.writeByte(fFinalistOneScore);
	filer.writeLong(fFinalistTwoTeamID.getID());
	filer.writeByte(fFinalistTwoScore);

	filer.writeLong(fLeagueChampTeamID.getID());
}

/******************************************************************************/
/******************************************************************************/

void PlayoffRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
}

/******************************************************************************/

void PlayoffRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw Exception("PlayoffRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* PlayoffRqst::fulfillRequest()
{
	auto_ptr<PlayoffResp> pResponse;
	TeamInfoNameVector teamNameVector;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TLeaguePtr leaguePtr;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);
	leaguePtr = TLeague::createGet(teamPtr->getLeagueID(),cam_MustExist);

	teamNameVector.fillByLeagueID(teamPtr->getLeagueID());

	pResponse.reset(new PlayoffResp(PlayoffTeams(leaguePtr),teamNameVector));
	return(pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
