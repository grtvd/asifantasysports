/* ASBasketballHtmlServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballHtmlServerH
#define ASBasketballHtmlServerH

#include "ASFantasyHtmlServer.h"
#include "ASBasketballHtmlPageBuilder.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballHtmlServer : public ASFantasyHtmlServer
{
protected:
	ASBasketballHtmlPageOptions fPageOptions;

public:
	ASBasketballHtmlServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlServer(pECB) {}

	static CStrVar dllName() { return("ASBkIsa"); }
	static CStrVar commErrFileName();

protected:
	virtual THtmlPageOptions& getPageOptions() { return(fPageOptions); }
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballHtmlServerH
/******************************************************************************/
/******************************************************************************/
