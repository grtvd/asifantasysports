/* ASFantasyGameResultsRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyGameResultsRqstH
#define ASFantasyGameResultsRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyType.h"
#include "ASFantasyMiscRqst.h"

namespace asfantasy
{

/******************************************************************************/

class GameResultsDay;	//forward reference
typedef RefCountPtr<GameResultsDay> GameResultsDayPtr;

class GameResultsDay : public RefCountObject, TStreamable
{
protected:
	CStrVar fGameDate;
	CStrVar fDescrip;

private:
	GameResultsDay(const TScheduleDayPtr scheduleDayPtr);

	GameResultsDay(const GameResultsDay&);						// don't allow copy constructor
	const GameResultsDay& operator=(const GameResultsDay&);		// or operator=

public:
	static GameResultsDayPtr createFromScheduleDay(
		const TScheduleDayPtr scheduleDayPtr)
		{ return(GameResultsDayPtr( new GameResultsDay(scheduleDayPtr))); } 

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	friend class RefCountPtr<GameResultsDay>;
};

class GameResultsDayVector : public std::vector<GameResultsDayPtr>
{
public:
	virtual void writeToFiler(TDataFiler& filer);
	void fillFromScheduleDayVector(const TScheduleDayVector& scheduleDayVector);
};

/******************************************************************************/

class GameResultsGame;	//forward reference
typedef RefCountPtr<GameResultsGame> GameResultsGamePtr;

class GameResultsGame : public RefCountObject, TStreamable
{
protected:
	TTeamID fHomeTeamID;
	CStrVar fDescrip;

private:
	GameResultsGame(const TScheduleDayGame& scheduleDayGame,
		const TTeamByIDVector& teamVector);

	GameResultsGame(const GameResultsDay&);						// don't allow copy constructor
	const GameResultsGame& operator=(const GameResultsDay&);		// or operator=

public:
	static GameResultsGamePtr createFromScheduleDayGame(
		const TScheduleDayGame& scheduleDayGame,const TTeamByIDVector& teamVector)
		{ return(GameResultsGamePtr( new GameResultsGame(scheduleDayGame,teamVector))); } 

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	friend class RefCountPtr<GameResultsGame>;
};

class GameResultsGameVector : public std::vector<GameResultsGamePtr>
{
public:
	virtual void writeToFiler(TDataFiler& filer);
	void fillFromScheduleDay(const TScheduleDayPtr scheduleDayPtr,
		const TTeamByIDVector& teamVector);
};

/******************************************************************************/

class GameResultsPlayer : public PlayerInfo
{
protected:
	short fTotalPoints;

	GameResultsPlayer(const TProfPlayerPtr profPlayerPtr,short totalPoints) :
		PlayerInfo(profPlayerPtr) { fTotalPoints = totalPoints; }
public:
	static PlayerInfoPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr,short totalPoints)
		{ return(PlayerInfoPtr(new GameResultsPlayer(profPlayerPtr,totalPoints))); }
	virtual void clear() { PlayerInfo::clear(); fTotalPoints = 0; }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	friend class RefCountPtr<GameResultsPlayer>;
};

class GameResultsPlayerPtr : public RefCountPtr<GameResultsPlayer>
{
public:
	GameResultsPlayerPtr(PlayerInfoPtr playerInfoPtr = PlayerInfoPtr()) :
		RefCountPtr<GameResultsPlayer>(playerInfoPtr.isNull() ? NULL :
			&dynamic_cast<GameResultsPlayer&>(*playerInfoPtr)) {}

	operator PlayerInfoPtr() { return(PlayerInfoPtr(fT)); }
};

/******************************************************************************/

class GameResultsRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;
	CStrVar fGameDate;
	TTeamID fHomeTeamID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
	int determineBestScheduleDayPosition(
		const TScheduleDayVector& scheduleDayVector);
	void fillGameResultsPlayerVector(TTeamID teamID,
		TDateTime gameDate,PlayerInfoVector& playerVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyGameResultsRqstH
/******************************************************************************/
/******************************************************************************/
