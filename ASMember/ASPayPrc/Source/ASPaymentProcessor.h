/* ASPaymentProcessor.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASPaymentProcessorH
#define ASPaymentProcessorH

#include <stdexcep.h>
#include "CommType.h"
#include "NTService.h"

#include "ASMemberType.h"
#include "ICVerifySaleRqst.h"

using namespace std;

namespace asmember
{

/******************************************************************************/

class TASPaymentProcessor;
typedef bool (TASPaymentProcessor::*waitEventCallback)();

/******************************************************************************/

class TASPaymentProcessor : public TNTService
{
protected:
	TFileStream *			fResponseStream;
	DirSpec					fPathName;			// path to request/response file loc
	CStrVar					fRequestFilePath;	// full path name of request file
	CStrVar					fResponseFilePath;	// full path name of response file
	TParticVector			fParticVector;		// list of participants being processd
	TPayHistoryVector		fPayHistoryVector;	// pay history database references

public:
	TASPaymentProcessor() : TNTService("ASMember PayProc Service"),
		fResponseStream(NULL) {}
	virtual ~TASPaymentProcessor();

	static TASPaymentProcessor& getThe()
		{ return(dynamic_cast<TASPaymentProcessor&>(TNTService::getThe())); }

protected:
	virtual void run();
	//#if defined(TEST_SERVICE)
	//virtual DWORD runIdleWaitTenths() { return(1); }
	//#endif

	bool loadCreditRequests( TDateTime& transDateTime );
	void writeCreditRequests( TDateTime& transDateTime );
	void fillAuthRequest( TICVerifySaleRqst * request, TParticPtr particPtr,
		TMemberPtr memberPtr );
	void fillPayHistoryRequest( TPayHistoryPtr payHistoryPtr,
		TICVerifySaleRqst * request, TParticPtr particPtr, TMemberPtr memberPtr,
		TDateTime& transDateTime );
	void checkCreditResponses();
	bool fileExists(const char* fileName);
	bool openResponseFile();
	void processCreditResponses();
	void cleanup( TDateTime& transDateTime );
	
	CStrVar getAuthBaseName( const TDateTime& transDateTime );
	CStrVar getBackupFileName( const TDateTime& transDateTime, const char* ext );
	CStrVar getRequestBackupFileName( const TDateTime& transDateTime );
	CStrVar getResponseBackupFileName( const TDateTime& transDateTime );

	bool waitForEvent(long waitTimeSecs, waitEventCallback callBack);
};

/******************************************************************************/

}; //namespace asmember

#endif //ASPaymentProcessorH
/******************************************************************************/
/******************************************************************************/

