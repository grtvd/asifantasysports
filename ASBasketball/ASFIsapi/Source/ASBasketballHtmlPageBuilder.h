/* ASBasketballHTMLPageBuilder.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballHtmlPageBuilderH
#define ASBasketballHtmlPageBuilderH

#include "ASFantasyHTMLPageBuilder.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

enum TASBasketballHTMLPage
{
//	htmlXXXPage = htmlASFantasyLastPage,
};

/******************************************************************************/

class ASBasketballHtmlPageOptions : public THtmlPageOptions
{
public:
	// defined in THtmlPageOptions
	virtual AnsiString getWebURLBasePath(int /*siteID*/,bool secure) const; //BOB siteID will be used when multiple WebServers are needed to support the load.
	virtual AnsiString getRootPath() const { return("/ASBasketball/"); }
	virtual AnsiString getImageRootPath() const { return("Images/"); }
	virtual AnsiString getJavaRootPath() const { return("Java/"); }
	virtual AnsiString getIsapiDll() const { return("/Scripts/Secure/ASBkIsa.dll"); }
	virtual AnsiString getIsapiDllNS() const { return("/Scripts/ASBkIsa.dll"); }
	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Basketball"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFB"); }
	
	virtual CStrVar getJavaDefaultArchive(ASFantasyJavaArchive fja) const;
	virtual CStrVar getJavaRequestDll() const { return("/Scripts/ASBkIsOb.dll"); }

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

class ASBasketballFooterViewIcons : public ASFantasyFooterViewIcons
{
protected:
	ASBasketballFooterViewIcons(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly) : ASFantasyFooterViewIcons(pageOptions,
		showCompanyOnly) {}

public:
	static THtmlViewPtr newInstance(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly)
		{ return(new ASBasketballFooterViewIcons(pageOptions,showCompanyOnly)); }

protected:
	virtual bool hasSponsor() const { return(false); }
	virtual void writeSponsorIcon(THTMLWriter& htmlWriter);
	virtual void writeSponsorText(THTMLWriter& htmlWriter);

	virtual bool hasPlayerAssoc() const { return(false); }
	virtual void writePlayerAssocIcon(THTMLWriter& htmlWriter);
	virtual void writePlayerAssocText(THTMLWriter& htmlWriter);
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballHtmlPageBuilderH
/******************************************************************************/
/******************************************************************************/
 
