/* ASBasketballStatFileLoader.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectStore.h"
#include "ASBasketballStatFileLoader.h"

namespace asbasketball
{

/******************************************************************************/

void OffGameStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();
	fPos = TBasketballPosition();
	fRosterStatus.clear();

	fStatDetail.clear();
	
	// don't clear
	//fStatPeriod;
	//fStatDate;
	//fAddNewPlayers;
}

/******************************************************************************/

void OffGameStatFileLine::readFromFiler(TDataFiler& filer)
{
	CStr15 posStr;
	short fieldGoalsMade;
	short fieldGoalsAttempted;
	short threePointGoalsAttempted;
	short tempShort;

	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());
	fProfTeamID.setID(filer.readShort());

	posStr = filer.readString().c_str();
	// convert position
	if(posStr == "G")			//Guard
		fPos = pos_ShootingGuard;
	else if(posStr == "GF")		//Guard-Forward
		fPos = pos_ShootingGuard;
	else if(posStr == "F")		//Forward
		fPos = pos_PowerForward;
	else if(posStr == "FC")		//Forward-Center
		fPos = pos_PowerForward;
	else
		fPos = TBasketballPosition(posStr);

	fStatDetail.fGamesPlayed = filer.readShort();
	fStatDetail.fMinutesPlayed = filer.readShort();
	fStatDetail.fPointsScored = filer.readShort();

	fieldGoalsMade = filer.readShort();	//Field Goals Made
	fieldGoalsAttempted = filer.readShort();	//Field Goals Attempted

	fStatDetail.fFreeThrowsMade = filer.readShort();	//Free Throws Made
	tempShort = filer.readShort();	//Free Throws Attempted
	fStatDetail.fFreeThrowsMissed = cast2short(tempShort -
		fStatDetail.fFreeThrowsMade);
	
	fStatDetail.fThreePointGoalsMade = filer.readShort();	//Three Point Goals Made
	threePointGoalsAttempted = filer.readShort();	//Three Point Goals Attempted
	fStatDetail.fThreePointGoalsMissed = cast2short(threePointGoalsAttempted -
		fStatDetail.fThreePointGoalsMade);

	fStatDetail.fTwoPointGoalsMade = cast2short(fieldGoalsMade -
		fStatDetail.fThreePointGoalsMade);
	fStatDetail.fTwoPointGoalsMissed = cast2short((fieldGoalsAttempted -
		threePointGoalsAttempted) - fStatDetail.fTwoPointGoalsMade);

	fStatDetail.fOffensiveRebounds = filer.readShort();
	fStatDetail.fDefensiveRebounds = filer.readShort();
	filer.readShort();	//Total Rebounds

	fStatDetail.fAssists = filer.readShort();
	fStatDetail.fSteals = filer.readShort();
	fStatDetail.fBlocks = filer.readShort();

	fStatDetail.fTurnovers = filer.readShort();
	fStatDetail.fPersonalFouls = filer.readShort();
	fStatDetail.fTechnicalFouls = filer.readShort();

	fRosterStatus = filer.readString().c_str();
}

/******************************************************************************/

void OffGameStatFileLine::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("OffGameStatFileLine::writeToFiler not supported");
}

/******************************************************************************/

void OffGameStatFileLine::process()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TBasketballProfPlayerPtr profPlayerPtr;
	TBasketballOffGameStatPtr offGameStatPtr;

	profPlayerPtr = store.getProfPlayer(fPlayerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		if(!fAddNewPlayers)
		{
			CommErrMsg(cel_Info,"OffGameStatFileLine::process: skipping "
				"PlayerID(%s)",fPlayerID.c_str());
			return;
		}
	
		profPlayerPtr = TProfPlayer::newInstance();
		profPlayerPtr->setPlayerID(fPlayerID);
		profPlayerPtr->getName() = fFullName;
		profPlayerPtr->setProfTeamID(fProfTeamID);
		profPlayerPtr->setGameStatus((fRosterStatus == rst_Inactive) ?
			ppgs_Disabled : ppgs_Active);	// rst_Disabled => ppgs_Active
		profPlayerPtr->setPosition(fPos);

		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());

		profPlayerPtr->setRosterStatus(fRosterStatus);

		store.addProfPlayer(profPlayerPtr);
		store.saveProfPlayer(fPlayerID);
		
		CommErrMsg(cel_Info,"OffGameStatFileLine::process: adding new "
			"player(%s)",profPlayerPtr->getPlayerID().c_str());
	}
	else
	{
		// Only active player if RosterStatus is active.
		if((profPlayerPtr->getGameStatus() != ppgs_Active) &&
			(fRosterStatus != rst_Inactive))
		{
			profPlayerPtr->setGameStatus(ppgs_Active);
			profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());

			CommErrMsg(cel_Warning,"OffGameStatFileLine::process: receiving "
				"stat for ineligible player(%s), activating",
				profPlayerPtr->getPlayerID().c_str());
		}

		profPlayerPtr->setRosterStatus(fRosterStatus);
	}

	offGameStatPtr = TOffGameStat::newInstance();
	
	offGameStatPtr->setPlayerID(fPlayerID);
	offGameStatPtr->setStatPeriod(fStatPeriod);
	if(fStatPeriod == stp_SeasonGame)
	{
		//offGameStatPtr->setPosition(fPos);
		offGameStatPtr->setStatDate(fStatDate);
	}

	offGameStatPtr->offGameStatDetail() = fStatDetail;
	offGameStatPtr->calcTotalPoints();
	
	offGameStatPtr->update();

	// Update ProfPlayer TotalPoints and LastWeeksPoints, but only for Offensive players
	if(TBasketballPosition(profPlayerPtr->getPosition()).isOffensive())
	{
		profPlayerPtr->setTotalPoints(cast2short(
			profPlayerPtr->getTotalPoints() +
			offGameStatPtr->getTotalPoints()));
		profPlayerPtr->setLastWeeksPoints(cast2short(
			profPlayerPtr->getLastWeeksPoints() +
			offGameStatPtr->getTotalPoints()));
	}
	else
		CommErrMsg(cel_Warning,"OffGameStatFileLine::process: receiving "
			"offensive stat for defensive player(%s)",fPlayerID.c_str());
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
