/* ASFantasyStandingsRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyMiscRqst.h"
#include "ASFantasyStandingsRqst.h"

namespace asfantasy
{

/******************************************************************************/

class StandingsResp : public TStreamable
{
private:
	TeamInfoNameVector	fEastTeamInfoNameVector;
	TeamInfoNameVector	fWestTeamInfoNameVector;

public:
	StandingsResp(TeamInfoNameVector& eastTeamInfoNameVector,
		TeamInfoNameVector& westTeamInfoNameVector);

	virtual const char* className() const { return("StandingsResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

StandingsResp::StandingsResp(TeamInfoNameVector& eastTeamInfoNameVector,
	TeamInfoNameVector& westTeamInfoNameVector)
{
	fEastTeamInfoNameVector = eastTeamInfoNameVector;
	fWestTeamInfoNameVector = westTeamInfoNameVector;
}

/******************************************************************************/

void StandingsResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("StandingsResp::readFromFiler: not supported");
}

/******************************************************************************/

void StandingsResp::writeToFiler(TDataFiler& filer)
{
	fEastTeamInfoNameVector.writeToFiler(filer);
	fWestTeamInfoNameVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

StandingsTeam::StandingsTeam(const TTeamPtr& teamPtr) : TeamInfoName(teamPtr)
{
	double winPercent;

	fWins = teamPtr->getWins();
	fLoses = teamPtr->getLoses();
	fTies = teamPtr->getTies();
	fDivWins = teamPtr->getDivWins();
	fDivLoses = teamPtr->getDivLoses();
	fDivTies = teamPtr->getDivTies();
	fStreak = teamPtr->getStreak();

	winPercent = teamPtr->winningPercentage();
	if(winPercent < 1.0)
		fWinPercent.CopyVarg(".%03.0lf",winPercent * 1000.0);
	else
		fWinPercent.Copy("1.000");
		
	fTotalPoints = teamPtr->getTotalPoints();
}

/******************************************************************************/

void StandingsTeam::readFromFiler(TDataFiler& filer)
{
	throw ASIException("StandingsTeam::readFromFiler: not supported");
}

/******************************************************************************/

void StandingsTeam::writeToFiler(TDataFiler& filer)
{
	// write parent data first
	TeamInfoName::writeToFiler(filer);

	// write our data
	filer.writeShort(fWins);
	filer.writeShort(fLoses);
	filer.writeShort(fTies);
	filer.writeShort(fDivWins);
	filer.writeShort(fDivLoses);
	filer.writeShort(fDivTies);
	filer.writeShort(fStreak);
	filer.writeString(fWinPercent.c_str());
	filer.writeShort(fTotalPoints);
}

/******************************************************************************/
/******************************************************************************/

void StandingsRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
}

/******************************************************************************/

void StandingsRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("StandingsRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* StandingsRqst::fulfillRequest()
{
	auto_ptr<StandingsResp> pResponse;
	TeamInfoNameVector eastTeamInfoNameVector;
	TeamInfoNameVector westTeamInfoNameVector;
	TParticPtr particPtr;
	TTeamPtr teamPtr;

	validateRequest(particPtr,teamPtr);
	fillTeamInfoNameVector(particPtr,teamPtr,eastTeamInfoNameVector,
		westTeamInfoNameVector);

	pResponse.reset(new StandingsResp(eastTeamInfoNameVector,
		westTeamInfoNameVector));
	return(pResponse.release());
}

/******************************************************************************/

void StandingsRqst::validateRequest(TParticPtr& particPtr,TTeamPtr& teamPtr)
{
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);
}

/******************************************************************************/

void StandingsRqst::fillTeamInfoNameVector(TParticPtr& particPtr,TTeamPtr& teamPtr,
	TeamInfoNameVector& eastTeamInfoNameVector,
	TeamInfoNameVector& westTeamInfoNameVector)
{
	TLeaguePtr		leaguePtr;
	TTeamIDVector	eastDivStandings;
	TTeamIDVector	westDivStandings;
	TTeamVector		leagueTeamVector;
	TTeamVector		eastTeamVector;
	TTeamVector		westTeamVector;

	// get league info
	leaguePtr = TLeague::createGet(teamPtr->getLeagueID(),cam_MustExist);

	// get standings by division
	eastDivStandings = leaguePtr->eastDivStandings();
	westDivStandings = leaguePtr->westDivStandings();

	// convert standings into list of teams
	LoadTeamVectorByLeagueID(teamPtr->getLeagueID(),leagueTeamVector);
	eastTeamVector.fillFromTeamIDVector(eastDivStandings,leagueTeamVector);
	westTeamVector.fillFromTeamIDVector(westDivStandings,leagueTeamVector);

	// load data into standings vector
	fillDivisionTeamInfoNameVector(eastTeamVector,eastTeamInfoNameVector);
	fillDivisionTeamInfoNameVector(westTeamVector,westTeamInfoNameVector);
}

/******************************************************************************/

// This is the same as TeamInfoNameVector::fillFromTeamVector() except that
// it creates instances of StandingsTeam instead of TeamInfoName.
void StandingsRqst::fillDivisionTeamInfoNameVector(TTeamVector& teamVector,
	TeamInfoNameVector& teamInfoNameVector)
{
	StandingsTeamPtr			standingsTeamPtr;
	TTeamVector::const_iterator iter;

	teamInfoNameVector.erase(teamInfoNameVector.begin(),teamInfoNameVector.end());
	for(iter=teamVector.begin(); iter!=teamVector.end(); iter++)
	{
		standingsTeamPtr = StandingsTeam::createFromTeamPtr(*iter);
		teamInfoNameVector.push_back(standingsTeamPtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
