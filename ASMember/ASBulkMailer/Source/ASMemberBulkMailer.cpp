/* ASMemberBulkMailer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommErr.h"
#include "CommDB.h"
#include "SendMail.h"

#include "ASMemberAppOptions.h"
#include "ASMemberBulkMailer.h"

using namespace tag;

namespace asmember
{

/******************************************************************************/

class ASMemberBulkMailer
{
protected:
	long fLineBufferSize;
	auto_ptr<char> fLineBuffer;

public:
	ASMemberBulkMailer() : fLineBufferSize(4096),
		fLineBuffer(new char[fLineBufferSize]) {}

	void run();

protected:
	CStrVar readNextLine(FILE* fp);
	void sendMail(TMailSender& sender,std::vector<CStrVar>& recipientVector,
		TMailSubject& subject,TMailBodyText& bodyText,
		TMailAttachedFile& attachedFile);
};

/******************************************************************************/

static TSendMailVector gUnusedSendMailVector;

/******************************************************************************/
/******************************************************************************/

void DoBulkMailer()
{
	ASMemberBulkMailer bulkMailer;

	bulkMailer.run();
}

/******************************************************************************/

void ASMemberBulkMailer::run()
{
	TDatabase* db = NULL;
	FILE* fp;
	char controlFileName[MAX_PATHNAME];
	auto_ptr<char> lineBuffer(new char[4096]);

	TMailSender sender;
	std::vector<CStrVar> recipientVector;
	TMailSubject subject;
	TMailBodyText bodyText;
	TMailAttachedFile attachedFile;

	CStrVar tempStr;
	bool error = false;
		
	printf("Enter control file: ");
	scanf("%s",controlFileName);
	if((fp = fopen(controlFileName,"rt")) != NULL)
	{
		try
		{
			db = OpenDatabase(MemberMiscDatabaseName());

			sender = readNextLine(fp);

			tempStr = readNextLine(fp);
			while(tempStr.hasLen())
			{
				recipientVector.push_back(tempStr);
				tempStr = readNextLine(fp);
			}

			subject = readNextLine(fp);
			attachedFile = readNextLine(fp);

			tempStr = readNextLine(fp);
			while(tempStr.hasLen())
			{
				bodyText.concat(tempStr);
				bodyText.concat("\r\n");
				tempStr = readNextLine(fp);
			}

			sendMail(sender,recipientVector,subject,bodyText,attachedFile);
		}
		catch(...)
		{
			error = true;
		}
		CloseDatabase(db);
		fclose(fp);
	}
	else
	{
		error = true;
		tErrorMsg("ASMemberBulkMailer: fopen(%s) failed",controlFileName);
	}

	printf(error ? "Failed!\n" : "Success!\n");
}

/******************************************************************************/

CStrVar ASMemberBulkMailer::readNextLine(FILE* fp)
{
	char* eol;
	
	if(fgets(fLineBuffer.get(),fLineBufferSize,fp) != NULL)
		if((eol = strchr(fLineBuffer.get(),'\n')) != NULL)
		{
			*eol = '\0';
			return(fLineBuffer.get());
		}

	throw ASIException("readNextLine: read error (line too long?)");
}

/******************************************************************************/

void ASMemberBulkMailer::sendMail(TMailSender& sender,
	std::vector<CStrVar>& recipientVector,TMailSubject& subject,
	TMailBodyText& bodyText,TMailAttachedFile& attachedFile)
{
	TSendMailPtr sendMailPtr;
	std::vector<CStrVar>::iterator iter;

	for(iter = recipientVector.begin(); iter != recipientVector.end(); iter++)
	{
		sendMailPtr = TSendMail::newInstance();
		sendMailPtr->setCreatedDateTime();
		sendMailPtr->setSender(sender);
		sendMailPtr->setRecipient(*iter);
		sendMailPtr->setSubject(subject);
		sendMailPtr->setBodyText(bodyText);
		sendMailPtr->setAttachedFile(attachedFile);
		sendMailPtr->update();
	}
}

/******************************************************************************/

}; //namespace asmember

/******************************************************************************/
/******************************************************************************/
 
