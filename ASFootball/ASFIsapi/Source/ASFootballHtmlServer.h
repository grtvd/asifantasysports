/* ASFootballHtmlServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballHtmlServerH
#define ASFootballHtmlServerH

#include "ASFantasyHtmlServer.h"
#include "ASFootballHtmlPageBuilder.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballHtmlServer : public ASFantasyHtmlServer
{
protected:
	ASFootballHtmlPageOptions fPageOptions;
	
public:
	ASFootballHtmlServer(LPEXTENSION_CONTROL_BLOCK pECB) :
		ASFantasyHtmlServer(pECB) {}

	static CStrVar dllName() { return("ASFbIsa"); }
	static CStrVar commErrFileName();

protected:
	virtual THtmlPageOptions& getPageOptions() { return(fPageOptions); }

	virtual ASFantasyBasePageHtmlViewPtr createNewPage(int htmlPage,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballHtmlServerH
/******************************************************************************/
/******************************************************************************/
