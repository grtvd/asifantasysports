/* ASBasketballHtmlObjectServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballHtmlObjectServerH
#define ASBasketballHtmlObjectServerH

#include "ASFantasyHtmlObjectServer.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballHtmlObjectServer : public ASFantasyHtmlObjectServer
{
public:
	ASBasketballHtmlObjectServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlObjectServer(pECB) {}

	static CStrVar dllName() { return("ASBkIsOb"); }
	static CStrVar commErrFileName();

protected:
	virtual void fulfillRequest(TStream& inputStream);
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballHtmlObjectServerH
/******************************************************************************/
/******************************************************************************/
