/* ASFantasyHtmlPageBuilder.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyHtmlPageBuilderH
#define ASFantasyHtmlPageBuilderH

/******************************************************************************/
// Defines in Project Options - Conditionals (DO NOT DEFINE HERE)
//LOCALWEB			- Links .HTML files instead of Iaspi DLL queries
//SHOW_PROTOTYPE	- Used to show GIFs in place of Java Applets

// Used to show table borders that are normally not shown.
#define SHOW_BORDER		0		// 0 or 1

#if !defined(LOCALWEB) && (SHOW_BORDER != 0)
#error SHOW_BORDER must not be set for production!
#endif
//#undef SHOW_BORDER
//#define SHOW_BORDER		1		// BOB remove

/******************************************************************************/

#include "IsHttpServer.h"
#include "HtmlView.h"
#include "HTMLWriter.h"
#include "ASMemberType.h"
#include "ASFantasyType.h"

using namespace asmember;

namespace asfantasy
{

/******************************************************************************/

#define ASFantasyStandardPageWidth()		(760)
#define ASFantasySlimPageWidth()			(600)

#define ASFantasyStandardFont()				("Arial, Helvetica")

/******************************************************************************/

enum TASFantasyHTMLPage
{
	htmlUndefinedPage,

	htmlHomePage,
	htmlErrorPage,
	htmlRequirementsPage,

	htmlSignupIntroGetPage,
	htmlSignupWhichGetPage,
	htmlNewMemberSignupPremiumGetPage,
	htmlNewMemberSignupStandardGetPage,
	htmlNewMemberSignupPostPage,

//	htmlNewParticSignupGetPage,
	htmlNewParticSignupPremiumGetPage,
	htmlNewParticSignupStandardGetPage,
	htmlNewParticSignupPostPage,

	htmlParticUpgradeGetPage,
	htmlParticUpgradePostPage,
	htmlParticPremiumTrialGetPage,
	htmlParticPremiumTrialPostPage,

	htmlPickParticPage,
	htmlHubPage,
	htmlCustomPage,
	htmlLeagueSignupPage,
	htmlTeamsPage,
	
	htmlDraftRankingsPage,
	htmlDraftResultsPage,
	
	htmlSchedulePage,
	htmlLineupPage,
	htmlGameResultsPage,
	htmlStandingsPage,
	htmlFreeAgentPage,
	htmlTradePage,
	htmlPlayoffPage,

	htmlASFantasyLastPage	// not a real page, used for derived enums
};

enum ASFantasyJavaArchive
{
	fja_Draft,
	fja_Season
};

/******************************************************************************/

enum TASFantasyStandardImage
{
	mainBackgroundImage,
	main_171x114Image,
	listBulletImage,

	asfantasyLastImagee		// not a real image, used for derived enums
};

/******************************************************************************/

class MemberParticMismatchException : public ASIException
{
public:
	MemberParticMismatchException() : ASIException("MemberParticMismatchException") {}
};

/******************************************************************************/

enum THtmlPageLinkType
{
	hplt_IsapiDll,
	hplt_Relative
};

class THTMLPageLinkInfo;	//forward reference

class THtmlPageOptions : public THtmlViewOptions
{
	static int fNextPortID;
	
	// WARNING: Do not access these fields directly, use get???() functions.
	asmember::TMemberID fRqstMemberID;	// MemberID of user requesting page (i.e. the
								//	user logged in).
	TParticPtr fRqstParticPtr;	// Partic of user requesting page (i.e. the
								//	user logged in).
	TTeamPtr fRqstTeamPtr;		// Team for fRqstParticPtr
	TLeaguePtr fRqstLeaguePtr;	// League for fRqstParticPtr/fRqstTeamPtr
	
	bool fSeasonView;			// Season or Draft, shows different icons/links
	
public:
	THtmlPageOptions() { fSeasonView = false; }

	int getNextPortID();

	void setRqstMemberID(asmember::TMemberID memberID);
	void setRqstPartic(TParticID particID,TPassword password);

	bool isRqstMemberSet() const { return(!fRqstMemberID.isUndefined()); }
	bool isRqstParticSet() const { return(!fRqstParticPtr.isNull()); }
	bool isRqstLeagueSet() const;
	
	asmember::TMemberID getRqstMemberID() const;
	TParticPtr getRqstPartic() const;
	TTeamPtr getRqstTeam() const;
	TLeaguePtr getRqstLeague() const;

	bool isSeasonView() const { return(fSeasonView); }
	void setSeasonView(bool seasonView) { fSeasonView = seasonView; }
	
	// General Parameters
	virtual CStrVar getJavaDefaultArchive(ASFantasyJavaArchive fja) const = 0;

	// Type Alpha Parameters
	virtual int getTypeAlphaPageWidth() const = 0;
	virtual int getTypeAlphaIconNavColWidth() const = 0;
	
	virtual const THTMLPageLinkInfo& getPageLinkInfo(int htmlPage) const = 0;
	virtual int getPageLinkInfoEnum(const AnsiString& pageName) const = 0;

	virtual CStrVar getStandardImageName(const int standardImage) const = 0;
	virtual CStrVar getStandardImageRootPath(const int standardImage) const = 0;

	// Helper Funtions
	AnsiString buildJavaPortUserParam(void) const;
	
	AnsiString buildPageLink(const AnsiString& linkURL) const;
	AnsiString buildUserLink(const TEncodedParticID& encodedParticID) const;
	AnsiString buildHTMLLink(const char* linkURL,THtmlPageLinkType linkType,
		bool includeUser /*= true*/, bool loginNeeded /*= true*/,
		const char* otherParams = NULL) const;

	// HtmlView Writers
	virtual void loadHeaderViewNavButtonBarArray(
		vector<vector<int> >& htmlPageArray)
		{ htmlPageArray.erase(htmlPageArray.begin(),htmlPageArray.end()); }

	virtual THtmlViewPtr getFooterViewIconsHtmlView(const bool showCompanyOnly) = 0;
};

/*
class TASFantasyHtmlPageOptions : public THtmlPageOptions
{
public:
	static TASFantasyHtmlPageOptions asDerived(THtmlPageOptions& pageOptions)
		{ return(dynamic_cast<TASFantasyHtmlPageOptions&>(pageOptions)); }
};
*/

/******************************************************************************/

// Contains information to link to a HTML page.

class THTMLPageLinkInfo
{
private:
	CStrVar fImageBaseName;
	CStrVar fImageExtName;

	CStrVar fLinkURL;
	THtmlPageLinkType fLinkType;
	CStrVar fLinkDesc;

	bool fIsMemberNeeded;
	bool fIsParticNeeded;
	bool fIsSSLNeeded;

public:
	THTMLPageLinkInfo(const char* imageBaseName,const char* imageExtName,
		const char* linkURL,THtmlPageLinkType linkType,const char* linkDesc,
		bool isMemberNeeded,bool isParticNeeded,bool isSSLNeeded)
	{
		fImageBaseName = imageBaseName;
		fImageExtName = imageExtName;

		fLinkURL = linkURL;
		fLinkType = linkType;
		fLinkDesc = linkDesc;

		fIsMemberNeeded = isMemberNeeded;
		fIsParticNeeded = isParticNeeded;
		fIsSSLNeeded = isSSLNeeded;
	}
	
	AnsiString GetName() const { return(fLinkURL.c_str()); }
	CStrVar getImageBaseName() { return(fImageBaseName); }
	CStrVar getImageExtName() { return(fImageBaseName); }

	AnsiString GetImageURL(const THtmlPageOptions& pageOptions) const;
	CStrVar getImageButtonURL(const THtmlPageOptions& pageOptions) const;

	AnsiString GetLinkURLToEncodedParticID(const THtmlPageOptions& pageOptions,
		const TEncodedParticID& encodedParticID) const;
	AnsiString GetAbsoluteLinkURLToEncodedParticID(int siteID,
		const THtmlPageOptions& pageOptions,
		const TEncodedParticID& encodedParticID) const;
	AnsiString GetSecureAbsoluteLinkURLToEncodedParticID(int siteID,
		const THtmlPageOptions& pageOptions,
		const TEncodedParticID& encodedParticID) const;
	CStrVar GetSecureAbsoluteLinkURL(int siteID,
		const THtmlPageOptions& pageOptions,const char* otherParams = NULL) const;
	AnsiString GetLinkURLToPartic(const THtmlPageOptions& pageOptions,
		TParticPtr particPtr) const;
	AnsiString GetLinkURL(const THtmlPageOptions& pageOptions,
		const char* otherParams = NULL) const;
	AnsiString GetLinkDesc(void) const;

	bool IsMemberNeeded(void) const { return(fIsMemberNeeded); }
	bool IsParticNeeded(void) const { return(fIsParticNeeded); }
	bool IsSSLNeeded(void) const { return(fIsSSLNeeded); }
};

/******************************************************************************/

// Virtual class which use the THtmlPageOptions class. Used to derive from.

class TPageOptionsHtmlView : public THTMLView
{
protected:
	THtmlPageOptions& fPageOptions;
	
	TPageOptionsHtmlView(THtmlPageOptions& pageOptions) :
		fPageOptions(pageOptions) {}
};

/******************************************************************************/

// Allows an empty Table Cell to have specific height and width
//BOB remove this when possible

class TEmptyTableCellHTMLView : public TEmptyTableCellHtmlView
{
public:
	TEmptyTableCellHTMLView(THtmlViewOptions& viewOptions,
		THtmlWidth width,THtmlHeight height = THtmlHeight()) :
		TEmptyTableCellHtmlView(viewOptions,width,height) {}
		
	static void Build(THTMLWriter& htmlWriter,const THtmlPageOptions& pageOptions,
		THtmlWidth width,THtmlHeight height = THtmlHeight())
		{ htmlWriter.WriteView(TEmptyTableCellHtmlView(
			const_cast<THtmlPageOptions&>(pageOptions),width,height)); }
};

/******************************************************************************/

// Build a view that is simple a AnsiString.  Could be HTML.

class TTextHTMLView : public THTMLView
{
protected:
	AnsiString fText;

public:
	TTextHTMLView(const AnsiString& text) { fText = text; }

	void SetText(const AnsiString& text) { fText = text; }
		
	static void Build(THTMLWriter& htmlWriter,const AnsiString& text);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Builds an icon type link image with a text description below it.

class TIconNavHTMLView : public THtmlView
{
private:
	THtmlPageOptions& fPageOptions;
	int fHtmlPage;

public:
	TIconNavHTMLView(THtmlPageOptions& pageOptions,int htmlPage) :
		THtmlView(pageOptions), fPageOptions(pageOptions), fHtmlPage(htmlPage) {}

	virtual void write(THTMLWriter& htmlWriter);
};


/******************************************************************************/

// Builds a column of TIconNavHTMLViews.

class TIconNavColumnHTMLView : public THTMLView
{
public:
	virtual void Write(THTMLWriter& htmlWriter) = 0;

protected:
	void WriteRow(THTMLWriter& htmlWriter,THtmlPageOptions& pageOptions,
		int htmlPage);
};

/******************************************************************************/

// Builds an icon type link image with a text description below it.

class TButtonNavHtmlView : public THtmlView
{
private:
	THtmlPageOptions& fPageOptions;
	int fHtmlPage;
	THtmlWidth fWidth;
	THtmlHeight fHeight;

public:
	TButtonNavHtmlView(THtmlPageOptions& pageOptions,int htmlPage,
		THtmlWidth width = THtmlWidth(),THtmlHeight height = THtmlHeight()) :
		THtmlView(pageOptions), fPageOptions(pageOptions), fHtmlPage(htmlPage),
		fWidth(width),fHeight(height) {}

	virtual void write(THTMLWriter& htmlWriter);
};


/******************************************************************************/
/******************************************************************************/

// Builds a text link.

class TTextNavHTMLView : public THTMLView
{
private:
	const THtmlPageOptions& fPageOptions;
	int fHtmlPage;
	CStrVar fExtraParameters;

public:
	TTextNavHTMLView(const THtmlPageOptions& pageOptions,int htmlPage,
		const char* extraParameters = NULL) : fPageOptions(pageOptions),
		fHtmlPage(htmlPage),fExtraParameters(extraParameters) {}

	static void Build(THTMLWriter& htmlWriter,
		const THtmlPageOptions& pageOptions,int htmlPage,
		const char* extraParameters = NULL);
	virtual void Write(THTMLWriter& htmlWriter);
};


/******************************************************************************/
/******************************************************************************/

// Builds Java applet with link to Sys. Require. page.

//BOB clean-up multiple

class TJavaPanelHtmlView : public THtmlView, public TPageOptionsHtmlView
{
private:
	ASFantasyJavaArchive fJavaArchive;
	CStrVar fJavaClass;
	int fJavaWidth;
	int fJavaHeight;
	
public:
	TJavaPanelHtmlView(THtmlPageOptions& pageOptions,
		ASFantasyJavaArchive javaArchive,const char* javaClass,int javaWidth,
		int javaHeight) : THtmlView(pageOptions),TPageOptionsHtmlView(pageOptions),
		fJavaArchive(javaArchive),fJavaClass(javaClass),fJavaWidth(javaWidth),
		fJavaHeight(javaHeight) {}
	
	virtual void write(THTMLWriter& htmlWriter);
	virtual void Write(THTMLWriter& htmlWriter) { write(htmlWriter); }
protected:
	virtual void WriteParameters(THTMLWriter& htmlWriter) {}
};
typedef TJavaPanelHtmlView TJavaPanelHTMLView;

/******************************************************************************/
/******************************************************************************/

class TMailToTheRefHtmlView : public TMailToHtmlView
{
public:
	TMailToTheRefHtmlView(THtmlViewOptions& viewOptions) :
		TMailToHtmlView(viewOptions,TechSupportEmail()) {}
};

/******************************************************************************/
/******************************************************************************/

class ASFantasyFooterViewIcons : public THtmlViewRefCountObject
{
protected:
	THtmlPageOptions& fPageOptions;
	bool fShowCompanyOnly;

protected:
	ASFantasyFooterViewIcons(THtmlPageOptions& pageOptions,
		const bool showCompanyOnly) : THtmlViewRefCountObject(pageOptions),
		fPageOptions(pageOptions),fShowCompanyOnly(showCompanyOnly) {}

public:
	virtual void write(THTMLWriter& htmlWriter);

protected:
	virtual bool hasSponsor() const { return(false); }
	virtual void writeSponsorIcon(THTMLWriter& htmlWriter) {}
	virtual void writeSponsorText(THTMLWriter& htmlWriter) {}

	virtual bool hasPlayerAssoc() const { return(false); }
	virtual void writePlayerAssocIcon(THTMLWriter& htmlWriter) {}
	virtual void writePlayerAssocText(THTMLWriter& htmlWriter) {}
};

/******************************************************************************/
/******************************************************************************/

// Base Page type.  Page split into Header, Body, Footer.

class ASFantasyBasePageHtmlView;	//forward reference
typedef RefCountPtr<ASFantasyBasePageHtmlView> ASFantasyBasePageHtmlViewPtr;

class ASFantasyBasePageHtmlView : public RefCountObject
{
protected:
	IsHtmlServer& fIsHtmlServer;
	THtmlPageOptions& fPageOptions;
	THTMLWriter& fHtmlWriter;

protected:
	ASFantasyBasePageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		fIsHtmlServer(isHtmlServer),fPageOptions(pageOptions),
		fHtmlWriter(htmlWriter) {}

private:
	ASFantasyBasePageHtmlView(const ASFantasyBasePageHtmlView&);						// don't allow copy constructor
	const ASFantasyBasePageHtmlView& operator=(const ASFantasyBasePageHtmlView&);		// or operator=

public:
	virtual void process() { initialize(); write(); }

	THtmlPageOptions& getPageOptions() { return(fPageOptions); }

protected:
	virtual void initialize() {}
	virtual void write();

	virtual CStrVar getPageTitle(void) const = 0;
	virtual int getPageWidth(void) const { return(ASFantasyStandardPageWidth()); }

	virtual bool canCachePage() const { return(false); }
	virtual void writeInitialize();
	virtual CStrVar getBackgroundImage() const
		{ return(fPageOptions.getStandardImageName(mainBackgroundImage)); }
	virtual TColor getBackgroundColor() const
		{ return(fPageOptions.getBackgroundColor()); }

	virtual bool showHeaderViewAd() const { return(true); }
	virtual void writeHeaderView();
	virtual void writeHeaderViewLogo();
	virtual void writeBodyView() = 0;

	virtual bool showFooterView() const { return(true); }
	virtual void writeFooterView();
	virtual bool showFooterViewIcons() const { return(true); }
	virtual bool showFooterViewIconsCompanyOnly() const { return(false); }

	virtual void writeFinalize();

	virtual void writeLinkStart(int htmlPage,const char* otherParams = NULL,
		const TEncodedParticID encodedParticID = TEncodedParticID());
public:
	virtual void writeTextLink(int htmlPage,const char* linkDescrip = NULL,
		const char* otherParams = NULL,
		const TEncodedParticID encodedParticID = TEncodedParticID());
	virtual void writeIconLink(int htmlPage,const char* imageName = NULL,
		const char* linkDescrip = NULL,const char* otherParams = NULL,
		const TEncodedParticID encodedParticID = TEncodedParticID());

	friend class RefCountPtr<ASFantasyBasePageHtmlView>;
};

/******************************************************************************/
/******************************************************************************/

class TTypeAlphaRightPanelTitleHtmlView : public TTextHTMLView
{
public:
	TTypeAlphaRightPanelTitleHtmlView(const AnsiString& title) :
		TTextHTMLView(title) {}

	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Builds type Alpha page right-panel in the default body.  Content area
//	is Java or some other data.

// Title Type.
enum TitleType	//BOB Rename ASFantasyBodyViewTitleType
{
	tt_None,
	tt_Manager,
	tt_League
};
typedef TitleType ASFantasyBodyViewTitleType;

class TTypeAlphaRightPanelHtmlView : public TPageOptionsHtmlView
{
protected:
	TitleType fTT;
	int fViewWidth;		// should be the width of the content (Java applet).
	CStr63 fTitle;
	TTextHTMLView fInstrucView;
	
public:
	TTypeAlphaRightPanelHtmlView(THtmlPageOptions& pageOptions,TitleType tt,
		int viewWidth,const AnsiString& title,const AnsiString& instructions) :
		TPageOptionsHtmlView(pageOptions),fTT(tt),fViewWidth(viewWidth),
		fTitle(title.c_str()),fInstrucView(instructions) {}
	
	virtual void Write(THTMLWriter& htmlWriter);

protected:
	void setTitleText(const AnsiString& title)
		{ fTitle.Copy(title.c_str()); }
	void setInstrucText(const AnsiString& instructions)
		{ fInstrucView.SetText(instructions); }
	
	virtual void writeTitleView(THTMLWriter& htmlWriter);
	virtual void writeInstrucView(THTMLWriter& htmlWriter)
		{ fInstrucView.Write(htmlWriter); }
		
	virtual void writeContentView(THTMLWriter& htmlWriter) {}
};

/******************************************************************************/

// Builds a Java containing right-panel, type Alpha page, in the default body.

#if 0

class TTypeAlphaJavaPanelHTMLView : public TTypeAlphaRightPanelHtmlView
{
private:
	TJavaPanelHTMLView fJavaView;
	
public:
	TTypeAlphaJavaPanelHTMLView(THtmlPageOptions& pageOptions,TitleType tt,
		int viewWidth,const AnsiString& title,const AnsiString& instructions,
		const AnsiString& javaClass,int javaWidth,int javaHeight) :
		TTypeAlphaRightPanelHtmlView(pageOptions,tt,viewWidth,title,instructions),
		fJavaView(pageOptions,javaClass.c_str(),javaWidth,javaHeight) {}
	
protected:
	virtual void writeContentView(THTMLWriter& htmlWriter)
		{ fJavaView.Write(htmlWriter); }
};

#elif 0

class TTypeAlphaJavaPanelHTMLView : public TTypeAlphaRightPanelHtmlView
{
private:
	int fViewWidth;		// should be the width of the Java applet.
	CStr63 fTitle;
	TTextHTMLView fInstrucView;
	TJavaPanelHTMLView fJavaView;
	
public:
	TTypeAlphaJavaPanelHTMLView(THtmlPageOptions& pageOptions,int viewWidth,
		const AnsiString& title,const AnsiString& instructions,
		const AnsiString& javaClass,int javaWidth,int javaHeight) :
		TPageOptionsHtmlView(pageOptions),fViewWidth(viewWidth),
		fTitle(title.c_str()),fInstrucView(instructions),
		fJavaView(pageOptions,javaClass,javaWidth,javaHeight) {}
	
	virtual void Write(THTMLWriter& htmlWriter);

protected:
	void setTitleText(const AnsiString& title)
		{ fTitle.Copy(title.c_str()); }
	void setInstrucText(const AnsiString& instructions)
		{ fInstrucView.SetText(instructions); }
	
	virtual void writeTitleView(THTMLWriter& htmlWriter);
	virtual void writeInstrucView(THTMLWriter& htmlWriter)
		{ fInstrucView.Write(htmlWriter); }
	virtual void writeJavaView(THTMLWriter& htmlWriter)
		{ fJavaView.Write(htmlWriter); }
};

#endif
/******************************************************************************/
/******************************************************************************/

// Builds type Alpha page default header. Left side contains Presents logo. 
//	Right side contains advertisment.

class TTypeAlphaDefaultHeaderHTMLView : public THTMLView
{
private:
	const THtmlPageOptions& fPageOptions;
	bool fShowAd;
	
public:
	TTypeAlphaDefaultHeaderHTMLView(const THtmlPageOptions& pageOptions,
		bool showAd) : fPageOptions(pageOptions), fShowAd(showAd) {}
	
	static void Build(THTMLWriter& htmlWriter,const THtmlPageOptions& pageOptions,
		bool showAd);
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds type Alpha page default body. Left side contains
//	TIconNavColumnHTMLView. Right side contains anything.

class TTypeAlphaDefaultBodyHTMLView : public TPageOptionsHtmlView
{
public:
	TTypeAlphaDefaultBodyHTMLView(THtmlPageOptions& pageOptions) :
		TPageOptionsHtmlView(pageOptions) {}
		
	virtual void Write(THTMLWriter& htmlWriter);

protected:
	virtual void writeLeftPanelView(THTMLWriter& htmlWriter) = 0;
	virtual void writeRightPanelView(THTMLWriter& htmlWriter) = 0;
};

/******************************************************************************/
/******************************************************************************/

// Builds type Alpha page default footer.

class TTypeAlphaDefaultFooterHTMLView : public TPageOptionsHtmlView
{
public:
	TTypeAlphaDefaultFooterHTMLView(THtmlPageOptions& pageOptions) :
		TPageOptionsHtmlView(pageOptions) {}
		
	virtual void Write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
/******************************************************************************/

// Builds type Alpha page.  Logos across top, icons down left, Java applet in
//	body, text link footer.

class TTypeAlphaPageHTMLView : public TPageOptionsHtmlView
{
protected:
	TTypeAlphaDefaultFooterHTMLView fFooterView;
		
public:
	TTypeAlphaPageHTMLView(THtmlPageOptions& pageOptions) :
		TPageOptionsHtmlView(pageOptions),fFooterView(pageOptions) {}
	
	virtual void Write(THTMLWriter& htmlWriter);

protected:
	virtual void writePageTitle(THTMLWriter& htmlWriter);
	
	virtual AnsiString getPageTitle(void) const = 0;
	
	virtual bool showHeaderViewAd() const { return(true); }
	virtual THTMLAlignHoriz getHeaderAlignHoriz() { return(ahCenter); }
	virtual void writeHeaderView(THTMLWriter& htmlWriter)
		{ TTypeAlphaDefaultHeaderHTMLView::Build(htmlWriter,fPageOptions,
			showHeaderViewAd()); }
	
	virtual THTMLAlignHoriz getBodyAlignHoriz() { return(ahCenter); }
	virtual void writeBodyView(THTMLWriter& htmlWriter) = 0;
	
	virtual bool showFooterView() const { return(true); }
	virtual THTMLAlignHoriz getFooterAlignHoriz() { return(ahCenter); }
	virtual void writeFooterView(THTMLWriter& htmlWriter)
		{ fFooterView.Write(htmlWriter); }
};

/******************************************************************************/
/******************************************************************************/

// Title at top of page.

class TTypeBetaPageTitleHtmlView
{
protected:
	CStrVar fTitle;

public:
	TTypeBetaPageTitleHtmlView(const char* title) : fTitle(title) {}
		
	static void build(THTMLWriter& htmlWriter,const char* title)
		{ TTypeBetaPageTitleHtmlView htmlView(title); htmlView.write(htmlWriter); }
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Title at top of section.

class TTypeBetaSectionTitleHtmlView
{
protected:
	CStrVar fTitle;

public:
	TTypeBetaSectionTitleHtmlView(const char* title) : fTitle(title) {}
		
	static void build(THTMLWriter& htmlWriter,const char* title)
		{ TTypeBetaSectionTitleHtmlView htmlView(title); htmlView.write(htmlWriter); }
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Title at top of section.

class TTypeBetaSectionTextHtmlView : public THtmlView
{
protected:
	CStrVar fText;
	TColor fTextColor;

public:
	TTypeBetaSectionTextHtmlView(THtmlPageOptions& pageOptions,
		const char* text,TColor textColor = clDefault) :
		THtmlView(pageOptions),fText(text),fTextColor(textColor) {}
		
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

// Subscript type text.

class TTypeBetaTinyTextHtmlView : public THtmlView
{
protected:
	CStrVar fText;

public:
	TTypeBetaTinyTextHtmlView(THtmlPageOptions& pageOptions,
		const char* text) : THtmlView(pageOptions),fText(text) {}
		
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/
#if 0	//BOB remove - convert Beta above to Gamma (or maybe to Signup)

// Build type Beta page.  Logo in upper left, title across top.

class TTypeBetaHtmlPage
{
protected:
	IsHtmlServer& fIsHtmlServer;
	THtmlPageOptions& fPageOptions;
	THTMLWriter& fHtmlWriter;

protected:
	TTypeBetaHtmlPage(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		fIsHtmlServer(isHtmlServer),fPageOptions(pageOptions),
		fHtmlWriter(htmlWriter) {}

public:
	virtual void process() { initialize(); write(); }

protected:
	virtual CStrVar getPageTitle(void) const = 0;
	virtual int getPageWidth(void) const { return(ASFantasyStandardPageWidth()); }

	virtual void initialize() {}
	virtual void write();

	virtual bool canCachePage() const { return(true); }
	virtual void writeInitialize();
	virtual AnsiString getBackgroundImage() const { return(""); }
	virtual TColor getBackgroundColor() const { return(clWhite); }

	virtual void writeHeaderView();
	virtual void writeBodyView() = 0;
	virtual void writeFooterView() {}

	virtual void writeFinalize();
};

#endif
/******************************************************************************/

// Build Type Gamma page.  Logo in upper left, navigation button bar under logo.

class TTypeGammaPageHtmlView : public ASFantasyBasePageHtmlView
{
protected:
	TTypeGammaPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		ASFantasyBasePageHtmlView(isHtmlServer,pageOptions,htmlWriter) {}

	virtual void writeHeaderView();
	virtual bool showHeaderViewNavButtonBar() const { return(true); }
	void writeHeaderViewNavButtonBar(vector<vector<int> >& htmlPageArray);

	virtual void writeBodyView();
	virtual int getBodyViewWidth(void) const { return(0); }
	virtual ASFantasyBodyViewTitleType getBodyViewTitleType()
		{ return(tt_League); }
	virtual void writeBodyViewTitle();
	virtual CStrVar getBodyViewInstructions(void) const
		{ return(CStrVar()); }
	virtual void writeBodyViewInstructions();
	virtual int getBodyViewBodyHeight(void) const { return(300); }
	virtual void writeBodyViewBody();
};

/******************************************************************************/
/******************************************************************************/

// Builds an Message page.

class TMessagePageHtmlView : public ASFantasyBasePageHtmlView
{
protected:
	CStrVar fMessage;

protected:
	TMessagePageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,
		const char* message) : ASFantasyBasePageHtmlView(isHtmlServer,
		pageOptions,htmlWriter),fMessage(message) {}

	virtual CStrVar getPageTitle(void) const { return("Message"); }

	virtual bool showHeaderViewAd() const { return(false); }

	virtual THTMLAlignHoriz getBodyAlignHoriz() { return(ahLeft); }
	virtual void writeBodyView();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

// Builds an Error page.

class TErrorPageHtmlView : public TMessagePageHtmlView
{
protected:
	TErrorPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,
		const char* message) : TMessagePageHtmlView(isHtmlServer,
		pageOptions,htmlWriter,message) {}

	virtual CStrVar getPageTitle(void) const { return("Error"); }

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

// Custon Links

class TSignupTextNavHtmlView : public THtmlView
{
protected:
	ASFantasyBasePageHtmlView& fPage;
	CStrVar fAltLinkDescrip;

public:
	TSignupTextNavHtmlView(ASFantasyBasePageHtmlView& page,
		const char* altLinkDescrip = NULL) : THtmlView(page.getPageOptions()),
		fPage(page),fAltLinkDescrip(altLinkDescrip) {}

	virtual void write(THTMLWriter& htmlWriter);
};


/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyHtmlPageBuilderH
/******************************************************************************/
/******************************************************************************/
