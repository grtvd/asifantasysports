/* ASFantasyEngine.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "CommDB.h"
#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyEngine.h"

#include "ASFantasyCreateDraftOrder.h"
#include "ASFantasyDraftResolver.h"

namespace asfantasy
{

/******************************************************************************/

#define WaitTimeForProcessTenths()		(300)	// Tenths to wait while waiting for other processes
#define EmailUpcomingDraftDaysBefore()	(4)		// Number of days prior to draft to send email reminder

/******************************************************************************/
/******************************************************************************/

class LeagueStandingsSorter
{
protected:
	class PrimarySortCompare
	{
	protected:
		TLeaguePtr& fLeaguePtr;
		const TScheduleDayVector& fScheduleDayVector;
		
	public:
		PrimarySortCompare(TLeaguePtr& leaguePtr,
			const TScheduleDayVector& scheduleDayVector) : fLeaguePtr(leaguePtr),
			fScheduleDayVector(scheduleDayVector) {}
			
		bool operator()(const TTeamPtr& x, const TTeamPtr& y) const;
	};

	class TiedSortCompare
	{
	protected:
		TLeaguePtr& fLeaguePtr;
		const TScheduleDayVector& fScheduleDayVector;
		
	public:
		TiedSortCompare(TLeaguePtr& leaguePtr,
			const TScheduleDayVector& scheduleDayVector) : fLeaguePtr(leaguePtr),
			fScheduleDayVector(scheduleDayVector) {}
			
		bool operator()(const TTeamPtr& x, const TTeamPtr& y) const;
	};

public:
	static void sort(TLeaguePtr& leaguePtr,
		const TScheduleDayVector& scheduleDayVector,TTeamVector& teamVector);
};

/******************************************************************************/
/******************************************************************************/

bool LeagueStandingsSorter::PrimarySortCompare::operator()(
	const TTeamPtr& teamOnePtr,const TTeamPtr& teamTwoPtr) const
{
	double teamOneWinPerc;
	double teamTwoWinPerc;
	short teamOnePoints;
	short teamTwoPoints;

	// Overall Winning Percentage
	teamOneWinPerc = teamOnePtr->winningPercentage();
	teamTwoWinPerc = teamTwoPtr->winningPercentage();
	
	if(teamOneWinPerc > teamTwoWinPerc)
		return(true);
	if(teamOneWinPerc < teamTwoWinPerc)
		return(false);

		
	// Winning Percentage in head to head competition
	teamOneWinPerc = fScheduleDayVector.getHeadToHeadWinningPercentage(
		teamOnePtr->getTeamID(),teamTwoPtr->getTeamID());
	teamTwoWinPerc = fScheduleDayVector.getHeadToHeadWinningPercentage(
		teamTwoPtr->getTeamID(),teamOnePtr->getTeamID());

	if(teamOneWinPerc > teamTwoWinPerc)
		return(true);
	if(teamOneWinPerc < teamTwoWinPerc)
		return(false);
		
	
	// Total Points in head to head competition
	teamOnePoints = fScheduleDayVector.getHeadToHeadTotalPoints(
		teamOnePtr->getTeamID(),teamTwoPtr->getTeamID());
		
	teamTwoPoints = fScheduleDayVector.getHeadToHeadTotalPoints(
		teamTwoPtr->getTeamID(),teamOnePtr->getTeamID());
		
	if(teamOnePoints > teamTwoPoints)
		return(true);
	if(teamOnePoints < teamTwoPoints)
		return(false);


	// Overall Total Points
	teamOnePoints = teamOnePtr->getTotalPoints();
	teamTwoPoints = teamTwoPtr->getTotalPoints();
	
	if(teamOnePoints > teamTwoPoints)
		return(true);
	if(teamOnePoints < teamTwoPoints)
		return(false);

		
	// Winning Percentage in divisional competition
	teamOneWinPerc = teamOnePtr->divWinningPercentage();
	teamTwoWinPerc = teamTwoPtr->divWinningPercentage();

	if(teamOneWinPerc > teamTwoWinPerc)
		return(true);
	if(teamOneWinPerc < teamTwoWinPerc)
		return(false);


	// Total Points in divisional competition
	teamOnePoints = fScheduleDayVector.getDivTotalPointsForTeam(
		teamOnePtr->getTeamID(),
		fLeaguePtr->getDivTeamIDVector(teamOnePtr->getDivision()));
	teamTwoPoints = fScheduleDayVector.getDivTotalPointsForTeam(
		teamTwoPtr->getTeamID(),
		fLeaguePtr->getDivTeamIDVector(teamTwoPtr->getDivision()));
	
	if(teamOnePoints > teamTwoPoints)
		return(true);
	if(teamOnePoints < teamTwoPoints)
		return(false);

		
	// Reverse Draft Order
	const TTeamIDVector& teamIDVector = fLeaguePtr->round1DraftOrder();
	TTeamIDVector::const_iterator iter;
	TTeamIDVector::difference_type teamOnePos = 0;
	TTeamIDVector::difference_type teamTwoPos = 0;

	if((iter = find(teamIDVector.begin(),teamIDVector.end(),
			teamOnePtr->getTeamID())) != teamIDVector.end())
		distance(teamIDVector.begin(),iter,teamOnePos);

	if((iter = find(teamIDVector.begin(),teamIDVector.end(),
			teamTwoPtr->getTeamID())) != teamIDVector.end())
		distance(teamIDVector.begin(),iter,teamTwoPos);
	
	return(teamOnePos > teamTwoPos);
}

/******************************************************************************/

bool LeagueStandingsSorter::TiedSortCompare::operator()(
	const TTeamPtr& teamOnePtr,const TTeamPtr& teamTwoPtr) const
{
	double teamOneWinPerc;
	double teamTwoWinPerc;
	short teamOnePoints;
	short teamTwoPoints;

	// Overall Total Points
	teamOnePoints = teamOnePtr->getTotalPoints();
	teamTwoPoints = teamTwoPtr->getTotalPoints();
	
	if(teamOnePoints > teamTwoPoints)
		return(true);
	if(teamOnePoints < teamTwoPoints)
		return(false);

		
	// Winning Percentage in divisional competition
	teamOneWinPerc = teamOnePtr->divWinningPercentage();
	teamTwoWinPerc = teamTwoPtr->divWinningPercentage();

	if(teamOneWinPerc > teamTwoWinPerc)
		return(true);
	if(teamOneWinPerc < teamTwoWinPerc)
		return(false);


	// Total Points in divisional competition
	teamOnePoints = fScheduleDayVector.getDivTotalPointsForTeam(
		teamOnePtr->getTeamID(),
		fLeaguePtr->getDivTeamIDVector(teamOnePtr->getDivision()));
	teamTwoPoints = fScheduleDayVector.getDivTotalPointsForTeam(
		teamTwoPtr->getTeamID(),
		fLeaguePtr->getDivTeamIDVector(teamTwoPtr->getDivision()));
	
	if(teamOnePoints > teamTwoPoints)
		return(true);
	if(teamOnePoints < teamTwoPoints)
		return(false);

		
	// Reverse Draft Order
	const TTeamIDVector& teamIDVector = fLeaguePtr->round1DraftOrder();
	TTeamIDVector::const_iterator iter;
	TTeamIDVector::difference_type teamOnePos = 0;
	TTeamIDVector::difference_type teamTwoPos = 0;

	if((iter = find(teamIDVector.begin(),teamIDVector.end(),
			teamOnePtr->getTeamID())) != teamIDVector.end())
		distance(teamIDVector.begin(),iter,teamOnePos);

	if((iter = find(teamIDVector.begin(),teamIDVector.end(),
			teamTwoPtr->getTeamID())) != teamIDVector.end())
		distance(teamIDVector.begin(),iter,teamTwoPos);
	
	return(teamOnePos > teamTwoPos);
}

/******************************************************************************/

void LeagueStandingsSorter::sort(TLeaguePtr& leaguePtr,
	const TScheduleDayVector& scheduleDayVector,TTeamVector& teamVector)
{
	TTeamVector finalTeamVector;
	TTeamVector tiedTeamVector;
	TTeamVector::iterator iterOuter;
	TTeamVector::iterator iterInner;

	// Initial sort using PrimarySortCompare
	std::sort(teamVector.begin(),teamVector.end(),
		PrimarySortCompare(leaguePtr,scheduleDayVector));

	// Secondary sort for 3 or more teams with tied winning percentage
	for(iterOuter = teamVector.begin(); iterOuter != teamVector.end(); /*no inc */)
	{
		TTeamPtr teamOnePtr = *iterOuter;

		tiedTeamVector.push_back(teamOnePtr);
		for(iterInner = iterOuter + 1; iterInner != teamVector.end(); ++iterInner)
		{
			TTeamPtr teamTwoPtr = *iterInner;
			double teamOneWinPerc = teamOnePtr->winningPercentage();
			double teamTwoWinPerc = teamTwoPtr->winningPercentage();

			// Warning: != was not working with return values from winningPercentage()
			if(teamOneWinPerc != teamTwoWinPerc)
				break;

			tiedTeamVector.push_back(teamTwoPtr);
		}

		if(tiedTeamVector.size() > 2)
			std::sort(tiedTeamVector.begin(),tiedTeamVector.end(),
				TiedSortCompare(leaguePtr,scheduleDayVector));

		finalTeamVector.insert(finalTeamVector.end(),tiedTeamVector.begin(),
			tiedTeamVector.end());
		tiedTeamVector.erase(tiedTeamVector.begin(),tiedTeamVector.end());

		iterOuter = iterInner;
	}

	if(finalTeamVector.size() != teamVector.size())
		throw ASIException("LeagueStandingsSorter::sort: finalTeamVector.size() != teamVector.size()");
	teamVector = finalTeamVector;
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::run()
{
	TDatabase* db = NULL;
	TDatabase* memdb = NULL;
	TDatabase* miscdb = NULL;
	CStrVar excepMsg;

	try
	{
		db = OpenDatabase(PrimaryDatabaseName());
		memdb = OpenDatabase(MemberDatabaseName());
		miscdb = OpenDatabase(MemberMiscDatabaseName());

		fNotify.notify(cel_Info,"Startup successful...");
		while(runWithWait())
		{
			if(beginProcessing())
			{
				backupDatabase();
				if(!isRunning())
					continue;

				waitForASMemberBackup();
				if(!isRunning())
					continue;

				fNotify.notify(cel_Info,"Beginning Processing...");
				
				try
				{
					addAllShelves();
					
					loadShelvesForStatLoad();
					processStatFiles();
					unloadShelvesForStatLoad();
					if(!isRunning())
					{
						delAllShelves();
						continue;
					}
					
					loadShelvesForProcessing();
					processAllLeagues();
					delAllShelves();
				}
				catch(const Exception& e)
				{
					delAllShelves();
					throw ASIException(e.Message.c_str());
				}
				catch(...)
				{
					delAllShelves();
					throw;
				}
				
				endProcessing();
				
				fNotify.notify(cel_Error,"Processing Complete...");	// cel_Error so ASManager sends SysOp notification of completion
			}
		}
	}
	catch(const Exception& e)
	{
		excepMsg.copyVarg("ASFantasyEngine::run(): Exception thrown: %s",
			e.Message.c_str());
	}
	catch(const ASIException& e)
	{
		excepMsg.copyVarg("ASFantasyEngine::run(): ASIException thrown: %s",
			e.getMsg());
	}
	catch(const exception& e)
	{
		excepMsg.copyVarg("ASFantasyEngine::run(): exception thrown: %s",
			e.what());
	}
	catch(...)
	{
		excepMsg.copyVarg("ASFantasyEngine::run(): exception thrown: unknown");
	}

	CloseDatabase(miscdb);
	CloseDatabase(memdb);
	CloseDatabase(db);

	if(excepMsg.hasLen())
		fNotify.notify(cel_Error,excepMsg);
	fNotify.notify(cel_Info,"Shutting down...");
}

/******************************************************************************/

void ASFantasyEngine::backupDatabase()
{
	DirSpec homeDir = getHomeDir();
	DirSpec databaseDir;
	DirSpec backupDir;
	TDatabaseTableVector databaseTableVector;

	if(TDateTime::CurrentDate() > LastBackupDate())
	{
		fNotify.notify(cel_Info,"Backing Up Database...");

		if(!databaseDir.SetFromParent(homeDir,"Database"))
			throw ASIException("ASFantasyEngine::backupDatabase: databaseDir.SetFromParent() failed");
		if(!backupDir.SetFromParent(databaseDir,"Backup"))
			throw ASIException("ASFantasyEngine::backupDatabase: backupDir.SetFromParent() failed");

		fillBackupDatabaseTableVector(databaseTableVector);

		BackupDatabaseTableVector(PrimaryDatabaseName(),databaseTableVector,
			BuildFullFileName(databaseDir,getEmptyBackupFileName()),
			BuildFullFileName(backupDir,getBackupFileName()),
			getBackupDatabaseName(),
			BuildBackupDatebaseFileNameFromDate(backupDir,getBackupFilePrefix(),"gdb",
			TDateTime::CurrentDate()));

		SetLastBackupDate(TDateTime::CurrentDate());
		fNotify.notify(cel_Info,"Back Up Complete.");
	}
	else
		fNotify.notify(cel_Info,"Skipping Back Up.");
}

/******************************************************************************/

void ASFantasyEngine::waitForASMemberBackup()
{
	if(TDateTime::CurrentDate() > MemberLastBackupDate())
	{
		fNotify.notify(cel_Info,"Waiting For ASMember Backup...");
			
		while(runWithWait(WaitTimeForProcessTenths()))
			if(MemberLastBackupDate() >= TDateTime::CurrentDate())
				break;
	}
}

/******************************************************************************/

void ASFantasyEngine::addAllShelves()
{
	fStore.addProfPlayerShelf();
	fStore.addProfTeamShelf();
	fStore.addTeamShelf();
	fStore.addPlayerShelf();
	fStore.addOffGameStatShelf();
	fStore.addDefGameStatShelf();
	fStore.addScheduleDayShelf();
}

/******************************************************************************/

void ASFantasyEngine::delAllShelves()
{
	fStore.delScheduleDayShelf();
	fStore.delDefGameStatShelf();
	fStore.delOffGameStatShelf();
	fStore.delPlayerShelf();
	fStore.delTeamShelf();
	fStore.delProfTeamShelf();
	fStore.delProfPlayerShelf();
}

/******************************************************************************/

void ASFantasyEngine::loadShelvesForStatLoad()
{
	fStore.loadAllProfPlayers();
	fStore.loadAllProfTeams();
}

/******************************************************************************/

void ASFantasyEngine::unloadShelvesForStatLoad()
{
	fStore.delAllProfPlayerShelfItems();
	fStore.delAllProfTeamShelfItems();
}

/******************************************************************************/

void ASFantasyEngine::loadShelvesForProcessing()
{
	fStore.loadKeyProfPlayers();
	fStore.loadAllProfTeams();
}

/******************************************************************************/

void ASFantasyEngine::unloadShelvesForProcessing()
{
	fStore.delAllProfPlayerShelfItems();
	fStore.delAllProfTeamShelfItems();
}

/******************************************************************************/
/******************************************************************************/

/* If it is time for daily processing, then this function is enter processing
	mode and return true.
	If it is NOT time for daily processing, then false is returned. */
	
bool ASFantasyEngine::beginProcessing()
{
	THoldProcessing holdProcessing = HoldNightlyProcessing();
	
	// Already in Nightly Processing, assumes program as be restarted after error.
	if(InNightlyProcessing() && (holdProcessing == hpr_NoHold))
		return(true);

	// Check for new day.
	if(TDateTime::CurrentDate() <= LastProcessingDate())
		return(false);
		
	if(TDateTime::CurrentTime() >= NightlyProcessingTime())
	{
		holdProcessing = HoldNightlyProcessing();

		if((holdProcessing == hpr_NoHold) || (holdProcessing == hpr_HoldAfterBegin))
		{
			SetInNightlyProcessing(true);

			if(holdProcessing == hpr_NoHold)
				return(true);
		}
			
		fNotify.notify(cel_Info,"Holding Processing...");
			
		while(runWithWait(WaitTimeForProcessTenths()))
		{
			if(HoldNightlyProcessing() == hpr_NoHold)
			{
				SetInNightlyProcessing(true);
				return(true);
			}
		}
	}

	return(false);
}

/******************************************************************************/

void ASFantasyEngine::endProcessing()
{
	SetLastProcessingDate(TDateTime::CurrentDate());
	SetInNightlyProcessing(false);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::processStatFiles()
{
	TDateTime today = TDateTime::CurrentDate();
	StatFileLoaderVector statFileLoaderVector;
	StatFileLoaderVector::iterator iter;
	TDatabase* db = NULL;

	if((today > StatStartDate()) && (today <= StatEndDate() + 1))
	{
		if(today > LastStatLoadDate())
		{
			getStatFilesForLoading(statFileLoaderVector);

			waitForStatFiles(statFileLoaderVector);
			if(!isRunning())
				return;

			fNotify.notify(cel_Info,"Loading Stat Files...");

			db = GetOpenDatabase(PrimaryDatabaseName());
			db->StartTransaction();
			try
			{
				if(shouldProfPlayersLastWeeksPointsBeCleared())
				{
					fNotify.notify(cel_Info,"Clearing ProfPlayers Last Weeks Points...");
					clearAllProfPlayersLastWeeksPoints();
				}

				for(iter = statFileLoaderVector.begin();
						iter != statFileLoaderVector.end(); ++iter)
					loadSingleStatFile(*iter);

				if(shouldStatSummariesBeCreated())
				{
					fNotify.notify(cel_Info,"Creating Stat Summaries...");
					createStatSummaries(today - 1);
				}

				db->Commit();

				SetLastStatLoadDate(today);
				fNotify.notify(cel_Info,"Stat Load Complete.");
			}
			catch(const Exception& e)
			{
				db->Rollback();
				throw ASIException(e.Message.c_str());
			}
			catch(...)
			{
				db->Rollback();
				throw;
			}
		}
		else if(today != LastStatLoadDate())
			throw ASIException("ASFantasyEngine::processStatFiles: unexpected LastStatLoadDate");
		else
			fNotify.notify(cel_Info,"Skipping Stat Load");
	}
	else
		SetLastStatLoadDate(today);
}

/******************************************************************************/

/* Checks and waits for stat files in ASMemberStatDownloadDir().*/

void ASFantasyEngine::waitForStatFiles(
	const StatFileLoaderVector& statFileLoaderVector)
{
	StatFileLoaderVector::const_iterator iter;
	DirSpec statDownloadDir(ASMemberStatDownloadDir());
	bool foundAllFiles;
	bool firstTime = true;

	while(runWithWait(WaitTimeForProcessTenths()))
	{
		foundAllFiles = true;
		for(iter = statFileLoaderVector.begin();
			iter != statFileLoaderVector.end(); ++iter)
		{
			if(!(*iter)->doesFileExistInDir(statDownloadDir))
				foundAllFiles = false;
		}

		if(foundAllFiles)
			break;

		if(firstTime)
		{
			fNotify.notify(cel_Info,"Waiting For Stat Files...");
			firstTime = false;
		}
	}
}

/******************************************************************************/

void ASFantasyEngine::clearAllProfPlayersLastWeeksPoints()
{
	TProfPlayerVector profPlayerVector;
	TProfPlayerVector::iterator iter;
	TProfPlayerPtr profPlayerPtr;

	fStore.getProfPlayerVector(profPlayerVector);
	for(iter = profPlayerVector.begin(); iter != profPlayerVector.end(); iter++)
	{
		profPlayerPtr = *iter;
		if(profPlayerPtr->getLastWeeksPoints() != 0)
		{
			profPlayerPtr->setLastWeeksPoints(0);
			profPlayerPtr->update();
		}
	}
}

/******************************************************************************/

void ASFantasyEngine::loadSingleStatFile(StatFileLoaderPtr loader)
{
	DirSpec statDownloadDir(ASMemberStatDownloadDir());
	DirSpec statHomeDir(StatHomeDir());
	int i,copyTries = 5;

	if(!loader->doesFileExistInDir(statDownloadDir))
		throw ASIException("ASFantasyEngine::loadSingleStatFile: stat file does not exist");

	fNotify.notify(cel_Info,CStrVar::build("Loading File %s...",
		loader->buildFileName().c_str()));

	// Copy Stat file, Need retry loop in case we see file while it is being
	// created by download process.
	for(i = 0; i < copyTries; i++)
	{
		if(!CopyFile(loader->buildFullFileNameInDir(statDownloadDir),
			loader->buildFullFileNameInDir(statHomeDir),true))
		{
			if(i < copyTries - 1)
			{
				fNotify.notify(cel_Info,"ASFantasyEngine::loadSingleStatFile:  CopyFile() failed, retrying");
				SleepEx(tConvertTenthsToTicks(50),FALSE);
			}
			else
				throw ASIException("ASFantasyEngine::loadSingleStatFile: CopyFile() failed");
		}
		else
			break;
	}
	
	// Load Stat file
	loader->setDirSpec(statHomeDir);
	loader->load();
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::processAllLeagues()
{
	TLeagueVector leagueVector;
	TLeagueVector::iterator iter;

	if(TDateTime::CurrentDate() != LastBackupDate())
		throw ASIException("ASFantasyEngine::processAllLeagues: Backup not performed");

	if(TDateTime::CurrentDate() != MemberLastBackupDate())
		throw ASIException("ASFantasyEngine::processAllLeagues: ASMember backup not performed");

	if(TDateTime::CurrentDate() != LastStatLoadDate())
		throw ASIException("ASFantasyEngine::processAllLeagues: Stat Load not performed");

	LoadLeagueVectorByNotLastProcessedDate(TDateTime::CurrentDate(),leagueVector);
	leagueVector.sortByID();

	for(iter = leagueVector.begin(); iter != leagueVector.end(); ++iter)
	{
		if(!isRunning())
			throw ASIException("ASFantasyEngine::processAllLeagues: terminated while processing leagues");

		processOneLeague(*iter);
	}
}

/******************************************************************************/

void ASFantasyEngine::processOneLeague(TLeaguePtr& leaguePtr)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TDatabase* db = NULL;
	TDatabase* memdb = NULL;
	TDatabase* miscdb = NULL;
	
	fNotify.notify(cel_Info,CStrVar::build("Processing %s League, ID(%s)...",
		leaguePtr->getName(),leaguePtr->getLeagueID().c_str()).c_str());

	if((leaguePtr->getLastProcessedDate() < TDateTime::CurrentDate() - 1) ||
			(leaguePtr->getLastProcessedDate() > TDateTime::CurrentDate()))
		throw ASIException("ASFantasyEngine::processOneLeague: invalid LastProcessedDate");

	fCurLeaguePtr = leaguePtr;	//BOB use fCurLeaguePtr everywhere
			
	db = GetOpenDatabase(PrimaryDatabaseName());
	memdb = GetOpenDatabase(MemberDatabaseName());
	miscdb = GetOpenDatabase(MemberMiscDatabaseName());
	
	miscdb->StartTransaction();
	memdb->StartTransaction();
	db->StartTransaction();
	try
	{
		store.loadTeamsForLeague(fCurLeaguePtr->getLeagueID());
		store.loadPlayersForLeague(fCurLeaguePtr->getLeagueID());
		store.loadScheduleDayVectorByLeagueID(fCurLeaguePtr->getLeagueID());
	
		switch(fCurLeaguePtr->getGamePhase())
		{
			case gmph_Enrollment:
				processEnrollmentLeague(fCurLeaguePtr);
				break;
			
			case gmph_PreDraft:
				processPreDraftLeague(fCurLeaguePtr);
				break;
			
			case gmph_Draft:
				processDraftLeague(fCurLeaguePtr);
				break;
			
			case gmph_PreSeason:
				processPreSeasonLeague(fCurLeaguePtr);
				break;
			
			case gmph_Season:
				processSeasonLeague(fCurLeaguePtr);
				break;
			
			case gmph_Playoffs:
				processPlayoffLeague(fCurLeaguePtr);
				break;

			case gmph_PostSeason:
				break;

			default:
				throw ASIException("ASFantasyEngine::processOneLeague: invalid phase");
		}

		store.saveAndDelAllScheduleDayShelfItems();
		store.delAllDefGameStatShelfItems();
		store.delAllOffGameStatShelfItems();
		store.saveAndDelAllPlayerShelfItems();
		store.saveAndDelAllTeamShelfItems();

		fCurLeaguePtr->setLastProcessedDate(TDateTime::CurrentDate());
		fCurLeaguePtr->update();
		fCurLeaguePtr = NULL;
		
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

/******************************************************************************/

void ASFantasyEngine::processEnrollmentLeague(TLeaguePtr& leaguePtr)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TTeamIDVector teamIDVector;
	int numTeams;
	
	if(leaguePtr->isReserved())
	{
		store.getTeamIDVector(teamIDVector);
		numTeams = teamIDVector.size();
		
		if(TDateTime::CurrentDate() >= RegularStartDate())
		{
			if((numTeams >= MinTeamsPerPrivateLeague()) && IsEven(numTeams))
			{
				leaguePtr->calcDraftDate(true);
				leaguePtr->setGamePhase(gmph_PreDraft);
				processPreDraftLeague(leaguePtr);
				return;
			}
		}
	}
}

/******************************************************************************/

void ASFantasyEngine::processPreDraftLeague(TLeaguePtr& leaguePtr)
{
	if(TDateTime::CurrentDate() == leaguePtr->getDraftDate() -
		EmailUpcomingDraftDaysBefore())
	{
		sendDraftUpcomingEmail();
	}
	else if(TDateTime::CurrentDate() == leaguePtr->getDraftDate())
	{
		leaguePtr->setGamePhase(gmph_Draft);
		processDraftLeague(leaguePtr);
		return;
	}
	else if(TDateTime::CurrentDate() > leaguePtr->getDraftDate())
		throw ASIException("ASFantasyEngine::processPreDraftLeague: fatal "
			"error, TDateTime::CurrentDate() > leaguePtr->getDraftDate()");
}

/******************************************************************************/

void ASFantasyEngine::processDraftLeague(TLeaguePtr& leaguePtr)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TTeamIDVector teamIDVector;
	TDateTime draftDate = leaguePtr->getDraftDate();
	TDateTime curDate = TDateTime::CurrentDate();
	DraftResolver draftResolver;
	int fromRound;
	TDraftResultPtr draftResultPtr;
	
	// Process Day 1
	if(curDate == draftDate)
	{
		store.getTeamIDVector(teamIDVector);
	
		// Create Draft Order record
		TDraftOrderPtr draftOrderPtr = CreateDraftOrder(leaguePtr->getLeagueID(),
			teamIDVector);

		// Create empty Draft Result record
		TDraftResultPtr draftResultPtr = TDraftResult::newInstance();
		draftResultPtr->setLeagueID(leaguePtr->getLeagueID());
		draftResultPtr->update();

		fromRound = 1;
		draftResolver.resolve(leaguePtr->getLeagueID(),fromRound,
			fromRound + NumDraftRoundsPerDay() - 1);
	}
	else if(curDate == draftDate + 1)
	{
		fromRound = NumDraftRoundsPerDay() + 1;
		draftResolver.resolve(leaguePtr->getLeagueID(),fromRound,
			fromRound + NumDraftRoundsPerDay() - 1);
	}
	else if(curDate == draftDate + 2)
	{
		fromRound = (NumDraftRoundsPerDay() * 2) + 1;
		draftResolver.resolve(leaguePtr->getLeagueID(),fromRound,
			fromRound + NumDraftRoundsPerDay() - 1);
	}
	else if(curDate == draftDate + 3)
	{
		fromRound = (NumDraftRoundsPerDay() * 3) + 1;
		draftResultPtr = draftResolver.resolve(leaguePtr->getLeagueID(),
			fromRound,NumDraftRounds());
		
		leaguePtr->setGamePhase(gmph_PreSeason);
		createSeasonSchedule();
		calcSeasonDate();
		createDefaultLineup(leaguePtr,draftResultPtr);
		calcLeagueStandings();
		addNewPlayersToFreeAgency(leaguePtr,true);
	}
	else
		throw ASIException("ASFantasyEngine::processDraftLeague: curDate outside of draft days");
}

/******************************************************************************/

void ASFantasyEngine::processPreSeasonLeague(TLeaguePtr& leaguePtr)
{
	if(TDateTime::CurrentDate() == leaguePtr->getSeasonDate())
	{
		leaguePtr->setGamePhase(gmph_Season);
		processSeasonLeague(leaguePtr);
		return;
	}
	else if(TDateTime::CurrentDate() > leaguePtr->getSeasonDate())
		throw ASIException("ASFantasyEngine::processPreSeasonLeague: fatal error, "
			"TDateTime::CurrentDate() > leaguePtr->getSeasonDate()");
			
	addNewPlayersToFreeAgency(leaguePtr,false);
	
	processFreeAgentClaims(TTradeVector(),TGameResultVector());

	sendNewFreeAgentsEmail();

	verifyRosters();
}

/******************************************************************************/

void ASFantasyEngine::processSeasonLeague(TLeaguePtr& leaguePtr)
{
	TTeamIDVector teamIDVector;
	TScheduleDayVector scheduleDayVector;
	TScheduleDayPtr lastScheduleDayPtr;
	TScheduleDayPtr thisScheduleDayPtr;
	TDateTime today = TDateTime::CurrentDate();
	TGameResultVector gameResultVector;
	TTradeVector tradeVector;
	TDateTime yesterday = TDateTime::CurrentDate() - 1;
	bool tradesClaimsProcessed = false;
	
	fStore.loadOffGameStatVectorByDatePeriod(yesterday,yesterday,stp_SeasonGame);
	fStore.loadDefGameStatVectorByDatePeriod(yesterday,yesterday,stp_SeasonGame);

	fStore.getScheduleDayVector(scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	lastScheduleDayPtr = scheduleDayVector.getLastWeeksScheduleDay();
	thisScheduleDayPtr = scheduleDayVector.getThisWeeksScheduleDay();

	if(!lastScheduleDayPtr.isNull())
	{
		if(today == lastScheduleDayPtr->getGameDate())
		{
			if(lastScheduleDayPtr->getStatus() == sdst_InProgress)
			{
				fStore.getTeamIDVector(teamIDVector);
				LoadGameResultVectorByTeamIDVectorGameDate(teamIDVector,
					lastScheduleDayPtr->getGameDate(),gameResultVector);
				updateGames(leaguePtr,lastScheduleDayPtr,gameResultVector,false);

				resolveGames(leaguePtr,lastScheduleDayPtr,false);

				gameResultVector.erase(gameResultVector.begin(),gameResultVector.end());
			}
			else if(lastScheduleDayPtr->getStatus() != sdst_Missed)
				throw ASIException("ASFantasyEngine::processSeasonLeague: unexpected TScheduleDay status");
		}
		else if(today < lastScheduleDayPtr->getGameDate())
			throw ASIException("ASFantasyEngine::processSeasonLeague: unexpected day for lastScheduleDay gameDate");
	}

	if(!thisScheduleDayPtr.isNull())
	{
		bool createdNextDay = areGameResultsCreatedNextDay();

		if((!createdNextDay && (today == thisScheduleDayPtr->getEarlyProfGameDate())) ||
			(createdNextDay && (today == thisScheduleDayPtr->getEarlyProfGameDate() + 1)))
		{
			// For games where lineups are always locked (all but football), 
			// Trades and FA Claims can be pending forever.  To fix this,
			// Trades and FA Claims are processed after the old game has
			// finished and before the new game starts.
			if(!createdNextDay)
			{
				if(gameResultVector.size() != 0)	// sanity check
					throw ASIException("ASFantasyEngine::processSeasonLeague: gameResultVector.size() != 0");

				LoadRecentTradesByLeagueID(leaguePtr->getLeagueID(),tradeVector);
				processTrades(tradeVector,gameResultVector);
				processFreeAgentClaims(tradeVector,gameResultVector);
				tradesClaimsProcessed = true;
			}

			if(thisScheduleDayPtr->getStatus() != sdst_NotStarted)
				throw ASIException("ASFantasyEngine::processSeasonLeague: unexpected TScheduleDay status");

			startGames(leaguePtr,thisScheduleDayPtr,gameResultVector);
		}
		else
		{
			fStore.getTeamIDVector(teamIDVector);
			LoadGameResultVectorByTeamIDVectorGameDate(teamIDVector,
				thisScheduleDayPtr->getGameDate(),gameResultVector);
		}

		if((today > thisScheduleDayPtr->getEarlyProfGameDate()) &&
			(today <= thisScheduleDayPtr->getLateProfGameDate()))
		{
			if(thisScheduleDayPtr->getStatus() != sdst_InProgress)
				throw ASIException("ASFantasyEngine::processSeasonLeague: unexpected TScheduleDay status");

			updateGames(leaguePtr,thisScheduleDayPtr,gameResultVector,false);
		}

		if(today >= thisScheduleDayPtr->getGameDate())
			throw ASIException("ASFantasyEngine::processSeasonLeague: unexpected day for thisScheduleDay gameDate");
	}

	addNewPlayersToFreeAgency(leaguePtr,false);
	
	if(!tradesClaimsProcessed)
	{
		LoadRecentTradesByLeagueID(leaguePtr->getLeagueID(),tradeVector);
		processTrades(tradeVector,gameResultVector);
		processFreeAgentClaims(tradeVector,gameResultVector);
	}

	sendNewFreeAgentsEmail();

	verifyRosters();

	if(TDateTime::CurrentDate() == PlayoffStartDate())
	{
		leaguePtr->setGamePhase(gmph_Playoffs);
		setupForSemiFinalPlayoffs();
	}
}

/******************************************************************************/

void ASFantasyEngine::processPlayoffLeague(TLeaguePtr& leaguePtr)
{
	TTeamIDVector teamIDVector;
	TScheduleDayVector scheduleDayVector;
	TScheduleDayPtr lastScheduleDayPtr;
	TScheduleDayPtr thisScheduleDayPtr;
	TDateTime today = TDateTime::CurrentDate();
	TDateTime postSeasonDate;
	TGameResultVector gameResultVector;
	
	fStore.getScheduleDayVector(scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	lastScheduleDayPtr = scheduleDayVector.getLastWeeksScheduleDay();
	thisScheduleDayPtr = scheduleDayVector.getThisWeeksScheduleDay();

	if(!lastScheduleDayPtr.isNull())
	{
		if(today == lastScheduleDayPtr->getGameDate())
		{
			if(lastScheduleDayPtr->getStatus() == sdst_InProgress)
			{
				fStore.getTeamIDVector(teamIDVector);
				LoadGameResultVectorByTeamIDVectorGameDate(teamIDVector,
					lastScheduleDayPtr->getGameDate(),gameResultVector);

				determinePlayoffGameStats(gameResultVector,
					today - lastScheduleDayPtr->getEarlyProfGameDate() + 1);
				updateGames(leaguePtr,lastScheduleDayPtr,gameResultVector,true);

				resolveGames(leaguePtr,lastScheduleDayPtr,true);

				gameResultVector.erase(gameResultVector.begin(),gameResultVector.end());

				// Was Semi-Final Games?
				if(lastScheduleDayPtr->getProfGameWeek() == cast2short(NumProfWeeks() + 1))
					setupForFinalPlayoffs(lastScheduleDayPtr);
				// Was Final Game?
				else if(lastScheduleDayPtr->getProfGameWeek() == cast2short(NumProfWeeks() + 2))
					setPlayoffsLeagueChamp(lastScheduleDayPtr);
			}
			else if(lastScheduleDayPtr->getStatus() != sdst_Missed)
				throw ASIException("ASFantasyEngine::processPlayoffLeague: unexpected TScheduleDay status");
		}
		else if(today < lastScheduleDayPtr->getGameDate())
			throw ASIException("ASFantasyEngine::processPlayoffLeague: unexpected day for lastScheduleDay gameDate");
	}

	if(!thisScheduleDayPtr.isNull())
	{
		if(today >= thisScheduleDayPtr->getEarlyProfGameDate())
		{
			if(today == thisScheduleDayPtr->getEarlyProfGameDate())
			{
				if(gameResultVector.size() != 0)	// sanity check
					throw ASIException("ASFantasyEngine::processPlayoffLeague: gameResultVector.size() != 0");

				if(thisScheduleDayPtr->getStatus() != sdst_NotStarted)
					throw ASIException("ASFantasyEngine::processPlayoffLeague: unexpected TScheduleDay status");

				startGames(leaguePtr,thisScheduleDayPtr,gameResultVector);
			}
			else
			{
				fStore.getTeamIDVector(teamIDVector);
				LoadGameResultVectorByTeamIDVectorGameDate(teamIDVector,
					thisScheduleDayPtr->getGameDate(),gameResultVector);
			}

			if(thisScheduleDayPtr->getStatus() != sdst_InProgress)
				throw ASIException("ASFantasyEngine::processPlayoffLeague: unexpected TScheduleDay status");

			determinePlayoffGameStats(gameResultVector,
				today - thisScheduleDayPtr->getEarlyProfGameDate() + 1);
			updateGames(leaguePtr,thisScheduleDayPtr,gameResultVector,true);
		}

		if(today >= thisScheduleDayPtr->getGameDate())
			throw ASIException("ASFantasyEngine::processPlayoffLeague: unexpected day for thisScheduleDay gameDate");
	}

	postSeasonDate = PlayoffStartDate() + (PlayoffSeriesLength() * 2);	// Semi-Finals and Finals
	if(today == postSeasonDate)
		leaguePtr->setGamePhase(gmph_PostSeason);
	else if(today > postSeasonDate)
		throw ASIException("ASFantasyEngine::processPlayoffLeague: today > postSeasonDate");
}

/******************************************************************************/

void ASFantasyEngine::getPremiumParticVector(TParticVector& particVector)
{
	TTeamVector teamVector;
	TParticVector allParticVector;
	TParticVector::iterator iter;

	particVector.erase(particVector.begin(),particVector.end());

	fStore.getTeamVector(teamVector);
	LoadParticVectorByTeamVector(teamVector,allParticVector);

	for(iter = allParticVector.begin(); iter != allParticVector.end(); ++iter)
	{
		if((*iter)->getGameLevel() == gml_Premium)
			particVector.push_back(*iter);
	}
}

/******************************************************************************/

void ASFantasyEngine::calcSeasonDate()
{
	TScheduleDayVector scheduleDayVector;
	TScheduleDayVector::const_iterator iter;
	TScheduleDayPtr scheduleDayPtr;
	TDateTime lastDraftDate;
	TDateTime tempDate;

	fStore.getScheduleDayVector(scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	// Find first EarlyProfGameDate after last draft day
	lastDraftDate = fCurLeaguePtr->getDraftDate() + DraftLength() - 1;
	for(iter = scheduleDayVector.begin(); iter != scheduleDayVector.end(); ++iter)
	{
		scheduleDayPtr = *iter;

		if(scheduleDayPtr->getEarlyProfGameDate() > lastDraftDate)
		{
			fCurLeaguePtr->setSeasonDate(scheduleDayPtr->getEarlyProfGameDate());
			return;
		}
		else
		{
			scheduleDayPtr->setStatus(sdst_Missed);
			scheduleDayPtr->update();
		}
	}

	throw ASIException("ASFantasyEngine::calcSeasonDate: could not set season date");
}

/******************************************************************************/

void ASFantasyEngine::startGames(TLeaguePtr leaguePtr,
	TScheduleDayPtr scheduleDayPtr,TGameResultVector& gameResultVector)
{
	TScheduleDayGameVector& scheduleDayGameVector =
		scheduleDayPtr->scheduleDayGameVector();
	TScheduleDayGameVector::iterator iter;

	gameResultVector.erase(gameResultVector.begin(),gameResultVector.end());

	for(iter = scheduleDayGameVector.begin();
		iter != scheduleDayGameVector.end(); ++iter)
	{
		gameResultVector.push_back(createNewGameResultForTeam(leaguePtr,
			scheduleDayPtr,(*iter).getHomeTeamID(),(*iter).getVisitTeamID()));
		gameResultVector.push_back(createNewGameResultForTeam(leaguePtr,
			scheduleDayPtr,(*iter).getVisitTeamID(),(*iter).getHomeTeamID()));
	}

	scheduleDayPtr->setStatus(sdst_InProgress);
	scheduleDayPtr->update();
}

/******************************************************************************/

TGameResultPtr ASFantasyEngine::createNewGameResultForTeam(TLeaguePtr leaguePtr,
	TScheduleDayPtr scheduleDayPtr,const TTeamID teamID,const TTeamID oppTeamID)
{
	TGameResultPtr gameResultPtr;
	TPlayerIDVector playerIDVector;

	gameResultPtr = TGameResult::newInstance();

	gameResultPtr->setTeamID(teamID);
	gameResultPtr->setGameDate(scheduleDayPtr->getGameDate());
	gameResultPtr->setOppTeamID(oppTeamID);

	loadGameStatPlayerIDVectorForTeam(teamID,true,playerIDVector);
	gameResultPtr->offPlayerDatesVector().fillFromPlayerIDVector(playerIDVector);

	loadGameStatPlayerIDVectorForTeam(teamID,false,playerIDVector);
	gameResultPtr->defPlayerDatesVector().fillFromPlayerIDVector(playerIDVector);

	gameResultPtr->update();

	return(gameResultPtr);
}

/******************************************************************************/

void ASFantasyEngine::updateGames(TLeaguePtr leaguePtr,
	TScheduleDayPtr scheduleDayPtr,TGameResultVector& gameResultVector,
	const bool inPlayoffs)
{
	TScheduleDayGameVector& scheduleDayGameVector =
		scheduleDayPtr->scheduleDayGameVector();
	TScheduleDayGameVector::iterator iter;
	TGameResultPtr gameResultPtr;

	for(iter = scheduleDayGameVector.begin();
		iter != scheduleDayGameVector.end(); ++iter)
	{
		gameResultPtr = gameResultVector.findByTeamID((*iter).getHomeTeamID());
		updateGameResultWithGameStatsFromObjectStore(gameResultPtr,inPlayoffs);
		(*iter).setHomeScore(gameResultPtr->getTotalPoints());

		gameResultPtr = gameResultVector.findByTeamID((*iter).getVisitTeamID());
		updateGameResultWithGameStatsFromObjectStore(gameResultPtr,inPlayoffs);
		(*iter).setVisitScore(gameResultPtr->getTotalPoints());
	}

	scheduleDayPtr->update();
}

/******************************************************************************/

void ASFantasyEngine::updateGameResultWithGameStatsFromObjectStore(
	TGameResultPtr gameResultPtr,const bool inPlayoffs)
{
	TPlayerIDVector playerIDVector;
	TOffGameStatVector offGameStatVector;
	TDefGameStatVector defGameStatVector;

	gameResultPtr->offPlayerDatesConstVector().loadPlayerIDVector(playerIDVector);
	fStore.getOffGameStatVectorByPlayerIDVector(playerIDVector,offGameStatVector);
	gameResultPtr->offPlayerDatesVector().updateFromOffGameStatVector(
		offGameStatVector,inPlayoffs);

	gameResultPtr->defPlayerDatesConstVector().loadPlayerIDVector(playerIDVector);
	fStore.getDefGameStatVectorByPlayerIDVector(playerIDVector,defGameStatVector);
	gameResultPtr->defPlayerDatesVector().updateFromDefGameStatVector(
		defGameStatVector,inPlayoffs);

	gameResultPtr->calcTotalPoints();
	gameResultPtr->update();
}

/******************************************************************************/

void ASFantasyEngine::resolveGames(TLeaguePtr& leaguePtr,
	TScheduleDayPtr& scheduleDayPtr,const bool inPlayoffs)
{
	TScheduleDayGameVector& scheduleDayGameVector =
		scheduleDayPtr->scheduleDayGameVector();
	TScheduleDayGameVector::iterator iter;
	
	for(iter = scheduleDayGameVector.begin();
		iter != scheduleDayGameVector.end(); iter++)
	{
		(*iter).setWasGamePlayed(true);
		if(!inPlayoffs)
			updateTeamStats(*iter);
		else
		{
			// During playoffs, ties go to the home team.
			if((*iter).wasGameTied())
				(*iter).setHomeScore(cast2short((*iter).getHomeScore() + 1));
		}
	}

	scheduleDayPtr->setStatus(sdst_Completed);
	scheduleDayPtr->update();

	if(!inPlayoffs)
		calcLeagueStandings();
	sendGameResultsEmail(scheduleDayPtr);
}

/******************************************************************************/

void ASFantasyEngine::updateTeamStats(const TScheduleDayGame& scheduleDayGame)
{
	TTeamPtr visitTeamPtr = fStore.getTeam(scheduleDayGame.getVisitTeamID());
	TTeamPtr homeTeamPtr = fStore.getTeam(scheduleDayGame.getHomeTeamID());
	bool divGame = visitTeamPtr->getDivision() == homeTeamPtr->getDivision();

	if(scheduleDayGame.wasGameTied())
	{
		visitTeamPtr->addTie(divGame);
		homeTeamPtr->addTie(divGame);
	}
	else if(scheduleDayGame.wasHomeTeamWinner())
	{
		visitTeamPtr->addLose(divGame);
		homeTeamPtr->addWin(divGame);
	}
	else
	{
		visitTeamPtr->addWin(divGame);
		homeTeamPtr->addLose(divGame);
	}

	visitTeamPtr->setTotalPoints(cast2short(visitTeamPtr->getTotalPoints() +
		scheduleDayGame.getVisitScore()));
	homeTeamPtr->setTotalPoints(cast2short(homeTeamPtr->getTotalPoints() +
		scheduleDayGame.getHomeScore()));
}

/******************************************************************************/

void ASFantasyEngine::calcLeagueStandings()
{
	TScheduleDayVector scheduleDayVector;
	TTeamVector teamVector;
	TTeamVector divTeamVector;
	TTeamIDVector teamIDVector;

	fStore.getScheduleDayVector(scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	fStore.getTeamVector(teamVector);
	
	divTeamVector.fillFromTeamVectorByDivision(teamVector,div_East);
	LeagueStandingsSorter::sort(fCurLeaguePtr,scheduleDayVector,divTeamVector);
	teamIDVector.fillFromTeamVector(divTeamVector);
	fCurLeaguePtr->eastDivStandings() = teamIDVector;
	
	divTeamVector.fillFromTeamVectorByDivision(teamVector,div_West);
	LeagueStandingsSorter::sort(fCurLeaguePtr,scheduleDayVector,divTeamVector);
	teamIDVector.fillFromTeamVector(divTeamVector);
	fCurLeaguePtr->westDivStandings() = teamIDVector;
	
	LeagueStandingsSorter::sort(fCurLeaguePtr,scheduleDayVector,teamVector);
	teamIDVector.fillFromTeamVector(teamVector);
	fCurLeaguePtr->overallStandings() = teamIDVector;

	reverse(teamIDVector.begin(),teamIDVector.end());
	fCurLeaguePtr->faClaimOrder() = teamIDVector;
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::setupForSemiFinalPlayoffs()
{
	fCurLeaguePtr->setEastWinnerTeamID(fCurLeaguePtr->eastDivStandings()[0]);
	fCurLeaguePtr->setEastWildCardTeamID(fCurLeaguePtr->eastDivStandings()[1]);

	fCurLeaguePtr->setWestWinnerTeamID(fCurLeaguePtr->westDivStandings()[0]);
	fCurLeaguePtr->setWestWildCardTeamID(fCurLeaguePtr->westDivStandings()[1]);

	setSemiFinalPlayoffSchedule();
}

/******************************************************************************/

void ASFantasyEngine::setupForFinalPlayoffs(TScheduleDayPtr scheduleDayPtr)
{
	const TScheduleDayGameVector& scheduleDayGameVector = 
		scheduleDayPtr->scheduleDayGameVector();

	if(scheduleDayGameVector.size() != 2)
		throw ASIException("ASFantasyEngine::setupForFinalPlayoffs: scheduleDayGameVector.size() != 2");

	fCurLeaguePtr->setFinalistOneTeamID(scheduleDayGameVector[0].getWinningTeamID());
	fCurLeaguePtr->setFinalistTwoTeamID(scheduleDayGameVector[1].getWinningTeamID());

	setFinalPlayoffSchedule();
}

/******************************************************************************/

void ASFantasyEngine::setPlayoffsLeagueChamp(TScheduleDayPtr scheduleDayPtr)
{
	const TScheduleDayGameVector& scheduleDayGameVector = 
		scheduleDayPtr->scheduleDayGameVector();

	if(scheduleDayGameVector.size() != 1)
		throw ASIException("ASFantasyEngine::setPlayoffsLeagueChamp: scheduleDayGameVector.size() != 1");

	fCurLeaguePtr->setLeagueChampTeamID(scheduleDayGameVector[0].getWinningTeamID());
	sendLeagueChampEmail();
}

/******************************************************************************/

void ASFantasyEngine::setSemiFinalPlayoffSchedule()
{
	TScheduleDayPtr scheduleDayPtr;
	TScheduleDayGame scheduleDayGame;

	scheduleDayPtr = TScheduleDay::newInstance();
	
	scheduleDayPtr->setLeagueID(fCurLeaguePtr->getLeagueID());
	scheduleDayPtr->setGameDate(PlayoffStartDate() + PlayoffSeriesLength());

	scheduleDayPtr->setStatus(sdst_NotStarted);

	scheduleDayPtr->setEarlyProfGameDate(scheduleDayPtr->getGameDate() -
		PlayoffSeriesDays() + 1);
	scheduleDayPtr->setEarlyProfGameTime(NightlyProcessingTime());
	scheduleDayPtr->setLateProfGameDate(scheduleDayPtr->getGameDate() - 1);
	scheduleDayPtr->setProfGameWeek(cast2short(NumProfWeeks() + 1));

	scheduleDayGame.clear();
	scheduleDayGame.setVisitTeamID(fCurLeaguePtr->getWestWildCardTeamID());
	scheduleDayGame.setHomeTeamID(fCurLeaguePtr->getEastWinnerTeamID());
	scheduleDayPtr->scheduleDayGameVector().push_back(scheduleDayGame);

	scheduleDayGame.clear();
	scheduleDayGame.setVisitTeamID(fCurLeaguePtr->getEastWildCardTeamID());
	scheduleDayGame.setHomeTeamID(fCurLeaguePtr->getWestWinnerTeamID());
	scheduleDayPtr->scheduleDayGameVector().push_back(scheduleDayGame);
	
	scheduleDayPtr->update();

	fStore.addScheduleDay(scheduleDayPtr);
}

/******************************************************************************/

void ASFantasyEngine::setFinalPlayoffSchedule()
{
	TScheduleDayPtr scheduleDayPtr;
	TScheduleDayGame scheduleDayGame;
	TTeamID gameOneWinnerTeamID(fCurLeaguePtr->getFinalistOneTeamID());
	TTeamID gameTwoWinnerTeamID(fCurLeaguePtr->getFinalistTwoTeamID());
	const TTeamIDVector& overallStandings(fCurLeaguePtr->overallStandings());

	scheduleDayPtr = TScheduleDay::newInstance();
	
	scheduleDayPtr->setLeagueID(fCurLeaguePtr->getLeagueID());
	scheduleDayPtr->setGameDate(PlayoffStartDate() + (PlayoffSeriesLength() * 2));

	scheduleDayPtr->setStatus(sdst_NotStarted);

	scheduleDayPtr->setEarlyProfGameDate(scheduleDayPtr->getGameDate() -
		PlayoffSeriesDays() + 1);
	scheduleDayPtr->setEarlyProfGameTime(NightlyProcessingTime());
	scheduleDayPtr->setLateProfGameDate(scheduleDayPtr->getGameDate() - 1);
	scheduleDayPtr->setProfGameWeek(cast2short(NumProfWeeks() + 2));

	scheduleDayGame.clear();
	if(overallStandings.getPosition(gameOneWinnerTeamID) <
		overallStandings.getPosition(gameTwoWinnerTeamID))
	{
		scheduleDayGame.setVisitTeamID(gameTwoWinnerTeamID);
		scheduleDayGame.setHomeTeamID(gameOneWinnerTeamID);
	}
	else
	{
		scheduleDayGame.setVisitTeamID(gameOneWinnerTeamID);
		scheduleDayGame.setHomeTeamID(gameTwoWinnerTeamID);
	}
	scheduleDayPtr->scheduleDayGameVector().push_back(scheduleDayGame);
	
	scheduleDayPtr->update();

	fStore.addScheduleDay(scheduleDayPtr);
}

/******************************************************************************/

void ASFantasyEngine::determinePlayoffGameStats(
	const TGameResultVector& gameResultVector,const int playoffDay)
{
	TGameResultVector::const_iterator gameResultIter;

	for(gameResultIter = gameResultVector.begin();
		gameResultIter != gameResultVector.end(); ++gameResultIter)
	{
		determinePlayoffOffGameStatsForGameResult(*gameResultIter,playoffDay);
		determinePlayoffDefGameStatsForGameResult(*gameResultIter,playoffDay);
	}
}

/******************************************************************************/

void ASFantasyEngine::determinePlayoffOffGameStatsForGameResult(
	TGameResultPtr gameResultPtr,const int playoffDay)
{
	const TPlayerDatesVector& playerDatesVector(
		gameResultPtr->offPlayerDatesConstVector());
	TPlayerDatesVector::const_iterator playerDatesIter;
	TDateTime fromDate;
	TDateTime toDate;

	getSeasonDateRangeForStatPeriod(stp_SeasonToDate,fromDate,toDate);

	// Determine stats for each player in the TGameResult.
	for(playerDatesIter = playerDatesVector.begin();
		playerDatesIter != playerDatesVector.end(); ++playerDatesIter)
	{
		TPlayerDates playerDates(*playerDatesIter);
		TProfPlayerPtr profPlayerPtr = fStore.getProfPlayer(
			playerDates.fPlayerID);
		TDateTimeVector::iterator dateTimeIter;
		TOffGameStatVector offGameStatVector;
		int numStatsToFetch;
		int statPos;

		// Fetch all stats for the player for the season.
		LoadOffGameStatVectorByPlayerIDDateRange(playerDates.fPlayerID,
			fromDate,toDate,offGameStatVector);

		// Remove any stats already selected.
		for(dateTimeIter = playerDates.fDateTimeVector.begin();
			dateTimeIter != playerDates.fDateTimeVector.end(); ++dateTimeIter)
		{
			offGameStatVector.removeByID(TPlayerStatID(
				playerDates.fPlayerID,*dateTimeIter));
		}

		// Randomly select new stats.
		numStatsToFetch = min(getNumOfPlayoffGameStatsPerPlayerByPosition(
			profPlayerPtr->getPosition(),playoffDay),
			cast2int(offGameStatVector.size()));
		for(int i = 0; i < numStatsToFetch; ++i)
		{
			statPos = GetRandomFromRange(0,offGameStatVector.size() - 1);

			if((statPos >= 0) && (statPos < cast2int(offGameStatVector.size())))	//santity check
			{
				fStore.addOffGameStat(offGameStatVector[statPos]);
				offGameStatVector.erase(offGameStatVector.begin() + statPos);
			}
			else
				throw ASIException("ASFantasyEngine::determinePlayoffOff"
					"GameStatsForGameResult: invalid statPos");
		}
	}
}

/******************************************************************************/

void ASFantasyEngine::determinePlayoffDefGameStatsForGameResult(
	TGameResultPtr gameResultPtr,const int playoffDay)
{
	const TPlayerDatesVector& playerDatesVector(
		gameResultPtr->defPlayerDatesConstVector());
	TPlayerDatesVector::const_iterator playerDatesIter;
	TDateTime fromDate;
	TDateTime toDate;

	getSeasonDateRangeForStatPeriod(stp_SeasonToDate,fromDate,toDate);

	// Determine stats for each player in the TGameResult.
	for(playerDatesIter = playerDatesVector.begin();
		playerDatesIter != playerDatesVector.end(); ++playerDatesIter)
	{
		TPlayerDates playerDates(*playerDatesIter);
		TProfPlayerPtr profPlayerPtr = fStore.getProfPlayer(
			playerDates.fPlayerID);
		TDateTimeVector::iterator dateTimeIter;
		TDefGameStatVector defGameStatVector;
		int numStatsToFetch;
		int statPos;

		// Fetch all stats for the player for the season.
		LoadDefGameStatVectorByPlayerIDDateRange(playerDates.fPlayerID,
			fromDate,toDate,defGameStatVector);

		// Remove any stats already selected.
		for(dateTimeIter = playerDates.fDateTimeVector.begin();
			dateTimeIter != playerDates.fDateTimeVector.end(); ++dateTimeIter)
		{
			defGameStatVector.removeByID(TPlayerStatID(
				playerDates.fPlayerID,*dateTimeIter));
		}

		// Randomly select new stats.
		numStatsToFetch = min(getNumOfPlayoffGameStatsPerPlayerByPosition(
			profPlayerPtr->getPosition(),playoffDay),
			cast2int(defGameStatVector.size()));
		for(int i = 0; i < numStatsToFetch; ++i)
		{
			statPos = GetRandomFromRange(0,defGameStatVector.size() - 1);

			if((statPos >= 0) && (statPos < cast2int(defGameStatVector.size())))	//santity check
			{
				fStore.addDefGameStat(defGameStatVector[statPos]);
				defGameStatVector.erase(defGameStatVector.begin() + statPos);
			}
			else
				throw ASIException("ASFantasyEngine::determinePlayoffDef"
					"GameStatsForGameResult: invalid statPos");
		}
	}
}

/******************************************************************************/
/******************************************************************************/

/* Sanity check function. Make sure that roster moves have not created
	invalid data for a team. */

void ASFantasyEngine::verifyRosters()
{
	TTeamPtr teamPtr;
	TTeamVector teamVector;
	TTeamVector::iterator iter;
	TPlayerIDVector playerIDVector;

	fStore.getTeamVector(teamVector);

	for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
	{
		teamPtr = *iter;
		fStore.getTeamPlayerIDVectorByTeam(teamPtr->getTeamID(),playerIDVector);

		if(cast2int(playerIDVector.size()) > MaxPlayersPerTeam())
			throw ASIException("ASFantasyEngine::verifyRosters: too many "
				"players on Team(%s)",teamPtr->getTeamID().c_str());
		else if(cast2int(playerIDVector.size()) < MaxPlayersPerTeam())
			CommErrMsg(cel_Info,"ASFantasyEngine::verifyRosters: "
				"Team(%s) only has %d players",teamPtr->getTeamID().c_str(),
				(int)playerIDVector.size());

		if(!isTeamsLineupStillValid(teamPtr->getTeamID()))
			throw ASIException("ASFantasyEngine::verifyRosters: Team(%s)'s "
				"lineup is no longer valid",teamPtr->getTeamID().c_str());
	}
}

/******************************************************************************/

bool ASFantasyEngine::isPlayerInGameResultLineup(TTeamID teamID,
	TPlayerID playerID,const TGameResultVector& gameResultVector) const
{
	TGameResultPtr gameResultPtr = gameResultVector.findByTeamID(teamID,
		cam_MayNotExist);
	TPlayerIDVector playerIDVector;

	if(gameResultPtr.isNull())
		return(false);

	gameResultPtr->offPlayerDatesConstVector().loadPlayerIDVector(playerIDVector);
	if(playerIDVector.contains(playerID))
		return(true);

	gameResultPtr->defPlayerDatesConstVector().loadPlayerIDVector(playerIDVector);
	if(playerIDVector.contains(playerID))
		return(true);

	return(false);
}

/******************************************************************************/

bool ASFantasyEngine::isAnyPlayerIDFromVectorInTeamsGameResultLineups(
	TTeamID teamID,const TGameResultVector& gameResultVector,
	const TPlayerIDVector& playerIDVector) const
{
	TPlayerIDVector::const_iterator iter;

	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		TPlayerID playerID = *iter;

		if(isPlayerInGameResultLineup(teamID,playerID,gameResultVector))
			return(true);
	}

	return(false);
}

/******************************************************************************/

void ASFantasyEngine::movePlayerToTeam(TPlayerID playerID,TTeamID teamID) const
{
	TPlayerPtr playerPtr = fStore.getPlayer(fCurLeaguePtr->getLeagueID(),playerID);

	#if defined(TOOLDEBUGON)
	{
		CStr255 str("ASFantasyEngine::movePlayerToTeam: ");

		str.ConcatVarg("Team(%s) getting ",teamID.c_str());
		str.ConcatVarg("Player(%s) from ",playerID.c_str());
		if(playerPtr->isFreeAgent())
			str.Concat("Free Agency");
		else
			str.ConcatVarg("Team(%s)",playerPtr->getTeamID().c_str());
		CommErrMsg(cel_Info,str);
	}
	#endif
			

	if(!playerPtr->isFreeAgent())
		removePlayerFromTeamsLineups(playerPtr->getTeamID(),playerID);

	playerPtr->setTeamID(teamID);
}

/******************************************************************************/

void ASFantasyEngine::movePlayerIDVectorToTeam(const TPlayerIDVector& playerIDVector,
	TTeamID teamID) const
{
	TPlayerIDVector::const_iterator iter;

	for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
	{
		TPlayerID playerID = *iter;

		movePlayerToTeam(playerID,teamID);
	}
}

/******************************************************************************/

void ASFantasyEngine::releasePlayerToFreeAgency(TPlayerID playerID) const
{
	TPlayerPtr playerPtr = fStore.getPlayer(fCurLeaguePtr->getLeagueID(),playerID);

	#if defined(TOOLDEBUGON)
	{
		CStr31 playerIDStr(playerPtr->getPlayerID().c_str());
		CommErrMsg(cel_Info,"ASFantasyEngine::releasePlayerToFreeAgency: "
			"Team(%s) releasing Player(%s) to Free Agency",
			playerPtr->getTeamID().c_str(),playerIDStr.c_str());
	}
	#endif

	removePlayerFromTeamsLineups(playerPtr->getTeamID(),playerID);

	playerPtr->setTeamID(TTeamID());
	playerPtr->setNewFADate(TDateTime::CurrentDate());
}

/******************************************************************************/

void ASFantasyEngine::releasePlayerIDVectorToFreeAgency(
	const TPlayerIDVector& playerIDVector,int numToRelease) const
{
	TPlayerIDVector::const_iterator iter;

	for(iter = playerIDVector.begin(); (iter != playerIDVector.end()) &&
		(numToRelease > 0); iter++)
	{
		TPlayerID playerID = *iter;

		releasePlayerToFreeAgency(playerID);
		numToRelease--;
	}
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::processTrades(TTradeVector& tradeVector,
	const TGameResultVector& gameResultVector) const
{
	TTradePtr tradePtr;
	TTradeVector::iterator iter;

	CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: processing Trades");

	// Process Open Trades
	for(iter = tradeVector.begin(); iter != tradeVector.end(); iter++)
	{
		tradePtr = *iter;

		if(tradePtr->getStatus() == trs_Proposed)
		{
			if(isTradeStillValid(tradePtr))
			{
				if(hasTradeExpired(tradePtr))
				{
					CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: expiring Trade(%s)",
						tradePtr->getTradeID().c_str());
					tradePtr->setStatus(trs_Expired);
				}
			}
			else
			{
				CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: invalidating Trade(%s)",
					tradePtr->getTradeID().c_str());
				tradePtr->setStatus(trs_Invalidated);
			}
		}
		else if(tradePtr->getStatus() == trs_Accepted)
		{
			if(isTradeStillValid(tradePtr))
			{
				if(hasTradeBeenProtested(tradePtr))
				{
					CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: protesting Trade(%s)",
						tradePtr->getTradeID().c_str());
					tradePtr->setStatus(trs_Protested);
				}
				else
				{
					if(hasTradeProtestPeriodPast(tradePtr))
					{
						if(!areAnyTradePlayersLocked(tradePtr,gameResultVector))
						{
							CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: completing Trade(%s)",
								tradePtr->getTradeID().c_str());

							performActualTrade(tradePtr);
							tradePtr->setStatus(trs_Completed);
						}
						else
							CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: postponing locked Trade(%s)",
								tradePtr->getTradeID().c_str());
					}
				}
			}
			else
			{
				CommErrMsg(cel_Info,"ASFantasyEngine::processTrades: invalidating Trade(%s)",
					tradePtr->getTradeID().c_str());
				tradePtr->setStatus(trs_Invalidated);
			}
		}

		tradePtr->update();
	}

	// Re-Verify Trades - Completed trade may have invalidated another trade.
	validateTrades(tradeVector);
}

/******************************************************************************/

void ASFantasyEngine::validateTrades(TTradeVector& tradeVector) const
{
	TTradePtr tradePtr;
	TTradeVector::iterator iter;

	for(iter = tradeVector.begin(); iter != tradeVector.end(); iter++)
	{
		tradePtr = *iter;

		if((tradePtr->getStatus() == trs_Proposed) ||
			(tradePtr->getStatus() == trs_Accepted))
		{
			if(!isTradeStillValid(tradePtr))
			{
				CommErrMsg(cel_Info,"ASFantasyEngine::validateTrades: invalidating Trade(%s)",
					tradePtr->getTradeID().c_str());
				tradePtr->setStatus(trs_Invalidated);
			}
		}

		tradePtr->update();
	}
}

/******************************************************************************/

bool ASFantasyEngine::isTradeStillValid(TTradePtr tradePtr) const
{
	TPlayerIDVector playerIDVector;

	fStore.getTeamPlayerIDVectorByTeam(tradePtr->getTeamID(),playerIDVector);
	if (!playerIDVector.contains(tradePtr->givePlayerIDVector(), false))
		return(false);
	if (!playerIDVector.contains(tradePtr->proposeRelPlayerIDVector(), false))
		return(false);

	if(cast2int(playerIDVector.size() + tradePtr->getPlayerIDVector().size() -
			tradePtr->givePlayerIDVector().size() -
			tradePtr->proposeRelPlayerIDVector().size()) > MaxPlayersPerTeam())
		return(false);

	fStore.getTeamPlayerIDVectorByTeam(tradePtr->getProposeToTeamID(),playerIDVector);
	if (!playerIDVector.contains(tradePtr->getPlayerIDVector(), false))
		return(false);
	if (!playerIDVector.contains(tradePtr->acceptRelPlayerIDVector(), false))
		return(false);

	// If receiving team has not accepted, then acceptRelPlayerIDVector will
	//	not be set and number of players might be over MaxPlayersPerTeam.
	if(tradePtr->getStatus() == trs_Accepted)
	{
		if(cast2int(playerIDVector.size() + tradePtr->givePlayerIDVector().size() -
				tradePtr->getPlayerIDVector().size() -
				tradePtr->acceptRelPlayerIDVector().size()) > MaxPlayersPerTeam())
			return(false);
	}

	return(true);
}

/******************************************************************************/

bool ASFantasyEngine::hasTradeExpired(TTradePtr tradePtr) const
{
	TDateTime expires = tradePtr->getProposedDate() + MaxTradeProposeDays;

	if(TDateTime::CurrentDate() + NightlyProcessingTime() >= expires)
		return(true);

	return(false);
}

/******************************************************************************/

bool ASFantasyEngine::hasTradeBeenProtested(TTradePtr tradePtr) const
{
	int numProtestsRequired =
		ceil((double)(fCurLeaguePtr->getNumTeamsInLeague() - 2) / (double)3);

	if(cast2int(tradePtr->protestTeamIDVector().size()) >= numProtestsRequired)
		return(true);

	return(false);
}

/******************************************************************************/

bool ASFantasyEngine::hasTradeProtestPeriodPast(TTradePtr tradePtr) const
{
	TDateTime expires = tradePtr->getAcceptedDate() + MaxTradeProtestDays;

	if(TDateTime::CurrentDate() + NightlyProcessingTime() >= expires)
		return(true);

	return(false);
}

/******************************************************************************/

/* Determines if player is ACTIVE in trade. A player is considered ACTIVE if
	player was 'proposed' by current team to give away/relase or was
	'accepted' by current team to give away/release. */

bool ASFantasyEngine::isPlayerActiveInTrade(const TPlayerPtr& playerPtr,
	const TTradePtr& tradePtr) const
{
	if(playerPtr->getTeamID() == tradePtr->getTeamID())
	{
		if((tradePtr->getStatus() == trs_Proposed) ||
			(tradePtr->getStatus() == trs_Accepted))
		{
			if(tradePtr->givePlayerIDVector().contains(playerPtr->getPlayerID()))
				return(true);

			if(tradePtr->proposeRelPlayerIDVector().contains(playerPtr->getPlayerID()))
				return(true);
		}
	}
	else if(playerPtr->getTeamID() == tradePtr->getProposeToTeamID())
	{
		if(tradePtr->getStatus() == trs_Accepted)
		{
			if(tradePtr->getPlayerIDVector().contains(playerPtr->getPlayerID()))
				return(true);

			if(tradePtr->acceptRelPlayerIDVector().contains(playerPtr->getPlayerID()))
				return(true);
		}
	}

	return(false);
}

/******************************************************************************/

bool ASFantasyEngine::isPlayerActiveInAnyTrade(TPlayerID playerID,
	TTradeVector& tradeVector) const
{
	TTradeVector::const_iterator iter;

	for(iter = tradeVector.begin(); iter != tradeVector.end(); iter++)
	{
		const TPlayerPtr playerPtr = fStore.getPlayer(
			fCurLeaguePtr->getLeagueID(),playerID);
		const TTradePtr tradePtr = *iter;

		if(isPlayerActiveInTrade(playerPtr,tradePtr))
			return(true);
	}

	return(false);
}

/******************************************************************************/

bool ASFantasyEngine::areAnyTradePlayersLocked(TTradePtr tradePtr,
	const TGameResultVector& gameResultVector) const
{
	if(isAnyPlayerIDFromVectorInTeamsGameResultLineups(tradePtr->getTeamID(),
			gameResultVector,tradePtr->givePlayerIDVector()))
		return(true);

	if(isAnyPlayerIDFromVectorInTeamsGameResultLineups(tradePtr->getTeamID(),
			gameResultVector,tradePtr->proposeRelPlayerIDVector()))
		return(true);

	if(isAnyPlayerIDFromVectorInTeamsGameResultLineups(tradePtr->getProposeToTeamID(),
			gameResultVector,tradePtr->getPlayerIDVector()))
		return(true);

	if(isAnyPlayerIDFromVectorInTeamsGameResultLineups(tradePtr->getProposeToTeamID(),
			gameResultVector,tradePtr->acceptRelPlayerIDVector()))
		return(true);

	return(false);
}

/******************************************************************************/

void ASFantasyEngine::performActualTrade(TTradePtr tradePtr) const
{
	TPlayerIDVector playerIDVector;

	movePlayerIDVectorToTeam(tradePtr->getPlayerIDVector(),tradePtr->getTeamID());
	movePlayerIDVectorToTeam(tradePtr->givePlayerIDVector(),tradePtr->getProposeToTeamID());

	fStore.getTeamPlayerIDVectorByTeam(tradePtr->getTeamID(),playerIDVector);
	releasePlayerIDVectorToFreeAgency(tradePtr->proposeRelPlayerIDVector(),
		max(0U,playerIDVector.size() - MaxPlayersPerTeam()));

	fStore.getTeamPlayerIDVectorByTeam(tradePtr->getProposeToTeamID(),playerIDVector);
	releasePlayerIDVectorToFreeAgency(tradePtr->acceptRelPlayerIDVector(),
		max(0U,playerIDVector.size() - MaxPlayersPerTeam()));
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::addNewPlayersToFreeAgency(TLeaguePtr& leaguePtr,
	bool includePrevious)
{
	TPlayerIDVector playerIDVector;
	TPlayerIDVector::iterator iter;
	TDateTime fromDate;
	TDateTime toDate;
	TDateTime today = TDateTime::CurrentDate();

	toDate = today;
	if(!includePrevious)
		fromDate = toDate;
	//else fromDate is 0
		
	fStore.getProfPlayerIDVectorByNewPlayerDateRange(fromDate,toDate,playerIDVector);

	if(playerIDVector.size() > 0)
	{
		for(iter = playerIDVector.begin(); iter != playerIDVector.end(); iter++)
		{
			TPlayerID playerID(*iter);
			bool addPlayer = true;

			// If includePrevious, then its possible that player already exits.
			if(includePrevious && !fStore.getPlayer(leaguePtr->getLeagueID(),
					playerID,ObjectStore::gim_MayNotExist).isNull())
				addPlayer = false;

			if(addPlayer)
			{
				TPlayerPtr playerPtr = fStore.newPlayer(leaguePtr->getLeagueID(),playerID);
				playerPtr->setNewFADate(today);
				playerPtr->update();
			}
		}
	}
}

/******************************************************************************/

void ASFantasyEngine::processFreeAgentClaims(TTradeVector& tradeVector,
	const TGameResultVector& gameResultVector)
{
	TTeamIDVector faClaimOrderVector = fCurLeaguePtr->faClaimOrder();
	TFreeAgentClaimVector freeAgentClaimVector;
	TTeamIDVector processedClaimsVector;
	TTeamIDVector::iterator iter;
	TPlayerIDVector playerIDVector;
	bool mustRelease;
	
	CommErrMsg(cel_Info,"ASFantasyEngine::processFreeAgentClaims: processing Free Agent claims");
	
	LoadPendingFreeAgentClaimVectorByTeamIDVector(
		fCurLeaguePtr->overallStandings(),freeAgentClaimVector);

	for(iter = faClaimOrderVector.begin(); iter != faClaimOrderVector.end(); ++iter)
	{
		TFreeAgentClaimPtr freeAgentClaimPtr =
			freeAgentClaimVector.findByTeamID(*iter,cam_MayNotExist);

		if(!freeAgentClaimPtr.isNull())
		{
			freeAgentClaimPtr->setProcessedDate(TDateTime::CurrentDate());

			if(isFreeAgentClaimStillValid(freeAgentClaimPtr))
			{
				TPlayerPtr& playerPtr = fStore.getPlayer(fCurLeaguePtr->getLeagueID(),
					freeAgentClaimPtr->getClaimPlayerID());

				if(!playerPtr->isNewFreeAgent())
				{
					mustRelease = true;

					fStore.getTeamPlayerIDVectorByTeam(freeAgentClaimPtr->getTeamID(),
						playerIDVector);
					if(cast2int(playerIDVector.size()) < MaxPlayersPerTeam())
						mustRelease = false;

					/* If a player is being released, verify the player is not
						activly involved in a trade. */
					if(!mustRelease ||
						!isPlayerActiveInAnyTrade(freeAgentClaimPtr->getReleasePlayerID(),
						tradeVector))
					{
						if(!isFreeAgentReleasePlayerLocked(freeAgentClaimPtr,
							gameResultVector))
						{
							// Assign Free Agent to Team
							movePlayerToTeam(freeAgentClaimPtr->getClaimPlayerID(),
								freeAgentClaimPtr->getTeamID());

							// Release Team Player to Free Agency
							if(mustRelease)
								releasePlayerToFreeAgency(freeAgentClaimPtr->getReleasePlayerID());
							
							freeAgentClaimPtr->setStatus(facs_Completed);

							processedClaimsVector.push_back(freeAgentClaimPtr->getTeamID());
						}
						else
						{
							CStr31 playerIDStr(freeAgentClaimPtr->getReleasePlayerID().c_str());
							CommErrMsg(cel_Info,"ASFantasyEngine::processFreeAgentClaims: claim skipped for Team(%s) because Player(%s) is locked",
								freeAgentClaimPtr->getTeamID().c_str(),playerIDStr.c_str());

							freeAgentClaimPtr->setProcessedStatus(fcps_Locked);
						}
					}
					else
					{
						CStr31 playerIDStr(freeAgentClaimPtr->getReleasePlayerID().c_str());
						CommErrMsg(cel_Info,"ASFantasyEngine::processFreeAgentClaims: claim skipped for Team(%s) because Player(%s) is active in trade",
							freeAgentClaimPtr->getTeamID().c_str(),playerIDStr.c_str());

						freeAgentClaimPtr->setProcessedStatus(fcps_InTrade);
					}
				}
				else
					freeAgentClaimPtr->setProcessedStatus(fcps_NewFreeAgent);
			}
			else
			{
				CStr31 playerIDStr(freeAgentClaimPtr->getClaimPlayerID().c_str());
				CommErrMsg(cel_Info,"ASFantasyEngine::processFreeAgentClaims: invalidating claim for Team(%s), Player(%s)",
					freeAgentClaimPtr->getTeamID().c_str(),playerIDStr.c_str());

				freeAgentClaimPtr->setStatus(facs_Invalidated);
			}

			freeAgentClaimPtr->update();
		}
	}

	// Update FAClaimOrder vector
	for(iter = processedClaimsVector.begin(); iter != processedClaimsVector.end(); ++iter)
		faClaimOrderVector.remove(*iter);

	for(iter = processedClaimsVector.begin(); iter != processedClaimsVector.end(); ++iter)
		faClaimOrderVector.push_back(*iter);

	if(faClaimOrderVector.size() != fCurLeaguePtr->faClaimOrder().size())
		throw ASIException("ASFantasyEngine::processFreeAgentClaims: FAClaimOrder size mismatch");

	fCurLeaguePtr->faClaimOrder() = faClaimOrderVector;
		
	// Verify Free Agent Claims - Completed free agent claim may have invalidated another claim.
	validateFreeAgentClaims();

	// Verify Trades - Completed free agent claim may have invalidated a trade.
	validateTrades(tradeVector);
}

/******************************************************************************/

void ASFantasyEngine::validateFreeAgentClaims() const
{
	TFreeAgentClaimPtr freeAgentClaimPtr;
	TFreeAgentClaimVector freeAgentClaimVector;
	TFreeAgentClaimVector::iterator iter;

	LoadPendingFreeAgentClaimVectorByTeamIDVector(
		fCurLeaguePtr->overallStandings(),freeAgentClaimVector);

	for(iter = freeAgentClaimVector.begin();
		iter != freeAgentClaimVector.end(); ++iter)
	{
		freeAgentClaimPtr = *iter;

		if(!isFreeAgentClaimStillValid(freeAgentClaimPtr))
		{
			CStr31 playerIDStr(freeAgentClaimPtr->getClaimPlayerID().c_str());
			CommErrMsg(cel_Info,"ASFantasyEngine::validateFreeAgentClaims: invalidating claim for Team(%s), Player(%s)",
				freeAgentClaimPtr->getTeamID().c_str(),playerIDStr.c_str());

			freeAgentClaimPtr->setProcessedDate(TDateTime::CurrentDate());
			freeAgentClaimPtr->setStatus(facs_Invalidated);
			freeAgentClaimPtr->update();
		}
	}
}

/******************************************************************************/

bool ASFantasyEngine::isFreeAgentClaimStillValid(
	TFreeAgentClaimPtr freeAgentClaimPtr) const
{
	TPlayerIDVector playerIDVector;
	TPlayerPtr playerPtr;

	// Verify claim player is still free agent.
	playerPtr = fStore.getPlayer(fCurLeaguePtr->getLeagueID(),
		freeAgentClaimPtr->getClaimPlayerID());
	if(!playerPtr->isFreeAgent())
		return(false);

	// Verify release player.
	fStore.getTeamPlayerIDVectorByTeam(freeAgentClaimPtr->getTeamID(),playerIDVector);
	if(freeAgentClaimPtr->getReleasePlayerID().isUndefined())
	{
		// If no player if being released, verify roster has room.
		if(cast2int(playerIDVector.size()) >= MaxPlayersPerTeam())
			return(false);
	}
	else
	{
		// If player is being released, verify player is still on roster.
		if(!playerIDVector.contains(freeAgentClaimPtr->getReleasePlayerID()))
			return(false);
	}

	return(true);
}

/******************************************************************************/

bool ASFantasyEngine::isFreeAgentReleasePlayerLocked(
	TFreeAgentClaimPtr freeAgentClaimPtr,
	const TGameResultVector& gameResultVector) const
{
	if(isPlayerInGameResultLineup(freeAgentClaimPtr->getTeamID(),
			freeAgentClaimPtr->getReleasePlayerID(),gameResultVector))
		return(true);

	return(false);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyEngine::sendDraftUpcomingEmail()
{
	TMemberPtr memberPtr;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TTeamVector teamVector;
	TTeamVector::iterator iter;
	TSendMailPtr sendMailPtr;

	CStrVar str;
	CStrVar str2;
	std::vector<int> linesVector;
	int i;

	fStore.getTeamVector(teamVector);

	for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
	{
		teamPtr = *iter;

		//BOB Need to optimize loading of Partics and Members
		particPtr = TPartic::createGet(teamPtr->getParticID(),cam_MustExist);

		if(particPtr->getStatus() != pts_Active)
			continue;

		memberPtr = TMember::createGet(particPtr->getMemberID(),cam_MustExist);

		if(memberPtr->isEmailInvalid())
			continue;

		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime();
		sendMailPtr->setSender(TechSupportEmail());
		sendMailPtr->setRecipient(memberPtr->getEmail());
		sendMailPtr->setSubject(AppNameFull());

		str.copy("TIME IS RUNNING OUT!\r\n\r\n");
		str.concatVarg("Only %d days left until the %s draft begins.\r\n\r\n",
			(int)EmailUpcomingDraftDaysBefore(),AppNameAbbr().c_str());
		str.concatVarg("Make sure the %s %s' draft rankings are set by the end "
			"of day on %s.  The %s League draft day 1 will take place on %s.\r\n\r\n",
			teamPtr->getRegionName(),teamPtr->getTeamName(),
			FormatDateOnlyStr(fCurLeaguePtr->getDraftDate() - 1,
			ASFantasyStandardDateFormat()).c_str(),
			fCurLeaguePtr->getName(),
			FormatDateTimeStr(fCurLeaguePtr->getDraftDate() + NightlyProcessingTime(),
			ASFantasyStandardDateTimeFormat()).c_str());
		str.concat("***\r\n\r\n");
		str.concat("Access your team at http://www.affinitysports.com\r\n\r\n");
		str.concatVarg("If you have forgotten your User Name or Password, send "
			"an email to %s (mailto:%s).\r\n\r\n\r\n",TechSupportName().c_str(),
			TechSupportEmail().c_str());
		str.concat("Thanks and good luck,\r\n\r\n");
		str.concat(TechSupportName());
		str.concat("\r\n");
		str.concatVarg("mailto:%s\r\n",TechSupportEmail().c_str());
		str.concat("Affinity Sports\r\n");
		str.concat("http://www.affinitysports.com\r\n");

		str2.clear();
		GetCharWordWrapLines(str,70,linesVector);
		for(i = 0; i < cast2int(linesVector.size()); i++)
			str2.concatVarg("%s\r\n",GetNextWordWrapLine(str,linesVector,i).c_str());

		sendMailPtr->setBodyText(str2);
		sendMailPtr->update();
	}
}

/******************************************************************************/

void ASFantasyEngine::sendNewFreeAgentsEmail()
{
	TMemberPtr memberPtr;
	TParticVector particVector;
	TParticVector::iterator particIter;
	TParticPtr particPtr;
	
	TPlayerVector playerVector;
	TPlayerVector freeAgentPlayerVector;
	TPlayerVector::iterator playerIter;
	
	TProfPlayerPtr profPlayerPtr;
	TDateTime today = TDateTime::CurrentDate();
	TSendMailPtr sendMailPtr;
	CStrVar str;

	getPremiumParticVector(particVector);
	if(particVector.size() == 0)
		return;

	fStore.getPlayerVector(playerVector);
	for(playerIter = playerVector.begin();
		playerIter != playerVector.end(); playerIter++)
	{
		if((*playerIter)->isFreeAgent() && ((*playerIter)->getNewFADate() == today))
			freeAgentPlayerVector.push_back(*playerIter);
	}

	if(freeAgentPlayerVector.size() == 0)
		return;

	for(particIter = particVector.begin(); particIter != particVector.end();
		particIter++)
	{
		particPtr = *particIter;

		if(particPtr->getStatus() != pts_Active)
			continue;

		//BOB Need to optimize loading of Partics and Members
		memberPtr = TMember::createGet(particPtr->getMemberID(),cam_MustExist);

		if(memberPtr->isEmailInvalid())
			continue;

		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime(TDateTime::CurrentDateTime());
		sendMailPtr->setSender(TechSupportEmail());
		sendMailPtr->setRecipient(memberPtr->getEmail());
		
		str.copyVarg("%s: New Free Agents",AppNameAbbr().c_str());
		sendMailPtr->setSubject(str);

		str.copyVarg("The following players have just been added to the free "
			"agent pool:\r\n\r\n");
		for(playerIter = freeAgentPlayerVector.begin();
			playerIter != freeAgentPlayerVector.end(); playerIter++)
		{
			profPlayerPtr = fStore.getProfPlayer((*playerIter)->getPlayerID());

			str.concatVarg("  %-25s  %-3s  %s\r\n",
				profPlayerPtr->getName().buildFullName().c_str(),
				fStore.getProfTeam(
					profPlayerPtr->getProfTeamID())->getProfTeamAbbr().c_str(),
				convertPositionToString(profPlayerPtr->getPosition()).c_str());
		}

		str.concat("\r\n\r\n***\r\n\r\n");
		str.concat("Access your team at http://www.affinitysports.com\r\n\r\n");

		sendMailPtr->setBodyText(str);
		sendMailPtr->update();
	}
}

/******************************************************************************/

void ASFantasyEngine::sendGameResultsEmail(TScheduleDayPtr& scheduleDayPtr)
{
	TMemberPtr memberPtr;
	TParticVector particVector;
	TParticVector::iterator particIter;
	TParticPtr particPtr;

	TScheduleDayGameVector& scheduleDayGameVector =
		scheduleDayPtr->scheduleDayGameVector();
	TScheduleDayGameVector::iterator iter;
	
	TSendMailPtr sendMailPtr;
	CStrVar str;

	getPremiumParticVector(particVector);
	if(particVector.size() == 0)
		return;

	for(particIter = particVector.begin(); particIter != particVector.end();
		particIter++)
	{
		particPtr = *particIter;

		if(particPtr->getStatus() != pts_Active)
			continue;

		//BOB Need to optimize loading of Partics and Members
		memberPtr = TMember::createGet((*particIter)->getMemberID(),cam_MustExist);

		if(memberPtr->isEmailInvalid())
			continue;

		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime(TDateTime::CurrentDateTime());
		sendMailPtr->setSender(TechSupportEmail());
		sendMailPtr->setRecipient(memberPtr->getEmail());
		
		str.copyVarg("%s: Game Results",AppNameAbbr().c_str());
		sendMailPtr->setSubject(str);

		str.clear();
		for(iter = scheduleDayGameVector.begin();
			iter != scheduleDayGameVector.end(); iter++)
		{
			TScheduleDayGame scheduleDayGame = *iter;

			str.concatVarg("%-30s  %3d\r\n",
				fStore.getTeam(scheduleDayGame.getVisitTeamID())->getFullTeamName().c_str(),
				(int)scheduleDayGame.getVisitScore());
			str.concatVarg("%-30s  %3d\r\n",
				fStore.getTeam(scheduleDayGame.getHomeTeamID())->getFullTeamName().c_str(),
				(int)scheduleDayGame.getHomeScore());
			str.concat("\r\n\r\n");
		}

		str.concat("***\r\n\r\n");
		str.concat("Access your team at http://www.affinitysports.com\r\n\r\n");

		sendMailPtr->setBodyText(str);
		sendMailPtr->update();
	}
}

/******************************************************************************/

void ASFantasyEngine::sendLeagueChampEmail()
{
	TMemberPtr memberPtr;
	TParticPtr particPtr;
	TTeamPtr teamPtr;
	TSendMailPtr sendMailPtr;
	CStrVar str;
	CStrVar str2;

	teamPtr = fStore.getTeam(fCurLeaguePtr->getLeagueChampTeamID());
	//BOB Need to optimize loading of Partics and Members
	particPtr = TPartic::createGet(teamPtr->getParticID(),cam_MustExist);
	memberPtr = TMember::createGet(particPtr->getMemberID(),cam_MustExist);

	if(memberPtr->isEmailInvalid())
		return;

	sendMailPtr = TSendMail::newInstance();
	sendMailPtr->setCreatedDateTime(TDateTime::CurrentDateTime());
	sendMailPtr->setSender(TechSupportEmail());
	sendMailPtr->setRecipient(memberPtr->getEmail());
	
	str.copyVarg("%s: League Championship",AppNameAbbr().c_str());
	sendMailPtr->setSubject(str);

	str.clear();

	str.concatVarg("Congratulations on winning the Championship of the "
		"%s League.\r\n\r\n",fCurLeaguePtr->getName());
	str.concat("We will be sending your championship T-shirt very soon.\r\n\r\n");
	str.concat("Please review your name and address below:\r\n\r\n");

	str.concat(memberPtr->getName().buildFullName());
	str.concat("\r\n");

	if(tStrHasLen(memberPtr->getAddrStreet1()))
	{
		str.concat(memberPtr->getAddrStreet1());
		str.concat("\r\n");
	}

	if(tStrHasLen(memberPtr->getAddrStreet2()))
	{
		str.concat(memberPtr->getAddrStreet2());
		str.concat("\r\n");
	}

	str2 = BuildAddressCityStateZipLine(memberPtr->getAddrCity(),
		memberPtr->getAddrState(),memberPtr->getAddrZip());
	if(str2.hasLen())
	{
		str.concat(str2);
		str.concat("\r\n");
	}

	str.concat("\r\n");

	str.concatVarg("If these are not correct, please notify %s (mailto:%s)."
		"\r\n\r\n\r\n",TechSupportName().c_str(),TechSupportEmail().c_str());

	str.concatVarg("Thanks for playing %s from Affinity Sports.\r\n\r\n",
		AppNameFull().c_str());

	str.concatVarg("%s\r\n",TechSupportName().c_str());
	str.concat("Affinity Sports\r\n");

	sendMailPtr->setBodyText(str);
	sendMailPtr->update();
}

/******************************************************************************/

}; //asfantasy

/******************************************************************************/
/******************************************************************************/
