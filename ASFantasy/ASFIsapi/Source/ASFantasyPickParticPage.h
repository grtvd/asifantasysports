/* ASFantasyPickParticPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyPickParticPageH
#define ASFantasyPickParticPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyPickParticPageHtmlView : public ASFantasyBasePageHtmlView
{
protected:
	const TParticVector& fParticVector;
	
protected:
	ASFantasyPickParticPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,
		const TParticVector& particVector) :
		ASFantasyBasePageHtmlView(isHtmlServer,pageOptions,htmlWriter),
		fParticVector(particVector) {}
	
	virtual CStrVar getPageTitle(void) const { return("Pick Participant"); }
	virtual void writeBodyView();
	virtual bool showFooterView() const { return(false); }

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyPickParticPageH
/******************************************************************************/
/******************************************************************************/
