/* ASFootballType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballTypeH
#define ASFootballTypeH

#include "ASFantasyType.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

#define MaxPassingTDBucs	(6)
#define MaxRushingTDBucs	(6)
#define MaxReceivingTDBucs	(6)
#define MaxKickReturnTDBucs	(6)
#define MaxMiscTDBucs		(6)
#define MaxFieldGoalBucs	(6)

#define MaxNFLGamesPerDay	(15)

/******************************************************************************/

/* ID classes */

/* Field classes */
DefineFixStrClass(TCollegeName,26);

enum TFootballPositionEnum
{
	pos_Undefined,
	pos_Quarterback,
	pos_WideReceiver,
	pos_RunningBack,
	pos_TightEnd,
	pos_Kicker,
	pos_Defense,	// Defensive Team

	// Non-Participating Player Positions
	pos_Center,		// C
	pos_NoseTackle,	// NT
	pos_Punter,		// P
	pos_Cornerback,	// CB
	pos_Linebacker,	// LB
	pos_DefEnd,		// DE
	pos_DefTackle,	// DT
	pos_DefBack,	// DB
	pos_Saftey,		// S
	pos_Tackle,		// T
	pos_Guard		// G
};
#define pos_LastKeyPos pos_Defense
#define pos_Last pos_Guard
class TFootballPosition : public EnumType<TFootballPositionEnum,pos_Undefined,pos_Last>
{
public:
	TFootballPosition(int t = pos_Undefined) :
		EnumType<TFootballPositionEnum,pos_Undefined,pos_Last>(t) {}
	TFootballPosition(const char* str);
	
	const char* c_str() const;

	bool isKey() const;
	bool isOffensive() const;
};

enum TFootballLineupEnum
{
	lut_Undefined,
	lut_Starting
};
#define lut_Last lut_Starting
class TFootballLineup : public EnumType<TFootballLineupEnum,lut_Undefined,lut_Last>
{
public:
	TFootballLineup(int t = lut_Undefined) :
		EnumType<TFootballLineupEnum,lut_Undefined,lut_Last>(t) {}
};

/******************************************************************************/

enum TRosterStatusEnum
{
	rst_Undefined,
	rst_Active,
	rst_Inactive
};
#define rst_Last rst_Inactive
class TRosterStatus : public EnumType<TRosterStatusEnum,rst_Undefined,rst_Last>
{
public:
	TRosterStatus(int t = rst_Undefined) :
		EnumType<TRosterStatusEnum,rst_Undefined,rst_Last>(t) {}
	TRosterStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TInjuryStatusEnum
{
	ist_Undefined,
	ist_NoInjury,
	ist_Probable,
	ist_Questionable,
	ist_Doubtful,
	ist_Out
};
#define ist_Last ist_Out
class TInjuryStatus : public EnumType<TInjuryStatusEnum,ist_Undefined,ist_Last>
{
public:
	TInjuryStatus(int t = ist_Undefined) :
		EnumType<TInjuryStatusEnum,ist_Undefined,ist_Last>(t) {}
	TInjuryStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

/*
Undefined
TotalPoints
PassingYards
PassingTDs
Interceptions
TwoPointPasses
RushingYards
RushingTDs
Fumbles
TwoPointRushes
ReceivingYards
ReceivingTDs
TwoPointReceptions
KickReturnTDs
MiscTDs
PATsMade
PATsMissed
FieldGoalsMade
FieldGoalsMissed
YardsAllowed
Safeties
Sacks
BlockedKicks
FumblesRecovered
DefInterceptions
DefensiveTDs
*/

enum FootballPlayerStatEnum
{
	pst_Undefined = 0,

	//Both
	pst_TotalPoints,

	// Offense
	pst_PassingYards,
	pst_PassingTDs,
	pst_Interceptions,
	pst_TwoPointPasses,
	pst_RushingYards,
	pst_RushingTDs,
	pst_Fumbles,
	pst_TwoPointRushes,
	pst_ReceivingYards,
	pst_ReceivingTDs,
	pst_TwoPointReceptions,
	pst_KickReturnTDs,
	pst_MiscTDs,
	pst_PATsMade,
	pst_PATsMissed,
	pst_FieldGoalsMade,
	pst_FieldGoalsMissed,

	// Defense
	pst_YardsAllowed,
	pst_Safeties,
	pst_Sacks,
	pst_BlockedKicks,
	pst_FumblesRecovered,
	pst_DefInterceptions,
	pst_DefensiveTDs
};
#define pst_Last pst_DefensiveTDs
class FootballPlayerStatType : public EnumType<FootballPlayerStatEnum,
	pst_Undefined,pst_Last>
{
public:
	FootballPlayerStatType(int t = pst_Undefined) :
		EnumType<FootballPlayerStatEnum,pst_Undefined,pst_Last>(t) {}

	bool isOffensive() const { return(fT < pst_YardsAllowed); }
};

/******************************************************************************/

TPlayerID ConvertProfTeamIDtoPlayerID(TProfTeamID profTeamID);
TProfTeamID ConvertPlayerIDtoProfTeamID(TPlayerID playerID);

/******************************************************************************/

class TFootballTeam : public TTeam
{
protected:
	TPlayerIDVector fLineup;		// Starting Lineup
	
protected:
	TFootballTeam() {}
	virtual ~TFootballTeam() {}
	
public:
	virtual void clear();
	
	virtual const TPlayerIDVector& lineupConst(TLineup lineup) const;
	virtual TPlayerIDVector& lineup(TLineup lineup);
	
protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	
public:
	friend class RefCountPtr<TFootballTeam>;
	friend class ASFootballObjectBuilder;
};

class TFootballTeamPtr : public TDataSetRecordPtr<TFootballTeam,TTeamID>
{
public:
	TFootballTeamPtr(TTeamPtr teamPtr = TTeamPtr()) :
		TDataSetRecordPtr<TFootballTeam,TTeamID>(
			teamPtr.isNull() ? NULL :
			&dynamic_cast<TFootballTeam&>(*teamPtr)) {}

	operator TTeamPtr() { return(TTeamPtr(fT)); }
};

/******************************************************************************/

class TFootballProfPlayer : public TProfPlayer
{
protected:
	TFootballPosition fPosition;

	TRosterStatus fRosterStatus;
	TInjuryStatus fInjuryStatus;
	TCollegeName fCollegeName;
	short fYearsPro;
	
protected:
	TFootballProfPlayer() { fYearsPro = 0; }
	virtual ~TFootballProfPlayer() {}
	
public:
	virtual void clear();
	
	virtual int getPosition() const { return(fPosition); }
	virtual void setPosition(int position)
		{ fPosition = position; setHasChanged(); }

	void setRosterStatus(TRosterStatus rosterStatus)
		{ fRosterStatus = rosterStatus; setHasChanged(); }
	TRosterStatus getRosterStatus(void) const { return (fRosterStatus); }
	virtual const char* getRosterStatusString() const
		{ return(fRosterStatus.c_str()); }

	void setInjuryStatus(TInjuryStatus injuryStatus)
		{ fInjuryStatus = injuryStatus; setHasChanged(); }
	TInjuryStatus getInjuryStatus(void) const { return (fInjuryStatus); }
	virtual const char* getInjuryStatusString() const
		{ return(fInjuryStatus.c_str()); }

	const char* getCollegeName() const { return(fCollegeName); }
	void setCollegeName(const char* collegeName)
		{ fCollegeName.Copy(collegeName); setHasChanged(); }
	
	virtual short getYearsPro() const { return(fYearsPro); }
	virtual void setYearsPro(short yearsPro)
		{ fYearsPro = yearsPro; setHasChanged(); }
	
protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	
	friend class RefCountPtr<TFootballProfPlayer>;
	friend class ASFootballObjectBuilder;
};

class TFootballProfPlayerPtr : public TDataSetRecordPtr<TFootballProfPlayer,TPlayerID>
{
public:
	TFootballProfPlayerPtr(TProfPlayerPtr profPlayerPtr = TProfPlayerPtr()) :
		TDataSetRecordPtr<TFootballProfPlayer,TPlayerID>(
			profPlayerPtr.isNull() ? NULL :
			&dynamic_cast<TFootballProfPlayer&>(*profPlayerPtr)) {}

	operator TProfPlayerPtr() { return(TProfPlayerPtr(fT)); }
};

/******************************************************************************/

/* Yardage Buckets Distance */
enum YardageBucketsDistanceEnum
{
	ybd_00_to_09 = 0,
	ybd_10_to_19 = 1,
	ybd_20_to_29 = 2,
	ybd_30_to_39 = 3,
	ybd_40_to_49 = 4,
	ybd_50_plus = 5,
};

class YardageBucketsDistance : public EnumType<YardageBucketsDistanceEnum,
	ybd_00_to_09,ybd_50_plus>
{
public:
	YardageBucketsDistance(int t = ybd_00_to_09) :
		EnumType<YardageBucketsDistanceEnum,ybd_00_to_09,ybd_50_plus>(t) {}
};

class YardageBuckets
{
protected:
	typedef byte ItemType;
	
	vector<ItemType> fBuckets;
public:
	void clear() { fBuckets.erase(fBuckets.begin(),fBuckets.end()); }

	void setBucket(YardageBucketsDistance ybd,short count);
	byte getBucket(YardageBucketsDistance ybd) const;
	int numBuckets() const { return(fBuckets.size()); }
	short totalBuckets() const;

	void incBucket(YardageBucketsDistance ybd)
		{ setBucket(ybd,cast2short(getBucket(ybd) + 1)); }
	void addYards(byte yards);
	
	void sumBuckets(const YardageBuckets& yardageBuckets);
};

/******************************************************************************/

class TOffGameStatDetail
{
public:
	/* Passing Stats */
	short fPassingYards;
	byte fInterceptions;
	byte fTwoPointPasses;
	YardageBuckets fPassingTDYardageBuckets;
	
	/* Rushing Stats */
	short fRushingYards;
	byte fFumbles;
	byte fTwoPointRushes;
	YardageBuckets fRushingTDYardageBuckets;
	
	/* Receiving Stats */
	short fReceivingYards;
	byte fTwoPointReceptions;
	YardageBuckets fReceivingTDYardageBuckets;

	/* Misc Offense */
	YardageBuckets fKickReturnTDYardageBuckets;
	YardageBuckets fMiscTDYardageBuckets;
	
	/* Kicking Stats */
	byte fPATsAttempted;
	byte fPATsMade;
	byte fFieldGoalsAttempted;
	YardageBuckets fFieldGoalYardageBuckets;

public:
	TOffGameStatDetail() { clear(); }

	virtual void clear();

	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TOffGameStatDetail& offGameStatDetail);
	
protected:
	static short calcTouchdowns(const YardageBuckets& yardageBuckets,
		short touchdownValue);
	static short calcFieldGoals(byte fieldGoalsAttempted,
		const YardageBuckets& yardageBuckets);
};

/******************************************************************************/

class TDefGameStatDetail
{
public:
	short fPassingYardsAllowed;
	short fRushingYardsAllowed;
	byte fSafeties;
	byte fSacks;
	byte fBlockedKicks;
	byte fFumblesRecovered;
	byte fInterceptions;
	byte fDefensiveTDs;
		
public:
	TDefGameStatDetail() { clear(); }

	virtual void clear();
	
	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TDefGameStatDetail& defGameStatDetail);
};

/******************************************************************************/

class TFootballOffGameStat : public TOffGameStat
{
protected:
	TOffGameStatDetail fOffGameStatDetail;

protected:
	TFootballOffGameStat() {}
	virtual ~TFootballOffGameStat() {}
	
public:
	virtual void clear();
	
	TOffGameStatDetail& offGameStatDetail() { setHasChanged(); return(fOffGameStatDetail); }
	const TOffGameStatDetail& offGameStatDetail() const { return(fOffGameStatDetail); }

	virtual void calcTotalPoints()
		{ fTotalPoints = fOffGameStatDetail.calcTotalPoints(); setHasChanged(); }
	
	virtual double getStat(int playerStatType);
	static CStr31 getDefaultStatStr(int playerStatType);
	virtual CStr31 getStatStr(int playerStatType);
	virtual void sumStats(const TOffGameStatPtr offGameStatPtr);
	
protected:
	/* DataSetRecord methods */
	void readYardageFromDataSet(TDataSet& dataSet,YardageBuckets& yardageBuckets,
		const char* subFieldName);
	virtual void readFromDataSet(TDataSet& dataSet);
	void writeYardageToDataSet(TDataSet& dataSet,
		const YardageBuckets& yardageBuckets,const char* subFieldName,
		int maxItems);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	
	friend class RefCountPtr<TFootballOffGameStat>;
	friend class ASFootballObjectBuilder;
};

class TFootballOffGameStatPtr : public TDataSetRecordPtr<TFootballOffGameStat,
	TPlayerDateID>
{
public:
	TFootballOffGameStatPtr(TOffGameStatPtr offGameStatPtr = TOffGameStatPtr()) :
		TDataSetRecordPtr<TFootballOffGameStat,TPlayerDateID>(
			offGameStatPtr.isNull() ? NULL :
			&dynamic_cast<TFootballOffGameStat&>(*offGameStatPtr)) {}

	operator TOffGameStatPtr() { return(TOffGameStatPtr(fT)); }
};

/******************************************************************************/

class TFootballDefGameStat : public TDefGameStat
{
protected:
	TDefGameStatDetail fDefGameStatDetail;

protected:
	TFootballDefGameStat() {}
	virtual ~TFootballDefGameStat() {}
	
public:
	virtual void clear();
	
	TDefGameStatDetail& defGameStatDetail() { setHasChanged(); return(fDefGameStatDetail); }
	const TDefGameStatDetail& defGameStatDetail() const { return(fDefGameStatDetail); }
	
	virtual void calcTotalPoints()
		{ fTotalPoints = fDefGameStatDetail.calcTotalPoints(); setHasChanged(); }

	virtual double getStat(int playerStatType);
	static CStr31 getDefaultStatStr(int playerStatType);
	virtual CStr31 getStatStr(int playerStatType);
	virtual void sumStats(const TDefGameStatPtr defGameStatPtr);
	
protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	
	friend class RefCountPtr<TFootballDefGameStat>;
	friend class ASFootballObjectBuilder;
};

class TFootballDefGameStatPtr : public TDataSetRecordPtr<TFootballDefGameStat,
	TPlayerDateID>
{
public:
	TFootballDefGameStatPtr(TDefGameStatPtr defGameStatPtr = TDefGameStatPtr()) :
		TDataSetRecordPtr<TFootballDefGameStat,TPlayerDateID>(
			defGameStatPtr.isNull() ? NULL :
			&dynamic_cast<TFootballDefGameStat&>(*defGameStatPtr)) {}

	operator TDefGameStatPtr() { return(TDefGameStatPtr(fT)); }
};

/******************************************************************************/

class TProfTeamGame
{
protected:
	TDateTime fGameDate;
	TDateTime fGameTime;
	
	TProfTeamID fVisitTeamID;
	TProfTeamID fHomeTeamID;

	byte fVisitScore;
	byte fHomeScore;

public:
	TProfTeamGame() { clear(); }
	
	void clear() { fGameDate = TDateTime(); fGameTime = TDateTime();
		fVisitTeamID = TProfTeamID(); fHomeTeamID = TProfTeamID();
		fVisitScore = 0; fHomeScore = 0; }

	void setGameDate(TDateTime gameDate) { fGameDate = gameDate; }
	TDateTime getGameDate() const { return(fGameDate); }

	void setGameTime(TDateTime gameTime) { fGameTime = gameTime; }
	TDateTime getGameTime() const { return(fGameTime); }
	
	void setVisitTeamID(TProfTeamID visitTeamID) { fVisitTeamID = visitTeamID; }
	TProfTeamID getVisitTeamID() const { return(fVisitTeamID); }
	
	void setHomeTeamID(TProfTeamID homeTeamID) { fHomeTeamID = homeTeamID; }
	TProfTeamID getHomeTeamID() const { return(fHomeTeamID); }

	void setVisitScore(byte visitScore) { fVisitScore = visitScore; }
	byte getVisitScore() const { return(fVisitScore); }
	
	void setHomeScore(byte homeScore) { fHomeScore = homeScore; }
	byte getHomeScore() const { return(fHomeScore); }

	TProfTeamID getOppTeamID(TProfTeamID teamID) const;
};

typedef std::vector<TProfTeamGame> TProfTeamGameVector;

/******************************************************************************/

class TFootballProfTeamSchedule;	//forward reference
typedef TDataSetRecordPtr<TFootballProfTeamSchedule,TProfGameWeek> TFootballProfTeamSchedulePtr;

class TFootballProfTeamSchedule : public TQueryDataSetRecord
{
protected:
	TProfGameWeek fProfGameWeek;

	TProfTeamGameVector fProfTeamGameVector;

protected:
	TFootballProfTeamSchedule() {}
	virtual ~TFootballProfTeamSchedule() {}
	
private:
	TFootballProfTeamSchedule(const TFootballProfTeamSchedule&);						// don't allow copy constructor
	const TFootballProfTeamSchedule& operator=(const TFootballProfTeamSchedule&);		// or operator=

public:
	virtual void clear();
		
	void setProfGameWeek(TProfGameWeek profGameWeek)
	{
		// Can only change fProfGameWeek if not set or is new record.
		if((fProfGameWeek != TProfGameWeek()) && !fIsNewRecord)
			throw ASIException("TFootballProfTeamSchedule::setProfGameWeek: can't change");
			
		fProfGameWeek = profGameWeek;
		setHasChanged();
	}
	TProfGameWeek getProfGameWeek(void) const { return(fProfGameWeek); }

	const TProfTeamGameVector& profTeamGameVector() const
		{ return(fProfTeamGameVector); }
	TProfTeamGameVector& profTeamGameVector()
		{ setHasChanged(); return(fProfTeamGameVector); }
	
	TDateTime findEarliestGameDate() const;
	TDateTime findEarliestGameTime() const;
	TDateTime findLatestGameDate() const;
	bool anyGamesForDate(const TDateTime gameDate);

	bool getProfTeamGameByProfTeamID(TProfTeamID profTeamID,
		TProfTeamGame& profTeamGame) const;
	
	// Helper/Template Functions
	static TFootballProfTeamSchedulePtr createGet(TProfGameWeek profGameWeek,CommonAccessMode getMode)
		{ return(CreateGetRecord<TFootballProfTeamSchedule,TProfGameWeek,
			TFootballProfTeamSchedulePtr>(profGameWeek,getMode)); }
	static TFootballProfTeamSchedulePtr newInstance();
	TProfGameWeek getKey() const { return(getProfGameWeek()); }
	void setKey(TProfGameWeek profGameWeek) { setProfGameWeek(profGameWeek); }
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(PrimaryDatabaseName()); }
	virtual const char* getTableName() { return("ProfTeamSchedule"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	void validateGameVector();
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TFootballProfTeamSchedule>;
	friend class ASFootballObjectBuilder;
};

class TFootballProfTeamScheduleVector : public std::vector<TFootballProfTeamSchedulePtr>
{
public:
	void sortByProfGameWeek() { std::sort(begin(),end(), profGameWeekLessCompare() ); }

	TFootballProfTeamSchedulePtr findByContainsGameDate(TDateTime gameDate,
		CommonAccessMode getMode);
	TFootballProfTeamSchedulePtr findCurrentAsOfToday(CommonAccessMode getMode);

protected:
	struct profGameWeekLessCompare
	{
		bool operator() (const TFootballProfTeamSchedulePtr& lhs,
				const TFootballProfTeamSchedulePtr& rhs) const
			{ return(lhs->getProfGameWeek() < rhs->getProfGameWeek()); }
	};
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballType
/******************************************************************************/
/******************************************************************************/
