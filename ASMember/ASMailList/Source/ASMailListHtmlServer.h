/* ASMailListHtmlServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASMailListHtmlServerH
#define ASMailListHtmlServerH

#include "IsHttpServer.h"
#include "ASMemberAppOptions.h"

using namespace tag;

namespace asmember
{

/******************************************************************************/

const char * ASMailListTableName = "MailList";

/******************************************************************************/

class ASMailListHtmlServer : public IsHtmlServer
{
public:
	/* constructor / destructor */
	ASMailListHtmlServer(LPEXTENSION_CONTROL_BLOCK EcbPtr) : IsHtmlServer(EcbPtr) {}
	virtual ~ASMailListHtmlServer() {}
	static CStrVar dllName() { return ("ASMailList"); }
	static CStrVar commErrFileName();

	virtual CStrVar getTechSupportPhoneNumber() const { return(TechSupportPhoneNumber()); }
	virtual CStrVar getTechSupportFaxNumber() const { return(TechSupportFaxNumber()); }
	virtual CStrVar getTechSupportName() const { return(TechSupportName()); }
	virtual CStrVar getTechSupportEmail() const { return(TechSupportEmail()); }
	
	/* Page building routines */
	virtual void formBuild();

protected:
	AnsiString getEmailAddress();
	void verifyEmailAddress( AnsiString emailAddress );
//BOB	bool		duplicateEmailAddress( AnsiString emailAddress );
	void saveEmailAddress(const char* emailAddress, TDateTime receivedDateTime,
		const char* source);
	void transmitOKPage(const char* altPage);
};

/******************************************************************************/

}; //namespace asmember

#endif	//ASMailListHtmlServerH
/******************************************************************************/
/******************************************************************************/

