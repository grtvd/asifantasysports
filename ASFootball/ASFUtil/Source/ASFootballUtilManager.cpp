/* ASFootballUtilManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"

#include "ASFootballStatFileLoader.h"
#include "ASFootballStatSummaryBuilder.h"
#include "ASFootballDraftRanking.h"

#include "ASFootballUtilManager.h"

namespace asfootball
{

/******************************************************************************/

/* Choices */
const int chc_LoadPlayerInfoStat			= 1;
const int chc_LoadOffensiveStats			= 2;
const int chc_LoadDefensiveStats			= 3;
const int chc_CalculateSummaryStats			= 4;
const int chc_CreateDefaultDraftRanking		= 5;
const int chc_ResetTeamDraftRanking			= 6;
const int chc_CreateCompAccounts			= 7;
const int chc_AddParticToLeague				= 8;

/* Comp Account Info */
static CompAccountInfo gCompAccountInfo[] = 
{
	// Email	Manager,		Region			Team
	{ NULL,		"Owen",			"Boston",		"Yanks" },
	{ NULL,		"Lombardi",		"Decatur",		"Staleys" },
	{ NULL,		"Brown",		"Cleveland",	"Bulldogs" },
	{ NULL,		"Flaherty",		"Brooklyn",		"Dodgers" },
	{ NULL,		"Kiesling",		"Chicago",		"Cardinals" },
	{ NULL,		"Halas",		"Houston",		"Oilers" },
	{ NULL,		"Lambeau",		"Portsmouth",	"Spartans" },
	{ NULL,		"Neale",		"Dallas",		"Texans" },
	{ NULL,		"Johnson",		"Baltimore",	"Colts" },
	{ NULL,		"Walsh",		"Pittsburgh",	"Pirates" },
};

/******************************************************************************/
/******************************************************************************/

void ASFootballUtilManager::promptChoices()
{
	printf("1. Load Player Info Status\n");
	printf("2. Load Offensive Stats\n");
	printf("3. Load Defensive Stats\n");
	printf("4. Calculate Season Summary Stats\n");
	printf("5. Create Default Draft Ranking\n");
	printf("6. Reset Team Draft Ranking\n");
	printf("7. Create Comp Accounts\n");
	printf("8. Add Partic To League\n");
}

/******************************************************************************/

bool ASFootballUtilManager::doesChoiceNeedTransaction(int choice)
{
	if(choice == chc_CreateCompAccounts)
		return(false);

	return(ASFantasyUtilManager::doesChoiceNeedTransaction(choice));
}

/******************************************************************************/

void ASFootballUtilManager::doChoice(int choice)
{
	if(choice == chc_LoadPlayerInfoStat)
	{
		DirSpec dirspec;
		TDateTime dateTime;
		StatFileLoaderPtr loader =
			PlayerInfoStatFileLoader::newInstance(dirspec,dateTime);
		
		loadStat(loader);
	}
	else if(choice == chc_LoadOffensiveStats)
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
		bool skipUnknownPlayers = !promptYesNo("Should unknown teams cause an error (Y/N)?");

		StatFileLoaderPtr loader =
			DefGameStatFileLoader::newInstance(DirSpec(),TDateTime(),
			statPeriod,skipUnknownPlayers);

		loadStat(loader);
	}
	else if(choice == chc_CalculateSummaryStats)
	{
		ASFootballStatSummaryBuilder builder;
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
		ASFootballDraftRankingBuilder builder;

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

int ASFootballUtilManager::getNumCompAccountInfo()
{
	return(sizeof(gCompAccountInfo) / sizeof(*gCompAccountInfo));
}

/******************************************************************************/

const CompAccountInfo* ASFootballUtilManager::getCompAccountInfo(int offset)
{
	return(&gCompAccountInfo[offset]);
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
