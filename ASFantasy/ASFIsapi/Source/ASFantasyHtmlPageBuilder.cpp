/* ASFantasyHtmlPageBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "PasswordEncode.h"

#include "ASFantasyObjectBuilder.h"
#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

void THtmlPageOptions::setRqstMemberID(TMemberID memberID)
{
	fRqstMemberID = memberID;
	fRqstMemberID.ToUpper();
	fRqstMemberID.Compress(CSW_TRAILING);	// InterBase considers trailing spaces OK when performing search.
}

/******************************************************************************/

void THtmlPageOptions::setRqstPartic(TParticID particID,TPassword password)
{
	fRqstParticPtr = TPartic::createGet(particID,cam_MustExist);

	if(fRqstParticPtr->getPassword() != password)
		throw ASIException("THtmlPageOptions::setRqstPartic: invalid pagePassword");
	
	if(fRqstParticPtr->getMemberID() != getRqstMemberID())
		throw MemberParticMismatchException();
}

/******************************************************************************/

bool THtmlPageOptions::isRqstLeagueSet() const
{
	if(!fRqstLeaguePtr.isNull())
		return(true);
		
	if(isRqstParticSet())
	{
		TTeamPtr teamPtr = getRqstTeam();

		// Has Partic join league yet?
		if(!teamPtr->getLeagueID().isUndefined())
			return(true);
	}

	return(false);
}

/******************************************************************************/

TMemberID THtmlPageOptions::getRqstMemberID() const
{
	if(fRqstMemberID.isUndefined())
		throw ASIException("THtmlPageOptions::getRqstMemberID: attempting to access undefined fRqstMemberID");

	return(fRqstMemberID);
}

/******************************************************************************/

TParticPtr THtmlPageOptions::getRqstPartic() const
{
	if(fRqstParticPtr.isNull())
		throw ASIException("THtmlPageOptions::getRqstPartic: attempting to access NULL fRqstParticPtr");

	return(fRqstParticPtr);
}

/******************************************************************************/

TTeamPtr THtmlPageOptions::getRqstTeam() const
{
	if(fRqstTeamPtr.isNull())
		const_cast<THtmlPageOptions*>(this)->fRqstTeamPtr =
			TTeam::createGet(getRqstPartic()->getTeamID(),cam_MustExist);

	return(fRqstTeamPtr);
}

/******************************************************************************/

TLeaguePtr THtmlPageOptions::getRqstLeague() const
{
	if(!fRqstLeaguePtr.isNull())
		return(fRqstLeaguePtr);

	TTeamPtr teamPtr = getRqstTeam();

	// Has Partic join league yet, if not, must be Draft view.
	if(teamPtr->getLeagueID().isUndefined())
		throw ASIException("THtmlPageOptions::getRqstLeague: teamPtr->getLeagueID().isUndefined()");
	
	//BOB do we want to store the league in fPageOptions?
	const_cast<THtmlPageOptions*>(this)->fRqstLeaguePtr =
		TLeague::createGet(teamPtr->getLeagueID(),cam_MustExist);

	return(fRqstLeaguePtr);
}

/******************************************************************************/
/******************************************************************************/
#if 0	//BOB

AnsiString THtmlPageOptions::buildImagePath(const AnsiString& imageURL) const
{
#ifdef LOCALWEB
	return(getImageRootPath() + imageURL);
#else
	return(getRootPath() + getImageRootPath() + imageURL);
#endif
}

/******************************************************************************/

AnsiString THtmlPageOptions::buildJavaCodeBasePath(void) const
{
#ifdef LOCALWEB
	return(getJavaRootPath());
#else
	return(getRootPath() + getJavaRootPath());
#endif
}

#endif
/******************************************************************************/
#if 0	//BOB

AnsiString THtmlPageOptions::buildJavaPortUserParam(void) const
{
	TParticPtr particPtr = getPagePartic();
	TEncodedParticID user = particPtr->encodeParticID();
	AnsiString str;

//BOB should build one string at a time and use htmlWriter.JavaParameter
	
	str = AnsiString("<param name=PortID value=\"") +
		AnsiString(CStr31().CopyVarg("%d",getNextPortID()).c_str()) +
		AnsiString("\">");
	str += AnsiString("<param name=") + AnsiString(gURLUserFieldStr) +
		AnsiString(" value=\"") + AnsiString(user.c_str()) +
		AnsiString("\">");
			
	return(str);
}

#endif
/******************************************************************************/

AnsiString THtmlPageOptions::buildPageLink(const AnsiString& linkURL) const
{
	return(AnsiString(gURLPageFieldStr) + AnsiString("=") + linkURL);
}

/******************************************************************************/

AnsiString THtmlPageOptions::buildUserLink(const TEncodedParticID& encodedParticID) const
{
	return(AnsiString(gURLUserFieldStr) + AnsiString("=") +
		encodedParticID.c_str());
}

/******************************************************************************/

AnsiString THtmlPageOptions::buildHTMLLink(const char* linkURL,
	THtmlPageLinkType linkType,bool includeUser, bool loginNeeded,
	const char* otherParams) const
{
	CStrVar str;
	
#ifdef LOCALWEB
	str = linkURL + ".html";
#else
	if(linkType == hplt_IsapiDll)
	{
		str.copy(loginNeeded ? getIsapiDll().c_str() : getIsapiDllNS().c_str());

		str.concatVarg("?%s",buildPageLink(linkURL).c_str());

		if(isBackdoorAccess())
			str.concat("&Backdoor=T");

		if(includeUser)
			str.concatVarg("&%s",
				buildUserLink(getRqstPartic()->encodeParticID()).c_str());

		if(tStrHasLen(otherParams))
			str.concatVarg("&%s",otherParams);
	}
	else if(linkType == hplt_Relative)
	{
		str = getRootPath().c_str();
		
		if(loginNeeded)
			str.concat("Secure/");

		str.concat(linkURL);
		str.concat(".html");
	}
	else
		throw ASIException("THtmlPageOptions::buildHTMLLink: unknown linkType");
#endif
	
	return(str.c_str());
}

/******************************************************************************/
/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetImageURL(const THtmlPageOptions& pageOptions) const
{
	CStrVar imageURL;

	imageURL.copy(fImageBaseName);
	imageURL.concat(fImageExtName);

	return(pageOptions.buildImagePath(imageURL.c_str()).c_str());
}

/******************************************************************************/

CStrVar THTMLPageLinkInfo::getImageButtonURL(const THtmlPageOptions& pageOptions) const
{
	CStrVar imageURL;

	imageURL.copy(fImageBaseName);
	imageURL.concat("Button");
	imageURL.concat(fImageExtName);

	return(pageOptions.buildImagePath(imageURL));
}

/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetLinkURLToEncodedParticID(
	const THtmlPageOptions& pageOptions,const TEncodedParticID& encodedParticID) const
{
	return(pageOptions.buildHTMLLink(fLinkURL.c_str(),hplt_IsapiDll,false,fIsMemberNeeded)
		+ AnsiString("&") + pageOptions.buildUserLink(encodedParticID));
}

/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetAbsoluteLinkURLToEncodedParticID(int siteID,
	const THtmlPageOptions& pageOptions,const TEncodedParticID& encodedParticID) const
{
	return(pageOptions.getWebURLBasePath(siteID,false) +
		pageOptions.buildHTMLLink(fLinkURL.c_str(),hplt_IsapiDll,false,fIsMemberNeeded) +
		AnsiString("&") + pageOptions.buildUserLink(encodedParticID));
}

/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetSecureAbsoluteLinkURLToEncodedParticID(int siteID,
	const THtmlPageOptions& pageOptions,const TEncodedParticID& encodedParticID) const
{
	return(pageOptions.getWebURLBasePath(siteID,true) +
		pageOptions.buildHTMLLink(fLinkURL.c_str(),hplt_IsapiDll,false,fIsMemberNeeded) +
		AnsiString("&") + pageOptions.buildUserLink(encodedParticID));
}

/******************************************************************************/

CStrVar THTMLPageLinkInfo::GetSecureAbsoluteLinkURL(int siteID,
	const THtmlPageOptions& pageOptions,const char* otherParams) const
{
	CStrVar str;

	str.copy(pageOptions.getWebURLBasePath(siteID,true).c_str());
	str.concat(pageOptions.buildHTMLLink(fLinkURL.c_str(),hplt_IsapiDll,false,
		fIsMemberNeeded).c_str());
	if(tStrHasLen(otherParams))
		str.concatVarg("&%s",otherParams);

	return(str);
}

/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetLinkURLToPartic(const THtmlPageOptions& pageOptions,
	TParticPtr particPtr) const
{
	return(pageOptions.buildHTMLLink(fLinkURL.c_str(),hplt_IsapiDll,false,
		fIsMemberNeeded) + AnsiString("&") +
		pageOptions.buildUserLink(particPtr->encodeParticID()));
}

/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetLinkURL(const THtmlPageOptions& pageOptions,
	const char* otherParams) const
{
	return(pageOptions.buildHTMLLink(fLinkURL.c_str(),fLinkType,
		fIsParticNeeded,fIsMemberNeeded,otherParams));
}

/******************************************************************************/

AnsiString THTMLPageLinkInfo::GetLinkDesc(void) const
{
	return(fLinkDesc.c_str());
}

/******************************************************************************/
/******************************************************************************/

void TTextHTMLView::Build(THTMLWriter& htmlWriter,const AnsiString& text)
{
	TTextHTMLView htmlView(text);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TTextHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString(fText.c_str());
}

/******************************************************************************/
/******************************************************************************/

void TIconNavHTMLView::write(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(fHtmlPage));
	
	htmlWriter.LinkStart(pageLinkInfo.GetLinkURL(fPageOptions).c_str(),"");
	htmlWriter.Image(pageLinkInfo.GetImageURL(fPageOptions).c_str(),
		pageLinkInfo.GetLinkDesc().c_str(),"",aiDefault);
	htmlWriter.LineBreak(hcrDefault);
	htmlWriter.FontStart(1, fcAbsolute, "", clDefault);
	htmlWriter.TextString(pageLinkInfo.GetLinkDesc().c_str());
	htmlWriter.FontEnd();
	htmlWriter.LinkEnd();
}

/******************************************************************************/
/******************************************************************************/

void TButtonNavHtmlView::write(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(fHtmlPage));

	htmlWriter.LinkStart(pageLinkInfo.GetLinkURL(fPageOptions).c_str(),"");
	htmlWriter.Image(pageLinkInfo.getImageButtonURL(fPageOptions),
		pageLinkInfo.GetLinkDesc().c_str(),"",aiDefault,fWidth,fHeight);
	htmlWriter.LinkEnd();
}

/******************************************************************************/
/******************************************************************************/

void TIconNavColumnHTMLView::WriteRow(THTMLWriter& htmlWriter,
	THtmlPageOptions& pageOptions,int htmlPage)
{
	htmlWriter.TableRowStart();
	
	htmlWriter.TableCellView(TIconNavHTMLView(pageOptions,htmlPage),0,0,
		THtmlWidth(),THtmlHeight(),ahCenter,avTop);
		
	htmlWriter.TableRowEnd();
}

/******************************************************************************/
/******************************************************************************/

void TTextNavHTMLView::Build(THTMLWriter& htmlWriter,
	const THtmlPageOptions& pageOptions,int htmlPage,const char* extraParameters)
{
	TTextNavHTMLView htmlView(pageOptions,htmlPage,extraParameters);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TTextNavHTMLView::Write(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(fHtmlPage));
	CStrVar url = pageLinkInfo.GetLinkURL(fPageOptions).c_str();

	if(fExtraParameters.hasLen())
	{
		if(fExtraParameters[0] != '&')
			url.concat("&");
		url.concat(fExtraParameters);
	}

	htmlWriter.Link(url,"",pageLinkInfo.GetLinkDesc().c_str());
}

/******************************************************************************/
/******************************************************************************/
#define USE_JAVA_ARCHIVE
#define USE_JAVA_CABBASE

void TJavaPanelHtmlView::write(THTMLWriter& htmlWriter)
{
#if !defined(SHOW_PROTOTYPE)
	CStrVar javaClass;
	CStrVar javaArchive;

	javaClass.copyVarg("%s.class",fJavaClass.c_str());
	#if defined(USE_JAVA_ARCHIVE)
	javaArchive.copyVarg("%s.zip",fPageOptions.getJavaDefaultArchive(fJavaArchive).c_str());
	#endif
	htmlWriter.JavaStart(javaClass,fPageOptions.buildJavaCodeBasePath().c_str(),
		javaArchive,fJavaWidth,fJavaHeight);

	htmlWriter.LineBreak(hcrDefault);
	htmlWriter.LineBreak(hcrDefault);
	htmlWriter.TextString("ERROR: The WWW Browser you are using does not support Java.  ");
	htmlWriter.TextString(fPageOptions.getAppNameAbbr());
	htmlWriter.TextString(" makes extensive use of Java. See ");

	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlRequirementsPage);
	
	htmlWriter.TextString(".");

	htmlWriter.JavaParamString("RequestDll",fPageOptions.getJavaRequestDll());

	htmlWriter.JavaParamString(gURLUserFieldStr,
		fPageOptions.getRqstPartic()->encodeParticID().c_str());

	#if defined(USE_JAVA_CABBASE)
	javaArchive.copyVarg("%s.cab",fPageOptions.getJavaDefaultArchive(fJavaArchive).c_str());
	htmlWriter.JavaParamString("cabbase",javaArchive);
	#endif

	WriteParameters(htmlWriter);
	htmlWriter.JavaEnd();
#else
	htmlWriter.Image(fPageOptions.buildImagePath(fJavaClass + ".gif"));
#endif
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyFooterViewIcons::write(THTMLWriter& htmlWriter)
{
	double colPercent;
	int numCols;
	int currentYear = DateYear(GetSystemDate());

	if(fShowCompanyOnly)
		numCols = 1;
	else
	{
		numCols = 2;
		if(hasSponsor())
			numCols++;
		if(hasPlayerAssoc())
			numCols++;
	}
	colPercent = 100.0 / numCols;

	htmlWriter.TableStart(SHOW_BORDER);
	htmlWriter.TableRowStart();

	/**************************************************************************/
	/* Sponsor */

	if(!fShowCompanyOnly && hasSponsor())
	{
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),
			THtmlHeight(),ahCenter,avMiddle);

		writeSponsorIcon(htmlWriter);

		htmlWriter.TableCellEnd();
	}
	
	/**************************************************************************/
	/* Player Assoc */

	if(!fShowCompanyOnly && hasPlayerAssoc())
	{
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),
			THtmlHeight(),ahCenter,avMiddle);

		writePlayerAssocIcon(htmlWriter);

		htmlWriter.TableCellEnd();
	}
	
	/**************************************************************************/
	/* Affinity Sports */

	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),THtmlHeight(),
		ahCenter,avMiddle);
	htmlWriter.LinkStart("http://www.affinitysports.com","Affinity Sports, Inc.");
	htmlWriter.Image(fPageOptions.buildSiteImagePath("ASILetterHeadLogo.gif").c_str(),
		"Affinity Sports, Inc.","",aiDefault,THtmlWidthValue(133),THtmlHeightValue(40));
	htmlWriter.LinkEnd();
	htmlWriter.TableCellEnd();

	/**************************************************************************/
	/* STATS Inc */

	if(!fShowCompanyOnly)
	{
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),THtmlHeight(),
			ahCenter,avMiddle);
		htmlWriter.LinkStart("http://www.stats.com","STATS, Inc.");
		htmlWriter.Image(fPageOptions.buildSiteImagePath("StatsInc_127x34.gif").c_str(),
			"STATS, Inc.","",aiDefault,THtmlWidthValue(127),THtmlHeightValue(34));
		htmlWriter.LinkEnd();
		htmlWriter.TableCellEnd();
	}

	/**************************************************************************/

	htmlWriter.TableRowEnd();

	htmlWriter.TableRowStart();

	/**************************************************************************/
	/* Sponsor */

	if(!fShowCompanyOnly && hasSponsor())
	{
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),
			THtmlHeight(),ahCenter,avTop);
		htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);

		writeSponsorText(htmlWriter);

		htmlWriter.FontEnd();
		htmlWriter.TableCellEnd();
	}

	/**************************************************************************/
	/* Player Assoc */

	if(!fShowCompanyOnly && hasPlayerAssoc())
	{
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),
			THtmlHeight(),ahCenter,avTop);
		htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);

		writePlayerAssocText(htmlWriter);

		htmlWriter.FontEnd();
		htmlWriter.TableCellEnd();
	}

	/**************************************************************************/
	/* Affinity Sports */

	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),THtmlHeight(),
		ahCenter,avTop);
	htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);
	htmlWriter.TextString(CStrVar::build("Copyright © %d by",currentYear));
	htmlWriter.LineBreak();
	htmlWriter.TextString("Affinity Sports, Inc.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("All Rights Reserved.");
	htmlWriter.FontEnd();
	htmlWriter.TableCellEnd();

	/**************************************************************************/
	/* STATS Inc */

	if(!fShowCompanyOnly)
	{
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,colPercent),THtmlHeight(),
			ahCenter,avTop);
		htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);
		htmlWriter.TextString(fPageOptions.getAppNameAbbr());
		htmlWriter.TextString(" stats provided by");
		htmlWriter.LineBreak();
		htmlWriter.TextString("STATS, Inc.");
		htmlWriter.LineBreak();
		htmlWriter.TextString(CStrVar::build("Statistics Copyright © %d by",currentYear));
		htmlWriter.LineBreak();
		htmlWriter.TextString("STATS, Inc.");
		htmlWriter.LineBreak();
		htmlWriter.TextString("All Rights Reserved.");
		htmlWriter.LineBreak();
		htmlWriter.TextString("Commercial distribution without");
		htmlWriter.LineBreak();
		htmlWriter.TextString("expressed written consent by");
		htmlWriter.LineBreak();
		htmlWriter.TextString("STATS, Inc. is strictly prohibited.");
		htmlWriter.FontEnd();
		htmlWriter.TableCellEnd();
	}

	/**************************************************************************/

	htmlWriter.TableRowEnd();
	htmlWriter.TableEnd(); 
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyBasePageHtmlView::write()
{
	writeInitialize();
	writeHeaderView();
	writeBodyView();
	writeFooterView();
	writeFinalize();
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeInitialize()
{
	CStrVar title;
	CStrVar background;
	
	fHtmlWriter.Initialize();	
	if(!canCachePage())
	{
		fHtmlWriter.Meta("","Pragma","no-cache");
		fHtmlWriter.Meta("","Expires",TDateTime().FormatString(
			"ddd', 'dd' 'mmm' 'yyyy' 'hh:mm:ss' EST'").c_str());
	}
	title.copyVarg("%s - %s",fPageOptions.getAppNameAbbr().c_str(),
		getPageTitle().c_str());
	fHtmlWriter.Title(title);

	if(tStrHasLen(getBackgroundImage().c_str()))
		background = fPageOptions.buildImagePath(getBackgroundImage().c_str());
	fHtmlWriter.Body(background,getBackgroundColor());
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeHeaderView()
{
	CStrVar str;

	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(getPageWidth()));
	fHtmlWriter.TableRowStart();

	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(171),THtmlHeight(114),ahLeft,avTop);
	#if 1	//BOB
	writeHeaderViewLogo();
	#else
	str.copyVarg("%s Home",fPageOptions.getAppNameAbbr().c_str());
	fHtmlWriter.LinkStart(fPageOptions.getPageLinkInfo(htmlHomePage).GetLinkURL(fPageOptions).c_str(),
		str);
	fHtmlWriter.Image(fPageOptions.buildImagePath(
		fPageOptions.getStandardImageName(main_171x114Image)).c_str(),
		str,"",aiDefault,THtmlWidthValue(171),THtmlHeightValue(114));
	fHtmlWriter.LinkEnd();
	#endif
	fHtmlWriter.TableCellEnd();
	
	TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,THtmlWidthValue(50));
	
	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(getPageWidth() - 171 - 50),
		THtmlHeight(),ahLeft,avTop);
	if(showHeaderViewAd())
	{
		#if 1
		// Put Ad code here
		#else
		fHtmlWriter.LinkStart("http://www.affinitysports.com","World Wide Fantasy Football");
		fHtmlWriter.Image(fPageOptions.buildImagePath("PlayFantasyFootballWWFF_468x60.gif").c_str(),
			"World Wide Fantasy Football","",aiDefault,THtmlWidthValue(468),THtmlHeightValue(60));
		fHtmlWriter.LinkEnd();
		#endif
	}
	fHtmlWriter.TableCellEnd();
	
	fHtmlWriter.TableRowEnd();
	
	
	fHtmlWriter.TableRowStart();
	TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,THtmlWidthValue(1),
		THtmlHeightValue(20));
	fHtmlWriter.TableCellString("");
	fHtmlWriter.TableCellString("");
	fHtmlWriter.TableRowEnd();
	
	fHtmlWriter.TableEnd(); 
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeHeaderViewLogo()
{
	CStrVar str;
	
	str.copyVarg("%s Home",fPageOptions.getAppNameAbbr().c_str());
	fHtmlWriter.LinkStart(fPageOptions.getPageLinkInfo(htmlHomePage).GetLinkURL(fPageOptions).c_str(),
		str);
	fHtmlWriter.Image(fPageOptions.buildImagePath(
		fPageOptions.getStandardImageName(main_171x114Image)).c_str(),
		str,"",aiDefault,THtmlWidthValue(171),THtmlHeightValue(114));
	fHtmlWriter.LinkEnd();
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeFooterView()
{
	THtmlViewPtr htmlViewPtr;

	if(showFooterView())
	{
		fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(getPageWidth()));

		/* Line */
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
		fHtmlWriter.Image(fPageOptions.buildImagePath("line.gif").c_str(),
			"","",aiDefault,THtmlWidthValue(getPageWidth() /*- 20*/),THtmlHeightValue(13));
		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();

		/* Having technical problems? */
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avTop);
		
		fHtmlWriter.FontStart(2, fcAbsolute, ASFantasyStandardFont(), clDefault);
		fHtmlWriter.TextString("Having technical problems? Have comments or suggestions?");
		fHtmlWriter.LineBreak();
		fHtmlWriter.TextString("Please email ");
		fHtmlWriter.WriteView(TMailToTheRefHtmlView(fPageOptions));
		fHtmlWriter.TextString(".");
		fHtmlWriter.FontEnd(); 

		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();

		if(showFooterViewIcons())
		{
			/* Blank Line */
			fHtmlWriter.TableRowStart();
			fHtmlWriter.WriteView(TEmptyTableCellHtmlView(fPageOptions,
				THtmlWidth(),THtmlHeightValue(20)));
			fHtmlWriter.TableRowEnd();

			/* Icons */
			fHtmlWriter.TableRowStart();
			fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),
				ahCenter,avMiddle);

			htmlViewPtr = fPageOptions.getFooterViewIconsHtmlView(
				showFooterViewIconsCompanyOnly());
			htmlViewPtr->write(fHtmlWriter);

			fHtmlWriter.TableCellEnd();
			fHtmlWriter.TableRowEnd();
		}

		fHtmlWriter.TableEnd(); 
	}
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeFinalize()
{
	fHtmlWriter.Finalize();
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeLinkStart(int htmlPage,
	const char* otherParams,const TEncodedParticID encodedParticID)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlPage));
	CStrVar linkURL;

	if(pageLinkInfo.IsSSLNeeded())	//BOB need to support SSL with EncodedParticID
		linkURL.copy(pageLinkInfo.GetSecureAbsoluteLinkURL(0,fPageOptions,
			otherParams));
	else
		linkURL.copy(pageLinkInfo.GetLinkURL(fPageOptions,otherParams).c_str());

	fHtmlWriter.LinkStart(linkURL,"");
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeTextLink(int htmlPage,
	const char* linkDescrip,const char* otherParams,
	const TEncodedParticID encodedParticID)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlPage));
	CStrVar descrip;

	writeLinkStart(htmlPage,otherParams,encodedParticID);

	if(tStrHasLen(linkDescrip))
		descrip.copy(linkDescrip);
	else
		descrip.copy(pageLinkInfo.GetLinkDesc().c_str());

	fHtmlWriter.TextString(descrip);
	fHtmlWriter.LinkEnd();
}

/******************************************************************************/

void ASFantasyBasePageHtmlView::writeIconLink(int htmlPage,const char* imageName,
	const char* linkDescrip,const char* otherParams,const TEncodedParticID encodedParticID)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlPage));
	CStrVar imageURL;
	CStrVar descrip;

	writeLinkStart(htmlPage,otherParams,encodedParticID);

	if(tStrHasLen(imageName))
		imageURL.copy(fPageOptions.buildImagePath(imageName));
	else
		imageURL.copy(pageLinkInfo.getImageButtonURL(fPageOptions).c_str());

	if(tStrHasLen(linkDescrip))
		descrip.copy(linkDescrip);
	else
		descrip.copy(pageLinkInfo.GetLinkDesc().c_str());

	fHtmlWriter.Image(imageURL,descrip,"",aiDefault);
	fHtmlWriter.LinkEnd();
}

/******************************************************************************/
/******************************************************************************/

void TTypeAlphaRightPanelTitleHtmlView::Write(THTMLWriter& htmlWriter)
{
#if 1
	htmlWriter.FontStart(5, fcAbsolute, ASFantasyStandardFont(), clDefault);
	htmlWriter.TextEffect(efBold,fText.c_str());
	htmlWriter.FontEnd(); 
#else
	htmlWriter.Heading(2, fText.c_str());
#endif
}

/******************************************************************************/
/******************************************************************************/

void TTypeAlphaRightPanelHtmlView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.TableStart(SHOW_BORDER);
	
	htmlWriter.TableRowStart();
	
	htmlWriter.TableCellStart(0,0,THtmlWidthValue(fViewWidth),
		THtmlHeightValue(50),ahCenter);
	writeTitleView(htmlWriter);
	htmlWriter.TableCellEnd();

	htmlWriter.TableRowEnd();

	htmlWriter.TableRowStart();

	htmlWriter.TableCellStart(0,0,THtmlWidthValue(fViewWidth));
	writeInstrucView(htmlWriter);
	htmlWriter.TableCellEnd();
	
	htmlWriter.TableRowEnd();
	
	
	htmlWriter.TableRowStart();

	htmlWriter.TableCellStart(0,0,THtmlWidthValue(fViewWidth));
	writeContentView(htmlWriter);
	htmlWriter.TableCellEnd();
	
	htmlWriter.TableRowEnd();
	
	htmlWriter.TableEnd(); 
}

/******************************************************************************/

void TTypeAlphaRightPanelHtmlView::writeTitleView(THTMLWriter& htmlWriter)
{
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	CStr127 title;
		
	if(fPageOptions.isRqstParticSet())
	{
		if(fTT == tt_Manager)
		{
			TTeamPtr teamPtr = fPageOptions.getRqstTeam();
			title.Concat(teamPtr->getManagerName());
			title.Concat("'s ");
		}
		else if(fTT == tt_League)
		{
			if(fPageOptions.isRqstLeagueSet())
			{
				TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
				title.Concat(leaguePtr->getName());
				title.Concat(" ");
			}
			title.Concat("League ");
		}
	}
	title.Concat(fTitle);

	TTypeAlphaRightPanelTitleHtmlView titleHtmlView(title.c_str());
	titleHtmlView.Write(htmlWriter);
}

/******************************************************************************/
/******************************************************************************/

void TTypeAlphaDefaultHeaderHTMLView::Build(THTMLWriter& htmlWriter,
	const THtmlPageOptions& pageOptions,bool showAd)
{
	TTypeAlphaDefaultHeaderHTMLView htmlView(pageOptions,showAd);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TTypeAlphaDefaultHeaderHTMLView::Write(THTMLWriter& htmlWriter)
{
#if 1	// Current Header
	htmlWriter.TableStart(SHOW_BORDER,THtmlWidth(ntPercent,100));
	
	htmlWriter.TableRowStart();

	htmlWriter.TableCellStart(0,0,THtmlWidthValue(171),THtmlHeight(114),ahLeft,avTop);
	htmlWriter.LinkStart(fPageOptions.getPageLinkInfo(htmlHomePage).GetLinkURL(fPageOptions).c_str(),
		"WWFF Home");
	htmlWriter.Image(fPageOptions.buildImagePath("WWFF_171x114.gif").c_str(),
		"WWFF Home","",aiDefault,THtmlWidthValue(171),THtmlHeightValue(114));
	htmlWriter.LinkEnd();
	htmlWriter.TableCellEnd();
	
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidthValue(50));
	
	htmlWriter.TableCellStart(0,0,THtmlWidthValue(
		fPageOptions.getTypeAlphaPageWidth() - 171 - 50),THtmlHeight(),ahLeft,avTop);
	if(fShowAd)
	{
		#if 1
		// Put Ad code here
		#else
		htmlWriter.LinkStart("http://www.affinitysports.com","World Wide Fantasy Football");
		htmlWriter.Image(fPageOptions.buildImagePath("PlayFantasyFootballWWFF_468x60.gif").c_str(),
			"World Wide Fantasy Football","",aiDefault,THtmlWidthValue(468),THtmlHeightValue(60));
		htmlWriter.LinkEnd();
		#endif
	}
	htmlWriter.TableCellEnd();
	
	htmlWriter.TableRowEnd();
	
	
	htmlWriter.TableRowStart();
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidthValue(1),
		THtmlHeightValue(20));
	htmlWriter.TableCellString("");
	htmlWriter.TableCellString("");
	htmlWriter.TableRowEnd();
	
	htmlWriter.TableEnd(); 
#else	// Presents, ASFLogo, Advertisment Header
	htmlWriter.TableStart(SHOW_BORDER,-100);
	
	htmlWriter.TableRowStart();
	
	htmlWriter.TableCellStart(0,4,0,ahLeft,avTop);
	htmlWriter.Image(fPageOptions.buildImagePath("Presents.gif"));
	htmlWriter.TableCellEnd();

	htmlWriter.TableRowEnd();

	
	htmlWriter.TableRowStart();

	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidthValue(5),
		THtmlHeightValue(1));
	
	htmlWriter.TableCellStart(0,0,1,ahLeft,avTop);
	htmlWriter.Image(fPageOptions.buildImagePath("ASFLogo.gif" /*"ASFLogoSm.gif"*/));
	htmlWriter.TableCellEnd();
	
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidthValue(10));
	
	htmlWriter.TableCellStart(0,0,0,ahRight,avTop);
	htmlWriter.Image(fPageOptions.buildImagePath("Advertisment.gif"));
	htmlWriter.TableCellEnd();
	
	htmlWriter.TableRowEnd();
	
	
	htmlWriter.TableRowStart();
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidthValue(1),
		THtmlHeightValue(10));
	htmlWriter.TableCell();
	htmlWriter.TableCell();
	htmlWriter.TableCell();
	htmlWriter.TableRowEnd();
	
	htmlWriter.TableEnd(); 
#endif
}

/******************************************************************************/
/******************************************************************************/

void TTypeAlphaDefaultBodyHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.TableStart(SHOW_BORDER,THtmlWidth(ntPercent,100));
	htmlWriter.TableRowStart();
	
	htmlWriter.TableCellStart(0,0,THtmlWidthValue(
		fPageOptions.getTypeAlphaIconNavColWidth()),THtmlHeight(),ahLeft,avMiddle);
	writeLeftPanelView(htmlWriter);
	htmlWriter.TableCellEnd();
	
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,100),THtmlHeight(),ahCenter,avTop);
	writeRightPanelView(htmlWriter);
	htmlWriter.TableCellEnd();
	
	htmlWriter.TableRowEnd();
	htmlWriter.TableEnd(); 
}

/******************************************************************************/
/******************************************************************************/

void TTypeAlphaDefaultFooterHTMLView::Write(THTMLWriter& htmlWriter)
{
	int iconNavColWidth = fPageOptions.getTypeAlphaIconNavColWidth();
	int leftColWidth = fPageOptions.getTypeAlphaPageWidth() - iconNavColWidth;
	
	htmlWriter.TableStart(SHOW_BORDER,THtmlWidth(ntPercent,100));
	htmlWriter.TableRowStart();

	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,
		THtmlWidthValue(iconNavColWidth));
	
	htmlWriter.TableCellStart(0,0,
		THtmlWidthValue(fPageOptions.getTypeAlphaPageWidth() - iconNavColWidth),
		THtmlHeight(),ahCenter);
		
	/**************************************************************************/

	htmlWriter.TableStart(SHOW_BORDER,THtmlWidth(ntPercent,100));

	/* Blank Line */
	htmlWriter.TableRowStart();
	htmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avMiddle);
	htmlWriter.Image(fPageOptions.buildImagePath("line.gif").c_str(),
		"","",aiDefault,THtmlWidthValue(leftColWidth),THtmlHeightValue(13));
	htmlWriter.TableCellEnd();
//	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidth(),
//		THtmlHeightValue(20));
	htmlWriter.TableRowEnd();

	/* Having technical problems? */
	htmlWriter.TableRowStart();
	htmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avTop);
	
	htmlWriter.FontStart(2, fcAbsolute, ASFantasyStandardFont(), clDefault);
	htmlWriter.TextString("Having technical problems? Have comments or suggestions?");
	htmlWriter.LineBreak();
	htmlWriter.TextString("Please email ");
	htmlWriter.WriteView(TMailToTheRefHtmlView(fPageOptions));
	htmlWriter.TextString(".");
	htmlWriter.FontEnd(); 

	htmlWriter.TableCellEnd();
	htmlWriter.TableRowEnd();

	/* Blank Line */
	htmlWriter.TableRowStart();
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidth(),
		THtmlHeightValue(20));
	htmlWriter.TableRowEnd();
	
	/**************************************************************************/
	/* 3 Images */
	htmlWriter.TableRowStart();
	htmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avTop);
	

	htmlWriter.TableStart(SHOW_BORDER);
	htmlWriter.TableRowStart();

		/* NFL Players */
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,33.33),THtmlHeight(),
		ahCenter,avMiddle);
	htmlWriter.LinkStart("http://www.nflplayers.com","NFL Players, Inc.");
	htmlWriter.Image(fPageOptions.buildImagePath("NFLPlayersInc.gif").c_str(),
		"NFL Players, Inc.","",aiDefault,THtmlWidthValue(65),THtmlHeightValue(60));
	htmlWriter.LinkEnd();
	htmlWriter.TableCellEnd();
			
		/* Affinity Sports */
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,33.33),THtmlHeight(),
		ahCenter,avMiddle);
	htmlWriter.LinkStart("http://www.affinitysports.com","Affinity Sports, Inc.");
	htmlWriter.Image(fPageOptions.buildSiteImagePath("ASILetterHeadLogo.gif").c_str(),
		"Affinity Sports, Inc.","",aiDefault,THtmlWidthValue(133),THtmlHeightValue(40));
	htmlWriter.LinkEnd();
	htmlWriter.TableCellEnd();

		/* STATS Inc */
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,33.33),THtmlHeight(),
		ahCenter,avMiddle);
	htmlWriter.LinkStart("http://www.stats.com","STATS, Inc.");
	htmlWriter.Image(fPageOptions.buildSiteImagePath("StatsInc_127x34.gif").c_str(),
		"STATS, Inc.","",aiDefault,THtmlWidthValue(127),THtmlHeightValue(34));
	htmlWriter.LinkEnd();
	htmlWriter.TableCellEnd();
			
	htmlWriter.TableRowEnd();

	htmlWriter.TableRowStart();

		/* NFL Players */
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,33.33),THtmlHeight(),
		ahCenter,avTop);
	htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);
	htmlWriter.TextString("WWFF is an officially licensed");
	htmlWriter.LineBreak();
	htmlWriter.TextString("product of the NFL Players.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("Players Inc logo is a registered");
	htmlWriter.LineBreak();
	htmlWriter.TextString("trademark of the NFL Players.");
	htmlWriter.FontEnd();
	htmlWriter.TableCellEnd();

		/* Affinity Sports */
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,33.33),THtmlHeight(),
		ahCenter,avTop);
	htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);
	htmlWriter.TextString(CStrVar().copyVarg("Copyright © %d by",
		(int)DateYear(GetSystemDate())));
	htmlWriter.LineBreak();
	htmlWriter.TextString("Affinity Sports, Inc.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("All Rights Reserved.");
	htmlWriter.FontEnd();
	htmlWriter.TableCellEnd();

		/* STATS Inc */
	htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,33.33),THtmlHeight(),
		ahCenter,avTop);
	htmlWriter.FontStart(1, fcAbsolute, ASFantasyStandardFont(), clDefault);
	htmlWriter.TextString("WWFF stats provided by");
	htmlWriter.LineBreak();
	htmlWriter.TextString("STATS, Inc.");
	htmlWriter.LineBreak();
	htmlWriter.TextString(CStrVar().copyVarg("Statistics Copyright © %d by",
		(int)DateYear(GetSystemDate())));
	htmlWriter.LineBreak();
	htmlWriter.TextString("STATS, Inc.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("All Rights Reserved.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("Commercial distribution without");
	htmlWriter.LineBreak();
	htmlWriter.TextString("expressed written consent by");
	htmlWriter.LineBreak();
	htmlWriter.TextString("STATS, Inc. is strictly prohibited.");
	htmlWriter.FontEnd();
	htmlWriter.TableCellEnd();

	htmlWriter.TableRowEnd();
	htmlWriter.TableEnd(); 


	htmlWriter.TableCellEnd();
	htmlWriter.TableRowEnd();

	/**************************************************************************/
	
	htmlWriter.TableEnd(); 
	
	/**************************************************************************/
	
	htmlWriter.TableCellEnd();
	htmlWriter.TableRowEnd();
	htmlWriter.TableEnd(); 
}

/******************************************************************************/
/******************************************************************************/

void TTypeAlphaPageHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.Initialize();	
	writePageTitle(htmlWriter);
	htmlWriter.Body(fPageOptions.buildImagePath("ASFBackground_Tile.gif").c_str() /*,clWhite*/ );
	
	htmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(
		fPageOptions.getTypeAlphaPageWidth()) /*THtmlWidth(ntPercent,100)*/);
	
	htmlWriter.TableRowStart(ahCenter);
	htmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),getHeaderAlignHoriz());
	writeHeaderView(htmlWriter);
	htmlWriter.TableCellEnd();
	htmlWriter.TableRowEnd();
	
	htmlWriter.TableRowStart();
	htmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),getBodyAlignHoriz());
	writeBodyView(htmlWriter);
	htmlWriter.TableCellEnd();
	htmlWriter.TableRowEnd();

	if(showFooterView())
	{
		htmlWriter.TableRowStart();
		htmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),getFooterAlignHoriz());
		writeFooterView(htmlWriter);
		htmlWriter.TableCellEnd();
		htmlWriter.TableRowEnd();
	}
	
	htmlWriter.TableEnd(); 
	
	htmlWriter.Finalize();
}

/******************************************************************************/

void TTypeAlphaPageHTMLView::writePageTitle(THTMLWriter& htmlWriter)
{
	CStrVar title;

	title.copyVarg("%s - %s",fPageOptions.getAppNameAbbr().c_str(),getPageTitle().c_str());
	htmlWriter.Title(title);
}

/******************************************************************************/
/******************************************************************************/

void TTypeBetaPageTitleHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.FontStart(6,fcAbsolute,ASFantasyStandardFont());
	htmlWriter.TextEffect(efBold,fTitle);
	htmlWriter.FontEnd();
}

/******************************************************************************/
/******************************************************************************/

void TTypeBetaSectionTitleHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.FontStart(4,fcAbsolute,ASFantasyStandardFont());
	htmlWriter.TextEffectStart(efBold);
	htmlWriter.TextParagraph(fTitle);
	htmlWriter.TextEffectEnd(efBold);
	htmlWriter.FontEnd();
}

/******************************************************************************/
/******************************************************************************/

void TTypeBetaSectionTextHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.FontStart(2,fcAbsolute,ASFantasyStandardFont(),fTextColor);
	htmlWriter.TextEffect(efBold,fText);
	htmlWriter.FontEnd();
}

/******************************************************************************/
/******************************************************************************/

void TTypeBetaTinyTextHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.FontStart(1,fcAbsolute,ASFantasyStandardFont());
	htmlWriter.TextParagraph(fText);
	htmlWriter.FontEnd();
}

/******************************************************************************/
/******************************************************************************/
#if 0	//BOB remove - convert Beta above to Gamma (or maybe to Signup)

void TTypeBetaHtmlPage::write()
{
	writeInitialize();
	writeHeaderView();
	writeBodyView();
	writeFooterView();
	writeFinalize();
}

/******************************************************************************/

void TTypeBetaHtmlPage::writeInitialize()
{
	CStrVar title;
	
	fHtmlWriter.Initialize();	
	if(!canCachePage())
	{
		fHtmlWriter.Meta("","Pragma","no-cache");
		fHtmlWriter.Meta("","Expires",TDateTime().FormatString(
			"ddd', 'dd' 'mmm' 'yyyy' 'hh:mm:ss' EST'").c_str());
	}
	title.copyVarg("%s - %s",fPageOptions.getAppNameAbbr().c_str(),
		getPageTitle().c_str());
	fHtmlWriter.Title(title);
	fHtmlWriter.Body(getBackgroundImage().c_str(),getBackgroundColor());
}

/******************************************************************************/
 
void TTypeBetaHtmlPage::writeHeaderView()
{
	fHtmlWriter.TableStart(0,THtmlWidthValue(getPageWidth()));
	fHtmlWriter.TableRowStart();

	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(175),THtmlHeight(),ahLeft,avTop);

	fHtmlWriter.LinkStart(fPageOptions.getPageLinkInfo(htmlHomePage).GetLinkURL(fPageOptions).c_str(),
		"WWFF Home");
	fHtmlWriter.Image(fPageOptions.buildImagePath("WWFF_171x114.gif").c_str(),
		"WWFF Home","",aiDefault,THtmlWidthValue(171),THtmlHeightValue(114));
	fHtmlWriter.LinkEnd();

	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableCellStart(0,0,THtmlWidthValue(getPageWidth() - 175),
		THtmlHeight(),ahCenter,avMiddle);
	TTypeBetaPageTitleHtmlView::build(fHtmlWriter,getPageTitle());
	fHtmlWriter.TableCellEnd();

	fHtmlWriter.TableRowEnd();
	fHtmlWriter.TableEnd();
}

/******************************************************************************/

void TTypeBetaHtmlPage::writeFinalize()
{
	fHtmlWriter.Finalize();
}

#endif
/******************************************************************************/
/******************************************************************************/

void TTypeGammaPageHtmlView::writeHeaderView()
{
	vector<vector<int> > htmlPageArray;

	ASFantasyBasePageHtmlView::writeHeaderView();

	if(showHeaderViewNavButtonBar())
	{
		fPageOptions.loadHeaderViewNavButtonBarArray(htmlPageArray);
		writeHeaderViewNavButtonBar(htmlPageArray);
	}
}

/******************************************************************************/

void TTypeGammaPageHtmlView::writeHeaderViewNavButtonBar(
	vector<vector<int> >& htmlPageArray)
{
	vector<vector<int> >::iterator rowIter;
	vector<int>::iterator colIter;
	int htmlPage;

	if(htmlPageArray.size() == 0)
		return;

	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidth(),1);

	for(rowIter = htmlPageArray.begin(); rowIter != htmlPageArray.end(); ++rowIter)
	{
		fHtmlWriter.TableRowStart();

		for(colIter = (*rowIter).begin(); colIter != (*rowIter).end(); ++colIter)
		{
			htmlPage = *colIter;

			fHtmlWriter.TableCellView(TButtonNavHtmlView(fPageOptions,htmlPage,
				THtmlWidthValue(125),THtmlHeightValue(20)),0,0,
				THtmlWidthValue(125),THtmlHeightValue(20),ahCenter,avTop);
		}

		fHtmlWriter.TableRowEnd();
	}
		
	fHtmlWriter.TableEnd();
}

/******************************************************************************/

void TTypeGammaPageHtmlView::writeBodyView()
{
	CStrVar str;

	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(getPageWidth()));
	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter,avTop);
	
	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(getBodyViewWidth()));

	/**************************************************************************/
	// Title

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeightValue(50),ahCenter,
		avMiddle);
	writeBodyViewTitle();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/
	// Instructions

	str = getBodyViewInstructions();
	if(str.hasLen())
	{
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
		writeBodyViewInstructions();
		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();
	}

	/**************************************************************************/
	// Body

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),
		THtmlHeightValue(getBodyViewBodyHeight()),ahCenter,avTop);
	writeBodyViewBody();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/
	// Spacer

	fHtmlWriter.TableRowStart();
	fHtmlWriter.WriteView(TEmptyTableCellHtmlView(fPageOptions,
		THtmlWidth(),THtmlHeightValue(20)));
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	fHtmlWriter.TableEnd();

	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
	fHtmlWriter.TableEnd();
}

/******************************************************************************/

void TTypeGammaPageHtmlView::writeBodyViewTitle()
{
	ASFantasyBodyViewTitleType titleType = getBodyViewTitleType();
	CStrVar title;
		
	if(fPageOptions.isRqstParticSet())
	{
		if(titleType == tt_Manager)
		{
			TTeamPtr teamPtr = fPageOptions.getRqstTeam();
			title.concat(teamPtr->getManagerName());
			title.concat("'s ");
		}
		else if(titleType == tt_League)
		{
			if(fPageOptions.isRqstLeagueSet())
			{
				TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
				title.concat(leaguePtr->getName());
				title.concat(" ");
			}
			title.concat("League ");
		}
	}
	title.concat(getPageTitle());

	fHtmlWriter.FontStart(5, fcAbsolute, ASFantasyStandardFont(), clDefault);
	fHtmlWriter.TextEffect(efBold,title);
	fHtmlWriter.FontEnd(); 
}

/******************************************************************************/

void TTypeGammaPageHtmlView::writeBodyViewInstructions()
{
	fHtmlWriter.FontStart(2, fcAbsolute, ASFantasyStandardFont(), clDefault);
	fHtmlWriter.TextParagraph(getBodyViewInstructions());
	fHtmlWriter.FontEnd(); 
}

/******************************************************************************/

void TTypeGammaPageHtmlView::writeBodyViewBody()
{
	// This needs to be defined for pages that may not show a body all of the time.
	fHtmlWriter.TextHtml("&nbsp;");
}

/******************************************************************************/
/******************************************************************************/

void TMessagePageHtmlView::writeBodyView()
{
	fHtmlWriter.FontStart(3, fcAbsolute, ASFantasyStandardFont(), clDefault);
	fHtmlWriter.TextEffectStart(efBold);
	fHtmlWriter.WriteView(TParagraphHtmlView(fPageOptions,fMessage));
	fHtmlWriter.TextEffectEnd(efBold);
	fHtmlWriter.FontEnd(); 
}

/******************************************************************************/
/******************************************************************************/

void TSignupTextNavHtmlView::write(THTMLWriter& htmlWriter)
{
	CStrVar otherParams;

	otherParams.copyVarg("Source=%s",CurrentGameID());
	fPage.writeTextLink(htmlSignupIntroGetPage,NULL,otherParams);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
