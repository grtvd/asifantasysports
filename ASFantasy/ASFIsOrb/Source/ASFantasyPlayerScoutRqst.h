/* ASFantasyPlayerScoutRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyPlayerScoutRqstH
#define ASFantasyPlayerScoutRqstH

#include <vector.h>

#include "Requestable.h"
#include "ASFantasyMiscRqst.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

#define PlayerScoutRqstMaxSelectNumPlayers()		(250)

/******************************************************************************/

enum StatYearEnum
{
	syr_Undefined = 0,
	syr_YearToDate,
	syr_LastTwoWeeks,
	syr_LastFourWeeks,
	syr_LastEightWeeks,
	syr_LastYear,
	syr_TwoYearsAgo,
	syr_ThreeYearsAgo
};
#define syr_Last syr_ThreeYearsAgo
class StatYearType : public EnumType<StatYearEnum,syr_Undefined,syr_Last>
{
public:
	StatYearType(int t = syr_Undefined) :
		EnumType<StatYearEnum,syr_Undefined,syr_Last>(t) {}
};

/******************************************************************************/

class PlayerScoutStat
{
public:
	int fStatType;		// Which stat, game specific.
	StatYearType fStatYear;

	PlayerScoutStat(int statType = 0,StatYearType statYear = syr_Undefined) :
		fStatType(statType), fStatYear(statYear) {}
};

class PlayerScoutStatVector : public std::vector<PlayerScoutStat> {};

/******************************************************************************/

DefineFixStrClass(PlayerStatValue,8);
class PlayerStatValueVector : public std::vector<PlayerStatValue> {};

class PlayerScoutPlayer : public PlayerInfo
{
protected:
	CStr15 fRosterStatus;
	CStr15 fInjuryStatus;
	TTeamID fTeamID;
	CStr15 fFreeAgentAvail;

	PlayerStatValueVector fPlayerStatValueVector;
	
protected:
	PlayerScoutPlayer(const TProfPlayerPtr profPlayerPtr);
	virtual ~PlayerScoutPlayer() {}
public:
	static PlayerInfoPtr createFromProfPlayer(
		const TProfPlayerPtr profPlayerPtr)
		{ return(PlayerInfoPtr(new PlayerScoutPlayer(profPlayerPtr))); }
	virtual void clear();

	void setTeamAvailable(TPlayerPtr playerPtr);
	
	PlayerStatValueVector& playerStatValueVector() { return(fPlayerStatValueVector); }
	const PlayerStatValueVector& playerStatValueVector() const { return(fPlayerStatValueVector); }
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	friend class RefCountPtr<PlayerScoutPlayer>;
};

class PlayerScoutPlayerPtr : public RefCountPtr<PlayerScoutPlayer>
{
public:
	PlayerScoutPlayerPtr(PlayerInfoPtr playerInfoPtr = PlayerInfoPtr()) :
		RefCountPtr<PlayerScoutPlayer>(playerInfoPtr.isNull() ? NULL :
			&dynamic_cast<PlayerScoutPlayer&>(*playerInfoPtr)) {}

	operator PlayerInfoPtr() { return(PlayerInfoPtr(fT)); }
};

/******************************************************************************/

class PlayerScoutPlayerVector : public std::vector<PlayerScoutPlayerPtr>
{
public:
	void sortByID() { std::sort(begin(),end(),sortIDCompare()); }

	// Must have called sortByID
	PlayerScoutPlayerPtr getByID(TPlayerID playerID)
	{
		iterator iter = std::lower_bound(begin(),end(),playerID,idSearch());
		
		if((iter != end()) && ((*iter)->getPlayerID() == playerID))
			return(*iter);
		
		return(PlayerScoutPlayerPtr());
	}

	// Must have called sortByID
	void removeByID(TPlayerID playerID)
	{
		iterator iter = std::lower_bound(begin(),end(),playerID,idSearch());
		
		if((iter != end()) && ((*iter)->getPlayerID() == playerID))
			erase(iter);
	}

	void sortByName() { std::sort(begin(),end(),sortNameCompare()); }
	void sortByStat(int stat,bool ascending) { std::sort(begin(),end(),
		sortStatCompare(stat,ascending)); }

protected:
	struct sortIDCompare
	{
		bool operator() (const PlayerScoutPlayerPtr& lhs, const PlayerScoutPlayerPtr& rhs) const
			{ return(lhs->getPlayerID() < rhs->getPlayerID()); }
	};
	struct idSearch
	{
		bool operator()(const PlayerScoutPlayerPtr& lhs, const TPlayerID& rhs) const
			{ return lhs->getPlayerID() < rhs; }
	};
		
	struct sortNameCompare
	{
		bool operator() (const PlayerScoutPlayerPtr& lhs, const PlayerScoutPlayerPtr& rhs) const
		{
			int rc;
			
			rc = stricmp(lhs->getName().fLastName,rhs->getName().fLastName);
			if(rc < 0)
				return(true);
			if(rc > 0)
				return(false);
				
			rc = stricmp(lhs->getName().fFirstName,rhs->getName().fFirstName);
			if(rc < 0)
				return(true);
			return(false);
		}
	};
	
	struct sortStatCompare
	{
	protected:
		int fStat;
		bool fAscending;
		
	public:
		sortStatCompare(int stat,bool ascending) { fStat = stat; fAscending = ascending; }
		
		bool operator() (const PlayerScoutPlayerPtr& lhs, const PlayerScoutPlayerPtr& rhs) const
		{
			PlayerStatValue lhsStat =
				(cast2int(lhs->playerStatValueVector().size()) > fStat)
				? lhs->playerStatValueVector()[fStat] : PlayerStatValue();
				
			PlayerStatValue rhsStat =
				(cast2int(rhs->playerStatValueVector().size()) > fStat)
				? rhs->playerStatValueVector()[fStat] : PlayerStatValue();

			if(fAscending)
				return(lhsStat < rhsStat);
			else
				return(rhsStat < lhsStat);
		}
	};
};

/******************************************************************************/

class PlayerScoutResp : public TStreamable
{
private:
	PlayerScoutPlayerVector fPlayerVector;
	TeamInfoNameVector fTeamInfoNameVector;

public:
	PlayerScoutResp(PlayerScoutPlayerVector& playerVector,
		TeamInfoNameVector teamInfoNameVector) : fPlayerVector(playerVector),
		fTeamInfoNameVector(teamInfoNameVector) {}
	
	virtual const char* className() const { return("PlayerScoutResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/

class PlayerScoutRqst : public TRequestable
{
protected:
	TEncodedParticID fEncodedParticID;
	
	TLastName fPartialPlayerLastName;	// Include by Partial Last Name
	TProfTeamAbbr fProfTeamAbbr;		// Include Prof Team
	TPositionVector fPositionVector;	// Include Positions
	
	PlayerScoutStatVector fStatVector;	// Return stats
	int fSelectNumPlayers;				// Number of players to return.
	int fSelectByStat;					// Offset into fStatVector, top
										//	fSelectNumPlayers by fStatVector stat.
	bool fSelectByStatAsc;				// Ascending or Descending

	bool fIsFreeAgentRequest;			// Is this a draft or free agent request?
	bool fShowRanked;					// Show Players already ranked (Draft)
	bool fShowDrafted;					// Show Players already drafted (Draft)
	bool fShowMyTeamPlayers;			// Show Players on my Team (Free Agent)
	bool fShowOtherTeamsPlayers;		// Show Players on other Teams in League (Free Agent)

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
	void fillPlayerVector(TTeamPtr& teamPtr,
		PlayerScoutPlayerVector& playerVector);
		
	virtual PlayerScoutPlayerPtr createNewPlayerScoutPlayer(
		const TProfPlayerPtr profPlayerPtr)
		{ return(PlayerScoutPlayer::createFromProfPlayer(profPlayerPtr)); }

	virtual PlayerStatValue getDefaultPlayerStatValue(int playerStatType) = 0;
	virtual bool isPlayerStatTypeOffensive(int playerStatType) = 0;
	virtual bool isPlayerStatTypeDefensive(int playerStatType) = 0;
	
	bool anyRequestForStatYear(StatYearType statYear,bool offensive);
	TStatPeriod getStatPeriodFromStatYear(StatYearType statYear);
	
	void getOffStatYearForPlayerVector(PlayerScoutPlayerVector& playerVector,
		StatYearType statYear);
	void getDefStatYearForPlayerVector(PlayerScoutPlayerVector& playerVector,
		StatYearType statYear);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyPlayerScoutRqstH
/******************************************************************************/
/******************************************************************************/
