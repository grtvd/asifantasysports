/* ASFantasyUtilManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "CommDB.h"
#include "CommErr.h"

#include "ASFantasyObjectStore.h"
#include "ASFantasyNewMemberSignupRqst.h"
#include "ASFantasyLeagueSignupRqst.h"
#include "ASFantasyUtilManager.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyUtilManager::main(const DirSpec& homeDir,const char* appName)
{
	TDatabase* db = NULL;  
	TDatabase* memdb = NULL;
	TDatabase* miscdb = NULL;
	CStrVar errMsg;

	CommErrSetOutputFileName(BuildFullFileName(homeDir,
		CStrVar::build("%s.out",appName)));
	CommErrInit(appName,ceo_File,cef_Pipe);
	try
	{
		fHomeDir = homeDir;
		
		try
		{
			db = OpenDatabase(PrimaryDatabaseName());
			memdb = OpenDatabase(MemberDatabaseName());
			miscdb = OpenDatabase(MemberMiscDatabaseName());

			mainLoop();
		}
		catch(const Exception& e)
		{
			CloseDatabase(miscdb);
			CloseDatabase(memdb);
			CloseDatabase(db);
			throw ASIException(e.Message.c_str());
		}
		catch(...)
		{
			CloseDatabase(miscdb);
			CloseDatabase(memdb);
			CloseDatabase(db);
			throw;
		}
			
		CloseDatabase(miscdb);
		CloseDatabase(memdb);
		CloseDatabase(db);
	}
	catch(const Exception& e)
	{
		errMsg.copy("catch: Exception: ");
		errMsg.concat(e.Message.c_str());
	}
	catch(const ASIException& e)
	{
		errMsg.copy("catch: ASIException: ");
		errMsg.concat(e.getMsg());
	}
	catch(const exception& e)
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
		printf(errMsg);
		printf("\n");
	}
	CommErrMsg(cel_Info,"done!");
	printf("done!\n");

	CommErrDispose();
}

/******************************************************************************/

void ASFantasyUtilManager::mainLoop()
{
	TDatabase* db = NULL;
	TDatabase* memdb = NULL;
	TDatabase* miscdb = NULL;
	char tempBuffer[256];
	long choice;

	while(TRUE)
	{
		printf("\n\n");
		promptChoices();
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

		if(doesChoiceNeedTransaction(choice))
		{
			db = GetOpenDatabase(PrimaryDatabaseName());
			memdb = GetOpenDatabase(MemberDatabaseName());
			miscdb = GetOpenDatabase(MemberMiscDatabaseName());
			miscdb->StartTransaction();
			memdb->StartTransaction();
			db->StartTransaction();
			try
			{
				doChoice(choice);

				db->Commit();
				memdb->Commit();
				miscdb->Commit();
			}
			catch(const Exception& e)
			{
				db->Rollback();
				memdb->Rollback();
				miscdb->Rollback();
				throw ASIException(e.Message.c_str());
			}
			catch(...)
			{
				db->Rollback();
				memdb->Rollback();
				miscdb->Rollback();
				throw;
			}
		}
		else
			doChoice(choice);
	}
}

/******************************************************************************/

CStrVar ASFantasyUtilManager::promptString(const char* prompt)
{
	char tempBuffer[256];

	printf(prompt);
	scanf("%s",tempBuffer);

	return(CStrVar(tempBuffer));
}

/******************************************************************************/

int ASFantasyUtilManager::promptInteger(const char* prompt)
{
	char tempBuffer[256];
	long result;

	while(TRUE)
	{
		printf(prompt);
		scanf("%s",tempBuffer);
		if(!StringToNumeric(tempBuffer,&result))
		{
			printf("Invalid Entry!\n");
			continue;
		}
		break;
	}

	return((int)result);
}

/******************************************************************************/

tag::TDate ASFantasyUtilManager::promptDate(const char* prompt)
{
	char tempBuffer[256];
	tag::TDate tDate;

	while(TRUE)
	{
		printf(prompt);
		scanf("%s",tempBuffer);
		if(!StringToDate(tempBuffer,DF_MM_DD_YY,&tDate))
		{
			printf("Invalid Entry!\n");
			continue;
		}
		break;
	}

	return(tDate);
}

/******************************************************************************/

bool ASFantasyUtilManager::promptYesNo(const char* prompt)
{
	char tempBuffer[256];
	bool result;

	while(TRUE)
	{
		printf(prompt);
		scanf("%s",tempBuffer);
		if(stricmp(tempBuffer,"Y") == 0)
			result = true;
		else if(stricmp(tempBuffer,"N") == 0)
			result = false;
		else
		{
			printf("Invalid Entry!\n");
			continue;
		}
		break;
	}

	return(result);
}

/******************************************************************************/

TEncodedParticID ASFantasyUtilManager::promptEncodedParticID()
{
	TMemberID memberID;
	TParticID particID;
	TParticPtr particPtr;

	while(TRUE)
	{
		memberID = promptString("Enter User Name: ").c_str();
		memberID.ToUpper();
		particID = promptInteger("Enter ParticID: ");

		particPtr = TPartic::createGet(particID,cam_MayNotExist);

		if(particPtr.isNull() || (particPtr->getMemberID() != memberID))
		{
			printf("Invalid Partic!\n");
			continue;
		}
		
		return(particPtr->encodeParticID());
	}
}

/******************************************************************************/

TStatPeriod ASFantasyUtilManager::promptStatPeriod()
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
/******************************************************************************/

void ASFantasyUtilManager::createCompAccounts()
{
	int numAccounts;

	numAccounts = promptInteger("How many accounts should be created: ");
	if(numAccounts < 1)
		return;

	if(promptYesNo("Should default Team Names be used (Y/N)? "))
		fNumCompAccountInfo = getNumCompAccountInfo();
	else
		fNumCompAccountInfo = 0;
	fCompAccountInfoOffset = 0;

	for(int i = 0; i < numAccounts; ++i)
	{
		createOneCompAccount();
		incCompAccountInfoOffset();
	}
}

/******************************************************************************/

void ASFantasyUtilManager::createOneCompAccount()
{
	ASFantasyNewMemberSignupRqst request;
	auto_ptr<ASFantasyNewSignupResp> newSignupResp;
	CStrVar tempStr;

	request.setSignupSource("Affinity");

	request.setMemberID(promptString("Enter User Name: ").c_str());
	tempStr = promptString("Enter Password: ");
	request.setPassword(tempStr);
	request.setReEnteredPassword(tempStr);

	request.setGameLevel(gml_Premium);
	request.setGamePrice(0.0);

	request.getName().fFirstName = "Complimentary";
	request.getName().fLastName = "Account";

	request.setAddrStreet1("n/a");
	request.setAddrStreet2("");
	request.setAddrCity("n/a");
	request.setAddrState("n/a");
	request.setAddrZip("n/a");
	
	request.setAddrCountry("n/a");
	request.setEmail(getCompAccountEmail());

	request.setManagerName(getCompAccountManagerName());
	request.setRegionName(getCompAccountRegionName());
	request.setTeamName(getCompAccountTeamName());

	request.setCCardViaFaxPhone(TBooleanType(true).c_str());

	newSignupResp.reset(request.fulfillRequest());
	if(newSignupResp->getSuccess())
		printf("Success.\n");
	else
		printf("Failed, Reason: %s\n",newSignupResp->getReasonFailed());
}

/******************************************************************************/

void ASFantasyUtilManager::incCompAccountInfoOffset()
{
	if(++fCompAccountInfoOffset >= fNumCompAccountInfo)
		fCompAccountInfoOffset = 0;
}

/******************************************************************************/

CStrVar ASFantasyUtilManager::getCompAccountEmail()
{
	const CompAccountInfo* compAccountInfo;

	if((fNumCompAccountInfo > 0) && ((compAccountInfo =
		getCompAccountInfo(fCompAccountInfoOffset)) != NULL))
	{
		if(compAccountInfo->fEmail != NULL)
			return(compAccountInfo->fEmail);

		return(TechSupportEmail());
	}

	return(promptString("Enter Email: "));
}

/******************************************************************************/

CStrVar ASFantasyUtilManager::getCompAccountManagerName()
{
	const CompAccountInfo* compAccountInfo;

	if((fNumCompAccountInfo > 0) && ((compAccountInfo =
			getCompAccountInfo(fCompAccountInfoOffset)) != NULL))
		return(compAccountInfo->fManagerName);

	return(promptString("Enter Manager Name: "));
}

/******************************************************************************/

CStrVar ASFantasyUtilManager::getCompAccountRegionName()
{
	const CompAccountInfo* compAccountInfo;

	if((fNumCompAccountInfo > 0) && ((compAccountInfo =
			getCompAccountInfo(fCompAccountInfoOffset)) != NULL))
		return(compAccountInfo->fRegionName);

	return(promptString("Enter Region Name: "));
}

/******************************************************************************/

CStrVar ASFantasyUtilManager::getCompAccountTeamName()
{
	const CompAccountInfo* compAccountInfo;

	if((fNumCompAccountInfo > 0) && ((compAccountInfo =
			getCompAccountInfo(fCompAccountInfoOffset)) != NULL))
		return(compAccountInfo->fTeamName);

	return(promptString("Enter Team Name: "));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyUtilManager::addParticToLeague()
{
	LeagueSignupRqst request;
	auto_ptr<LeagueSignupResp> response;
	CStrVar tempStr;
	int tempInt;

	printf("1. Join League\n");
	printf("2. Create League\n");
	tempInt = promptInteger("Which: ");
	if(tempInt == 1)
	{
		request.setEncodedParticID(promptEncodedParticID());
		if((tempInt = promptInteger("Enter LeagueID (0 = next available): ")) != 0)
		{
			request.setLeagueSignupType(lst_JoinPrivate);
			request.setLeagueID(tempInt);

			tempStr = promptString("Enter League Password (x = none): ");
			if(stricmp(tempStr,"x") != 0)
				request.setLeaguePassword(tempStr);
		}
		else
			request.setLeagueSignupType(lst_JoinOpenPublic);
	}
	else if(tempInt == 2)
	{
		request.setLeagueSignupType(lst_CreatePrivate);
		request.setEncodedParticID(promptEncodedParticID());
		request.setLeaguePassword(promptString("Enter League Password: "));
	}
	else
	{
		printf("Invalid Entry!\n");
		return;
	}
	
	response.reset(&dynamic_cast<LeagueSignupResp&>(*request.fulfillRequest()));
	if(response->getSuccess())
		printf("Successfully added to the %s League.\n",
			response->getLeagueName());
	else
		printf("Failed, Reason: %s\n",response->getReasonFailed());
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyUtilManager::loadStat(StatFileLoaderPtr loader)
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

		tFromDate = promptDate("Enter starting date of stat files to load (m/d/y): ");
		tToDate = promptDate("Enter ending date of stat files to load (m/d/y): ");

		dirSpec.SetFromParent(fHomeDir,"Stats");
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
			catch(const Exception& e)
			{
				errMsg.copy("catch: Exception: ");
				errMsg.concat(e.Message.c_str());
			}
			catch(const ASIException& e)
			{
				errMsg.copy("catch: ASIException: ");
				errMsg.concat(e.getMsg());
			}
			catch(const exception& e)
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

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
