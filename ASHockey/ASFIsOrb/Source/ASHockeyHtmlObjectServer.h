/* ASHockeyHtmlObjectServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyHtmlObjectServerH
#define ASHockeyHtmlObjectServerH

#include "ASFantasyHtmlObjectServer.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyHtmlObjectServer : public ASFantasyHtmlObjectServer
{
public:
	ASHockeyHtmlObjectServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlObjectServer(pECB) {}

	static CStrVar dllName() { return("ASHkIsOb"); }
	static CStrVar commErrFileName();

protected:
	virtual void fulfillRequest(TStream& inputStream);
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyHtmlObjectServerH
/******************************************************************************/
/******************************************************************************/
