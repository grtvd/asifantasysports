/* ASHockeyHtmlServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyHtmlServerH
#define ASHockeyHtmlServerH

#include "ASFantasyHtmlServer.h"
#include "ASHockeyHtmlPageBuilder.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyHtmlServer : public ASFantasyHtmlServer
{
protected:
	ASHockeyHtmlPageOptions fPageOptions;

public:
	ASHockeyHtmlServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlServer(pECB) {}

	static CStrVar dllName() { return("ASHkIsa"); }
	static CStrVar commErrFileName();

protected:
	virtual THtmlPageOptions& getPageOptions() { return(fPageOptions); }
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyHtmlServerH
/******************************************************************************/
/******************************************************************************/
