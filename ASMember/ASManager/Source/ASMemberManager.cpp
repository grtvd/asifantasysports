/* ASMemberManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommMisc.h"
#include "CommDir.h"
#include "CommDB.h"
#include "CommTick.h"
#include "SMTPMailer.h"
#include "SendMail.h"
#include "ErrorLog.h"

#include "ASMemberAppOptions.h"
#include "ASMemberManager.h"

namespace asmember
{

/******************************************************************************/

#define EmailSendFailedIntSecs()	(600)		// Number of secs to wait between failed emails (MailerUnavailException)

/******************************************************************************/
/******************************************************************************/

TNTService& tag::getTheNTService()
{
	static asmember::ASMemberManager manager;
	return(manager);
}

/******************************************************************************/
/******************************************************************************/

void ASMemberManager::run()
{
	TDatabase* db = NULL;
	CStrVar excepMsg;

	try
	{
		TSMTPMailer::setDefaultHostName(MailHostName());
		TSMTPMailer::setDefaultUserID(MailUserID());
		GetMemberCommErrFileList(fCommErrFileList);
		
		fLastStatusEmailDateTime = TDateTime::CurrentDateTime() -
			((double)MemberStatusEmailIntSecs() / (double)SECONDS_PER_DAY);

		db = OpenDatabase(MemberMiscDatabaseName());
		fNotify.notify(cel_Info,"Startup successful...");
		
		while(runWithWait())
		{
			backupDatabase();
			doMiscProcessing();
		}
	}
	catch(const Exception& e)
	{
		excepMsg.copyVarg("TASMemberManager::run(): Exception thrown: %s",
			e.Message.c_str());
	}
	catch(const ASIException& e)
	{
		excepMsg.copyVarg("TASMemberManager::run(): ASIException thrown: %s",
			e.getMsg());
	}
	catch(const exception& e)
	{
		excepMsg.copyVarg("TASMemberManager::run(): exception thrown: %s",
			e.what());
	}
	catch(...)
	{
		excepMsg.copyVarg("TASMemberManager::run(): exception thrown: unknown");
	}

	CloseDatabase(db);

	if(excepMsg.hasLen())
		fNotify.notify(cel_Error,excepMsg);
	fNotify.notify(cel_Info,"Shutting down...");
}

/******************************************************************************/
/******************************************************************************/

void ASMemberManager::backupDatabase()
{
	if((TDateTime::CurrentTime() >= MemberDailyBackupTime()) &&
		(TDateTime::CurrentDate() > MemberLastBackupDate()))
	{
		DirSpec homeDir = ASMemberHomeDir();
		DirSpec databaseDir;
		DirSpec backupDir;

		TDatabaseTableVector databaseTableVector;

		fNotify.notify(cel_Info,"Backing Up Database...");

		if(!databaseDir.SetFromParent(homeDir,"Database"))
			throw ASIException("ASMemberManager::backupDatabase: databaseDir.SetFromParent() failed");
		if(!backupDir.SetFromParent(databaseDir,"Backup"))
			throw ASIException("ASMemberManager::backupDatabase: backupDir.SetFromParent() failed");

		databaseTableVector.push_back("Member");
		databaseTableVector.push_back("Partic");
		databaseTableVector.push_back("PayHistory");

		BackupDatabaseTableVector(MemberDatabaseName(),databaseTableVector,
			BuildFullFileName(databaseDir,"ASMemberEmpty.gdb"),
			BuildFullFileName(backupDir,"ASMemberBackup.gdb"),"ASMemberBackup",
			BuildBackupDatebaseFileNameFromDate(backupDir,"ASMember","gdb",
			TDateTime::CurrentDate()));

		SetMemberLastBackupDate(TDateTime::CurrentDate());
		fNotify.notify(cel_Info,"Back Up Complete.");
	}
}

/******************************************************************************/

void ASMemberManager::doMiscProcessing()
{
	loadCommErrFiles();
	processNewErrors();
	sendNewEmails();
}

/******************************************************************************/

void ASMemberManager::sendNewEmails()
{
	TDateTime nextRunTime = fLastEmailSendFailedDateTime +
		((double)EmailSendFailedIntSecs()/(double)SECONDS_PER_DAY);
	TSendMailVector sendMailVector;
	TMailerPtr mailerPtr;

	if(TDateTime::CurrentDateTime() < nextRunTime)
		return;

	LoadSendMailVectorByNotSent(sendMailVector);
	if(sendMailVector.size() > 0)
	{
		//fNotify.notify(cel_Info,"Sending Emails...");
		mailerPtr = TSMTPMailer::newInstance();
		try
		{
			SendAllSendMailVector(sendMailVector,mailerPtr);
		}
		catch(const MailerUnavailException& e)
		{
			fLastEmailSendFailedDateTime = TDateTime::CurrentDateTime();
			CommErrMsg(cel_Warning,"ASMemberManager::sendNewEmails: "
				"MailerUnavailException thrown: %s",e.getMsg());
		}
		catch(const Exception& e)
		{
			throw ASIException(e.Message.c_str());
		}
		catch(...)
		{
			throw;
		}
	}
}

/******************************************************************************/

void ASMemberManager::loadCommErrFiles()
{
	int numFiles, i;

	numFiles = fCommErrFileList.size();
	for(i = 0; i < numFiles; i++)
	{
		InsertCommErrFileIntoErrorLog(fCommErrFileList[i],
			MemberMiscDatabaseName(),iceo_FileMayNotExist |
			iceo_RenameForLoad | iceo_LoadExistingTemp |
			iceo_DatabaseIsOpen | iceo_StartTransaction);
	}
}

/******************************************************************************/

void ASMemberManager::processNewErrors()
{
	TDateTime nextRunTime = fLastStatusEmailDateTime +
		((double)MemberStatusEmailIntSecs()/(double)SECONDS_PER_DAY);
	TErrorLogVector allMessagesVector;
	TErrorLogVector errorsOnlyVector;
	TErrorLogVector::const_iterator iter;
	bool sendStatus = false;

	LoadErrorLogVectorByNew(allMessagesVector);
	allMessagesVector.sort();

	for(iter = allMessagesVector.begin(); iter != allMessagesVector.end(); iter++)
		if((*iter)->getLevel() == cel_Error)
			errorsOnlyVector.push_back(*iter);

	if(errorsOnlyVector.size() > 0)
	{
		sendErrorsEmail(errorsOnlyVector);
		sendStatus = true;
		nextRunTime = TDateTime::CurrentDateTime();
	}
	else if(TDateTime::CurrentDateTime() >= nextRunTime)
		sendStatus = true;

	if(sendStatus)
	{
		sendStatusEmail(allMessagesVector);
		UpdateErrorLogVectorAsProcessed(allMessagesVector,true);
		fLastStatusEmailDateTime = nextRunTime;
	}
}

/******************************************************************************/

void ASMemberManager::sendErrorsEmail(const TErrorLogVector& errorLogVector)
{
	TErrorLogPtr errorLogPtr;
	TErrorLogVector::const_iterator iter;
	TSendMailPtr sendMailPtr;
	TDateTime now = TDateTime::CurrentDateTime();
	const char* subject = "ASI Operations ERROR";
	CStrVar str;

	for(iter = errorLogVector.begin(); iter != errorLogVector.end(); iter++)
	{
		errorLogPtr = *iter;

		str.copy(errorLogPtr->getSource());
		str.concat(": ");
		str.concat(errorLogPtr->getMessage());

		// Email to SysOpEmail
		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime(now);
		sendMailPtr->setSender(TechSupportEmail());
		sendMailPtr->setRecipient(SysOpEmail());
		sendMailPtr->setSubject(subject);
		sendMailPtr->setBodyText(str);
		sendMailPtr->update();

		// Copy to TechSupportEmail
		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime(now);
		sendMailPtr->setSender(TechSupportEmail());
		sendMailPtr->setRecipient(TechSupportEmail());
		sendMailPtr->setSubject(subject);
		sendMailPtr->setBodyText(str);
		sendMailPtr->update();
	}
}

/******************************************************************************/

void ASMemberManager::sendStatusEmail(const TErrorLogVector& errorLogVector)
{
	TErrorLogPtr errorLogPtr;
	TErrorLogVector errorsOnlyVector;
	TErrorLogVector warningsOnlyVector;
	const TErrorLogVector* pErrorLogVector;
	TErrorLogVector::const_iterator iter;
	TSendMailPtr sendMailPtr;
	TDateTime now = TDateTime::CurrentDateTime();
	const char* subject = "ASI Operations Status";
	const int messageWidth = 47;
	const int messagePad = 27;
	std::vector<int> linesVector;
	int i,j,num;
	int errors,warnings,infos,unknowns;
	CStrVar bodyText;
	CStrVar leftPadSpaces;
	char tempStr[MAX(DATE_LEN,TIME_LEN)];

	errors = warnings = infos = unknowns = 0;
	for(iter = errorLogVector.begin(); iter != errorLogVector.end(); iter++)
	{
		errorLogPtr = *iter;
		if(errorLogPtr->getLevel() == cel_Error)
		{
			++errors;
			errorsOnlyVector.push_back(*iter);
		}
		else if(errorLogPtr->getLevel() == cel_Warning)
		{
			++warnings;
			warningsOnlyVector.push_back(*iter);
		}
		else if(errorLogPtr->getLevel() == cel_Info)
			++infos;
		else
			++unknowns;
	}

	bodyText.concatVarg("%4d Errors\r\n",errors);
	bodyText.concatVarg("%4d Warnings\r\n",warnings);
	bodyText.concatVarg("%4d Infos\r\n",infos);
	if(unknowns > 0)
		bodyText.concatVarg("%4d Unknowns\r\n",unknowns);

	leftPadSpaces = BuildStringFromChar(' ',messagePad);
	for(j = 0; j < 3; j++)
	{
		if(j == 0)
			pErrorLogVector = &errorsOnlyVector;
		else if(j == 1)
			pErrorLogVector = &warningsOnlyVector;
		else
			pErrorLogVector = &errorLogVector;

		if(pErrorLogVector->size() > 0)
			bodyText.concat("**************************************************\r\n");
		for(iter = pErrorLogVector->begin(); iter != pErrorLogVector->end(); iter++)
		{
			errorLogPtr = *iter;

			GetCharWordWrapLines(errorLogPtr->getMessage(),messageWidth,linesVector);

			num = MAX(linesVector.size(),2);
			for(i = 0; i < num; i++)
			{
				if(i == 0)
				{
					DateToString(ConvertTDateTimetoTDate(errorLogPtr->getDateTime()),
						tempStr,DF_MM_DD_YY,FSF_NOZERO);
					bodyText.concatVarg("%-10s",tempStr);
					bodyText.concatVarg("%-17s",errorLogPtr->getSource());
				}
				else if(i == 1)
				{
					TimeToString(ConvertTDateTimetoTTime(errorLogPtr->getDateTime()),
						tempStr,TF_HH_MM_SSA,FSF_NOZERO);
					bodyText.concatVarg("%-12s",tempStr);
					bodyText.concatVarg("%-15s",errorLogPtr->getLevel().c_str());
				}

				if(i < cast2int(linesVector.size()))
				{
					if(i >= 2)
						bodyText.concat(leftPadSpaces);

					if(i >= 1)
						bodyText.concat("  ");	// Indent lines after first line.

					bodyText.concat(GetNextWordWrapLine(errorLogPtr->getMessage(),
						linesVector,i));
				}

				bodyText.concat("\r\n");
			}
		}
	}

	if(errorLogVector.size() == 0)
	{
		bodyText.copy("No Messages");

		// Email to SysOpEmail
		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime(now);
		sendMailPtr->setSender(TechSupportEmail());
		sendMailPtr->setRecipient(SysOpEmail());
		sendMailPtr->setSubject(subject);
		sendMailPtr->setBodyText(bodyText);
		sendMailPtr->update();
	}
		
	// Copy to TechSupportEmail
	sendMailPtr = TSendMail::newInstance();
	sendMailPtr->setCreatedDateTime(now);
	sendMailPtr->setSender(TechSupportEmail());
	sendMailPtr->setRecipient(TechSupportEmail());
	sendMailPtr->setSubject(subject);
	sendMailPtr->setBodyText(bodyText);
	sendMailPtr->update();
}

/******************************************************************************/

}; //namespace asmember

/******************************************************************************/
/******************************************************************************/
