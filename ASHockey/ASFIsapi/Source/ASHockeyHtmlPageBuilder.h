/* ASHockeyHTMLPageBuilder.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyHtmlPageBuilderH
#define ASHockeyHtmlPageBuilderH

#include "ASFantasyHTMLPageBuilder.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

enum TASHockeyHTMLPage
{
//	htmlXXXPage = htmlASFantasyLastPage,
};

/******************************************************************************/

class ASHockeyHtmlPageOptions : public THtmlPageOptions
{
public:
	// defined in THtmlPageOptions
	virtual AnsiString getWebURLBasePath(int /*siteID*/,bool secure) const; //BOB siteID will be used when multiple WebServers are needed to support the load.
	virtual AnsiString getRootPath() const { return("/ASHockey/"); }
	virtual AnsiString getImageRootPath() const { return("Images/"); }
	virtual AnsiString getJavaRootPath() const { return("Java/"); }
	virtual AnsiString getIsapiDll() const { return("/Scripts/Secure/ASHkIsa.dll"); }
	virtual AnsiString getIsapiDllNS() const { return("/Scripts/ASHkIsa.dll"); }
	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Hockey"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFH"); }
	
	virtual CStrVar getJavaDefaultArchive(ASFantasyJavaArchive fja) const;
	virtual CStrVar getJavaRequestDll() const { return("/Scripts/ASHkIsOb.dll"); }

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
/******************************************************************************/

class ASHockeyFooterViewIcons : public ASFantasyFooterViewIcons
{
protected:
	ASHockeyFooterViewIcons(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly) : ASFantasyFooterViewIcons(pageOptions,
		showCompanyOnly) {}

public:
	static THtmlViewPtr newInstance(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly)
		{ return(new ASHockeyFooterViewIcons(pageOptions,showCompanyOnly)); }

protected:
	virtual bool hasSponsor() const { return(false); }
	virtual void writeSponsorIcon(THTMLWriter& htmlWriter);
	virtual void writeSponsorText(THTMLWriter& htmlWriter);

	virtual bool hasPlayerAssoc() const { return(false); }
	virtual void writePlayerAssocIcon(THTMLWriter& htmlWriter);
	virtual void writePlayerAssocText(THTMLWriter& htmlWriter);
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyHtmlPageBuilderH
/******************************************************************************/
/******************************************************************************/
 
