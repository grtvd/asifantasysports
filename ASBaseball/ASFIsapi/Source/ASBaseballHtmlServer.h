/* ASBaseballHtmlServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballHtmlServerH
#define ASBaseballHtmlServerH

#include "ASFantasyHtmlServer.h"
#include "ASBaseballHtmlPageBuilder.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballHtmlServer : public ASFantasyHtmlServer
{
protected:
	ASBaseballHtmlPageOptions fPageOptions;
	
public:
	ASBaseballHtmlServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlServer(pECB) {}
	
	static CStrVar dllName() { return("ASBbIsa"); }
	static CStrVar commErrFileName();

protected:
	virtual THtmlPageOptions& getPageOptions() { return(fPageOptions); }
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballHtmlServerH
/******************************************************************************/
/******************************************************************************/
