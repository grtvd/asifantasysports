/* ASFantasyHtmlObjectServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyHtmlObjectServerH
#define ASFantasyHtmlObjectServerH

#include "IsHttpServer.h"
#include "FulfillerNotify.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class TASFantasyFulfillerNotify : public TFulfillerNotify
{
public:
	virtual void notify(const AnsiString &msg);
};

/******************************************************************************/

class ASFantasyHtmlObjectServer : public IsHtmlServer
{
protected:
	static TDateTime fLastStatLoadDate;
	static bool fStoreIsSetup;
	
public:
	ASFantasyHtmlObjectServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		IsHtmlServer(pECB) {}
	virtual ~ASFantasyHtmlObjectServer();

	virtual void formBuild();
	
protected:
	void setup();
	virtual void addAllShelves();
	virtual void delAllShelves();
	virtual void loadAllShelves();

	virtual void fulfillRequest(TStream& inputStream) = 0;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyHtmlObjectServerH
/******************************************************************************/
/******************************************************************************/
