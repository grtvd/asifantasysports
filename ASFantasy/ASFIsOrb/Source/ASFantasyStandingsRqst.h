/* ASFantasyStandingsRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyStandingsRqstH
#define ASFantasyStandingsRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyType.h"
#include "ASFantasyMiscRqst.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class StandingsTeam : public TeamInfoName
{
protected:
	short	fWins;
	short	fLoses;
	short	fTies;
	short	fDivWins;
	short	fDivLoses;
	short	fDivTies;
	short	fStreak;
	CStr31	fWinPercent;
	short	fTotalPoints;

	StandingsTeam(const TTeamPtr& teamPtr);
public:
	static TeamInfoNamePtr createFromTeamPtr(const TTeamPtr& teamPtr)
		{ return(TeamInfoNamePtr(new StandingsTeam(teamPtr))); }

	short getTotalPoints() const { return(fTotalPoints); }
		
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	friend class RefCountPtr<StandingsTeam>;
};

class StandingsTeamPtr : public RefCountPtr<StandingsTeam>
{
public:
	StandingsTeamPtr(TeamInfoNamePtr teamInfoNamePtr = TeamInfoNamePtr()) :
		RefCountPtr<StandingsTeam>(teamInfoNamePtr.isNull() ? NULL :
			&dynamic_cast<StandingsTeam&>(*teamInfoNamePtr)) {}

	operator TeamInfoNamePtr() { return(TeamInfoNamePtr(fT)); }
};

/******************************************************************************/

class StandingsRqst : public TRequestable
{
private:
	TEncodedParticID fEncodedParticID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual TStreamable* fulfillRequest();

protected:
	void validateRequest(TParticPtr& particPtr,TTeamPtr& teamPtr);
	void fillTeamInfoNameVector(TParticPtr& particPtr,TTeamPtr& teamPtr,
		TeamInfoNameVector& eastTeamInfoNameVector,
		TeamInfoNameVector& westTeamInfoNameVector);
	void fillDivisionTeamInfoNameVector(TTeamVector& teamVector,
		TeamInfoNameVector& teamInfoNameVector);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyStandingsRqstH
/******************************************************************************/
/******************************************************************************/
