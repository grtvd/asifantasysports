/* ASHockeyType.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommDB.h"

#include "ASHockeyType.h"
#include "ASHockeyObjectBuilder.h"

namespace ashockey
{

// Template code is not being include.
TPositionVector gUnusedPositionVector;

/******************************************************************************/
/******************************************************************************/

THockeyPosition::THockeyPosition(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "W")
		fT = pos_Winger;
	else if(value == "C")
		fT = pos_Center;
	else if(value == "D")
		fT = pos_Defenseman;
	else if(value == "G")
		fT = pos_Goalie;

	// Non-Participating Player Positions
	
	else
		throw ASIException("THockeyPosition::THockeyPosition: invalid "
			"str(%s)",str);
}

/******************************************************************************/

const char* THockeyPosition::c_str() const
{
	switch(fT)
	{
		case pos_Winger:
			return("W");
		case pos_Center:
			return("C");
		case pos_Defenseman:
			return("D");
		case pos_Goalie:
			return("G");
			
		// Non-Participating Player Positions

		default:
			break;
	};

	throw ASIException("THockeyPosition::c_str: invalid fT");
}

/******************************************************************************/

bool THockeyPosition::isKey() const
{
	if(isUndefined())
		throw ASIException("THockeyPosition::isKey: invalid fT(%d)",(int)fT);

	return(fT <= pos_LastKeyPos);
}

/******************************************************************************/

bool THockeyPosition::isOffensive() const
{
	if(isUndefined() || !isKey())
		throw ASIException("THockeyPosition::isOffensive: invalid fT(%d)",(int)fT);

	return(fT != pos_Goalie);
}

/******************************************************************************/

void asfantasy::loadKeyPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = ashockey::pos_Winger; i <= ashockey::pos_LastKeyPos; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadAllPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = ashockey::pos_Winger; i <= ashockey::pos_Last; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadDefaultLineupPositionVector(const TLineup lineup,
	TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	if(lineup == ashockey::lut_Skater)
	{
		posVector.push_back(ashockey::pos_Winger);
		posVector.push_back(ashockey::pos_Winger);
		posVector.push_back(ashockey::pos_Winger);
		posVector.push_back(ashockey::pos_Winger);
		posVector.push_back(ashockey::pos_Center);
		posVector.push_back(ashockey::pos_Center);
		posVector.push_back(ashockey::pos_Defenseman);
		posVector.push_back(ashockey::pos_Defenseman);
		posVector.push_back(ashockey::pos_Defenseman);
		posVector.push_back(ashockey::pos_Defenseman);
	}
	else if(lineup == ashockey::lut_Goalie)
	{
		posVector.push_back(ashockey::pos_Goalie);
	}
}

/******************************************************************************/

CStrVar asfantasy::convertPositionToString(int position)
{
	ashockey::THockeyPosition hockeyPosition(position);

	return(hockeyPosition.c_str());
}

/******************************************************************************/
/******************************************************************************/

TRosterStatus::TRosterStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "A")
		fT = rst_Active;
	else if(value == "D")
		fT = rst_Disabled;
	else if(value == "I")
		fT = rst_Inactive;
	else
		throw ASIException("TRosterStatus::TRosterStatus: invalid str(%s)",str);
}

/******************************************************************************/

const char* TRosterStatus::c_str() const
{
	switch(fT)
	{
		case rst_Active:
			return("A");
		case rst_Disabled:
			return("D");
		case rst_Inactive:
			return("I");
		default:
			break;
	};

	throw ASIException("TRosterStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

void THockeyTeam::clear()
{
	TTeam::clear();
	
	fSkaterLineup.erase(fSkaterLineup.begin(),fSkaterLineup.end());
	fGoalieLineup.erase(fGoalieLineup.begin(),fGoalieLineup.end());
}

/******************************************************************************/

const TPlayerIDVector& THockeyTeam::lineupConst(TLineup lineup) const
{
	if(lineup == lut_Skater)
		return(fSkaterLineup);

	if(lineup == lut_Goalie)
		return(fGoalieLineup);

	throw ASIException("THockeyTeam::lineupConst: invalid lineup");
}

/******************************************************************************/

TPlayerIDVector& THockeyTeam::lineup(TLineup lineup)
{
	setHasChanged();

	if(lineup == lut_Skater)
		return(fSkaterLineup);

	if(lineup == lut_Goalie)
		return(fGoalieLineup);

	throw ASIException("THockeyTeam::lineup: invalid lineup");
}

/******************************************************************************/

void THockeyTeam::readFromDataSet(TDataSet& dataSet)
{
	TTeam::readFromDataSet(dataSet);

	readLineupFromDataSet(dataSet,lut_Skater,"Skater");
	readLineupFromDataSet(dataSet,lut_Goalie,"Goalie");
}

/******************************************************************************/

void THockeyTeam::writeToDataSet(TDataSet& dataSet)
{
	TTeam::writeToDataSet(dataSet);

	writeLineupToDataSet(dataSet,lut_Skater,"Skater");
	writeLineupToDataSet(dataSet,lut_Goalie,"Goalie");
}

/******************************************************************************/
/******************************************************************************/

void THockeyProfPlayer::clear()
{
	TProfPlayer::clear();

	fPosition.clear();

	fRosterStatus.clear();
}

/******************************************************************************/

void THockeyProfPlayer::readFromDataSet(TDataSet& dataSet)
{
	TProfPlayer::readFromDataSet(dataSet);

	fPosition = dataSet.FieldByName("Pos")->AsString.c_str();

	fRosterStatus = dataSet.FieldByName("RosterStatus")->AsString.c_str();
}

/******************************************************************************/

void THockeyProfPlayer::writeToDataSet(TDataSet& dataSet)
{
	TProfPlayer::writeToDataSet(dataSet);

	dataSet.FieldByName("Pos")->AsString = fPosition.c_str();

	dataSet.FieldByName("RosterStatus")->AsString = fRosterStatus.c_str();
}

/******************************************************************************/

void THockeyProfPlayer::validateForUpdate()
{
	TProfPlayer::validateForUpdate();

	if(fPosition.isUndefined())
		throw ASIException("THockeyProfPlayer::validateForUpdate: fPosition.isUndefined()");

	if(fRosterStatus.isUndefined())
		throw ASIException("THockeyProfPlayer::validateForUpdate: fRosterStatus.isUndefined()");
}

/******************************************************************************/
/******************************************************************************/

void TOffGameStatDetail::clear()
{
	fGamesPlayed = 0;
	fGoals = 0;
	fAssists = 0;
	fPoints = 0;
	fShots = 0;
	fPlusMinus = 0;

	fPowerPlayGoals = 0;
	fPowerPlayAssists = 0;
	fShortHandedGoals = 0;
	fShortHandedAssists = 0;
	fGameWinningGoals = 0;
	fGameTyingGoals = 0;
	fEmptyNetGoals = 0;
	fOvertimeGoals = 0;

	fMajorPenalties = 0;
	fMinorPenalties = 0;
	fPenaltyMinutes = 0;
	fHatTricks = 0;
	fFights = 0;
}

/******************************************************************************/

short TOffGameStatDetail::calcTotalPoints() const
{
	short totalPoints = 0;

	totalPoints += cast2short(fGoals * 15);
	totalPoints += cast2short(fAssists * 15);
	totalPoints += cast2short(fPenaltyMinutes * 2);
	totalPoints += cast2short(fShots * 1);
	totalPoints += cast2short(fPlusMinus * 10);

	totalPoints += cast2short(fPowerPlayGoals * 15);
	totalPoints += cast2short(fPowerPlayAssists * 15);
	totalPoints += cast2short(fShortHandedGoals * 15);
	totalPoints += cast2short(fShortHandedAssists * 15);
	totalPoints += cast2short(fGameWinningGoals * 15);
	totalPoints += cast2short(fGameTyingGoals * 15);
	totalPoints += cast2short(fOvertimeGoals * 15);

	totalPoints += cast2short(fHatTricks * 45);
	
	return(totalPoints);
}

/******************************************************************************/

double TOffGameStatDetail::getStat(int playerStatType)
{
	THockeyPlayerStatType hockeyPlayerStatType(playerStatType);
	
	switch(hockeyPlayerStatType)
	{
		case pst_GamesPlayed:
			return(fGamesPlayed);
		case pst_Goals:
			return(fGoals);
		case pst_Assists:
			return(fAssists);
		case pst_PenaltyMinutes:
			return(fPenaltyMinutes);
		case pst_Shots:
			return(fShots);
		case pst_PlusMinus:
			return(fPlusMinus);

		case pst_PowerPlayGoals:
			return(fPowerPlayGoals);
		case pst_PowerPlayAssists:
			return(fPowerPlayAssists);
		case pst_ShortHandedGoals:
			return(fShortHandedGoals);
		case pst_ShortHandedAssists:
			return(fShortHandedAssists);
		case pst_GameWinningGoals:
			return(fGameWinningGoals);
		case pst_GameTyingGoals:
			return(fGameTyingGoals);
		case pst_OvertimeGoals:
			return(fOvertimeGoals);

		case pst_HatTricks:
			return(fOvertimeGoals);

		default:
			break;
	}

	throw ASIException("TOffGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TOffGameStatDetail::sumStats(const TOffGameStatDetail& offGameStatDetail)
{
	fGamesPlayed += offGameStatDetail.fGamesPlayed;
	fGoals += offGameStatDetail.fGoals;
	fAssists += offGameStatDetail.fAssists;
	fPoints += offGameStatDetail.fPoints;
	fShots += offGameStatDetail.fShots;
	fPlusMinus += offGameStatDetail.fPlusMinus;

	fPowerPlayGoals += offGameStatDetail.fPowerPlayGoals;
	fPowerPlayAssists += offGameStatDetail.fPowerPlayAssists;
	fShortHandedGoals += offGameStatDetail.fShortHandedGoals;
	fShortHandedAssists += offGameStatDetail.fShortHandedAssists;
	fGameWinningGoals += offGameStatDetail.fGameWinningGoals;
	fGameTyingGoals += offGameStatDetail.fGameTyingGoals;
	fEmptyNetGoals += offGameStatDetail.fEmptyNetGoals;
	fOvertimeGoals += offGameStatDetail.fOvertimeGoals;

	fMajorPenalties += offGameStatDetail.fMajorPenalties;
	fMinorPenalties += offGameStatDetail.fMinorPenalties;
	fPenaltyMinutes += offGameStatDetail.fPenaltyMinutes;
	fHatTricks += offGameStatDetail.fHatTricks;
	fFights += offGameStatDetail.fFights;
}

/******************************************************************************/
/******************************************************************************/

void TDefGameStatDetail::clear()
{
	fGamesPlayed = 0;
	fGamesStarted = 0;
	fMinutesPlayed = 0;

	fWins = 0;
	fLosses = 0;
	fTies = 0;

	fGoalsAgainst = 0;
	fEmptyNetGoalsAgainst = 0;
	fShotsAgainst = 0;
	fSaves = 0;
	fShutouts = 0;

	fMajorPenalties = 0;
	fPenaltyMinutes = 0;
	fFights = 0;
}

/******************************************************************************/

short TDefGameStatDetail::calcTotalPoints() const
{
	short totalPoints = 0;

	totalPoints += cast2short(fWins * 40);
	totalPoints -= cast2short(fLosses * 40);
	totalPoints += cast2short(fTies * 20);

	totalPoints -= cast2short(fGoalsAgainst * 15);
	totalPoints += cast2short(fSaves * 2);
	totalPoints += cast2short(fShutouts * 120);

	return(totalPoints);
}

/******************************************************************************/

double TDefGameStatDetail::getStat(int playerStatType)
{
	THockeyPlayerStatType hockeyPlayerStatType(playerStatType);

	switch(hockeyPlayerStatType)
	{
		case pst_GamesPlayed:
			return(fGamesPlayed);
		case pst_GamesStarted:
			return(fGamesStarted);

		case pst_Wins:
			return(fWins);
		case pst_Losses:
			return(fLosses);
		case pst_Ties:
			return(fTies);

		case pst_GoalsAgainst:
			return(fGoalsAgainst);
		case pst_Saves:
			return(fSaves);
		case pst_Shutouts:
			return(fShutouts);

		default:
			break;
	}

	throw ASIException("TDefGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TDefGameStatDetail::sumStats(const TDefGameStatDetail& defGameStatDetail)
{
	fGamesPlayed += defGameStatDetail.fGamesPlayed;
	fGamesStarted += defGameStatDetail.fGamesStarted;
	fMinutesPlayed += defGameStatDetail.fMinutesPlayed;

	fWins += defGameStatDetail.fWins;
	fLosses += defGameStatDetail.fLosses;
	fTies += defGameStatDetail.fTies;

	fGoalsAgainst += defGameStatDetail.fGoalsAgainst;
	fEmptyNetGoalsAgainst += defGameStatDetail.fEmptyNetGoalsAgainst;
	fShotsAgainst += defGameStatDetail.fShotsAgainst;
	fSaves += defGameStatDetail.fSaves;
	fShutouts += defGameStatDetail.fShutouts;

	fMajorPenalties += defGameStatDetail.fMajorPenalties;
	fPenaltyMinutes += defGameStatDetail.fPenaltyMinutes;
	fFights += defGameStatDetail.fFights;
}

/******************************************************************************/
/******************************************************************************/

void THockeyOffGameStat::clear()
{
	TOffGameStat::clear();

	fOffGameStatDetail.clear();
}

/******************************************************************************/

double THockeyOffGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);

	return(fOffGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 THockeyOffGameStat::getDefaultStatStr(int playerStatType)
{
	return("0000");
}

/******************************************************************************/

CStr31 THockeyOffGameStat::getStatStr(int playerStatType)
{
	CStr31 str;
	double stat = getStat(playerStatType);

	if(stat < 0)
		str.CopyVarg("-%03.lf",stat * -1.0);
	else
		str.CopyVarg("%04.lf",stat);

	return(str);
}

/******************************************************************************/

void THockeyOffGameStat::sumStats(const TOffGameStatPtr offGameStatPtr)
{
	fTotalPoints +=
		THockeyOffGameStatPtr(offGameStatPtr)->getTotalPoints();

	fOffGameStatDetail.sumStats(
		THockeyOffGameStatPtr(offGameStatPtr)->offGameStatDetail());
}

/******************************************************************************/

void THockeyOffGameStat::readFromDataSet(TDataSet& dataSet)
{
	TOffGameStat::readFromDataSet(dataSet);
	
	fOffGameStatDetail.fGamesPlayed =
		(short)dataSet.FieldByName("GamesPlayed")->AsInteger;
	fOffGameStatDetail.fGoals = (short)dataSet.FieldByName("Goals")->AsInteger;
	fOffGameStatDetail.fAssists =
		(short)dataSet.FieldByName("Assists")->AsInteger;
	fOffGameStatDetail.fPoints =
		(short)dataSet.FieldByName("Points")->AsInteger;
	fOffGameStatDetail.fShots = (short)dataSet.FieldByName("Shots")->AsInteger;
	fOffGameStatDetail.fPlusMinus =
		(short)dataSet.FieldByName("PlusMinus")->AsInteger;

	fOffGameStatDetail.fPowerPlayGoals =
		(short)dataSet.FieldByName("PowerPlayGoals")->AsInteger;
	fOffGameStatDetail.fPowerPlayAssists =
		(short)dataSet.FieldByName("PowerPlayAssists")->AsInteger;
	fOffGameStatDetail.fShortHandedGoals =
		(short)dataSet.FieldByName("ShortHandedGoals")->AsInteger;
	fOffGameStatDetail.fShortHandedAssists =
		(short)dataSet.FieldByName("ShortHandedAssists")->AsInteger;
	fOffGameStatDetail.fGameWinningGoals =
		(short)dataSet.FieldByName("GameWinningGoals")->AsInteger;
	fOffGameStatDetail.fGameTyingGoals =
		(short)dataSet.FieldByName("GameTyingGoals")->AsInteger;
	fOffGameStatDetail.fEmptyNetGoals =
		(short)dataSet.FieldByName("EmptyNetGoals")->AsInteger;
	fOffGameStatDetail.fOvertimeGoals =
		(short)dataSet.FieldByName("OvertimeGoals")->AsInteger;

	fOffGameStatDetail.fMajorPenalties =
		(short)dataSet.FieldByName("MajorPenalties")->AsInteger;
	fOffGameStatDetail.fMinorPenalties =
		(short)dataSet.FieldByName("MinorPenalties")->AsInteger;
	fOffGameStatDetail.fPenaltyMinutes =
		(short)dataSet.FieldByName("PenaltyMinutes")->AsInteger;
	fOffGameStatDetail.fHatTricks =
		(short)dataSet.FieldByName("HatTricks")->AsInteger;
	fOffGameStatDetail.fFights =
		(short)dataSet.FieldByName("Fights")->AsInteger;
}

/******************************************************************************/

void THockeyOffGameStat::writeToDataSet(TDataSet& dataSet)
{
	TOffGameStat::writeToDataSet(dataSet);

	dataSet.FieldByName("GamesPlayed")->AsInteger =
		fOffGameStatDetail.fGamesPlayed;
	dataSet.FieldByName("Goals")->AsInteger = fOffGameStatDetail.fGoals;
	dataSet.FieldByName("Assists")->AsInteger = fOffGameStatDetail.fAssists;
	dataSet.FieldByName("Points")->AsInteger = fOffGameStatDetail.fPoints;
	dataSet.FieldByName("Shots")->AsInteger = fOffGameStatDetail.fShots;
	dataSet.FieldByName("PlusMinus")->AsInteger = fOffGameStatDetail.fPlusMinus;

	dataSet.FieldByName("PowerPlayGoals")->AsInteger =
		fOffGameStatDetail.fPowerPlayGoals;
	dataSet.FieldByName("PowerPlayAssists")->AsInteger =
		fOffGameStatDetail.fPowerPlayAssists;
	dataSet.FieldByName("ShortHandedGoals")->AsInteger =
		fOffGameStatDetail.fShortHandedGoals;
	dataSet.FieldByName("ShortHandedAssists")->AsInteger =
		fOffGameStatDetail.fShortHandedAssists;
	dataSet.FieldByName("GameWinningGoals")->AsInteger =
		fOffGameStatDetail.fGameWinningGoals;
	dataSet.FieldByName("GameTyingGoals")->AsInteger =
		fOffGameStatDetail.fGameTyingGoals;
	dataSet.FieldByName("EmptyNetGoals")->AsInteger =
		fOffGameStatDetail.fEmptyNetGoals;
	dataSet.FieldByName("OvertimeGoals")->AsInteger =
		fOffGameStatDetail.fOvertimeGoals;

	dataSet.FieldByName("MajorPenalties")->AsInteger =
		fOffGameStatDetail.fMajorPenalties;
	dataSet.FieldByName("MinorPenalties")->AsInteger =
		fOffGameStatDetail.fMinorPenalties;
	dataSet.FieldByName("PenaltyMinutes")->AsInteger =
		fOffGameStatDetail.fPenaltyMinutes;
	dataSet.FieldByName("HatTricks")->AsInteger = fOffGameStatDetail.fHatTricks;
	dataSet.FieldByName("Fights")->AsInteger = fOffGameStatDetail.fFights;
}

/******************************************************************************/

void THockeyOffGameStat::validateForUpdate()
{
	TOffGameStat::validateForUpdate();
}

/******************************************************************************/
/******************************************************************************/

void THockeyDefGameStat::clear()
{
	TDefGameStat::clear();

	fDefGameStatDetail.clear();
}

/******************************************************************************/

double THockeyDefGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);

	return(fDefGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 THockeyDefGameStat::getDefaultStatStr(int playerStatType)
{
	return("0000");
}

/******************************************************************************/

CStr31 THockeyDefGameStat::getStatStr(int playerStatType)
{
	CStr31 str;
	double stat = getStat(playerStatType);

	if(stat < 0)
		str.CopyVarg("-%03.lf",stat * -1.0);
	else
		str.CopyVarg("%04.lf",stat);

	return(str);
}

/******************************************************************************/
	
void THockeyDefGameStat::sumStats(const TDefGameStatPtr defGameStatPtr)
{
	fTotalPoints +=
		THockeyDefGameStatPtr(defGameStatPtr)->getTotalPoints();

	fDefGameStatDetail.sumStats(
		THockeyDefGameStatPtr(defGameStatPtr)->defGameStatDetail());
}

/******************************************************************************/
	
void THockeyDefGameStat::readFromDataSet(TDataSet& dataSet)
{
	TDefGameStat::readFromDataSet(dataSet);

	fDefGameStatDetail.fGamesPlayed =
		(short)dataSet.FieldByName("GamesPlayed")->AsInteger;
	fDefGameStatDetail.fGamesStarted =
		(short)dataSet.FieldByName("GamesStarted")->AsInteger;
	fDefGameStatDetail.fMinutesPlayed =
		(short)dataSet.FieldByName("MinutesPlayed")->AsInteger;

	fDefGameStatDetail.fWins = (short)dataSet.FieldByName("Wins")->AsInteger;
	fDefGameStatDetail.fLosses = (short)dataSet.FieldByName("Losses")->AsInteger;
	fDefGameStatDetail.fTies = (short)dataSet.FieldByName("Ties")->AsInteger;

	fDefGameStatDetail.fGoalsAgainst =
		(short)dataSet.FieldByName("GoalsAgainst")->AsInteger;
	fDefGameStatDetail.fEmptyNetGoalsAgainst =
		(short)dataSet.FieldByName("EmptyNetGoalsAgainst")->AsInteger;
	fDefGameStatDetail.fShotsAgainst =
		(short)dataSet.FieldByName("ShotsAgainst")->AsInteger;
	fDefGameStatDetail.fSaves = (short)dataSet.FieldByName("Saves")->AsInteger;
	fDefGameStatDetail.fShutouts =
		(short)dataSet.FieldByName("Shutouts")->AsInteger;

	fDefGameStatDetail.fMajorPenalties =
		(short)dataSet.FieldByName("MajorPenalties")->AsInteger;
	fDefGameStatDetail.fPenaltyMinutes =
		(short)dataSet.FieldByName("PenaltyMinutes")->AsInteger;
	fDefGameStatDetail.fFights =
		(short)dataSet.FieldByName("Fights")->AsInteger;
}

/******************************************************************************/

void THockeyDefGameStat::writeToDataSet(TDataSet& dataSet)
{
	TDefGameStat::writeToDataSet(dataSet);
	
	dataSet.FieldByName("GamesPlayed")->AsInteger =
		fDefGameStatDetail.fGamesPlayed;
	dataSet.FieldByName("GamesStarted")->AsInteger =
		fDefGameStatDetail.fGamesStarted;
	dataSet.FieldByName("MinutesPlayed")->AsInteger =
		fDefGameStatDetail.fMinutesPlayed;

	dataSet.FieldByName("Wins")->AsInteger = fDefGameStatDetail.fWins;
	dataSet.FieldByName("Losses")->AsInteger = fDefGameStatDetail.fLosses;
	dataSet.FieldByName("Ties")->AsInteger = fDefGameStatDetail.fTies;

	dataSet.FieldByName("GoalsAgainst")->AsInteger =
		fDefGameStatDetail.fGoalsAgainst;
	dataSet.FieldByName("EmptyNetGoalsAgainst")->AsInteger =
		fDefGameStatDetail.fEmptyNetGoalsAgainst;
	dataSet.FieldByName("ShotsAgainst")->AsInteger =
		fDefGameStatDetail.fShotsAgainst;
	dataSet.FieldByName("Saves")->AsInteger = fDefGameStatDetail.fSaves;
	dataSet.FieldByName("Shutouts")->AsInteger = fDefGameStatDetail.fShutouts;

	dataSet.FieldByName("MajorPenalties")->AsInteger =
		fDefGameStatDetail.fMajorPenalties;
	dataSet.FieldByName("PenaltyMinutes")->AsInteger =
		fDefGameStatDetail.fPenaltyMinutes;
	dataSet.FieldByName("Fights")->AsInteger = fDefGameStatDetail.fFights;
}

/******************************************************************************/

void THockeyDefGameStat::validateForUpdate()
{
	TDefGameStat::validateForUpdate();
}

/******************************************************************************/
/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
