/* ASHockeyType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyTypeH
#define ASHockeyTypeH

#include "ASFantasyType.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

/* ID classes */

/* Field classes */

enum THockeyPositionEnum
{
	pos_Undefined,
	pos_Winger,
	pos_Center,
	pos_Defenseman,
	pos_Goalie,

	// Non-Participating Player Positions
	pos_	//none
};
#define pos_LastKeyPos pos_Goalie
#define pos_Last pos_Goalie
class THockeyPosition : public EnumType<THockeyPositionEnum,pos_Undefined,pos_Last>
{
public:
	THockeyPosition(int t = pos_Undefined) :
		EnumType<THockeyPositionEnum,pos_Undefined,pos_Last>(t) {}
	THockeyPosition(const char* str);
	
	const char* c_str() const;

	bool isKey() const;
	bool isOffensive() const;
};

enum THockeyLineupEnum
{
	lut_Undefined,
	lut_Skater,
	lut_Goalie
};
#define lut_Last lut_Goalie
class THockeyLineup : public EnumType<THockeyLineupEnum,lut_Undefined,lut_Last>
{
public:
	THockeyLineup(int t = lut_Undefined) :
		EnumType<THockeyLineupEnum,lut_Undefined,lut_Last>(t) {}
};

/******************************************************************************/

enum TRosterStatusEnum
{
	rst_Undefined,
	rst_Active,
	rst_Disabled,
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

/*
Undefined
TotalPoints
GamesPlayed
Goals
Assists
PenaltyMinutes
Shots
PlusMinus
PowerPlayGoals
PowerPlayAssists
ShortHandedGoals
ShortHandedAssists
GameWinningGoals
GameTyingGoals
OvertimeGoals
HatTricks
GamesStarted
Wins
Losses
Ties
GoalsAgainst
Saves
Shutouts
*/

enum THockeyPlayerStatEnum
{
	pst_Undefined = 0,

	//Both
	pst_TotalPoints,
	pst_GamesPlayed,

	// Offense
	pst_Goals,
	pst_Assists,
	pst_PenaltyMinutes,
	pst_Shots,
	pst_PlusMinus,

	pst_PowerPlayGoals,
	pst_PowerPlayAssists,
	pst_ShortHandedGoals,
	pst_ShortHandedAssists,
	pst_GameWinningGoals,
	pst_GameTyingGoals,
	pst_OvertimeGoals,

	pst_HatTricks,

	// Defense
	pst_GamesStarted,

	pst_Wins,
	pst_Losses,
	pst_Ties,

	pst_GoalsAgainst,
	pst_Saves,
	pst_Shutouts,
};
#define pst_Last pst_Shutouts
class THockeyPlayerStatType : public EnumType<THockeyPlayerStatEnum,
	pst_Undefined,pst_Last>
{
public:
	THockeyPlayerStatType(int t = pst_Undefined) :
		EnumType<THockeyPlayerStatEnum,pst_Undefined,pst_Last>(t) {}

	bool isOffensive() const { return(fT < pst_GamesStarted); }
};

/******************************************************************************/

class THockeyTeam : public TTeam
{
protected:
	TPlayerIDVector fSkaterLineup;
	TPlayerIDVector fGoalieLineup;
	
protected:
	THockeyTeam() {}
	virtual ~THockeyTeam() {}
	
public:
	virtual void clear();
	
	virtual const TPlayerIDVector& lineupConst(TLineup lineup) const;
	virtual TPlayerIDVector& lineup(TLineup lineup);
	
protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	
public:
	friend class RefCountPtr<THockeyTeam>;
	friend class ASHockeyObjectBuilder;
};

class THockeyTeamPtr : public TDataSetRecordPtr<THockeyTeam,TTeamID>
{
public:
	THockeyTeamPtr(TTeamPtr teamPtr = TTeamPtr()) :
		TDataSetRecordPtr<THockeyTeam,TTeamID>(
			teamPtr.isNull() ? NULL :
			&dynamic_cast<THockeyTeam&>(*teamPtr)) {}

	operator TTeamPtr() { return(TTeamPtr(fT)); }
};

/******************************************************************************/

class THockeyProfPlayer : public TProfPlayer
{
protected:
	THockeyPosition fPosition;

	TRosterStatus fRosterStatus;
	
protected:
	THockeyProfPlayer() {}
	virtual ~THockeyProfPlayer() {}
	
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

	virtual const char* getInjuryStatusString() const { return(""); }

protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	
	friend class RefCountPtr<THockeyProfPlayer>;
	friend class ASHockeyObjectBuilder;
};

class THockeyProfPlayerPtr : public TDataSetRecordPtr<THockeyProfPlayer,TPlayerID>
{
public:
	THockeyProfPlayerPtr(TProfPlayerPtr profPlayerPtr = TProfPlayerPtr()) :
		TDataSetRecordPtr<THockeyProfPlayer,TPlayerID>(
			profPlayerPtr.isNull() ? NULL :
			&dynamic_cast<THockeyProfPlayer&>(*profPlayerPtr)) {}

	operator TProfPlayerPtr() { return(TProfPlayerPtr(fT)); }
};

/******************************************************************************/

/*
GamesPlayed
Goals
Assists
Points
Shots
PlusMinus
PowerPlayGoals
PowerPlayAssists
ShortHandedGoals
ShortHandedAssists
GameWinningGoals
GameTyingGoals
EmptyNetGoals
OvertimeGoals
MajorPenalties
MinorPenalties
PenaltyMinutes
HatTricks
Fights
*/

class TOffGameStatDetail
{
public:
	short fGamesPlayed;
	short fGoals;
	short fAssists;
	short fPoints;
	short fShots;
	short fPlusMinus;

	short fPowerPlayGoals;
	short fPowerPlayAssists;
	short fShortHandedGoals;
	short fShortHandedAssists;
	short fGameWinningGoals;
	short fGameTyingGoals;
	short fEmptyNetGoals;
	short fOvertimeGoals;

	//fTotalPenalties = fMajorPenalties + fMinorPenalties
	short fMajorPenalties;
	short fMinorPenalties;
	short fPenaltyMinutes;
	short fHatTricks;
	short fFights;

public:
	TOffGameStatDetail() { clear(); }

	virtual void clear();

	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TOffGameStatDetail& offGameStatDetail);
};

/******************************************************************************/

/*
GamesPlayed
GamesStarted
MinutesPlayed
Wins
Losses
Ties
GoalsAgainst
EmptyNetGoalsAgainst
ShotsAgainst
Saves
Shutouts
MajorPenalties
PenaltyMinutes
Fights
*/

class TDefGameStatDetail
{
public:
	short fGamesPlayed;
	short fGamesStarted;
	short fMinutesPlayed;

	short fWins;
	short fLosses;
	short fTies;

	short fGoalsAgainst;
	short fEmptyNetGoalsAgainst;
	short fShotsAgainst;
	short fSaves;
	short fShutouts;

	short fMajorPenalties;
	short fPenaltyMinutes;
	short fFights;

public:
	TDefGameStatDetail() { clear(); }

	virtual void clear();
	
	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TDefGameStatDetail& defGameStatDetail);
};

/******************************************************************************/

class THockeyOffGameStat : public TOffGameStat
{
protected:
	TOffGameStatDetail fOffGameStatDetail;

protected:
	THockeyOffGameStat() {}
	virtual ~THockeyOffGameStat() {}
	
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
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	
	friend class RefCountPtr<THockeyOffGameStat>;
	friend class ASHockeyObjectBuilder;
};

class THockeyOffGameStatPtr : public TDataSetRecordPtr<THockeyOffGameStat,
	TPlayerDateID>
{
public:
	THockeyOffGameStatPtr(TOffGameStatPtr offGameStatPtr = TOffGameStatPtr()) :
		TDataSetRecordPtr<THockeyOffGameStat,TPlayerDateID>(
			offGameStatPtr.isNull() ? NULL :
			&dynamic_cast<THockeyOffGameStat&>(*offGameStatPtr)) {}

	operator TOffGameStatPtr() { return(TOffGameStatPtr(fT)); }
};

/******************************************************************************/

class THockeyDefGameStat : public TDefGameStat
{
protected:
	TDefGameStatDetail fDefGameStatDetail;

protected:
	THockeyDefGameStat() {}
	virtual ~THockeyDefGameStat() {}
	
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
	
	friend class RefCountPtr<THockeyDefGameStat>;
	friend class ASHockeyObjectBuilder;
};

class THockeyDefGameStatPtr : public TDataSetRecordPtr<THockeyDefGameStat,
	TPlayerDateID>
{
public:
	THockeyDefGameStatPtr(TDefGameStatPtr defGameStatPtr = TDefGameStatPtr()) :
		TDataSetRecordPtr<THockeyDefGameStat,TPlayerDateID>(
			defGameStatPtr.isNull() ? NULL :
			&dynamic_cast<THockeyDefGameStat&>(*defGameStatPtr)) {}

	operator TDefGameStatPtr() { return(TDefGameStatPtr(fT)); }
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyType
/******************************************************************************/
/******************************************************************************/
