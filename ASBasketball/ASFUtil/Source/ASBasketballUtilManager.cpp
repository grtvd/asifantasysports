/* ASBasketballUtilManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"

#include "ASBasketballStatFileLoader.h"
#include "ASBasketballStatSummaryBuilder.h"
#include "ASBasketballDraftRanking.h"

#include "ASBasketballUtilManager.h"

namespace asbasketball
{

/******************************************************************************/

/* Choices */
const int chc_LoadOffensiveStats			= 1;
const int chc_CalculateSummaryStats			= 2;
const int chc_CreateDefaultDraftRanking		= 3;
const int chc_ResetTeamDraftRanking			= 4;
const int chc_CreateCompAccounts			= 5;
const int chc_AddParticToLeague				= 6;

/* Comp Account Info */
static CompAccountInfo gCompAccountInfo[] = 
{
	// Email	Manager,		Region			Team
	{ NULL,		"Popovich",		"San Antonio",	"Spurs" },
	{ NULL,		"Van Gundy",	"New York",		"Knicks" },
	{ NULL,		"Bird",			"Indiana",		"Pacers" },
	{ NULL,		"Dunleavy",		"Portland",		"Trail Blazers" },
	{ NULL,		"Brown",		"Philadelphia",	"76ers" },
	{ NULL,		"Jackson",		"Los Angeles",	"Lakers" },
	{ NULL,		"Wilkens",		"Altanta",		"Hawks" },
	{ NULL,		"Sloan",		"Utah",			"Jazz" },
	{ NULL,		"Riley",		"Miami",		"Heat" },
	{ NULL,		"Rivers",		"Orlando",		"Magic" },
};

/******************************************************************************/
/******************************************************************************/

void ASBasketballUtilManager::promptChoices()
{
	printf("1. Load Offensive Stats\n");
	printf("2. Calculate Season Summary Stats\n");
	printf("3. Create Default Draft Ranking\n");
	printf("4. Reset Team Draft Ranking\n");
	printf("5. Create Comp Accounts\n");
	printf("6. Add Partic To League\n");
}

/******************************************************************************/

bool ASBasketballUtilManager::doesChoiceNeedTransaction(int choice)
{
	if(choice == chc_CreateCompAccounts)
		return(false);

	return(ASFantasyUtilManager::doesChoiceNeedTransaction(choice));
}

/******************************************************************************/

void ASBasketballUtilManager::doChoice(int choice)
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
	else if(choice == chc_CalculateSummaryStats)
	{
		ASBasketballStatSummaryBuilder builder;
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
		ASBasketballDraftRankingBuilder builder;

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

int ASBasketballUtilManager::getNumCompAccountInfo()
{
	return(sizeof(gCompAccountInfo) / sizeof(*gCompAccountInfo));
}

/******************************************************************************/

const CompAccountInfo* ASBasketballUtilManager::getCompAccountInfo(int offset)
{
	return(&gCompAccountInfo[offset]);
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
