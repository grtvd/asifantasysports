/* ASFantasyMiscRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyObjectBuilder.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyMiscRqst.h"

namespace asfantasy
{

/******************************************************************************/

static void UnusedFunctionForTemplateCreatation();

/******************************************************************************/
/******************************************************************************/

void UnusedFunctionForTemplateCreatation()
{
	new TeamInfoNameVector();
}

/******************************************************************************/
/******************************************************************************/

PlayerInfo::PlayerInfo(const TProfPlayerPtr profPlayerPtr) :
	fPosition(0)
{
	if(!profPlayerPtr.isNull())
	{
		TProfTeamPtr profTeamPtr = ASFantasyObjectStore::getThe().getProfTeam(
			profPlayerPtr->getProfTeamID(),ObjectStore::gim_MustExist);

		fPlayerID = profPlayerPtr->getPlayerID();
		fName = profPlayerPtr->getName();
		fProfTeamAbbr = profTeamPtr->getProfTeamAbbr();
		fPosition = profPlayerPtr->getPosition();
	}
}

/******************************************************************************/

void PlayerInfo::clear()
{
	fPlayerID.clear();
	fName.clear();
	fProfTeamAbbr.clear();
	fPosition = 0;
}

/******************************************************************************/
	
void PlayerInfo::readFromFiler(TDataFiler& filer)
{
	throw ASIException("PlayerInfo::readFromFiler: not supported");
}

/******************************************************************************/

void PlayerInfo::writeToFiler(TDataFiler& filer)
{
	filer.writeLong(fPlayerID.getID());
	fName.writeToFiler(filer);
	filer.writeString(fProfTeamAbbr.c_str());
	filer.writeByte((byte)fPosition);
}

/******************************************************************************/
/******************************************************************************/

void PlayerInfoVector::writeToFiler(TDataFiler& filer)
{
	const_iterator iter;
	PlayerInfoPtr playerInfoPtr;
	
	filer.writeShort((short)size());
	for(iter = begin(); iter != end(); iter++)
	{
		playerInfoPtr = *iter;
		playerInfoPtr->writeToFiler(filer);
	}
}

/******************************************************************************/
/******************************************************************************/

PlayerInfoExt::PlayerInfoExt(const TProfPlayerPtr profPlayerPtr) :
	PlayerInfo(profPlayerPtr)
{
	fTotalPoints = profPlayerPtr->getTotalPoints();
	fLastWeeksPoints = profPlayerPtr->getLastWeeksPoints();
	
	fRosterStatus = profPlayerPtr->getRosterStatusString();
	fInjuryStatus = profPlayerPtr->getInjuryStatusString();
}

/******************************************************************************/

void PlayerInfoExt::clear()
{
	PlayerInfo::clear();
	
	fTotalPoints = 0;
	fLastWeeksPoints = 0;
	
	fRosterStatus.Clear();
	fInjuryStatus.Clear();
}

/******************************************************************************/

void PlayerInfoExt::readFromFiler(TDataFiler& filer)
{
	throw ASIException("PlayerInfoExt::readFromFiler: not supported");
}

/******************************************************************************/

void PlayerInfoExt::writeToFiler(TDataFiler& filer)
{
	PlayerInfo::writeToFiler(filer);
	
	filer.writeShort(fTotalPoints);
	filer.writeShort(fLastWeeksPoints);
	
	filer.writeString(fRosterStatus.c_str());
	filer.writeString(fInjuryStatus.c_str());
}

/******************************************************************************/
/******************************************************************************/

TeamInfoName::TeamInfoName(const TTeamPtr& teamPtr)
{
	clear();

	fTeamID = teamPtr->getTeamID();
	fRegionName.Copy(teamPtr->getRegionName());
	fTeamName.Copy(teamPtr->getTeamName());
}

/******************************************************************************/

void TeamInfoName::readFromFiler(TDataFiler& filer)
{
	throw ASIException("TeamInfoName::readFromFiler: not supported");
}

/******************************************************************************/

void TeamInfoName::writeToFiler(TDataFiler& filer)
{
	filer.writeLong(fTeamID.getID());
	filer.writeString(fRegionName.c_str());
	filer.writeString(fTeamName.c_str());
}

/******************************************************************************/
/******************************************************************************/

void TeamInfoNameVector::writeToFiler(TDataFiler& filer)
{
	const_iterator iter;
	TeamInfoNamePtr teamNamePtr;
	
	filer.writeShort((short)size());
	for(iter = begin(); iter != end(); iter++)
	{
		teamNamePtr = *iter;
		teamNamePtr->writeToFiler(filer);
	}
}

/******************************************************************************/

void TeamInfoNameVector::fillByLeagueID(const TLeagueID& leagueID)
{
	TTeamVector		teamVector;
	TeamInfoNamePtr	teamNamePtr;
	TTeamVector::const_iterator iter;

	erase(begin(),end());
	
	LoadTeamVectorByLeagueID( leagueID, teamVector );
	teamVector.sortByName();
	for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
	{
		teamNamePtr = TeamInfoName::createFromTeamPtr(*iter);
		push_back(teamNamePtr);
	}
}

/******************************************************************************/

void TeamInfoNameVector::removeByID(TTeamID teamID)
{
	iterator iter;
	
	for(iter = begin(); iter != end(); iter++)
		if((*iter)->getTeamID() == teamID)
		{
			erase(iter);
			return;
		}
}

/******************************************************************************/
/******************************************************************************/

void FillPlayerInfoExtVector(TTeamID teamID,PlayerInfoVector& playerInfoVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerVector playerVector;
	TPlayerVector::const_iterator iter;
	
	TProfPlayerPtr profPlayerPtr;
	PlayerInfoExtPtr playerInfoPtr;

	playerInfoVector.erase(playerInfoVector.begin(),playerInfoVector.end());
	LoadPlayerVectorByTeamID(teamID,playerVector);
	
	for (iter = playerVector.begin(); iter != playerVector.end(); iter++)
	{
		profPlayerPtr = store.getProfPlayer( (*iter)->getPlayerID() );
		playerInfoPtr = PlayerInfoExt::createFromProfPlayer(profPlayerPtr);
		
		playerInfoVector.push_back(playerInfoPtr);
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
