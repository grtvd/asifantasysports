/* ASMemberManager.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASMemberManagerH
#define ASMemberManagerH

#include "ErrorLog.h"
#include "NTService.h"

using namespace tag;

namespace asmember
{

/******************************************************************************/

class ASMemberManager : public TNTService
{
protected:
	CStrVarVector fCommErrFileList;
	TDateTime fLastStatusEmailDateTime;
	TDateTime fLastEmailSendFailedDateTime;

protected:
	ASMemberManager() : TNTService("ASMember Manager Service") {}
public:
	virtual ~ASMemberManager() {}

	static ASMemberManager& getThe()
		{ return(dynamic_cast<ASMemberManager&>(TNTService::getThe())); }

	void run();
	#if defined(TEST_SERVICE)
	virtual DWORD runIdleWaitTenths() { return(1); }
	#endif

protected:
	void backupDatabase();
	void doMiscProcessing();

	void sendNewEmails();
	void loadCommErrFiles();
	void processNewErrors();
	void sendErrorsEmail(const TErrorLogVector& errorLogVector);
	void sendStatusEmail(const TErrorLogVector& errorLogVector);

	friend TNTService& tag::getTheNTService();
};

/******************************************************************************/

}; //namespace asmember

#endif //ASMemberManagerH
/******************************************************************************/
/******************************************************************************/
