/* ASFantasyMiscRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyMiscRqstH
#define ASFantasyMiscRqstH

#include <vector.h>

#include "Streamable.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class PlayerInfo;	//forward reference
typedef RefCountPtr<PlayerInfo> PlayerInfoPtr;

class PlayerInfo : public RefCountObject, TStreamable
{
protected:
	TPlayerID fPlayerID;
	TFullName fName;
	TProfTeamAbbr fProfTeamAbbr;
	TPosition fPosition;

	PlayerInfo(const TProfPlayerPtr profPlayerPtr);
	virtual ~PlayerInfo() {}
public:
	static PlayerInfoPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr)
		{ return(PlayerInfoPtr(new PlayerInfo(profPlayerPtr))); }
	virtual void clear();

	TPlayerID getPlayerID(void) const { return(fPlayerID); }
	
	const TFullName& getName() const { return(fName); }
	TFullName& getName() { return(fName); }

	TPosition getPosition(void) const { return(fPosition); }
		
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	friend class RefCountPtr<PlayerInfo>;
};

/******************************************************************************/

class PlayerInfoVector : public std::vector<PlayerInfoPtr>
{
public:
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/

class PlayerInfoExt : public PlayerInfo
{
protected:
	short fTotalPoints;
	short fLastWeeksPoints;
	
	CStr15 fRosterStatus;	// game specific
	CStr15 fInjuryStatus;	// game specific
	
	PlayerInfoExt(const TProfPlayerPtr profPlayerPtr);
public:
	static PlayerInfoPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr)
		{ return(PlayerInfoPtr(new PlayerInfoExt(profPlayerPtr))); }
	virtual void clear();

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	friend class RefCountPtr<PlayerInfoExt>;
};

class PlayerInfoExtPtr : public RefCountPtr<PlayerInfoExt>
{
public:
	PlayerInfoExtPtr(PlayerInfoPtr playerInfoPtr = PlayerInfoPtr()) :
		RefCountPtr<PlayerInfoExt>(playerInfoPtr.isNull() ? NULL :
			&dynamic_cast<PlayerInfoExt&>(*playerInfoPtr)) {}

	operator PlayerInfoPtr() { return(PlayerInfoPtr(fT)); }
};

/******************************************************************************/

class TeamInfoName;	//forward reference
typedef RefCountPtr<TeamInfoName> TeamInfoNamePtr;

class TeamInfoName : public RefCountObject, TStreamable
{
protected:
	TTeamID		fTeamID;
	TRegionName	fRegionName;
	TTeamName	fTeamName;
	
	TeamInfoName(const TTeamPtr& teamPtr);
public:
	static TeamInfoNamePtr createFromTeamPtr(
		const TTeamPtr teamPtr)
		{ return(TeamInfoNamePtr(new TeamInfoName(teamPtr))); }
	virtual void clear() { fTeamID.clear(); fRegionName.Clear(); fTeamName.Clear(); }
	
	TTeamID getTeamID(void) const { return(fTeamID); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	friend class RefCountPtr<TeamInfoName>;
};

/******************************************************************************/

class TeamInfoNameVector : public std::vector<TeamInfoNamePtr>
{
public:
	virtual void writeToFiler(TDataFiler& filer);
	void fillFromTeamVector(const TTeamVector& teamVector);
	void fillByLeagueID(const TLeagueID& leagueID);

	void removeByID(TTeamID teamID);
};

/******************************************************************************/

void FillPlayerInfoExtVector(TTeamID teamID,PlayerInfoVector& playerInfoVector);

/******************************************************************************/

}; //namespace asfantasy

#endif	//ASFantasyMiscRqstH
/******************************************************************************/
/******************************************************************************/
