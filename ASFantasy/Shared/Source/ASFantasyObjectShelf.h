/* ASFantasyObjectShelf.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyObjectShelfH
#define ASFantasyObjectShelfH

#include "DataSetObjectShelf.h"
#include "ObjectStore.h"
#include "ASFantasyType.h"
#include "ASFantasyObjectBuilder.h"
#include "ASDraftType.h"
			 
using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class LeagueObjectShelf : public ObjectShelf<TLeagueID,TLeaguePtr>
{
public:
	LeagueObjectShelf(ASFantasyObjectBuilder& builder) :
		ObjectShelf<TLeagueID,TLeaguePtr>(builder) {}

/*
	virtual ObjectShelfItemBase* newItem(const ObjectShelfItemKeyBase& key) {}	//BOB
	virtual void loadItem(const ObjectShelfItemKeyBase& key,
		ObjectShelfItemBase& item) {}
	virtual TTeamPtr* newItemInstance(TTeamID key) { return(NULL); }
*/
};

/******************************************************************************/

class TeamObjectShelf : public DataSetObjectShelf<TTeamID,TTeamPtr>
{
public:
	TeamObjectShelf(ASFantasyObjectBuilder& builder) :
		DataSetObjectShelf<TTeamID,TTeamPtr>(builder) {}
		
	ASFantasyObjectBuilder& getBuilder() { return(dynamic_cast<ASFantasyObjectBuilder&>(fBuilder)); }

	virtual TTeamPtr* newItemInstance(TTeamID key);
};

/******************************************************************************/

class ProfPlayerObjectShelf : public DataSetObjectShelf<TPlayerID,TProfPlayerPtr>
{
public:
	ProfPlayerObjectShelf(ASFantasyObjectBuilder& builder) :
		DataSetObjectShelf<TPlayerID,TProfPlayerPtr>(builder) {}

	ASFantasyObjectBuilder& getBuilder() { return(dynamic_cast<ASFantasyObjectBuilder&>(fBuilder)); }
		
	virtual TProfPlayerPtr* newItemInstance(TPlayerID key);

	void getIDVectorByNewPlayerDateRange(TDateTime fromDate,TDateTime toDate,
		TPlayerIDVector& playerIDVector);
};

/******************************************************************************/

class ProfTeamObjectShelf : public ObjectShelf<TProfTeamID,TProfTeamPtr>
{
public:
	ProfTeamObjectShelf(ASFantasyObjectBuilder& builder) :
		ObjectShelf<TProfTeamID,TProfTeamPtr>(builder) {}

	TProfTeamPtr getByAbbr(TProfTeamAbbr profTeamAbbr,ObjectStore::GetItemMode getItemMode =
		ObjectStore::gim_MustExist);
};

/******************************************************************************/

class PlayerObjectShelf : public DataSetObjectShelf<TLeaguePlayerID,TPlayerPtr>
{
public:
	PlayerObjectShelf(ASFantasyObjectBuilder& builder) :
		DataSetObjectShelf<TLeaguePlayerID,TPlayerPtr>(builder) {}

	void getTeamPlayerIDVectorByTeam(TTeamID teamID,TPlayerIDVector& playerIDVector);
};

/******************************************************************************/

class OffGameStatObjectShelf : public ObjectShelf<TPlayerStatID,TOffGameStatPtr>
{
public:
	OffGameStatObjectShelf(ASFantasyObjectBuilder& builder) :
		ObjectShelf<TPlayerStatID,TOffGameStatPtr>(builder) {}
		
	void getVectorByPlayerIDVector(TPlayerIDVector& playerIDVector,
		TOffGameStatVector& offGameStatVector);
	void getVectorRandomByPlayerIDVector(TPlayerIDVector& playerIDVector,
		TOffGameStatVector& offGameStatVector);
};

/******************************************************************************/

class DefGameStatObjectShelf : public ObjectShelf<TPlayerStatID,TDefGameStatPtr>
{
public:
	DefGameStatObjectShelf(ASFantasyObjectBuilder& builder) :
		ObjectShelf<TPlayerStatID,TDefGameStatPtr>(builder) {}
		
	void getVectorByPlayerIDVector(TPlayerIDVector& playerIDVector,
		TDefGameStatVector& defGameStatVector);
	void getVectorRandomByPlayerIDVector(TPlayerIDVector& playerIDVector,
		TDefGameStatVector& defGameStatVector);
};

/******************************************************************************/

class DraftRankingObjectShelf : public ObjectShelf<TTeamID,TDraftRankingPtr>
{
public:
	DraftRankingObjectShelf(ASFantasyObjectBuilder& builder) :
		ObjectShelf<TTeamID,TDraftRankingPtr>(builder) {}
};

/******************************************************************************/

class DraftPosCountObjectShelf : public ObjectShelf<TDraftPosCountKey,TDraftPosCount>
{
public:
	DraftPosCountObjectShelf(ASFantasyObjectBuilder& builder) :
		ObjectShelf<TDraftPosCountKey,TDraftPosCount>(builder) {}
};

/******************************************************************************/

class ScheduleDayObjectShelf : public DataSetObjectShelf<TScheduleDayID,TScheduleDayPtr>
{
public:
	ScheduleDayObjectShelf(ASFantasyObjectBuilder& builder) :
		DataSetObjectShelf<TScheduleDayID,TScheduleDayPtr>(builder) {}
};

/******************************************************************************/

}; //namespace tag

#endif //ASFantasyObjectShelfH
/******************************************************************************/
/******************************************************************************/


