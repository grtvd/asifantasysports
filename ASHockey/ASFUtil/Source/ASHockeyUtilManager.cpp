/* ASHockeyUtilManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"

#include "ASHockeyStatFileLoader.h"
#include "ASHockeyStatSummaryBuilder.h"
#include "ASHockeyDraftRanking.h"

#include "ASHockeyUtilManager.h"

namespace ashockey
{

/******************************************************************************/

/* Choices */
const int chc_LoadOffensiveStats			= 1;
const int chc_LoadDefensiveStats			= 2;
const int chc_CalculateSummaryStats			= 3;
const int chc_CreateDefaultDraftRanking		= 4;
const int chc_ResetTeamDraftRanking			= 5;
const int chc_CreateCompAccounts			= 6;
const int chc_AddParticToLeague				= 7;

/* Comp Account Info */
static CompAccountInfo gCompAccountInfo[] = 
{
	// Email	Manager,		Region			Team
	{ NULL,		"Ruff",			"Buffalo",		"Sabres" },
	{ NULL,		"Hitchcock",	"Dallas",		"Stars" },
	{ NULL,		"Quinn",		"Toronto",		"Maple Leafs" },
	{ NULL,		"Hartley",		"Colorado",		"Avalanche" },
	{ NULL,		"Constantine",	"Pittsburgh",	"Penguins" },
	{ NULL,		"Burns",		"Boston",		"Bruins" },
	{ NULL,		"Quenneville",	"St. Louis",	"Blues" },
	{ NULL,		"Bowman",		"Detroit",		"Red Wings" },
	{ NULL,		"Neilson",		"Philadelphia",	"Flyers" },
	{ NULL,		"Lowe",			"Edmonton",		"Oilers" },
};

/******************************************************************************/
/******************************************************************************/

void ASHockeyUtilManager::promptChoices()
{
	printf("1. Load Offensive Stats\n");
	printf("2. Load Defensive Stats\n");
	printf("3. Calculate Season Summary Stats\n");
	printf("4. Create Default Draft Ranking\n");
	printf("5. Reset Team Draft Ranking\n");
	printf("6. Create Comp Accounts\n");
	printf("7. Add Partic To League\n");
}

/******************************************************************************/

bool ASHockeyUtilManager::doesChoiceNeedTransaction(int choice)
{
	if(choice == chc_CreateCompAccounts)
		return(false);

	return(ASFantasyUtilManager::doesChoiceNeedTransaction(choice));
}

/******************************************************************************/

void ASHockeyUtilManager::doChoice(int choice)
{
	if(choice == chc_LoadOffensiveStats)
	{
		TStatPeriod statPeriod = promptStatPeriod();
		bool addNewPlayers = promptYesNo("Should unknown players be added (Y/N)?");

		StatFileLoaderPtr loader =
			OffGameStatFileLoader::newInstance(DirSpec(),TDateTime(),
			statPeriod,addNewPlayers);

		loadStat(loader);
	}
	else if(choice == chc_LoadDefensiveStats)
	{
		TStatPeriod statPeriod = promptStatPeriod();
		bool addNewPlayers = promptYesNo("Should unknown players be added (Y/N)?");

		StatFileLoaderPtr loader =
			DefGameStatFileLoader::newInstance(DirSpec(),TDateTime(),
			statPeriod,addNewPlayers);

		loadStat(loader);
	}
	else if(choice == chc_CalculateSummaryStats)
	{
		ASHockeyStatSummaryBuilder builder;
		TStatPeriod statPeriod = promptStatPeriod();
		
		if(statPeriod == stp_SeasonToDate)
		{
			tag::TDate tAsOfDate = promptDate("Enter 'as of' date (m/d/y): ");

			builder.standAloneBuildAllPlayersForThisSeason(
				ConvertTDatetoTDateTime(tAsOfDate));
		}
		else
			builder.standAloneBuildAllPlayersForStatPeriod(statPeriod);
	}
	else if(choice == chc_CreateDefaultDraftRanking)
	{
		ASHockeyDraftRankingBuilder builder;

		builder.build();
	}
	else if(choice == chc_ResetTeamDraftRanking)
	{
		long tempLong = promptInteger("Enter TeamID of Draft Ranking to Reset (0=cancel): ");

		if(tempLong != 0)
			ASFantasyDraftRankingReseter::reset(tempLong);
	}
	else if(choice == chc_CreateCompAccounts)
	{
		createCompAccounts();
	}
	else if(choice == chc_AddParticToLeague)
	{
		addParticToLeague();
	}
	else
		printf("Invalid Entry!\n");
}

/******************************************************************************/

int ASHockeyUtilManager::getNumCompAccountInfo()
{
	return(sizeof(gCompAccountInfo) / sizeof(*gCompAccountInfo));
}

/******************************************************************************/

const CompAccountInfo* ASHockeyUtilManager::getCompAccountInfo(int offset)
{
	return(&gCompAccountInfo[offset]);
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
