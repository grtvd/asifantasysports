/* ASBaseballType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballTypeH
#define ASBaseballTypeH

#include "ASFantasyType.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

/* ID classes */

/* Field classes */
enum TBaseballPositionEnum
{
	pos_Undefined,
	pos_FirstBaseman,
	pos_SecondBaseman,
	pos_ShortStop,
	pos_ThirdBaseman,
	pos_Catcher,
	pos_Outfielder,
	pos_DesignatedHitter,
	pos_StartingPitcher,
	pos_ReliefPitcher

	// Non-Participating Player Positions
	//pos_	//none
};
#define pos_LastKeyPos pos_ReliefPitcher
#define pos_Last pos_ReliefPitcher
class TBaseballPosition : public EnumType<TBaseballPositionEnum,pos_Undefined,pos_Last>
{
public:
	TBaseballPosition(int t = pos_Undefined) :
		EnumType<TBaseballPositionEnum,pos_Undefined,pos_Last>(t) {}
	TBaseballPosition(const char* str);
	
	const char* c_str() const;

	bool isKey() const;
	bool isOffensive() const;
};

enum TBaseballLineupEnum
{
	lut_Undefined,
	lut_Batter,
	lut_Pitcher,
};
#define lut_Last lut_Pitcher
class TBaseballLineup : public EnumType<TBaseballLineupEnum,lut_Undefined,lut_Last>
{
public:
	TBaseballLineup(int t = lut_Undefined) :
		EnumType<TBaseballLineupEnum,lut_Undefined,lut_Last>(t) {}
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
TotalPoints
GamesPlayed
GamesStarted
Errors
BattingAverage
AtBats
Hits
Doubles
Triples
OneRunHomers
TwoRunHomers
ThreeRunHomers
GrandSlams
RunsScored
RunsBattedIn
Sacrifices
HitByPicth
Walks
Strikeouts
StolenBases
CaughtStealing
GroundedDoublePlay
HitForCycle
EarnedRunAverage
Wins
Losses
Saves
InningsPitched
HitsAllowed
DoublesAllowed
TriplesAllowed
OneRunHomersAllowed
TwoRunHomersAllowed
ThreeRunHomersAllowed
GrandSlamsAllowed
RunsAllowed
EarnedRunsAllowed
SacrificesAllowed
HitBatsmen
WalkedBatsmen
StruckoutBatsmen
WildPitches
Balks
CompleteGames
Shutouts
NoHitters
PerfectGames
*/

enum TBaseballPlayerStatEnum
{
	pst_Undefined = 0,

	//Both
	pst_TotalPoints,
	pst_GamesPlayed,
	pst_GamesStarted,
	pst_Errors,

	// Offense
	pst_BattingAverage,
	pst_AtBats,

	pst_Hits,
	pst_Doubles,
	pst_Triples,

	pst_OneRunHomers,
	pst_TwoRunHomers,
	pst_ThreeRunHomers,
	pst_GrandSlams,

	pst_RunsScored,
	pst_RunsBattedIn,
	pst_Sacrifices,
	pst_HitByPicth,
	pst_Walks,

	pst_Strikeouts,
	pst_StolenBases,
	pst_CaughtStealing,
	pst_GroundedDoublePlay,
	pst_HitForCycle,

	// Defense
	pst_EarnedRunAverage,

	pst_Wins,
	pst_Losses,
	pst_Saves,

	pst_InningsPitched,
	pst_HitsAllowed,
	pst_DoublesAllowed,
	pst_TriplesAllowed,

	pst_OneRunHomersAllowed,
	pst_TwoRunHomersAllowed,
	pst_ThreeRunHomersAllowed,
	pst_GrandSlamsAllowed,

	pst_RunsAllowed,
	pst_EarnedRunsAllowed,
	pst_SacrificesAllowed,
	pst_HitBatsmen,
	pst_WalkedBatsmen,
	pst_StruckoutBatsmen,
	pst_WildPitches,
	pst_Balks,

	pst_CompleteGames,
	pst_Shutouts,
	pst_NoHitters,
	pst_PerfectGames
};
#define pst_Last pst_PerfectGames
class TBaseballPlayerStatType : public EnumType<TBaseballPlayerStatEnum,
	pst_Undefined,pst_Last>
{
public:
	TBaseballPlayerStatType(int t = pst_Undefined) :
		EnumType<TBaseballPlayerStatEnum,pst_Undefined,pst_Last>(t) {}

	bool isOffensive() const { return(fT < pst_EarnedRunAverage); }
};

/******************************************************************************/

class TBaseballTeam : public TTeam
{
protected:
	TPlayerIDVector fBatterLineup;
	TPlayerIDVector fPitcherLineup;
	
protected:
	TBaseballTeam() {}
	virtual ~TBaseballTeam() {}
	
public:
	virtual void clear();
	
	virtual const TPlayerIDVector& lineupConst(TLineup lineup) const;
	virtual TPlayerIDVector& lineup(TLineup lineup);
	
protected:
	/* DataSetRecord methods */
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	
	friend class RefCountPtr<TBaseballTeam>;
	friend class ASBaseballObjectBuilder;
};

class TBaseballTeamPtr : public TDataSetRecordPtr<TBaseballTeam,TTeamID>
{
public:
	TBaseballTeamPtr(TTeamPtr teamPtr = TTeamPtr()) :
		TDataSetRecordPtr<TBaseballTeam,TTeamID>(
			teamPtr.isNull() ? NULL :
			&dynamic_cast<TBaseballTeam&>(*teamPtr)) {}

	operator TTeamPtr() { return(TTeamPtr(fT)); }
};

/******************************************************************************/

class TBaseballProfPlayer : public TProfPlayer
{
protected:
	TBaseballPosition fPositionPrimary;
	TBaseballPosition fPositionSecondary;

	TRosterStatus fRosterStatus;
	
protected:
	TBaseballProfPlayer() {}
	virtual ~TBaseballProfPlayer() {}
	
public:
	virtual void clear();
	
	virtual int getPosition() const { return(fPositionPrimary); }
	virtual void setPosition(int position)
		{ fPositionPrimary = position; setHasChanged(); }
	
	int getPositionSecondary() const { return(fPositionSecondary); }
	void setPositionSecondary(int position)
		{ fPositionSecondary = position; setHasChanged(); }

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
	
	friend class RefCountPtr<TBaseballProfPlayer>;
	friend class ASBaseballObjectBuilder;
};

class TBaseballProfPlayerPtr : public TDataSetRecordPtr<TBaseballProfPlayer,TPlayerID>
{
public:
	TBaseballProfPlayerPtr(TProfPlayerPtr profPlayerPtr = TProfPlayerPtr()) :
		TDataSetRecordPtr<TBaseballProfPlayer,TPlayerID>(
			profPlayerPtr.isNull() ? NULL :
			&dynamic_cast<TBaseballProfPlayer&>(*profPlayerPtr)) {}

	operator TProfPlayerPtr() { return(TProfPlayerPtr(fT)); }
};

/******************************************************************************/

/*
GamesPlayed
GamesStarted
AtBats
Singles
Doubles
Triples
OneRunHomers
TwoRunHomers
ThreeRunHomers
GrandSlams
RunsScored
RunsBattedIn
SacrificeHits
SacrificeFlies
HitByPicth
UnintentWalks
IntentWalks
Strikeouts
StolenBases
CaughtStealing
Errors
GroundedDoublePlay
HitForCycle
*/

class TOffGameStatDetail
{
public:
	short fGamesPlayed;
	short fGamesStarted;
	short fAtBats;

	short fSingles;
	short fDoubles;
	short fTriples;

	short fOneRunHomers;
	short fTwoRunHomers;
	short fThreeRunHomers;
	short fGrandSlams;

	short fRunsScored;
	short fRunsBattedIn;
	short fSacrificeHits;
	short fSacrificeFlies;
	short fHitByPicth;
	short fUnintentWalks;
	short fIntentWalks;

	short fStrikeouts;
	short fStolenBases;
	short fCaughtStealing;
	short fErrors;
	short fGroundedDoublePlay;
	short fHitForCycle;

public:
	TOffGameStatDetail() { clear(); }

	virtual void clear();

	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TOffGameStatDetail& offGameStatDetail);
};

/******************************************************************************/

/*
Wins
Losses
Saves
BlownSaves
Holds
GamesPlayed
GamesStarted
CompleteGames
GamesFinished
QualityStarts
Shutouts
NoHitters
PerfectGames
OutsPitched
BattersFaced
SinglesAllowed
DoublesAllowed
TriplesAllowed
OneRunHomersAllowed
TwoRunHomersAllowed
ThreeRunHomersAllowed
GrandSlamsAllowed
UnearnedRunsAllowed
EarnedRunsAllowed
SacrificeHitsAllowed
SacrificeFliesAllowed
HitBatsmen
UnintentWalkedBatsmen
IntentWalkedBatsmen
StruckoutBatsmen
WildPitches
Balks
Errors
*/

class TDefGameStatDetail
{
public:
	short fWins;
	short fLosses;
	short fSaves;
	short fBlownSaves;
	short fHolds;

	short fGamesPlayed;
	short fGamesStarted;

	short fCompleteGames;
	short fGamesFinished;
	short fQualityStarts;
	short fShutouts;
	short fNoHitters;
	short fPerfectGames;

	short fOutsPitched;
	short fBattersFaced;
	short fSinglesAllowed;
	short fDoublesAllowed;
	short fTriplesAllowed;

	short fOneRunHomersAllowed;
	short fTwoRunHomersAllowed;
	short fThreeRunHomersAllowed;
	short fGrandSlamsAllowed;

	short fUnearnedRunsAllowed;
	short fEarnedRunsAllowed;
	short fSacrificeHitsAllowed;
	short fSacrificeFliesAllowed;
	short fHitBatsmen;
	short fUnintentWalkedBatsmen;
	short fIntentWalkedBatsmen;
	short fStruckoutBatsmen;
	short fWildPitches;
	short fBalks;
	short fErrors;
		
public:
	TDefGameStatDetail() { clear(); }

	virtual void clear();
	
	short calcTotalPoints() const;
	double getStat(int playerStatType);
	void sumStats(const TDefGameStatDetail& defGameStatDetail);
};

/******************************************************************************/

class TBaseballOffGameStat : public TOffGameStat
{
protected:
	TBaseballPosition fPosition;

	TOffGameStatDetail fOffGameStatDetail;

protected:
	TBaseballOffGameStat() {}
	virtual ~TBaseballOffGameStat() {}
	
public:
	virtual void clear();
	
	int getPosition() const { return(fPosition); }
	void setPosition(int position) { fPosition = position; setHasChanged(); }

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
	
	friend class RefCountPtr<TBaseballOffGameStat>;
	friend class ASBaseballObjectBuilder;
};

class TBaseballOffGameStatPtr : public TDataSetRecordPtr<TBaseballOffGameStat,
	TPlayerStatID>
{
public:
	TBaseballOffGameStatPtr(TOffGameStatPtr offGameStatPtr = TOffGameStatPtr()) :
		TDataSetRecordPtr<TBaseballOffGameStat,TPlayerStatID>(
			offGameStatPtr.isNull() ? NULL :
			&dynamic_cast<TBaseballOffGameStat&>(*offGameStatPtr)) {}

	operator TOffGameStatPtr() { return(TOffGameStatPtr(fT)); }
};

/******************************************************************************/

class TBaseballDefGameStat : public TDefGameStat
{
protected:
	TBaseballPosition fPosition;

	TDefGameStatDetail fDefGameStatDetail;

protected:
	TBaseballDefGameStat() {}
	virtual ~TBaseballDefGameStat() {}
	
public:
	virtual void clear();
	
	int getPosition() const { return(fPosition); }
	void setPosition(int position) { fPosition = position; setHasChanged(); }

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
	
	friend class RefCountPtr<TBaseballDefGameStat>;
	friend class ASBaseballObjectBuilder;
};

class TBaseballDefGameStatPtr : public TDataSetRecordPtr<TBaseballDefGameStat,
	TPlayerStatID>
{
public:
	TBaseballDefGameStatPtr(TDefGameStatPtr defGameStatPtr = TDefGameStatPtr()) :
		TDataSetRecordPtr<TBaseballDefGameStat,TPlayerStatID>(
			defGameStatPtr.isNull() ? NULL :
			&dynamic_cast<TBaseballDefGameStat&>(*defGameStatPtr)) {}

	operator TDefGameStatPtr() { return(TDefGameStatPtr(fT)); }
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballTypeH
/******************************************************************************/
/******************************************************************************/
