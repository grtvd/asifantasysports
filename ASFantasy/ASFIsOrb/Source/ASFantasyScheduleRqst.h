/* ASFantasyScheduleRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyScheduleRqstH
#define ASFantasyScheduleRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class ASFantasyScheduleDayGame;	//forward reference
typedef RefCountPtr<ASFantasyScheduleDayGame> ASFantasyScheduleDayGamePtr;

class ASFantasyScheduleDayGame : public RefCountObject, TStreamable
{
protected:
	TProfGameWeek fProfGameWeek;
	bool fGameIsScheduled;
	
	bool fIsHome;
	bool fDidWin;
	
	TTeamID fOppTeamID;

	short fWinningScore;
	short fLosingScore;
	
	ASFantasyScheduleDayGame(TTeamID teamID,
		const TScheduleDayPtr scheduleDayPtr);
public:
	static ASFantasyScheduleDayGamePtr createFromScheduleDayGame(
		TTeamID teamID,const TScheduleDayPtr scheduleDayPtr)
		{ return(ASFantasyScheduleDayGamePtr(
			new ASFantasyScheduleDayGame(teamID,scheduleDayPtr))); }

	void clear() { fProfGameWeek.clear(); fGameIsScheduled = false; fIsHome = false;
		fDidWin = false; fOppTeamID.clear(); fWinningScore = 0;
		fLosingScore = 0; }
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	friend class RefCountPtr<ASFantasyScheduleDayGame>;
};

/******************************************************************************/

typedef std::vector<ASFantasyScheduleDayGamePtr> ASFantasyScheduleDayGameVector;

/******************************************************************************/

class ScheduleRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual TStreamable* fulfillRequest();

protected:
	void fillGameVector(const TTeamPtr teamPtr,
		ASFantasyScheduleDayGameVector& gameVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyScheduleRqstH
/******************************************************************************/
/******************************************************************************/
