/* ASFantasyType.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "CommDB.h"
#include "PipeTextFiler.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyType.h"
#include "ASFantasyObjectBuilder.h"

using namespace asfantasy;

/******************************************************************************/
/******************************************************************************/

void UnusedFunctionForTemplateCreatation()
{
	new TLeagueVector();
	new TTeamIDVector();
	new TPlayerDateIDVector();

	new TDraftPickVector();
	new TScheduleDayGameVector();
	new TOffGameStatVector();
	new TDefGameStatVector();
	new TScheduleDayVector();
	new TGameResultVector();
}

/******************************************************************************/
/******************************************************************************/

TPlayerStatID::TPlayerStatID(TPlayerID playerID,TStatPeriod statPeriod,
	TDateTime statDate)
{
	if((statPeriod == stp_SeasonGame) && (statDate == TDateTime()))
		throw ASIException("TPlayerStatID::TPlayerStatID: (statPeriod == stp_SeasonGame) && (statDate == TDateTime())");

	if((statPeriod != stp_SeasonGame) && (statDate != TDateTime()))
		throw ASIException("TPlayerStatID::TPlayerStatID: (statPeriod != stp_SeasonGame) && (statDate != TDateTime())");

	clear();
	
	fPlayerID = playerID;
	fStatPeriod = statPeriod;
	fStatDate = statDate;
}

/******************************************************************************/

bool TPlayerStatID::operator==(const TPlayerStatID& rhs) const
{
	if(fPlayerID != rhs.fPlayerID)
		return(false);

	if(fStatPeriod != rhs.fStatPeriod)
		return(false);

	if(fStatDate != rhs.fStatDate)
		return(false);

	return(true);
}

/******************************************************************************/

bool TPlayerStatID::operator<(const TPlayerStatID& rhs) const
{
	if(fPlayerID < rhs.fPlayerID)
		return(true);
	if(fPlayerID > rhs.fPlayerID)
		return(false);

	if(fStatPeriod < rhs.fStatPeriod)
		return(true);
	if(fStatPeriod > rhs.fStatPeriod)
		return(false);

	if(fStatDate < rhs.fStatDate)
		return(true);
	return(false);
}

/******************************************************************************/
/******************************************************************************/

TDivision::TDivision(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "X")
		fT = div_Undefined;
	else if(value == "E")
		fT = div_East;
	else if(value == "W")
		fT = div_West;
	else
		throw ASIException("TDivision::TDivision: invalid str");
}

/******************************************************************************/

const char* TDivision::c_str() const
{
	switch(fT)
	{
		case div_Undefined:
			return("X");
		case div_East:
			return("E");
		case div_West:
			return("W");
		default:
			break;
	};

	throw ASIException("TDivision::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TGamePhase::TGamePhase(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "EN")
		fT = gmph_Enrollment;
	else if(value == "PD")
		fT = gmph_PreDraft;
	else if(value == "DR")
		fT = gmph_Draft;
	else if(value == "PS")
		fT = gmph_PreSeason;
	else if(value == "SE")
		fT = gmph_Season;
	else if(value == "PL")
		fT = gmph_Playoffs;
	else if(value == "PO")
		fT = gmph_PostSeason;
	else
		throw ASIException("TGamePhase::TGamePhase: invalid str");
}

/******************************************************************************/

const char* TGamePhase::c_str() const
{
	switch(fT)
	{
		case gmph_Enrollment:
			return("EN");
		case gmph_PreDraft:
			return("PD");
		case gmph_Draft: 
			return("DR");
		case gmph_PreSeason:
			return("PS");
		case gmph_Season:
			return("SE");
		case gmph_Playoffs:
			return("PL");
		case gmph_PostSeason:
			return("PO");
		default:
			break;
	};

	throw ASIException("TGamePhase::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TProfPlayerGameStatus::TProfPlayerGameStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = ppgs_Undefined;
	else if(value == "A")
		fT = ppgs_Active;
	else if(value == "D")
		fT = ppgs_Disabled;
	else
		throw ASIException("TProfPlayerGameStatus::TProfPlayerGameStatus: invalid str");
}

/******************************************************************************/

const char* TProfPlayerGameStatus::c_str() const
{
	switch(fT)
	{
		case ppgs_Undefined:
			return("X");
		case ppgs_Active:
			return("A");
		case ppgs_Disabled:
			return("D");
		default:
			break;
	};

	throw ASIException("TProfPlayerGameStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TStatPeriod::TStatPeriod(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "G")
		fT = stp_SeasonGame;

	else if(value == "W")
		fT = stp_LastTwoWeeks;
	else if(value == "F")
		fT = stp_LastFourWeeks;
	else if(value == "E")
		fT = stp_LastEightWeeks;

	else if(value == "D")
		fT = stp_SeasonToDate;
	else if(value == "L")
		fT = stp_LastSeason;
	else if(value == "T")
		fT = stp_TwoSeasonsAgo;
	else if(value == "R")
		fT = stp_ThreeSeasonsAgo;
	else
		throw ASIException("TStatPeriod::TStatPeriod: invalid str");
}

/******************************************************************************/

const char* TStatPeriod::c_str() const
{
	switch(fT)
	{
		case stp_SeasonGame:
			return("G");

		case stp_LastTwoWeeks:
			return("W");
		case stp_LastFourWeeks:
			return("F");
		case stp_LastEightWeeks:
			return("E");

		case stp_SeasonToDate:
			return("D");
		case stp_LastSeason:
			return("L");
		case stp_TwoSeasonsAgo:
			return("T");
		case stp_ThreeSeasonsAgo:
			return("R");
		default:
			break;
	};

	throw ASIException("TStatPeriod::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TScheduleDayStatus::TScheduleDayStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = sdst_Undefined;
	else if(value == "M")
		fT = sdst_Missed;
	else if(value == "N")
		fT = sdst_NotStarted;
	else if(value == "I")
		fT = sdst_InProgress;
	else if(value == "C")
		fT = sdst_Completed;
	else
		throw ASIException("TScheduleDayStatus::TScheduleDayStatus: invalid str");
}

/******************************************************************************/

const char* TScheduleDayStatus::c_str() const
{
	switch(fT)
	{
		case sdst_Undefined:
			return("X");
		case sdst_Missed:
			return("M");
		case sdst_NotStarted:
			return("N");
		case sdst_InProgress:
			return("I");
		case sdst_Completed:
			return("C");
		default:
			break;
	};

	throw ASIException("TScheduleDayStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TFreeAgentClaimStatus::TFreeAgentClaimStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = facs_Undefined;
	else if(value == "P")
		fT = facs_Pending;
	else if(value == "R")
		fT = facs_Cleared;
	else if(value == "I")
		fT = facs_Invalidated;
	else if(value == "C")
		fT = facs_Completed;
	else
		throw ASIException("TFreeAgentClaimStatus::TFreeAgentClaimStatus: invalid str");
}

/******************************************************************************/

const char* TFreeAgentClaimStatus::c_str() const
{
	switch(fT)
	{
		case facs_Undefined:
			return("X");
		case facs_Pending:
			return("P");
		case facs_Cleared:
			return("R");
		case facs_Invalidated:
			return("I");
		case facs_Completed:
			return("C");
		default:
			break;
	};

	throw ASIException("TFreeAgentClaimStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TFAClaimProcessedStatus::TFAClaimProcessedStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = fcps_Undefined;
	else if(value == "P")
		fT = fcps_NotProcessed;
	else if(value == "N")
		fT = fcps_NewFreeAgent;
	else if(value == "T")
		fT = fcps_InTrade;
	else if(value == "L")
		fT = fcps_Locked;
	else
		throw ASIException("TFAClaimProcessedStatus::TFAClaimProcessedStatus: invalid str");
}

/******************************************************************************/

const char* TFAClaimProcessedStatus::c_str() const
{
	switch(fT)
	{
		case fcps_Undefined:
			return("X");
		case fcps_NotProcessed:
			return("P");
		case fcps_NewFreeAgent:
			return("N");
		case fcps_InTrade:
			return("T");
		case fcps_Locked:
			return("L");
		default:
			break;
	};

	throw ASIException("TFAClaimProcessedStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TTradeStatus::TTradeStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = trs_Undefined;
	else if(value == "P")
		fT = trs_Proposed;
	else if(value == "R")
		fT = trs_Cleared;
	else if(value == "D")
		fT = trs_Declined;
	else if(value == "A")
		fT = trs_Accepted;
	else if(value == "E")
		fT = trs_Expired;
	else if(value == "T")
		fT = trs_Protested;
	else if(value == "I")
		fT = trs_Invalidated;
	else if(value == "C")
		fT = trs_Completed;
	else
		throw ASIException("TTradeStatus::TTradeStatus: invalid str");
}

/******************************************************************************/

const char* TTradeStatus::c_str() const
{
	switch(fT)
	{
		case trs_Undefined:
			return("X");
		case trs_Proposed:
			return("P");
		case trs_Cleared:
			return("R");
		case trs_Declined:
			return("D");
		case trs_Accepted:
			return("A");
		case trs_Expired:
			return("E");
		case trs_Protested:
			return("T");
		case trs_Invalidated:
			return("I");
		case trs_Completed:
			return("C");
		default:
			break;
	};

	throw ASIException("TTradeStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

void TPlayerIDVector::readFromFiler(TDataFiler& filer)
{
	int i,numPlayers;

	erase(begin(),end());
	
	numPlayers = filer.readShort();
	for(i = 0; i < numPlayers; i++)
		push_back(TPlayerID(filer.readLong()));
}

/******************************************************************************/

void TPlayerIDVector::writeToFiler(TDataFiler& filer)
{
	const_iterator iter;

	filer.writeShort((short)size());
	for(iter = begin(); iter != end(); iter++)
		filer.writeLong((*iter).getID());
}

/******************************************************************************/

void TPlayerIDVector::fillFromPlayerVector(const TPlayerVector& playerVector)
{
	TPlayerVector::const_iterator iter;

	erase(begin(),end());
	
	for(iter = playerVector.begin(); iter != playerVector.end(); iter++)
		push_back((*iter)->getPlayerID());
}

/******************************************************************************/
	
void TPlayerIDVector::removeUndefined()
{
	erase(remove(begin(),end(),TPlayerID()),end());
}
	
/******************************************************************************/

/* Searches for duplicate IDs in the vector.  If ignoreZeroIDs is true, then
	multiple zero IDs in the vector are not considered duplicates.  If
	ignoreZeroIDs is false, two or more zero IDs in vector would be considered
	duplicates. */
	
bool TPlayerIDVector::doesContainDups(bool ignoreUndefineds) const
{
	const_iterator iter;

	for(iter = begin(); iter != end(); iter++)
	{
		if(find(iter + 1, end(), *iter) != end())
		{
			if((*iter).isUndefined())
			{
				if(!ignoreUndefineds)
					return(true);
			}
			else
				return(true);
		}
	}

	return(false);
}

/******************************************************************************/

// Is 'this' a superset of playerIDVector?

bool TPlayerIDVector::contains(const TPlayerIDVector& playerIDVector,
	bool skipUndefineds) const
{
	const_iterator iter;

	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		if(std::find(begin(),end(),(*iter)) == end())
		{
			if((*iter).isUndefined())
			{
				if(!skipUndefineds)
					return(false);
			}
			else
				return (false);
		}
	}
	
	return (true);
}

/******************************************************************************/

// Does 'this' contain any of same IDs as in playerIDVector?

bool TPlayerIDVector::containsAny(const TPlayerIDVector& playerIDVector,
	bool skipUndefineds) const
{
	const_iterator iter;

	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		if(std::find(begin(),end(),(*iter)) != end())
		{
			if((*iter).isUndefined())
			{
				if(!skipUndefineds)
					return(true);
			}
			else
				return (true);
		}
	}
	
	return (false);
}

/******************************************************************************/

void TPlayerIDVector::replace(TPlayerID& oldPlayerID,TPlayerID& newPlayerID)
{
	iterator iter;
	
	while((iter = find(begin(),end(),oldPlayerID)) != end())
		*iter = newPlayerID;
}

/******************************************************************************/
/******************************************************************************/

int TTeamIDVector::getPosition(const TTeamID teamID,const CommonAccessMode cam) const
{
	const_iterator iter;

	if((iter = find(begin(),end(),teamID)) != end())
		return(iter - begin());
	else if(cam == cam_MustExist)
		throw ASIException("TTeamIDVector::getPosition: teamID not found");

	return(-1);
}

/******************************************************************************/

void TTeamIDVector::remove(const TTeamID teamID,const CommonAccessMode cam)
{
	iterator iter;

	if((iter = find(begin(),end(),teamID)) != end())
		erase(iter);
	else if(cam == cam_MustExist)
		throw ASIException("TTeamIDVector::remove: teamID not found");
}

/******************************************************************************/

void TTeamIDVector::fillFromTeamVector(const TTeamVector& teamVector)
{
	TTeamVector::const_iterator iter;

	erase(begin(),end());
	
	for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
		push_back((*iter)->getTeamID());
}

/******************************************************************************/

void TPlayerDateIDVector::fillFromOffGameStatVector(
	const TOffGameStatVector& offGameStatVector)
{
	TOffGameStatVector::const_iterator iter;

	erase(begin(),end());
	
	for(iter = offGameStatVector.begin(); iter != offGameStatVector.end(); iter++)
		push_back((*iter)->getPlayerDateID());
}

/******************************************************************************/

void TPlayerDateIDVector::fillFromDefGameStatVector(
	const TDefGameStatVector& defGameStatVector)
{
	TDefGameStatVector::const_iterator iter;

	erase(begin(),end());
	
	for(iter = defGameStatVector.begin(); iter != defGameStatVector.end(); iter++)
		push_back((*iter)->getPlayerDateID());
}

/******************************************************************************/
/******************************************************************************/

short TPlayerDatesVector::calcTotalPoints() const
{
	const_iterator iter;
	short totalPoints = 0;

	for(iter = begin(); iter != end(); ++iter)
		totalPoints += (*iter).fPoints;

	return(totalPoints);
}

/******************************************************************************/

void TPlayerDatesVector::fillFromPlayerIDVector(const TPlayerIDVector& playerIDVector)
{
	TPlayerDates playerDates;
	TPlayerIDVector::const_iterator iter;

	erase(begin(),end());
	
	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); ++iter)
	{
		playerDates.clear();
		playerDates.fPlayerID = *iter;
		push_back(playerDates);
	}
}

/******************************************************************************/

void TPlayerDatesVector::loadPlayerIDVector(TPlayerIDVector& playerIDVector) const
{
	const_iterator iter;

	playerIDVector.erase(playerIDVector.begin(),playerIDVector.end());

	for(iter = begin(); iter != end(); ++iter)
		playerIDVector.push_back((*iter).fPlayerID);
}

/******************************************************************************/

void TPlayerDatesVector::updateFromOffGameStatVector(
	const TOffGameStatVector& offGameStatVector,const bool inPlayoffs)
{
	iterator playerDatesIter;
	TOffGameStatVector::const_iterator gameStatIter;
	bool found;

	for(gameStatIter = offGameStatVector.begin();
		gameStatIter != offGameStatVector.end(); ++gameStatIter)
	{
		found = false;
		for(playerDatesIter = begin(); (playerDatesIter != end()) && !found;
			++playerDatesIter)
		{
			if((*playerDatesIter).fPlayerID == (*gameStatIter)->getPlayerID())
			{
				(*playerDatesIter).fDateTimeVector.push_back(
					(*gameStatIter)->getStatDate());

				if(inPlayoffs)	// average by 4
				{
					int totalPoints = abs((*gameStatIter)->getTotalPoints());
					totalPoints = (((double)totalPoints / 4.0) + 0.5);
					if((*gameStatIter)->getTotalPoints() < 0)
						totalPoints *= -1;
					(*playerDatesIter).fPoints += totalPoints;
				}
				else
					(*playerDatesIter).fPoints += (*gameStatIter)->getTotalPoints();

				found = true;
			}
		}
		if(!found)
			throw ASIException("TPlayerDatesVector::updateFromOffGameStatVector: playerID not found");
	}
}

/******************************************************************************/

void TPlayerDatesVector::updateFromDefGameStatVector(
	const TDefGameStatVector& defGameStatVector,const bool inPlayoffs)
{
	iterator playerDatesIter;
	TDefGameStatVector::const_iterator gameStatIter;
	bool found;

	for(gameStatIter = defGameStatVector.begin();
		gameStatIter != defGameStatVector.end(); ++gameStatIter)
	{
		found = false;
		for(playerDatesIter = begin(); (playerDatesIter != end()) && !found;
			++playerDatesIter)
		{
			if((*playerDatesIter).fPlayerID == (*gameStatIter)->getPlayerID())
			{
				(*playerDatesIter).fDateTimeVector.push_back(
					(*gameStatIter)->getStatDate());
				if(inPlayoffs)	// average by 4
				{
					int totalPoints = abs((*gameStatIter)->getTotalPoints());
					totalPoints = (((double)totalPoints / 4.0) + 0.5);
					if((*gameStatIter)->getTotalPoints() < 0)
						totalPoints *= -1;
					(*playerDatesIter).fPoints += totalPoints;
				}
				else
					(*playerDatesIter).fPoints += (*gameStatIter)->getTotalPoints();

				found = true;
			}
		}
		if(!found)
			throw ASIException("TPlayerDatesVector::updateFromOffGameStatVector: playerID not found");
	}
}

/******************************************************************************/
/******************************************************************************/

double asfantasy::calcWinningPercentage(int wins,int loses)
{
	if((wins + loses) == 0)
		return(0.0);

	return((double)wins / ((double)wins + (double)loses));
}

/******************************************************************************/
/******************************************************************************/

void TLeague::clear()
{
	TQueryDataSetRecord::clear();

	fLeagueID.clear();
	fName.Clear();
	fPassword.Clear();
	
	fGamePhase = TGamePhase();
	fReserved = false;
	
	fLastProcessedDate = TDateTime();
	fDraftDate = TDateTime();
	fSeasonDate = TDateTime();
	
	fOverallStandings.erase(fOverallStandings.begin(),fOverallStandings.end());
	fEastDivStandings.erase(fEastDivStandings.begin(),fEastDivStandings.end());
	fWestDivStandings.erase(fWestDivStandings.begin(),fWestDivStandings.end());

	fFAClaimOrder.erase(fFAClaimOrder.begin(),fFAClaimOrder.end());
	fRound1DraftOrder.erase(fRound1DraftOrder.begin(),fRound1DraftOrder.end());

	// Playoff Data
	fEastWinnerTeamID.clear();
	fEastWildCardTeamID.clear();

	fWestWinnerTeamID.clear();
	fWestWildCardTeamID.clear();
	
	fFinalistOneTeamID.clear();
	fFinalistTwoTeamID.clear();

	fLeagueChampTeamID.clear();
}

/******************************************************************************/

TTeamIDVector TLeague::getDivTeamIDVector(TDivision division) const
{
	TTeamIDVector teamIDVector;

	if(division == div_East)
		return(fEastDivStandings);

	if(division == div_West)
		return(fWestDivStandings);

	//throw ASIException();	//BOB
	return(TTeamIDVector());
}

/******************************************************************************/
	
const TTeamIDVector& TLeague::round1DraftOrder()
{
	if(fRound1DraftOrder.size() != 0)
		return(fRound1DraftOrder);

	const TDraftOrderPtr draftOrderPtr = TDraftOrder::createGet(fLeagueID,cam_MustExist);
	const TDraftRoundVector& draftRoundVector = draftOrderPtr->draftRoundVector();

	if(draftRoundVector.size() == 0)
		throw ASIException("TLeague::round1DraftOrder: round 1 does not exist");

	fRound1DraftOrder = draftRoundVector[0];
		
	return(fRound1DraftOrder);
}

/******************************************************************************/

void TLeague::calcDraftDate(bool inNightlyProcessing)
{
	if(fDraftDate != TDateTime())
		throw ASIException("TLeague::calcDraftDate: fDraftDate already defined");
	
	fDraftDate = getEarliestDraftDate(inNightlyProcessing);
}

/******************************************************************************/

TDateTime TLeague::getEarliestDraftDate(bool inNightlyProcessing)
{
	TDateTime curDate = TDateTime::CurrentDate();
	TDateTime curTime = TDateTime::CurrentTime();
	TDateTime draftDate;
	
	if(curDate < RegularStartDate())
	{
		draftDate = RegularStartDate();	//BOB + PreDraftLength();
	}
	else if(curDate == RegularStartDate())
	{
		if(inNightlyProcessing || (curTime < NightlyProcessingTime()))
			draftDate = RegularStartDate();	//BOB + PreDraftLength();
		else
			draftDate = RegularStartDate() + 1;	//BOB+ PreDraftLength();
	}
	else
	{
		if(inNightlyProcessing || (curTime < NightlyProcessingTime()))
			draftDate = curDate;	//BOB + PreDraftLength();
		else
			draftDate = curDate + 1;	//BOB + PreDraftLength();
	}

	return(draftDate);
}

/******************************************************************************/

TLeaguePtr TLeague::newInstance()
{
	TLeaguePtr leaguePtr = ASFantasyObjectBuilder::getThe().newLeague();
	leaguePtr->clear();
	return(leaguePtr);
}

/******************************************************************************/
	
void TLeague::readFromDataSet(TDataSet& dataSet)
{
	TTeamID teamID;
	CStr31 fieldName;
	int i,numTeams;
	
	fLeagueID = DataSetReadNumericID(dataSet,"LeagueID");

	fName = dataSet.FieldByName("Name")->AsString.c_str();
	fPassword = dataSet.FieldByName("Passwd")->AsString.c_str();
	
	fGamePhase = dataSet.FieldByName("GamePhase")->AsString.c_str();
	fReserved = (dataSet.FieldByName("Reserved")->AsInteger == 0) ? false : true;

	fLastProcessedDate = DataSetReadDateTime(dataSet,"LastProcessedDate");
	fDraftDate = DataSetReadDateTime(dataSet,"DraftDate");
	fSeasonDate = DataSetReadDateTime(dataSet,"SeasonDate");
	
	/* fOverallStandings */
	numTeams = dataSet.FieldByName("NumOverallTeams")->AsInteger;

	fOverallStandings.erase(fOverallStandings.begin(),fOverallStandings.end());
	
	for(i = 0; i < numTeams; i++)
	{
		fieldName.CopyVarg("OverallStand%02d",i + 1);
		teamID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fOverallStandings.push_back(teamID);
	}
	
	/* fEastDivStandings */
	numTeams = dataSet.FieldByName("NumEastDivTeams")->AsInteger;

	fEastDivStandings.erase(fEastDivStandings.begin(),fEastDivStandings.end());
	
	for(i = 0; i < numTeams; i++)
	{
		fieldName.CopyVarg("EastDivStand%02d",i + 1);
		teamID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fEastDivStandings.push_back(teamID);
	}
	
	/* fWestDivStandings */
	numTeams = dataSet.FieldByName("NumWestDivTeams")->AsInteger;

	fWestDivStandings.erase(fWestDivStandings.begin(),fWestDivStandings.end());
	
	for(i = 0; i < numTeams; i++)
	{
		fieldName.CopyVarg("WestDivStand%02d",i + 1);
		teamID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fWestDivStandings.push_back(teamID);
	}

	/* FA Claim Order */
	numTeams = dataSet.FieldByName("NumFAClaimTeams")->AsInteger;

	fFAClaimOrder.erase(fFAClaimOrder.begin(),fFAClaimOrder.end());
	
	for(i = 0; i < numTeams; i++)
	{
		fieldName.CopyVarg("FAClaimTeam%02d",i + 1);
		teamID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fFAClaimOrder.push_back(teamID);
	}

	// Playoff Data
	fEastWinnerTeamID = dataSet.FieldByName("EastWinnerTeamID")->AsInteger;
	fEastWildCardTeamID = dataSet.FieldByName("EastWildCardTeamID")->AsInteger;

	fWestWinnerTeamID = dataSet.FieldByName("WestWinnerTeamID")->AsInteger;
	fWestWildCardTeamID = dataSet.FieldByName("WestWildCardTeamID")->AsInteger;

	fFinalistOneTeamID = dataSet.FieldByName("FinalistOneTeamID")->AsInteger;
	fFinalistTwoTeamID = dataSet.FieldByName("FinalistTwoTeamID")->AsInteger;

	fLeagueChampTeamID = dataSet.FieldByName("LeagueChampTeamID")->AsInteger;
}

/******************************************************************************/

void TLeague::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	int i,numTeams;
	
	DataSetWriteNumericID(dataSet,"LeagueID",fLeagueID);
	
	dataSet.FieldByName("Name")->AsString = fName.c_str();
	dataSet.FieldByName("Passwd")->AsString = fPassword.c_str();
	
	dataSet.FieldByName("GamePhase")->AsString = fGamePhase.c_str();
	dataSet.FieldByName("Reserved")->AsInteger = fReserved ? 1 : 0;
	
	DataSetWriteDateTime(dataSet,"LastProcessedDate",fLastProcessedDate);
	DataSetWriteDateTime(dataSet,"DraftDate",fDraftDate);
	DataSetWriteDateTime(dataSet,"SeasonDate",fSeasonDate);

	/* fOverallStandings */
	numTeams = fOverallStandings.size();
	
	dataSet.FieldByName("NumOverallTeams")->AsInteger = numTeams;

	for(i = 0; i < MaxTeamsPerPrivateLeague(); i++)
	{
		fieldName.CopyVarg("OverallStand%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numTeams) ? fOverallStandings[i].getID() : 0;
	}
	
	/* fEastDivStandings */
	numTeams = fEastDivStandings.size();
	
	dataSet.FieldByName("NumEastDivTeams")->AsInteger = numTeams;

	for(i = 0; i < MaxTeamsPerDivision(); i++)
	{
		fieldName.CopyVarg("EastDivStand%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numTeams) ? fEastDivStandings[i].getID() : 0;
	}
	
	/* fWestDivStandings */
	numTeams = fWestDivStandings.size();
	
	dataSet.FieldByName("NumWestDivTeams")->AsInteger = numTeams;

	for(i = 0; i < MaxTeamsPerDivision(); i++)
	{
		fieldName.CopyVarg("WestDivStand%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numTeams) ? fWestDivStandings[i].getID() : 0;
	}

	/* FA Claim Order */
	numTeams = fFAClaimOrder.size();
	
	dataSet.FieldByName("NumFAClaimTeams")->AsInteger = numTeams;

	for(i = 0; i < MaxTeamsPerPrivateLeague(); i++)
	{
		fieldName.CopyVarg("FAClaimTeam%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numTeams) ? fFAClaimOrder[i].getID() : 0;
	}

	// Playoff Data
	dataSet.FieldByName("EastWinnerTeamID")->AsInteger = fEastWinnerTeamID.getID();
	dataSet.FieldByName("EastWildCardTeamID")->AsInteger = fEastWildCardTeamID.getID();

	dataSet.FieldByName("WestWinnerTeamID")->AsInteger = fWestWinnerTeamID.getID();
	dataSet.FieldByName("WestWildCardTeamID")->AsInteger = fWestWildCardTeamID.getID();

	dataSet.FieldByName("FinalistOneTeamID")->AsInteger = fFinalistOneTeamID.getID();
	dataSet.FieldByName("FinalistTwoTeamID")->AsInteger = fFinalistTwoTeamID.getID();

	dataSet.FieldByName("LeagueChampTeamID")->AsInteger = fLeagueChampTeamID.getID();
}

/******************************************************************************/

void TLeague::validateForUpdate()
{
	if(fIsNewRecord)
		fLeagueID = GetNextNum(getDatabaseName(),getTableName());
		
	if(fLeagueID.isUndefined())
		throw ASIException("TLeague::validateForUpdate: fLeagueID.isUndefined()");

	if(!fName.HasLen())
		throw ASIException("TLeague::validateForUpdate: !fName.HasLen()");

	if(fLastProcessedDate == TDateTime())
		throw ASIException("TLeague::validateForUpdate: LastProcessedDate == TDateTime()");
}

/******************************************************************************/

CStrVar TLeague::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(LeagueID = \"%s\")",fLeagueID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TTeam::clear()
{
	TQueryDataSetRecord::clear();

	fTeamID.clear();
	fParticID.clear();
	fLeagueID.clear();
	fDivision = TDivision();

	fRegionName.Clear();
	fTeamName.Clear();
	
	fManagerName.Clear();

	fWins = 0;
	fLoses = 0;
	fTies = 0;
	fDivWins = 0;
	fDivLoses = 0;
	fDivTies = 0;
	fStreak = 0;
	fTotalPoints = 0;
	
	fNumTradeProtests = 0;
}

/******************************************************************************/

TFullTeamName TTeam::getFullTeamName() const
{
	TFullTeamName fullTeamName;

	fullTeamName.Copy(fRegionName);
	if(fTeamName.HasLen())
	{
		if(fullTeamName.HasLen())
			fullTeamName.Concat(" ");
		fullTeamName.Concat(fTeamName);
	}

	return(fullTeamName);
}

/******************************************************************************/

void TTeam::addWin(bool divGame)
{
	fWins++;

	if(divGame)
		fDivWins++;

	if(fStreak > 0)
		fStreak++;
	else
		fStreak = 1;
}

/******************************************************************************/

void TTeam::addLose(bool divGame)
{
	fLoses++;

	if(divGame)
		fDivLoses++;
		
	if(fStreak < 0)
		fStreak--;
	else
		fStreak = -1;
}

/******************************************************************************/

void TTeam::addTie(bool divGame)
{
	fTies++;

	if(divGame)
		fDivTies++;

	fStreak = 0;
}

/******************************************************************************/

TTeamPtr TTeam::newInstance()
{
	TTeamPtr teamPtr = ASFantasyObjectBuilder::getThe().newTeam();
	teamPtr->clear();
	return(teamPtr);
}

/******************************************************************************/

void TTeam::readLineupFromDataSet(TDataSet& dataSet,const TLineup lut,
	const char* fieldNamePrefix)
{
	TPlayerIDVector& playerIDVector(lineup(lut));
	CStr31 fieldName;
	int i,maxPlayers;
	TPlayerID playerID;

	playerIDVector.erase(playerIDVector.begin(),playerIDVector.end());
	maxPlayers = MaxPlayersInLineup(lut);

	for(i = 0; i < maxPlayers; i++)
	{
		fieldName.CopyVarg("%sPlayer%02d",fieldNamePrefix,i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		playerIDVector.push_back(playerID);
	}
}

/******************************************************************************/
	
void TTeam::readFromDataSet(TDataSet& dataSet)
{
	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;
	fParticID = dataSet.FieldByName("ParticID")->AsInteger;
	fLeagueID = dataSet.FieldByName("LeagueID")->AsInteger;
	fDivision = dataSet.FieldByName("Division")->AsString.c_str();
	
	fRegionName = dataSet.FieldByName("RegionName")->AsString.c_str();
	fTeamName = dataSet.FieldByName("TeamName")->AsString.c_str();

	fManagerName = dataSet.FieldByName("ManagerName")->AsString.c_str();

	fWins = (short)dataSet.FieldByName("Wins")->AsInteger;
	fLoses = (short)dataSet.FieldByName("Loses")->AsInteger;
	fTies = (short)dataSet.FieldByName("Ties")->AsInteger;
	fDivWins = (short)dataSet.FieldByName("DivWins")->AsInteger;
	fDivLoses = (short)dataSet.FieldByName("DivLoses")->AsInteger;
	fDivTies = (short)dataSet.FieldByName("DivTies")->AsInteger;
	fStreak = (short)dataSet.FieldByName("Streak")->AsInteger;
	fTotalPoints = (short)dataSet.FieldByName("TotalPoints")->AsInteger;

	// Trades
	fNumTradeProtests = (short)dataSet.FieldByName("NumTradeProtests")->AsInteger;
}

/******************************************************************************/

void TTeam::writeLineupToDataSet(TDataSet& dataSet,const TLineup lut,
	const char* fieldNamePrefix)
{
	const TPlayerIDVector& playerIDVector(lineup(lut));
	CStr31 fieldName;
	int i,numPlayers,maxPlayers;
	TPlayerID playerID;

	numPlayers = playerIDVector.size();
	maxPlayers = MaxPlayersInLineup(lut);
		
	for(i = 0; i < maxPlayers; i++)
	{
		fieldName.CopyVarg("%sPlayer%02d",fieldNamePrefix,i + 1);
		
		if(i < numPlayers)
		{
			playerID = playerIDVector[i];
			if(playerID.isUndefined())
				dataSet.FieldByName(fieldName.c_str())->Clear();
			else
				dataSet.FieldByName(fieldName.c_str())->AsInteger = playerID.getID();
		}
		else
			dataSet.FieldByName(fieldName.c_str())->Clear();
	}
}

/******************************************************************************/

void TTeam::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();
	dataSet.FieldByName("ParticID")->AsInteger = fParticID.getID();

	if(fLeagueID.isUndefined())
		dataSet.FieldByName("LeagueID")->Clear();
	else
		dataSet.FieldByName("LeagueID")->AsInteger = fLeagueID.getID();

	dataSet.FieldByName("Division")->AsString = fDivision.c_str();
	
	dataSet.FieldByName("RegionName")->AsString = fRegionName.c_str();
	dataSet.FieldByName("TeamName")->AsString = fTeamName.c_str();

	dataSet.FieldByName("ManagerName")->AsString = fManagerName.c_str();
	
	dataSet.FieldByName("Wins")->AsInteger = fWins;
	dataSet.FieldByName("Loses")->AsInteger = fLoses;
	dataSet.FieldByName("Ties")->AsInteger = fTies;
	dataSet.FieldByName("DivWins")->AsInteger = fDivWins;
	dataSet.FieldByName("DivLoses")->AsInteger = fDivLoses;
	dataSet.FieldByName("DivTies")->AsInteger = fDivTies;
	dataSet.FieldByName("Streak")->AsInteger = fStreak;
	dataSet.FieldByName("TotalPoints")->AsInteger = fTotalPoints;

	// Trades
	dataSet.FieldByName("NumTradeProtests")->AsInteger = fNumTradeProtests;
}

/******************************************************************************/

void TTeam::validateForUpdate()
{
	if(fIsNewRecord)
		fTeamID = GetNextNum(getDatabaseName(),getTableName());

	if(fTeamID.isUndefined())
		throw ASIException("TTeam::validateForUpdate: fTeamID.isUndefined()");

	// ParticID should only be undefined when added, it should be set on the first update.
	if(!fIsNewRecord && fParticID.isUndefined())
		throw ASIException("TTeam::validateForUpdate: fParticID.isUndefined()");
		
	if(!fLeagueID.isUndefined() && fDivision.isUndefined())
		throw ASIException("TTeam::validateForUpdate: !fLeagueID.isUndefined() && fDivision.isUndefined()");

	if(fRegionName.Len() == 0)
		throw ASIException("TTeam::validateForUpdate: fRegionName.Len() == 0");
	if(fTeamName.Len() == 0)
		throw ASIException("TTeam::validateForUpdate: fTeamName.Len() == 0");

	if(fManagerName.Len() == 0)
		throw ASIException("TTeam::validateForUpdate: fManagerName.Len() == 0");
}

/******************************************************************************/

CStrVar TTeam::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(TeamID = \"%s\")",fTeamID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

TTeamPtr TTeamVector::findByID(const TTeamID teamID,
	const CommonAccessMode getMode) const
{
	const_iterator iter;
	
	iter = std::find_if(begin(),end(),findIDCompare(teamID));
	if(iter != end())
		return(*iter);

	if(getMode == cam_MustExist)
		throw ASIException("TTeamVector::findByID: not found (%s)",
			teamID.c_str());

	return(TTeamPtr());
}

/******************************************************************************/

void TTeamVector::fillFromTeamIDVector(const TTeamIDVector& teamIDVector,
	const TTeamVector& teamVector)
{
	TTeamByIDVector teamByIDVector;
	TTeamPtr teamPtr;
	TTeamIDVector::const_iterator iter;

	erase(begin(),end());
	
	teamByIDVector = teamVector;
	
	for(iter = teamIDVector.begin(); iter != teamIDVector.end(); iter++)
	{
		teamPtr = teamByIDVector.getByID(*iter);
		if(teamPtr.isNull())
			throw ASIException("TTeamVector::fillFromTeamIDVector: invalid TeamID");

		push_back(teamPtr);
	}
}

/******************************************************************************/

void TTeamVector::fillFromTeamVectorByDivision(const TTeamVector& teamVector,
	TDivision division)
{
	TTeamVector::const_iterator iter;

	erase(begin(),end());
	
	for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
	{
		if((*iter)->getDivision() == division)
			push_back(*iter);
	}
}

/******************************************************************************/

TTeamByIDVector& TTeamByIDVector::operator=(const TTeamVector& rhs)
{
	erase(begin(),end());
	
	resize(rhs.size());
	copy(rhs.begin(),rhs.end(),begin());
	sort();

	return(*this);
}

/******************************************************************************/
/******************************************************************************/

void TProfPlayer::clear()
{
	TQueryDataSetRecord::clear();
	
	fPlayerID.clear();
	fName.clear();
	fProfTeamID.clear();
	fGameStatus.clear();

	fNewPlayerDate = TDateTime();
	fTotalPoints = 0;
	fLastWeeksPoints = 0;

	fLastUpdatedDate = TDateTime();
}

/******************************************************************************/

TProfPlayerPtr TProfPlayer::newInstance()
{
	TProfPlayerPtr profPlayerPtr = ASFantasyObjectBuilder::getThe().newProfPlayer();
	profPlayerPtr->clear();
	return(profPlayerPtr);
}

/******************************************************************************/
	
void TProfPlayer::readFromDataSet(TDataSet& dataSet)
{
	fPlayerID = dataSet.FieldByName("PlayerID")->AsInteger;
	
	fName.fFirstName = dataSet.FieldByName("FirstName")->AsString.c_str();
	fName.fLastName = dataSet.FieldByName("LastName")->AsString.c_str();
	
	fProfTeamID = (unsigned short)dataSet.FieldByName("ProfTeamID")->AsInteger;
	fGameStatus = dataSet.FieldByName("GameStatus")->AsString.c_str();
	
	fNewPlayerDate = dataSet.FieldByName("NewPlayerDate")->AsFloat;	//BOB AsDateTime
	fTotalPoints = (short)dataSet.FieldByName("TotalPoints")->AsInteger;
	fLastWeeksPoints = (short)dataSet.FieldByName("LastWeeksPoints")->AsInteger;

	fLastUpdatedDate = dataSet.FieldByName("LastUpdated")->AsFloat;	//Add Date to end //BOB AsDateTime;
}

/******************************************************************************/

void TProfPlayer::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("PlayerID")->AsInteger = fPlayerID.getID();
	
	dataSet.FieldByName("FirstName")->AsString = fName.fFirstName.c_str();
	dataSet.FieldByName("LastName")->AsString = fName.fLastName.c_str();
	
	dataSet.FieldByName("ProfTeamID")->AsInteger = fProfTeamID.getID();
	dataSet.FieldByName("GameStatus")->AsString = fGameStatus.c_str();

	dataSet.FieldByName("NewPlayerDate")->AsDateTime = fNewPlayerDate;
	dataSet.FieldByName("TotalPoints")->AsInteger = fTotalPoints;
	dataSet.FieldByName("LastWeeksPoints")->AsInteger = fLastWeeksPoints;

	dataSet.FieldByName("LastUpdated")->AsDateTime = fLastUpdatedDate;	//BOB Add Date to end 
}

/******************************************************************************/

void TProfPlayer::validateForUpdate()
{
	if(fPlayerID.isUndefined())
		throw ASIException("TProfPlayer::validateForUpdate: fPlayerID.isUndefined()");

	// Don't test fFirstName, Defences do not have first names.
	// if(fName.fFirstName.Len() == 0)
	// 	throw ASIException("TProfPlayer::validateForUpdate: fName.fFirstName.Len() == 0");
	if(fName.fLastName.Len() == 0)
		throw ASIException("TProfPlayer::validateForUpdate: fName.fLastName.Len() == 0");
		
	if(fProfTeamID.isUndefined())
		throw ASIException("TProfPlayer::validateForUpdate: fProfTeamID.isUndefined()");
	if(fGameStatus.isUndefined())
		throw ASIException("TProfPlayer::validateForUpdate: fGameStatus.isUndefined()");
}

/******************************************************************************/

CStrVar TProfPlayer::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(PlayerID = \"%s\")",fPlayerID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TProfTeam::clear()
{
	TQueryDataSetRecord::clear();
	
	fProfTeamID.clear();
	fProfTeamAbbr.Clear();

	fRegionName.Clear();
	fTeamName.Clear();
}

/******************************************************************************/

TProfTeamPtr TProfTeam::newInstance()
{
	TProfTeamPtr profTeamPtr = ASFantasyObjectBuilder::getThe().newProfTeam();
	profTeamPtr->clear();
	return(profTeamPtr);
}

/******************************************************************************/
	
void TProfTeam::readFromDataSet(TDataSet& dataSet)
{
	fProfTeamID = (short)dataSet.FieldByName("ProfTeamID")->AsInteger;
	fProfTeamAbbr = dataSet.FieldByName("ProfTeamAbbr")->AsString.c_str();
	
	fRegionName = dataSet.FieldByName("RegionName")->AsString.c_str();
	fTeamName = dataSet.FieldByName("TeamName")->AsString.c_str();
}

/******************************************************************************/

void TProfTeam::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("ProfTeamID")->AsInteger = fProfTeamID.getID();
	dataSet.FieldByName("ProfTeamAbbr")->AsString = fProfTeamAbbr.c_str();
	
	dataSet.FieldByName("RegionName")->AsString = fRegionName.c_str();
	dataSet.FieldByName("TeamName")->AsString = fTeamName.c_str();
}

/******************************************************************************/

void TProfTeam::validateForUpdate()
{
	if(fProfTeamID.isUndefined())
		throw ASIException("TProfTeam::validateForUpdate: fProfTeamID.isUndefined()");
	if(fProfTeamAbbr.isUndefined())
		throw ASIException("TProfTeam::validateForUpdate: fProfTeamAbbr.isUndefined()");
		
	if(fRegionName.Len() == 0)
		throw ASIException("TProfTeam::validateForUpdate: fRegionName.Len() == 0");
	if(fTeamName.Len() == 0)
		throw ASIException("TProfTeam::validateForUpdate: fTeamName.Len() == 0");
}

/******************************************************************************/

CStrVar TProfTeam::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(ProfTeamID = \"%s\")",fProfTeamID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TPlayer::clear()
{
	TQueryDataSetRecord::clear();
	
	fLeagueID.clear();
	fPlayerID.clear();
	
	fTeamID.clear();
	
	fNewFADate = TDateTime();
}

/******************************************************************************/

TPlayerPtr TPlayer::newInstance()
{
	TPlayerPtr playerPtr = ASFantasyObjectBuilder::getThe().newPlayer();
	playerPtr->clear();
	return(playerPtr);
}

/******************************************************************************/

bool TPlayer::isNewFreeAgent() const
{
	if(!isFreeAgent())
		return(false);
		
	return(fNewFADate + MinFreeAgentPoolDays > TDateTime::CurrentDate());
}

/******************************************************************************/

TDateTime TPlayer::getFreeAgentAvailableDate() const
{
	if(!isFreeAgent())
		throw ASIException("TPlayer::getFreeAgentAvailableDate: calling for TeamPlayer");

	return(fNewFADate + MinFreeAgentPoolDays);
}

/******************************************************************************/

void TPlayer::readFromDataSet(TDataSet& dataSet)
{
	fLeagueID = dataSet.FieldByName("LeagueID")->AsInteger;
	fPlayerID = dataSet.FieldByName("PlayerID")->AsInteger;
	
	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;

	fNewFADate = dataSet.FieldByName("NewFADate")->AsFloat;	//BOB AsDateTime;
}

/******************************************************************************/

void TPlayer::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("LeagueID")->AsInteger = fLeagueID.getID();
	dataSet.FieldByName("PlayerID")->AsInteger = fPlayerID.getID();
	
	if(fTeamID.isUndefined())
		dataSet.FieldByName("TeamID")->Clear();
	else
		dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();

	dataSet.FieldByName("NewFADate")->AsDateTime = fNewFADate;
}

/******************************************************************************/

void TPlayer::validateForUpdate()
{
	if(fPlayerID.isUndefined())
		throw ASIException("TPlayer::validateForUpdate: fPlayerID.isUndefined()");
	if(fLeagueID.isUndefined())
		throw ASIException("TPlayer::validateForUpdate: fLeagueID.isUndefined()");
		
	//if(fTeamID.isUndefined())
	//	throw ASIException("TPlayer::validateForUpdate: fTeamID.isUndefined()");
}

/******************************************************************************/

CStrVar TPlayer::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(LeagueID = \"%s\") and ",fLeagueID.c_str());
	str.concatVarg("(PlayerID = \"%s\")",fPlayerID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TOffGameStat::clear()
{
	TQueryDataSetRecord::clear();
	
	fPlayerID.clear();
	fStatPeriod.clear();
	fStatDate = TDateTime(); 

	fTotalPoints = 0;
}

/******************************************************************************/

TPlayerDateID TOffGameStat::getPlayerDateID(void) const
{
	if(fStatPeriod != stp_SeasonGame)
		throw ASIException("TOffGameStat::getPlayerDateID: fStatDate undefined for fStatPeriod");

	return(TPlayerDateID(fPlayerID,fStatDate));
}

/******************************************************************************/

TOffGameStatPtr TOffGameStat::newInstance()
{
	TOffGameStatPtr offGameStatPtr =
		ASFantasyObjectBuilder::getThe().newOffGameStat();
	offGameStatPtr->clear();
	return(offGameStatPtr);
}

/******************************************************************************/
	
void TOffGameStat::readFromDataSet(TDataSet& dataSet)
{
	fPlayerID = dataSet.FieldByName("PlayerID")->AsInteger;
	fStatPeriod = dataSet.FieldByName("StatPeriod")->AsString.c_str();
	fStatDate = dataSet.FieldByName("StatDate")->AsFloat;

	fTotalPoints = (short)dataSet.FieldByName("TotalPoints")->AsInteger;
}

/******************************************************************************/

void TOffGameStat::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("PlayerID")->AsInteger = fPlayerID.getID();
	dataSet.FieldByName("StatPeriod")->AsString = fStatPeriod.c_str();
	dataSet.FieldByName("StatDate")->AsDateTime = fStatDate;

	dataSet.FieldByName("TotalPoints")->AsInteger = fTotalPoints;
}

/******************************************************************************/

void TOffGameStat::validateForUpdate()
{
	if(fPlayerID.isUndefined())
		throw ASIException("TOffGameStat::validateForUpdate: fPlayerID.isUndefined()");
	if(fStatPeriod.isUndefined())
		throw ASIException("TOffGameStat::validateForUpdate: fStatPeriod.isUndefined()");

	if((fStatPeriod == stp_SeasonGame) && (fStatDate == TDateTime()))
		throw ASIException("TOffGameStat::validateForUpdate: (fStatPeriod == stp_SeasonGame) && (fStatDate == TDateTime())");

	if((fStatPeriod != stp_SeasonGame) && (fStatDate != TDateTime()))
		throw ASIException("TOffGameStat::validateForUpdate: (fStatPeriod != stp_SeasonGame) && (fStatDate != TDateTime())");
}

/******************************************************************************/

CStrVar TOffGameStat::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(PlayerID = \"%s\") and ",fPlayerID.c_str());
	str.concatVarg("(StatPeriod = \"%s\") and ",fStatPeriod.c_str());
	str.concatVarg("(StatDate = \"%s\")",FormatDateTimeStr(fStatDate).c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TOffGameStatVector::removeByID(const TPlayerStatID playerStatID,
	const CommonAccessMode getMode)
{
	iterator iter;
	
	iter = std::find_if(begin(),end(),findIDCompare(playerStatID));
	if(iter != end())
		erase(iter);
	else if(getMode == cam_MustExist)
		throw ASIException("TOffGameStatVector::removeByID: not found");
}

/******************************************************************************/
/******************************************************************************/

void TDefGameStat::clear()
{
	TQueryDataSetRecord::clear();
	
	fPlayerID.clear();
	fStatPeriod.clear();
	fStatDate = TDateTime();

	fTotalPoints = 0;
}

/******************************************************************************/

TPlayerDateID TDefGameStat::getPlayerDateID(void) const
{
	if(fStatPeriod != stp_SeasonGame)
		throw ASIException("TDefGameStat::getPlayerDateID: fStatDate undefined for fStatPeriod");

	return(TPlayerDateID(fPlayerID,fStatDate));
}

/******************************************************************************/

TDefGameStatPtr TDefGameStat::newInstance()
{
	TDefGameStatPtr defGameStatPtr =
		ASFantasyObjectBuilder::getThe().newDefGameStat();
	defGameStatPtr->clear();
	return(defGameStatPtr);
}

/******************************************************************************/

void TDefGameStat::readFromDataSet(TDataSet& dataSet)
{
	fPlayerID = dataSet.FieldByName("PlayerID")->AsInteger;
	fStatPeriod = dataSet.FieldByName("StatPeriod")->AsString.c_str();
	fStatDate = dataSet.FieldByName("StatDate")->AsFloat;	//BOB AsDateTime

	fTotalPoints = (short)dataSet.FieldByName("TotalPoints")->AsInteger;
}

/******************************************************************************/

void TDefGameStat::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("PlayerID")->AsInteger = fPlayerID.getID();
	dataSet.FieldByName("StatPeriod")->AsString = fStatPeriod.c_str();
	dataSet.FieldByName("StatDate")->AsDateTime = fStatDate;

	dataSet.FieldByName("TotalPoints")->AsInteger = fTotalPoints;
}

/******************************************************************************/

void TDefGameStat::validateForUpdate()
{
	if(fPlayerID.isUndefined())
		throw ASIException("TDefGameStat::validateForUpdate: fPlayerID.isUndefined()");
	if(fStatPeriod.isUndefined())
		throw ASIException("TDefGameStat::validateForUpdate: fStatPeriod.isUndefined()");

	if((fStatPeriod == stp_SeasonGame) && (fStatDate == TDateTime()))
		throw ASIException("TDefGameStat::validateForUpdate: (fStatPeriod == stp_SeasonGame) && (fStatDate == TDateTime())");

	if((fStatPeriod != stp_SeasonGame) && (fStatDate != TDateTime()))
		throw ASIException("TDefGameStat::validateForUpdate: (fStatPeriod == stp_SeasonGame) && (fStatDate == TDateTime())");
}

/******************************************************************************/

CStrVar TDefGameStat::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(PlayerID = \"%s\") and ",fPlayerID.c_str());
	str.concatVarg("(StatPeriod = \"%s\") and ",fStatPeriod.c_str());
	str.concatVarg("(StatDate = \"%s\")",FormatDateTimeStr(fStatDate).c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TDefGameStatVector::removeByID(const TPlayerStatID playerStatID,
	const CommonAccessMode getMode)
{
	iterator iter;
	
	iter = std::find_if(begin(),end(),findIDCompare(playerStatID));
	if(iter != end())
		erase(iter);
	else if(getMode == cam_MustExist)
		throw ASIException("TDefGameStatVector::removeByID: not found");
}

/******************************************************************************/
/******************************************************************************/

void TDraftOrder::clear()
{
	TQueryDataSetRecord::clear();
	
	fLeagueID.clear();
	
	fDraftRoundVector.erase(fDraftRoundVector.begin(),fDraftRoundVector.end());
}

/******************************************************************************/

TDraftOrderPtr TDraftOrder::newInstance()
{
	TDraftOrderPtr draftOrderPtr = ASFantasyObjectBuilder::getThe().newDraftOrder();
	draftOrderPtr->clear();
	return(draftOrderPtr);
}

/******************************************************************************/

void TDraftOrder::readFromDataSet(TDataSet& dataSet)
{
	TTeamIDVector teamIDVector;
	TTeamID teamID;
	CStr31 fieldName;
	int i,j,numRounds,numTeams;
	CStrVar dataStr;
	auto_ptr<TStream> pStream(new TMemoryStream());
	auto_ptr<TPipeTextFiler> pFiler(new TPipeTextFiler(pStream.get(),false));

	fLeagueID = dataSet.FieldByName("LeagueID")->AsInteger;
	numRounds = dataSet.FieldByName("NumRounds")->AsInteger;
	numTeams = dataSet.FieldByName("NumTeams")->AsInteger;

	fDraftRoundVector.erase(fDraftRoundVector.begin(),fDraftRoundVector.end());
	
	for(i = 0; i < numRounds; i++)
	{
		teamIDVector.erase(teamIDVector.begin(),teamIDVector.end());
	
		fieldName.CopyVarg("Round%02d",i + 1);
		dataStr = dataSet.FieldByName(fieldName.c_str())->AsString.c_str();
		ConvertStringToStream(dataStr,pStream.get());
		pFiler->setupForRead();

		for(j = 0; j < numTeams; j++)
		{
			teamID = pFiler->readLong();
			teamIDVector.push_back(teamID);
		}
		pFiler->readEOL();	//verify all teamIDs have been read
		
		fDraftRoundVector.push_back(teamIDVector);
	}
}

/******************************************************************************/

void TDraftOrder::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	int i,j,numRounds,numTeams;
	CStrVar dataStr;
	auto_ptr<TStream> pStream(new TMemoryStream());
	auto_ptr<TPipeTextFiler> pFiler(new TPipeTextFiler(pStream.get(),false));

	//this code assumes ::validateForUpdate has already been called.
	
	numRounds = fDraftRoundVector.size();
	numTeams = (numRounds > 0) ? fDraftRoundVector.begin()->size() : 0;
	
	dataSet.FieldByName("LeagueID")->AsInteger = fLeagueID.getID();
	dataSet.FieldByName("NumRounds")->AsInteger = numRounds;
	dataSet.FieldByName("NumTeams")->AsInteger = numTeams;

	for(i = 0; i < NumDraftRounds(); i++)
	{
		pFiler->setupForRead(); //BOB this is really setupForWrite()

		dataStr.clear();
		if(i < numRounds)
		{
			for(j = 0; j < numTeams; j++)
				pFiler->writeLong(fDraftRoundVector[i][j].getID());
			pFiler->writeEOL();	//to verify all teamIDs have been read in readFromDataSet

			dataStr = ConvertStreamToString(pStream.get());
		}

		fieldName.CopyVarg("Round%02d",i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsString = dataStr.c_str();
	}
}

/******************************************************************************/

void TDraftOrder::validateForUpdate()
{
	TDraftRoundVector::iterator iter;
	int numTeams;
	
	if(fLeagueID.isUndefined())
		throw ASIException("TDraftOrder::validateForUpdate: fLeagueID.isUndefined()");

	// fDraftRoundVector must contains NumDraftRounds rounds.
	if(cast2int(fDraftRoundVector.size()) != NumDraftRounds())
		throw ASIException("TDraftOrder::validateForUpdate: fDraftRoundVector.size() != NumDraftRounds");

	// Number of teams in each round must be the same.
	numTeams = fDraftRoundVector.begin()->size();
	for(iter = fDraftRoundVector.begin() + 1; iter != fDraftRoundVector.end();
		iter++)
	{
		if(cast2int(iter->size()) != numTeams)
			throw ASIException("TDraftOrder::validateForUpdate: numTeams is not consistant between rounds");
	}
}

/******************************************************************************/

CStrVar TDraftOrder::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(LeagueID = \"%s\")",fLeagueID.c_str());
	
	return(str);
}


/******************************************************************************/
/******************************************************************************/

void TDraftRanking::clear()
{
	TQueryDataSetRecord::clear();
	
	fTeamID.clear();
	
	fPlayerIDVector.erase(fPlayerIDVector.begin(),fPlayerIDVector.end());
}

/******************************************************************************/

TDraftRankingPtr TDraftRanking::newInstance()
{
	TDraftRankingPtr draftRankingPtr =
		ASFantasyObjectBuilder::getThe().newDraftRanking();
	draftRankingPtr->clear();
	return(draftRankingPtr);
}

/******************************************************************************/
	
void TDraftRanking::readFromDataSet(TDataSet& dataSet)
{
	TPlayerID playerID;
	CStr31 fieldName;
	int i,numPlayers;

	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;
	numPlayers = dataSet.FieldByName("NumRankings")->AsInteger;

	fPlayerIDVector.erase(fPlayerIDVector.begin(),fPlayerIDVector.end());
	
	for(i = 0; i < numPlayers; i++)
	{
		fieldName.CopyVarg("Rank%03d",i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
//		fPlayerIDVector.insert(fPlayerIDVector.end(),(TPlayerID&)playerID);
		fPlayerIDVector.push_back(playerID);
	}
}

/******************************************************************************/

void TDraftRanking::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	int i,numPlayers = fPlayerIDVector.size();
	
	dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();
	dataSet.FieldByName("NumRankings")->AsInteger = numPlayers;

	for(i = 0; i < MaxDraftRankingPlayers(); i++)
	{
		fieldName.CopyVarg("Rank%03d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numPlayers) ? fPlayerIDVector[i].getID() : 0;
	}
}

/******************************************************************************/

void TDraftRanking::validateForUpdate()
{
	if(fTeamID.isUndefined())
		throw ASIException("TDraftRanking::validateForUpdate: fTeamID.isUndefined()");

	if(cast2int(fPlayerIDVector.size()) > MaxDraftRankingPlayers())
		throw ASIException("TDraftRanking::validateForUpdate: fPlayerIDVector.size() > MaxDraftRankingPlayers");
}

/******************************************************************************/

CStrVar TDraftRanking::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(TeamID = \"%s\")",fTeamID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TDraftResult::clear()
{
	TQueryDataSetRecord::clear();
	
	fLeagueID.clear();
	fDraftPickRoundVector.erase(fDraftPickRoundVector.begin(),
		fDraftPickRoundVector.end());
}

/******************************************************************************/

TDraftResultPtr TDraftResult::newInstance()
{
	TDraftResultPtr draftResultPtr = ASFantasyObjectBuilder::getThe().newDraftResult();
	draftResultPtr->clear();
	return(draftResultPtr);
}

/******************************************************************************/

void TDraftResult::readFromDataSet(TDataSet& dataSet)
{
	TDraftPickVector draftPickVector;
	TTeamID teamID;
	TPlayerID playerID;
	CStr31 fieldName;
	int i,j,numRounds,numTeams;
	CStrVar dataStr;
	auto_ptr<TStream> pStream(new TMemoryStream());
	auto_ptr<TPipeTextFiler> pFiler(new TPipeTextFiler(pStream.get(),false));

	fLeagueID = dataSet.FieldByName("LeagueID")->AsInteger;
	numRounds = dataSet.FieldByName("NumRounds")->AsInteger;
	numTeams = dataSet.FieldByName("NumTeams")->AsInteger;

	fDraftPickRoundVector.erase(fDraftPickRoundVector.begin(),fDraftPickRoundVector.end());
	
	for(i = 0; i < numRounds; i++)
	{
		draftPickVector.erase(draftPickVector.begin(),draftPickVector.end());
	
		fieldName.CopyVarg("Round%02d",i + 1);
		dataStr = dataSet.FieldByName(fieldName.c_str())->AsString.c_str();
		ConvertStringToStream(dataStr,pStream.get());
		pFiler->setupForRead();

		for(j = 0; j < numTeams; j++)
		{
			teamID = pFiler->readLong();
			playerID = pFiler->readLong();
			draftPickVector.push_back(TDraftPick(teamID,playerID));
		}
		pFiler->readEOL();	//verify all teamIDs have been read
		
		fDraftPickRoundVector.push_back(draftPickVector);
	}
}

/******************************************************************************/

void TDraftResult::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	int i,j,numRounds,numTeams;
	CStrVar dataStr;
	auto_ptr<TStream> pStream(new TMemoryStream());
	auto_ptr<TPipeTextFiler> pFiler(new TPipeTextFiler(pStream.get(),false));

	//this code assumes ::validateForUpdate has already been called.
	
	numRounds = fDraftPickRoundVector.size();
	numTeams = (numRounds > 0) ? fDraftPickRoundVector.begin()->size() : 0;
	
	dataSet.FieldByName("LeagueID")->AsInteger = fLeagueID.getID();
	dataSet.FieldByName("NumRounds")->AsInteger = numRounds;
	dataSet.FieldByName("NumTeams")->AsInteger = numTeams;

	for(i = 0; i < NumDraftRounds(); i++)
	{
		pFiler->setupForRead(); //BOB this is really setupForWrite()

		dataStr.clear();
		if(i < numRounds)
		{
			for(j = 0; j < numTeams; j++)
			{
				pFiler->writeLong(fDraftPickRoundVector[i][j].fTeamID.getID());
				pFiler->writeLong(fDraftPickRoundVector[i][j].fPlayerID.getID());
			}
			pFiler->writeEOL();	//to verify all teamIDs have been read in readFromDataSet

			dataStr = ConvertStreamToString(pStream.get());
		}

		fieldName.CopyVarg("Round%02d",i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsString = dataStr.c_str();
	}
}

/******************************************************************************/

void TDraftResult::validateForUpdate()
{
	TDraftPickRoundVector::iterator iter;
	int numTeams;
	
	if(fLeagueID.isUndefined())
		throw ASIException("TDraftResult::validateForUpdate: fLeagueID.isUndefined()");

	// fDraftPickRoundVector must not be greater than NumDraftRounds rounds.
	if(cast2int(fDraftPickRoundVector.size()) > NumDraftRounds())
		throw ASIException("TDraftResult::validateForUpdate: fDraftPickRoundVector.size() > NumDraftRounds");

	// Number of teams in each round must be the same.
	if(fDraftPickRoundVector.size() > 0)
	{
		numTeams = fDraftPickRoundVector.begin()->size();
		for(iter = fDraftPickRoundVector.begin() + 1; iter != fDraftPickRoundVector.end();
			iter++)
		{
			if(cast2int(iter->size()) != numTeams)
				throw ASIException("TDraftResult::validateForUpdate: numTeams is not consistant between rounds");
		}
	}
}

/******************************************************************************/

CStrVar TDraftResult::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(LeagueID = \"%s\")",fLeagueID.c_str());
	
	return(str);
}


/******************************************************************************/
/******************************************************************************/

bool TScheduleDayGame::wasGameTied() const
{
	if(wasGamePlayed())
		return(fVisitScore == fHomeScore);
		
	throw ASIException("TScheduleDayGame::wasGameTied: game not played");
}

/******************************************************************************/

bool TScheduleDayGame::wasHomeTeamWinner() const
{
	if(wasGamePlayed() && !wasGameTied())
		return(getWinningTeamID() == fHomeTeamID);
		
	throw ASIException("TScheduleDayGame::wasHomeTeamWinner: no winner");
}

/******************************************************************************/

TTeamID TScheduleDayGame::getWinningTeamID() const
{
	if(wasGamePlayed() && !wasGameTied())
	{
		if(fVisitScore > fHomeScore)
			return(fVisitTeamID);

		return(fHomeTeamID);
	}
	
	throw ASIException("TScheduleDayGame::getWinningTeamID: no winner");
}

/******************************************************************************/
	
TTeamID TScheduleDayGame::getLosingTeamID() const
{
	if(wasGamePlayed() && !wasGameTied())
	{
		if(fVisitScore > fHomeScore)
			return(fHomeTeamID);
			
		return(fVisitTeamID);
	}
	
	throw ASIException("TScheduleDayGame::getLosingTeamID: no loser");
}

/******************************************************************************/

short TScheduleDayGame::getWinningScore() const
{
	if(wasGamePlayed() && !wasGameTied())
	{
		if(fVisitScore > fHomeScore)
			return(fVisitScore);

		return(fHomeScore);
	}
	
	throw ASIException("TScheduleDayGame::getWinningScore: no winner");
}

/******************************************************************************/

short TScheduleDayGame::getLosingScore() const
{
	if(wasGamePlayed() && !wasGameTied())
	{
		if(fVisitScore > fHomeScore)
			return(fHomeScore);
			
		return(fVisitScore);
	}
	
	throw ASIException("TScheduleDayGame::getLosingScore: no loser");
}

/******************************************************************************/

bool TScheduleDayGame::wasMatchUpBetween(TTeamID teamID,TTeamID oppTeamID) const
{
	if(fHomeTeamID == teamID)
	{
		if(fVisitTeamID == oppTeamID)
			return(true);
	}
	else if(fHomeTeamID == oppTeamID)
	{
		if(fVisitTeamID == teamID)
			return(true);
	}

	return(false);
}

/******************************************************************************/

TTeamID TScheduleDayGame::getOppTeamID(TTeamID teamID) const
{
	if(teamID == fHomeTeamID)
		return(fVisitTeamID);
		
	if(teamID == fVisitTeamID)
		return(fHomeTeamID);
		
	throw ASIException("TScheduleDayGame::getOppTeamID: teamID not in game");
}

/******************************************************************************/
/******************************************************************************/

void TScheduleDay::clear()
{
	TQueryDataSetRecord::clear(); 

	fLeagueID = TLeagueID();
	fGameDate = TDateTime();

	fStatus.clear();

	fEarlyProfGameDate = TDateTime();
	fLateProfGameDate = TDateTime();
	fProfGameWeek.clear();

	fScheduleDayGameVector.erase(fScheduleDayGameVector.begin(),
		fScheduleDayGameVector.end());
}

/******************************************************************************/

bool TScheduleDay::getScheduleDayGameByTeamID(TTeamID teamID,
	TScheduleDayGame& scheduleDayGame) const
{
	TScheduleDayGameVector::const_iterator iter;
	
	for(iter = fScheduleDayGameVector.begin(); iter !=
		fScheduleDayGameVector.end(); iter++)
	{
		const TScheduleDayGame& game = *iter;

		if((game.getVisitTeamID() == teamID) ||
			(game.getHomeTeamID() == teamID))
		{
			scheduleDayGame = game;
			return(true);
		}
	}

	return(false);
}

/******************************************************************************/

int TScheduleDay::getScheduleDayGamePositionByTeamID(TTeamID teamID) const
{
	TScheduleDayGameVector::const_iterator iter;
	
	for(iter = fScheduleDayGameVector.begin(); iter !=
		fScheduleDayGameVector.end(); iter++)
	{
		const TScheduleDayGame& game = *iter;

		if((game.getVisitTeamID() == teamID) ||
			(game.getHomeTeamID() == teamID))
		{
			return(iter - fScheduleDayGameVector.begin());
		}
	}

	return(-1);
}

/******************************************************************************/

TScheduleDayPtr TScheduleDay::newInstance()
{
	TScheduleDayPtr scheduleDayPtr = ASFantasyObjectBuilder::getThe().newScheduleDay();
	scheduleDayPtr->clear();
	return(scheduleDayPtr);
}

/******************************************************************************/
	
void TScheduleDay::readFromDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	CStr31 fieldNamePrefix; 
	int i,numGames;
	TScheduleDayGame scheduleDayGame;
	
	fLeagueID = dataSet.FieldByName("LeagueID")->AsInteger;
	fGameDate = DataSetReadDateTime(dataSet,"GameDate");

	fStatus = dataSet.FieldByName("Status")->AsString.c_str();

	fEarlyProfGameDate = GetDateOnly(DataSetReadDateTime(dataSet,"EarlyProfGameDateTime"));
	fEarlyProfGameTime = GetTimeOnly(DataSetReadDateTime(dataSet,"EarlyProfGameDateTime"));
	fLateProfGameDate = DataSetReadDateTime(dataSet,"LateProfGameDate");
	fProfGameWeek = (short)dataSet.FieldByName("ProfGameWeek")->AsInteger;
	
	fieldNamePrefix.Copy("SchedGame");
	
	/* fScheduleDayGameVector */
	numGames = dataSet.FieldByName("NumScheduleGames")->AsInteger;

	fScheduleDayGameVector.erase(fScheduleDayGameVector.begin(),
		fScheduleDayGameVector.end());
	
	for(i = 0; i < numGames; i++)
	{
		scheduleDayGame.clear();

		scheduleDayGame.setWasGamePlayed(fStatus == sdst_Completed);
		
		fieldName.CopyVarg("%s%02dVisitTeamID",fieldNamePrefix.c_str(),i + 1);
		scheduleDayGame.setVisitTeamID(
			dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fieldName.CopyVarg("%s%02dHomeTeamID",fieldNamePrefix.c_str(),i + 1);
		scheduleDayGame.setHomeTeamID(
			dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fieldName.CopyVarg("%s%02dVisitScore",fieldNamePrefix.c_str(),i + 1);
		scheduleDayGame.setVisitScore(
			(short)dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fieldName.CopyVarg("%s%02dHomeScore",fieldNamePrefix.c_str(),i + 1);
		scheduleDayGame.setHomeScore(
			(short)dataSet.FieldByName(fieldName.c_str())->AsInteger);
		
		fScheduleDayGameVector.push_back(scheduleDayGame);
	}
}

/******************************************************************************/

void TScheduleDay::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	CStr31 fieldNamePrefix; 
	int i,numGames;
	TScheduleDayGame scheduleDayGame;
	
	dataSet.FieldByName("LeagueID")->AsInteger = fLeagueID.getID();
	DataSetWriteDateTime(dataSet,"GameDate",fGameDate);

	dataSet.FieldByName("Status")->AsString = fStatus.c_str();

	DataSetWriteDateTime(dataSet,"EarlyProfGameDateTime",
		fEarlyProfGameDate + fEarlyProfGameTime);
	DataSetWriteDateTime(dataSet,"LateProfGameDate",fLateProfGameDate);
	dataSet.FieldByName("ProfGameWeek")->AsInteger = fProfGameWeek.getID();

	fieldNamePrefix.Copy("SchedGame");
	
	/* fScheduleDayGameVector */
	numGames = fScheduleDayGameVector.size();
	
	dataSet.FieldByName("NumScheduleGames")->AsInteger = numGames;

	for(i = 0; i < MaxGamesPerDay(); i++)
	{
		if(i < numGames)
			scheduleDayGame = fScheduleDayGameVector[i];
		else
			scheduleDayGame.clear();

		fieldName.CopyVarg("%s%02dVisitTeamID",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			scheduleDayGame.getVisitTeamID().getID();
			
		fieldName.CopyVarg("%s%02dHomeTeamID",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			scheduleDayGame.getHomeTeamID().getID();
		
		fieldName.CopyVarg("%s%02dVisitScore",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			scheduleDayGame.getVisitScore();
		
		fieldName.CopyVarg("%s%02dHomeScore",fieldNamePrefix.c_str(),i + 1);
		dataSet.FieldByName(fieldName.c_str())->AsInteger = 
			scheduleDayGame.getHomeScore();
	}
}

/******************************************************************************/

void TScheduleDay::validateForUpdate()
{
	if(fLeagueID.isUndefined())
		throw ASIException("TScheduleDay::validateForUpdate: fLeagueID.isUndefined()");

	if(fGameDate == TDateTime())
		throw ASIException("TScheduleDay::validateForUpdate: fGameDate == TDateTime()");

	if(fStatus.isUndefined())
		throw ASIException("TScheduleDay::validateForUpdate: fStatus.isUndefined()");

	if(fEarlyProfGameDate == TDateTime())
		throw ASIException("TScheduleDay::validateForUpdate: fEarlyProfGameDate == TDateTime()");

	if(fLateProfGameDate == TDateTime())
		throw ASIException("TScheduleDay::validateForUpdate: fLateProfGameDate == TDateTime()");

	if(fProfGameWeek.isUndefined())
		throw ASIException("TScheduleDay::validateForUpdate: fProfGameWeek.isUndefined()");
}

/******************************************************************************/

CStrVar TScheduleDay::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(LeagueID = \"%s\") and ",fLeagueID.c_str());
	str.concatVarg("(GameDate = \"%s\")",FormatDateTimeStr(fGameDate).c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

double TScheduleDayVector::getHeadToHeadWinningPercentage(TTeamID teamID,
	TTeamID oppTeamID) const
{
	int wins = 0;
	int loses = 0;
	const_iterator iter;

	for(iter = begin(); iter != end(); iter++)
	{
		const TScheduleDayPtr& scheduleDayPtr = *iter;
		TScheduleDayGame scheduleDayGame;

		if(scheduleDayPtr->getScheduleDayGameByTeamID(teamID,scheduleDayGame))
		{
			if(scheduleDayGame.wasMatchUpBetween(teamID,oppTeamID) &&
				scheduleDayGame.wasGamePlayed() && !scheduleDayGame.wasGameTied())
			{
				if(teamID == scheduleDayGame.getWinningTeamID())
					wins++;
				else
					loses++;
			}
		}
	}

	return(calcWinningPercentage(wins,loses));
}

/******************************************************************************/

short TScheduleDayVector::getHeadToHeadTotalPoints(TTeamID teamID,
	TTeamID oppTeamID) const
{
	short totalPoints = 0;
	const_iterator iter;

	for(iter = begin(); iter != end(); iter++)
	{
		const TScheduleDayPtr& scheduleDayPtr = *iter;
		TScheduleDayGame scheduleDayGame;

		if(scheduleDayPtr->getScheduleDayGameByTeamID(teamID,scheduleDayGame))
		{
			if(scheduleDayGame.wasMatchUpBetween(teamID,oppTeamID) &&
				scheduleDayGame.wasGamePlayed())
			{
				if(teamID == scheduleDayGame.getHomeTeamID())
					totalPoints += scheduleDayGame.getHomeScore();
				else
					totalPoints += scheduleDayGame.getVisitScore();
			}
		}
	}

	return(totalPoints);
}

/******************************************************************************/

short TScheduleDayVector::getDivTotalPointsForTeam(TTeamID teamID,
	const TTeamIDVector& divTeamIDVector) const
{
	short totalPoints = 0;
	const_iterator iter;

	for(iter = begin(); iter != end(); iter++)
	{
		const TScheduleDayPtr& scheduleDayPtr = *iter;
		TScheduleDayGame scheduleDayGame;

		if(scheduleDayPtr->getScheduleDayGameByTeamID(teamID,scheduleDayGame))
		{
			if(scheduleDayGame.wasGamePlayed())
			{
				TTeamID oppTeamID = scheduleDayGame.getOppTeamID(teamID);

				// Was this a divison game? (i.e. is oppTeamID in my division)
				if(divTeamIDVector.contains(oppTeamID))
				{
					if(teamID == scheduleDayGame.getHomeTeamID())
						totalPoints += scheduleDayGame.getHomeScore();
					else
						totalPoints += scheduleDayGame.getVisitScore();
				}
			}
		}
	}

	return(totalPoints);
}

/******************************************************************************/

// Assumes vector is sorted by GameDate.

TScheduleDayPtr TScheduleDayVector::getLastWeeksScheduleDay() const
{
	TDateTime today = TDateTime::CurrentDate();

	const_reverse_iterator iter(end());
	const_reverse_iterator iter_end(begin());

	for(; iter != iter_end; ++iter)
		if(today >= (*iter)->getGameDate())
			return(*iter);

	return(TScheduleDayPtr());
}

/******************************************************************************/

// Assumes vector is sorted by GameDate.

TScheduleDayPtr TScheduleDayVector::getThisWeeksScheduleDay() const
{
	TDateTime today = TDateTime::CurrentDate();
	const_iterator iter;

	for(iter = begin(); iter != end(); ++iter)
		if((*iter)->getGameDate() > today)
			return(*iter);

	return(TScheduleDayPtr());
}

/******************************************************************************/

// Assumes vector is sorted by GameDate.

TScheduleDayPtr TScheduleDayVector::getLastCompletedScheduleDay() const
{
	const_reverse_iterator iter(end());
	const_reverse_iterator iter_end(begin());

	for(; iter != iter_end; ++iter)
		if((*iter)->getStatus() == sdst_Completed)
			return(*iter);

	return(TScheduleDayPtr());
}

/******************************************************************************/

// Assumes vector is sorted by GameDate.

TScheduleDayPtr TScheduleDayVector::getInProgressScheduleDay() const
{
	const_iterator iter;

	for(iter = begin(); iter != end(); ++iter)
		if((*iter)->getStatus() == sdst_InProgress)
			return(*iter);

	return(TScheduleDayPtr());
}

/******************************************************************************/

// Assumes vector is sorted by GameDate.

TScheduleDayPtr TScheduleDayVector::getFirstNotStartedScheduleDay() const
{
	const_iterator iter;

	for(iter = begin(); iter != end(); ++iter)
		if((*iter)->getStatus() == sdst_NotStarted)
			return(*iter);

	return(TScheduleDayPtr());
}

/******************************************************************************/

// Assumes vector is sorted by GameDate.

int TScheduleDayVector::getGameDatePosition(TDateTime gameDate,
	const CommonAccessMode getMode) const
{
	const_iterator iter;

	iter = std::lower_bound(begin(),end(),gameDate,gameDateLessSearch());
		
	if(iter != end())
	{
		if((*iter)->getGameDate() == gameDate)
			return(iter - begin());

		if(getMode == cam_MustExist)
			throw ASIException("TScheduleDayVector::getGameDatePosition: not found");
	}
	
	return(-1);
}

/******************************************************************************/
/******************************************************************************/

void TGameResult::clear()
{
	TQueryDataSetRecord::clear();
	
	fTeamID.clear();
	fGameDate = TDateTime();
	fOppTeamID.clear();

	fTotalPoints = 0;

	fOffPlayerDatesVector.erase(fOffPlayerDatesVector.begin(),
		fOffPlayerDatesVector.end());
	fDefPlayerDatesVector.erase(fDefPlayerDatesVector.begin(),
		fDefPlayerDatesVector.end());
}

/******************************************************************************/

void TGameResult::calcTotalPoints()
{
	fTotalPoints = cast2short(fOffPlayerDatesVector.calcTotalPoints() +
		fDefPlayerDatesVector.calcTotalPoints());

	setHasChanged();
}

/******************************************************************************/

TGameResultPtr TGameResult::newInstance()
{
	TGameResultPtr gameResultPtr = ASFantasyObjectBuilder::getThe().newGameResult();
	gameResultPtr->clear();
	return(gameResultPtr);
}

/******************************************************************************/

void TGameResult::readPlayerDatesVectorFromDataSet(TDataSet& dataSet,
	const char* fieldPrefix,TPlayerDatesVector& playerDatesVector)
{
	TPlayerDates playerDates;
	CStr31 fieldName;
	int i,numPlayers;
	int j,numDates;
	TDateTime date;
	CStrVar datesStr;
	auto_ptr<TStream> pStream(new TMemoryStream());
	auto_ptr<TPipeTextFiler> pFiler(new TPipeTextFiler(pStream.get(),false));

	playerDatesVector.erase(playerDatesVector.begin(),playerDatesVector.end());

	fieldName.CopyVarg("Num%sPlayers",fieldPrefix);
	numPlayers = dataSet.FieldByName(fieldName.c_str())->AsInteger;

	for(i = 0; i < numPlayers; i++)
	{
		playerDates.clear();

		fieldName.CopyVarg("%sPlayer%02d",fieldPrefix,i + 1);
		playerDates.fPlayerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;

		fieldName.CopyVarg("%sPlayer%02dPoints",fieldPrefix,i + 1);
		playerDates.fPoints = (short)dataSet.FieldByName(fieldName.c_str())->AsInteger;

		fieldName.CopyVarg("%sPlayer%02dDates",fieldPrefix,i + 1);
		datesStr = dataSet.FieldByName(fieldName.c_str())->AsString.c_str();
		ConvertStringToStream(datesStr,pStream.get());
		pFiler->setupForRead();

		numDates = pFiler->readShort();
		for(j = 0; j < numDates; j++)
		{
			date = pFiler->readDate();
			playerDates.fDateTimeVector.push_back(date);
		}
		pFiler->readEOL();	//verify all dates have been read

		playerDatesVector.push_back(playerDates);
	}
}

/******************************************************************************/

void TGameResult::readFromDataSet(TDataSet& dataSet)
{
	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;
	fGameDate = dataSet.FieldByName("GameDate")->AsFloat;		//BOB AsDateTime;
	fOppTeamID = dataSet.FieldByName("OppTeamID")->AsInteger;

	fTotalPoints = (short)dataSet.FieldByName("TotalPoints")->AsInteger;

	readPlayerDatesVectorFromDataSet(dataSet,"Off",fOffPlayerDatesVector);
	readPlayerDatesVectorFromDataSet(dataSet,"Def",fDefPlayerDatesVector);
}

/******************************************************************************/

void TGameResult::writePlayerDatesVectorToDataSet(TDataSet& dataSet,
	const char* fieldPrefix,const TPlayerDatesVector& playerDatesVector)
{
	TPlayerDates playerDates;
	CStr31 fieldName;
	int i,numPlayers;
	int j,numDates;
	TDateTime date;
	CStrVar datesStr;
	auto_ptr<TPipeTextFiler> pFiler(new TPipeTextFiler());

	numPlayers = playerDatesVector.size();

	fieldName.CopyVarg("Num%sPlayers",fieldPrefix);
	dataSet.FieldByName(fieldName.c_str())->AsInteger = numPlayers;

	for(i = 0; i < MaxPlayersOfTypeInGameResult(); i++)
	{
		if(i < numPlayers)
		{
			playerDates = playerDatesVector[i];

			fieldName.CopyVarg("%sPlayer%02d",fieldPrefix,i + 1);
			dataSet.FieldByName(fieldName.c_str())->AsInteger = playerDates.fPlayerID.getID();

			fieldName.CopyVarg("%sPlayer%02dPoints",fieldPrefix,i + 1);
			dataSet.FieldByName(fieldName.c_str())->AsInteger = playerDates.fPoints;

			pFiler->resetForWrite();

			numDates = playerDates.fDateTimeVector.size();
			pFiler->writeShort((short)numDates);
			
			for(j = 0; j < numDates; j++)
				pFiler->writeDate(playerDates.fDateTimeVector[j]);
			pFiler->writeEOL();	//to verify all dates have been read in readFromDataSet

			datesStr = ConvertStreamToString(pFiler->getStream());

			fieldName.CopyVarg("%sPlayer%02dDates",fieldPrefix,i + 1);
			dataSet.FieldByName(fieldName.c_str())->AsString = datesStr.c_str();
		}
		else
		{
			fieldName.CopyVarg("%sPlayer%02d",fieldPrefix,i + 1);
			dataSet.FieldByName(fieldName.c_str())->Clear();

			fieldName.CopyVarg("%sPlayer%02dPoints",fieldPrefix,i + 1);
			dataSet.FieldByName(fieldName.c_str())->Clear();

			fieldName.CopyVarg("%sPlayer%02dDates",fieldPrefix,i + 1);
			dataSet.FieldByName(fieldName.c_str())->Clear();
		}
	}
}

/******************************************************************************/

void TGameResult::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();
	dataSet.FieldByName("GameDate")->AsDateTime = fGameDate;
	dataSet.FieldByName("OppTeamID")->AsInteger = fOppTeamID.getID();

	dataSet.FieldByName("TotalPoints")->AsInteger = fTotalPoints;

	writePlayerDatesVectorToDataSet(dataSet,"Off",fOffPlayerDatesVector);
	writePlayerDatesVectorToDataSet(dataSet,"Def",fDefPlayerDatesVector);
}

/******************************************************************************/

void TGameResult::validateForUpdate()
{
	if(fTeamID.isUndefined())
		throw ASIException("TGameResult::validateForUpdate: fTeamID.isUndefined()");
		
	if(fGameDate == TDateTime())
		throw ASIException("TGameResult::validateForUpdate: fGameDate == TDateTime()");
		
	if(fOppTeamID.isUndefined())
		throw ASIException("TGameResult::validateForUpdate: fOppTeamID.isUndefined()");
}

/******************************************************************************/

CStrVar TGameResult::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(TeamID = \"%s\") and ",fTeamID.c_str());
	str.concatVarg("(GameDate = \"%s\")",FormatDateTimeStr(fGameDate).c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

TGameResultPtr TGameResultVector::findByTeamID(const TTeamID teamID,
	const CommonAccessMode getMode) const
{
	const_iterator iter;
	
	iter = std::find_if(begin(),end(),findTeamIDCompare(teamID));
	if(iter != end())
		return(*iter);

	if(getMode == cam_MustExist)
		throw ASIException("TGameResultVector::findByID: not found (%s)",
			teamID.c_str());

	return(TGameResultPtr());
}

/******************************************************************************/
/******************************************************************************/

void TFreeAgentClaim::clear()
{
	TQueryDataSetRecord::clear();

	fFreeAgentClaimID.clear();

	fTeamID.clear();
	fClaimDateTime = TDateTime();
	fStatus.clear();

	fClaimPlayerID.clear();
	fReleasePlayerID.clear();

	fProcessedDate = TDateTime();
	fProcessedStatus.clear();
}

/******************************************************************************/

TFreeAgentClaimPtr TFreeAgentClaim::newInstance()
{
	TFreeAgentClaimPtr freeAgentClaimPtr =
		ASFantasyObjectBuilder::getThe().newFreeAgentClaim();
	freeAgentClaimPtr->clear();
	return(freeAgentClaimPtr);
}

/******************************************************************************/
	
void TFreeAgentClaim::readFromDataSet(TDataSet& dataSet)
{
	fFreeAgentClaimID = dataSet.FieldByName("FreeAgentClaimID")->AsInteger;

	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;
	fClaimDateTime = dataSet.FieldByName("ClaimDateTime")->AsFloat;	//BOB AsDateTime
	fStatus = dataSet.FieldByName("Status")->AsString.c_str();

	fClaimPlayerID = dataSet.FieldByName("ClaimPlayerID")->AsInteger;
	fReleasePlayerID = dataSet.FieldByName("ReleasePlayerID")->AsInteger;

	fProcessedDate = dataSet.FieldByName("ProcessedDate")->AsFloat;	//BOB AsDateTime
	fProcessedStatus = dataSet.FieldByName("ProcessedStatus")->AsString.c_str();
}

/******************************************************************************/

void TFreeAgentClaim::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("FreeAgentClaimID")->AsInteger = fFreeAgentClaimID.getID();

	dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();
	dataSet.FieldByName("ClaimDateTime")->AsDateTime = fClaimDateTime;
	dataSet.FieldByName("Status")->AsString = fStatus.c_str();

	dataSet.FieldByName("ClaimPlayerID")->AsInteger = fClaimPlayerID.getID();
	dataSet.FieldByName("ReleasePlayerID")->AsInteger = fReleasePlayerID.getID();

	dataSet.FieldByName("ProcessedDate")->AsDateTime = fProcessedDate;
	dataSet.FieldByName("ProcessedStatus")->AsString = fProcessedStatus.c_str();
}

/******************************************************************************/

void TFreeAgentClaim::validateForUpdate()
{
	if(fIsNewRecord)
		fFreeAgentClaimID = GetNextNum(getDatabaseName(),getTableName());

	if(fFreeAgentClaimID.isUndefined())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fFreeAgentClaimID.isUndefined()");

	if(fTeamID.isUndefined())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fTeamID.isUndefined()");
	if(fClaimDateTime == TDateTime())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fClaimDateTime == TDateTime()");
	if(fStatus.isUndefined())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fStatus.isUndefined()");

	if(fClaimPlayerID.isUndefined())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fClaimPlayerID.isUndefined()");
	if(fReleasePlayerID.isUndefined())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fReleasePlayerID.isUndefined()");

	if(fProcessedStatus.isUndefined())
		throw ASIException("TFreeAgentClaim::validateForUpdate: fProcessedStatus.isUndefined()");
}

/******************************************************************************/

CStrVar TFreeAgentClaim::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(FreeAgentClaimID = \"%s\")",fFreeAgentClaimID.c_str());
	
	return(str);
}


/******************************************************************************/
/******************************************************************************/

TFreeAgentClaimPtr TFreeAgentClaimVector::findByTeamID(const TTeamID teamID,
	const CommonAccessMode getMode) const
{
	const_iterator iter;
	
	iter = std::find_if(begin(),end(),findTeamIDCompare(teamID));
	if(iter != end())
		return(*iter);

	if(getMode == cam_MustExist)
		throw ASIException("TFreeAgentClaimVector::findByTeamID: not found (%s)",
			teamID.c_str());

	return(TFreeAgentClaimPtr());
}

/******************************************************************************/
/******************************************************************************/

void TTrade::clear()
{
	TQueryDataSetRecord::clear();

	fTradeID.clear();

	// Trades - Proposed
	fTeamID.clear();
	fProposeToTeamID.clear();
	fProposedDate = TDateTime();
	fStatus = TTradeStatus();

	fGetPlayerIDVector.erase(fGetPlayerIDVector.begin(),
		fGetPlayerIDVector.end());

	fGivePlayerIDVector.erase(fGivePlayerIDVector.begin(),
		fGivePlayerIDVector.end());
	
	fProposeRelPlayerIDVector.erase(fProposeRelPlayerIDVector.begin(),
		fProposeRelPlayerIDVector.end());
	
	// Trades - Accepted
	fAcceptedDate = TDateTime();
	fAcceptRelPlayerIDVector.erase(fAcceptRelPlayerIDVector.begin(),
		fAcceptRelPlayerIDVector.end());
	
	// Trades - Protesting
	fProtestTeamIDVector.erase(fProtestTeamIDVector.begin(),
		fProtestTeamIDVector.end());
}

/******************************************************************************/

TTradePtr TTrade::newInstance()
{
	TTradePtr tradePtr = ASFantasyObjectBuilder::getThe().newTrade();
	tradePtr->clear();
	return(tradePtr);
}

/******************************************************************************/
	
void TTrade::readFromDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	int i,numPlayers;
	TPlayerID playerID;

	fTradeID = dataSet.FieldByName("TradeID")->AsInteger;

	// Trades - Proposed
	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;
	fProposeToTeamID = dataSet.FieldByName("ProposeToTeamID")->AsInteger;
	fProposedDate = dataSet.FieldByName("ProposedDate")->AsFloat;	//BOB AsDateTime
	fStatus = dataSet.FieldByName("Status")->AsString.c_str();

	/* fGetPlayerIDVector */
	numPlayers = dataSet.FieldByName("NumGetPlayers")->AsInteger;

	fGetPlayerIDVector.erase(fGetPlayerIDVector.begin(),fGetPlayerIDVector.end());
	
	for(i = 0; i < numPlayers; i++)
	{
		fieldName.CopyVarg("GetPlayer%02d",i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fGetPlayerIDVector.push_back(playerID);
	}
	
	/* fGivePlayerIDVector */
	numPlayers = dataSet.FieldByName("NumGivePlayers")->AsInteger;

	fGivePlayerIDVector.erase(fGivePlayerIDVector.begin(),fGivePlayerIDVector.end());
	
	for(i = 0; i < numPlayers; i++)
	{
		fieldName.CopyVarg("GivePlayer%02d",i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fGivePlayerIDVector.push_back(playerID);
	}
	
	/* fProposeRelPlayerIDVector */
	numPlayers = dataSet.FieldByName("NumProposeRelPlayers")->AsInteger;

	fProposeRelPlayerIDVector.erase(fProposeRelPlayerIDVector.begin(),fProposeRelPlayerIDVector.end());
	
	for(i = 0; i < numPlayers; i++)
	{
		fieldName.CopyVarg("ProposeRelPlayer%02d",i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fProposeRelPlayerIDVector.push_back(playerID);
	}
	
	// Trades - Accepted
	fAcceptedDate = dataSet.FieldByName("AcceptedDate")->AsFloat;	//BOB AsDateTime
	
	/* fAcceptRelPlayerIDVector */
	numPlayers = dataSet.FieldByName("NumAcceptRelPlayers")->AsInteger;

	fAcceptRelPlayerIDVector.erase(fAcceptRelPlayerIDVector.begin(),fAcceptRelPlayerIDVector.end());
	
	for(i = 0; i < numPlayers; i++)
	{
		fieldName.CopyVarg("AcceptRelPlayer%02d",i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fAcceptRelPlayerIDVector.push_back(playerID);
	}

	// Trades - Protesting

	/* fProtestTeamIDVector */
	numPlayers = dataSet.FieldByName("NumProtestTeams")->AsInteger;

	fProtestTeamIDVector.erase(fProtestTeamIDVector.begin(),fProtestTeamIDVector.end());
	
	for(i = 0; i < numPlayers; i++)
	{
		fieldName.CopyVarg("ProtestTeam%02d",i + 1);
		playerID = dataSet.FieldByName(fieldName.c_str())->AsInteger;
		
		fProtestTeamIDVector.push_back(playerID);
	}
}

/******************************************************************************/

void TTrade::writeToDataSet(TDataSet& dataSet)
{
	CStr31 fieldName;
	int i,numPlayers;

	dataSet.FieldByName("TradeID")->AsInteger = fTradeID.getID();

	// Trades - Proposed
	dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();
	dataSet.FieldByName("ProposeToTeamID")->AsInteger = fProposeToTeamID.getID();
	dataSet.FieldByName("ProposedDate")->AsDateTime = fProposedDate;
	dataSet.FieldByName("Status")->AsString = fStatus.c_str();

	/* fGetPlayerIDVector */
	numPlayers = fGetPlayerIDVector.size();
	
	dataSet.FieldByName("NumGetPlayers")->AsInteger = numPlayers;

	for(i = 0; i < MaxGetPlayerPerTrade; i++)
	{
		fieldName.CopyVarg("GetPlayer%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numPlayers) ? fGetPlayerIDVector[i].getID() : 0;
	}
	
	/* fGivePlayerIDVector */
	numPlayers = fGivePlayerIDVector.size();
	
	dataSet.FieldByName("NumGivePlayers")->AsInteger = numPlayers;

	for(i = 0; i < MaxGivePlayersPerTrade; i++)
	{
		fieldName.CopyVarg("GivePlayer%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numPlayers) ? fGivePlayerIDVector[i].getID() : 0;
	}
	
	/* fProposeRelPlayerIDVector */
	numPlayers = fProposeRelPlayerIDVector.size();
	
	dataSet.FieldByName("NumProposeRelPlayers")->AsInteger = numPlayers;

	for(i = 0; i < MaxReleasePlayerPerTrade; i++)
	{
		fieldName.CopyVarg("ProposeRelPlayer%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numPlayers) ? fProposeRelPlayerIDVector[i].getID() : 0;
	}

	// Trades - Received
	dataSet.FieldByName("AcceptedDate")->AsDateTime = fAcceptedDate;

	/* fAcceptRelPlayerIDVector */
	numPlayers = fAcceptRelPlayerIDVector.size();
	
	dataSet.FieldByName("NumAcceptRelPlayers")->AsInteger = numPlayers;

	for(i = 0; i < MaxReleasePlayerPerTrade; i++)
	{
		fieldName.CopyVarg("AcceptRelPlayer%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numPlayers) ? fAcceptRelPlayerIDVector[i].getID() : 0;
	}

	// Trades - Protesting

	/* fProtestTeamIDVector */
	numPlayers = fProtestTeamIDVector.size();
	
	dataSet.FieldByName("NumProtestTeams")->AsInteger = numPlayers;

	for(i = 0; i < MaxProtestTeamPerTrade; i++)
	{
		fieldName.CopyVarg("ProtestTeam%02d",i + 1);
		
		dataSet.FieldByName(fieldName.c_str())->AsInteger =
			(i < numPlayers) ? fProtestTeamIDVector[i].getID() : 0;
	}
}

/******************************************************************************/

void TTrade::validateForUpdate()
{
	if(fIsNewRecord)
		fTradeID = GetNextNum(getDatabaseName(),getTableName());

	if(fTradeID.isUndefined())
		throw ASIException("TTrade::validateForUpdate: fTradeID.isUndefined()");

	if(fTeamID.isUndefined())
		throw ASIException("TTrade::validateForUpdate: fTeamID.isUndefined()");
	if(fProposeToTeamID.isUndefined())
		throw ASIException("TTrade::validateForUpdate: fProposeToTeamID.isUndefined()");

	if(fProposedDate == TDateTime())
		throw ASIException("TTrade::validateForUpdate: fProposedDate == TDateTime()");
	if(fStatus.isUndefined())
		throw ASIException("TTrade::validateForUpdate: fStatus.isUndefined()");
}

/******************************************************************************/

CStrVar TTrade::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(TradeID = \"%s\")",fTradeID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/
