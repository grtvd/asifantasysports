/* ASFootballType.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommDB.h"

#include "ASFootballAppOptions.h"
#include "ASFootballType.h"
#include "ASFootballObjectBuilder.h"

namespace asfootball
{

// Template code is not being include.
TPositionVector gUnusedPositionVector;

/******************************************************************************/
/******************************************************************************/

TFootballPosition::TFootballPosition(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "QB")
		fT = pos_Quarterback;
	else if(value == "WR")
		fT = pos_WideReceiver;
	else if(value == "RB")
		fT = pos_RunningBack;
	else if(value == "TE")
		fT = pos_TightEnd;
	else if(value == "K")
		fT = pos_Kicker;
	else if(value == "D")
		fT = pos_Defense;

	// Non-Participating Player Positions
	
	else if(value == "C")
		fT = pos_Center;
	else if(value == "NT")
		fT = pos_NoseTackle;
	else if(value == "P")
		fT = pos_Punter;
	else if(value == "CB")
		fT = pos_Cornerback;
	else if(value == "LB")
		fT = pos_Linebacker;
	else if(value == "DE")
		fT = pos_DefEnd;
	else if(value == "DT")
		fT = pos_DefTackle;
	else if(value == "DB")
		fT = pos_DefBack;
	else if(value == "S")  
		fT = pos_Saftey;
	else if(value == "T")
		fT = pos_Tackle;
	else if(value == "G")
		fT = pos_Guard;
	else
		throw ASIException("TFootballPosition::TFootballPosition: invalid "
			"str(%s)",str);
}

/******************************************************************************/

const char* TFootballPosition::c_str() const
{
	switch(fT)
	{
		case pos_Quarterback:
			return("QB");
		case pos_WideReceiver:
			return("WR");
		case pos_RunningBack:
			return("RB");
		case pos_TightEnd:
			return("TE");
		case pos_Kicker:
			return("K");
		case pos_Defense:
			return("D");
			
		// Non-Participating Player Positions

		case pos_Center:
			return("C");
		case pos_NoseTackle:
			return("NT");
		case pos_Punter:
			return("P");
		case pos_Cornerback:
			return("CB");
		case pos_Linebacker:
			return("LB");
		case pos_DefEnd:
			return("DE");
		case pos_DefTackle:
			return("DT");
		case pos_DefBack:
			return("DB");
		case pos_Saftey:
			return("S");
		case pos_Tackle:
			return("T");
		case pos_Guard:
			return("G");
		
		default:
			break;
	};

	throw ASIException("TFootballPosition::c_str: invalid fT");
}

/******************************************************************************/

bool TFootballPosition::isKey() const
{
	if(isUndefined())
		throw ASIException("TFootballPosition::isKey: invalid fT(%d)",(int)fT);

	return(fT <= pos_LastKeyPos);
}

/******************************************************************************/

bool TFootballPosition::isOffensive() const
{
	if(isUndefined() || !isKey())
		throw ASIException("TFootballPosition::isOffensive: invalid fT(%d)",(int)fT);

	return(fT != pos_Defense);
}

/******************************************************************************/

void asfantasy::loadKeyPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = asfootball::pos_Quarterback; i <= asfootball::pos_LastKeyPos; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadAllPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = asfootball::pos_Quarterback; i <= asfootball::pos_Last; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadDefaultLineupPositionVector(const TLineup lineup,
	TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	if(lineup == asfootball::lut_Starting)
	{
		posVector.push_back(asfootball::pos_Quarterback);
		posVector.push_back(asfootball::pos_RunningBack);
		posVector.push_back(asfootball::pos_RunningBack);
		posVector.push_back(asfootball::pos_WideReceiver);
		posVector.push_back(asfootball::pos_WideReceiver);
		posVector.push_back(asfootball::pos_TightEnd);
		posVector.push_back(asfootball::pos_Kicker);
		posVector.push_back(asfootball::pos_Defense);
	}
}

/******************************************************************************/

CStrVar asfantasy::convertPositionToString(int position)
{
	asfootball::TFootballPosition footballPosition(position);

	return(footballPosition.c_str());
}

/******************************************************************************/
/******************************************************************************/

TRosterStatus::TRosterStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "A")
		fT = rst_Active;
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
		case rst_Inactive:
			return("I");
		default:
			break;
	};

	throw ASIException("TRosterStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TInjuryStatus::TInjuryStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = ist_NoInjury;
	else if(value == "P")
		fT = ist_Probable;
	else if(value == "Q")
		fT = ist_Questionable;
	else if(value == "D")
		fT = ist_Doubtful;
	else if(value == "O")
		fT = ist_Out;
	else
		throw ASIException("TInjuryStatus::TInjuryStatus: invalid str(%s)",str);
}

/******************************************************************************/

const char* TInjuryStatus::c_str() const
{
	switch(fT)
	{
		case ist_NoInjury:
			return("X");
		case ist_Probable:
			return("P");
		case ist_Questionable:
			return("Q");
		case ist_Doubtful:
			return("D");
		case ist_Out:
			return("O");
		default:
			break;
	};

	throw ASIException("TInjuryStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TPlayerID asfootball::ConvertProfTeamIDtoPlayerID(TProfTeamID profTeamID)
{
	return(999999000UL + profTeamID.getID());
}

/******************************************************************************/

TProfTeamID asfootball::ConvertPlayerIDtoProfTeamID(TPlayerID playerID)
{
	if((playerID < 999999000UL) || (playerID > 999999999UL))
		throw ASIException("ConvertPlayerIDtoProfTeamID: bad playerID");
		
	return(playerID.getID() - 999999000UL);
}

/******************************************************************************/
/******************************************************************************/

void TFootballTeam::clear()
{
	TTeam::clear();
	
	fLineup.erase(fLineup.begin(),fLineup.end());
}

/******************************************************************************/

const TPlayerIDVector& TFootballTeam::lineupConst(TLineup lineup) const
{
	if(lineup != lut_Starting)
		throw ASIException("TFootballTeam::lineupConst: invalid lineup");

	return(fLineup);
}

/******************************************************************************/

TPlayerIDVector& TFootballTeam::lineup(TLineup lineup)
{
	if(lineup != lut_Starting)
		throw ASIException("TFootballTeam::lineup: invalid lineup");

	setHasChanged();
	return(fLineup);
}

/******************************************************************************/

void TFootballTeam::readFromDataSet(TDataSet& dataSet)
{
	TTeam::readFromDataSet(dataSet);

	readLineupFromDataSet(dataSet,lut_Starting,"Lineup");
}

/******************************************************************************/

void TFootballTeam::writeToDataSet(TDataSet& dataSet)
{
	TTeam::writeToDataSet(dataSet);
	
	writeLineupToDataSet(dataSet,lut_Starting,"Lineup");
}

/******************************************************************************/
/******************************************************************************/

void TFootballProfPlayer::clear()
{
	TProfPlayer::clear();

	fPosition.clear();

	fRosterStatus.clear();
	fInjuryStatus.clear();
	fCollegeName.Clear();
	fYearsPro = 0;
}

/******************************************************************************/

void TFootballProfPlayer::readFromDataSet(TDataSet& dataSet)
{
	TProfPlayer::readFromDataSet(dataSet);
	
	fPosition = dataSet.FieldByName("Pos")->AsString.c_str();

	fRosterStatus = dataSet.FieldByName("RosterStatus")->AsString.c_str();
	fInjuryStatus = dataSet.FieldByName("InjuryStatus")->AsString.c_str();
	fCollegeName = dataSet.FieldByName("CollegeAttended")->AsString.c_str();
	fYearsPro = (short)dataSet.FieldByName("YearsPro")->AsInteger;
}

/******************************************************************************/

void TFootballProfPlayer::writeToDataSet(TDataSet& dataSet)
{
	TProfPlayer::writeToDataSet(dataSet);
	
	dataSet.FieldByName("Pos")->AsString = fPosition.c_str();
	
	dataSet.FieldByName("RosterStatus")->AsString = fRosterStatus.c_str();
	dataSet.FieldByName("InjuryStatus")->AsString = fInjuryStatus.c_str();
	dataSet.FieldByName("CollegeAttended")->AsString = fCollegeName.c_str();
	dataSet.FieldByName("YearsPro")->AsInteger = fYearsPro;
}

/******************************************************************************/

void TFootballProfPlayer::validateForUpdate()
{
	TProfPlayer::validateForUpdate();

	if(fPosition.isUndefined())
		throw ASIException("TFootballProfPlayer::validateForUpdate: fPosition.isUndefined()");
		
	if(fRosterStatus.isUndefined())
		throw ASIException("TFootballProfPlayer::validateForUpdate: fRosterStatus.isUndefined()");
	if(fInjuryStatus.isUndefined())
		throw ASIException("TFootballProfPlayer::validateForUpdate: fInjuryStatus.isUndefined()");
}

/******************************************************************************/
/******************************************************************************/

void YardageBuckets::setBucket(YardageBucketsDistance ybd,short count)
{
	int i,numAdd;
	
	if(ybd >= fBuckets.size())
	{
		numAdd = ybd - fBuckets.size() + 1;
		for(i = 0; i < numAdd; i++)
			fBuckets.push_back(0);
	}

	if(count <= UCHAR_MAX)
		fBuckets[ybd] = (byte)count;
	else
		throw ASIException("YardageBuckets::setBucket: overflow");
}

/******************************************************************************/

byte YardageBuckets::getBucket(YardageBucketsDistance ybd) const
{
	if(ybd >= fBuckets.size())
		return(0);

	return(fBuckets[ybd]);
}

/******************************************************************************/

short YardageBuckets::totalBuckets() const
{
	vector<ItemType>::const_iterator iter;
	short count = 0;

	for(iter = fBuckets.begin(); iter != fBuckets.end(); iter++)
		count += *iter;

	return(count);
}

/******************************************************************************/

void YardageBuckets::addYards(byte yards)
{
	if(yards < 10)
		incBucket(ybd_00_to_09);
	else if(yards < 20)
		incBucket(ybd_10_to_19);
	else if(yards < 30)
		incBucket(ybd_20_to_29);
	else if(yards < 40)
		incBucket(ybd_30_to_39);
	else if(yards < 50)
		incBucket(ybd_40_to_49);
	else
		incBucket(ybd_50_plus);
}

/******************************************************************************/

void YardageBuckets::sumBuckets(const YardageBuckets& yardageBuckets)
{
	int i,numItems = yardageBuckets.numBuckets();

	for(i = 0; i < numItems; i++)
		setBucket(i,getBucket(i) + yardageBuckets.getBucket(i));
}

/******************************************************************************/
/******************************************************************************/

void TOffGameStatDetail::clear()
{
	/* Passing Stats */
	fPassingYards = 0;
	fInterceptions = 0;
	fTwoPointPasses = 0;
	fPassingTDYardageBuckets.clear();
	
	/* Rushing Stats */
	fRushingYards = 0;
	fFumbles = 0;
	fTwoPointRushes = 0;
	fRushingTDYardageBuckets.clear();
	
	/* Receiving Stats */
	fReceivingYards = 0;
	fTwoPointReceptions = 0;
	fReceivingTDYardageBuckets.clear();

	/* Misc Offense */
	fKickReturnTDYardageBuckets.clear();
	fMiscTDYardageBuckets.clear();
		
	/* Kicking Stats */
	fPATsAttempted = 0;
	fPATsMade = 0;
	fFieldGoalsAttempted = 0;
	fFieldGoalYardageBuckets.clear();
}

/******************************************************************************/

short TOffGameStatDetail::calcTotalPoints() const
{
	short totalPoints = 0;

	/* Passing Stats */
	if(fPassingYards >= 50)								// >= 150
		totalPoints += (fPassingYards / 50);			// ((fPassingYards - 100) / 50)
	
	totalPoints -= (fInterceptions * 3);
	totalPoints += (fTwoPointPasses * 2);
	
	totalPoints += calcTouchdowns(fPassingTDYardageBuckets,3);
	
	/* Rushing Stats */
	if(fRushingYards >= 25)								// >= 25
		totalPoints += (fRushingYards / 25);			// ((fRushingYards - 25) / 25)
		
	totalPoints -= (fFumbles * 3);
	totalPoints += (fTwoPointRushes * 2);

	totalPoints += calcTouchdowns(fRushingTDYardageBuckets,6);
	
	/* Receiving Stats */
	if(fReceivingYards >= 50)
		totalPoints += ((fReceivingYards - 25) / 25);
		
	totalPoints += (fTwoPointReceptions * 2);

	totalPoints += calcTouchdowns(fReceivingTDYardageBuckets,6);

	/* Misc Offense */
	totalPoints += calcTouchdowns(fKickReturnTDYardageBuckets,6);
	totalPoints += calcTouchdowns(fMiscTDYardageBuckets,6);
		
	/* Kicking Stats */
	totalPoints += (fPATsMade * 1);
	totalPoints -= ((fPATsAttempted - fPATsMade) * 1);

	totalPoints += calcFieldGoals(fFieldGoalsAttempted,
		fFieldGoalYardageBuckets);
	
	return(totalPoints);
}

/******************************************************************************/

double TOffGameStatDetail::getStat(int playerStatType)
{
	FootballPlayerStatType footballPlayerStatType(playerStatType);
	
	switch(footballPlayerStatType)
	{
		case pst_PassingYards:
			return(fPassingYards);
		case pst_PassingTDs:
			return(fPassingTDYardageBuckets.totalBuckets());
		case pst_Interceptions:
			return(fInterceptions);
		case pst_TwoPointPasses:
			return(fTwoPointPasses);
		case pst_RushingYards:
			return(fRushingYards);
		case pst_RushingTDs:
			return(fRushingTDYardageBuckets.totalBuckets());
		case pst_Fumbles:
			return(fFumbles);
		case pst_TwoPointRushes:
			return(fTwoPointRushes);
		case pst_ReceivingYards:
			return(fReceivingYards);
		case pst_ReceivingTDs:
			return(fReceivingTDYardageBuckets.totalBuckets());
		case pst_TwoPointReceptions:
			return(fTwoPointReceptions);
		case pst_KickReturnTDs:
			return(fKickReturnTDYardageBuckets.totalBuckets());
		case pst_MiscTDs:
			return(fMiscTDYardageBuckets.totalBuckets());
		case pst_PATsMade:
			return(fPATsMade);
		case pst_PATsMissed:
			return(fPATsAttempted - fPATsMade);
		case pst_FieldGoalsMade:
			return(fFieldGoalYardageBuckets.totalBuckets());
		case pst_FieldGoalsMissed:
			return(fFieldGoalsAttempted - fFieldGoalYardageBuckets.totalBuckets());
		default:
			break;
	}

	throw ASIException("TOffGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TOffGameStatDetail::sumStats(const TOffGameStatDetail& offGameStatDetail)
{
	/* Passing Stats */
	fPassingYards += offGameStatDetail.fPassingYards;
	fInterceptions += offGameStatDetail.fInterceptions;
	fTwoPointPasses += offGameStatDetail.fTwoPointPasses;
	fPassingTDYardageBuckets.sumBuckets(offGameStatDetail.fPassingTDYardageBuckets);
	
	/* Rushing Stats */
	fRushingYards += offGameStatDetail.fRushingYards;
	fFumbles += offGameStatDetail.fFumbles;
	fTwoPointRushes += offGameStatDetail.fTwoPointRushes;
	fRushingTDYardageBuckets.sumBuckets(offGameStatDetail.fRushingTDYardageBuckets);
	
	/* Receiving Stats */
	fReceivingYards += offGameStatDetail.fReceivingYards;
	fTwoPointReceptions += offGameStatDetail.fTwoPointReceptions;
	fReceivingTDYardageBuckets.sumBuckets(offGameStatDetail.fReceivingTDYardageBuckets);

	/* Misc Offense */
	fKickReturnTDYardageBuckets.sumBuckets(offGameStatDetail.fKickReturnTDYardageBuckets);
	fMiscTDYardageBuckets.sumBuckets(offGameStatDetail.fMiscTDYardageBuckets);
	
	/* Kicking Stats */
	fPATsAttempted += offGameStatDetail.fPATsAttempted;
	fPATsMade += offGameStatDetail.fPATsMade;
	fFieldGoalsAttempted += offGameStatDetail.fFieldGoalsAttempted;
	fFieldGoalYardageBuckets.sumBuckets(offGameStatDetail.fFieldGoalYardageBuckets);
}

/******************************************************************************/

short TOffGameStatDetail::calcTouchdowns(const YardageBuckets& yardageBuckets,
	short touchdownValue)
{
	short totalPoints = 0;
	
	totalPoints += (yardageBuckets.totalBuckets() * touchdownValue);

	totalPoints += (yardageBuckets.getBucket(ybd_10_to_19) * 1);
	totalPoints += (yardageBuckets.getBucket(ybd_20_to_29) * 2);
	totalPoints += (yardageBuckets.getBucket(ybd_30_to_39) * 3);
	totalPoints += (yardageBuckets.getBucket(ybd_40_to_49) * 4);
	totalPoints += (yardageBuckets.getBucket(ybd_50_plus) * 5);

	return(totalPoints);
}

/******************************************************************************/

short TOffGameStatDetail::calcFieldGoals(byte fieldGoalsAttempted,
	const YardageBuckets& yardageBuckets)
{
	short totalPoints = 0;
	int numItems;

	numItems = yardageBuckets.totalBuckets();
	totalPoints += (numItems * 3);

//	totalPoints += (yardageBuckets.getBucket(ybd_30_to_39) * 1);
//	totalPoints += (yardageBuckets.getBucket(ybd_40_to_49) * 2);
//	totalPoints += (yardageBuckets.getBucket(ybd_50_plus) * 3);
	totalPoints += (yardageBuckets.getBucket(ybd_40_to_49) * 1);
	totalPoints += (yardageBuckets.getBucket(ybd_50_plus) * 2);
			
//	totalPoints -= ((fieldGoalsAttempted - numItems) * 1);
	totalPoints -= ((fieldGoalsAttempted - numItems) * 3);
	return(totalPoints);
}

/******************************************************************************/
/******************************************************************************/

void TDefGameStatDetail::clear()
{
	fPassingYardsAllowed = 0;
	fRushingYardsAllowed = 0;
	fSafeties = 0;
	fSacks = 0;
	fBlockedKicks = 0;
	fFumblesRecovered = 0;
	fInterceptions = 0;
	fDefensiveTDs = 0;
}

/******************************************************************************/

short TDefGameStatDetail::calcTotalPoints() const
{
	short totalPoints = 0;
	short yardsAllowed = fPassingYardsAllowed + fRushingYardsAllowed;

	if(yardsAllowed < 150)
		totalPoints += 4;
	else if(yardsAllowed < 200)
		totalPoints += 3;
	else if(yardsAllowed < 250)
		totalPoints += 2;
	else if(yardsAllowed < 300)
		totalPoints += 1;
	else if(yardsAllowed < 350)
		totalPoints += 0;
	else if(yardsAllowed < 400)
		totalPoints += -1;
	else if(yardsAllowed < 450)
		totalPoints += -2;
	else if(yardsAllowed < 500)
		totalPoints += -3;
	else
		totalPoints += -4;
			
	totalPoints += fSafeties * 2;
	totalPoints += fSacks * 1;
	totalPoints += fBlockedKicks * 2;
	totalPoints += (fFumblesRecovered + fInterceptions) * 2;
	totalPoints += fDefensiveTDs * 6;
		 
	return(totalPoints);
}

/******************************************************************************/

double TDefGameStatDetail::getStat(int playerStatType)
{
	FootballPlayerStatType footballPlayerStatType(playerStatType);
	
	switch(footballPlayerStatType)
	{
		case pst_YardsAllowed:
			return(fPassingYardsAllowed + fRushingYardsAllowed);
		case pst_Safeties:
			return(fSafeties);
		case pst_Sacks:
			return(fSacks);
		case pst_BlockedKicks:
			return(fBlockedKicks);
		case pst_FumblesRecovered:
			return(fFumblesRecovered);
		case pst_DefInterceptions:
			return(fInterceptions);
		case pst_DefensiveTDs:
			return(fDefensiveTDs);
		default:
			break;
	}

	throw ASIException("TDefGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TDefGameStatDetail::sumStats(const TDefGameStatDetail& defGameStatDetail)
{
	fPassingYardsAllowed += defGameStatDetail.fPassingYardsAllowed;
	fRushingYardsAllowed += defGameStatDetail.fRushingYardsAllowed;
	fSafeties += defGameStatDetail.fSafeties;
	fSacks += defGameStatDetail.fSacks;
	fBlockedKicks += defGameStatDetail.fBlockedKicks;
	fFumblesRecovered += defGameStatDetail.fFumblesRecovered;
	fInterceptions += defGameStatDetail.fInterceptions;
	fDefensiveTDs += defGameStatDetail.fDefensiveTDs;
}

/******************************************************************************/
/******************************************************************************/

void TFootballOffGameStat::clear()
{
	TOffGameStat::clear();
	
	fOffGameStatDetail.clear();
}

/******************************************************************************/

double TFootballOffGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);
		
	return(fOffGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 TFootballOffGameStat::getDefaultStatStr(int playerStatType)
{
	return("0000");
}

/******************************************************************************/

CStr31 TFootballOffGameStat::getStatStr(int playerStatType)
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

void TFootballOffGameStat::sumStats(const TOffGameStatPtr offGameStatPtr)
{
	fTotalPoints +=
		TFootballOffGameStatPtr(offGameStatPtr)->getTotalPoints();

	fOffGameStatDetail.sumStats(
		TFootballOffGameStatPtr(offGameStatPtr)->offGameStatDetail());
}

/******************************************************************************/

void TFootballOffGameStat::readYardageFromDataSet(TDataSet& dataSet,
	YardageBuckets& yardageBuckets,const char* subFieldName)
{
	CStr31 fieldName;
	byte count;
	int i,numItems;
	
	fieldName.CopyVarg("Num%sBucs",subFieldName);
	numItems = dataSet.FieldByName(fieldName.c_str())->AsInteger;
	
	yardageBuckets.clear();
	
	for(i = 0; i < numItems; i++)
	{
		fieldName.CopyVarg("%sBuc%02d",subFieldName,i + 1);
		count = (byte)(dataSet.FieldByName(fieldName.c_str())->AsInteger);
			
		yardageBuckets.setBucket(i,count);
	}
}

/******************************************************************************/
	
void TFootballOffGameStat::readFromDataSet(TDataSet& dataSet)
{
	TOffGameStat::readFromDataSet(dataSet);
	
	/* Passing Stats */
	fOffGameStatDetail.fPassingYards = (short)dataSet.FieldByName("PassingYards")->AsInteger;
	fOffGameStatDetail.fInterceptions = (byte)dataSet.FieldByName("Interceptions")->AsInteger;
	fOffGameStatDetail.fTwoPointPasses = (byte)dataSet.FieldByName("TwoPointPasses")->AsInteger;
	
	readYardageFromDataSet(dataSet,fOffGameStatDetail.fPassingTDYardageBuckets,
		"PassingTD");
	
	/* Rushing Stats */
	fOffGameStatDetail.fRushingYards = (short)dataSet.FieldByName("RushingYards")->AsInteger;
	fOffGameStatDetail.fFumbles = (byte)dataSet.FieldByName("Fumbles")->AsInteger;
	fOffGameStatDetail.fTwoPointRushes = (byte)dataSet.FieldByName("TwoPointRushes")->AsInteger;
	
	readYardageFromDataSet(dataSet,fOffGameStatDetail.fRushingTDYardageBuckets,
		"RushingTD");
	
	/* Receiving Stats */
	fOffGameStatDetail.fReceivingYards = (short)dataSet.FieldByName("ReceivingYards")->AsInteger;
	fOffGameStatDetail.fTwoPointReceptions = (byte)dataSet.FieldByName("TwoPointReceptions")->AsInteger;

	readYardageFromDataSet(dataSet,fOffGameStatDetail.fReceivingTDYardageBuckets,
		"ReceivingTD");

	/* Misc Offense */
	readYardageFromDataSet(dataSet,fOffGameStatDetail.fKickReturnTDYardageBuckets,
		"KickReturnTD");
	readYardageFromDataSet(dataSet,fOffGameStatDetail.fMiscTDYardageBuckets,"MiscTD");
	
	/* Kicking Stats */
	fOffGameStatDetail.fPATsAttempted = (byte)dataSet.FieldByName("PATsAttempted")->AsInteger;
	fOffGameStatDetail.fPATsMade = (byte)dataSet.FieldByName("PATsMade")->AsInteger;
	fOffGameStatDetail.fFieldGoalsAttempted = (byte)dataSet.FieldByName("FieldGoalsAttempted")->AsInteger;
	
	readYardageFromDataSet(dataSet,fOffGameStatDetail.fFieldGoalYardageBuckets,
		"FieldGoal");
}

/******************************************************************************/

void TFootballOffGameStat::writeYardageToDataSet(TDataSet& dataSet,
	const YardageBuckets& yardageBuckets,const char* subFieldName,int maxItems)
{
	CStr31 fieldName;
	int i,numItems;
	
	numItems = yardageBuckets.numBuckets();
	
	fieldName.CopyVarg("Num%sBucs",subFieldName);
	dataSet.FieldByName(fieldName.c_str())->AsInteger = numItems;
	
	for(i = 0; i < maxItems; i++)
	{
		fieldName.CopyVarg("%sBuc%02d",subFieldName,i + 1);

		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numItems) ? yardageBuckets.getBucket(i) : 0;
	}
}

/******************************************************************************/

void TFootballOffGameStat::writeToDataSet(TDataSet& dataSet)
{
	TOffGameStat::writeToDataSet(dataSet);

	/* Passing Stats */
	dataSet.FieldByName("PassingYards")->AsInteger =
		fOffGameStatDetail.fPassingYards;
	dataSet.FieldByName("Interceptions")->AsInteger =
		fOffGameStatDetail.fInterceptions;
	dataSet.FieldByName("TwoPointPasses")->AsInteger =
		fOffGameStatDetail.fTwoPointPasses;
	
	writeYardageToDataSet(dataSet,fOffGameStatDetail.fPassingTDYardageBuckets,
		"PassingTD",MaxPassingTDBucs);
	
	/* Rushing Stats */
	dataSet.FieldByName("RushingYards")->AsInteger =
		fOffGameStatDetail.fRushingYards;
	dataSet.FieldByName("Fumbles")->AsInteger =
		fOffGameStatDetail.fFumbles;
	dataSet.FieldByName("TwoPointRushes")->AsInteger =
		fOffGameStatDetail.fTwoPointRushes;

	writeYardageToDataSet(dataSet,fOffGameStatDetail.fRushingTDYardageBuckets,
		"RushingTD",MaxRushingTDBucs);
	
	/* Receiving Stats */
	dataSet.FieldByName("ReceivingYards")->AsInteger =
		fOffGameStatDetail.fReceivingYards;
	dataSet.FieldByName("TwoPointReceptions")->AsInteger =
		fOffGameStatDetail.fTwoPointReceptions;

	writeYardageToDataSet(dataSet,fOffGameStatDetail.fReceivingTDYardageBuckets,
		"ReceivingTD",MaxReceivingTDBucs);
	
	/* Misc Stats */
	writeYardageToDataSet(dataSet,fOffGameStatDetail.fKickReturnTDYardageBuckets,
		"KickReturnTD",MaxKickReturnTDBucs);
	writeYardageToDataSet(dataSet,fOffGameStatDetail.fMiscTDYardageBuckets,
		"MiscTD",MaxMiscTDBucs);
	
	/* Kicking Stats */
	dataSet.FieldByName("PATsAttempted")->AsInteger =
		fOffGameStatDetail.fPATsAttempted;
	dataSet.FieldByName("PATsMade")->AsInteger = fOffGameStatDetail.fPATsMade;
	dataSet.FieldByName("FieldGoalsAttempted")->AsInteger =
		fOffGameStatDetail.fFieldGoalsAttempted;
	
	writeYardageToDataSet(dataSet,fOffGameStatDetail.fFieldGoalYardageBuckets,
		"FieldGoal",MaxFieldGoalBucs);
}

/******************************************************************************/

void TFootballOffGameStat::validateForUpdate()
{
	TOffGameStat::validateForUpdate();
}

/******************************************************************************/
/******************************************************************************/

void TFootballDefGameStat::clear()
{
	TDefGameStat::clear();

	fDefGameStatDetail.clear();
}

/******************************************************************************/

double TFootballDefGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);
		
	return(fDefGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 TFootballDefGameStat::getDefaultStatStr(int playerStatType)
{
	return("0000");
}

/******************************************************************************/

CStr31 TFootballDefGameStat::getStatStr(int playerStatType)
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
	
void TFootballDefGameStat::sumStats(const TDefGameStatPtr defGameStatPtr)
{
	fTotalPoints +=
		TFootballDefGameStatPtr(defGameStatPtr)->getTotalPoints();

	fDefGameStatDetail.sumStats(
		TFootballDefGameStatPtr(defGameStatPtr)->defGameStatDetail());
}

/******************************************************************************/
	
void TFootballDefGameStat::readFromDataSet(TDataSet& dataSet)
{
	TDefGameStat::readFromDataSet(dataSet);

	fDefGameStatDetail.fPassingYardsAllowed =
		(short)dataSet.FieldByName("PassingYardsAllowed")->AsInteger;
	fDefGameStatDetail.fRushingYardsAllowed =
		(short)dataSet.FieldByName("RushingYardsAllowed")->AsInteger;
		
	fDefGameStatDetail.fSafeties =
		(byte)dataSet.FieldByName("Safeties")->AsInteger;
	fDefGameStatDetail.fSacks =
		(byte)dataSet.FieldByName("Sacks")->AsInteger;
	fDefGameStatDetail.fBlockedKicks =
		(byte)dataSet.FieldByName("BlockedKicks")->AsInteger;
		
	fDefGameStatDetail.fFumblesRecovered =
		(byte)dataSet.FieldByName("FumblesRecovered")->AsInteger;
	fDefGameStatDetail.fInterceptions =
		(byte)dataSet.FieldByName("Interceptions")->AsInteger;
	fDefGameStatDetail.fDefensiveTDs =
		(byte)dataSet.FieldByName("DefensiveTDs")->AsInteger;
}

/******************************************************************************/

void TFootballDefGameStat::writeToDataSet(TDataSet& dataSet)
{
	TDefGameStat::writeToDataSet(dataSet);
	
	dataSet.FieldByName("PassingYardsAllowed")->AsInteger =
		fDefGameStatDetail.fPassingYardsAllowed;
	dataSet.FieldByName("RushingYardsAllowed")->AsInteger =
		fDefGameStatDetail.fRushingYardsAllowed;
		
	dataSet.FieldByName("Safeties")->AsInteger = fDefGameStatDetail.fSafeties;
	dataSet.FieldByName("Sacks")->AsInteger = fDefGameStatDetail.fSacks;
	dataSet.FieldByName("BlockedKicks")->AsInteger = fDefGameStatDetail.fBlockedKicks;
	
	dataSet.FieldByName("FumblesRecovered")->AsInteger =
		fDefGameStatDetail.fFumblesRecovered;
	dataSet.FieldByName("Interceptions")->AsInteger =
		fDefGameStatDetail.fInterceptions;
	dataSet.FieldByName("DefensiveTDs")->AsInteger =
		fDefGameStatDetail.fDefensiveTDs;
}

/******************************************************************************/

void TFootballDefGameStat::validateForUpdate()
{
	TDefGameStat::validateForUpdate();
}

/******************************************************************************/
/******************************************************************************/

TProfTeamID TProfTeamGame::getOppTeamID(TProfTeamID teamID) const
{
	if(teamID == fHomeTeamID)
		return(fVisitTeamID);
		
	if(teamID == fVisitTeamID)
		return(fHomeTeamID);
		
	throw ASIException("TProfTeamGame::getOppTeamID: teamID not in game");
}

/******************************************************************************/
/******************************************************************************/

void TFootballProfTeamSchedule::clear()
{
	TQueryDataSetRecord::clear();

	fProfGameWeek = TProfGameWeek();
	
	fProfTeamGameVector.erase(fProfTeamGameVector.begin(),
		fProfTeamGameVector.end());
}

/******************************************************************************/

TDateTime TFootballProfTeamSchedule::findEarliestGameDate() const
{
#if 1	//BOB
	if(fProfTeamGameVector.size() > 0)
		return(fProfTeamGameVector[0].getGameDate());

	throw ASIException("TFootballProfTeamSchedule::findEarliestGameDate: date not found");
#else
	TDateTime earliestGameDate(2020,12,31);		//BOB is there a max date value
	TProfTeamGameVector::const_iterator iter;
	bool dateFound = false;

	for(iter = fProfTeamGameVector.begin(); iter != fProfTeamGameVector.end();
		iter++)
	{
		const TProfTeamGame& profTeamGame = *iter;

		if(profTeamGame.getGameDate() < earliestGameDate)
		{
			earliestGameDate = profTeamGame.getGameDate();
			dateFound = true;
		}
	}

	if(!dateFound)
		throw ASIException("TFootballProfTeamSchedule::findEarliestGameDate: date not found");
	return(earliestGameDate);
#endif
}

/******************************************************************************/

TDateTime TFootballProfTeamSchedule::findEarliestGameTime() const
{
	if(fProfTeamGameVector.size() > 0)
		return(fProfTeamGameVector[0].getGameTime());

	throw ASIException("TFootballProfTeamSchedule::findEarliestGameTime: date not found");
}

/******************************************************************************/

TDateTime TFootballProfTeamSchedule::findLatestGameDate() const
{
#if 1	//BOB
	int numGames = fProfTeamGameVector.size();

	if(numGames > 0)
		return(fProfTeamGameVector[numGames - 1].getGameDate());

	throw ASIException("TFootballProfTeamSchedule::findLatestGameDate: date not found");
#else
	TDateTime latestGameDate(1000,1,1);		//BOB is there a min date value
	TProfTeamGameVector::const_iterator iter;
	bool dateFound = false;

	for(iter = fProfTeamGameVector.begin(); iter != fProfTeamGameVector.end();
		iter++)
	{
		const TProfTeamGame& profTeamGame = *iter;

		if(profTeamGame.getGameDate() > latestGameDate)
		{
			latestGameDate = profTeamGame.getGameDate();
			dateFound = true;
		}
	}

	if(!dateFound)
		throw ASIException("TFootballProfTeamSchedule::findLatestGameDate: date not found");
	return(latestGameDate);
#endif
}

/******************************************************************************/

bool TFootballProfTeamSchedule::anyGamesForDate(const TDateTime gameDate)
{
	TProfTeamGameVector::const_iterator iter;

	for(iter = fProfTeamGameVector.begin(); iter != fProfTeamGameVector.end();
		iter++)
	{
		const TProfTeamGame& profTeamGame = *iter;

		if(profTeamGame.getGameDate() == gameDate)
			return(true);
	}

	return(false);
}

/******************************************************************************/

bool TFootballProfTeamSchedule::getProfTeamGameByProfTeamID(TProfTeamID profTeamID,
	TProfTeamGame& profTeamGame) const
{
	TProfTeamGameVector::const_iterator iter;
	
	for(iter = fProfTeamGameVector.begin(); iter !=
		fProfTeamGameVector.end(); iter++)
	{
		const TProfTeamGame& game = *iter;

		if((game.getVisitTeamID() == profTeamID) ||
			(game.getHomeTeamID() == profTeamID))
		{
			profTeamGame = game;
			return(true);
		}
	}

	return(false);
}

/******************************************************************************/

TFootballProfTeamSchedulePtr TFootballProfTeamSchedule::newInstance()
{
	TFootballProfTeamSchedulePtr footballProfTeamSchedulePtr =
		ASFootballObjectBuilder::getThe().newFootballProfTeamSchedule();
	footballProfTeamSchedulePtr->clear();
	return(footballProfTeamSchedulePtr);
}

/******************************************************************************/
	
void TFootballProfTeamSchedule::readFromDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	CStr31 fieldNamePrefix; 
	int i,numGames;
	TProfTeamGame profTeamGame;
	
	fProfGameWeek = (short)dataSet.FieldByName("ProfGameWeek")->AsInteger;
	
	fieldNamePrefix.Copy("SchedGame");
	
	/* fProfTeamGameVector */
	numGames = dataSet.FieldByName("NumScheduleGames")->AsInteger;

	fProfTeamGameVector.erase(fProfTeamGameVector.begin(),
		fProfTeamGameVector.end());
	
	for(i = 0; i < numGames; i++)
	{
		profTeamGame.clear();
		
		if(i == 0)
		{
			fieldName.CopyVarg("%s%02dDateTime",fieldNamePrefix.c_str(),i + 1);
			profTeamGame.setGameTime(GetTimeOnly(DataSetReadDateTime(dataSet,fieldName)));
		}
		else
			fieldName.CopyVarg("%s%02dDate",fieldNamePrefix.c_str(),i + 1);
		profTeamGame.setGameDate(GetDateOnly(DataSetReadDateTime(dataSet,fieldName)));
		
		fieldName.CopyVarg("%s%02dVisitProfTeamID",fieldNamePrefix.c_str(),i + 1);
		profTeamGame.setVisitTeamID(
			dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fieldName.CopyVarg("%s%02dHomeProfTeamID",fieldNamePrefix.c_str(),i + 1);
		profTeamGame.setHomeTeamID(
			dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fieldName.CopyVarg("%s%02dVisitScore",fieldNamePrefix.c_str(),i + 1);
		profTeamGame.setVisitScore(
			(byte)dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fieldName.CopyVarg("%s%02dHomeScore",fieldNamePrefix.c_str(),i + 1);
		profTeamGame.setHomeScore(
			(byte)dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fProfTeamGameVector.push_back(profTeamGame);
	}

	validateGameVector();
}

/******************************************************************************/

void TFootballProfTeamSchedule::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	CStr31 fieldNamePrefix; 
	int i,numGames;
	TProfTeamGame profTeamGame;
	
	dataSet.FieldByName("ProfGameWeek")->AsInteger = fProfGameWeek.getID();

	fieldNamePrefix.Copy("SchedGame");

	/* fProfTeamGameVector */
	numGames = fProfTeamGameVector.size();

	dataSet.FieldByName("NumScheduleGames")->AsInteger = numGames;

	for(i = 0; i < MaxNFLGamesPerDay; i++)
	{
		if(i < numGames)
			profTeamGame = fProfTeamGameVector[i];
		else
			profTeamGame.clear();

		if(i == 0)
		{
			fieldName.CopyVarg("%s%02dDateTime",fieldNamePrefix.c_str(),i + 1);
			DataSetWriteDateTime(dataSet,fieldName,profTeamGame.getGameDate() + 
				profTeamGame.getGameTime());
		}
		else
		{
			fieldName.CopyVarg("%s%02dDate",fieldNamePrefix.c_str(),i + 1);
			DataSetWriteDateTime(dataSet,fieldName,profTeamGame.getGameDate());
		}

		fieldName.CopyVarg("%s%02dVisitProfTeamID",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			profTeamGame.getVisitTeamID().getID();
			
		fieldName.CopyVarg("%s%02dHomeProfTeamID",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			profTeamGame.getHomeTeamID().getID();
		
		fieldName.CopyVarg("%s%02dVisitScore",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			profTeamGame.getVisitScore();
		
		fieldName.CopyVarg("%s%02dHomeScore",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			profTeamGame.getHomeScore();
	}
}

/******************************************************************************/

void TFootballProfTeamSchedule::validateGameVector()
{
	TProfTeamGame profTeamGame;
	TDateTime gameDate;
	int i,numGames;

	numGames = fProfTeamGameVector.size();

	// Verify Time is set for first game.
	if(numGames > 0)
	{
		if(fProfTeamGameVector[0].getGameTime() == TDateTime())
			throw ASIException("TFootballProfTeamSchedule::validateGameVector: game 1 time not set");
	}

	for(i = 0; i < numGames; i++)
	{
		profTeamGame = fProfTeamGameVector[i];

		if(profTeamGame.getGameDate() < gameDate)
			throw ASIException("TFootballProfTeamSchedule::validateGameVector: game dates not increasing");
		gameDate = profTeamGame.getGameDate();
	}
}

/******************************************************************************/

void TFootballProfTeamSchedule::validateForUpdate()
{
	if(fProfGameWeek.isUndefined())
		throw ASIException("TFootballProfTeamSchedule::validateForUpdate: fProfGameWeek.isUndefined()");

	validateGameVector();
}

/******************************************************************************/

CStrVar TFootballProfTeamSchedule::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(ProfGameWeek = \"%s\")",fProfGameWeek.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

TFootballProfTeamSchedulePtr TFootballProfTeamScheduleVector::findByContainsGameDate(
	TDateTime gameDate,CommonAccessMode getMode)
{
	TFootballProfTeamScheduleVector::iterator iter;
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;

	for(iter = begin(); iter != end(); iter++)
	{
		profTeamSchedulePtr = *iter;

		if((gameDate >= profTeamSchedulePtr->findEarliestGameDate()) &&
				(gameDate <= profTeamSchedulePtr->findLatestGameDate()))
			return(profTeamSchedulePtr);
	}

	if(getMode == cam_MustExist)
		throw ASIException("TFootballProfTeamScheduleVector::findByContainsGameDate: gameDate not found");

	return(TFootballProfTeamSchedulePtr());
}

/******************************************************************************/

/* Based on today's date and NightlyProcessingTime, determines the current
	ProfTeamSchedule record. */

TFootballProfTeamSchedulePtr TFootballProfTeamScheduleVector::findCurrentAsOfToday(
	CommonAccessMode getMode)
{
	TDateTime today = TDateTime::CurrentDate();
	TFootballProfTeamScheduleVector::iterator iter;
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;
	TFootballProfTeamSchedulePtr lastProfTeamSchedulePtr;

	for(iter = begin(); iter != end(); iter++)
	{
		profTeamSchedulePtr = *iter;

		if((today >= profTeamSchedulePtr->findEarliestGameDate()) &&
				(today <= profTeamSchedulePtr->findLatestGameDate()))
			return(profTeamSchedulePtr);
		if((today == profTeamSchedulePtr->findLatestGameDate() + 1) &&
				(TDateTime::CurrentTime() < NightlyProcessingTime()))
			return(profTeamSchedulePtr);

		if(today < profTeamSchedulePtr->findEarliestGameDate())
		{
			if(lastProfTeamSchedulePtr.isNull())
				lastProfTeamSchedulePtr = profTeamSchedulePtr;

			// Take earist ProfWeek that has not ended.
			else if(profTeamSchedulePtr->getProfGameWeek() < 
					lastProfTeamSchedulePtr->getProfGameWeek())
				lastProfTeamSchedulePtr = profTeamSchedulePtr;
		}
	}

	if(lastProfTeamSchedulePtr.isNull() && (getMode == cam_MustExist))
		throw ASIException("TFootballProfTeamScheduleVector::findCurrentAsOfToday: not found");

	return(lastProfTeamSchedulePtr);
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
