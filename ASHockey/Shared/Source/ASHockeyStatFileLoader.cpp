/* ASHockeyStatFileLoader.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectStore.h"
#include "ASHockeyStatFileLoader.h"

namespace ashockey
{

/******************************************************************************/

void OffGameStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();
	fPos = THockeyPosition();
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

	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());

	posStr = filer.readString().c_str();
	// convert position
	if(posStr == "LW")
		fPos = pos_Winger;
	else if(posStr == "RW")
		fPos = pos_Winger;
	else
		fPos = THockeyPosition(posStr);

	filer.readString();	// ProfTeam Abbr
	fProfTeamID.setID(filer.readShort());
	
	fStatDetail.fGamesPlayed = filer.readShort();
	fStatDetail.fGoals = filer.readShort();
	fStatDetail.fAssists = filer.readShort();
	fStatDetail.fPoints = filer.readShort();
	fStatDetail.fPlusMinus = filer.readShort();

	filer.readShort(); //total penalties
	fStatDetail.fMajorPenalties = filer.readShort();
	fStatDetail.fMinorPenalties = filer.readShort();
	fStatDetail.fPenaltyMinutes = filer.readShort();

	fStatDetail.fPowerPlayGoals = filer.readShort();
	fStatDetail.fShortHandedGoals = filer.readShort();
	fStatDetail.fGameWinningGoals = filer.readShort();
	fStatDetail.fGameTyingGoals = filer.readShort();
	fStatDetail.fEmptyNetGoals = filer.readShort();
	fStatDetail.fPowerPlayAssists = filer.readShort();
	fStatDetail.fShortHandedAssists = filer.readShort();
	fStatDetail.fOvertimeGoals = filer.readShort();

	fStatDetail.fShots = filer.readShort();
	fStatDetail.fHatTricks = filer.readShort();
	fStatDetail.fFights = filer.readShort();

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
	THockeyProfPlayerPtr profPlayerPtr;
	THockeyOffGameStatPtr offGameStatPtr;

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
	if(THockeyPosition(profPlayerPtr->getPosition()).isOffensive())
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
/******************************************************************************/

void DefGameStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();
	fRosterStatus.clear();

	fStatDetail.clear();
	
	// don't clear
	//fStatPeriod;
	//fStatDate;
	//fAddNewPlayers;
}

/******************************************************************************/

void DefGameStatFileLine::readFromFiler(TDataFiler& filer)
{
	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());
	filer.readString();	// ProfTeam Abbr
	fProfTeamID.setID(filer.readShort());

	fStatDetail.fGamesPlayed = filer.readShort();
	fStatDetail.fGamesStarted = filer.readShort();
	fStatDetail.fMinutesPlayed = filer.readShort();
	filer.readFloat();	// goals against average

	fStatDetail.fWins = filer.readShort();
	fStatDetail.fLosses = filer.readShort();
	fStatDetail.fTies = filer.readShort();

	fStatDetail.fEmptyNetGoalsAgainst = filer.readShort();
	fStatDetail.fShutouts = filer.readShort();
	fStatDetail.fGoalsAgainst = filer.readShort();
	fStatDetail.fShotsAgainst = filer.readShort();
	fStatDetail.fSaves = filer.readShort();
	filer.readFloat();	// save percentage

	fStatDetail.fMajorPenalties = filer.readShort();
	fStatDetail.fPenaltyMinutes = filer.readShort();
	fStatDetail.fFights = filer.readShort();

	fRosterStatus = filer.readString().c_str();
}

/******************************************************************************/

void DefGameStatFileLine::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("DefGameStatFileLine::writeToFiler not supported");
}

/******************************************************************************/

void DefGameStatFileLine::process()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	THockeyProfPlayerPtr profPlayerPtr;
	THockeyDefGameStatPtr defGameStatPtr;

	profPlayerPtr = store.getProfPlayer(fPlayerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		if(!fAddNewPlayers)
		{
			CommErrMsg(cel_Info,"DefGameStatFileLine::process: skipping "
				"PlayerID(%s)",fPlayerID.c_str());
			return;
		}
	
		profPlayerPtr = TProfPlayer::newInstance();
		profPlayerPtr->setPlayerID(fPlayerID);
		profPlayerPtr->getName() = fFullName;
		profPlayerPtr->setProfTeamID(fProfTeamID);
		profPlayerPtr->setGameStatus((fRosterStatus == rst_Inactive) ?
			ppgs_Disabled : ppgs_Active);	// rst_Disabled => ppgs_Active
		profPlayerPtr->setPosition(pos_Goalie);

		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());

		profPlayerPtr->setRosterStatus(fRosterStatus);

		store.addProfPlayer(profPlayerPtr);
		store.saveProfPlayer(fPlayerID);
		
		CommErrMsg(cel_Info,"DefGameStatFileLine::process: adding new "
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

			CommErrMsg(cel_Warning,"DefGameStatFileLine::process: receiving "
				"stat for ineligible player(%s), activating",
				profPlayerPtr->getPlayerID().c_str());
		}

		profPlayerPtr->setRosterStatus(fRosterStatus);
	}
	
	defGameStatPtr = TDefGameStat::newInstance();
	
	defGameStatPtr->setPlayerID(fPlayerID);
	defGameStatPtr->setStatPeriod(fStatPeriod);
	if(fStatPeriod == stp_SeasonGame)
	{
		//defGameStatPtr->setPosition(pos_Goalie);
		defGameStatPtr->setStatDate(fStatDate);
	}
	defGameStatPtr->defGameStatDetail() = fStatDetail;
	defGameStatPtr->calcTotalPoints();
	
	defGameStatPtr->update();

	// Update ProfPlayer TotalPoints and LastWeeksPoints, but only for Defensive players
	if(!THockeyPosition(profPlayerPtr->getPosition()).isOffensive())
	{
		profPlayerPtr->setTotalPoints(cast2short(
			profPlayerPtr->getTotalPoints() +
			defGameStatPtr->getTotalPoints()));
		profPlayerPtr->setLastWeeksPoints(cast2short(
			profPlayerPtr->getLastWeeksPoints() +
			defGameStatPtr->getTotalPoints()));
	}
	else
		CommErrMsg(cel_Warning,"OffGameStatFileLine::process: receiving "
			"defensive stat for offensive player(%s)",fPlayerID.c_str());
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
