/* ASFantasyPlayerScoutRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include <algorith.h>
#include "CommType.h"
#include "CommDB.h"

#include "ASFantasyObjectStore.h"
#include "ASFantasyDB.h"
#include "ASFantasyPlayerScoutRqst.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

PlayerScoutPlayer::PlayerScoutPlayer(const TProfPlayerPtr profPlayerPtr) :
	PlayerInfo(profPlayerPtr)
{
	fRosterStatus = profPlayerPtr->getRosterStatusString();
	fInjuryStatus = profPlayerPtr->getInjuryStatusString();
}

/******************************************************************************/

void PlayerScoutPlayer::clear()
{
	PlayerInfo::clear();

	fRosterStatus.Clear();
	fInjuryStatus.Clear();
	fTeamID.clear();
	fFreeAgentAvail.Clear();
	
	fPlayerStatValueVector.erase(fPlayerStatValueVector.begin(),
		fPlayerStatValueVector.end());
}

/******************************************************************************/

void PlayerScoutPlayer::setTeamAvailable(TPlayerPtr playerPtr)
{
	if(playerPtr->isFreeAgent())
	{
		if(playerPtr->isNewFreeAgent())
			fFreeAgentAvail.Copy(FormatDateOnlyStr(
				playerPtr->getFreeAgentAvailableDate(),"m/d").c_str());
		else
			fFreeAgentAvail.Copy("Now");
	}
	else
		fTeamID = playerPtr->getTeamID();
}

/******************************************************************************/

void PlayerScoutPlayer::readFromFiler(TDataFiler& filer)
{
	throw ASIException("TPlayerScoutPlayer::readFromFiler: not supported");
}

/******************************************************************************/

void PlayerScoutPlayer::writeToFiler(TDataFiler& filer)
{
	int i,numItems;
	
	PlayerInfo::writeToFiler(filer);
		
	filer.writeString(fRosterStatus.c_str());
	filer.writeString(fInjuryStatus.c_str());
	filer.writeLong(fTeamID.getID());
	filer.writeString(fFreeAgentAvail.c_str());

	numItems = fPlayerStatValueVector.size();
	filer.writeByte((byte)numItems);
	for(i = 0; i < numItems; i++)
		filer.writeString(fPlayerStatValueVector[i].c_str());
}

/******************************************************************************/
/******************************************************************************/

void PlayerScoutResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("PlayerScoutResp::readFromFiler: not supported");
}

/******************************************************************************/

void PlayerScoutResp::writeToFiler(TDataFiler& filer)
{
	PlayerScoutPlayerPtr playerPtr;
	int i,numItems = fPlayerVector.size();

	filer.writeShort((short)numItems);
	for(i = 0; i < numItems; i++)
	{
		playerPtr = fPlayerVector[i];
		playerPtr->writeToFiler(filer);
	}

	fTeamInfoNameVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

void PlayerScoutRqst::readFromFiler(TDataFiler& filer)
{
	StatYearType statYearType;
	int statType;
	int i,numItems;
	
	fEncodedParticID = filer.readString().c_str();

	fPartialPlayerLastName = filer.readString().c_str();
	fProfTeamAbbr = filer.readString().c_str();

	numItems = filer.readByte();
	for(i = 0; i < numItems; i++)
		fPositionVector.push_back(asfantasy::TPosition(filer.readByte()));
	
	numItems = filer.readByte();
	for(i = 0; i < numItems; i++)
	{
		statType = filer.readByte();
		statYearType = filer.readByte();
		
		fStatVector.push_back(PlayerScoutStat(statType,statYearType));
	}
	
	fSelectNumPlayers = filer.readShort();
	fSelectByStat = filer.readByte();
	fSelectByStatAsc = filer.readBoolean();

	fIsFreeAgentRequest	= filer.readBoolean();
	fShowRanked = filer.readBoolean();
	fShowDrafted = filer.readBoolean();
	fShowMyTeamPlayers = filer.readBoolean();
	fShowOtherTeamsPlayers = filer.readBoolean();
}

/******************************************************************************/

void PlayerScoutRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("PlayerScoutRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* PlayerScoutRqst::fulfillRequest()
{
	auto_ptr<PlayerScoutResp> pResponse;
	PlayerScoutPlayerVector playerVector;
	TeamInfoNameVector teamInfoNameVector;
	
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TTeamVector teamVector;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);
	teamPtr = TTeam::createGet(particPtr->getTeamID(), cam_MustExist);

	if(fIsFreeAgentRequest)
	{
		if(fShowOtherTeamsPlayers)
			teamInfoNameVector.fillByLeagueID(teamPtr->getLeagueID());
		else if(fShowMyTeamPlayers)
			teamInfoNameVector.push_back(TeamInfoName::createFromTeamPtr(teamPtr));
	}

	fillPlayerVector(teamPtr,playerVector);

	pResponse.reset(new PlayerScoutResp(playerVector,teamInfoNameVector));
	return(pResponse.release());
}

/******************************************************************************/

void PlayerScoutRqst::fillPlayerVector(TTeamPtr& teamPtr,
	PlayerScoutPlayerVector& playerVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerIDVector playerIDVector;
	PlayerScoutPlayerPtr playerScoutPlayerPtr;
	TProfPlayerPtr profPlayerPtr;
	TPlayerID playerID;
	TPlayerIDVector::const_iterator idIter;
	int partialPlayerLastNameLen;
	TProfTeamID profTeamID;
	bool include;
	PlayerStatValueVector playerStatValueVector;
	int i,numItems;

	// Validate fSelectNumPlayers
	if((fSelectNumPlayers < 1) ||
			(fSelectNumPlayers > PlayerScoutRqstMaxSelectNumPlayers()))
		throw ASIException("PlayerScoutRqst::fillPlayerVector: invalid "
			"fSelectNumPlayers(%d)",fSelectNumPlayers);

	// Setup default PlayerStatValueVector
	numItems = fStatVector.size();
	for(i = 0; i < numItems; i++)
		playerStatValueVector.push_back(getDefaultPlayerStatValue(
			fStatVector[i].fStatType));

	// Fetcher ProfPlayers by search criteria
	
	partialPlayerLastNameLen = fPartialPlayerLastName.Len();
	store.getProfPlayerIDVector(playerIDVector);
	
	if(fProfTeamAbbr.Len() > 0)
	{
		TProfTeamPtr profTeamPtr = store.getProfTeamAbbr(fProfTeamAbbr,
			ObjectStore::gim_MustExist);

		profTeamID = profTeamPtr->getProfTeamID();
	}
	
	for(idIter = playerIDVector.begin(); idIter != playerIDVector.end(); idIter++)
	{
		playerID = *idIter;
		profPlayerPtr = store.getProfPlayer(playerID);

		include = true;
		// Was player's partial last name specified in search?
		if((partialPlayerLastNameLen > 0) &&
				(strnicmp(profPlayerPtr->getName().fLastName,
				fPartialPlayerLastName,partialPlayerLastNameLen) != 0))
			include = false;

		// Was player's prof team specified in search?
		if(include && !profTeamID.isUndefined() &&
				(profTeamID != profPlayerPtr->getProfTeamID()))
			include = false;

		// Was player's pos specified in search?
		if(include && !fPositionVector.contains(profPlayerPtr->getPosition()))
			include = false;

		if(include)
		{
			playerScoutPlayerPtr = createNewPlayerScoutPlayer(profPlayerPtr);
			playerScoutPlayerPtr->playerStatValueVector() = playerStatValueVector;
			playerVector.push_back(playerScoutPlayerPtr);
		}
	}

	playerVector.sortByID();
	
	// Free Agent Request
	if(fIsFreeAgentRequest)
	{
		TPlayerVector playerFreeAgentVector;
		TPlayerVector::const_iterator iter;

		LoadPlayerVectorByLeagueID(teamPtr->getLeagueID(),ptf_TeamPlayer |
			ptf_FreeAgent,playerFreeAgentVector);
			
		for(iter = playerFreeAgentVector.begin();
			iter != playerFreeAgentVector.end(); iter++)
		{
			TPlayerPtr playerPtr = *iter;

			playerScoutPlayerPtr = playerVector.getByID(playerPtr->getPlayerID());
			if(!playerScoutPlayerPtr.isNull())
			{
				include = false;

				if(playerPtr->isFreeAgent())
					include = true;
				else if(fShowMyTeamPlayers &&
						(playerPtr->getTeamID() == teamPtr->getTeamID()))
					include = true;
				else if(fShowOtherTeamsPlayers &&
						(playerPtr->getTeamID() != teamPtr->getTeamID()))
					include = true;

				if(include)
					playerScoutPlayerPtr->setTeamAvailable(playerPtr);
				else
					playerVector.removeByID(playerPtr->getPlayerID());
			}
		}
	}

	// Draft Request
	if(!fIsFreeAgentRequest)
	{
		// If ranked players should not be shown, fetch ranking and remove.
		if(!fShowRanked)
		{
			TDraftRankingPtr draftRankingPtr = TDraftRanking::createGet(
				teamPtr->getTeamID(),cam_MustExist);
			const TPlayerIDVector& playerIDVector = draftRankingPtr->playerIDVector();
			TPlayerIDVector::const_iterator iter;
		
			//BOB TOOLDEBUG( tErrorMsg("PlayerScoutRqst::fillPlayerVector: removing ranked players"); );
		
			for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
				playerVector.removeByID(*iter);
		}

		// If players already drafted should not be shown, remove from ranking.
		if(!fShowDrafted && !teamPtr->getLeagueID().isUndefined())
		{
			TPlayerVector playerTeamVector;
			TPlayerVector::const_iterator iter;

			LoadPlayerVectorByLeagueID(teamPtr->getLeagueID(),ptf_TeamPlayer,
				playerTeamVector);
				
			for(iter = playerTeamVector.begin();
					iter != playerTeamVector.end(); iter++)
				playerVector.removeByID((*iter)->getPlayerID());
		}
	}

	// Fetch stats for ProfPlayer, after removing "ranked" players
	//BOB TOOLDEBUG( tErrorMsg("PlayerScoutRqst::fillPlayerVector: fetching stats for %d players",
	//BOB 	playerVector.size()); );

	if(anyRequestForStatYear(syr_YearToDate,true))
		getOffStatYearForPlayerVector(playerVector,syr_YearToDate);
	if(anyRequestForStatYear(syr_YearToDate,false))
		getDefStatYearForPlayerVector(playerVector,syr_YearToDate);

	if(anyRequestForStatYear(syr_LastTwoWeeks,true))
		getOffStatYearForPlayerVector(playerVector,syr_LastTwoWeeks);
	if(anyRequestForStatYear(syr_LastTwoWeeks,false))
		getDefStatYearForPlayerVector(playerVector,syr_LastTwoWeeks);

	if(anyRequestForStatYear(syr_LastFourWeeks,true))
		getOffStatYearForPlayerVector(playerVector,syr_LastFourWeeks);
	if(anyRequestForStatYear(syr_LastFourWeeks,false))
		getDefStatYearForPlayerVector(playerVector,syr_LastFourWeeks);

	if(anyRequestForStatYear(syr_LastEightWeeks,true))
		getOffStatYearForPlayerVector(playerVector,syr_LastEightWeeks);
	if(anyRequestForStatYear(syr_LastEightWeeks,false))
		getDefStatYearForPlayerVector(playerVector,syr_LastEightWeeks);

	if(anyRequestForStatYear(syr_LastYear,true))
		getOffStatYearForPlayerVector(playerVector,syr_LastYear);
	if(anyRequestForStatYear(syr_LastYear,false))
		getDefStatYearForPlayerVector(playerVector,syr_LastYear);

	if(anyRequestForStatYear(syr_TwoYearsAgo,true))
		getOffStatYearForPlayerVector(playerVector,syr_TwoYearsAgo);
	if(anyRequestForStatYear(syr_TwoYearsAgo,false))
		getDefStatYearForPlayerVector(playerVector,syr_TwoYearsAgo);
	
	if(anyRequestForStatYear(syr_ThreeYearsAgo,true))
		getOffStatYearForPlayerVector(playerVector,syr_ThreeYearsAgo);
	if(anyRequestForStatYear(syr_ThreeYearsAgo,false))
		getDefStatYearForPlayerVector(playerVector,syr_ThreeYearsAgo);

	// If number of players found is large the requested, them trim.
	if(cast2int(playerVector.size()) > fSelectNumPlayers)
	{
		//BOB TOOLDEBUG( tErrorMsg("PlayerScoutRqst::fillPlayerVector: narrowing selection to top %d from %d",
		//BOB 	(int)fSelectNumPlayers,playerVector.size()); );
		
		// Sort by request.
		if((fSelectByStat >= 1) && (fSelectByStat <= 3))
			playerVector.sortByStat(fSelectByStat - 1,fSelectByStatAsc);
		else
			playerVector.sortByName();

		playerVector.erase(playerVector.begin() + fSelectNumPlayers,
			playerVector.end());
	}
	
	//BOB TOOLDEBUG( tErrorMsg("PlayerScoutRqst::fillPlayerVector: selection complete"); );
}

/******************************************************************************/

bool PlayerScoutRqst::anyRequestForStatYear(StatYearType statYear,bool offensive)
{
	int i,numStatVector = fStatVector.size();

	for(i = 0; i < numStatVector; i++)
		if((fStatVector[i].fStatType != 0) &&
				(fStatVector[i].fStatYear == statYear))
		{
			if(offensive)
			{
				if(isPlayerStatTypeOffensive(fStatVector[i].fStatType))
					return(true);
			}
			else
			{
				if(isPlayerStatTypeDefensive(fStatVector[i].fStatType))
					return(true);
			}
		}

	return(false);	
}

/******************************************************************************/

TStatPeriod PlayerScoutRqst::getStatPeriodFromStatYear(StatYearType statYear)
{
	if(statYear == syr_YearToDate)
		return(stp_SeasonToDate);

	if(statYear == syr_LastTwoWeeks)
		return(stp_LastTwoWeeks);

	if(statYear == syr_LastFourWeeks)
		return(stp_LastFourWeeks);

	if(statYear == syr_LastEightWeeks)
		return(stp_LastEightWeeks);

	if(statYear == syr_LastYear)
		return(stp_LastSeason);

	if(statYear == syr_TwoYearsAgo)
		return(stp_TwoSeasonsAgo);

	if(statYear == syr_ThreeYearsAgo)
		return(stp_ThreeSeasonsAgo);

	throw ASIException("PlayerScoutRqst::getStatPeriodFromStatYear: invalid statYear");
}

/******************************************************************************/

void PlayerScoutRqst::getOffStatYearForPlayerVector(
	PlayerScoutPlayerVector& playerVector,StatYearType statYear)
{
	TOffGameStatVector offGameStatVector;
	TOffGameStatVector::const_iterator iter;
	TOffGameStatPtr offGameStatPtr;

	PlayerScoutPlayerPtr playerScoutPlayerPtr;
	PlayerScoutStat playerScoutStat;
	
	int i,numStatVector;
	
	numStatVector = fStatVector.size();
	LoadOffGameStatVectorByStatPeriod(getStatPeriodFromStatYear(statYear),
		offGameStatVector);

	for(iter = offGameStatVector.begin(); iter != offGameStatVector.end(); ++iter)
	{
		offGameStatPtr = (*iter);

		playerScoutPlayerPtr = playerVector.getByID(offGameStatPtr->getPlayerID());
		if(!playerScoutPlayerPtr.isNull())
		{
			for(i = 0; i < numStatVector; i++)
			{
				playerScoutStat = fStatVector[i];
				
				if((playerScoutStat.fStatYear == statYear) &&
					(playerScoutStat.fStatType != 0) &&
					isPlayerStatTypeOffensive(playerScoutStat.fStatType))
				{
					if(i >= cast2int(playerScoutPlayerPtr->playerStatValueVector().size()))
						throw ASIException("PlayerScoutRqst::getStatYearForPlayerVector: fStatVector.size() != playerStatValueVector.size()");
						
					playerScoutPlayerPtr->playerStatValueVector()[i] = 
						offGameStatPtr->getStatStr(
						playerScoutStat.fStatType).c_str();
				}
			}
		}
	}
}

/******************************************************************************/

void PlayerScoutRqst::getDefStatYearForPlayerVector(
	PlayerScoutPlayerVector& playerVector,StatYearType statYear)
{
	TDefGameStatVector defGameStatVector;
	TDefGameStatVector::const_iterator iter;
	TDefGameStatPtr defGameStatPtr;
	
	PlayerScoutPlayerPtr playerScoutPlayerPtr;
	PlayerScoutStat playerScoutStat;
	
	TDateTime summaryDate;
	int i,numStatVector;
	
	LoadDefGameStatVectorByStatPeriod(getStatPeriodFromStatYear(statYear),
		defGameStatVector);
	numStatVector = fStatVector.size();
	
	for(iter = defGameStatVector.begin(); iter != defGameStatVector.end(); ++iter)
	{
		defGameStatPtr = (*iter);

		playerScoutPlayerPtr = playerVector.getByID(defGameStatPtr->getPlayerID());
		if(!playerScoutPlayerPtr.isNull())
		{
			for(i = 0; i < numStatVector; i++)
			{
				playerScoutStat = fStatVector[i];
				
				if((playerScoutStat.fStatYear == statYear) &&
					(playerScoutStat.fStatType != 0) &&
					isPlayerStatTypeDefensive(playerScoutStat.fStatType))
				{
					if(i >= cast2int(playerScoutPlayerPtr->playerStatValueVector().size()))
						throw ASIException("PlayerScoutRqst::getStatYearForPlayerVector: fStatVector.size() != playerStatValueVector.size()");
						
					playerScoutPlayerPtr->playerStatValueVector()[i] = 
						defGameStatPtr->getStatStr(
						playerScoutStat.fStatType).c_str();
				}
			}
		}
	}
}

/******************************************************************************/

};	// namespace asfantasy

/******************************************************************************/
/******************************************************************************/
