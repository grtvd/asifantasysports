/* ASMailListHtmlServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommDB.h"
#include "HTMLWriter.h"
#include "ASMailListHtmlServer.h"

using namespace tag;
using namespace asmember;

/******************************************************************************/

CStrVar ASMailListHtmlServer::commErrFileName()
{
	return(BuildFullFileName(ASMemberHomeDir(),"ASMailList.out"));
}

/******************************************************************************/

void ASMailListHtmlServer::formBuild()
{
	AnsiString emailString;
	TDateTime receivedDateTime;
	CStrVar source;
	CStrVar altPage;

	// open mailing list if the table is currently closed
	OpenDatabase(MemberMiscDatabaseName());

	// retrieve and verify E-mail address
	emailString = getEmailAddress();
//BOB	verifyEmailAddress(emailString);
	receivedDateTime = TDateTime::CurrentDateTime();
	source = getStringField("Source", cam_MustExist);
	altPage = getStringField("ReturnPage", cam_MayNotExist);

	// verify that E-mail address is not already present
//BOB	if (!duplicateEmailAddress( emailString ))
	saveEmailAddress( emailString.c_str(), receivedDateTime, source );

	// return 'OK' page
	transmitOKPage(altPage);
}

/******************************************************************************/

AnsiString ASMailListHtmlServer::getEmailAddress()
{
	CStrVar	emailAddress;

	// get E-mail address, remove leading and trailing spaces
	emailAddress = getStringField( "EmailEdt", cam_MustExist );
	emailAddress.compress(CSW_LEADING | CSW_TRAILING);
	return emailAddress.c_str();
}

/******************************************************************************/

void ASMailListHtmlServer::verifyEmailAddress( AnsiString emailAddress )
{
	static char *	strInvalidEmailAddress = "Invalid E-mail address";
	short	len, i;
	bool	foundAtSymbol = FALSE, foundPeriod = FALSE;

	// verify one '@' symbol, and data is both before and after '@' symbol
	len = (short) emailAddress.Length();
	for (i=1; i<=len; i++)
	{
		if (emailAddress[i] == '@')
		{
			// multiple '@' symbols - invalid address
			if (foundAtSymbol)
				throw ASIException(strInvalidEmailAddress);
			foundAtSymbol = TRUE;

			// no data before or after '@' symbol
			if ((i == 1) || (i == len))
				throw ASIException(strInvalidEmailAddress);
		}
		else if ((emailAddress[i] == '.') && foundAtSymbol)
			 foundPeriod = TRUE;
	}

	// need at least one '@' symbol
	if (!foundAtSymbol || !foundPeriod)
		throw ASIException(strInvalidEmailAddress);
}

/******************************************************************************/
#if 0	//BOB

bool ASMailListHtmlServer::duplicateEmailAddress( AnsiString emailAddress )
{
	TVarRec	key;

	key = TVarRec(emailAddress);
	return fMailListTable->FindKey( &key, 0 );
}

#endif
/******************************************************************************/

void ASMailListHtmlServer::saveEmailAddress(const char* emailAddress,
	TDateTime receivedDateTime, const char* source)
{
	TTable* table = NULL;

	try
	{
		table = OpenTable(MemberMiscDatabaseName(),ASMailListTableName);

		table->Append();
		table->FieldByName("Email")->AsString = emailAddress;
		table->FieldByName("ReceivedDateTime")->AsDateTime = receivedDateTime;
		table->FieldByName("Source")->AsString = source;
		table->FieldByName("Status")->AsString = "A";
		table->Post();
	}
	catch(const Exception& e)
	{
		CloseTable(table);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseTable(table);
		throw;
	}

	CloseTable(table);
}

/******************************************************************************/

void ASMailListHtmlServer::transmitOKPage(const char* altPage)
{
	THTMLWriter htmlWriter(fContent.get());
	bool showGeneric = true;

	DirSpec appDir;
	CStrVar fileName;

	if(tStrHasLen(altPage))
	{
		if(!appDir.SetFromParent(ASMemberHomeDir(),"ASMailList"))
			throw ASIException("ASMailListHtmlServer::transmitOKPage: SetFromParent failed");
		fileName.copyVarg("%s.html",altPage);

		htmlWriter.InsertFile(BuildFullFileName(appDir,fileName));
		showGeneric = false;
	}

	if(showGeneric)
	{
		htmlWriter.Initialize();	
		htmlWriter.Title("E-Mail Received");
		htmlWriter.Body();
		htmlWriter.Heading( 2, "E-Mail Received...Thank You" );
		htmlWriter.Finalize();
	}
}

/******************************************************************************/
/******************************************************************************/
