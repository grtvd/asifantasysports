/* ASBaseballHtmlObjectServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballHtmlObjectServerH
#define ASBaseballHtmlObjectServerH

#include "ASFantasyHtmlObjectServer.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballHtmlObjectServer : public ASFantasyHtmlObjectServer
{
public:
	ASBaseballHtmlObjectServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlObjectServer(pECB) {}

	static CStrVar dllName() { return("ASBbIsOb"); }
	static CStrVar commErrFileName();

protected:
	virtual void fulfillRequest(TStream& inputStream);
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballHtmlObjectServerH
/******************************************************************************/
/******************************************************************************/
