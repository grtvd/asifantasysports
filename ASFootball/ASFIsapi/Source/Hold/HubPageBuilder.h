/* HubPageBuilder.h */

/******************************************************************************/
/******************************************************************************/
#ifndef HubPageBuilderH
#define HubPageBuilderH

#include "ASFootballHTMLPageBuilder.h"

/******************************************************************************/

class THubLineItemHtmlView : public TPageOptionsHtmlView
{
public:
	THubLineItemHtmlView(THtmlPageOptions& pageOptions) : 
		TPageOptionsHtmlView(pageOptions) {}
		
	virtual bool show() throw(Exception) { return(true); }
};

/******************************************************************************/

class HubRightPanelHtmlView : public TTypeAlphaRightPanelHtmlView
{
protected:
	bool fAnyInvolvedTradeMessages;

public:               
	HubRightPanelHtmlView(THtmlPageOptions& pageOptions) :
		TTypeAlphaRightPanelHtmlView(pageOptions,tt_None,550,
			"Front Office",""), fAnyInvolvedTradeMessages(false) {}

protected:
	void writeItemRow(THubLineItemHtmlView& lineItemHtmlView,THTMLWriter& htmlWriter);
	bool buildParticStatusMessages(THTMLWriter& htmlWriter) throw(Exception);
	void buildDraftMessages(THTMLWriter& htmlWriter);
	void buildSeasonMessages(THTMLWriter& htmlWriter);

	void buildMyTradeMessages(THTMLWriter& htmlWriter,TTradeVector& tradeVector);
	void buildOtherTradeMessages(THTMLWriter& htmlWriter,TTradeVector& tradeVector);
	void buildTradeMessages(THTMLWriter& htmlWriter);
	
	virtual void writeContentView(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class HubBodyHTMLView : public TFootballTypeAlphaBodyHTMLView
{
protected:
	HubRightPanelHtmlView fRightPanel;
	
public:               
	HubBodyHTMLView(THtmlPageOptions& pageOptions) :
		TFootballTypeAlphaBodyHTMLView(pageOptions), fRightPanel(pageOptions) {}

protected:
	virtual void writeRightPanelView(THTMLWriter& htmlWriter)
		{ fRightPanel.Write(htmlWriter); }
};

/******************************************************************************/

class HubPageHTMLView : public TFootballTypeAlphaPageHTMLView
{
	HubBodyHTMLView fBodyView;
	
public:		      
	HubPageHTMLView(THtmlPageOptions& pageOptions) :
		TFootballTypeAlphaPageHTMLView(pageOptions), fBodyView(pageOptions) {}
	
protected:
	virtual AnsiString getPageTitle(void) const { return("Hub"); }
	
	virtual void writeBodyView(THTMLWriter& htmlWriter)
		{ fBodyView.Write(htmlWriter); }
};


#endif
/******************************************************************************/
/******************************************************************************/
 
