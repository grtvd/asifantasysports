/* ASPaymentProcessor.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <io.h>

#include "CommType.h"
#include "CommDB.h"
#include "QuotedTextFiler.h"

#include "ASPaymentProcessor.h"
#include "CreditCardVerify.h"
#include "ICVerifySaleResp.h"

using namespace tag;

/******************************************************************************/

// Delay time between checking for manual abort
const int	kDelayTimeMS = 100;

/******************************************************************************/

// Database information
const char *	ASParticTable = "Partic";
const char *	ASPayHistoryTable = "PayHistory";

// Authorization file information
const char* gRequestFileName = "ICVER001.REQ";
const char* gResponseFileName = "ICVER001.ANS";
const char *		RequestExtension = ".REQ";
const char *		ResponseExtension = ".ANS";

// Credit Authorization File Commands
const char *	StrSaleCommand = "C1";

// miscellaneous
const int gWaitTimeAfterCreditAuthTenths = 1;	// wait a minimum amount of time (1 tenth)
const int gWaitTimeAfterIdleTenths = 150;		// 15 seconds
const int gWaitTimeForResponseSecs = 600;		// 10 minutes

/******************************************************************************/
/******************************************************************************/

TNTService& tag::getTheNTService()
{
	static asmember::TASPaymentProcessor service;
	return(service);
}

/******************************************************************************/
/******************************************************************************/

TASPaymentProcessor::~TASPaymentProcessor()
{
	if (fResponseStream != NULL)
		delete fResponseStream;
}

/******************************************************************************/

void TASPaymentProcessor::run()
{
	TDatabase* db = NULL;
	TDateTime curDateTime;
	long waitTimeTenths;
	CStrVar excepMsg;

	try
	{
		db = OpenDatabase(MemberDatabaseName());

		if(!fPathName.SetFromParent(ASMemberHomeDir(),"PayProc"))
			throw ASIException("TASPaymentProcessor::run: SetFromParent failed");

		// build full path names to request and response files
		fRequestFilePath = BuildFullFileName(fPathName,gRequestFileName);
		fResponseFilePath = BuildFullFileName(fPathName,gResponseFileName);

		// process credit requests
		waitTimeTenths = gWaitTimeAfterIdleTenths;
		fNotify.notify(cel_Info,"Waiting for new Participants...");
		while(runWithWait(waitTimeTenths))
		{
			// error if request or response file exists
			if (fileExists(fRequestFilePath) || fileExists(fResponseFilePath))
				throw ASIException( "TASPaymentProcessor::run: Credit request/response file exists prior to authorization" );

			// set default wait time and get current system time
			waitTimeTenths = gWaitTimeAfterIdleTenths;
			curDateTime = TDateTime::CurrentDateTime();

			// find participants that need credit authorization
			if (loadCreditRequests( curDateTime ))
			{
				try
				{
					fNotify.notify(cel_Info,"New Participants found, building request file...");
					writeCreditRequests( curDateTime );
				
					fNotify.notify(cel_Info,"Waiting for response file...");
					checkCreditResponses();

					fNotify.notify(cel_Info,"Response file found, processing responses...");
					processCreditResponses();
		
					fNotify.notify(cel_Info,"Processing responses successful, cleaning up...");
					cleanup( curDateTime );
					waitTimeTenths = gWaitTimeAfterCreditAuthTenths;
				
					fNotify.notify(cel_Info,"Waiting for new Participants...");
				}
				catch(const Exception& e)
				{
					cleanup( curDateTime );
					throw ASIException(e.Message.c_str());
				}
				catch(...)
				{
					cleanup( curDateTime );
					throw;
				}
			}
		}
	}
	catch(const Exception& e)
	{
		excepMsg.copyVarg("TASPaymentProcessor::run(): Exception thrown: %s",
			e.Message.c_str());
	}
	catch(const ASIException& e)
	{
		excepMsg.copyVarg("TASPaymentProcessor::run(): ASIException thrown: %s",
			e.getMsg());
	}
	catch(const exception& e)
	{
		excepMsg.copyVarg("TASPaymentProcessor::run(): exception thrown: %s",
			e.what());
	}
	catch(...)
	{
		excepMsg.copyVarg("TASPaymentProcessor::run(): exception thrown: unknown");
	}

	CloseDatabase(db);

	if(excepMsg.hasLen())
		fNotify.notify(cel_Error,excepMsg);
	fNotify.notify(cel_Info,"Shutting down...");
}

/******************************************************************************/

bool TASPaymentProcessor::loadCreditRequests( TDateTime& transDateTime )
{
	TQuery *	pQuery = NULL;
	CStrVar		str;
	TParticPtr 	particPtr;

	try
	{
		// clear old participants
		fParticVector.erase(fParticVector.begin(),fParticVector.end());
		
		// execute query
		str.copyVarg("select * from %s where (Status = \"%s\") or "
			"((Status = \"%s\") and (GamePrice = \"0.0\")) or "
			"((Status = \"%s\") and (UpgradeStatus = \"%s\"))",
			ASParticTable,
			TParticStatus(pts_WaitingApproval).c_str(),
			TParticStatus(pts_NeedCCInfo).c_str(),
			TParticStatus(pts_Active).c_str(),
			TParticUpgradeStatus(pus_WaitingApproval).c_str());
		pQuery = OpenQuery(MemberDatabaseName(),str.c_str());

		// loop through the query results, loading participants
		pQuery->First();
		while(!pQuery->Eof)
		{
			particPtr = TPartic::newInstance();
			particPtr->load(*pQuery);

			// If game is Free, then automatically approve Partic if
			// status is pts_WaitingApproval or pts_NeedCCInfo.
			if((particPtr->getStatus() == pts_WaitingApproval) ||
				(particPtr->getStatus() == pts_NeedCCInfo))
			{
				if(particPtr->getGamePrice() == 0.0)
				{
					CommErrMsg(cel_Info,"TASPaymentProcessor::loadCreditRequests: "
						"gamePrice == 0.0, auto approving, MemberID(%s),ParticID(%s)",
						particPtr->getMemberID().c_str(),
						particPtr->getParticID().c_str());
						
					particPtr->setStatus(pts_PaymentApproved);
					particPtr->update();
				}
				else if(particPtr->getStatus() == pts_WaitingApproval)
					fParticVector.push_back(particPtr);
			}
			// Partic status is Active, processing upgrade
			else if(particPtr->getStatus() == pts_Active)
			{
				if(particPtr->getGameLevel() == gml_Premium)
					CommErrMsg(cel_Info,"TASPaymentProcessor::loadCreditRequests: validating upgrade for Premium game");

				if(particPtr->getUpgradeStatus() == pus_WaitingApproval)
				{
					if(particPtr->getUpgradePrice() == 0.0)
					{
						CommErrMsg(cel_Info,"TASPaymentProcessor::loadCreditRequests: "
							"upgradePrice == 0.0, auto approving, MemberID(%s),ParticID(%s)",
							particPtr->getMemberID().c_str(),
							particPtr->getParticID().c_str());
						
						particPtr->setGameLevel(gml_Premium);
						particPtr->setUpgradeStatus(pus_PaymentApproved);
						particPtr->update();
					}
					else
						fParticVector.push_back(particPtr);
				}
				else
					throw ASIException("TASPaymentProcessor::loadCreditRequests: invalid upgrade status");
			}
			else
				throw ASIException("TASPaymentProcessor::loadCreditRequests: invalid status");
				
			pQuery->Next();
		}

		// discard query
		CloseQuery( pQuery );
	}
	catch(const Exception& e)
	{
		CloseQuery( pQuery );
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery( pQuery );
		throw;
	}

	// indicate whether any requests were written
	return ((fParticVector.size() > 0) ? TRUE : FALSE);
}

/******************************************************************************/

void TASPaymentProcessor::writeCreditRequests( TDateTime& transDateTime )
{
	auto_ptr<TFileStream>		reqStream;
	auto_ptr<TFileStream>		backupStream;
	auto_ptr<TQuotedTextFiler>	textFiler;
	auto_ptr<TICVerifySaleRqst>	request;

	TMemberPtr		memberPtr;
	TPayHistoryPtr	payHistoryPtr;
	long			bytesCopied;

	// clear old pay history
	fPayHistoryVector.erase(fPayHistoryVector.begin(),fPayHistoryVector.end());

	// create request file
	backupStream.reset(new TFileStream( getRequestBackupFileName(transDateTime).c_str(),
		fmCreate | fmShareExclusive ));
	textFiler.reset(new TQuotedTextFiler( backupStream.get(), FALSE ));
	request.reset(new TICVerifySaleRqst);

	// add each request to the file
	for (TParticVector::iterator iter=fParticVector.begin();
		iter!=fParticVector.end(); iter++)
	{
		// find member information in database
		memberPtr = TMember::createGet( (*iter)->getMemberID(), cam_MustExist );
		fillAuthRequest( request.get(), (*iter), memberPtr );

		// allocate pay history record
		payHistoryPtr = TPayHistory::newInstance();
		fillPayHistoryRequest( payHistoryPtr, request.get(), (*iter), memberPtr,
			transDateTime );
		payHistoryPtr->update();
		fPayHistoryVector.push_back(payHistoryPtr);

		// write request to file
		request->writeToFiler( *textFiler );
		textFiler->writeEOL();
	}

	// copy backup to actual request file
	reqStream.reset(new TFileStream( fRequestFilePath.c_str(), fmCreate | fmShareExclusive ));
	bytesCopied = reqStream->CopyFrom( backupStream.get(), 0 );
	
	if(bytesCopied != backupStream->Size)
		CommErrMsg(cel_Error,"TASPaymentProcessor::writeCreditRequests: "
			"bytesCopied(%ld) != backupStream->Size(%ld)",bytesCopied,
			backupStream->Size);
}

/******************************************************************************/

void TASPaymentProcessor::fillAuthRequest( TICVerifySaleRqst * request,
	TParticPtr particPtr, TMemberPtr memberPtr )
{
	CStr31 buf;

	// fill in request
	request->clear();
	request->setSaleCommand( StrSaleCommand );
	buf.CopyVarg("%s:%s", memberPtr->getMemberID().c_str(),
		particPtr->getParticID().c_str() );
	request->setComment( buf.c_str() );
	request->setCardNumber( memberPtr->getCCardNumber() );
	request->setCardExpDate( memberPtr->getCCardExpDate() );

	if((particPtr->getStatus() == pts_Active) &&
			(particPtr->getUpgradeStatus() == pus_WaitingApproval))
		request->setAmount( particPtr->getUpgradePrice() );
	else if(particPtr->getStatus() == pts_WaitingApproval)
		request->setAmount( particPtr->getGamePrice() );
	else
		throw ASIException("TASPaymentProcessor::fillAuthRequest: status mismatch");

	request->setAddrZip( memberPtr->getAddrZip() );
	request->setAddrStreet1( memberPtr->getAddrStreet1() );
}

/******************************************************************************/

void TASPaymentProcessor::fillPayHistoryRequest( TPayHistoryPtr payHistoryPtr,
	TICVerifySaleRqst * request, TParticPtr particPtr, TMemberPtr memberPtr,
	TDateTime& transDateTime )
{
	payHistoryPtr->setMemberID( memberPtr->getMemberID() );
	payHistoryPtr->setTransDateTime( transDateTime );
	payHistoryPtr->setParticID( particPtr->getParticID() );
	payHistoryPtr->setGameID( particPtr->getGameID() );
	payHistoryPtr->setCCardType( memberPtr->getCCardType() );
	payHistoryPtr->setCCardNumber( memberPtr->getCCardNumber() );
	payHistoryPtr->setCCardExpDate( memberPtr->getCCardExpDate() );
	payHistoryPtr->setCCardNameOn( memberPtr->getCCardNameOn() );
	payHistoryPtr->setSaleCommand( request->getSaleCommand() );
	payHistoryPtr->setClerk( request->getClerk() );
	payHistoryPtr->setComment( request->getComment() );
	payHistoryPtr->setAmount( request->getAmount() );
}

/******************************************************************************/

void TASPaymentProcessor::checkCreditResponses()
{
	// initialize
	if (fResponseStream != NULL)
	{
		delete fResponseStream;
		fResponseStream = NULL;
	}

	// wait until output file opened
	waitForEvent(gWaitTimeForResponseSecs,
		&(TASPaymentProcessor::openResponseFile));

	// timed out waiting for a response
	if (fResponseStream == NULL)
		throw ASIException( "TASPaymentProcessor::checkCreditResponses: Credit response not received" );
}

/******************************************************************************/

bool TASPaymentProcessor::fileExists(const char* fileName)
{
	return (access(fileName,0) == 0);
}

/******************************************************************************/

bool TASPaymentProcessor::openResponseFile()
{
	bool	responseFileOpen = FALSE;

	// attempt to open the response file with exclusive access
	try
	{
		if(fileExists(fResponseFilePath))
		{
			fResponseStream = new TFileStream( fResponseFilePath.c_str(),
				fmOpenRead | fmShareExclusive );
			responseFileOpen = TRUE;
		}
	}

	// not a fatal error if response file is not available, just try again shortly
	catch(...)
	{
		fResponseStream = NULL;
	}

	return (responseFileOpen);
}

/******************************************************************************/

void TASPaymentProcessor::processCreditResponses()
{
	auto_ptr<TQuotedTextFiler>	textFiler;
	auto_ptr<TICVerifySaleResp>	response;

	try
	{
		textFiler.reset(new TQuotedTextFiler( fResponseStream, FALSE ));
		response.reset(new TICVerifySaleResp);

		// verify that both vectors are the same size
		if (fParticVector.size() != fPayHistoryVector.size())
			throw ASIException("TASPaymentProcessor::processCreditResponses: Array size mismatch for participant and pay history vectors");
		
		TParticVector::iterator particIter=fParticVector.begin();
		TPayHistoryVector::iterator historyIter=fPayHistoryVector.begin();
		for (; (particIter!=fParticVector.end()) && (historyIter!=fPayHistoryVector.end());
			particIter++, historyIter++)
		{
			// read response from file, some errors include 3 extra fields
			response->readFromFiler( *textFiler );
			if(!textFiler->isEOL())
			{
				textFiler->readString();
				textFiler->readString();
				textFiler->readString();
			}
			textFiler->readEOL();

			// set status of credit auth and update database
			if(((*particIter)->getStatus() == pts_Active) &&
				((*particIter)->getUpgradeStatus() == pus_WaitingApproval))
			{
				if((*particIter)->getGameLevel() == gml_Premium)
					CommErrMsg(cel_Info,"TASPaymentProcessor::processCreditResponses: "
						"validating upgrade for Premium game");

				if(response->isApproved())
				{
					(*particIter)->setGameLevel(gml_Premium);
					(*particIter)->setUpgradeStatus(pus_PaymentApproved);
				}
				else
					(*particIter)->setUpgradeStatus(pus_PaymentDenied);
			}
			else if((*particIter)->getStatus() == pts_WaitingApproval)
			{
				(*particIter)->setStatus( (response->isApproved()) ? pts_PaymentApproved :
					pts_PaymentDenied );

				CommErrMsg(cel_Info,"TASPaymentProcessor::processCreditResponses: "
					"Response(%s),MemberID(%s),ParticID(%s)",
						response->getResponse(),
						(*particIter)->getMemberID().c_str(),
						(*particIter)->getParticID().c_str());
			}
			else
				throw ASIException("TASPaymentProcessor::processCreditResponses: status mismatch");
			(*particIter)->update(dsrum_AlwaysUpdate);

			// update pay history
			(*historyIter)->setApproved( response->isApproved() );
			(*historyIter)->setResponse( response->getResponse() );
			(*historyIter)->update();
		}

		// verify that both iterators are done
		if ((particIter!=fParticVector.end()) || (historyIter!=fPayHistoryVector.end()))
			throw ASIException("TASPaymentProcessor::processCreditResponses: Array size mismatch for participant and pay history vectors (Iterator)");

		delete fResponseStream;
		fResponseStream = NULL;
	}
	catch(const Exception& e)
	{
		delete fResponseStream;
		fResponseStream = NULL;
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		delete fResponseStream;
		fResponseStream = NULL;
		throw;
	}
}

/******************************************************************************/

void TASPaymentProcessor::cleanup( TDateTime& transDateTime )
{
	// delete participants
	fParticVector.erase(fParticVector.begin(),fParticVector.end());
	fPayHistoryVector.erase(fPayHistoryVector.begin(),fPayHistoryVector.end());

	// rename response file
	if(rename( fResponseFilePath, getResponseBackupFileName(transDateTime).c_str() ))
		CommErrMsg(cel_Error,"TASPaymentProcessor::cleanup: Error renaming "
			"response file (errno=%d)",errno);
}

/******************************************************************************/

CStrVar TASPaymentProcessor::getAuthBaseName( const TDateTime& transDateTime )
{
	return(FormatDateTimeStr(transDateTime,"yyyymmdd'-'hhmmss"));
}

/******************************************************************************/

CStrVar TASPaymentProcessor::getBackupFileName( const TDateTime& transDateTime,
	const char* ext )
{
	CStrVar baseFileName;
	
	baseFileName.copy(getAuthBaseName(transDateTime));
	baseFileName.concat(ext);
	
	return(BuildFullFileName(fPathName,baseFileName));
}

/******************************************************************************/

CStrVar TASPaymentProcessor::getRequestBackupFileName(
	const TDateTime& transDateTime)
{
	return(getBackupFileName(transDateTime,RequestExtension));
}

/******************************************************************************/

CStrVar TASPaymentProcessor::getResponseBackupFileName(
	const TDateTime& transDateTime)
{
	return(getBackupFileName(transDateTime,ResponseExtension));
}

/******************************************************************************/

bool TASPaymentProcessor::waitForEvent( long waitTimeSecs,
	waitEventCallback callBack)
{
	TTick startTick;

	// calculate timeout point
	startTick = tGetTickCount();

	// loop until event occurs or time out
	while(runWithWait(1))
	{
		// check for event
		if (callBack != NULL)
			if ((this->*callBack)())
				return (TRUE);

		if(tHaveSecsPast(startTick,waitTimeSecs))
			break;
	}

	return (FALSE);
}

/******************************************************************************/
/******************************************************************************/
