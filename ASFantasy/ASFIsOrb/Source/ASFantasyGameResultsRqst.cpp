/* ASFantasyGameResultsRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyDB.h"
#include "ASFantasyGameResultsRqst.h"

namespace asfantasy
{

/******************************************************************************/

class GameResultsResp : public TStreamable
{
private:
	TGameLevel fGameLevel;

	GameResultsDayVector fGameResultsDayVector;
	short fShowDay;
	GameResultsGameVector fGameResultsGameVector;
	short fShowGame;

	TScheduleDayStatus fStatus;

	TeamInfoNamePtr fVisitTeamPtr;
	short fVisitScore;
	PlayerInfoVector fVisitPlayerVector;

	TeamInfoNamePtr fHomeTeamPtr;
	short fHomeScore;
	PlayerInfoVector fHomePlayerVector;

public:
	GameResultsResp(TGameLevel gameLevel,
		GameResultsDayVector& gameResultsDayVector,short showDay,
		GameResultsGameVector& gameResultsGameVector,short showGame,
		TScheduleDayStatus status,TeamInfoNamePtr& visitTeamPtr,
		short visitScore,PlayerInfoVector& visitPlayerVector,
		TeamInfoNamePtr& homeTeamPtr,short homeScore,
		PlayerInfoVector& homePlayerVector);
	
	virtual const char* className() const { return("GameResultsResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

GameResultsDay::GameResultsDay(const TScheduleDayPtr scheduleDayPtr)
{
	char str[DATE_LEN];

	DateToString(ConvertTDateTimetoTDate(scheduleDayPtr->getGameDate()),str,
		DF_MM_DD_YYYY,FSF_NOZERO);
	fGameDate.copy(str);

	fDescrip.copyVarg("%d",(int)(scheduleDayPtr->getProfGameWeek().getID()));
}

/******************************************************************************/

void GameResultsDay::readFromFiler(TDataFiler& filer)
{
	throw ASIException("GameResultsDay::readFromFiler: not supported");
}

/******************************************************************************/

void GameResultsDay::writeToFiler(TDataFiler& filer)
{
	filer.writeString(fGameDate.c_str());
	filer.writeString(fDescrip.c_str());
}

/******************************************************************************/
/******************************************************************************/

void GameResultsDayVector::writeToFiler(TDataFiler& filer)
{
	const_iterator iter;
	GameResultsDayPtr gameResultsDayPtr;
	
	filer.writeShort((short)size());
	for(iter = begin(); iter != end(); iter++)
	{
		gameResultsDayPtr = *iter;
		gameResultsDayPtr->writeToFiler(filer);
	}
}

/******************************************************************************/

void GameResultsDayVector::fillFromScheduleDayVector(
	const TScheduleDayVector& scheduleDayVector)
{
	GameResultsDayPtr gameResultsDayPtr;
	TScheduleDayVector::const_iterator iter;

	for(iter = scheduleDayVector.begin(); iter != scheduleDayVector.end(); iter++)
	{
		gameResultsDayPtr = GameResultsDay::createFromScheduleDay(*iter);
		push_back(gameResultsDayPtr);
	}
}

/******************************************************************************/
/******************************************************************************/

GameResultsGame::GameResultsGame(const TScheduleDayGame& scheduleDayGame,
	const TTeamByIDVector& teamVector)
{
	TTeamPtr teamPtr;

	fHomeTeamID = scheduleDayGame.getHomeTeamID();

	teamPtr = teamVector.getByID(scheduleDayGame.getVisitTeamID());
	fDescrip.copy(teamPtr->getFullTeamName());
	fDescrip.concat(" at ");
	teamPtr = teamVector.getByID(scheduleDayGame.getHomeTeamID());
	fDescrip.concat(teamPtr->getFullTeamName());
}

/******************************************************************************/

void GameResultsGame::readFromFiler(TDataFiler& filer)
{
	throw ASIException("GameResultsGame::readFromFiler: not supported");
}

/******************************************************************************/

void GameResultsGame::writeToFiler(TDataFiler& filer)
{
	filer.writeLong(fHomeTeamID.getID());
	filer.writeString(fDescrip.c_str());
}

/******************************************************************************/
/******************************************************************************/

void GameResultsGameVector::writeToFiler(TDataFiler& filer)
{
	const_iterator iter;
	GameResultsGamePtr gameResultsGamePtr;
	
	filer.writeShort((short)size());
	for(iter = begin(); iter != end(); iter++)
	{
		gameResultsGamePtr = *iter;
		gameResultsGamePtr->writeToFiler(filer);
	}
}

/******************************************************************************/

void GameResultsGameVector::fillFromScheduleDay(
	const TScheduleDayPtr scheduleDayPtr,const TTeamByIDVector& teamVector)
{
	GameResultsGamePtr gameResultsGamePtr;
	const TScheduleDayGameVector& scheduleDayGameVector = 
		scheduleDayPtr->scheduleDayGameVector();
	TScheduleDayGameVector::const_iterator iter;

	for(iter = scheduleDayGameVector.begin();
		iter != scheduleDayGameVector.end(); iter++)
	{
		gameResultsGamePtr = GameResultsGame::createFromScheduleDayGame(
			*iter,teamVector);
		push_back(gameResultsGamePtr);
	}
}

/******************************************************************************/
/******************************************************************************/

GameResultsResp::GameResultsResp(TGameLevel gameLevel,
	GameResultsDayVector& gameResultsDayVector,short showDay,
	GameResultsGameVector& gameResultsGameVector,short showGame,
	TScheduleDayStatus status,TeamInfoNamePtr& visitTeamPtr,short visitScore,
	PlayerInfoVector& visitPlayerVector,TeamInfoNamePtr& homeTeamPtr,
	short homeScore,PlayerInfoVector& homePlayerVector)
{
	fGameLevel = gameLevel;

	fGameResultsDayVector = gameResultsDayVector;
	fShowDay = showDay;
	fGameResultsGameVector = gameResultsGameVector;
	fShowGame = showGame;

	fStatus = status;

	fVisitTeamPtr = visitTeamPtr;
	fVisitScore = visitScore;
	fVisitPlayerVector = visitPlayerVector;

	fHomeTeamPtr = homeTeamPtr;
	fHomeScore = homeScore;
	fHomePlayerVector = homePlayerVector;
}

/******************************************************************************/

void GameResultsResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("GameResultsResp::readFromFiler: not supported");
}

/******************************************************************************/

void GameResultsResp::writeToFiler(TDataFiler& filer)
{
	filer.writeByte((byte)fGameLevel);

	fGameResultsDayVector.writeToFiler(filer);
	filer.writeShort(fShowDay);
	fGameResultsGameVector.writeToFiler(filer);
	filer.writeShort(fShowGame);

	filer.writeByte(fStatus);

	// write visit team information
	fVisitTeamPtr->writeToFiler(filer);
	filer.writeShort(fVisitScore);
	fVisitPlayerVector.writeToFiler(filer);

	// write home team information
	fHomeTeamPtr->writeToFiler(filer);
	filer.writeShort(fHomeScore);
	fHomePlayerVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/
/*

GameResultsPlayer::GameResultsPlayer(const TProfPlayerPtr profPlayerPtr)
{
	clear();

	fName = profPlayerPtr->getName();
	fPosition = profPlayerPtr->getPosition();
}

*/
/******************************************************************************/
	
void GameResultsPlayer::readFromFiler(TDataFiler& filer)
{
	throw ASIException("GameResultsPlayer::readFromFiler: not supported");
}

/******************************************************************************/

void GameResultsPlayer::writeToFiler(TDataFiler& filer)
{
	PlayerInfo::writeToFiler(filer);
	
	filer.writeShort(fTotalPoints);
}

/******************************************************************************/
/******************************************************************************/

void GameResultsRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fGameDate = filer.readString().c_str();
	fHomeTeamID = filer.readLong();
}

/******************************************************************************/

void GameResultsRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("GameResultsRqst::writeToFiler: not supported");
}

/******************************************************************************/
	
TStreamable* GameResultsRqst::fulfillRequest()
{
	auto_ptr<GameResultsResp> pResponse;

	tag::TDate tempDate;
	TDateTime gameDate;

	TTeamByIDVector teamVector;
	TScheduleDayVector scheduleDayVector;

	short showDay;
	GameResultsDayVector gameResultsDayVector;

	short showGame;
	GameResultsGameVector gameResultsGameVector;

	TScheduleDayStatus status;

	TeamInfoNamePtr visitTeamPtr;
	short visitScore;
	PlayerInfoVector visitPlayerVector;
	
	TeamInfoNamePtr homeTeamPtr;
	short homeScore;
	PlayerInfoVector homePlayerVector;
	
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TScheduleDayPtr scheduleDayPtr;
	TScheduleDayGame scheduleDayGame;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(), cam_MustExist);

	//TOOLDEBUG( tErrorMsg("GameResultsRqst::fulfillRequest: requesting GameDate(%s), HomeTeamID(%s)",
	//	fGameDate.c_str(),fHomeTeamID.c_str()); );
		
	if(fGameDate.hasLen())
	{
		if(!StringToDate(fGameDate,DF_MM_DD_YYYY,&tempDate))
			throw ASIException("GameResultsRqst::fulfillRequest: bad gameDate");
		gameDate = ConvertTDatetoTDateTime(tempDate);
	}

	LoadTeamVectorByLeagueID(teamPtr->getLeagueID(),teamVector);
	teamVector.sort();

	LoadScheduleDayVectorByLeagueID(teamPtr->getLeagueID(),scheduleDayVector);
	scheduleDayVector.sortByGameDate();
	if(scheduleDayVector.size() == 0)
		throw ASIException("GameResultsRqst::fulfillRequest: no schedule found");

	gameResultsDayVector.fillFromScheduleDayVector(scheduleDayVector);

	// Fetch Schedule Day
	if((gameDate == TDateTime()) || (particPtr->getGameLevel() == gml_Standard))
	{
		showDay = determineBestScheduleDayPosition(scheduleDayVector);
	}
	else
	{
		showDay = scheduleDayVector.getGameDatePosition(gameDate);
	}
	if(showDay == -1)
		showDay = 0;
	scheduleDayPtr = scheduleDayVector[showDay];
	gameResultsGameVector.fillFromScheduleDay(scheduleDayPtr,teamVector);

	// Fetch Schedule Day Game
	if(fHomeTeamID.isUndefined() || (particPtr->getGameLevel() == gml_Standard))
	{
		showGame = scheduleDayPtr->getScheduleDayGamePositionByTeamID(teamPtr->getTeamID());

		// For premium teams, show first game if their team did not play.
		if((showGame == -1) &&
				(scheduleDayPtr->scheduleDayGameVector().size() > 0) &&
				(particPtr->getGameLevel() == gml_Premium))
			showGame = 0;
	}
	else
	{
		showGame = scheduleDayPtr->getScheduleDayGamePositionByTeamID(fHomeTeamID);
	}

	/**************************************************************************/

	status = scheduleDayPtr->getStatus();

	if((status == sdst_InProgress) || (status == sdst_Completed))
	{
		if(showGame == -1)
			throw ASIException("GameResultsRqst::fulfillRequest: no game found for in progress/completed schedule");

		scheduleDayGame = scheduleDayPtr->scheduleDayGameVector()[showGame];

		visitTeamPtr = TeamInfoName::createFromTeamPtr(
			teamVector.getByID(scheduleDayGame.getVisitTeamID()));
		visitScore = scheduleDayGame.getVisitScore();
		fillGameResultsPlayerVector(scheduleDayGame.getVisitTeamID(),
			scheduleDayPtr->getGameDate(),visitPlayerVector);
			
		homeTeamPtr = TeamInfoName::createFromTeamPtr(
			teamVector.getByID(scheduleDayGame.getHomeTeamID()));
		homeScore = scheduleDayGame.getHomeScore();
		fillGameResultsPlayerVector(scheduleDayGame.getHomeTeamID(),
			scheduleDayPtr->getGameDate(),homePlayerVector);
	}
	else
	{
		visitTeamPtr = TeamInfoName::createFromTeamPtr(TTeam::newInstance());
		visitScore = 0;
		homeTeamPtr = TeamInfoName::createFromTeamPtr(TTeam::newInstance());
		homeScore = 0;
	}

	pResponse.reset(new GameResultsResp(particPtr->getGameLevel(),
		gameResultsDayVector,showDay,gameResultsGameVector,showGame,status,
		visitTeamPtr,visitScore,visitPlayerVector,homeTeamPtr,homeScore,
		homePlayerVector));
	return (pResponse.release());
}

/******************************************************************************/

// Determines best scheduleDay to show when none was specified.
// Assumes vector is sorted by GameDate.

int GameResultsRqst::determineBestScheduleDayPosition(
	const TScheduleDayVector& scheduleDayVector)
{
	int lastNotStartedPos = -1;
	int i;

	for(i = scheduleDayVector.size() - 1; i >= 0; --i)
	{
		if((scheduleDayVector[i]->getStatus() == sdst_InProgress) ||
				(scheduleDayVector[i]->getStatus() == sdst_Completed))
			return(i);
		else if(scheduleDayVector[i]->getStatus() == sdst_NotStarted)
			lastNotStartedPos = i;
	}

	return(lastNotStartedPos);
}

/******************************************************************************/

void GameResultsRqst::fillGameResultsPlayerVector(TTeamID teamID,
	TDateTime gameDate,PlayerInfoVector& playerVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TGameResultPtr gameResultPtr = TGameResult::createGet(
		TTeamDateID(teamID,gameDate),cam_MustExist);
	TPlayerDatesVector::const_iterator iter;

	TProfPlayerPtr profPlayerPtr;
	GameResultsPlayerPtr gameResultsPlayerPtr;

	// Load Off Players
	const TPlayerDatesVector& offPlayerDatesVector =
		gameResultPtr->offPlayerDatesConstVector();
		
	for (iter = offPlayerDatesVector.begin(); iter != offPlayerDatesVector.end();
		++iter)
	{
		const TPlayerDates& playerDates = *iter;
		
		profPlayerPtr = store.getProfPlayer(playerDates.fPlayerID);
		gameResultsPlayerPtr = GameResultsPlayer::createFromProfPlayer(
			profPlayerPtr,playerDates.fPoints);
		playerVector.push_back(gameResultsPlayerPtr);
	}

	// Load Def Players
	const TPlayerDatesVector& defPlayerDatesVector =
		gameResultPtr->defPlayerDatesConstVector();

	for (iter = defPlayerDatesVector.begin(); iter != defPlayerDatesVector.end();
		++iter)
	{
		const TPlayerDates& playerDates = *iter;
		
		profPlayerPtr = store.getProfPlayer(playerDates.fPlayerID);
		gameResultsPlayerPtr = GameResultsPlayer::createFromProfPlayer(
			profPlayerPtr,playerDates.fPoints);
		playerVector.push_back(gameResultsPlayerPtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
