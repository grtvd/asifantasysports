/* ASFantasyScheduleRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyMiscRqst.h"
#include "ASFantasyScheduleRqst.h"

namespace asfantasy
{

/******************************************************************************/

class ScheduleResp : public TStreamable
{
private:
	ASFantasyScheduleDayGameVector fGameVector;
	TeamInfoNameVector fTeamNameVector;

public:
	ScheduleResp(ASFantasyScheduleDayGameVector& gameVector,
		TeamInfoNameVector& teamNameVector);

	virtual const char* className() const { return("ScheduleResp"); }
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

ScheduleResp::ScheduleResp(
	ASFantasyScheduleDayGameVector& gameVector,
	TeamInfoNameVector& teamNameVector)
{
	fGameVector = gameVector;
	fTeamNameVector = teamNameVector;
}

/******************************************************************************/

void ScheduleResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ScheduleResp::readFromFiler: not supported");
}

/******************************************************************************/

void ScheduleResp::writeToFiler(TDataFiler& filer)
{
	ASFantasyScheduleDayGamePtr gamePtr;
	int i, numItems;

	// write player information
	numItems = fGameVector.size();
	filer.writeShort((short)numItems);
	for (i=0; i<numItems; i++)
	{
		gamePtr = fGameVector[i];
		gamePtr->writeToFiler(filer);
	}

	// write team information
	fTeamNameVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

ASFantasyScheduleDayGame::ASFantasyScheduleDayGame(TTeamID teamID,
	const TScheduleDayPtr scheduleDayPtr)
{
	TScheduleDayGame scheduleDayGame;
	
	clear();

	fProfGameWeek = scheduleDayPtr->getProfGameWeek();

	if(scheduleDayPtr->getScheduleDayGameByTeamID(teamID,scheduleDayGame))
	{
		fGameIsScheduled = true;

		if(scheduleDayGame.getHomeTeamID() == teamID)
		{
			fOppTeamID = scheduleDayGame.getVisitTeamID();
			fIsHome = true;
		}
		else
			fOppTeamID = scheduleDayGame.getHomeTeamID();

		if(scheduleDayGame.wasGamePlayed())
		{
			if(!scheduleDayGame.wasGameTied())
			{
				fDidWin = (scheduleDayGame.getWinningTeamID() == teamID);
				fWinningScore = scheduleDayGame.getWinningScore();
				fLosingScore = scheduleDayGame.getLosingScore();
			}
			else
			{
				fDidWin = false;
				fWinningScore = fLosingScore = scheduleDayGame.getHomeScore();
			}
		}
	}
}

/******************************************************************************/

void ASFantasyScheduleDayGame::readFromFiler(TDataFiler& filer)
{
	throw ASIException("ASFantasyScheduleDayGame::readFromFiler: not supported");
}

/******************************************************************************/

void ASFantasyScheduleDayGame::writeToFiler(TDataFiler& filer)
{
	filer.writeByte((byte)fProfGameWeek.getID());
	filer.writeBoolean(fGameIsScheduled);
	filer.writeBoolean(fIsHome);
	filer.writeBoolean(fDidWin);
	filer.writeLong(fOppTeamID.getID());
	filer.writeShort(fWinningScore);
	filer.writeShort(fLosingScore);
}

/******************************************************************************/
/******************************************************************************/

void ScheduleRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
}

/******************************************************************************/

void ScheduleRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("ScheduleRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* ScheduleRqst::fulfillRequest()
{
	auto_ptr<ScheduleResp> pResponse;
	ASFantasyScheduleDayGameVector gameVector;
	TeamInfoNameVector teamNameVector;
	TParticPtr particPtr;
	TTeamPtr teamPtr;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(),cam_MustExist);
	
	fillGameVector(teamPtr,gameVector);
	teamNameVector.fillByLeagueID(teamPtr->getLeagueID());

	pResponse.reset(new ScheduleResp(gameVector,teamNameVector));
	return(pResponse.release());
}

/******************************************************************************/

void ScheduleRqst::fillGameVector(const TTeamPtr teamPtr,
	ASFantasyScheduleDayGameVector& gameVector)
{
	TScheduleDayVector scheduleDayVector;
	TScheduleDayVector::const_iterator iter;
	
	LoadScheduleDayVectorByLeagueID(teamPtr->getLeagueID(),scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	for(iter = scheduleDayVector.begin(); iter != scheduleDayVector.end(); iter++)
	{
		const TScheduleDayPtr& scheduleDayPtr = *iter;
		
		ASFantasyScheduleDayGamePtr gamePtr =
			ASFantasyScheduleDayGame::createFromScheduleDayGame(
			teamPtr->getTeamID(),scheduleDayPtr);
			
		gameVector.push_back(gamePtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
