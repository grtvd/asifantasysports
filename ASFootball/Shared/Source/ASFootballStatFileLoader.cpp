/* ASFootballStatFileLoader.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectStore.h"
#include "ASFootballStatFileLoader.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

void PlayerInfoStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fPos = TFootballPosition();
	fProfTeamID.clear();
	
	fCollegeName.Clear();
	fYearsPro = 0;

	fLastUpdated = TDateTime();
	fInjuryStatus.clear();
	fRosterStatus.clear();
}

/******************************************************************************/

void PlayerInfoStatFileLine::readFromFiler(TDataFiler& filer)
{
	fFullName.fLastName.Copy(filer.readString().c_str());
	fFullName.fFirstName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());
	fPos = TFootballPosition(filer.readString().c_str());
	fProfTeamID.setID(filer.readShort());
	fLastUpdated = filer.readDate(DF_MM_DD_YYYY);
	
	fCollegeName = filer.readString().c_str();
	fYearsPro = filer.readShort();
	fInjuryStatus = filer.readString().c_str();
	fRosterStatus = filer.readString().c_str();
}

/******************************************************************************/

void PlayerInfoStatFileLine::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("PlayerInfoStatFileLine::writeToFiler not supported");
}

/******************************************************************************/
	
void PlayerInfoStatFileLine::process()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TFootballProfPlayerPtr profPlayerPtr;
	TFootballPosition usePosition;

	usePosition = fPos;
	
	profPlayerPtr = store.getProfPlayer(fPlayerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		profPlayerPtr = TProfPlayer::newInstance();
		profPlayerPtr->setPlayerID(fPlayerID);

		// Assume inactive players are not eligible, disabled players are eligible
		profPlayerPtr->setGameStatus((fRosterStatus == rst_Inactive) ?
			ppgs_Disabled : ppgs_Active);
		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());

		store.addProfPlayer(profPlayerPtr);
	}
	else if(profPlayerPtr->getPosition() != fPos)
	{
		usePosition = profPlayerPtr->getPosition();

		if(usePosition.isKey())
		{		
			TOOLDEBUG( tErrorMsg("PlayerInfoStatFileLine::process: overriding "
				"status file pos (%s) with stored pos (%s) for %s (%s)",
				fPos.c_str(),usePosition.c_str(),
				profPlayerPtr->getName().fLastName.c_str(),		//BOB buildFullName(),
				profPlayerPtr->getPlayerID().c_str()); );
		}
		else
		{
			TOOLDEBUG( tErrorMsg("PlayerInfoStatFileLine::process: replacing "
				"stored pos (%s) with status file pos (%s) for %s (%s)",
				usePosition.c_str(),fPos.c_str(),
				profPlayerPtr->getName().fLastName.c_str(),		//BOB buildFullName(),
				profPlayerPtr->getPlayerID().c_str()); );
		
			usePosition = fPos;
		}
	}

	profPlayerPtr->getName() = fFullName;
	profPlayerPtr->setProfTeamID(fProfTeamID);
	profPlayerPtr->setPosition(usePosition);

	profPlayerPtr->setLastUpdatedDate(fLastUpdated);
	profPlayerPtr->setRosterStatus(fRosterStatus);
	profPlayerPtr->setInjuryStatus(fInjuryStatus);
	profPlayerPtr->setCollegeName(fCollegeName);
	profPlayerPtr->setYearsPro(fYearsPro);
	
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/
/******************************************************************************/

void OffGameStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();
	fPos = TFootballPosition();

	fStatDetail.clear();
	
	// don't clear
	//fStatPeriod;
	//fStatDate;
	//fAddNewPlayers;
}

/******************************************************************************/

void OffGameStatFileLine::readYardageBucketsFromFiler(TDataFiler& filer,
	YardageBuckets& yardageBuckets)
{
	int i,numItems;

	yardageBuckets.clear();
	
	numItems = filer.readByte();
	for(i = 0; i < numItems; i++)
		yardageBuckets.addYards(filer.readByte());
}

/******************************************************************************/

void OffGameStatFileLine::readFromFiler(TDataFiler& filer)
{
	fFullName.fLastName.Copy(filer.readString().c_str());
	fFullName.fFirstName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());
	fPos = TFootballPosition(filer.readString().c_str());
	fProfTeamID.setID(filer.readShort());
	
	if(filer.readDate(DF_MM_DD_YYYY) != fStatDate)	//fStatDate
		throw ASIException("OffGameStatFileLine::readFromFiler: fStatDate mismatch");
	
	/* Passing Stats */
	fStatDetail.fPassingYards = filer.readShort();
	fStatDetail.fInterceptions = filer.readByte();
	fStatDetail.fTwoPointPasses = filer.readByte();
	
	/* Rushing Stats */
	fStatDetail.fRushingYards = filer.readShort();
	fStatDetail.fFumbles = filer.readByte();
	fStatDetail.fTwoPointRushes = filer.readByte();
	
	/* Receiving Stats */
	fStatDetail.fReceivingYards = filer.readShort();
	fStatDetail.fTwoPointReceptions = filer.readByte();

	/* TD Yardage Stats */	
	readYardageBucketsFromFiler(filer,fStatDetail.fPassingTDYardageBuckets);
	readYardageBucketsFromFiler(filer,fStatDetail.fRushingTDYardageBuckets);
	readYardageBucketsFromFiler(filer,fStatDetail.fReceivingTDYardageBuckets);
	readYardageBucketsFromFiler(filer,fStatDetail.fKickReturnTDYardageBuckets);
	readYardageBucketsFromFiler(filer,fStatDetail.fMiscTDYardageBuckets);
	
	/* Kicking Stats */
	fStatDetail.fPATsAttempted = filer.readByte();
	fStatDetail.fPATsMade = filer.readByte();
	fStatDetail.fFieldGoalsAttempted = filer.readByte();
	
	readYardageBucketsFromFiler(filer,fStatDetail.fFieldGoalYardageBuckets);
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
	TFootballProfPlayerPtr profPlayerPtr;
	TFootballOffGameStatPtr offGameStatPtr;

	profPlayerPtr = store.getProfPlayer(fPlayerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		if(!fAddNewPlayers)
		{
			TOOLDEBUG( tErrorMsg("OffGameStatFileLine::process: skipping "
				"PlayerID(%s)",fPlayerID.c_str()); );
			return;
		}
	
		profPlayerPtr = TProfPlayer::newInstance();
		profPlayerPtr->setPlayerID(fPlayerID);
		profPlayerPtr->getName() = fFullName;
		profPlayerPtr->setProfTeamID(fProfTeamID);
		profPlayerPtr->setGameStatus(ppgs_Active);
		profPlayerPtr->setPosition(fPos);

		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());
		
		profPlayerPtr->setRosterStatus(rst_Active);
		profPlayerPtr->setInjuryStatus(ist_NoInjury);
	
		store.addProfPlayer(profPlayerPtr);
		store.saveProfPlayer(fPlayerID);
		
		TOOLDEBUG( tErrorMsg("OffGameStatFileLine::process: adding new "
			"player(%s)",profPlayerPtr->getPlayerID().c_str()); );
	}
	else
	{
		if(profPlayerPtr->getGameStatus() != ppgs_Active)
		{
			profPlayerPtr->setGameStatus(ppgs_Active);
			profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());
			profPlayerPtr->setRosterStatus(rst_Active);

			CommErrMsg(cel_Warning,"OffGameStatFileLine::process: receiving "
				"stat for ineligible player(%s), activating",
				profPlayerPtr->getPlayerID().c_str());
		}

		if(profPlayerPtr->getRosterStatus() != rst_Active)
		{
			profPlayerPtr->setRosterStatus(rst_Active);

			CommErrMsg(cel_Warning,"OffGameStatFileLine::process: receiving "
				"stat for inactive player(%s), activating",
				profPlayerPtr->getPlayerID().c_str());
		}
	}

	offGameStatPtr = TOffGameStat::newInstance();
	
	offGameStatPtr->setPlayerID(fPlayerID);
	offGameStatPtr->setStatPeriod(fStatPeriod);
	if(fStatPeriod == stp_SeasonGame)
		offGameStatPtr->setStatDate(fStatDate);
	offGameStatPtr->offGameStatDetail() = fStatDetail;
	offGameStatPtr->calcTotalPoints();
	
	offGameStatPtr->update();

	profPlayerPtr->setTotalPoints(cast2short(profPlayerPtr->getTotalPoints() +
		offGameStatPtr->getTotalPoints()));
	profPlayerPtr->setLastWeeksPoints(offGameStatPtr->getTotalPoints());
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/
/******************************************************************************/

void DefGameStatFileLine::clear()
{
	fRegionName.Clear();
	fTeamName.Clear();
	fProfTeamID.clear();

	fStatDetail.clear();
	
	// don't clear
	//fStatPeriod;
	//fStatDate;
	//fSkipUnknownPlayers;
}

/******************************************************************************/

void DefGameStatFileLine::readFromFiler(TDataFiler& filer)
{
	fRegionName.Copy(filer.readString().c_str());
	fTeamName.Copy(filer.readString().c_str());
	fProfTeamID.setID(filer.readShort());
	
	if(filer.readDate(DF_MM_DD_YYYY) != fStatDate)	//fStatDate
		throw ASIException("DefGameStatFileLine::readFromFiler: fStatDate mismatch");
	
	fStatDetail.fPassingYardsAllowed = filer.readShort();
	fStatDetail.fRushingYardsAllowed = filer.readShort();
	fStatDetail.fSafeties = filer.readByte();
	fStatDetail.fSacks = filer.readByte();
	fStatDetail.fBlockedKicks = filer.readByte();
	fStatDetail.fFumblesRecovered = filer.readByte();
	fStatDetail.fDefensiveTDs = filer.readByte();
	fStatDetail.fInterceptions = filer.readByte();
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
	TFootballProfPlayerPtr profPlayerPtr;
	TFootballDefGameStatPtr defGameStatPtr;
	TPlayerID playerID;

	playerID = ConvertProfTeamIDtoPlayerID(fProfTeamID);
	profPlayerPtr = store.getProfPlayer(playerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		if(fSkipUnknownPlayers)
		{
			CommErrMsg(cel_Info,"DefGameStatFileLine::process: skipping "
				"ProfTeamID(%s)",fProfTeamID.c_str());
			return;
		}

		throw ASIException("DefGameStatFileLine::process: invalid PlayerID");
	}
	
	defGameStatPtr = TDefGameStat::newInstance();
	
	defGameStatPtr->setPlayerID(playerID);
	defGameStatPtr->setStatPeriod(fStatPeriod);
	if(fStatPeriod == stp_SeasonGame)
		defGameStatPtr->setStatDate(fStatDate);
	defGameStatPtr->defGameStatDetail() = fStatDetail;
	defGameStatPtr->calcTotalPoints();
	
	defGameStatPtr->update();

	profPlayerPtr->setTotalPoints(cast2short(profPlayerPtr->getTotalPoints() +
		defGameStatPtr->getTotalPoints()));
	profPlayerPtr->setLastWeeksPoints(defGameStatPtr->getTotalPoints());
	store.saveProfPlayer(playerID);
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
