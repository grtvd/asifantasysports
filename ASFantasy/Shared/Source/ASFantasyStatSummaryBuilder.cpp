/* ASFantasyStatSummaryBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "CommDB.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyStatSummaryBuilder.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void StatSummaryBuilder::standAloneBuildAllPlayersForStatPeriod(
	const TStatPeriod statPeriod)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	try
	{
		store.addProfPlayerShelf();
		store.addProfTeamShelf();

		store.loadAllProfPlayers();
		store.loadAllProfTeams();
	
		buildAllPlayersForStatPeriod(statPeriod);
	}
	catch(const Exception& e)
	{
		store.delProfTeamShelf();
		store.delProfPlayerShelf();
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		store.delProfTeamShelf();
		store.delProfPlayerShelf();
		throw;
	}
		
	store.delProfTeamShelf();
	store.delProfPlayerShelf();
}

/******************************************************************************/

void StatSummaryBuilder::buildAllPlayersForStatPeriod(
	const TStatPeriod statPeriod)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerIDVector playerIDVector;
	TDateTime fromDate;
	TDateTime toDate;

	store.getProfPlayerIDVector(playerIDVector);

	PurgeOffGameStatByStatPeriod(statPeriod);
	PurgeDefGameStatByStatPeriod(statPeriod);

	getSeasonDateRangeForStatPeriod(statPeriod,fromDate,toDate);
	sumPlayerIDVectorForStatPeriodDateRange(playerIDVector,statPeriod,
		fromDate,toDate);
}

/******************************************************************************/

void StatSummaryBuilder::standAloneBuildAllPlayersForThisSeason(
	const TDateTime asOfDate)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	try
	{
		store.addProfPlayerShelf();
		store.addProfTeamShelf();

		store.loadKeyProfPlayers();
		store.loadAllProfTeams();
	
		buildAllPlayersForThisSeason(asOfDate);
	}
	catch(const Exception& e)
	{
		store.delProfTeamShelf();
		store.delProfPlayerShelf();
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		store.delProfTeamShelf();
		store.delProfPlayerShelf();
		throw;
	}
		
	store.delProfTeamShelf();
	store.delProfPlayerShelf();
}

/******************************************************************************/

void StatSummaryBuilder::buildAllPlayersForThisSeason(const TDateTime asOfDate)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();

	TPlayerIDVector playerIDVector;
	TPlayerIDVector::iterator playerIDIter;
	TPlayerID playerID;

	TStatPeriodVector statPeriodVector;
	TStatPeriodVector::iterator statPeriodIter;
	TStatPeriod statPeriod;

	TOffGameStatVector seasonOffGameStatVector;
	TDefGameStatVector seasonDefGameStatVector;
	TOffGameStatVector offGameStatVector;
	TDefGameStatVector defGameStatVector;

	TDateTime seasonFromDate;
	TDateTime seasonToDate;
	TDateTime fromDate;
	TDateTime toDate;

	// setup 'this season' stat periods
	statPeriodVector.push_back(stp_LastTwoWeeks);
	statPeriodVector.push_back(stp_LastFourWeeks);
	statPeriodVector.push_back(stp_LastEightWeeks);
	statPeriodVector.push_back(stp_SeasonToDate);

	// purge all stats for all 'this season' stat periods
	PurgeOffGameStatByStatPeriodVector(statPeriodVector);
	PurgeDefGameStatByStatPeriodVector(statPeriodVector);

	// get all players
	store.getProfPlayerIDVector(playerIDVector);
	getSeasonDateRangeForStatPeriod(stp_SeasonToDate,seasonFromDate,seasonToDate);

	for(playerIDIter = playerIDVector.begin();
		playerIDIter != playerIDVector.end(); ++playerIDIter)
	{
		playerID = *playerIDIter;

		// get all OffGameStats for player for this season
		LoadOffGameStatVectorByPlayerIDDateRange(playerID,seasonFromDate,
			seasonToDate,seasonOffGameStatVector);

		if(seasonOffGameStatVector.size() > 0)
		{
			// sum OffGameStats for all StatPeriods
			for(statPeriodIter = statPeriodVector.begin();
				statPeriodIter != statPeriodVector.end(); ++statPeriodIter)
			{
				statPeriod = *statPeriodIter;

				getDateRangeForStatPeriodAsOfDate(statPeriod,asOfDate,fromDate,
					toDate);
				getOffGamesStatsInDateRange(seasonOffGameStatVector,fromDate,
					toDate,offGameStatVector);
				sumOffStatsForProfPlayerStatPeriod(playerID,statPeriod,
					offGameStatVector);
			}
		}

		// get all DefGameStats for player for this season
		LoadDefGameStatVectorByPlayerIDDateRange(playerID,seasonFromDate,
			seasonToDate,seasonDefGameStatVector);

		if(seasonDefGameStatVector.size() > 0)
		{
			// sum DefGameStats for all StatPeriods
			for(statPeriodIter = statPeriodVector.begin();
				statPeriodIter != statPeriodVector.end(); ++statPeriodIter)
			{
				statPeriod = *statPeriodIter;

				getDateRangeForStatPeriodAsOfDate(statPeriod,asOfDate,fromDate,
					toDate);
				getDefGamesStatsInDateRange(seasonDefGameStatVector,fromDate,
					toDate,defGameStatVector);
				sumDefStatsForProfPlayerStatPeriod(playerID,statPeriod,
					defGameStatVector);
			}
		}
	}
}

/******************************************************************************/

void StatSummaryBuilder::getOffGamesStatsInDateRange(
	const TOffGameStatVector& offGameStatVector,const TDateTime fromDate,
	const TDateTime toDate,TOffGameStatVector& subSetOffGameStatVector)
{
	TOffGameStatVector::const_iterator iter;
	TOffGameStatPtr offGameStatPtr;

	subSetOffGameStatVector.erase(subSetOffGameStatVector.begin(),
		subSetOffGameStatVector.end());

	for(iter = offGameStatVector.begin(); iter != offGameStatVector.end(); ++iter)
	{
		offGameStatPtr = *iter;

		if((offGameStatPtr->getStatDate() >= fromDate) &&
				(offGameStatPtr->getStatDate() <= toDate))
			subSetOffGameStatVector.push_back(offGameStatPtr);
	}
}

/******************************************************************************/

void StatSummaryBuilder::getDefGamesStatsInDateRange(
	const TDefGameStatVector& defGameStatVector,const TDateTime fromDate,
	const TDateTime toDate,TDefGameStatVector& subSetDefGameStatVector)
{
	TDefGameStatVector::const_iterator iter;
	TDefGameStatPtr defGameStatPtr;

	subSetDefGameStatVector.erase(subSetDefGameStatVector.begin(),
		subSetDefGameStatVector.end());

	for(iter = defGameStatVector.begin(); iter != defGameStatVector.end(); ++iter)
	{
		defGameStatPtr = *iter;

		if((defGameStatPtr->getStatDate() >= fromDate) &&
				(defGameStatPtr->getStatDate() <= toDate))
			subSetDefGameStatVector.push_back(defGameStatPtr);
	}
}

/******************************************************************************/

void StatSummaryBuilder::getSeasonDateRangeForStatPeriod(
	const TStatPeriod statPeriod,TDateTime& fromDate,TDateTime& toDate)
{
	int firstStatYear = DateYear(ConvertTDateTimetoTDate(StatStartDate()));
	int firstStatMonth;
	int firstStatDay;

	getEarliestPossibleStatMonthDay(firstStatMonth,firstStatDay);

	if(statPeriod == stp_SeasonToDate)
		;
	else if(statPeriod == stp_LastSeason)
		firstStatYear -= 1;
	else if(statPeriod == stp_TwoSeasonsAgo)
		firstStatYear -= 2;
	else if(statPeriod == stp_ThreeSeasonsAgo)
		firstStatYear -= 3;
	else
		throw ASIException("StatSummaryBuilder::"
			"getSeasonDateRangeForStatPeriod: unkown statPeriod");

	fromDate = TDateTime((ushort)firstStatYear,(ushort)firstStatMonth,
		(ushort)firstStatDay);
	toDate = TDateTime((ushort)(firstStatYear + 1),(ushort)firstStatMonth,
		(ushort)firstStatDay);
	toDate -= 1.0;	// One day prior.
}

/******************************************************************************/

void StatSummaryBuilder::getDateRangeForStatPeriodAsOfDate(
	const TStatPeriod statPeriod,const TDateTime asOfDate,TDateTime& fromDate,
	TDateTime& toDate)
{
	if(statPeriod == stp_LastTwoWeeks)
	{
		fromDate = asOfDate - 13;
		toDate = asOfDate;
	}
	else if(statPeriod == stp_LastFourWeeks)
	{
		fromDate = asOfDate - 27;
		toDate = asOfDate;
	}
	else if(statPeriod == stp_LastEightWeeks)
	{
		fromDate = asOfDate - 55;
		toDate = asOfDate;
	}
	else	// season length stat period
		getSeasonDateRangeForStatPeriod(statPeriod,fromDate,toDate);
}

/******************************************************************************/

void StatSummaryBuilder::sumPlayerIDVectorForStatPeriodDateRange(
	const TPlayerIDVector& playerIDVector,const TStatPeriod statPeriod,
	const TDateTime fromDate,const TDateTime toDate)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TPlayerIDVector::const_iterator iter;
	TPlayerID playerID;
	TProfPlayerPtr profPlayerPtr;

	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		playerID = *iter;
		profPlayerPtr = store.getProfPlayer(playerID);
		
		sumOffStatsForProfPlayerDateRange(profPlayerPtr,statPeriod,
			fromDate,toDate);
		sumDefStatsForProfPlayerDateRange(profPlayerPtr,statPeriod,
			fromDate,toDate);
	}
}

/******************************************************************************/

void StatSummaryBuilder::sumOffStatsForProfPlayerStatPeriod(
	const TPlayerID playerID,const TStatPeriod statPeriod,
	const TOffGameStatVector& offGameStatVector)
{
	TOffGameStatVector::const_iterator iter;
	TOffGameStatPtr sumOffGameStatPtr;

	if(offGameStatVector.size() > 0)
	{
		sumOffGameStatPtr = TOffGameStat::newInstance();
		sumOffGameStatPtr->setPlayerID(playerID);
		sumOffGameStatPtr->setStatPeriod(statPeriod);

		for(iter = offGameStatVector.begin(); iter != offGameStatVector.end(); ++iter)
			sumOffGameStatPtr->sumStats(*iter);

		sumOffGameStatPtr->update();
	}
}

/******************************************************************************/

void StatSummaryBuilder::sumOffStatsForProfPlayerDateRange(
	const TProfPlayerPtr profPlayerPtr,const TStatPeriod statPeriod,
	const TDateTime fromDate,const TDateTime toDate)
{
#if 1	//BOB
	TOffGameStatVector offGameStatVector;

	LoadOffGameStatVectorByPlayerIDDateRange(profPlayerPtr->getPlayerID(),
		fromDate,toDate,offGameStatVector);
	sumOffStatsForProfPlayerStatPeriod(profPlayerPtr->getPlayerID(),statPeriod,
		offGameStatVector);
#else	//BOB
	TOffGameStatVector offGameStatVector;
	TOffGameStatVector::iterator iter;
	TOffGameStatPtr sumOffGameStatPtr;

	LoadOffGameStatVectorByPlayerIDDateRange(profPlayerPtr->getPlayerID(),
		fromDate,toDate,offGameStatVector);

	if(offGameStatVector.size() > 0)
	{
		sumOffGameStatPtr = TOffGameStat::newInstance();
		sumOffGameStatPtr->setPlayerID(profPlayerPtr->getPlayerID());
		sumOffGameStatPtr->setStatPeriod(statPeriod);

		for(iter = offGameStatVector.begin(); iter != offGameStatVector.end(); ++iter)
			sumOffGameStatPtr->sumStats(*iter);

		sumOffGameStatPtr->update();
	}
#endif	//BOB
}

/******************************************************************************/

void StatSummaryBuilder::sumDefStatsForProfPlayerStatPeriod(
	const TPlayerID playerID,const TStatPeriod statPeriod,
	const TDefGameStatVector& defGameStatVector)
{
	TDefGameStatVector::const_iterator iter;
	TDefGameStatPtr sumDefGameStatPtr;

	if(defGameStatVector.size() > 0)
	{
		sumDefGameStatPtr = TDefGameStat::newInstance();
		sumDefGameStatPtr->setPlayerID(playerID);
		sumDefGameStatPtr->setStatPeriod(statPeriod);

		for(iter = defGameStatVector.begin(); iter != defGameStatVector.end(); ++iter)
			sumDefGameStatPtr->sumStats(*iter);

		sumDefGameStatPtr->update();
	}
}

/******************************************************************************/

void StatSummaryBuilder::sumDefStatsForProfPlayerDateRange(
	const TProfPlayerPtr profPlayerPtr,const TStatPeriod statPeriod,
	const TDateTime fromDate,const TDateTime toDate)
{
#if 1	//BOB
	TDefGameStatVector defGameStatVector;

	LoadDefGameStatVectorByPlayerIDDateRange(profPlayerPtr->getPlayerID(),
		fromDate,toDate,defGameStatVector);
	sumDefStatsForProfPlayerStatPeriod(profPlayerPtr->getPlayerID(),statPeriod,
		defGameStatVector);
#else	//BOB
	TDefGameStatVector defGameStatVector;
	TDefGameStatVector::iterator iter;
	TDefGameStatPtr sumDefGameStatPtr;

	LoadDefGameStatVectorByPlayerIDDateRange(profPlayerPtr->getPlayerID(),
		fromDate,toDate,defGameStatVector);

	if(defGameStatVector.size() > 0)
	{
		sumDefGameStatPtr = TDefGameStat::newInstance();
		sumDefGameStatPtr->setPlayerID(profPlayerPtr->getPlayerID());
		sumDefGameStatPtr->setStatPeriod(statPeriod);

		for(iter = defGameStatVector.begin(); iter != defGameStatVector.end(); ++iter)
			sumDefGameStatPtr->sumStats(*iter);

		sumDefGameStatPtr->update();
	}
#endif
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/




