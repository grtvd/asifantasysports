/* ASBaseballStatFileLoader.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyObjectStore.h"
#include "ASBaseballStatFileLoader.h"

namespace asbaseball
{

/******************************************************************************/

static TBaseballPosition ConvertStrToBaseballPosition(const char* position,
	const bool isPitcherStarter);

/******************************************************************************/
/******************************************************************************/

TBaseballPosition ConvertStrToBaseballPosition(const char* position,
	const bool isPitcherStarter)
{
	CStr31 posStr(position);
	TBaseballPosition pos;

	if(!posStr.HasLen())
		return(TBaseballPosition());

	// convert position
	if(posStr == "LF")
		pos = pos_Outfielder;
	else if(posStr == "CF")
		pos = pos_Outfielder;
	else if(posStr == "RF")
		pos = pos_Outfielder;
	else if(posStr == "PH")
		pos = pos_DesignatedHitter;
	else if(posStr == "PR")
		pos = pos_DesignatedHitter;
	else if(posStr == "P")
	{
		if(isPitcherStarter)
			pos = pos_StartingPitcher;
		else
			pos = pos_ReliefPitcher;
	}
	else
		pos = TBaseballPosition(posStr);

	return(pos);
}

/******************************************************************************/
/******************************************************************************/

void PlayerRosterFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();

	fPosPrimary = TBaseballPosition();
	fPosSecondary = TBaseballPosition();

	fRosterStatus.clear();
}

/******************************************************************************/

void PlayerRosterFileLine::readFromFiler(TDataFiler& filer)
{
	CStr15 posStr;
	TBooleanType active;

	fPlayerID.setID(filer.readLong());
	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());
	
	fProfTeamID.setID(filer.readShort());
	filer.readString();	// ProfTeam Abbr

	fPosPrimary = ConvertStrToBaseballPosition(filer.readString().c_str(),
		false);
	fPosSecondary = ConvertStrToBaseballPosition(filer.readString().c_str(),
		false);

	if(fPosPrimary == fPosSecondary)
		fPosSecondary.clear();

	active = filer.readString().c_str();
	fRosterStatus = active ? rst_Active : rst_Inactive;
}

/******************************************************************************/

void PlayerRosterFileLine::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("PlayerRosterFileLine::writeToFiler not supported");
}

/******************************************************************************/
	
void PlayerRosterFileLine::process()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TBaseballProfPlayerPtr profPlayerPtr;
	TBaseballOffGameStatPtr offGameStatPtr;

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
		
	profPlayerPtr->getName() = fFullName;
	profPlayerPtr->setProfTeamID(fProfTeamID);
	
	profPlayerPtr->setPosition(fPosPrimary);
	profPlayerPtr->setPositionSecondary(fPosSecondary);
	profPlayerPtr->setRosterStatus(fRosterStatus);
	
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/
/******************************************************************************/

void OffGameStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();
	fPos = TBaseballPosition();

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
	short hits;
	short walks;

	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());
	filer.readString();	// ProfTeam Abbr
	fProfTeamID.setID(filer.readShort());
	posStr = filer.readString().c_str();
	
	fStatDetail.fGamesPlayed = filer.readShort();
	fStatDetail.fGamesStarted = filer.readShort();
	fStatDetail.fAtBats = filer.readShort();

	// convert position
	if(posStr == "LF")
		fPos = pos_Outfielder;
	else if(posStr == "CF")
		fPos = pos_Outfielder;
	else if(posStr == "RF")
		fPos = pos_Outfielder;
	else if(posStr == "PH")
		fPos = pos_DesignatedHitter;
	else if(posStr == "PR")
		fPos = pos_DesignatedHitter;
	else if(posStr == "P")
	{
		if(fStatDetail.fGamesStarted)
			fPos = pos_StartingPitcher;
		else
			fPos = pos_ReliefPitcher;
	}
	else
		fPos = TBaseballPosition(posStr);

	fStatDetail.fRunsScored = filer.readShort();

	hits = filer.readShort();
	fStatDetail.fDoubles = filer.readShort();
	fStatDetail.fTriples = filer.readShort();

	fStatDetail.fOneRunHomers = filer.readShort();
	fStatDetail.fTwoRunHomers = filer.readShort();
	fStatDetail.fThreeRunHomers = filer.readShort();
	fStatDetail.fGrandSlams = filer.readShort();

	fStatDetail.fSingles = hits - fStatDetail.fDoubles - fStatDetail.fTriples -
		fStatDetail.fOneRunHomers - fStatDetail.fTwoRunHomers - 
		fStatDetail.fThreeRunHomers - fStatDetail.fGrandSlams;

	fStatDetail.fRunsBattedIn = filer.readShort();
	fStatDetail.fSacrificeHits = filer.readShort();
	fStatDetail.fSacrificeFlies = filer.readShort();
	fStatDetail.fHitByPicth = filer.readShort();

	walks = filer.readShort();
	fStatDetail.fIntentWalks = filer.readShort();
	fStatDetail.fUnintentWalks = walks - fStatDetail.fIntentWalks;

	fStatDetail.fStrikeouts = filer.readShort();
	fStatDetail.fStolenBases = filer.readShort();
	fStatDetail.fCaughtStealing = filer.readShort();
	fStatDetail.fErrors = filer.readShort();
	fStatDetail.fGroundedDoublePlay = filer.readShort();
	fStatDetail.fHitForCycle = filer.readShort();
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
	TBaseballProfPlayerPtr profPlayerPtr;
	TBaseballOffGameStatPtr offGameStatPtr;

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
		profPlayerPtr->setGameStatus(ppgs_Active);
		profPlayerPtr->setPosition(fPos);

		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());
		
		profPlayerPtr->setRosterStatus(rst_Active);
	
		store.addProfPlayer(profPlayerPtr);
		store.saveProfPlayer(fPlayerID);
		
		CommErrMsg(cel_Info,"OffGameStatFileLine::process: adding new "
			"player(%s)",profPlayerPtr->getPlayerID().c_str());
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
				"stat for %s player(%s), activating",
				(profPlayerPtr->getRosterStatus() == rst_Disabled) ?
				"disabled" : "inactive",profPlayerPtr->getPlayerID().c_str());
		}

		#if 0	//BOB
		if(profPlayerPtr->getPosition() != fPos)
		{
			TBaseballPosition playerPos = profPlayerPtr->getPosition();
			
			CommErrMsg(cel_Warning,"OffGameStatFileLine::process: receiving "
				"stat for alternate pos(%s) for player(%s), pos(%s)",
				fPos.c_str(),profPlayerPtr->getPlayerID().c_str(),
				playerPos.c_str());
		}
		#endif	//BOB
	}

	offGameStatPtr = TOffGameStat::newInstance();
	
	offGameStatPtr->setPlayerID(fPlayerID);
	offGameStatPtr->setStatPeriod(fStatPeriod);
	if(fStatPeriod == stp_SeasonGame)
	{
		offGameStatPtr->setPosition(fPos);
		offGameStatPtr->setStatDate(fStatDate);
	}
	offGameStatPtr->offGameStatDetail() = fStatDetail;
	offGameStatPtr->calcTotalPoints();
	
	offGameStatPtr->update();

	// Update ProfPlayer TotalPoints and LastWeeksPoints, but only for Offensive players
	if(TBaseballPosition(profPlayerPtr->getPosition()).isOffensive())
	{
		profPlayerPtr->setTotalPoints(profPlayerPtr->getTotalPoints() +
			offGameStatPtr->getTotalPoints());
		profPlayerPtr->setLastWeeksPoints(profPlayerPtr->getLastWeeksPoints() +
			offGameStatPtr->getTotalPoints());
	}
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/
/******************************************************************************/

void DefGameStatFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();
	fPos = TBaseballPosition();

	fStatDetail.clear();
	
	// don't clear
	//fStatPeriod;
	//fStatDate;
	//fAddNewPlayers;
}

/******************************************************************************/

void DefGameStatFileLine::readFromFiler(TDataFiler& filer)
{
	double inningsPitched;
	short hits;
	short runs;
	short walks;

	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());
	
	fPlayerID.setID(filer.readLong());
	filer.readString();	// ProfTeam Abbr
	fProfTeamID.setID(filer.readShort());

	fStatDetail.fWins = filer.readShort();
	fStatDetail.fLosses = filer.readShort();
	fStatDetail.fSaves = filer.readShort();
	fStatDetail.fBlownSaves = filer.readShort();
	fStatDetail.fHolds = filer.readShort();

	fStatDetail.fGamesPlayed = filer.readShort();
	fStatDetail.fGamesStarted = filer.readShort();

	if(fStatDetail.fGamesStarted)
		fPos = pos_StartingPitcher;
	else
		fPos = pos_ReliefPitcher;

	fStatDetail.fCompleteGames = filer.readShort();
	fStatDetail.fGamesFinished = filer.readShort();
	fStatDetail.fQualityStarts = filer.readShort();
	fStatDetail.fShutouts = filer.readShort();

	inningsPitched = filer.readDouble();
	fStatDetail.fOutsPitched = floor(inningsPitched) * 3;	//BOB OutsPerInning() or ConvOutsToInnings(), ConvInningsToOuts()
	if(floor(((inningsPitched - floor(inningsPitched)) * 10) + 0.5) == 1)
		fStatDetail.fOutsPitched += 1;
	else if(floor(((inningsPitched - floor(inningsPitched)) * 10) + 0.5) == 2)
		fStatDetail.fOutsPitched += 2;

	fStatDetail.fBattersFaced = filer.readShort();
	hits = filer.readShort();
	fStatDetail.fDoublesAllowed = filer.readShort();
	fStatDetail.fTriplesAllowed = filer.readShort();

	fStatDetail.fOneRunHomersAllowed = filer.readShort();
	fStatDetail.fTwoRunHomersAllowed = filer.readShort();
	fStatDetail.fThreeRunHomersAllowed = filer.readShort();
	fStatDetail.fGrandSlamsAllowed = filer.readShort();

	fStatDetail.fSinglesAllowed = hits - fStatDetail.fDoublesAllowed -
		fStatDetail.fTriplesAllowed - fStatDetail.fOneRunHomersAllowed -
		fStatDetail.fTwoRunHomersAllowed - fStatDetail.fThreeRunHomersAllowed -
		fStatDetail.fGrandSlamsAllowed;

	runs = filer.readShort();
	fStatDetail.fEarnedRunsAllowed = filer.readShort();
	fStatDetail.fUnearnedRunsAllowed = runs - fStatDetail.fEarnedRunsAllowed;

	fStatDetail.fSacrificeHitsAllowed = filer.readShort();
	fStatDetail.fSacrificeFliesAllowed = filer.readShort();
	fStatDetail.fHitBatsmen = filer.readShort();

	walks = filer.readShort();
	fStatDetail.fIntentWalkedBatsmen = filer.readShort();
	fStatDetail.fUnintentWalkedBatsmen = walks - fStatDetail.fIntentWalkedBatsmen;

	fStatDetail.fStruckoutBatsmen = filer.readShort();
	fStatDetail.fWildPitches = filer.readShort();
	fStatDetail.fBalks = filer.readShort();
	
	fStatDetail.fNoHitters = filer.readShort();
	fStatDetail.fPerfectGames = filer.readShort();

	fStatDetail.fErrors = filer.readShort();
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
	TBaseballProfPlayerPtr profPlayerPtr;
	TBaseballDefGameStatPtr defGameStatPtr;

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
		profPlayerPtr->setGameStatus(ppgs_Active);
		profPlayerPtr->setPosition(fPos);

		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());
		
		profPlayerPtr->setRosterStatus(rst_Active);
	
		store.addProfPlayer(profPlayerPtr);
		store.saveProfPlayer(fPlayerID);
		
		CommErrMsg(cel_Info,"DefGameStatFileLine::process: adding new "
			"player(%s)",profPlayerPtr->getPlayerID().c_str());
	}
	else
	{
		if(profPlayerPtr->getGameStatus() != ppgs_Active)
		{
			profPlayerPtr->setGameStatus(ppgs_Active);
			profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());
			profPlayerPtr->setRosterStatus(rst_Active);

			CommErrMsg(cel_Warning,"DefGameStatFileLine::process: receiving "
				"stat for ineligible player(%s), activating",
				profPlayerPtr->getPlayerID().c_str());
		}

		if(profPlayerPtr->getRosterStatus() != rst_Active)
		{
			profPlayerPtr->setRosterStatus(rst_Active);

			CommErrMsg(cel_Warning,"DefGameStatFileLine::process: receiving "
				"stat for %s player(%s), activating",
				(profPlayerPtr->getRosterStatus() == rst_Disabled) ?
				"disabled" : "inactive",profPlayerPtr->getPlayerID().c_str());
		}

		#if 0	//BOB
		if(profPlayerPtr->getPosition() != fPos)
		{
			TBaseballPosition playerPos = profPlayerPtr->getPosition();
			
			CommErrMsg(cel_Warning,"DefGameStatFileLine::process: receiving "
				"stat for alternate pos(%s) for player(%s), pos(%s)",
				fPos.c_str(),profPlayerPtr->getPlayerID().c_str(),
				playerPos.c_str());
		}
		#endif
	}
	
	defGameStatPtr = TDefGameStat::newInstance();
	
	defGameStatPtr->setPlayerID(fPlayerID);
	defGameStatPtr->setStatPeriod(fStatPeriod);
	if(fStatPeriod == stp_SeasonGame)
	{
		defGameStatPtr->setPosition(fPos);
		defGameStatPtr->setStatDate(fStatDate);
	}
	defGameStatPtr->defGameStatDetail() = fStatDetail;
	defGameStatPtr->calcTotalPoints();
	
	defGameStatPtr->update();

	// Update ProfPlayer TotalPoints and LastWeeksPoints, but only for Defensive players
	if(!TBaseballPosition(profPlayerPtr->getPosition()).isOffensive())
	{
		profPlayerPtr->setTotalPoints(profPlayerPtr->getTotalPoints() +
			defGameStatPtr->getTotalPoints());
		profPlayerPtr->setLastWeeksPoints(profPlayerPtr->getLastWeeksPoints() +
			defGameStatPtr->getTotalPoints());
	}
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/
/******************************************************************************/

void InjuryFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();

	fRosterStatus.clear();
	fStatusDate = TDateTime();
	fNotes.clear();
}

/******************************************************************************/

void InjuryFileLine::readFromFiler(TDataFiler& filer)
{
	CStr15 posStr;
	TBooleanType active;

	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());

	fPlayerID.setID(filer.readLong());
	filer.readString();	// ProfTeam Abbr
	fProfTeamID.setID(filer.readShort());

	fRosterStatus = filer.readString().c_str();
	fStatusDate = filer.readDate();
	fNotes = filer.readString().c_str();
}

/******************************************************************************/

void InjuryFileLine::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("InjuryFileLine::writeToFiler not supported");
}

/******************************************************************************/

void InjuryFileLine::process()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TBaseballProfPlayerPtr profPlayerPtr;

	profPlayerPtr = store.getProfPlayer(fPlayerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		CommErrMsg(cel_Info,"InjuryFileLine::process: skipping PlayerID(%s)",
			fPlayerID.c_str());
		return;
	}
		
	profPlayerPtr->getName() = fFullName;
	profPlayerPtr->setProfTeamID(fProfTeamID);

	if((fRosterStatus == rst_Active) &&
		(profPlayerPtr->getGameStatus() != ppgs_Active))
	{
		profPlayerPtr->setGameStatus(ppgs_Active);
		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());

		CommErrMsg(cel_Info,"InjuryFileLine::process: receiving "
			"activation for ineligible player(%s), activating",
			profPlayerPtr->getPlayerID().c_str());
	}

	profPlayerPtr->setLastUpdatedDate(fStatusDate);
	profPlayerPtr->setRosterStatus(fRosterStatus);
	
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/
/******************************************************************************/

void TransactionFileLine::clear()
{
	fFullName.clear();
	fPlayerID.clear();
	fProfTeamID.clear();

	fRosterStatus.clear();
	fStatusDate = TDateTime();
	fNotes.clear();
}

/******************************************************************************/

void TransactionFileLine::readFromFiler(TDataFiler& filer)
{
	CStr15 posStr;
	TBooleanType active;

	fFullName.fFirstName.Copy(filer.readString().c_str());
	fFullName.fLastName.Copy(filer.readString().c_str());

	fPlayerID.setID(filer.readLong());
	filer.readString();	// ProfTeam Abbr
	fProfTeamID.setID(filer.readShort());

	fRosterStatus = filer.readString().c_str();
	fStatusDate = filer.readDate();
	fNotes = filer.readString().c_str();
}

/******************************************************************************/

void TransactionFileLine::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TransactionFileLine::writeToFiler not supported");
}

/******************************************************************************/

void TransactionFileLine::process()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TBaseballProfPlayerPtr profPlayerPtr;

	profPlayerPtr = store.getProfPlayer(fPlayerID,ObjectStore::gim_MayNotExist);
	if(profPlayerPtr.isNull())
	{
		CommErrMsg(cel_Info,"TransactionFileLine::process: skipping PlayerID(%s)",
			fPlayerID.c_str());
		return;
	}
		
	profPlayerPtr->getName() = fFullName;
	profPlayerPtr->setProfTeamID(fProfTeamID);

	if((fRosterStatus == rst_Active) &&
		(profPlayerPtr->getGameStatus() != ppgs_Active))
	{
		profPlayerPtr->setGameStatus(ppgs_Active);
		profPlayerPtr->setNewPlayerDate(TDateTime::CurrentDate());

		CommErrMsg(cel_Info,"TransactionFileLine::process: receiving "
			"activation for ineligible player(%s), activating",
			profPlayerPtr->getPlayerID().c_str());
	}

	profPlayerPtr->setLastUpdatedDate(fStatusDate);
	profPlayerPtr->setRosterStatus(fRosterStatus);
	
	store.saveProfPlayer(fPlayerID);
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
