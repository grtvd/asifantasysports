/* ASFantasyHtmlServer.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyHtmlServerH
#define ASFantasyHtmlServerH

#include "IsHttpServer.h"
#include "HtmlWriter.h"

#include "ASFantasyHtmlPageBuilder.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class ASFantasyHtmlServer : public IsHtmlServer
{
public:
	ASFantasyHtmlServer(LPEXTENSION_CONTROL_BLOCK pECB) : IsHtmlServer(pECB) {}
	virtual ~ASFantasyHtmlServer();

	virtual void buildPage(const char* pageName);
	
protected:
	virtual THtmlPageOptions& getPageOptions() = 0;

	virtual ASFantasyBasePageHtmlViewPtr createMessagePage(
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,const bool isError,
		const char* message);
	virtual ASFantasyBasePageHtmlViewPtr createNewPage(int htmlPage,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter);
	
private:
	void setUpPageOptions();
	void determineGameView();
	bool determineRqstPartic(THTMLWriter& htmlWriter);
	bool determineRqstParticActive(THTMLWriter& htmlWriter);
	void buildMemberParticMismatchPage(THTMLWriter& htmlWriter);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyHtmlServerH
/******************************************************************************/
/******************************************************************************/
