/* ASFantasyType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyTypeH
#define ASFantasyTypeH

#include <stdexcep.h>
#include <vector.h>
#include <math.h>

#include "CommType.h"
#include "DataSetRecord.h"
#include "ObjectBuilderDataSetRecord.h "

#include "ASMemberType.h"

using namespace std;
using namespace tag;
using namespace asmember;

namespace asfantasy
{

/******************************************************************************/

#define ASFantasyStandardDateTimeFormat()	("dddd', 'mmmm' 'd' at 'h:mm' 'AM/PM' ET'")
#define ASFantasyStandardDateFormat()		("dddd', 'mmmm' 'd'")

//BOB move all of these to TGameOptions
#define MaxGetPlayerPerTrade		(5)
#define MaxGivePlayersPerTrade		(5)
#define MaxReleasePlayerPerTrade	(5)
#define MaxProtestTeamPerTrade		(MaxTeamsPerPrivateLeague())
#define MaxStatsPerGameResult		(8)
#define MinFreeAgentPoolDays		(3)	//Minimum days FA must be in pool before being claimed.
#define MaxTradeProposeDays			(2) // Number of days in which a proposed trade must be accepted or it will expire.
#define MaxTradeProtestDays			(2) // Number of days in which an accepted trade cant be protested or it will be completed.
#define MaxTradeProtestsAllowed		(2)	// Maximum protests per team per season
//BOB move all of these to TGameOptions

/******************************************************************************/
/* Basic Types */

enum TDivisionEnum
{
	div_Undefined,
	div_East,
	div_West
};
class TDivision : public EnumType<TDivisionEnum,div_Undefined,div_West>
{
public:
	TDivision(int t = div_Undefined) :
		EnumType<TDivisionEnum,div_Undefined,div_West>(t) {}
	TDivision(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TGamePhaseEnum
{
	gmph_Enrollment,
	gmph_PreDraft,
	gmph_Draft,
	gmph_PreSeason,
	gmph_Season,
	gmph_Playoffs,
	gmph_PostSeason
};
class TGamePhase : public EnumType<TGamePhaseEnum,gmph_Enrollment,gmph_PostSeason>
{
public:
	TGamePhase(int t = gmph_Enrollment) :
		EnumType<TGamePhaseEnum,gmph_Enrollment,gmph_PostSeason>(t) {}
	TGamePhase(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TProfPlayerGameStatusEnum
{
	ppgs_Undefined,
	ppgs_Active,
	ppgs_Disabled
};
#define ppgs_Last ppgs_Disabled
class TProfPlayerGameStatus : public EnumType<TProfPlayerGameStatusEnum,
	ppgs_Undefined,ppgs_Last>
{
public:
	TProfPlayerGameStatus(int t = ppgs_Undefined) :
		EnumType<TProfPlayerGameStatusEnum,ppgs_Undefined,ppgs_Last>(t) {}
	TProfPlayerGameStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TStatPeriodEnum
{
	stp_Undefined,

//not	stp_PreSeasonGame,
	stp_SeasonGame,
//not	stp_PlayoffGame,

	stp_LastTwoWeeks,
	stp_LastFourWeeks,
	stp_LastEightWeeks,

	stp_SeasonToDate,
	stp_LastSeason,
	stp_TwoSeasonsAgo,
	stp_ThreeSeasonsAgo
//	stp_Career
};
#define stp_Last stp_ThreeSeasonsAgo
class TStatPeriod : public EnumType<TStatPeriodEnum,stp_Undefined,stp_Last>
{
public:
	TStatPeriod(int t = stp_Undefined) :
		EnumType<TStatPeriodEnum,stp_Undefined,stp_Last>(t) {}
	TStatPeriod(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TScheduleDayStatusEnum
{
	sdst_Undefined,
	sdst_Missed,
	sdst_NotStarted,
	sdst_InProgress,
	sdst_Completed
};
#define sdst_Last sdst_Completed
class TScheduleDayStatus : public EnumType<TScheduleDayStatusEnum,
	sdst_Undefined,sdst_Last>
{
public:
	TScheduleDayStatus(int t = sdst_Undefined) :
		EnumType<TScheduleDayStatusEnum,sdst_Undefined,sdst_Last>(t) {}
	TScheduleDayStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TFreeAgentClaimStatusEnum
{
	facs_Undefined,
	facs_Pending,		// Initiated but not yet Completed.
	facs_Cleared,		// FA claim was cleared or overwritten.
	facs_Invalidated,	// Player claimed is no longer FA or player releasing is no longer on team.
	facs_Completed		// FA claim was successfully completed.
};
#define facs_Last facs_Completed
class TFreeAgentClaimStatus : public EnumType<TFreeAgentClaimStatusEnum,
	facs_Undefined,facs_Last>
{
public:
	TFreeAgentClaimStatus(int t = facs_Undefined) :
		EnumType<TFreeAgentClaimStatusEnum,facs_Undefined,facs_Last>(t) {}
	TFreeAgentClaimStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TFAClaimProcessedStatusEnum
{
	fcps_Undefined,
	fcps_NotProcessed,	// FA claim has not yet been processed.
	fcps_NewFreeAgent,	// FA claim was held up becuase player claimed is a new free agent.
	fcps_InTrade,		// FA claim was held up becuase player releasing is involved in a trade.
	fcps_Locked,		// FA claim was held up becuase player releasing is in in-process game.
};
#define fcps_Last fcps_Locked
class TFAClaimProcessedStatus : public EnumType<TFAClaimProcessedStatusEnum,
	fcps_Undefined,fcps_Last>
{
public:
	TFAClaimProcessedStatus(int t = fcps_Undefined) :
		EnumType<TFAClaimProcessedStatusEnum,fcps_Undefined,fcps_Last>(t) {}
	TFAClaimProcessedStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TTradeStatusEnum
{
	trs_Undefined,
	trs_Proposed,		// Initiated but not Accepted or Declined
	trs_Cleared,		// Trade was cleared by Initiator before it was Accepted or Declined
	trs_Declined,		// Declined by receiving Team, trade is dead
	trs_Accepted,		// Accepted by receiving Team, may be protested.
	trs_Expired,		// Trade expired before it was Accepted or Declined.
	trs_Protested,		// Trade was protested by others in league, trade is dead.
	trs_Invalidated,	// Other roster move invalidated this trade before it was completed.
	trs_Completed		// Trade was successfully completed.
};
#define trs_Last trs_Completed
class TTradeStatus : public EnumType<TTradeStatusEnum,trs_Undefined,trs_Last>
{
public:
	TTradeStatus(int t = trs_Undefined) :
		EnumType<TTradeStatusEnum,trs_Undefined,trs_Last>(t) {}
	TTradeStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/
/* ID classes */

typedef TNumericID<unsigned long> TLeagueID;
typedef TNumericID<unsigned long> TPlayerID;
typedef TNumericID<unsigned short> TProfTeamID;
DefineTStringIDClass(TProfTeamAbbr,TProfTeamAbbrBase,4);
typedef TNumericID<unsigned short> TProfGameWeek;
typedef TNumericID<unsigned long> TFreeAgentClaimID;
typedef TNumericID<unsigned long> TTradeID;

class TLeaguePlayerID
{
public:
	TLeagueID fLeagueID;
	TPlayerID fPlayerID;

	TLeaguePlayerID() { clear(); }
	TLeaguePlayerID(TLeagueID leagueID,TPlayerID playerID)
		{ clear(); fLeagueID = leagueID; fPlayerID = playerID; }

	void clear() { fLeagueID.clear(); fPlayerID.clear(); }

	bool operator<(const TLeaguePlayerID& rhs) const
	{
		if(fLeagueID < rhs.fLeagueID)
			return(true);
		if(fLeagueID > rhs.fLeagueID)
			return(false);
		if(fPlayerID < rhs.fPlayerID)
			return(true);
		return(false);
	}
};

class TTeamDateID
{
public:
	TTeamID fTeamID;
	TDateTime fDateID;

	TTeamDateID() { clear(); }
	TTeamDateID(TTeamID teamID,TDateTime dateID)
		{ clear(); fTeamID = teamID; fDateID = dateID; }
	
	void clear() { fTeamID.clear(); fDateID = TDateTime(); };
};

class TPlayerStatID
{
public:
	TPlayerID fPlayerID;
	TStatPeriod fStatPeriod;
	TDateTime fStatDate;

	TPlayerStatID() { clear(); }
	TPlayerStatID(TPlayerID playerID,TStatPeriod statPeriod,
		TDateTime statDate);
	TPlayerStatID(TPlayerID playerID,TStatPeriod statPeriod) :
		fPlayerID(playerID),fStatPeriod(statPeriod),fStatDate(TDateTime()) {}
	TPlayerStatID(TPlayerID playerID,TDateTime statDate) :
		fPlayerID(playerID),fStatPeriod(stp_SeasonGame),fStatDate(statDate) {}
	
	void clear() { fPlayerID.clear(); fStatPeriod.clear(); fStatDate = TDateTime(); };
	
	bool operator==(const TPlayerStatID& rhs) const;
	bool operator!=(const TPlayerStatID& rhs) const
		{ return(!(*this == rhs)); }
	bool operator<(const TPlayerStatID& rhs) const;
};

class TPlayerDateID
{
public:
	TPlayerID fPlayerID;
	TDateTime fDateID;

	TPlayerDateID() { clear(); }
	TPlayerDateID(TPlayerID playerID,TDateTime dateID)
		{ clear(); fPlayerID = playerID; fDateID = dateID; }
	
	void clear() { fPlayerID.clear(); fDateID = TDateTime(); };
	
	bool operator<(const TPlayerDateID& rhs) const
	{
		if(fPlayerID < rhs.fPlayerID)
			return(true);
		if(fPlayerID > rhs.fPlayerID)
			return(false);
		if(fDateID < rhs.fDateID)
			return(true);
		return(false);
	}
};

class TPlayerDates
{
public:
	TPlayerID fPlayerID;
	short fPoints;
	TDateTimeVector fDateTimeVector;

	TPlayerDates() { clear(); }
	
	void clear() { fPlayerID.clear(); fPoints = 0;
		fDateTimeVector.erase(fDateTimeVector.begin(),fDateTimeVector.end()); };
};

/******************************************************************************/
/* Field classes */

DefineFixStrClass(TLeagueName,26);
DefineFixStrClass(TRegionName,16);
DefineFixStrClass(TTeamName,16);
DefineFixStrClass(TFullTeamName,32);
typedef TFirstName TManagerName;

/******************************************************************************/
/* Vectors */

typedef std::vector<TStatPeriod> TStatPeriodVector;

class TPlayerVector;	//forward referance

class TPlayerIDVector : public std::vector<TPlayerID>
{
public:
	void readFromFiler(TDataFiler& filer);
	void writeToFiler(TDataFiler& filer);

	void fillFromPlayerVector(const TPlayerVector& playerVector);
	
	void removeUndefined();
	bool doesContainDups(bool ignoreUndefineds = false) const;
	bool contains(const TPlayerID playerID) const // Does 'this' contain the specified playerID?
		{ return(find(begin(),end(),playerID) != end()); }
	bool contains(const TPlayerIDVector& playerIDVector,
		bool skipUndefineds = false) const;	// 'this' is superset of playerIDVector
	bool containsAny(const TPlayerIDVector& playerIDVector,
		bool skipUndefineds = false) const;
	void replace(TPlayerID& oldPlayerID,TPlayerID& newPlayerID);
};

class TTeamVector;	//forward referance
class TTeamByIDVector;	//forward referance

class TTeamIDVector : public std::vector<TTeamID>
{
public:
	bool contains(const TTeamID teamID) const // Does 'this' contain the specified teamID?
		{ return(find(begin(),end(),teamID) != end()); }
	int getPosition(const TTeamID teamID,const CommonAccessMode cam = cam_MustExist) const;
	void remove(const TTeamID teamID,const CommonAccessMode cam = cam_MustExist);
	void fillFromTeamVector(const TTeamVector& teamVector);
};

typedef std::vector<TLeaguePlayerID> TLeaguePlayerIDVector;

class TOffGameStatVector;	//forward referance
class TDefGameStatVector;	//forward referance

class TPlayerDateIDVector : public std::vector<TPlayerDateID>
{
public:
	void fillFromOffGameStatVector(const TOffGameStatVector& offGameStatVector);
	void fillFromDefGameStatVector(const TDefGameStatVector& defGameStatVector);
};

class TPlayerDatesVector : public std::vector<TPlayerDates>
{
public:
	short calcTotalPoints() const;

	void fillFromPlayerIDVector(const TPlayerIDVector& playerIDVector);
	void loadPlayerIDVector(TPlayerIDVector& playerIDVector) const;

	void updateFromOffGameStatVector(const TOffGameStatVector& offGameStatVector,
		const bool inPlayoffs);
	void updateFromDefGameStatVector(const TDefGameStatVector& defGameStatVector,
		const bool inPlayoffs);
};

/******************************************************************************/
/* Abstract Types */

/* TPosition - since player positions vary from game to game, each game
	has the responsibility of defining its own range of valid positions.
	loadKeyPositionVector and loadAllPositionVector must be defined in
	derived game. */

typedef int TPosition;

class TPositionVector : public std::vector<TPosition>
{
public:
	bool contains(const TPosition position) const // Does 'this' contain the specified position?
		{ return(find(begin(),end(),position) != end()); }
};

/* TLineup - since types of lineups vary from game to game, each game has
	the responsibility of defining its own range of valid lineup types. */
typedef int TLineup;

void loadKeyPositionVector(TPositionVector& posVector);
void loadAllPositionVector(TPositionVector& posVector);
void loadDefaultLineupPositionVector(const TLineup lineup,
	TPositionVector& posVector);
CStrVar convertPositionToString(TPosition position);

/******************************************************************************/

double calcWinningPercentage(int wins,int loses);

/******************************************************************************/

#define DefaultDraftRankingTeamID	(TTeamID(1))

/* Player Type Flag */
#define ptf_TeamPlayer		0x01
#define ptf_FreeAgent		0x02

/******************************************************************************/
/******************************************************************************/

class TLeague;	//forward reference
typedef TDataSetRecordPtr<TLeague,TLeagueID> TLeaguePtr;

class TLeague : public TQueryDataSetRecord
{
	TLeagueID fLeagueID;
	TLeagueName fName;
	TPassword fPassword;

	TGamePhase fGamePhase;
	bool fReserved;

	TDateTime fLastProcessedDate;	// Date ASFbEng last processed league.
	TDateTime fDraftDate;	// Date of first draft day.
	TDateTime fSeasonDate;	// Date of first season game.
	
	TTeamIDVector fOverallStandings;
	TTeamIDVector fEastDivStandings;
	TTeamIDVector fWestDivStandings;

	TTeamIDVector fFAClaimOrder;
	TTeamIDVector fRound1DraftOrder;	// used for standings tie breaker
	
	// Playoff Data
	TTeamID fEastWinnerTeamID;
	TTeamID fEastWildCardTeamID;

	TTeamID fWestWinnerTeamID;
	TTeamID fWestWildCardTeamID;
	
	TTeamID fFinalistOneTeamID;
	TTeamID fFinalistTwoTeamID;

	TTeamID fLeagueChampTeamID;

protected:
	TLeague() : fReserved(false) {}
	virtual ~TLeague() {}

private:
	TLeague(const TLeague&);						// don't allow copy constructor
	const TLeague& operator=(const TLeague&);		// or operator=

public:
	virtual void clear();
			
	void setLeagueID(TLeagueID leagueID)
	{
		// Can only change fLeagueID for new records.
		if(!fIsNewRecord)
			throw ASIException("TLeague::setLeagueID: can't change");
			
		fLeagueID = leagueID;
		setHasChanged();
	}
	TLeagueID getLeagueID(void) const { return(fLeagueID); }
	
	const char* getName() const { return(fName); }
	void setName(const char* name)
		{ fName.Copy(name); setHasChanged(); }
		
	const char* getPassword() const { return(fPassword); }
	void setPassword(const char* password)
		{ fPassword.Copy(password); setHasChanged(); }

	TGamePhase getGamePhase(void) const { return(fGamePhase); }
	void setGamePhase(TGamePhase gamePhase)
		{ fGamePhase = gamePhase; setHasChanged(); }

	bool isReserved(void) const { return(fReserved); }
	void setReserved(bool reserved)
		{ fReserved = reserved; setHasChanged(); }

	TDateTime getLastProcessedDate(void) const { return(fLastProcessedDate); }
	void setLastProcessedDate(TDateTime lastProcessedDate)
		{ fLastProcessedDate = lastProcessedDate; setHasChanged(); }
		
	TDateTime getDraftDate(void) const { return(fDraftDate); }
	void setDraftDate(TDateTime draftDate)
		{ fDraftDate = draftDate; setHasChanged(); }

	TDateTime getSeasonDate(void) const { return(fSeasonDate); }
	void setSeasonDate(TDateTime seasonDate)
		{ fSeasonDate = seasonDate; setHasChanged(); }

	int getNumTeamsInLeague() const { return(fOverallStandings.size()); }
	
	const TTeamIDVector& overallStandings() const { return(fOverallStandings); }
	TTeamIDVector& overallStandings() { setHasChanged(); return(fOverallStandings); }
		
	const TTeamIDVector& eastDivStandings() const { return(fEastDivStandings); }
	TTeamIDVector& eastDivStandings() { setHasChanged(); return(fEastDivStandings); }
	
	const TTeamIDVector& westDivStandings() const { return(fWestDivStandings); }
	TTeamIDVector& westDivStandings() { setHasChanged(); return(fWestDivStandings); }

	TTeamIDVector getDivTeamIDVector(TDivision division) const;
	
	const TTeamIDVector& faClaimOrder() const { return(fFAClaimOrder); }
	TTeamIDVector& faClaimOrder() { setHasChanged(); return(fFAClaimOrder); }

	const TTeamIDVector& round1DraftOrder();

	void setEastWinnerTeamID(TTeamID eastWinnerTeamID) { fEastWinnerTeamID = eastWinnerTeamID; setHasChanged(); }
	TTeamID getEastWinnerTeamID() const { return(fEastWinnerTeamID); }

	void setEastWildCardTeamID(TTeamID eastWildCardTeamID) { fEastWildCardTeamID = eastWildCardTeamID; setHasChanged(); }
	TTeamID getEastWildCardTeamID() const { return(fEastWildCardTeamID); }

	void setWestWinnerTeamID(TTeamID westWinnerTeamID) { fWestWinnerTeamID = westWinnerTeamID; setHasChanged(); }
	TTeamID getWestWinnerTeamID() const { return(fWestWinnerTeamID); }

	void setWestWildCardTeamID(TTeamID westWildCardTeamID) { fWestWildCardTeamID = westWildCardTeamID; setHasChanged(); }
	TTeamID getWestWildCardTeamID() const { return(fWestWildCardTeamID); }

	void setFinalistOneTeamID(TTeamID finalistOneTeamID) { fFinalistOneTeamID = finalistOneTeamID; setHasChanged(); }
	TTeamID getFinalistOneTeamID() const { return(fFinalistOneTeamID); }

	void setFinalistTwoTeamID(TTeamID finalistTwoTeamID) { fFinalistTwoTeamID = finalistTwoTeamID; setHasChanged(); }
	TTeamID getFinalistTwoTeamID() const { return(fFinalistTwoTeamID); }

	void setLeagueChampTeamID(TTeamID leagueChampTeamID) { fLeagueChampTeamID = leagueChampTeamID; setHasChanged(); }
	TTeamID getLeagueChampTeamID() const { return(fLeagueChampTeamID); }

	void calcDraftDate(bool inNightlyProcessing);
	TDateTime getEarliestDraftDate(bool inNightlyProcessing);
	
	// Helper/Template Functions
	static TLeaguePtr createGet(TLeagueID leagueID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TLeague,TLeagueID,TLeaguePtr>(leagueID,getMode)); }
	static TLeaguePtr newInstance();
	TLeagueID getKey() const { return(getLeagueID()); }
	void setKey(TLeagueID leagueID) { setLeagueID(leagueID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("League"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);
	
	friend class RefCountPtr<TLeague>;
	friend class ASFantasyObjectBuilder;
};

/******************************************************************************/

class TLeagueVector : public std::vector<TLeaguePtr>
{
public:
	void sortByID() { std::sort(begin(),end(), sortIDCompare() ); }
	void sortByName() { std::sort(begin(),end(), sortNameCompare() ); }
	
protected:
	struct sortIDCompare
	{
		bool operator() (const TLeaguePtr& x, const TLeaguePtr& y) const
			{ return(x->getLeagueID() < y->getLeagueID()); }
	};
	struct sortNameCompare
	{
		bool operator() (const TLeaguePtr& x, const TLeaguePtr& y) const
		{
			if(stricmp(x->getName(),y->getName()) < 0)
				return(true);
			return(false);
		}
	};
};

/******************************************************************************/

class TTeam;	//forward reference
typedef TDataSetRecordPtr<TTeam,TTeamID> TTeamPtr;

class TTeam : public TQueryDataSetRecord
{
protected:
	TTeamID fTeamID;
	TParticID fParticID;
	TLeagueID fLeagueID;
	TDivision fDivision;

	TRegionName fRegionName;
	TTeamName fTeamName;

	TManagerName fManagerName;

	short fWins;
	short fLoses;
	short fTies;
	short fDivWins;
	short fDivLoses;
	short fDivTies;
	short fStreak;	// Win/Lose streak. Positive is Winning streak, Negative is Losing streak.
	short fTotalPoints;		// Total points for season thus far.

	// Trades
	short fNumTradeProtests;

protected:
	TTeam() : fWins(0),fLoses(0),fTies(0),fDivWins(0),fDivLoses(0),
		fDivTies(0),fStreak(0),fNumTradeProtests(0) {}
	virtual ~TTeam() {}
	
private:
	TTeam(const TTeam&);						// don't allow copy constructor
	const TTeam& operator=(const TTeam&);		// or operator=

public:
	virtual void clear();
		
	void setTeamID(TTeamID teamID)
	{
		// Can only change fTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TTeam::setTeamID: can't change");
			
		fTeamID = teamID;
		setHasChanged();
	}
	TTeamID getTeamID(void) const { return(fTeamID); }

	void setParticID(TParticID particID)
		{ fParticID = particID; setHasChanged(); }
	TParticID getParticID(void) const { return(fParticID); }
	
	void setLeagueID(TLeagueID leagueID)
	{
		// Can only change fLeagueID if not set or is new record.
		if((fLeagueID != TLeagueID()) && !fIsNewRecord)
			throw ASIException("TTeam::setLeagueID: can't change");
			
		fLeagueID = leagueID;
		setHasChanged();
	}
	TLeagueID getLeagueID(void) const { return(fLeagueID); }

	void setDivision(TDivision division)
		{ fDivision = division; setHasChanged(); }
	TDivision getDivision(void) const { return (fDivision); }
	
	const char* getRegionName() const { return(fRegionName); }
	void setRegionName(const char* regionName)
		{ fRegionName.Copy(regionName); setHasChanged(); }

	void setTeamName(const char* teamName)
		{ fTeamName.Copy(teamName); setHasChanged(); }
	const char* getTeamName() const { return(fTeamName); }

	TFullTeamName getFullTeamName() const;
	
	void setManagerName(const char* managerName)
		{ fManagerName.Copy(managerName); setHasChanged(); }
	const char* getManagerName() const { return(fManagerName); }

	void setWins(short wins)
		{ fWins = wins; setHasChanged(); }
	short getWins() const { return(fWins); }
	
	void setLoses(short loses)
		{ fLoses = loses; setHasChanged(); }
	short getLoses() const { return(fLoses); }
	
	void setTies(short ties)
		{ fTies = ties; setHasChanged(); }
	short getTies() const { return(fTies); }

	void setDivWins(short divWins)
		{ fDivWins = divWins; setHasChanged(); }
	short getDivWins() const { return(fDivWins); }

	void setDivLoses(short divLoses)
		{ fDivLoses = divLoses; setHasChanged(); }
	short getDivLoses() const { return(fDivLoses); }

	void setDivTies(short divTies)
		{ fDivTies = divTies; setHasChanged(); }
	short getDivTies() const { return(fDivTies); }
	
	void setStreak(short streak)
		{ fStreak = streak; setHasChanged(); }
	short getStreak() const { return(fStreak); }
	
	void setTotalPoints(short totalPoints)
		{ fTotalPoints = totalPoints; setHasChanged(); }
	short getTotalPoints() const { return(fTotalPoints); }

	// Trades
	void setNumTradeProtests(short numTradeProtests)
		{ fNumTradeProtests = numTradeProtests; setHasChanged(); }
	short getNumTradeProtests() const { return(fNumTradeProtests); }
	void incNumTradeProtests() { fNumTradeProtests++; setHasChanged(); }


	// Abstract Lineup methods
	virtual const TPlayerIDVector& lineupConst(TLineup lineup) const = 0;
	virtual TPlayerIDVector& lineup(TLineup lineup) = 0;
	
	void addWin(bool divGame);
	void addLose(bool divGame);
	void addTie(bool divGame);

	double winningPercentage() const { return(calcWinningPercentage(fWins,fLoses)); }
	double divWinningPercentage() const { return(calcWinningPercentage(fDivWins,fDivLoses)); }
	
	// Helper/Template Functions
	static TTeamPtr createGet(TTeamID teamID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TTeam,TTeamID,TTeamPtr>(teamID,getMode)); }
	static TTeamPtr newInstance();
	TTeamID getKey() const { return(getTeamID()); }
	void setKey(TTeamID teamID) { setTeamID(teamID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("Team"); }
	
	void readLineupFromDataSet(TDataSet& dataSet,const TLineup lut,
		const char* fieldNamePrefix);
	virtual void readFromDataSet(TDataSet& dataSet);
	void writeLineupToDataSet(TDataSet& dataSet,const TLineup lut,
		const char* fieldNamePrefix);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TTeam>;
};

class TTeamVector : public std::vector<TTeamPtr>
{
public:
	void sortByName() { std::sort(begin(),end(), sortNameCompare() ); }

	TTeamPtr findByID(const TTeamID teamID,
		const CommonAccessMode getMode = cam_MustExist) const;

	void fillFromTeamIDVector(const TTeamIDVector& teamIDVector,
		const TTeamVector& teamVector);
	void fillFromTeamVectorByDivision(const TTeamVector& teamVector,
		TDivision division);
		
protected:
	struct sortNameCompare
	{
		bool operator() (const TTeamPtr& x, const TTeamPtr& y) const
		{
			int rc;

			rc = stricmp(x->getRegionName(),y->getRegionName());
			if(rc < 0)
				return(true);
			if(rc > 0)
				return(false);
				
			rc = stricmp(x->getTeamName(),y->getTeamName());
			if(rc < 0)
				return(true);
			return(false);
		}
	};

	struct findIDCompare
	{
	protected:
		TTeamID fTeamID;

	public:
		findIDCompare(const TTeamID teamID) { fTeamID = teamID; }
		bool operator() (const TTeamPtr& lhs) const
			{ return(lhs->getTeamID() == fTeamID); }
	};
};

class TTeamByIDVector : public TTeamVector
{
public:
	TTeamByIDVector& operator=(const TTeamVector& rhs);
	
	void sort() { std::sort(begin(),end(), sortCompare() ); }
		
	TTeamPtr getByID(TTeamID teamID) const
	{
		const_iterator iter = std::lower_bound(begin(),end(),teamID,idSearch());
		
		if(iter != end())
			return(*iter);
		
		return(NULL);
	}
	
//	TTeamPtr findByXXX(XXX xxx);

protected:
	struct sortCompare
	{
		bool operator() (const TTeamPtr& x, const TTeamPtr& y) const
			{ return x->getTeamID() < y->getTeamID(); }
	};

	struct idSearch
	{
		bool operator()(const TTeamPtr& x, const TTeamID& y) const
			{ return x->getTeamID() < y; }
	};
};

/******************************************************************************/

class TProfPlayer;	//forward reference
typedef TDataSetRecordPtr<TProfPlayer,TPlayerID> TProfPlayerPtr;

class TProfPlayer : public TQueryDataSetRecord
{
protected:
	TPlayerID fPlayerID;
	
	TFullName fName;
	TProfTeamID fProfTeamID;
	TProfPlayerGameStatus fGameStatus;

	TDateTime fNewPlayerDate;
	short fTotalPoints;
	short fLastWeeksPoints;
	
	TDateTime fLastUpdatedDate;

protected:
	TProfPlayer() {}
	virtual ~TProfPlayer() {}
	
private:
	TProfPlayer(const TProfPlayer&);						// don't allow copy constructor
	const TProfPlayer& operator=(const TProfPlayer&);		// or operator=

public:
	virtual void clear();
		
	void setPlayerID(TPlayerID playerID)
	{
		// Can only change fPlayerID for new records.
		if(!fIsNewRecord)
			throw ASIException("TProfPlayer::setPlayerID: can't change");
			
		fPlayerID = playerID;
		setHasChanged();
	}
	TPlayerID getPlayerID(void) const { return(fPlayerID); }

	const TFullName& getName() const { return(fName); }
	TFullName& getName() { setHasChanged(); return(fName); }
	void setName(const TFullName& name) { fName = name; setHasChanged(); }

	TProfTeamID getProfTeamID() const { return(fProfTeamID); }
	void setProfTeamID(TProfTeamID profTeamID)
		{ fProfTeamID = profTeamID; setHasChanged(); }

	TProfPlayerGameStatus getGameStatus() const { return(fGameStatus); }
	void setGameStatus(TProfPlayerGameStatus gameStatus)
		{ fGameStatus = gameStatus; setHasChanged(); }

	TDateTime getNewPlayerDate() const { return(fNewPlayerDate); }
	void setNewPlayerDate(TDateTime newPlayerDate)
		{ fNewPlayerDate = newPlayerDate; setHasChanged(); }

	void setTotalPoints(short totalPoints)
		{ fTotalPoints = totalPoints; setHasChanged(); }
	short getTotalPoints() const { return(fTotalPoints); }

	void setLastWeeksPoints(short lastWeeksPoints)
		{ fLastWeeksPoints = lastWeeksPoints; setHasChanged(); }
	short getLastWeeksPoints() const { return(fLastWeeksPoints); }

	void setLastUpdatedDate(TDateTime lastUpdatedDate)
		{ fLastUpdatedDate = lastUpdatedDate; setHasChanged(); }
	TDateTime getLastUpdatedDate() const { return(fLastUpdatedDate); }
		
	virtual int getPosition() const = 0;	//game specific
	virtual void setPosition(int position) = 0;		//game specific

	virtual const char* getRosterStatusString() const = 0;	//game specific
	virtual const char* getInjuryStatusString() const = 0;	//game specific

	// Helper/Template Functions
	static TProfPlayerPtr createGet(TPlayerID playerID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TProfPlayer,TPlayerID,TProfPlayerPtr>(playerID,getMode)); }
	static TProfPlayerPtr newInstance();
	TPlayerID getKey() const { return(getPlayerID()); }
	void setKey(TPlayerID playerID) { setPlayerID(playerID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("ProfPlayer"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TProfPlayer>;
};

typedef std::vector<TProfPlayerPtr> TProfPlayerVector;

/******************************************************************************/

class TProfTeam;	//forward reference
typedef TDataSetRecordPtr<TProfTeam,TProfTeamID> TProfTeamPtr;

class TProfTeam : public TQueryDataSetRecord
{
protected:
	TProfTeamID fProfTeamID;
	TProfTeamAbbr fProfTeamAbbr;
	
	TRegionName fRegionName;
	TTeamName fTeamName;

protected:
	TProfTeam() {}
	virtual ~TProfTeam() {}
	
private:
	TProfTeam(const TProfTeam&);						// don't allow copy constructor
	const TProfTeam& operator=(const TProfTeam&);		// or operator=

public:
	virtual void clear();
		
	void setProfTeamID(TProfTeamID profTeamID)
	{
		// Can only change fProfTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TProfTeam::setProfTeamID: can't change");
			
		fProfTeamID = profTeamID;
		setHasChanged();
	}
	TProfTeamID getProfTeamID(void) const { return(fProfTeamID); }

	void setProfTeamAbbr(TProfTeamAbbr profTeamAbbr)
		{ fProfTeamAbbr = profTeamAbbr; setHasChanged(); }
	TProfTeamAbbr getProfTeamAbbr() const { return(fProfTeamAbbr); }
	
	const char* getRegionName() const { return(fRegionName); }
	void setRegionName(const char* regionName)
		{ fRegionName.Copy(regionName); setHasChanged(); }

	void setTeamName(const char* teamName)
		{ fTeamName.Copy(teamName); setHasChanged(); }
	const char* getTeamName() const { return(fTeamName); }
	
	
	// Helper/Template Functions
	static TProfTeamPtr createGet(TProfTeamID profTeamID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TProfTeam,TProfTeamID,TProfTeamPtr>(profTeamID,getMode)); }
	static TProfTeamPtr newInstance();
	TProfTeamID getKey() const { return(getProfTeamID()); }
	void setKey(TProfTeamID profTeamID) { setProfTeamID(profTeamID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("ProfTeam"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TProfTeam>;
	friend class ASFantasyObjectBuilder;
};

/******************************************************************************/

/* TPlayer contains both Team Players and Free Agents.  The key
	is on TLeagueID, TPlayerID.  If TTeamID is 0, then the TPlayer is a Free
	Agent.  If TTeamID is set, then TPlayer is a Team Player. */

/* As a santity check, getTeamID() will throw an exception if it is called
	and fTeamID == 0.  This is to catch mistakes were TPlayer is thought to
	be a Team Player when really a Free Agent.  Use isFreeAgent() to 
	dertermine if TPlayer is a Free Agent. */
	
class TPlayer;	//forward reference
typedef TDataSetRecordPtr<TPlayer,TLeaguePlayerID> TPlayerPtr;

class TPlayer : public TQueryDataSetRecord
{
protected:
	TLeagueID fLeagueID;
	TPlayerID fPlayerID;

	TTeamID fTeamID;

	TDateTime fNewFADate;
	
protected:
	TPlayer() {}
	virtual ~TPlayer() {}
	
private:
	TPlayer(const TPlayer&);						// don't allow copy constructor
	const TPlayer& operator=(const TPlayer&);		// or operator=

public:
	virtual void clear();

	void setLeagueID(TLeagueID leagueID)
	{
		// Can only change fLeagueID if not set or is new record.
		if((fLeagueID != TLeagueID()) && !fIsNewRecord)
			throw ASIException("TPlayer::setLeagueID: can't change");
			
		fLeagueID = leagueID;
		setHasChanged();
	}
	TLeagueID getLeagueID(void) const { return(fLeagueID); }
		
	void setPlayerID(TPlayerID playerID)
	{
		// Can only change fPlayerID for new records.
		if(!fIsNewRecord)
			throw ASIException("TPlayer::setPlayerID: can't change");
			
		fPlayerID = playerID;
		setHasChanged();
	}
	TPlayerID getPlayerID(void) const { return(fPlayerID); }
	
	TLeaguePlayerID getLeaguePlayerID(void) const
		{ return(TLeaguePlayerID(fLeagueID,fPlayerID)); }

	void setTeamID(TTeamID teamID)
		{ fTeamID = teamID; setHasChanged(); }
	TTeamID getTeamID(void) const
		{ if(fTeamID.isUndefined()) throw ASIException("TPlayer::getTeamID: calling for FreeAgent");
			return(fTeamID); }
	
	void setNewFADate(TDateTime newFADate)
		{ fNewFADate = newFADate; setHasChanged(); }
	TDateTime getNewFADate(void) const { return(fNewFADate); }
	
	bool isFreeAgent() const { return(fTeamID.isUndefined()); }
	bool isNewFreeAgent() const;
	TDateTime getFreeAgentAvailableDate() const;
	
	// Helper/Template Functions
	static TPlayerPtr createGet(TLeaguePlayerID leaguePlayerID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TPlayer,TLeaguePlayerID,TPlayerPtr>(leaguePlayerID,getMode)); }
	static TPlayerPtr newInstance();
	TLeaguePlayerID getKey() const { return(getLeaguePlayerID()); }
	void setKey(TLeaguePlayerID leaguePlayerID)
		{ setLeagueID(leaguePlayerID.fLeagueID);
		setPlayerID(leaguePlayerID.fPlayerID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("Player"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TPlayer>;
	friend class ASFantasyObjectBuilder;
};

class TPlayerVector : public std::vector<TPlayerPtr>
{
public:
};

/******************************************************************************/

class TOffGameStat;	//forward reference
typedef TDataSetRecordPtr<TOffGameStat,TPlayerStatID> TOffGameStatPtr;

class TOffGameStat : public TQueryDataSetRecord
{
protected:
	TPlayerID fPlayerID;
	TStatPeriod fStatPeriod;
	TDateTime fStatDate;

	short fTotalPoints;

protected:
	TOffGameStat() {}
	virtual ~TOffGameStat() {}
	
private:
	TOffGameStat(const TOffGameStat&);						// don't allow copy constructor
	const TOffGameStat& operator=(const TOffGameStat&);		// or operator=

public:
	virtual void clear();
		
	void setPlayerID(TPlayerID playerID)
	{
		// Can only change fPlayerID for new records.
		if(!fIsNewRecord)
			throw ASIException("TOffGameStat::setPlayerID: can't change");
			
		fPlayerID = playerID;
		setHasChanged();
	}
	TPlayerID getPlayerID(void) const { return(fPlayerID); }
	
	void setStatPeriod(TStatPeriod statPeriod)
	{
		// Can only change fStatDate for new records.
		if(!fIsNewRecord)
			throw ASIException("TOffGameStat::setStatPeriod: can't change");
			
		fStatPeriod = statPeriod;
		setHasChanged();
	}
	TStatPeriod getStatPeriod(void) const { return(fStatPeriod); }
	
	void setStatDate(TDateTime statDate)
	{
		// Can only change fStatDate for new records.
		if(!fIsNewRecord)
			throw ASIException("TOffGameStat::setStatDate: can't change");
			
		fStatDate = statDate;
		setHasChanged();
	}
	TDateTime getStatDate(void) const { return(fStatDate); }

	virtual void calcTotalPoints() = 0;
	short getTotalPoints() const { return(fTotalPoints); }

	TPlayerStatID getPlayerStatID(void) const
		{ return(TPlayerStatID(fPlayerID,fStatPeriod,fStatDate)); }
	TPlayerDateID getPlayerDateID(void) const;
	
	virtual double getStat(int playerStatType) = 0;
	virtual CStr31 getStatStr(int playerStatType) = 0;
	virtual void sumStats(const TOffGameStatPtr offGameStatPtr) = 0;
	
	// Helper/Template Functions
	static TOffGameStatPtr createGet(TPlayerStatID playerStatID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TOffGameStat,TPlayerStatID,TOffGameStatPtr>(playerStatID,getMode)); }
	static TOffGameStatPtr newInstance();
	TPlayerStatID getKey() const { return(getPlayerStatID()); }
	void setKey(TPlayerStatID playerStatID)
		{ setPlayerID(playerStatID.fPlayerID);
			setStatPeriod(playerStatID.fStatPeriod);
			setStatDate(playerStatID.fStatDate); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("OffGameStat"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TOffGameStat>;
};

class TOffGameStatVector : public std::vector<TOffGameStatPtr>
{
public:
	void removeByID(const TPlayerStatID playerStatID,
		const CommonAccessMode getMode = cam_MustExist);

protected:
	struct findIDCompare
	{
	protected:
		TPlayerStatID fPlayerStatID;

	public:
		findIDCompare(const TPlayerStatID playerStatID)
			{ fPlayerStatID = playerStatID; }
		bool operator() (const TOffGameStatPtr& lhs) const
			{ return(lhs->getPlayerStatID() == fPlayerStatID); }
	};
};

/******************************************************************************/

class TDefGameStat;	//forward reference
typedef TDataSetRecordPtr<TDefGameStat,TPlayerStatID> TDefGameStatPtr;

class TDefGameStat : public TQueryDataSetRecord
{
protected:
	TPlayerID fPlayerID;
	TStatPeriod fStatPeriod;
	TDateTime fStatDate;

	short fTotalPoints;

protected:
	TDefGameStat() {}
	virtual ~TDefGameStat() {}
	
private:
	TDefGameStat(const TDefGameStat&);						// don't allow copy constructor
	const TDefGameStat& operator=(const TDefGameStat&);		// or operator=

public:
	virtual void clear();
		
	void setPlayerID(TPlayerID playerID)
	{
		// Can only change fPlayerID for new records.
		if(!fIsNewRecord)
			throw ASIException("TDefGameStat::setPlayerID: can't change");
			
		fPlayerID = playerID;
		setHasChanged();
	}
	TPlayerID getPlayerID(void) const { return(fPlayerID); }
	
	void setStatPeriod(TStatPeriod statPeriod)
	{
		// Can only change fStatDate for new records.
		if(!fIsNewRecord)
			throw ASIException("TDefGameStat::setStatPeriod: can't change");
			
		fStatPeriod = statPeriod;
		setHasChanged();
	}
	TStatPeriod getStatPeriod(void) const { return(fStatPeriod); }

	void setStatDate(TDateTime statDate)
	{
		// Can only change fStatDate for new records.
		if(!fIsNewRecord)
			throw ASIException("TDefGameStat::setStatDate: can't change");
			
		fStatDate = statDate;
		setHasChanged();
	}
	TDateTime getStatDate(void) const { return(fStatDate); }

	virtual void calcTotalPoints() = 0;
	short getTotalPoints() const { return(fTotalPoints); }

	TPlayerStatID getPlayerStatID(void) const
		{ return(TPlayerStatID(fPlayerID,fStatPeriod,fStatDate)); }
	TPlayerDateID getPlayerDateID(void) const;
	
	virtual double getStat(int playerStatType) = 0;
	virtual CStr31 getStatStr(int playerStatType) = 0;
	virtual void sumStats(const TDefGameStatPtr defGameStatPtr) = 0;
	
	// Helper/Template Functions
	static TDefGameStatPtr createGet(TPlayerStatID playerStatID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TDefGameStat,TPlayerStatID,TDefGameStatPtr>(playerStatID,getMode)); }
	static TDefGameStatPtr newInstance();
	TPlayerStatID getKey() const { return(getPlayerStatID()); }
	void setKey(TPlayerStatID playerStatID)
		{ setPlayerID(playerStatID.fPlayerID);
			setStatPeriod(playerStatID.fStatPeriod);
			setStatDate(playerStatID.fStatDate); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("DefGameStat"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TDefGameStat>;
};

class TDefGameStatVector : public std::vector<TDefGameStatPtr>
{
public:
	void removeByID(const TPlayerStatID playerStatID,
		const CommonAccessMode getMode = cam_MustExist);

protected:
	struct findIDCompare
	{
	protected:
		TPlayerStatID fPlayerStatID;

	public:
		findIDCompare(const TPlayerStatID playerStatID)
			{ fPlayerStatID = playerStatID; }
		bool operator() (const TDefGameStatPtr& lhs) const
			{ return(lhs->getPlayerStatID() == fPlayerStatID); }
	};
};

/******************************************************************************/
/******************************************************************************/

class TDraftRoundVector : public std::vector<TTeamIDVector>
{
};

class TDraftOrder;	//forward reference
typedef TDataSetRecordPtr<TDraftOrder,TLeagueID> TDraftOrderPtr;

class TDraftOrder : public TQueryDataSetRecord
{
protected:
	TLeagueID fLeagueID;
	TDraftRoundVector fDraftRoundVector;

protected:
	TDraftOrder() {}
	virtual ~TDraftOrder() {}
	
private:
	TDraftOrder(const TDraftOrder&);						// don't allow copy constructor
	const TDraftOrder& operator=(const TDraftOrder&);		// or operator=

public:
	virtual void clear();
		
	void setLeagueID(TLeagueID leagueID)
	{
		// Can only change fLeagueID for new records.
		if(!fIsNewRecord)
			throw ASIException("TDraftOrder::setLeagueID: can't change");
			
		fLeagueID = leagueID;
		setHasChanged();
	}
	TLeagueID getLeagueID(void) const { return(fLeagueID); }

	TDraftRoundVector& draftRoundVector(void) { setHasChanged(); return(fDraftRoundVector); }
	const TDraftRoundVector& draftRoundVector(void) const { return(fDraftRoundVector); }
	
	// Helper/Template Functions
	static TDraftOrderPtr createGet(TLeagueID leagueID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TDraftOrder,TLeagueID,TDraftOrderPtr>(leagueID,getMode)); }
	static TDraftOrderPtr newInstance();
	TLeagueID getKey() const { return(getLeagueID()); }
	void setKey(TLeagueID leagueID) { setLeagueID(leagueID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("DraftOrder"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TDraftOrder>;
	friend class ASFantasyObjectBuilder;
};


/******************************************************************************/

class TDraftRanking;	//forward reference
typedef TDataSetRecordPtr<TDraftRanking,TTeamID> TDraftRankingPtr;

class TDraftRanking : public TQueryDataSetRecord
{
protected:
	TTeamID fTeamID;
	TPlayerIDVector fPlayerIDVector;

protected:
	TDraftRanking() {}
	virtual ~TDraftRanking() {}
	
private:
	TDraftRanking(const TDraftRanking&);						// don't allow copy constructor
	const TDraftRanking& operator=(const TDraftRanking&);		// or operator=

public:
	virtual void clear();
		
	void setTeamID(TTeamID teamID)
	{
		// Can only change fTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TDraftRanking::setTeamID: can't change");
			
		fTeamID = teamID;
		setHasChanged();
	}
	TTeamID getTeamID(void) const { return(fTeamID); }

	TPlayerIDVector& playerIDVector(void) { setHasChanged(); return(fPlayerIDVector); }
	const TPlayerIDVector& playerIDVector(void) const { return(fPlayerIDVector); }
	
	// Helper/Template Functions
	static TDraftRankingPtr createGet(TTeamID teamID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TDraftRanking,TTeamID,TDraftRankingPtr>(teamID,getMode)); }
	static TDraftRankingPtr newInstance();
	TTeamID getKey() const { return(getTeamID()); }
	void setKey(TTeamID teamID) { setTeamID(teamID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("DraftRanking"); }
	virtual TUpdateMode getUpdateMode() const { return(upWhereKeyOnly); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TDraftRanking>;
	friend class ASFantasyObjectBuilder;
};

typedef std::vector<TDraftRankingPtr> TDraftRankingVector;

/******************************************************************************/

class TDraftPick
{
public:
	TTeamID fTeamID;
	TPlayerID fPlayerID;

	TDraftPick() { clear(); }
	TDraftPick(TTeamID teamID,TPlayerID playerID)
		{ clear(); fTeamID = teamID; fPlayerID = playerID; }
	
	void clear() { fTeamID.clear(); fPlayerID.clear(); };
};

class TDraftPickVector : public std::vector<TDraftPick>
{
};

class TDraftPickRoundVector : public std::vector<TDraftPickVector>
{
};

class TDraftResult;	//forward reference
typedef TDataSetRecordPtr<TDraftResult,TLeagueID> TDraftResultPtr;

class TDraftResult : public TQueryDataSetRecord
{
protected:
	TLeagueID fLeagueID;
	TDraftPickRoundVector fDraftPickRoundVector;

protected:
	TDraftResult() {}
	virtual ~TDraftResult(void) {}
	
private:
	TDraftResult(const TDraftResult&);						// don't allow copy constructor
	const TDraftResult& operator=(const TDraftResult&);		// or operator=

public:
	virtual void clear();
		
	void setLeagueID(TLeagueID leagueID)
	{
		// Can only change fLeagueID for new records.
		if(!fIsNewRecord)
			throw ASIException("TDraftResult::setLeagueID: can't change");
			
		fLeagueID = leagueID;
		setHasChanged();
	}
	TLeagueID getLeagueID(void) const { return(fLeagueID); }

	TDraftPickRoundVector& draftPickRoundVector(void) { setHasChanged(); return(fDraftPickRoundVector); }
	const TDraftPickRoundVector& draftPickRoundVector(void) const { return(fDraftPickRoundVector); }
	
	// Helper/Template Functions
	static TDraftResultPtr createGet(TLeagueID leagueID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TDraftResult,TLeagueID,TDraftResultPtr>(leagueID,getMode)); }
	static TDraftResultPtr newInstance();
	TLeagueID getKey() const { return(getLeagueID()); }
	void setKey(TLeagueID leagueID) { setLeagueID(leagueID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("DraftResult"); }
	virtual TUpdateMode getUpdateMode() const { return(upWhereKeyOnly); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TDraftResult>;
	friend class ASFantasyObjectBuilder;
};

/******************************************************************************/
/******************************************************************************/

class TScheduleDayGame
{
protected:
	TTeamID fVisitTeamID;
	TTeamID fHomeTeamID;

	bool fWasGamePlayed;

	short fVisitScore;
	short fHomeScore;

public:
	TScheduleDayGame() { clear(); }
	
	void clear() { fVisitTeamID = TTeamID(); fHomeTeamID = TTeamID();
		fWasGamePlayed = false; fVisitScore = 0; fHomeScore = 0; }
	
	void setVisitTeamID(TTeamID visitTeamID) { fVisitTeamID = visitTeamID; }
	TTeamID getVisitTeamID() const { return(fVisitTeamID); }
	
	void setHomeTeamID(TTeamID homeTeamID) { fHomeTeamID = homeTeamID; }
	TTeamID getHomeTeamID() const { return(fHomeTeamID); }

	void setWasGamePlayed(bool wasGamePlayed) { fWasGamePlayed = wasGamePlayed; }
	bool wasGamePlayed() const { return(fWasGamePlayed); }

	void setVisitScore(short visitScore) { fVisitScore = visitScore; }
	short getVisitScore() const { return(fVisitScore); }
	
	void setHomeScore(short homeScore) { fHomeScore = homeScore; }
	short getHomeScore() const { return(fHomeScore); }

	bool wasGameTied() const;
	bool wasHomeTeamWinner() const;
		
	TTeamID getWinningTeamID() const;
	TTeamID getLosingTeamID() const;
	short getWinningScore() const;
	short getLosingScore() const;

	bool wasMatchUpBetween(TTeamID teamID,TTeamID oppTeamID) const;
	TTeamID getOppTeamID(TTeamID teamID) const;
};

typedef std::vector<TScheduleDayGame> TScheduleDayGameVector;

/******************************************************************************/

class TScheduleDayID
{
public:
	TLeagueID fLeagueID;
	TDateTime fGameDate;

	TScheduleDayID() { clear(); }
	TScheduleDayID(TLeagueID leagueID,TDateTime gameDate)
		{ clear(); fLeagueID = leagueID; fGameDate = gameDate; }

	void clear() { fLeagueID.clear(); fGameDate = TDateTime(); }

	bool operator<(const TScheduleDayID& rhs) const
	{
		if(fLeagueID < rhs.fLeagueID)
			return(true);
		if(fLeagueID > rhs.fLeagueID)
			return(false);
		if(fGameDate < rhs.fGameDate)
			return(true);
		return(false);
	}
};

class TScheduleDay;	//forward reference
typedef TDataSetRecordPtr<TScheduleDay,TScheduleDayID> TScheduleDayPtr;

class TScheduleDay : public TQueryDataSetRecord
{
protected:
	TLeagueID fLeagueID;
	TDateTime fGameDate;

	TScheduleDayStatus fStatus;

	TDateTime fEarlyProfGameDate;
	TDateTime fEarlyProfGameTime;
	TDateTime fLateProfGameDate;
	TProfGameWeek fProfGameWeek;	// Week of professional season

	TScheduleDayGameVector fScheduleDayGameVector;
	
protected:
	TScheduleDay() {}
	virtual ~TScheduleDay() {}
	
private:
	TScheduleDay(const TScheduleDay&);						// don't allow copy constructor
	const TScheduleDay& operator=(const TScheduleDay&);		// or operator=

public:
	virtual void clear();
		
	void setLeagueID(TLeagueID leagueID)
	{
		// Can only change fLeagueID if not set or is new record.
		if((fLeagueID != TLeagueID()) && !fIsNewRecord)
			throw ASIException("TScheduleDay::setLeagueID: can't change");
			
		fLeagueID = leagueID;
		setHasChanged();
	}
	TLeagueID getLeagueID(void) const { return(fLeagueID); }

	void setGameDate(TDateTime gameDate)
	{
		// Can only change fGameDate if not set or is new record.
		if((fGameDate != TDateTime()) && !fIsNewRecord)
			throw ASIException("TScheduleDay::setGameDate: can't change");
			
		fGameDate = gameDate;
		setHasChanged();
	}
	TDateTime getGameDate(void) const { return(fGameDate); }
	
	TScheduleDayID getScheduleDayID(void) const
		{ return(TScheduleDayID(fLeagueID,fGameDate)); }
	
	TScheduleDayStatus getStatus() const { return(fStatus); }
	void setStatus(TScheduleDayStatus status) { fStatus = status; setHasChanged(); }

	TDateTime getEarlyProfGameDate() const { return(fEarlyProfGameDate); }
	void setEarlyProfGameDate(TDateTime earlyProfGameDate)
		{ fEarlyProfGameDate = earlyProfGameDate; setHasChanged(); }
	
	TDateTime getEarlyProfGameTime() const { return(fEarlyProfGameTime); }
	void setEarlyProfGameTime(TDateTime earlyProfGameTime)
		{ fEarlyProfGameTime = earlyProfGameTime; setHasChanged(); }

	TDateTime getLateProfGameDate() const { return(fLateProfGameDate); }
	void setLateProfGameDate(TDateTime lateProfGameDate)
		{ fLateProfGameDate = lateProfGameDate; setHasChanged(); }
	
	TProfGameWeek getProfGameWeek() const { return(fProfGameWeek); }
	void setProfGameWeek(TProfGameWeek profGameWeek)
		{ fProfGameWeek = profGameWeek; setHasChanged(); }

	const TScheduleDayGameVector& scheduleDayGameVector() const
		{ return(fScheduleDayGameVector); }
	TScheduleDayGameVector& scheduleDayGameVector()
		{ setHasChanged(); return(fScheduleDayGameVector); }
	
	
	bool getScheduleDayGameByTeamID(TTeamID teamID,
		TScheduleDayGame& scheduleDayGame) const;
	int getScheduleDayGamePositionByTeamID(TTeamID teamID) const;
	
	// Helper/Template Functions
	static TScheduleDayPtr createGet(TScheduleDayID scheduleDayID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TScheduleDay,TScheduleDayID,TScheduleDayPtr>(scheduleDayID,getMode)); }
	static TScheduleDayPtr newInstance();
	TScheduleDayID getKey() const { return(getScheduleDayID()); }
	void setKey(TScheduleDayID scheduleDayID)
		{ setLeagueID(scheduleDayID.fLeagueID);
			setGameDate(scheduleDayID.fGameDate); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("ScheduleDay"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TScheduleDay>;
	friend class ASFantasyObjectBuilder;
};

class TScheduleDayVector : public std::vector<TScheduleDayPtr>
{
public:
	void sortByGameDate() { std::sort(begin(),end(), gameDateLessCompare() ); }

	double getHeadToHeadWinningPercentage(TTeamID teamID,TTeamID oppTeamID) const;
	short getHeadToHeadTotalPoints(TTeamID teamID,TTeamID oppTeamID) const;
	short getDivTotalPointsForTeam(TTeamID teamID,
		const TTeamIDVector& divTeamIDVector) const;

	TScheduleDayPtr getLastWeeksScheduleDay() const;
	TScheduleDayPtr getThisWeeksScheduleDay() const;

	TScheduleDayPtr getLastCompletedScheduleDay() const;
	TScheduleDayPtr getInProgressScheduleDay() const;
	TScheduleDayPtr getFirstNotStartedScheduleDay() const;

	int getGameDatePosition(TDateTime gameDate,
		const CommonAccessMode getMode = cam_MustExist) const;

protected:
	struct gameDateLessCompare
	{
		bool operator() (const TScheduleDayPtr& lhs,const TScheduleDayPtr& rhs) const
			{ return(lhs->getGameDate() < rhs->getGameDate()); }
	};

	struct gameDateLessSearch
	{
		bool operator() (const TScheduleDayPtr& lhs,const TDateTime& rhs) const
			{ return(lhs->getGameDate() < rhs); }
	};
};

/******************************************************************************/

class TGameResult;	//forward reference
typedef TDataSetRecordPtr<TGameResult,TTeamDateID> TGameResultPtr;

class TGameResult : public TQueryDataSetRecord
{
protected:
	TTeamID fTeamID;
	TDateTime fGameDate;
	TTeamID fOppTeamID;

	short fTotalPoints;		// Total points for game.

	TPlayerDatesVector fOffPlayerDatesVector;
	TPlayerDatesVector fDefPlayerDatesVector;
	
protected:
	TGameResult() {}
	virtual ~TGameResult() {}
	
private:
	TGameResult(const TGameResult&);						// don't allow copy constructor
	const TGameResult& operator=(const TGameResult&);		// or operator=

public:
	virtual void clear();
		
	void setTeamID(TTeamID teamID)
	{
		// Can only change fTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TGameResult::setTeamID: can't change");
			
		fTeamID = teamID;
		setHasChanged();
	}
	TTeamID getTeamID(void) const { return(fTeamID); }

	void setGameDate(TDateTime gameDate)
	{
		// Can only change fGameDate for new records.
		if(!fIsNewRecord)
			throw ASIException("TOffGameStat::setGameDate: can't change");
			
		fGameDate = gameDate;
		setHasChanged();
	}
	TDateTime getGameDate(void) const { return(fGameDate); }
	
	void setOppTeamID(TTeamID oppTeamID)
		{ fOppTeamID = oppTeamID; setHasChanged(); }
	TTeamID getOppTeamID(void) const { return(fOppTeamID); }
	
	void calcTotalPoints();
	short getTotalPoints() const { return(fTotalPoints); }

	const TPlayerDatesVector& offPlayerDatesConstVector() const
		{ return(fOffPlayerDatesVector); }
	TPlayerDatesVector& offPlayerDatesVector()
		{ setHasChanged(); return(fOffPlayerDatesVector); }
	
	const TPlayerDatesVector& defPlayerDatesConstVector() const
		{ return(fDefPlayerDatesVector); }
	TPlayerDatesVector& defPlayerDatesVector()
		{ setHasChanged(); return(fDefPlayerDatesVector); }
	
	TTeamDateID getTeamDateID(void) const
		{ return(TTeamDateID(fTeamID,fGameDate)); }
	
	// Helper/Template Functions
	static TGameResultPtr createGet(TTeamDateID teamDateID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TGameResult,TTeamDateID,TGameResultPtr>(teamDateID,getMode)); }
	static TGameResultPtr newInstance();
	TTeamDateID getKey() const { return(getTeamDateID()); }
	void setKey(TTeamDateID teamDateID)
		{ setTeamID(teamDateID.fTeamID); setGameDate(teamDateID.fDateID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("GameResult"); }
	
	void readPlayerDatesVectorFromDataSet(TDataSet& dataSet,
		const char* fieldPrefix,TPlayerDatesVector& playerDatesVector);
	virtual void readFromDataSet(TDataSet& dataSet);
	void writePlayerDatesVectorToDataSet(TDataSet& dataSet,
		const char* fieldPrefix,const TPlayerDatesVector& playerDatesVector);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TGameResult>;
	friend class ASFantasyObjectBuilder;
};

/******************************************************************************/

class TGameResultVector : public std::vector<TGameResultPtr>
{
public:
	TGameResultPtr findByTeamID(const TTeamID teamID,
		const CommonAccessMode getMode = cam_MustExist) const;
		
protected:
	struct findTeamIDCompare
	{
	protected:
		TTeamID fTeamID;

	public:
		findTeamIDCompare(const TTeamID teamID) { fTeamID = teamID; }
		bool operator() (const TGameResultPtr& lhs) const
			{ return(lhs->getTeamID() == fTeamID); }
	};
};

/******************************************************************************/

class TFreeAgentClaim;	//forward reference
typedef TDataSetRecordPtr<TFreeAgentClaim,TFreeAgentClaimID> TFreeAgentClaimPtr;

class TFreeAgentClaim : public TQueryDataSetRecord
{
protected:
	TFreeAgentClaimID fFreeAgentClaimID;
	
	TTeamID fTeamID;
	TDateTime fClaimDateTime;
	TFreeAgentClaimStatus fStatus;

	TPlayerID fClaimPlayerID;
	TPlayerID fReleasePlayerID;

	TDateTime fProcessedDate;
	TFAClaimProcessedStatus fProcessedStatus;

protected:
	TFreeAgentClaim() {}
	virtual ~TFreeAgentClaim() {}
	
private:
	TFreeAgentClaim(const TFreeAgentClaim&);						// don't allow copy constructor
	const TFreeAgentClaim& operator=(const TFreeAgentClaim&);		// or operator=

public:
	virtual void clear();
		
	void setFreeAgentClaimID(TFreeAgentClaimID freeAgentClaimID)
	{
		// Can only change fFreeAgentClaimID for new records.
		if(!fIsNewRecord)
			throw ASIException("TFreeAgentClaim::setFreeAgentClaimID: can't change");
			
		fFreeAgentClaimID = freeAgentClaimID;
		setHasChanged();
	}
	TFreeAgentClaimID getFreeAgentClaimID(void) const { return(fFreeAgentClaimID); }

	void setTeamID(TTeamID teamID)
	{
		// Can only change fTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TFreeAgentClaim::setTeamID: can't change");
			
		fTeamID = teamID;
		setHasChanged();
	}
	TTeamID getTeamID(void) const { return(fTeamID); }

	void setClaimDateTime(TDateTime claimDateTime)
		{ fClaimDateTime = claimDateTime; setHasChanged(); }
	TDateTime getClaimDateTime() const { return(fClaimDateTime); }

	void setStatus(TFreeAgentClaimStatus trStatus)
		{ fStatus = trStatus; setHasChanged(); }
	TFreeAgentClaimStatus getStatus() const { return(fStatus); }
	
	void setClaimPlayerID(TPlayerID claimPlayerID)
		{ fClaimPlayerID = claimPlayerID; setHasChanged(); }
	TPlayerID getClaimPlayerID() const { return(fClaimPlayerID); }

	void setReleasePlayerID(TPlayerID releasePlayerID)
		{ fReleasePlayerID = releasePlayerID; setHasChanged(); }
	TPlayerID getReleasePlayerID() const { return(fReleasePlayerID); }

	void setProcessedDate(TDateTime processedDate)
		{ fProcessedDate = processedDate; setHasChanged(); }
	TDateTime getProcessedDate() const { return(fProcessedDate); }
	
	void setProcessedStatus(TFAClaimProcessedStatus facStatus)
		{ fProcessedStatus = facStatus; setHasChanged(); }
	TFAClaimProcessedStatus getProcessedStatus() const
		{ return(fProcessedStatus); }

	// Helper/Template Functions
	static TFreeAgentClaimPtr createGet(TFreeAgentClaimID freeAgentClaimID,
			CommonAccessMode getMode)
		{ return(CreateGetRecord<TFreeAgentClaim,TFreeAgentClaimID,
		TFreeAgentClaimPtr>(freeAgentClaimID,getMode)); }
	static TFreeAgentClaimPtr newInstance();
	TFreeAgentClaimID getKey() const { return(getFreeAgentClaimID()); }
	void setKey(TFreeAgentClaimID freeAgentClaimID)
		{ setFreeAgentClaimID(freeAgentClaimID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("FreeAgentClaim"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TFreeAgentClaim>;
	friend class ASFantasyObjectBuilder;
};

class TFreeAgentClaimVector : public std::vector<TFreeAgentClaimPtr>
{
public:
	TFreeAgentClaimPtr findByTeamID(const TTeamID teamID,
		const CommonAccessMode getMode = cam_MustExist) const;

protected:
	struct findTeamIDCompare
	{
	protected:
		TTeamID fTeamID;

	public:
		findTeamIDCompare(const TTeamID teamID) { fTeamID = teamID; }
		bool operator() (const TFreeAgentClaimPtr& lhs) const
			{ return(lhs->getTeamID() == fTeamID); }
	};
};

/******************************************************************************/

class TTrade;	//forward reference
typedef TDataSetRecordPtr<TTrade,TTradeID> TTradePtr;

class TTrade : public TQueryDataSetRecord
{
protected:
	TTradeID fTradeID;
	
	// Trades - Proposed
	TTeamID fTeamID;
	TTeamID fProposeToTeamID;
	TDateTime fProposedDate;
	TTradeStatus fStatus;

	TPlayerIDVector fGetPlayerIDVector;
	TPlayerIDVector fGivePlayerIDVector;
	TPlayerIDVector fProposeRelPlayerIDVector;		// Initiating Team - players to release

	// Trades - Accepted
	TDateTime fAcceptedDate;
	TPlayerIDVector fAcceptRelPlayerIDVector;		// Accepting Team - players to release
	
	// Trades - Protesting
	TTeamIDVector fProtestTeamIDVector;

protected:
	TTrade() {}
	virtual ~TTrade() {}
	
private:
	TTrade(const TTrade&);						// don't allow copy constructor
	const TTrade& operator=(const TTrade&);		// or operator=

public:
	virtual void clear();
		
	void setTradeID(TTradeID tradeID)
	{
		// Can only change fTradeID for new records.
		if(!fIsNewRecord)
			throw ASIException("TTrade::setTradeID: can't change");
			
		fTradeID = tradeID;
		setHasChanged();
	}
	TTradeID getTradeID(void) const { return(fTradeID); }

	// Trades - Proposed
	void setTeamID(TTeamID teamID)
	{
		// Can only change fTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TTrade::setTeamID: can't change");
			
		fTeamID = teamID;
		setHasChanged();
	}
	TTeamID getTeamID(void) const { return(fTeamID); }

	void setProposeToTeamID(TTeamID proposeToTeamID)
	{
		// Can only change fTeamID for new records.
		if(!fIsNewRecord)
			throw ASIException("TTrade::setProposeToTeamID: can't change");
			
		fProposeToTeamID = proposeToTeamID;
		setHasChanged();
	}
	TTeamID getProposeToTeamID() const { return(fProposeToTeamID); }
	
	void setProposedDate(TDateTime proposedDate)
		{ fProposedDate = proposedDate; setHasChanged(); }
	TDateTime getProposedDate() const { return(fProposedDate); }
	
	void setStatus(TTradeStatus trStatus)
		{ fStatus = trStatus; setHasChanged(); }
	TTradeStatus getStatus() const { return(fStatus); }
	
	const TPlayerIDVector& getPlayerIDVector() const
		{ return(fGetPlayerIDVector); }
	TPlayerIDVector& getPlayerIDVector()
		{ setHasChanged(); return(fGetPlayerIDVector); }
	
	const TPlayerIDVector& givePlayerIDVector() const
		{ return(fGivePlayerIDVector); }
	TPlayerIDVector& givePlayerIDVector()
		{ setHasChanged(); return(fGivePlayerIDVector); }
	
	const TPlayerIDVector& proposeRelPlayerIDVector() const
		{ return(fProposeRelPlayerIDVector); }
	TPlayerIDVector& proposeRelPlayerIDVector()
		{ setHasChanged(); return(fProposeRelPlayerIDVector); }

	// Trades - Accepted
	void setAcceptedDate(TDateTime trAcceptedDate)
		{ fAcceptedDate = trAcceptedDate; setHasChanged(); }
	TDateTime getAcceptedDate() const { return(fAcceptedDate); }

	const TPlayerIDVector& acceptRelPlayerIDVector() const
		{ return(fAcceptRelPlayerIDVector); }
	TPlayerIDVector& acceptRelPlayerIDVector()
		{ setHasChanged(); return(fAcceptRelPlayerIDVector); }

	// Trades - Protesting
	const TTeamIDVector& protestTeamIDVector() const
		{ return(fProtestTeamIDVector); }
	TTeamIDVector& protestTeamIDVector()
		{ setHasChanged(); return(fProtestTeamIDVector); }

	bool isTeamInvolvedInTrade(TTeamID teamID) const
		{ return((teamID == fTeamID) || (teamID == fProposeToTeamID)); }

	bool hasTeamProtestedTrade(TTeamID teamID) const
		{ return(protestTeamIDVector().contains(teamID)); }

	// Helper/Template Functions
	static TTradePtr createGet(TTradeID tradeID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TTrade,TTradeID,TTradePtr>(tradeID,getMode)); }
	static TTradePtr newInstance();
	TTradeID getKey() const { return(getTradeID()); }
	void setKey(TTradeID tradeID) { setTradeID(tradeID); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("Trade"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TTrade>;
	friend class ASFantasyObjectBuilder;
};

typedef std::vector<TTradePtr> TTradeVector;

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyTypeH
/******************************************************************************/
/******************************************************************************/

