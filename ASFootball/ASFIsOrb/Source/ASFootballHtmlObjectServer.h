/* ASFootballHtmlObjectServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballHtmlObjectServerH
#define ASFootballHtmlObjectServerH

#include "ASFantasyHtmlObjectServer.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballHtmlObjectServer : public ASFantasyHtmlObjectServer
{
public:
	ASFootballHtmlObjectServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlObjectServer(pECB) {}

	static CStrVar dllName() { return("ASFbIsOb"); }
	static CStrVar commErrFileName();

protected:
	virtual void addAllShelves();
	virtual void delAllShelves();
	virtual void loadAllShelves();

	virtual void fulfillRequest(TStream& inputStream);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballHtmlObjectServerH
/******************************************************************************/
/******************************************************************************/
