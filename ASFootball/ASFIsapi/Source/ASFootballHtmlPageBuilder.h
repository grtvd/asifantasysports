/* ASFootballHTMLPageBuilder.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballHtmlPageBuilderH
#define ASFootballHtmlPageBuilderH

#include "ASFantasyHTMLPageBuilder.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

enum TASFootballHTMLPage
{
//	htmlXXXPage = htmlASFantasyLastPage,
};

/******************************************************************************/

class ASFootballHtmlPageOptions : public THtmlPageOptions
{
public:
	// defined in THtmlPageOptions
	virtual AnsiString getWebURLBasePath(int /*siteID*/,bool secure) const; //BOB siteID will be used when multiple WebServers are needed to support the load.
	virtual AnsiString getRootPath() const { return("/ASFootball/"); }
	virtual AnsiString getImageRootPath() const { return("Images/"); }
	virtual AnsiString getJavaRootPath() const { return("Java/"); }
	virtual AnsiString getIsapiDll() const { return("/Scripts/Secure/ASFbIsa.dll"); }
	virtual AnsiString getIsapiDllNS() const { return("/Scripts/ASFbIsa.dll"); }
	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Football"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFF"); }
	
	virtual CStrVar getJavaDefaultArchive(ASFantasyJavaArchive fja) const;
	virtual CStrVar getJavaRequestDll() const { return("/Scripts/ASFbIsOb.dll"); }

	virtual int getTypeAlphaPageWidth() const { return(765); }
	virtual int getTypeAlphaIconNavColWidth() const { return(135); }
	
	virtual const THTMLPageLinkInfo& getPageLinkInfo(int htmlPage) const;
	virtual int getPageLinkInfoEnum(const AnsiString& pageName) const;

	virtual CStrVar getStandardImageName(const int standardImage) const;
	virtual CStrVar getStandardImageRootPath(const int standardImage) const;

	virtual void loadHeaderViewNavButtonBarArray(
		vector<vector<int> >& htmlPageArray);

	virtual THtmlViewPtr getFooterViewIconsHtmlView(const bool showCompanyOnly);
};

/******************************************************************************/
#if 0	//BOB

// Builds the Season column of TIconNavHTMLViews.

class TSeasonIconNavColumnHTMLView : public TIconNavColumnHTMLView
{
	const THtmlPageOptions& fPageOptions;

public:
	TSeasonIconNavColumnHTMLView(const THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}

	static void Build(THTMLWriter& htmlWriter,const THtmlPageOptions& pageOptions);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Builds the Draft column of TIconNavHTMLViews.

class TDraftIconNavColumnHTMLView : public TIconNavColumnHTMLView
{
	const THtmlPageOptions& fPageOptions;

public:
	TDraftIconNavColumnHTMLView(const THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}

	static void Build(THTMLWriter& htmlWriter,const THtmlPageOptions& pageOptions);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds the Season Remote Control.

class TSeasonRemoteControlHtmlView : public TPageOptionsHtmlView
{
public:
	TSeasonRemoteControlHtmlView(THtmlPageOptions& pageOptions) :
		TPageOptionsHtmlView(pageOptions) {}

	static void Build(THTMLWriter& htmlWriter,THtmlPageOptions& pageOptions);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Builds the Draft Remote Control.

class TDraftRemoteControlHtmlView : public TPageOptionsHtmlView
{
public:
	TDraftRemoteControlHtmlView(THtmlPageOptions& pageOptions) :
		TPageOptionsHtmlView(pageOptions) {}

	static void Build(THTMLWriter& htmlWriter,THtmlPageOptions& pageOptions);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds the Season footer line of TTextNavHTMLViews.

class TSeasonTextNavLineHTMLView : public THTMLView
{
	const THtmlPageOptions& fPageOptions;

public:
	TSeasonTextNavLineHTMLView(const THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}

	static void Build(THTMLWriter& htmlWriter,const THtmlPageOptions& pageOptions);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Builds the Draft footer line of TTextNavHTMLViews.

class TDraftTextNavLineHTMLView : public THTMLView
{
	const THtmlPageOptions& fPageOptions;

public:
	TDraftTextNavLineHTMLView(const THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}

	static void Build(THTMLWriter& htmlWriter,const THtmlPageOptions& pageOptions);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds Season/Draft TIconNavColumnHTMLView.

class TFootballIconNavColumnHTMLView : public TIconNavColumnHTMLView
{
	const THtmlPageOptions& fPageOptions;
	
public:
	TFootballIconNavColumnHTMLView(const THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}
	
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds Season/Draft TRemoteControlHTMLView.

class TFootballRemoteControlHtmlView : public TPageOptionsHtmlView
{
public:
	TFootballRemoteControlHtmlView(THtmlPageOptions& pageOptions) :
		TPageOptionsHtmlView(pageOptions) {}
	
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds Season/Draft TextNavLineHTMLView.

class TFootballTextNavLineHTMLView : public THTMLView
{
	const THtmlPageOptions& fPageOptions;

public:
	TFootballTextNavLineHTMLView(const THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}
	
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

class TFootballTypeAlphaBodyHTMLView : public TTypeAlphaDefaultBodyHTMLView
{
//	TFootballIconNavColumnHTMLView fLeftPanelView;
	TFootballRemoteControlHtmlView fLeftPanelView;

public:
	TFootballTypeAlphaBodyHTMLView(THtmlPageOptions& pageOptions) :
		TTypeAlphaDefaultBodyHTMLView(pageOptions),
		fLeftPanelView(pageOptions) {}
		
	virtual void writeLeftPanelView(THTMLWriter& htmlWriter)
		{ fLeftPanelView.Write(htmlWriter); }
};

/******************************************************************************/
/******************************************************************************/

class TFootballTypeAlphaPageHTMLView : public TTypeAlphaPageHTMLView
{
	TFootballTextNavLineHTMLView fFooterView;

public:		
	TFootballTypeAlphaPageHTMLView(THtmlPageOptions& pageOptions) :
		TTypeAlphaPageHTMLView(pageOptions),fFooterView(pageOptions) {}
	
protected:
	virtual void writeFooterView(THTMLWriter& htmlWriter);
};

#endif	//BOB
/******************************************************************************/
/******************************************************************************/

class ASFootballFooterViewIcons : public ASFantasyFooterViewIcons
{
protected:
	ASFootballFooterViewIcons(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly) : ASFantasyFooterViewIcons(pageOptions,
		showCompanyOnly) {}

public:
	static THtmlViewPtr newInstance(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly)
		{ return(new ASFootballFooterViewIcons(pageOptions,showCompanyOnly)); }

protected:
	virtual bool hasSponsor() const { return(false); }
	virtual void writeSponsorIcon(THTMLWriter& htmlWriter);
	virtual void writeSponsorText(THTMLWriter& htmlWriter);

	virtual bool hasPlayerAssoc() const { return(true); }
	virtual void writePlayerAssocIcon(THTMLWriter& htmlWriter);
	virtual void writePlayerAssocText(THTMLWriter& htmlWriter);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballHtmlPageBuilderH
/******************************************************************************/
/******************************************************************************/
 
