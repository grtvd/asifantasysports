/* ASBaseballType.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballType.h"

namespace asbaseball
{

// Template code is not being include.
TPositionVector gUnusedPositionVector;

/******************************************************************************/
/******************************************************************************/

TBaseballPosition::TBaseballPosition(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "1B")
		fT = pos_FirstBaseman;
	else if(value == "2B")
		fT = pos_SecondBaseman;
	else if(value == "SS")
		fT = pos_ShortStop;
	else if(value == "3B")
		fT = pos_ThirdBaseman;
	else if(value == "C")
		fT = pos_Catcher;
	else if(value == "OF")
		fT = pos_Outfielder;
	else if(value == "DH")
		fT = pos_DesignatedHitter;
	else if(value == "SP")
		fT = pos_StartingPitcher;
	else if(value == "RP")
		fT = pos_ReliefPitcher;

	// Non-Participating Player Positions

	else
		throw ASIException("TBaseballPosition::TBaseballPosition: invalid "
			"str(%s)",str);
}

/******************************************************************************/

const char* TBaseballPosition::c_str() const
{
	switch(fT)
	{
		case pos_FirstBaseman:
			return("1B");
		case pos_SecondBaseman:
			return("2B");
		case pos_ShortStop:
			return("SS");
		case pos_ThirdBaseman:
			return("3B");
		case pos_Catcher:
			return("C");
		case pos_Outfielder:
			return("OF");
		case pos_DesignatedHitter:
			return("DH");
		case pos_StartingPitcher:
			return("SP");
		case pos_ReliefPitcher:
			return("RP");
			
		// Non-Participating Player Positions

		default:
			break;
	};

	throw ASIException("TBaseballPosition::c_str: invalid fT(%d)",(int)fT);
}

/******************************************************************************/

bool TBaseballPosition::isKey() const
{
	if(isUndefined())
		throw ASIException("TBaseballPosition::isKey: invalid fT(%d)",(int)fT);

	return(fT <= pos_ThirdBaseman);
}

/******************************************************************************/

bool TBaseballPosition::isOffensive() const
{
	if(isUndefined())
		throw ASIException("TBaseballPosition::isOffensive: invalid fT(%d)",(int)fT);

	if((fT == pos_StartingPitcher) || (fT == pos_ReliefPitcher))
		return(false);

	return(true);
}

/******************************************************************************/

void asfantasy::loadKeyPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = asbaseball::pos_FirstBaseman; i <= asbaseball::pos_LastKeyPos; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadAllPositionVector(TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	for(int i = asbaseball::pos_FirstBaseman; i <= asbaseball::pos_Last; i++)
		posVector.push_back(i);
}

/******************************************************************************/

void asfantasy::loadDefaultLineupPositionVector(const TLineup lineup,
	TPositionVector& posVector)
{
	posVector.erase(posVector.begin(),posVector.end());
	
	if(lineup == asbaseball::lut_Batter)
	{
		posVector.push_back(asbaseball::pos_FirstBaseman);
		posVector.push_back(asbaseball::pos_SecondBaseman);
		posVector.push_back(asbaseball::pos_ShortStop);
		posVector.push_back(asbaseball::pos_ThirdBaseman);
		posVector.push_back(asbaseball::pos_Catcher);
		posVector.push_back(asbaseball::pos_Outfielder);
		posVector.push_back(asbaseball::pos_Outfielder);
		posVector.push_back(asbaseball::pos_Outfielder);
		posVector.push_back(asbaseball::pos_DesignatedHitter);
	}
	else if(lineup == asbaseball::lut_Pitcher)
	{
		posVector.push_back(asbaseball::pos_StartingPitcher);
		posVector.push_back(asbaseball::pos_StartingPitcher);
		posVector.push_back(asbaseball::pos_StartingPitcher);
		posVector.push_back(asbaseball::pos_StartingPitcher);
		posVector.push_back(asbaseball::pos_StartingPitcher);
		posVector.push_back(asbaseball::pos_ReliefPitcher);
		posVector.push_back(asbaseball::pos_ReliefPitcher);
		posVector.push_back(asbaseball::pos_ReliefPitcher);
		posVector.push_back(asbaseball::pos_ReliefPitcher);
	}
}

/******************************************************************************/

CStrVar asfantasy::convertPositionToString(int position)
{
	asbaseball::TBaseballPosition baseballPosition(position);

	return(baseballPosition.c_str());
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

void TBaseballTeam::clear()
{
	TTeam::clear();
	
	fBatterLineup.erase(fBatterLineup.begin(),fBatterLineup.end());
	fPitcherLineup.erase(fPitcherLineup.begin(),fPitcherLineup.end());
}

/******************************************************************************/

const TPlayerIDVector& TBaseballTeam::lineupConst(TLineup lineup) const
{
	if(lineup == lut_Batter)
		return(fBatterLineup);

	if(lineup == lut_Pitcher)
		return(fPitcherLineup);

	throw ASIException("TBaseballTeam::lineup: invalid lineup");
}

/******************************************************************************/

TPlayerIDVector& TBaseballTeam::lineup(TLineup lineup)
{
	setHasChanged();

	if(lineup == lut_Batter)
		return(fBatterLineup);

	if(lineup == lut_Pitcher)
		return(fPitcherLineup);

	throw ASIException("TBaseballTeam::lineup: invalid lineup");
}

/******************************************************************************/

void TBaseballTeam::readFromDataSet(TDataSet& dataSet)
{
	TTeam::readFromDataSet(dataSet);
	
	readLineupFromDataSet(dataSet,lut_Batter,"Batter");
	readLineupFromDataSet(dataSet,lut_Pitcher,"Pitcher");
}

/******************************************************************************/

void TBaseballTeam::writeToDataSet(TDataSet& dataSet)
{
	TTeam::writeToDataSet(dataSet);
	
	writeLineupToDataSet(dataSet,lut_Batter,"Batter");
	writeLineupToDataSet(dataSet,lut_Pitcher,"Pitcher");
}

/******************************************************************************/
/******************************************************************************/

void TBaseballProfPlayer::clear()
{
	TProfPlayer::clear();
	
	fPositionPrimary.clear();
	fPositionSecondary.clear();

	fRosterStatus.clear();
}

/******************************************************************************/
	
void TBaseballProfPlayer::readFromDataSet(TDataSet& dataSet)
{
	TProfPlayer::readFromDataSet(dataSet);
	
	fPositionPrimary = dataSet.FieldByName("PosPrimary")->AsString.c_str();
	if(dataSet.FieldByName("PosSecondary")->IsNull)
		fPositionSecondary.clear();
	else
		fPositionSecondary = dataSet.FieldByName("PosSecondary")->AsString.c_str();

	fRosterStatus = dataSet.FieldByName("RosterStatus")->AsString.c_str();
}

/******************************************************************************/

void TBaseballProfPlayer::writeToDataSet(TDataSet& dataSet)
{
	TProfPlayer::writeToDataSet(dataSet);
	
	dataSet.FieldByName("PosPrimary")->AsString = fPositionPrimary.c_str();
	if(fPositionSecondary.isUndefined())
		dataSet.FieldByName("PosSecondary")->Clear();
	else
		dataSet.FieldByName("PosSecondary")->AsString = fPositionSecondary.c_str();
	
	dataSet.FieldByName("RosterStatus")->AsString = fRosterStatus.c_str();
}

/******************************************************************************/

void TBaseballProfPlayer::validateForUpdate()
{
	TProfPlayer::validateForUpdate();

	if(fPositionPrimary.isUndefined())
		throw ASIException("TBaseballProfPlayer::validateForUpdate: fPosition.isUndefined()");
		
	if(fRosterStatus.isUndefined())
		throw ASIException("TBaseballProfPlayer::validateForUpdate: fRosterStatus.isUndefined()");
}

/******************************************************************************/
/******************************************************************************/

void TOffGameStatDetail::clear()
{
	fGamesPlayed = 0;
	fGamesStarted = 0;
	fAtBats = 0;

	fSingles = 0;
	fDoubles = 0;
	fTriples = 0;

	fOneRunHomers = 0;
	fTwoRunHomers = 0;
	fThreeRunHomers = 0;
	fGrandSlams = 0;

	fRunsScored = 0;
	fRunsBattedIn = 0;
	fSacrificeHits = 0;
	fSacrificeFlies = 0;
	fHitByPicth = 0;
	fUnintentWalks = 0;
	fIntentWalks = 0;

	fStrikeouts = 0;
	fStolenBases = 0;
	fCaughtStealing = 0;
	fErrors = 0;
	fGroundedDoublePlay = 0;
	fHitForCycle = 0;
}

/******************************************************************************/

short TOffGameStatDetail::calcTotalPoints() const
{
	int totalPoints = 0;

	totalPoints += (fSingles * 1);
	totalPoints += (fDoubles * 2);
	totalPoints += (fTriples * 3);

	totalPoints += (fOneRunHomers * 4);
	totalPoints += (fTwoRunHomers * 6);
	totalPoints += (fThreeRunHomers * 8);
	totalPoints += (fGrandSlams * 10);

	totalPoints += (fRunsScored * 2);
	totalPoints += (fRunsBattedIn * 2);
	totalPoints += ((fSacrificeHits + fSacrificeFlies) * 1);
	totalPoints += (fHitByPicth * 1);
	totalPoints += ((fUnintentWalks + fIntentWalks) * 1);

	totalPoints -= (fStrikeouts * 1);
	totalPoints += (fStolenBases * 1);
	totalPoints -= (fCaughtStealing * 1);
	totalPoints -= (fErrors * 1);
	totalPoints -= (fGroundedDoublePlay * 1);
	totalPoints += (fHitForCycle * 10);

	return((short)totalPoints);
}

/******************************************************************************/

double TOffGameStatDetail::getStat(int playerStatType)
{
	TBaseballPlayerStatType baseballPlayerStatType(playerStatType);
	
	switch(baseballPlayerStatType)
	{
		case pst_GamesPlayed:
			return(fGamesPlayed);
		case pst_GamesStarted:
			return(fGamesStarted);
		case pst_Errors:
			return(fErrors);

		case pst_BattingAverage:
			if(fAtBats > 0.0)
				return((double)(fSingles + fDoubles + fTriples +
					fOneRunHomers +	fTwoRunHomers + fThreeRunHomers +
					fGrandSlams) / (double)fAtBats);
			return(0.0);

		case pst_AtBats:
			return(fAtBats);

		case pst_Hits:
			return(fSingles + fDoubles + fTriples + fOneRunHomers +
				fTwoRunHomers + fThreeRunHomers + fGrandSlams);
		case pst_Doubles:
			return(fDoubles);
		case pst_Triples:
			return(fTriples);

		case pst_OneRunHomers:
			return(fOneRunHomers);
		case pst_TwoRunHomers:
			return(fTwoRunHomers);
		case pst_ThreeRunHomers:
			return(fThreeRunHomers);
		case pst_GrandSlams:
			return(fGrandSlams);

		case pst_RunsScored:
			return(fRunsScored);
		case pst_RunsBattedIn:
			return(fRunsBattedIn);
		case pst_Sacrifices:
			return((double)fSacrificeHits + (double)fSacrificeFlies);
		case pst_HitByPicth:
			return(fHitByPicth);
		case pst_Walks:
			return((double)fUnintentWalks + (double)fIntentWalks);

		case pst_Strikeouts:
			return(fStrikeouts);
		case pst_StolenBases:
			return(fStolenBases);
		case pst_CaughtStealing:
			return(fCaughtStealing);
		case pst_GroundedDoublePlay:
			return(fGroundedDoublePlay);
		case pst_HitForCycle:
			return(fHitForCycle);

		default:
			break;
	}
	
	throw ASIException("TOffGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TOffGameStatDetail::sumStats(const TOffGameStatDetail& offGameStatDetail)
{
	fGamesPlayed += offGameStatDetail.fGamesPlayed;
	fGamesStarted += offGameStatDetail.fGamesStarted;
	fAtBats += offGameStatDetail.fAtBats;

	fSingles += offGameStatDetail.fSingles;
	fDoubles += offGameStatDetail.fDoubles;
	fTriples += offGameStatDetail.fTriples;

	fOneRunHomers += offGameStatDetail.fOneRunHomers;
	fTwoRunHomers += offGameStatDetail.fTwoRunHomers;
	fThreeRunHomers += offGameStatDetail.fThreeRunHomers;
	fGrandSlams += offGameStatDetail.fGrandSlams;

	fRunsScored += offGameStatDetail.fRunsScored;
	fRunsBattedIn += offGameStatDetail.fRunsBattedIn;
	fSacrificeHits += offGameStatDetail.fSacrificeHits;
	fSacrificeFlies += offGameStatDetail.fSacrificeFlies;
	fHitByPicth += offGameStatDetail.fHitByPicth;
	fUnintentWalks += offGameStatDetail.fUnintentWalks;
	fIntentWalks += offGameStatDetail.fIntentWalks;

	fStrikeouts += offGameStatDetail.fStrikeouts;
	fStolenBases += offGameStatDetail.fStolenBases;
	fCaughtStealing += offGameStatDetail.fCaughtStealing;
	fErrors += offGameStatDetail.fErrors;
	fGroundedDoublePlay += offGameStatDetail.fGroundedDoublePlay;
	fHitForCycle += offGameStatDetail.fHitForCycle;
}

/******************************************************************************/
/******************************************************************************/

void TDefGameStatDetail::clear()
{
	fWins = 0;
	fLosses = 0;
	fSaves = 0;
	fBlownSaves = 0;
	fHolds = 0;

	fGamesPlayed = 0;
	fGamesStarted = 0;

	fCompleteGames = 0;
	fGamesFinished = 0;
	fQualityStarts = 0;
	fShutouts = 0;
	fNoHitters = 0;
	fPerfectGames = 0;

	fOutsPitched = 0;
	fBattersFaced = 0;
	fSinglesAllowed = 0;
	fDoublesAllowed = 0;
	fTriplesAllowed = 0;

	fOneRunHomersAllowed = 0;
	fTwoRunHomersAllowed = 0;
	fThreeRunHomersAllowed = 0;
	fGrandSlamsAllowed = 0;

	fUnearnedRunsAllowed = 0;
	fEarnedRunsAllowed = 0;
	fSacrificeHitsAllowed = 0;
	fSacrificeFliesAllowed = 0;
	fHitBatsmen = 0;
	fUnintentWalkedBatsmen = 0;
	fIntentWalkedBatsmen = 0;
	fStruckoutBatsmen = 0;
	fWildPitches = 0;
	fBalks = 0;
	fErrors = 0;
}

/******************************************************************************/

short TDefGameStatDetail::calcTotalPoints() const
{
	int totalPoints = 0;

	totalPoints += (fWins * 10);
	totalPoints -= (fLosses * 10);
	totalPoints += (fSaves * 5);
	totalPoints += (fHolds * 5);

	totalPoints += (fCompleteGames * 10);
	totalPoints += (fShutouts * 10);
	totalPoints += (fNoHitters * 10);
	totalPoints += (fPerfectGames * 10);

	totalPoints += (fOutsPitched * 1);
	totalPoints -= (fSinglesAllowed * 1);
	totalPoints -= (fDoublesAllowed * 2);
	totalPoints -= (fTriplesAllowed * 3);

	totalPoints -= (fOneRunHomersAllowed * 4);
	totalPoints -= (fTwoRunHomersAllowed * 6);
	totalPoints -= (fThreeRunHomersAllowed * 8);
	totalPoints -= (fGrandSlamsAllowed * 10);

	totalPoints -= (fUnearnedRunsAllowed * 1);
	totalPoints -= (fEarnedRunsAllowed * 2);
	totalPoints -= ((fSacrificeHitsAllowed + fSacrificeFliesAllowed)* 1);
	totalPoints -= (fHitBatsmen * 1);
	totalPoints -= ((fUnintentWalkedBatsmen + fIntentWalkedBatsmen)* 1);
	totalPoints += (fStruckoutBatsmen * 1);
	totalPoints -= (fWildPitches * 1);
	totalPoints -= (fBalks * 1);
	totalPoints -= (fErrors * 1);

	return((short)totalPoints);
}

/******************************************************************************/

double TDefGameStatDetail::getStat(int playerStatType)
{
	TBaseballPlayerStatType baseballPlayerStatType(playerStatType);
	
	switch(baseballPlayerStatType)
	{
		case pst_GamesPlayed:
			return(fGamesPlayed);
		case pst_GamesStarted:
			return(fGamesStarted);
		case pst_Errors:
			return(fErrors);

		case pst_EarnedRunAverage:
			if(fOutsPitched > 0.0)
				return(((double)fEarnedRunsAllowed * 9.0) /
					((double)fOutsPitched / 3.0));
			return(0.0);

		case pst_Wins:
			return(fWins);
		case pst_Losses:
			return(fLosses);
		case pst_Saves:
			return(fSaves);

		case pst_InningsPitched:
			return((double)fOutsPitched / 3.0);
		case pst_HitsAllowed:
			return(fSinglesAllowed + fDoublesAllowed + fTriplesAllowed +
				fOneRunHomersAllowed + fTwoRunHomersAllowed +
				fThreeRunHomersAllowed + fGrandSlamsAllowed);
		case pst_DoublesAllowed:
			return(fDoublesAllowed);
		case pst_TriplesAllowed:
			return(fTriplesAllowed);

		case pst_OneRunHomersAllowed:
			return(fOneRunHomersAllowed);
		case pst_TwoRunHomersAllowed:
			return(fTwoRunHomersAllowed);
		case pst_ThreeRunHomersAllowed:
			return(fThreeRunHomersAllowed);
		case pst_GrandSlamsAllowed:
			return(fGrandSlamsAllowed);

		case pst_RunsAllowed:
			return(fUnearnedRunsAllowed + fEarnedRunsAllowed);
		case pst_EarnedRunsAllowed:
			return(fEarnedRunsAllowed);
		case pst_SacrificesAllowed:
			return((double)fSacrificeHitsAllowed + (double)fSacrificeFliesAllowed);
		case pst_HitBatsmen:
			return(fHitBatsmen);
		case pst_WalkedBatsmen:
			return((double)fUnintentWalkedBatsmen + (double)fIntentWalkedBatsmen);
		case pst_StruckoutBatsmen:
			return(fStruckoutBatsmen);
		case pst_WildPitches:
			return(fWildPitches);
		case pst_Balks:
			return(fBalks);
		case pst_CompleteGames:
			return(fCompleteGames);
		case pst_Shutouts:
			return(fShutouts);
		case pst_NoHitters:
			return(fNoHitters);
		case pst_PerfectGames:
			return(fPerfectGames);

		default:
			break;
	}
	
	throw ASIException("TDefGameStatDetail::getStat: unsupported playerStatType");
}

/******************************************************************************/

void TDefGameStatDetail::sumStats(const TDefGameStatDetail& defGameStatDetail)
{
	fWins += defGameStatDetail.fWins;
	fLosses += defGameStatDetail.fLosses;
	fSaves += defGameStatDetail.fSaves;
	fBlownSaves += defGameStatDetail.fBlownSaves;
	fHolds += defGameStatDetail.fHolds;

	fGamesPlayed += defGameStatDetail.fGamesPlayed;
	fGamesStarted += defGameStatDetail.fGamesStarted;

	fCompleteGames += defGameStatDetail.fCompleteGames;
	fGamesFinished += defGameStatDetail.fGamesFinished;
	fQualityStarts += defGameStatDetail.fQualityStarts;
	fShutouts += defGameStatDetail.fShutouts;
	fNoHitters += defGameStatDetail.fNoHitters;
	fPerfectGames += defGameStatDetail.fPerfectGames;

	fOutsPitched += defGameStatDetail.fOutsPitched;
	fBattersFaced += defGameStatDetail.fBattersFaced;
	fSinglesAllowed += defGameStatDetail.fSinglesAllowed;
	fDoublesAllowed += defGameStatDetail.fDoublesAllowed;
	fTriplesAllowed += defGameStatDetail.fTriplesAllowed;

	fOneRunHomersAllowed += defGameStatDetail.fOneRunHomersAllowed;
	fTwoRunHomersAllowed += defGameStatDetail.fTwoRunHomersAllowed;
	fThreeRunHomersAllowed += defGameStatDetail.fThreeRunHomersAllowed;
	fGrandSlamsAllowed += defGameStatDetail.fGrandSlamsAllowed;

	fUnearnedRunsAllowed += defGameStatDetail.fUnearnedRunsAllowed;
	fEarnedRunsAllowed += defGameStatDetail.fEarnedRunsAllowed;
	fSacrificeHitsAllowed += defGameStatDetail.fSacrificeHitsAllowed;
	fSacrificeFliesAllowed += defGameStatDetail.fSacrificeFliesAllowed;
	fHitBatsmen += defGameStatDetail.fHitBatsmen;
	fUnintentWalkedBatsmen += defGameStatDetail.fUnintentWalkedBatsmen;
	fIntentWalkedBatsmen += defGameStatDetail.fIntentWalkedBatsmen;
	fStruckoutBatsmen += defGameStatDetail.fStruckoutBatsmen;
	fWildPitches += defGameStatDetail.fWildPitches;
	fBalks += defGameStatDetail.fBalks;
	fErrors += defGameStatDetail.fErrors;
}

/******************************************************************************/
/******************************************************************************/

void TBaseballOffGameStat::clear()
{
	TOffGameStat::clear();

	fPosition.clear();

	fOffGameStatDetail.clear();
}

/******************************************************************************/

double TBaseballOffGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);
		
	return(fOffGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 TBaseballOffGameStat::getDefaultStatStr(int playerStatType)
{
	CStr31 str;

	if(playerStatType == pst_BattingAverage)
		str.Copy(" .000");
	else
		str.Copy("0000");

	return(str);
}

/******************************************************************************/

CStr31 TBaseballOffGameStat::getStatStr(int playerStatType)
{
	CStr31 str;
	double stat = getStat(playerStatType);

	if(playerStatType == pst_BattingAverage)
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

void TBaseballOffGameStat::sumStats(const TOffGameStatPtr offGameStatPtr)
{
	fTotalPoints += offGameStatPtr->getTotalPoints();

	fOffGameStatDetail.sumStats(
		TBaseballOffGameStatPtr(offGameStatPtr)->offGameStatDetail());
}

/******************************************************************************/
	
void TBaseballOffGameStat::readFromDataSet(TDataSet& dataSet)
{
	TOffGameStat::readFromDataSet(dataSet);
	
	if(dataSet.FieldByName("Pos")->IsNull)
		fPosition.clear();
	else
		fPosition = dataSet.FieldByName("Pos")->AsString.c_str();

	fOffGameStatDetail.fGamesPlayed = (short)dataSet.FieldByName("GamesPlayed")->AsInteger;
	fOffGameStatDetail.fGamesStarted = (short)dataSet.FieldByName("GamesStarted")->AsInteger;
	fOffGameStatDetail.fAtBats = (short)dataSet.FieldByName("AtBats")->AsInteger;

	fOffGameStatDetail.fSingles = (short)dataSet.FieldByName("Singles")->AsInteger;
	fOffGameStatDetail.fDoubles = (short)dataSet.FieldByName("Doubles")->AsInteger;
	fOffGameStatDetail.fTriples = (short)dataSet.FieldByName("Triples")->AsInteger;

	fOffGameStatDetail.fOneRunHomers = (short)dataSet.FieldByName("OneRunHomers")->AsInteger;
	fOffGameStatDetail.fTwoRunHomers = (short)dataSet.FieldByName("TwoRunHomers")->AsInteger;
	fOffGameStatDetail.fThreeRunHomers = (short)dataSet.FieldByName("ThreeRunHomers")->AsInteger;
	fOffGameStatDetail.fGrandSlams = (short)dataSet.FieldByName("GrandSlams")->AsInteger;

	fOffGameStatDetail.fRunsScored = (short)dataSet.FieldByName("RunsScored")->AsInteger;
	fOffGameStatDetail.fRunsBattedIn = (short)dataSet.FieldByName("RunsBattedIn")->AsInteger;
	fOffGameStatDetail.fSacrificeHits = (short)dataSet.FieldByName("SacrificeHits")->AsInteger;
	fOffGameStatDetail.fSacrificeFlies = (short)dataSet.FieldByName("SacrificeFlies")->AsInteger;
	fOffGameStatDetail.fHitByPicth = (short)dataSet.FieldByName("HitByPicth")->AsInteger;
	fOffGameStatDetail.fUnintentWalks = (short)dataSet.FieldByName("UnintentWalks")->AsInteger;
	fOffGameStatDetail.fIntentWalks = (short)dataSet.FieldByName("IntentWalks")->AsInteger;

	fOffGameStatDetail.fStrikeouts = (short)dataSet.FieldByName("Strikeouts")->AsInteger;
	fOffGameStatDetail.fStolenBases = (short)dataSet.FieldByName("StolenBases")->AsInteger;
	fOffGameStatDetail.fCaughtStealing = (short)dataSet.FieldByName("CaughtStealing")->AsInteger;
	fOffGameStatDetail.fErrors = (short)dataSet.FieldByName("Errors")->AsInteger;
	fOffGameStatDetail.fGroundedDoublePlay = (short)dataSet.FieldByName("GroundedDoublePlay")->AsInteger;
	fOffGameStatDetail.fHitForCycle = (short)dataSet.FieldByName("HitForCycle")->AsInteger;
}

/******************************************************************************/

void TBaseballOffGameStat::writeToDataSet(TDataSet& dataSet)
{
	TOffGameStat::writeToDataSet(dataSet);

	if(fPosition.isUndefined())
		dataSet.FieldByName("Pos")->Clear();
	else
		dataSet.FieldByName("Pos")->AsString = fPosition.c_str();

	dataSet.FieldByName("GamesPlayed")->AsInteger = fOffGameStatDetail.fGamesPlayed;
	dataSet.FieldByName("GamesStarted")->AsInteger = fOffGameStatDetail.fGamesStarted;
	dataSet.FieldByName("AtBats")->AsInteger = fOffGameStatDetail.fAtBats;

	dataSet.FieldByName("Singles")->AsInteger = fOffGameStatDetail.fSingles;
	dataSet.FieldByName("Doubles")->AsInteger = fOffGameStatDetail.fDoubles;
	dataSet.FieldByName("Triples")->AsInteger = fOffGameStatDetail.fTriples;

	dataSet.FieldByName("OneRunHomers")->AsInteger = fOffGameStatDetail.fOneRunHomers;
	dataSet.FieldByName("TwoRunHomers")->AsInteger = fOffGameStatDetail.fTwoRunHomers;
	dataSet.FieldByName("ThreeRunHomers")->AsInteger = fOffGameStatDetail.fThreeRunHomers;
	dataSet.FieldByName("GrandSlams")->AsInteger = fOffGameStatDetail.fGrandSlams;

	dataSet.FieldByName("RunsScored")->AsInteger = fOffGameStatDetail.fRunsScored;
	dataSet.FieldByName("RunsBattedIn")->AsInteger = fOffGameStatDetail.fRunsBattedIn;
	dataSet.FieldByName("SacrificeHits")->AsInteger = fOffGameStatDetail.fSacrificeHits;
	dataSet.FieldByName("SacrificeFlies")->AsInteger = fOffGameStatDetail.fSacrificeFlies;
	dataSet.FieldByName("HitByPicth")->AsInteger = fOffGameStatDetail.fHitByPicth;
	dataSet.FieldByName("UnintentWalks")->AsInteger = fOffGameStatDetail.fUnintentWalks;
	dataSet.FieldByName("IntentWalks")->AsInteger = fOffGameStatDetail.fIntentWalks;

	dataSet.FieldByName("Strikeouts")->AsInteger = fOffGameStatDetail.fStrikeouts;
	dataSet.FieldByName("StolenBases")->AsInteger = fOffGameStatDetail.fStolenBases;
	dataSet.FieldByName("CaughtStealing")->AsInteger = fOffGameStatDetail.fCaughtStealing;
	dataSet.FieldByName("Errors")->AsInteger = fOffGameStatDetail.fErrors;
	dataSet.FieldByName("GroundedDoublePlay")->AsInteger = fOffGameStatDetail.fGroundedDoublePlay;
	dataSet.FieldByName("HitForCycle")->AsInteger = fOffGameStatDetail.fHitForCycle;
}

/******************************************************************************/

void TBaseballOffGameStat::validateForUpdate()
{
	TOffGameStat::validateForUpdate();

	if((fStatPeriod == stp_SeasonGame) && fPosition.isUndefined())
		throw ASIException("TBaseballOffGameStat::validateForUpdate: (fStatPeriod == stp_SeasonGame) && fPosition.isUndefined()");

	if((fStatPeriod != stp_SeasonGame) && !fPosition.isUndefined())
		throw ASIException("TBaseballOffGameStat::validateForUpdate: (fStatPeriod != stp_SeasonGame) && !fPosition.isUndefined()");

	if(fStatPeriod == stp_SeasonGame)
	{
		if(fOffGameStatDetail.fGamesPlayed > 3)
			throw ASIException("TBaseballOffGameStat::validateForUpdate: fOffGameStatDetail.fGamesPlayed > 3");
		else if(fOffGameStatDetail.fGamesPlayed > 1)
			CommErrMsg(cel_Warning,"TBaseballOffGameStat::validateForUpdate: gamesPlayed(%d), double or triple header?",
				(int)fOffGameStatDetail.fGamesPlayed);
				
		if(fOffGameStatDetail.fGamesStarted > 3)
			throw ASIException("TBaseballOffGameStat::validateForUpdate: fOffGameStatDetail.fGamesStarted > 3");
		else if(fOffGameStatDetail.fGamesStarted > 1)
			CommErrMsg(cel_Warning,"TBaseballOffGameStat::validateForUpdate: gamesStarted(%d), double or triple header?",
				(int)fOffGameStatDetail.fGamesStarted);
	}
}

/******************************************************************************/
/******************************************************************************/

void TBaseballDefGameStat::clear()
{
	TDefGameStat::clear();
	
	fPosition.clear();

	fDefGameStatDetail.clear();
}

/******************************************************************************/

double TBaseballDefGameStat::getStat(int playerStatType)
{
	if(playerStatType == pst_TotalPoints)
		return(fTotalPoints);
		
	return(fDefGameStatDetail.getStat(playerStatType));
}

/******************************************************************************/

CStr31 TBaseballDefGameStat::getDefaultStatStr(int playerStatType)
{
	CStr31 str;

	if(playerStatType == pst_EarnedRunAverage)
		str.Copy(" 0.00");
	else
		str.Copy("0000");

	return(str);
}

/******************************************************************************/

CStr31 TBaseballDefGameStat::getStatStr(int playerStatType)
{
	CStr31 str;
	double stat = getStat(playerStatType);

	if(playerStatType == pst_EarnedRunAverage)
		str.CopyVarg("%5.2lf",stat);
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
	
void TBaseballDefGameStat::sumStats(const TDefGameStatPtr defGameStatPtr)
{
	fTotalPoints += defGameStatPtr->getTotalPoints();

	fDefGameStatDetail.sumStats(
		TBaseballDefGameStatPtr(defGameStatPtr)->defGameStatDetail());
}

/******************************************************************************/
	
void TBaseballDefGameStat::readFromDataSet(TDataSet& dataSet)
{
	TDefGameStat::readFromDataSet(dataSet);

	if(dataSet.FieldByName("Pos")->IsNull)
		fPosition.clear();
	else
		fPosition = dataSet.FieldByName("Pos")->AsString.c_str();

	fDefGameStatDetail.fWins = (short)dataSet.FieldByName("Wins")->AsInteger;
	fDefGameStatDetail.fLosses = (short)dataSet.FieldByName("Losses")->AsInteger;
	fDefGameStatDetail.fSaves = (short)dataSet.FieldByName("Saves")->AsInteger;
	fDefGameStatDetail.fBlownSaves = (short)dataSet.FieldByName("BlownSaves")->AsInteger;
	fDefGameStatDetail.fHolds = (short)dataSet.FieldByName("Holds")->AsInteger;

	fDefGameStatDetail.fGamesPlayed = (short)dataSet.FieldByName("GamesPlayed")->AsInteger;
	fDefGameStatDetail.fGamesStarted = (short)dataSet.FieldByName("GamesStarted")->AsInteger;

	fDefGameStatDetail.fCompleteGames = (short)dataSet.FieldByName("CompleteGames")->AsInteger;
	fDefGameStatDetail.fGamesFinished = (short)dataSet.FieldByName("GamesFinished")->AsInteger;
	fDefGameStatDetail.fQualityStarts = (short)dataSet.FieldByName("QualityStarts")->AsInteger;
	fDefGameStatDetail.fShutouts = (short)dataSet.FieldByName("Shutouts")->AsInteger;
	fDefGameStatDetail.fNoHitters = (short)dataSet.FieldByName("NoHitters")->AsInteger;
	fDefGameStatDetail.fPerfectGames = (short)dataSet.FieldByName("PerfectGames")->AsInteger;

	fDefGameStatDetail.fOutsPitched = (short)dataSet.FieldByName("OutsPitched")->AsInteger;
	fDefGameStatDetail.fBattersFaced = (short)dataSet.FieldByName("BattersFaced")->AsInteger;
	fDefGameStatDetail.fSinglesAllowed = (short)dataSet.FieldByName("SinglesAllowed")->AsInteger;
	fDefGameStatDetail.fDoublesAllowed = (short)dataSet.FieldByName("DoublesAllowed")->AsInteger;
	fDefGameStatDetail.fTriplesAllowed = (short)dataSet.FieldByName("TriplesAllowed")->AsInteger;

	fDefGameStatDetail.fOneRunHomersAllowed = (short)dataSet.FieldByName("OneRunHomersAllowed")->AsInteger;
	fDefGameStatDetail.fTwoRunHomersAllowed = (short)dataSet.FieldByName("TwoRunHomersAllowed")->AsInteger;
	fDefGameStatDetail.fThreeRunHomersAllowed = (short)dataSet.FieldByName("ThreeRunHomersAllowed")->AsInteger;
	fDefGameStatDetail.fGrandSlamsAllowed = (short)dataSet.FieldByName("GrandSlamsAllowed")->AsInteger;

	fDefGameStatDetail.fUnearnedRunsAllowed = (short)dataSet.FieldByName("UnearnedRunsAllowed")->AsInteger;
	fDefGameStatDetail.fEarnedRunsAllowed = (short)dataSet.FieldByName("EarnedRunsAllowed")->AsInteger;
	fDefGameStatDetail.fSacrificeHitsAllowed = (short)dataSet.FieldByName("SacrificeHitsAllowed")->AsInteger;
	fDefGameStatDetail.fSacrificeFliesAllowed = (short)dataSet.FieldByName("SacrificeFliesAllowed")->AsInteger;
	fDefGameStatDetail.fHitBatsmen = (short)dataSet.FieldByName("HitBatsmen")->AsInteger;
	fDefGameStatDetail.fUnintentWalkedBatsmen = (short)dataSet.FieldByName("UnintentWalkedBatsmen")->AsInteger;
	fDefGameStatDetail.fIntentWalkedBatsmen = (short)dataSet.FieldByName("IntentWalkedBatsmen")->AsInteger;
	fDefGameStatDetail.fStruckoutBatsmen = (short)dataSet.FieldByName("StruckoutBatsmen")->AsInteger;
	fDefGameStatDetail.fWildPitches = (short)dataSet.FieldByName("WildPitches")->AsInteger;
	fDefGameStatDetail.fBalks = (short)dataSet.FieldByName("Balks")->AsInteger;
	fDefGameStatDetail.fErrors = (short)dataSet.FieldByName("Errors")->AsInteger;
}

/******************************************************************************/

void TBaseballDefGameStat::writeToDataSet(TDataSet& dataSet)
{
	TDefGameStat::writeToDataSet(dataSet);
	
	if(fPosition.isUndefined())
		dataSet.FieldByName("Pos")->Clear();
	else
		dataSet.FieldByName("Pos")->AsString = fPosition.c_str();

	dataSet.FieldByName("Wins")->AsInteger = fDefGameStatDetail.fWins;
	dataSet.FieldByName("Losses")->AsInteger = fDefGameStatDetail.fLosses;
	dataSet.FieldByName("Saves")->AsInteger = fDefGameStatDetail.fSaves;
	dataSet.FieldByName("BlownSaves")->AsInteger = fDefGameStatDetail.fBlownSaves;
	dataSet.FieldByName("Holds")->AsInteger = fDefGameStatDetail.fHolds;

	dataSet.FieldByName("GamesPlayed")->AsInteger = fDefGameStatDetail.fGamesPlayed;
	dataSet.FieldByName("GamesStarted")->AsInteger = fDefGameStatDetail.fGamesStarted;

	dataSet.FieldByName("CompleteGames")->AsInteger = fDefGameStatDetail.fCompleteGames;
	dataSet.FieldByName("GamesFinished")->AsInteger = fDefGameStatDetail.fGamesFinished;
	dataSet.FieldByName("QualityStarts")->AsInteger = fDefGameStatDetail.fQualityStarts;
	dataSet.FieldByName("Shutouts")->AsInteger = fDefGameStatDetail.fShutouts;
	dataSet.FieldByName("NoHitters")->AsInteger = fDefGameStatDetail.fNoHitters;
	dataSet.FieldByName("PerfectGames")->AsInteger = fDefGameStatDetail.fPerfectGames;

	dataSet.FieldByName("OutsPitched")->AsInteger = fDefGameStatDetail.fOutsPitched;
	dataSet.FieldByName("BattersFaced")->AsInteger = fDefGameStatDetail.fBattersFaced;
	dataSet.FieldByName("SinglesAllowed")->AsInteger = fDefGameStatDetail.fSinglesAllowed;
	dataSet.FieldByName("DoublesAllowed")->AsInteger = fDefGameStatDetail.fDoublesAllowed;
	dataSet.FieldByName("TriplesAllowed")->AsInteger = fDefGameStatDetail.fTriplesAllowed;

	dataSet.FieldByName("OneRunHomersAllowed")->AsInteger = fDefGameStatDetail.fOneRunHomersAllowed;
	dataSet.FieldByName("TwoRunHomersAllowed")->AsInteger = fDefGameStatDetail.fTwoRunHomersAllowed;
	dataSet.FieldByName("ThreeRunHomersAllowed")->AsInteger = fDefGameStatDetail.fThreeRunHomersAllowed;
	dataSet.FieldByName("GrandSlamsAllowed")->AsInteger = fDefGameStatDetail.fGrandSlamsAllowed;

	dataSet.FieldByName("UnearnedRunsAllowed")->AsInteger = fDefGameStatDetail.fUnearnedRunsAllowed;
	dataSet.FieldByName("EarnedRunsAllowed")->AsInteger = fDefGameStatDetail.fEarnedRunsAllowed;
	dataSet.FieldByName("SacrificeHitsAllowed")->AsInteger = fDefGameStatDetail.fSacrificeHitsAllowed;
	dataSet.FieldByName("SacrificeFliesAllowed")->AsInteger = fDefGameStatDetail.fSacrificeFliesAllowed;
	dataSet.FieldByName("HitBatsmen")->AsInteger = fDefGameStatDetail.fHitBatsmen;
	dataSet.FieldByName("UnintentWalkedBatsmen")->AsInteger = fDefGameStatDetail.fUnintentWalkedBatsmen;
	dataSet.FieldByName("IntentWalkedBatsmen")->AsInteger = fDefGameStatDetail.fIntentWalkedBatsmen;
	dataSet.FieldByName("StruckoutBatsmen")->AsInteger = fDefGameStatDetail.fStruckoutBatsmen;
	dataSet.FieldByName("WildPitches")->AsInteger = fDefGameStatDetail.fWildPitches;
	dataSet.FieldByName("Balks")->AsInteger = fDefGameStatDetail.fBalks;
	dataSet.FieldByName("Errors")->AsInteger = fDefGameStatDetail.fErrors;
}

/******************************************************************************/

void TBaseballDefGameStat::validateForUpdate()
{
	TDefGameStat::validateForUpdate();

	if((fStatPeriod == stp_SeasonGame) && fPosition.isUndefined())
		throw ASIException("TBaseballDefGameStat::validateForUpdate: (fStatPeriod == stp_SeasonGame) && fPosition.isUndefined()");

	if((fStatPeriod != stp_SeasonGame) && !fPosition.isUndefined())
		throw ASIException("TBaseballDefGameStat::validateForUpdate: (fStatPeriod != stp_SeasonGame) && !fPosition.isUndefined()");

	if(fStatPeriod == stp_SeasonGame)
	{
		if(fDefGameStatDetail.fGamesPlayed > 3)
			throw ASIException("TBaseballDefGameStat::validateForUpdate: fDeffGameStatDetail.fGamesPlayed > 3");
		else if(fDefGameStatDetail.fGamesPlayed > 1)
			CommErrMsg(cel_Warning,"TBaseballDefGameStat::validateForUpdate: gamesPlayed(%d), double or triple header?",
				(int)fDefGameStatDetail.fGamesPlayed);
			
		if(fDefGameStatDetail.fGamesStarted > 3)
			throw ASIException("TBaseballDefGameStat::validateForUpdate: fDefGameStatDetail.fGamesStarted > 3");
		else if(fDefGameStatDetail.fGamesStarted > 1)
			CommErrMsg(cel_Warning,"TBaseballDefGameStat::validateForUpdate: gamesStarted(%d), double or triple header?",
				(int)fDefGameStatDetail.fGamesStarted);
	}
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/

