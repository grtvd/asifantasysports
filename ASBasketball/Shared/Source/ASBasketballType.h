/* ASBasketballType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballTypeH
#define ASBasketballTypeH

#include "ASFantasyType.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

/* ID classes */

/* Field classes */

enum TBasketballPositionEnum
{
	pos_Undefined,
	pos_PointGuard,
	pos_ShootingGuard,
	pos_SmallForward,
	pos_PowerForward,
	pos_Center,

	// Non-Participating Player Positions
	//none
};
#define pos_FirstKeyPos pos_PointGuard
#define pos_LastKeyPos pos_Center
#define pos_Last pos_Center
class TBasketballPosition : public EnumType<TBasketballPositionEnum,
	pos_Undefined,pos_Last>
{
public:
	TBasketballPosition(int t = pos_Undefined) :
		EnumType<TBasketballPositionEnum,pos_Undefined,pos_Last>(t) {}
	TBasketballPosition(const char* str);
	
	const char* c_str() const;

	bool isKey() const;
	bool isOffensive() const;
};

enum TBasketballLineupEnum
{
	lut_Undefined,
	lut_Starting,
};
#define lut_Last lut_Starting
class TBasketballLineup : public EnumType<TBasketballLineupEnum,lut_Undefined,
	lut_Last>
{
public:
	TBasketballLineup(int t = lut_Undefined) :
		EnumType<TBasketballLineupEnum,lut_Undefined,lut_Last>(t) {}
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
MinutesPlayed
PointsScored
FieldGoalsMade
FieldGoalsAttempted
FieldGoalPercentage
FreeThrowsMade
FreeThrowsAttempted
FreeThrowPercentage
ThreePointGoalsMade
ThreePointGoalsAttempted
OffensiveRebounds
DefensiveRebounds
Assists
Steals
Blocks
Turnovers
PersonalFouls
TechnicalFouls
*/

enum TBasketballPlayerStatEnum
{
	pst_Undefined = 0,

	//Both
	pst_TotalPoints,
	pst_GamesPlayed,

	// Offense
	pst_MinutesPlayed,
	pst_PointsScored,

	pst_FieldGoalsMade,
	pst_FieldGoalsAttempted,
	pst_FieldGoalPercentage,
	pst_FreeThrowsMade,
	pst_FreeThrowsAttempted,
	pst_FreeThrowPercentage,
	pst_ThreePointGoalsMade,
	pst_ThreePointGoalsAttempted,

	pst_OffensiveRebounds,
	pst_DefensiveRebounds,
	pst_Assists,
	pst_Steals,
	pst_Blocks,

	pst_Turnovers,
	pst_PersonalFouls,
	pst_TechnicalFouls,

	// Defense
};
#define pst_Last pst_TechnicalFouls
class TBasketballPlayerStatType : public EnumType<TBasketballPlayerStatEnum,
	pst_Undefined,pst_Last>
{
public:
	TBasketballPlayerStatType(int t = pst_Undefined) :
		EnumType<TBasketballPlayerStatEnum,pst_Undefined,pst_Last>(t) {}

	bool isOffensive() const { return(true); }
};

/******************************************************************************/

class TBasketballTeam : public TTeam
{
protected:
	TPlayerIDVector fLineup;
	
protected:
	TBasketballTeam() {}
	virtual ~TBasketballTeam() {}
	
public:
	virtual void clear();
	
	virtual const TPlayerIDVector& lineupConst(TLineup lineup) const;
	virtual TPlayerIDVector& lineup(TLineup lineup);
	
protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	
public:
	friend class RefCountPtr<TBasketballTeam>;
	friend class ASBasketballObjectBuilder;
};

class TBasketballTeamPtr : public TDataSetRecordPtr<TBasketballTeam,TTeamID>
{
public:
	TBasketballTeamPtr(TTeamPtr teamPtr = TTeamPtr()) :
		TDataSetRecordPtr<TBasketballTeam,TTeamID>(
			teamPtr.isNull() ? NULL :
			&dynamic_cast<TBasketballTeam&>(*teamPtr)) {}

	operator TTeamPtr() { return(TTeamPtr(fT)); }
};

/******************************************************************************/

class TBasketballProfPlayer : public TProfPlayer
{
protected:
	TBasketballPosition fPosition;

	TRosterStatus fRosterStatus;
	
protected:
	TBasketballProfPlayer() {}
	virtual ~TBasketballProfPlayer() {}
	
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
	
	friend class RefCountPtr<TBasketballProfPlayer>;
	friend class ASBasketballObjectBuilder;
};

class TBasketballProfPlayerPtr : public TDataSetRecordPtr<TBasketballProfPlayer,TPlayerID>
{
public:
	TBasketballProfPlayerPtr(TProfPlayerPtr profPlayerPtr = TProfPlayerPtr()) :
		TDataSetRecordPtr<TBasketballProfPlayer,TPlayerID>(
			profPlayerPtr.isNull() ? NULL :
			&dynamic_cast<TBasketballProfPlayer&>(*profPlayerPtr)) {}

	operator TProfPlayerPtr() { return(TProfPlayerPtr(fT)); }
};

/******************************************************************************/

/*
GamesPlayed
MinutesPlayed
PointsScored
TwoPointGoalsMade
TwoPointGoalsMissed
ThreePointGoalsMade
ThreePointGoalsMissed
FreeThrowsMade
FreeThrowsMissed
OffensiveRebounds
DefensiveRebounds
Assists
Steals
Blocks
Turnovers
PersonalFouls
TechnicalFouls
*/

class TOffGameStatDetail
{
public:
	short fGamesPlayed;
	short fMinutesPlayed;
	short fPointsScored;

	short fTwoPointGoalsMade;
	short fTwoPointGoalsMissed;
	short fThreePointGoalsMade;
	short fThreePointGoalsMissed;
	short fFreeThrowsMade;
	short fFreeThrowsMissed;

	short fOffensiveRebounds;
	short fDefensiveRebounds;
	short fAssists;
	short fSteals;
	short fBlocks;

	short fTurnovers;
	short fPersonalFouls;
	short fTechnicalFouls;

public:
	TOffGameStatDetail() { clear(); }

	virtual void clear();

	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TOffGameStatDetail& offGameStatDetail);
};

/******************************************************************************/
#if 0	//BOB

/*
GamesPlayed
*/

class TDefGameStatDetail
{
public:
	short fGamesPlayed;

public:
	TDefGameStatDetail() { clear(); }

	virtual void clear();
	
	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TDefGameStatDetail& defGameStatDetail);
};

#endif	//BOB
/******************************************************************************/

class TBasketballOffGameStat : public TOffGameStat
{
protected:
	TOffGameStatDetail fOffGameStatDetail;

protected:
	TBasketballOffGameStat() {}
	virtual ~TBasketballOffGameStat() {}
	
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
	
	friend class RefCountPtr<TBasketballOffGameStat>;
	friend class ASBasketballObjectBuilder;
};

class TBasketballOffGameStatPtr : public TDataSetRecordPtr<TBasketballOffGameStat,
	TPlayerDateID>
{
public:
	TBasketballOffGameStatPtr(TOffGameStatPtr offGameStatPtr = TOffGameStatPtr()) :
		TDataSetRecordPtr<TBasketballOffGameStat,TPlayerDateID>(
			offGameStatPtr.isNull() ? NULL :
			&dynamic_cast<TBasketballOffGameStat&>(*offGameStatPtr)) {}

	operator TOffGameStatPtr() { return(TOffGameStatPtr(fT)); }
};

/******************************************************************************/
#if 0	//BOB

class TBasketballDefGameStat : public TDefGameStat
{
protected:
	TDefGameStatDetail fDefGameStatDetail;

protected:
	TBasketballDefGameStat() {}
	virtual ~TBasketballDefGameStat() {}
	
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
	
	friend class RefCountPtr<TBasketballDefGameStat>;
	friend class ASBasketballObjectBuilder;
};

class TBasketballDefGameStatPtr : public TDataSetRecordPtr<TBasketballDefGameStat,
	TPlayerDateID>
{
public:
	TBasketballDefGameStatPtr(TDefGameStatPtr defGameStatPtr = TDefGameStatPtr()) :
		TDataSetRecordPtr<TBasketballDefGameStat,TPlayerDateID>(
			defGameStatPtr.isNull() ? NULL :
			&dynamic_cast<TBasketballDefGameStat&>(*defGameStatPtr)) {}

	operator TDefGameStatPtr() { return(TDefGameStatPtr(fT)); }
};

#endif	//BOB
/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballType
/******************************************************************************/
/******************************************************************************/
