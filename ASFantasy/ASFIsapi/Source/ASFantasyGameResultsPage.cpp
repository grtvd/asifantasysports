/* ASFantasyGameResultsPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyGameResultsPage.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyGameResultsJavaPanelHtmlView : public TJavaPanelHtmlView
{
protected:
	CStrVar fGameDate;

public:
	ASFantasyGameResultsJavaPanelHtmlView(THtmlPageOptions& pageOptions,
		ASFantasyJavaArchive javaArchive,const char* javaClass,int javaWidth,
		int javaHeight,const char* gameDate) : TJavaPanelHtmlView(pageOptions,
		javaArchive,javaClass,javaWidth,javaHeight),fGameDate(gameDate) {}

	virtual void WriteParameters(THTMLWriter& htmlWriter);
};

/******************************************************************************/

void ASFantasyGameResultsJavaPanelHtmlView::WriteParameters(THTMLWriter& htmlWriter)
{
	if(fGameDate.hasLen())
		htmlWriter.JavaParamString("GameDate",fGameDate.c_str());
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyGameResultsPageHtmlView::initialize()
{
	fGameDate.copy(fIsHtmlServer.getStringField("GameDate",cam_MayNotExist).c_str());
}

/******************************************************************************/

void ASFantasyGameResultsPageHtmlView::writeBodyViewBody()
{
	ASFantasyGameResultsJavaPanelHtmlView htmlView(fPageOptions,fja_Season,
		"GameResultsApplet",getBodyViewWidth(),getBodyViewBodyHeight(),
		fGameDate);

	fHtmlWriter.WriteView(htmlView);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
