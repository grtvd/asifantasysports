/* ASBasketballType.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommDB.h"

#include "ASBasketballType.h"
#include "ASBasketballObjectBuilder.h"

namespace asbasketball
{

// Template code is not being include.
TPositionVector gUnusedPositionVector;

/******************************************************************************/
/******************************************************************************/

TBasketballPosition::TBasketballPosition(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "PG")
		fT = pos_PointGuard;
	else if(value == "SG")
		fT = pos_ShootingGuard;
	else if(value == "SF")
		fT = pos_SmallForward;
	else if(value == "PF")
		fT = pos_PowerForward;
	else if(value == "C")
		fT = pos_Center;

	// Non-Participating Player Positions
	
	else
		throw ASIException("TBasketballPosition::TBasketballPosition: invalid "
			"str(%s)",str);
}

/******************************************************************************/

const char* TBasketballPosition::c_str() const
{
	switch(fT)
	{
		case pos_PointGuard:
			return("PG");
		case pos_ShootingGuard:
			return("SG");
		case pos_SmallForward:
			return("SF");
		case pos_PowerForward:
			return("PF");
		case pos_Center:
			return("C");

		// Non-Participating Player Positions

		default:
			break;
	};

	throw ASIException("TBasketballPosition::c_str: invalid fT");
}

/******************************************************************************/

bool TBasketballPosition::isKey() const
{
	if(isUndefined())
		throw ASIException("TBasketballPosition::isKey: invalid fT(%d)",(int)fT);

	return(fT <= pos_LastKeyPos);
}

/******************************************************************************/

bool TBasketballPosition::isOffensive() const
{
	if(isUndefined() || !isKey())
		throw ASIException("TBasketballPosition::isOffensive: invalid fT(%d)",(int)fT);

	return(true);
}

/******************************************************************************/

void asfantasy::loadKeyPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = asbasketball::pos_FirstKeyPos; i <= asbasketball::pos_LastKeyPos; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadAllPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = asbasketball::pos_FirstKeyPos; i <= asbasketball::pos_Last; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadDefaultLineupPositionVector(const TLineup lineup,
	TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	if(lineup == asbasketball::lut_Starting)
	{
		posVector.push_back(asbasketball::pos_PointGuard);
		posVector.push_back(asbasketball::pos_PointGuard);
		posVector.push_back(asbasketball::pos_ShootingGuard);
		posVector.push_back(asbasketball::pos_ShootingGuard);
		posVector.push_back(asbasketball::pos_SmallForward);
		posVector.push_back(asbasketball::pos_SmallForward);
		posVector.push_back(asbasketball::pos_PowerForward);
		posVector.push_back(asbasketball::pos_PowerForward);
		posVector.push_back(asbasketball::pos_Center);
	}
}

/******************************************************************************/

CStrVar asfantasy::convertPositionToString(int position)
{
	asbasketball::TBasketballPosition basketballPosition(position);

	return(basketballPosition.c_str());
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

void TBasketballTeam::clear()
{
	TTeam::clear();

	fLineup.erase(fLineup.begin(),fLineup.end());
}

/******************************************************************************/

const TPlayerIDVector& TBasketballTeam::lineupConst(TLineup lineup) const
{
	if(lineup == lut_Starting)
		return(fLineup);

	throw ASIException("TBasketballTeam::lineupConst: invalid lineup");
}

/******************************************************************************/

TPlayerIDVector& TBasketballTeam::lineup(TLineup lineup)
{
	setHasChanged();

	if(lineup == lut_Starting)
		return(fLineup);

	throw ASIException("TBasketballTeam::lineup: invalid lineup");
}

/******************************************************************************/

void TBasketballTeam::readFromDataSet(TDataSet& dataSet)
{
	TTeam::readFromDataSet(dataSet);

	readLineupFromDataSet(dataSet,lut_Starting,"Lineup");
}

/******************************************************************************/

void TBasketballTeam::writeToDataSet(TDataSet& dataSet)
{
	TTeam::writeToDataSet(dataSet);

	writeLineupToDataSet(dataSet,lut_Starting,"Lineup");
}

/******************************************************************************/
/******************************************************************************/

void TBasketballProfPlayer::clear()
{
	TProfPlayer::clear();

	fPosition.clear();

	fRosterStatus.clear();
}

/******************************************************************************/

void TBasketballProfPlayer::readFromDataSet(TDataSet& dataSet)
{
	TProfPlayer::readFromDataSet(dataSet);

	fPosition = dataSet.FieldByName("Pos")->AsString.c_str();

	fRosterStatus = dataSet.FieldByName("RosterStatus")->AsString.c_str();
}

/******************************************************************************/

void TBasketballProfPlayer::writeToDataSet(TDataSet& dataSet)
{
	TProfPlayer::writeToDataSet(dataSet);

	dataSet.FieldByName("Pos")->AsString = fPosition.c_str();

	dataSet.FieldByName("RosterStatus")->AsString = fRosterStatus.c_str();
}

/******************************************************************************/

void TBasketballProfPlayer::validateForUpdate()
{
	TProfPlayer::validateForUpdate();

	if(fPosition.isUndefined())
		throw ASIException("TBasketballProfPlayer::validateForUpdate: fPosition.isUndefined()");

	if(fRosterStatus.isUndefined())
		throw ASIException("TBasketballProfPlayer::validateForUpdate: fRosterStatus.isUndefined()");
}

/******************************************************************************/
/******************************************************************************/

void TOffGameStatDetail::clear()
{
	fGamesPlayed = 0;
	fMinutesPlayed = 0;
	fPointsScored = 0;

	fTwoPointGoalsMade = 0;
	fTwoPointGoalsMissed = 0;
	fThreePointGoalsMade = 0;
	fThreePointGoalsMissed = 0;
	fFreeThrowsMade = 0;
	fFreeThrowsMissed = 0;

	fOffensiveRebounds = 0;
	fDefensiveRebounds = 0;
	fAssists = 0;
	fSteals = 0;
	fBlocks = 0;

	fTurnovers = 0;
	fPersonalFouls = 0;
	fTechnicalFouls = 0;
}

/******************************************************************************/

short TOffGameStatDetail::calcTotalPoints() const
{
	short totalPoints = 0;

	totalPoints += cast2short(fTwoPointGoalsMade * 2);
	totalPoints -= cast2short(fTwoPointGoalsMissed * 1);
	totalPoints += cast2short(fThreePointGoalsMade * 3);
	totalPoints -= cast2short(fThreePointGoalsMissed * 1);
	totalPoints += cast2short(fFreeThrowsMade * 1);
	totalPoints -= cast2short(fFreeThrowsMissed * 1);

	totalPoints += cast2short(fOffensiveRebounds * 1);
	totalPoints += cast2short(fDefensiveRebounds * 1);
	totalPoints += cast2short(fAssists * 2);
	totalPoints += cast2short(fSteals * 4);
	totalPoints += cast2short(fBlocks * 4);

	totalPoints -= cast2short(fTurnovers * 1);
	totalPoints -= cast2short(fPersonalFouls * 1);
	totalPoints -= cast2short(fTechnicalFouls * 3);

	return(totalPoints);
}

/******************************************************************************/

double TOffGameStatDetail::getStat(int playerStatType)
{
	TBasketballPlayerStatType basketballPlayerStatType(playerStatType);
	
	switch(basketballPlayerStatType)
	{
		case pst_GamesPlayed:
			return(fGamesPlayed);
		case pst_MinutesPlayed:
			return(fMinutesPlayed);
		case pst_PointsScored:
			return(fPointsScored);

		case pst_FieldGoalsMade:
			return(fTwoPointGoalsMade + fThreePointGoalsMade);
		case pst_FieldGoalsAttempted:
			return(fTwoPointGoalsMade + fTwoPointGoalsMissed +
				fThreePointGoalsMade + fThreePointGoalsMissed);
		case pst_FieldGoalPercentage:
		{
			double attempts = fTwoPointGoalsMade + fTwoPointGoalsMissed +
				fThreePointGoalsMade + fThreePointGoalsMissed;
			if(attempts != 0.0)
				return((double)(fTwoPointGoalsMade + fThreePointGoalsMade) / attempts);
			return(0.0);
		}
		case pst_FreeThrowsMade:
			return(fFreeThrowsMade);
		case pst_FreeThrowsAttempted:
			return(fFreeThrowsMade + fFreeThrowsMissed);
		case pst_FreeThrowPercentage:
		{
			double attempts = fFreeThrowsMade + fFreeThrowsMissed;
			if(attempts != 0.0)
				return((double)fFreeThrowsMade / attempts);
			return(0.0);
		}
		case pst_ThreePointGoalsMade:
			return(fThreePointGoalsMade);
		case pst_ThreePointGoalsAttempted:
			return(fThreePointGoalsMade + fThreePointGoalsMissed);

		case pst_OffensiveRebounds:
			return(fOffensiveRebounds);
		case pst_DefensiveRebounds:
			return(fDefensiveRebounds);
		case pst_Assists:
			return(fAssists);
		case pst_Steals:
			return(fSteals);
		case pst_Blocks:
			return(fBlocks);

		case pst_Turnovers:
			return(fTurnovers);
		case pst_PersonalFouls:
			return(fPersonalFouls);
		case pst_TechnicalFouls:
			return(fTechnicalFouls);

		default:
			break;
	}

	throw ASIException("TOffGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TOffGameStatDetail::sumStats(const TOffGameStatDetail& offGameStatDetail)
{
	fGamesPlayed += offGameStatDetail.fGamesPlayed;
	fMinutesPlayed += offGameStatDetail.fMinutesPlayed;
	fPointsScored += offGameStatDetail.fPointsScored;

	fTwoPointGoalsMade += offGameStatDetail.fTwoPointGoalsMade;
	fTwoPointGoalsMissed += offGameStatDetail.fTwoPointGoalsMissed;
	fThreePointGoalsMade += offGameStatDetail.fThreePointGoalsMade;
	fThreePointGoalsMissed += offGameStatDetail.fThreePointGoalsMissed;
	fFreeThrowsMade += offGameStatDetail.fFreeThrowsMade;
	fFreeThrowsMissed += offGameStatDetail.fFreeThrowsMissed;

	fOffensiveRebounds += offGameStatDetail.fOffensiveRebounds;
	fDefensiveRebounds += offGameStatDetail.fDefensiveRebounds;
	fAssists += offGameStatDetail.fAssists;
	fSteals += offGameStatDetail.fSteals;
	fBlocks += offGameStatDetail.fBlocks;

	fTurnovers += offGameStatDetail.fTurnovers;
	fPersonalFouls += offGameStatDetail.fPersonalFouls;
	fTechnicalFouls += offGameStatDetail.fTechnicalFouls;
}

/******************************************************************************/
/******************************************************************************/
#if 0	//BOB

void TDefGameStatDetail::clear()
{
	fGamesPlayed = 0;
}

/******************************************************************************/

short TDefGameStatDetail::calcTotalPoints() const
{
	short totalPoints = 0;

	return(totalPoints);
}

/******************************************************************************/

double TDefGameStatDetail::getStat(int playerStatType)
{
	TBasketballPlayerStatType basketballPlayerStatType(playerStatType);

	switch(basketballPlayerStatType)
	{
		case pst_GamesPlayed:
			return(fGamesPlayed);

		default:
			break;
	}

	throw ASIException("TDefGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TDefGameStatDetail::sumStats(const TDefGameStatDetail& defGameStatDetail)
{
	fGamesPlayed += defGameStatDetail.fGamesPlayed;
}

#endif	//BOB
/******************************************************************************/
/******************************************************************************/

void TBasketballOffGameStat::clear()
{
	TOffGameStat::clear();

	fOffGameStatDetail.clear();
}

/******************************************************************************/

double TBasketballOffGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);

	return(fOffGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 TBasketballOffGameStat::getDefaultStatStr(int playerStatType)
{
	CStr31 str;

	if((playerStatType == pst_FieldGoalPercentage) ||
			(playerStatType == pst_FreeThrowPercentage))
		str.Copy(" .000");
	else
		str.Copy("0000");

	return(str);
}

/******************************************************************************/

CStr31 TBasketballOffGameStat::getStatStr(int playerStatType)
{
	CStr31 str;
	double stat = getStat(playerStatType);

	if((playerStatType == pst_FieldGoalPercentage) ||
		(playerStatType == pst_FreeThrowPercentage))
	{
		if(stat < 1.0)
			str.CopyVarg(" .%03.0lf",stat * 1000.0);
		else
			str.Copy("1.000");
	}
	else
	{
		if(stat < 0)
			str.CopyVarg("-%03.lf",stat * -1.0);
		else
			str.CopyVarg("%04.lf",stat);
	}

	return(str);
}

/******************************************************************************/

void TBasketballOffGameStat::sumStats(const TOffGameStatPtr offGameStatPtr)
{
	fTotalPoints +=
		TBasketballOffGameStatPtr(offGameStatPtr)->getTotalPoints();

	fOffGameStatDetail.sumStats(
		TBasketballOffGameStatPtr(offGameStatPtr)->offGameStatDetail());
}

/******************************************************************************/

void TBasketballOffGameStat::readFromDataSet(TDataSet& dataSet)
{
	TOffGameStat::readFromDataSet(dataSet);
	
	fOffGameStatDetail.fGamesPlayed =
		(short)dataSet.FieldByName("GamesPlayed")->AsInteger;
	fOffGameStatDetail.fMinutesPlayed =
		(short)dataSet.FieldByName("MinutesPlayed")->AsInteger;
	fOffGameStatDetail.fPointsScored =
		(short)dataSet.FieldByName("PointsScored")->AsInteger;
	fOffGameStatDetail.fTwoPointGoalsMade =
		(short)dataSet.FieldByName("TwoPointGoalsMade")->AsInteger;
	fOffGameStatDetail.fTwoPointGoalsMissed =
		(short)dataSet.FieldByName("TwoPointGoalsMissed")->AsInteger;
	fOffGameStatDetail.fThreePointGoalsMade =
		(short)dataSet.FieldByName("ThreePointGoalsMade")->AsInteger;
	fOffGameStatDetail.fThreePointGoalsMissed =
		(short)dataSet.FieldByName("ThreePointGoalsMissed")->AsInteger;
	fOffGameStatDetail.fFreeThrowsMade =
		(short)dataSet.FieldByName("FreeThrowsMade")->AsInteger;
	fOffGameStatDetail.fFreeThrowsMissed =
		(short)dataSet.FieldByName("FreeThrowsMissed")->AsInteger;
	fOffGameStatDetail.fOffensiveRebounds =
		(short)dataSet.FieldByName("OffensiveRebounds")->AsInteger;
	fOffGameStatDetail.fDefensiveRebounds =
		(short)dataSet.FieldByName("DefensiveRebounds")->AsInteger;
	fOffGameStatDetail.fAssists =
		(short)dataSet.FieldByName("Assists")->AsInteger;
	fOffGameStatDetail.fSteals =(short)dataSet.FieldByName("Steals")->AsInteger;
	fOffGameStatDetail.fBlocks =(short)dataSet.FieldByName("Blocks")->AsInteger;
	fOffGameStatDetail.fTurnovers =
		(short)dataSet.FieldByName("Turnovers")->AsInteger;
	fOffGameStatDetail.fPersonalFouls =
		(short)dataSet.FieldByName("PersonalFouls")->AsInteger;
	fOffGameStatDetail.fTechnicalFouls =
		(short)dataSet.FieldByName("TechnicalFouls")->AsInteger;
}

/******************************************************************************/

void TBasketballOffGameStat::writeToDataSet(TDataSet& dataSet)
{
	TOffGameStat::writeToDataSet(dataSet);

	dataSet.FieldByName("GamesPlayed")->AsInteger =
		fOffGameStatDetail.fGamesPlayed;
	dataSet.FieldByName("MinutesPlayed")->AsInteger =
		fOffGameStatDetail.fMinutesPlayed;
	dataSet.FieldByName("PointsScored")->AsInteger =
		fOffGameStatDetail.fPointsScored;
	dataSet.FieldByName("TwoPointGoalsMade")->AsInteger =
		fOffGameStatDetail.fTwoPointGoalsMade;
	dataSet.FieldByName("TwoPointGoalsMissed")->AsInteger =
		fOffGameStatDetail.fTwoPointGoalsMissed;
	dataSet.FieldByName("ThreePointGoalsMade")->AsInteger =
		fOffGameStatDetail.fThreePointGoalsMade;
	dataSet.FieldByName("ThreePointGoalsMissed")->AsInteger =
		fOffGameStatDetail.fThreePointGoalsMissed;
	dataSet.FieldByName("FreeThrowsMade")->AsInteger =
		fOffGameStatDetail.fFreeThrowsMade;
	dataSet.FieldByName("FreeThrowsMissed")->AsInteger =
		fOffGameStatDetail.fFreeThrowsMissed;
	dataSet.FieldByName("OffensiveRebounds")->AsInteger =
		fOffGameStatDetail.
			fOffensiveRebounds;
	dataSet.FieldByName("DefensiveRebounds")->AsInteger =
		fOffGameStatDetail.fDefensiveRebounds;
	dataSet.FieldByName("Assists")->AsInteger =fOffGameStatDetail.fAssists;
	dataSet.FieldByName("Steals")->AsInteger =fOffGameStatDetail.fSteals;
	dataSet.FieldByName("Blocks")->AsInteger =fOffGameStatDetail.fBlocks;
	dataSet.FieldByName("Turnovers")->AsInteger =fOffGameStatDetail.fTurnovers;
	dataSet.FieldByName("PersonalFouls")->AsInteger =
		fOffGameStatDetail.fPersonalFouls;
	dataSet.FieldByName("TechnicalFouls")->AsInteger =
		fOffGameStatDetail.fTechnicalFouls;
}

/******************************************************************************/

void TBasketballOffGameStat::validateForUpdate()
{
	TOffGameStat::validateForUpdate();
}

/******************************************************************************/
/******************************************************************************/
#if 0	//BOB

void TBasketballDefGameStat::clear()
{
	TDefGameStat::clear();

	fDefGameStatDetail.clear();
}

/******************************************************************************/

double TBasketballDefGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);

	return(fDefGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 TBasketballDefGameStat::getDefaultStatStr(int playerStatType)
{
	return("0000");
}

/******************************************************************************/

CStr31 TBasketballDefGameStat::getStatStr(int playerStatType)
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
	
void TBasketballDefGameStat::sumStats(const TDefGameStatPtr defGameStatPtr)
{
	fTotalPoints +=
		TBasketballDefGameStatPtr(defGameStatPtr)->getTotalPoints();

	fDefGameStatDetail.sumStats(
		TBasketballDefGameStatPtr(defGameStatPtr)->defGameStatDetail());
}

/******************************************************************************/
	
void TBasketballDefGameStat::readFromDataSet(TDataSet& dataSet)
{
	TDefGameStat::readFromDataSet(dataSet);

	fDefGameStatDetail.fGamesPlayed =
		(short)dataSet.FieldByName("GamesPlayed")->AsInteger;
}

/******************************************************************************/

void TBasketballDefGameStat::writeToDataSet(TDataSet& dataSet)
{
	TDefGameStat::writeToDataSet(dataSet);
	
	dataSet.FieldByName("GamesPlayed")->AsInteger =
		fDefGameStatDetail.fGamesPlayed;
}

/******************************************************************************/

void TBasketballDefGameStat::validateForUpdate()
{
	TDefGameStat::validateForUpdate();
}

#endif	//BOB
/******************************************************************************/
/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
