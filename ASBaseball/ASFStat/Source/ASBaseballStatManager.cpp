/* ASBaseballStatManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "CommDB.h"

#include "ASFantasyObjectStore.h"

#include "ASBaseballAppOptions.h"

#include "ASBaseballStatFileLoader.h"
#include "ASBaseballStatSummaryBuilder.h"
#include "ASBaseballDraftRanking.h"

#include "ASBaseballStatManager.h"

using namespace tag;
using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

/* Choices */
const int chc_ClearLastWeeksPoints			= 1;
const int chc_LoadPlayerRoster				= 2;
const int chc_LoadBattingStats				= 3;
const int chc_LoadPitchingStats				= 4;
const int chc_LoadInjuryFile				= 5;
const int chc_LoadTransactionFile			= 6;
const int chc_CalculateSummaryStats			= 7;
const int chc_CreateDefaultDraftRanking		= 8;
const int chc_ResetTeamDraftRanking			= 9;

/******************************************************************************/
/******************************************************************************/

void ASBaseballStatManager::run(void)
{
	TDatabase* db = NULL;  
	TDatabase* memdb = NULL;
	CStrVar errMsg;

	CommErrSetOutputFileName("ASBbStat.out");
	CommErrInit("ASBbStat",ceo_File,cef_Pipe);
	try
	{
		Application->Initialize();
		
		try
		{
			db = OpenDatabase(PrimaryDatabaseName());
			memdb = OpenDatabase(MemberDatabaseName());

			mainLoop();
		}
		catch(...)
		{
			CloseDatabase(memdb);
			CloseDatabase(db);
			throw;
		}
			
		CloseDatabase(memdb);
		CloseDatabase(db);
	}
	catch(Exception& e)
	{
		errMsg.copy("catch: Exception: ");
		errMsg.concat(e.Message.c_str());
	}
	catch(exception& e)
	{
		errMsg.copy("catch: exception: ");
		errMsg.concat(e.what());
	}
	catch(...)
	{
		errMsg.copy("catch: ...");
	}
	
	if(errMsg.hasLen())
	{
		TOOLDEBUG( CommErrMsg(cel_Error,errMsg); )
		printf(errMsg);
		printf("\n");
	}
	TOOLDEBUG( CommErrMsg(cel_Info,"done!"); )
	printf("done!\n");

	CommErrDispose();
}

/******************************************************************************/

void ASBaseballStatManager::mainLoop()
{
	TDatabase* db = NULL;
	TDatabase* memdb = NULL;
	char tempBuffer[256];
	long choice;

	while(TRUE)
	{
		printf("\n\n");
		printf("1. Clear Last Weeks Points\n");
		printf("2. Load Player Roster\n");
		printf("3. Load Batting Stats\n");
		printf("4. Load Pitching Stats\n");
		printf("5. Load Injury File\n");
		printf("6. Load Transaction File\n");
		printf("7. Calculate Season Summary Stats\n");
		printf("8. Create Default Draft Ranking\n");
		printf("9. Reset Team Draft Ranking\n");
		printf("Q. Quit\n");
		printf("\nChoice: ");
		scanf("%s",tempBuffer);

		if(stricmp(tempBuffer,"Q") == 0)
			break;

		if(!StringToNumeric(tempBuffer,&choice))
		{
			printf("Invalid Entry!\n");
			continue;
		}
		
		printf("\n\n");

		db = GetOpenDatabase(PrimaryDatabaseName());
		memdb = GetOpenDatabase(MemberDatabaseName());
		memdb->StartTransaction();
		db->StartTransaction();
		try
		{
			doChoice(choice);

			db->Commit();
			memdb->Commit();
		}
		catch(...)
		{
			db->Rollback();
			memdb->Rollback();
			throw;
		}
	}
}

/******************************************************************************/

void ASBaseballStatManager::doChoice(int choice)
{
	char tempBuffer[256];
	TStatPeriod statPeriod;
	tag::TDate tAsOfDate;
	bool addNewPlayers = false;

	if((choice == chc_LoadBattingStats) ||
		(choice == chc_LoadPitchingStats))
	{
		statPeriod = promptStatPeriod();
		
		while(TRUE)
		{
			printf("Should unknown players be added (Y/N)?");
			scanf("%s",tempBuffer);
			if(stricmp(tempBuffer,"Y") == 0)
				addNewPlayers = true;
			else if(stricmp(tempBuffer,"N") == 0)
				addNewPlayers = false;
			else
			{
				printf("Invalid Entry!\n");
				continue;
			}
			break;
		}
	}

	if(choice == chc_ClearLastWeeksPoints)
	{
		/* BOB
		printf("Should last week's points be cleared (Y/N)?: ");
		scanf("%s",tempBuffer);
		if(stricmp(tempBuffer,"Y") == 0)
			ClearLastWeeksPointsForAllProfPlayers();
		BOB */
	}
	else if(choice == chc_LoadPlayerRoster)
	{
		DirSpec dirspec;
		TDateTime dateTime;
		StatFileLoaderPtr loader =
			PlayerRosterFileLoader::newInstance(dirspec,dateTime);
		
		loadStat(loader);
	}
	else if(choice == chc_LoadBattingStats)
	{
		StatFileLoaderPtr loader =
			OffGameStatFileLoader::newInstance(DirSpec(),TDateTime(),
			statPeriod,addNewPlayers);

		loadStat(loader);
	}
	else if(choice == chc_LoadPitchingStats)
	{
		StatFileLoaderPtr loader =
			DefGameStatFileLoader::newInstance(DirSpec(),TDateTime(),
			statPeriod,addNewPlayers);

		loadStat(loader);
	}
	else if(choice == chc_LoadInjuryFile)
	{
		StatFileLoaderPtr loader = 
			InjuryFileLoader::newInstance(DirSpec(),TDateTime());

		loadStat(loader);
	}
	else if(choice == chc_LoadTransactionFile)
	{
		StatFileLoaderPtr loader = 
			TransactionFileLoader::newInstance(DirSpec(),TDateTime());

		loadStat(loader);
	}
	else if(choice == chc_CalculateSummaryStats)
	{
		ASBaseballStatSummaryBuilder builder;
		statPeriod = promptStatPeriod();
		
		if(statPeriod == stp_SeasonToDate)
		{
			printf("Enter 'as of' date (m/d/y): ");
			scanf("%s",tempBuffer);
			if(!StringToDate(tempBuffer,DF_MM_DD_YY,&tAsOfDate))
				throw ASIException("bad date");

			builder.standAloneBuildAllPlayersForThisSeason(
				ConvertTDatetoTDateTime(tAsOfDate));
		}
		else
			builder.standAloneBuildAllPlayersForStatPeriod(statPeriod);
	}
	else if(choice == chc_CreateDefaultDraftRanking)
	{
		ASBaseballDraftRankingBuilder builder;

		builder.build();
	}
	else if(choice == chc_ResetTeamDraftRanking)
	{
		long tempLong;

		printf("Enter TeamID of Draft Ranking to Reset (0=cancel): ");
		scanf("%s",tempBuffer);
		if(StringToNumeric(tempBuffer,&tempLong))
		{
			if(tempLong != 0)
				ASFantasyDraftRankingReseter::reset(tempLong);
		}
		else
			printf("Invalid Entry!\n");
	}
	else
		printf("Invalid Entry!\n");
}

/******************************************************************************/

TStatPeriod ASBaseballStatManager::promptStatPeriod()
{
	char tempBuffer[256];
	long tempLong;
	TStatPeriod statPeriod;

	while(TRUE)
	{
		printf("What is the stat period?\n");
		printf("(1) Season Game\n");
		printf("(2) Season-To-Date\n");
		printf("(3) Last Season\n");
		printf("(4) Two Seasons Ago\n");
		printf("(5) Three Seasons Ago\n");
		printf("\nWhich: ");
		scanf("%s",tempBuffer);
		if(!StringToNumeric(tempBuffer,&tempLong) ||
			((tempLong < 1) || (tempLong > 5)))
		{
			printf("Invalid Entry!\n");
			continue;
		}
		if(tempLong == 1)
			statPeriod = stp_SeasonGame;
		else if(tempLong == 2)
			statPeriod = stp_SeasonToDate;
		else if(tempLong == 3)
			statPeriod = stp_LastSeason;
		else if(tempLong == 4)
			statPeriod = stp_TwoSeasonsAgo;
		else //if(tempLong == 5)
			statPeriod = stp_ThreeSeasonsAgo;
		break;
	}

	return(statPeriod);
}

/******************************************************************************/

void ASBaseballStatManager::loadStat(StatFileLoaderPtr loader)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	DirSpec dirSpec;
	char tempBuffer[256];
	tag::TDate tFromDate,tToDate,tDate = 0;
	CStrVar errMsg;
	
	try
	{
		store.addProfPlayerShelf();
		store.addProfTeamShelf();

		store.loadAllProfPlayers();
		store.loadAllProfTeams();

		printf("Enter starting date of stat files to load (m/d/y): ");
		scanf("%s",tempBuffer);
		if(!StringToDate(tempBuffer,DF_MM_DD_YY,&tFromDate))
			throw ASIException("bad date");

		printf("Enter ending date of stat files to load (m/d/y): ");
		scanf("%s",tempBuffer);
		if(!StringToDate(tempBuffer,DF_MM_DD_YY,&tToDate))
			throw ASIException("bad date");
		
		dirSpec.SetFromParent(ASBaseballHomeDir(),"Stats");
		loader->setDirSpec(dirSpec);

		for(tDate = tFromDate; tDate <= tToDate; tDate++)
		{	
			loader->setFileNameDate(ConvertTDatetoTDateTime(tDate));

			DateToString(tDate,tempBuffer,DF_MM_DD_YYYY,0);
			if(!loader->doesFileExist())
			{
				printf("No stats for %s...\n",tempBuffer);
				continue;
			}
				
			printf("Loading stats for %s...\n",tempBuffer);
				
			errMsg = NULL;
			try
			{			
				loader->load();
			}
			catch(Exception& e)
			{
				errMsg.copy("catch: Exception: ");
				errMsg.concat(e.Message.c_str());
			}
			catch(exception& e)
			{
				errMsg.copy("catch: exception: ");
				errMsg.concat(e.what());
			}
			catch(...)
			{
				errMsg.copy("catch: ...");
			}

			if(errMsg.hasLen())
			{
				CommErrMsg(cel_Error,errMsg);
				printf("%s\n",errMsg.c_str());
			
				CommErrMsg(cel_Error,"catch: Exception: failed loading "
					"stats for day %s",tempBuffer);
				printf("catch: Exception: failed loading stats for day "
					"%s",tempBuffer);
			}
		}
			
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

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
