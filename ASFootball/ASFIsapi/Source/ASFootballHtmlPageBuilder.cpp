/* ASFootballHtmlPageBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballHtmlPageBuilder.h"

namespace asfootball
{

/******************************************************************************/

// This list must be insync with the ASFootballHTMLPage enum.

const THTMLPageLinkInfo gHTMLPageInfoList[] =
{					//	fImageBaseName,	fImageExtName,fLinkURL						fLinkType		fLinkDesc		fIsMemberNeeded	fIsParticNeeded	fIsSSLNeeded
	THTMLPageLinkInfo(	"",				"",			"Undefined",					hplt_Relative,	"Undefined",	false,			false,			false ),

	THTMLPageLinkInfo(	"Home",			".gif",		"Default",						hplt_Relative,	"Home",			false,			false,			false ),
	THTMLPageLinkInfo(	"",				"",			"Error",						hplt_IsapiDll,	"Error",		false,			false,			false ),
	THTMLPageLinkInfo(	"",				"",			"Requirements",					hplt_Relative,	"System Requirements",false,	false,			false ),

	THTMLPageLinkInfo(	"",				"",			"Signup",						hplt_IsapiDll,	"Sign-Up",		false,			false,			false ),
	THTMLPageLinkInfo(	"",				"",			"SignupWhichGet",				hplt_IsapiDll,	"Sign-Up",		false,			false,			false ),
	THTMLPageLinkInfo(	"",				"",			"NewMemberSignupPremiumGet",	hplt_IsapiDll,	"Sign-Up",		false,			false,			true ),
	THTMLPageLinkInfo(	"",				"",			"NewMemberSignupStandardGet",	hplt_IsapiDll,	"",				false,			false,			true ),
	THTMLPageLinkInfo(	"",				"",			"NewMemberSignupPost",			hplt_IsapiDll,	"",				false,			false,			true ),

//	THTMLPageLinkInfo(	"",				"",			"Signup",						hplt_Relative,	"Sign-Up",		true,			false,			true ),
	THTMLPageLinkInfo(	"",				"",			"NewParticSignupPremiumGet",	hplt_IsapiDll,	"Sign-Up",		true,			false,			true ),
	THTMLPageLinkInfo(	"",				"",			"NewParticSignupStandardGet",	hplt_IsapiDll,	"",				true,			false,			true ),
	THTMLPageLinkInfo(	"",				"",			"NewParticSignupPost",			hplt_IsapiDll,	"",				true,			false,			true ),
	THTMLPageLinkInfo(	"",				"",			"ParticUpgradeGet",				hplt_IsapiDll,	"Upgrade",		true,			true,			true ),
	THTMLPageLinkInfo(	"",				"",			"ParticUpgradePost",			hplt_IsapiDll,	"",				true,			true,			true ),

	THTMLPageLinkInfo(	"",				"",			"ParticPremiumTrialGet",		hplt_IsapiDll,	"Trial",		true,			true,			false ),
	THTMLPageLinkInfo(	"",				"",			"ParticPremiumTrialPost",		hplt_IsapiDll,	"",				true,			true,			false ),

	THTMLPageLinkInfo(	"",				"",			"ParticPick",					hplt_IsapiDll,	"",				true,			true,			false ),
	THTMLPageLinkInfo(	"Hub",			".gif",		"Hub",							hplt_IsapiDll,	"Front Office",	true,			true,			false ),
	THTMLPageLinkInfo(	"",				"",			"Custom",						hplt_IsapiDll,	"",				true,			true,			false ),
	THTMLPageLinkInfo(	"",				"",			"LeagueSignup",					hplt_IsapiDll,	"League Signup",true,			true,			false ),
	THTMLPageLinkInfo(	"Teams",		".gif",		"Teams",						hplt_IsapiDll,	"Teams",		true,			true,			false ),

	THTMLPageLinkInfo(	"DraftRankings",".gif",		"DraftRankings",				hplt_IsapiDll,	"Draft Ranking",true,			true,			false ),
	THTMLPageLinkInfo(	"DraftResults",	".gif",		"DraftResults",					hplt_IsapiDll,	"Draft Results",true,			true,			false ),

	THTMLPageLinkInfo(	"Schedule",		".gif",		"Schedule",						hplt_IsapiDll,	"Schedule",		true,			true,			false ),
	THTMLPageLinkInfo(	"Lineup",		".gif",		"Lineup",						hplt_IsapiDll,	"Lineup",		true,			true,			false ),
	THTMLPageLinkInfo(	"GameResults",	".gif",		"GameResults",					hplt_IsapiDll,	"Game Results",	true,			true,			false ),
	THTMLPageLinkInfo(	"Standings",	".gif",		"Standings",					hplt_IsapiDll,	"Standings",	true,			true,			false ),
	THTMLPageLinkInfo(	"FreeAgent",	".gif",		"FreeAgent",					hplt_IsapiDll,	"Free Agents",	true,			true,			false ),
	THTMLPageLinkInfo(	"Trade",		".gif",		"Trade",						hplt_IsapiDll,	"Trades",		true,			true,			false ),
	THTMLPageLinkInfo(	"Playoff",		".gif",		"Playoff",						hplt_IsapiDll,	"Playoffs",		true,			true,			false ),
//	THTMLPageLinkInfo(	"RecentTrans",	".gif",		"RecentTrans",					hplt_IsapiDll,	"Rec. Trans." )

//	THTMLPageLinkInfo(	"",	".gif", "", "" )
};

/******************************************************************************/

AnsiString ASFootballHtmlPageOptions::getWebURLBasePath(int /*siteID*/,
	bool secure = false) const
{
	if(secure)
		return("https://www.affinitysports.com/");
	else
		return("http://www.affinitysports.com/");
}

/******************************************************************************/

CStrVar ASFootballHtmlPageOptions::getJavaDefaultArchive(
	ASFantasyJavaArchive fja) const
{
	if(fja == fja_Draft)
		return("ASFbJavaDraft3");

	return("ASFbJavaSeason4");
}

/******************************************************************************/

const THTMLPageLinkInfo& ASFootballHtmlPageOptions::getPageLinkInfo(
	int htmlPage) const
{
	if((htmlPage >= 0) &&
			(htmlPage < sizeof(gHTMLPageInfoList) / sizeof(*gHTMLPageInfoList)))
		return(gHTMLPageInfoList[htmlPage]);

	throw ASIException("ASFootballHtmlPageOptions::getPageLinkInfo: invalid htmlPage");
}

/******************************************************************************/

int ASFootballHtmlPageOptions::getPageLinkInfoEnum(const AnsiString& pageName)
	const
{
	AnsiString name;
	int i;

	for(i = 0; i < sizeof(gHTMLPageInfoList) / sizeof(*gHTMLPageInfoList); i++)
	{
		name = gHTMLPageInfoList[i].GetName();
		if(strcmp(name.c_str(),pageName.c_str()) == 0)
//BOB		if(gHTMLPageInfoList[i].GetName() == pageName)
			return(i);
	}

	throw ASIException("ASFootballHtmlPageOptions::getPageLinkInfoByName: invalid htmlPage");
}

/******************************************************************************/

CStrVar ASFootballHtmlPageOptions::getStandardImageName(
	const int standardImage) const
{
	if(standardImage == mainBackgroundImage)
		return("ASFBackground_Tile.gif");
	if(standardImage == main_171x114Image)
		return("WWFF_171x114.gif");
	if(standardImage == listBulletImage)
		return("Foot_30x18.gif");

	throw ASIException("ASFootballHtmlPageOptions::getStandardImageName: unknown standardImage");
}

/******************************************************************************/

CStrVar ASFootballHtmlPageOptions::getStandardImageRootPath(
	const int standardImage) const
{
	return(getImageRootPath().c_str());
}

/******************************************************************************/

void ASFootballHtmlPageOptions::loadHeaderViewNavButtonBarArray(
	vector<vector<int> >& htmlPageArray)
{
	vector<int> htmlPageRow;

	htmlPageArray.erase(htmlPageArray.begin(),htmlPageArray.end());

	if(isSeasonView())
	{
		htmlPageRow.push_back(htmlHomePage);
		htmlPageRow.push_back(htmlHubPage);
		htmlPageRow.push_back(htmlSchedulePage);
		htmlPageRow.push_back(htmlLineupPage);
		htmlPageRow.push_back(htmlGameResultsPage);

		htmlPageArray.push_back(htmlPageRow);

		htmlPageRow.erase(htmlPageRow.begin(),htmlPageRow.end());
		htmlPageRow.push_back(htmlStandingsPage);
		htmlPageRow.push_back(htmlFreeAgentPage);
		htmlPageRow.push_back(htmlTradePage);
		htmlPageRow.push_back(htmlTeamsPage);

		htmlPageArray.push_back(htmlPageRow);
	}
	else
	{
		htmlPageRow.push_back(htmlHomePage);
		htmlPageRow.push_back(htmlHubPage);
		htmlPageRow.push_back(htmlDraftRankingsPage);
		htmlPageRow.push_back(htmlDraftResultsPage);
		htmlPageRow.push_back(htmlTeamsPage);

		htmlPageArray.push_back(htmlPageRow);
	}
}

/******************************************************************************/

THtmlViewPtr ASFootballHtmlPageOptions::getFooterViewIconsHtmlView(
	const bool showCompanyOnly)
{
	return(ASFootballFooterViewIcons::newInstance(*this,showCompanyOnly));
}

/******************************************************************************/
/******************************************************************************/
#if 0	//BOB

void TSeasonIconNavColumnHTMLView::Build(THTMLWriter& htmlWriter,
	const THtmlPageOptions& pageOptions)
{
	TSeasonIconNavColumnHTMLView htmlView(pageOptions);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TSeasonIconNavColumnHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.TableStart(SHOW_BORDER,
		THtmlWidthValue(fPageOptions.getTypeAlphaIconNavColWidth()));
	
	WriteRow(htmlWriter,fPageOptions,htmlHomePage);
	WriteRow(htmlWriter,fPageOptions,htmlHubPage);
	WriteRow(htmlWriter,fPageOptions,htmlSchedulePage);
	WriteRow(htmlWriter,fPageOptions,htmlLineupPage);
	WriteRow(htmlWriter,fPageOptions,htmlGameResultsPage);
	WriteRow(htmlWriter,fPageOptions,htmlStandingsPage);
	WriteRow(htmlWriter,fPageOptions,htmlFreeAgentPage);
	WriteRow(htmlWriter,fPageOptions,htmlTradePage);
	
	htmlWriter.TableEnd();
}

/******************************************************************************/
/******************************************************************************/

void TDraftIconNavColumnHTMLView::Build(THTMLWriter& htmlWriter,
	const THtmlPageOptions& pageOptions)
{
	TDraftIconNavColumnHTMLView htmlView(pageOptions);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TDraftIconNavColumnHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.TableStart(SHOW_BORDER,
		THtmlWidthValue(fPageOptions.getTypeAlphaIconNavColWidth()));
	
	WriteRow(htmlWriter,fPageOptions,htmlHomePage);
	WriteRow(htmlWriter,fPageOptions,htmlHubPage);
	WriteRow(htmlWriter,fPageOptions,htmlDraftRankingsPage);
	WriteRow(htmlWriter,fPageOptions,htmlDraftResultsPage);
	
	htmlWriter.TableEnd();
}

/******************************************************************************/
/******************************************************************************/

void TSeasonRemoteControlHtmlView::Build(THTMLWriter& htmlWriter,
	THtmlPageOptions& pageOptions)
{
	TSeasonRemoteControlHtmlView htmlView(pageOptions);
	htmlView.Write(htmlWriter);
}
		
/******************************************************************************/

void TSeasonRemoteControlHtmlView::Write(THTMLWriter& htmlWriter)
{
	int homeCoords[] = { 59, 12, 41, 13, 32, 18, 29, 25, 31, 31, 44, 38, 52, 38, 61, 38, 73, 38, 84, 34, 89, 27, 87, 17, 75, 14, 63, 11 };
	int hubCoords[] = { 82, 53, 55, 49, 35, 53, 19, 61, 14, 69, 17, 80, 36, 87, 57, 90, 77, 88, 97, 79, 104, 68, 100, 60 };
	int scheduleCoords[] = { 13, 98, 104, 117 };
	int lineupCoords[] = { 11, 130, 103, 147 };
	int gameResultsCoords[] = { 12, 157, 107, 176 };
	int standingsCoords[] = { 12, 190, 107, 209 };
	int freeAgentCoords[] = { 13, 223, 104, 241 };
	int tradeCoords[] = { 26, 253, 17, 259, 16, 268, 21, 274, 30, 278, 39, 275, 97, 274, 97, 257, 43, 256, 38, 252 };
	int teamsCoords[] = { 37, 288, 30, 286, 23, 289, 17, 298, 20, 308, 29, 315, 40, 311, 96, 311, 95, 292, 46, 293 };
	
	htmlWriter.MapStart("RemoteControlMap");
	
	htmlWriter.MapArea(shPolygon,homeCoords,sizeof(homeCoords)/sizeof(*homeCoords),
		fPageOptions.getPageLinkInfo(htmlHomePage).GetLinkURL(fPageOptions).c_str());
		
	htmlWriter.MapArea(shPolygon,hubCoords,sizeof(hubCoords)/sizeof(*hubCoords),
		fPageOptions.getPageLinkInfo(htmlHubPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shRect,scheduleCoords,sizeof(scheduleCoords)/sizeof(*scheduleCoords),
		fPageOptions.getPageLinkInfo(htmlSchedulePage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shRect,lineupCoords,sizeof(lineupCoords)/sizeof(*lineupCoords),
		fPageOptions.getPageLinkInfo(htmlLineupPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shRect,gameResultsCoords,sizeof(gameResultsCoords)/sizeof(*gameResultsCoords),
		fPageOptions.getPageLinkInfo(htmlGameResultsPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shRect,standingsCoords,sizeof(standingsCoords)/sizeof(*standingsCoords),
		fPageOptions.getPageLinkInfo(htmlStandingsPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shRect,freeAgentCoords,sizeof(freeAgentCoords)/sizeof(*freeAgentCoords),
		fPageOptions.getPageLinkInfo(htmlFreeAgentPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shPolygon,tradeCoords,sizeof(tradeCoords)/sizeof(*tradeCoords),
		fPageOptions.getPageLinkInfo(htmlTradePage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shPolygon,teamsCoords,sizeof(teamsCoords)/sizeof(*teamsCoords),
		fPageOptions.getPageLinkInfo(htmlTeamsPage).GetLinkURL(fPageOptions).c_str());
		
	htmlWriter.MapEnd();

	htmlWriter.Image(fPageOptions.buildImagePath("RemoteSeason_123X400.gif").c_str(),
		"","#RemoteControlMap",aiDefault,THtmlWidthValue(123),
		THtmlHeightValue(400));
}

/******************************************************************************/
/******************************************************************************/

void TDraftRemoteControlHtmlView::Build(THTMLWriter& htmlWriter,
	THtmlPageOptions& pageOptions)
{
	TDraftRemoteControlHtmlView htmlView(pageOptions);
	htmlView.Write(htmlWriter);
}
		
/******************************************************************************/

void TDraftRemoteControlHtmlView::Write(THTMLWriter& htmlWriter)
{
	int homeCoords[] = { 82, 17, 66, 18, 56, 21, 45, 26, 32, 34, 23, 41, 23, 47, 27, 50, 37, 48, 53, 46, 67, 39, 78, 33, 83, 27 };
	int hubCoords[] = { 60, 54, 43, 63, 28, 71, 17, 82, 13, 92, 20, 98, 32, 99, 44, 97, 54, 94, 63, 91, 74, 86, 91, 75, 100, 65, 99, 57, 97, 52, 92, 49, 78, 49 };
	int draftRankingCoords[] = { 106, 141, 16, 173, 14, 190, 104, 160 };
	int draftResultsCoords[] = { 106, 186, 16, 215, 15, 231, 104, 203 };
	int teamsCoords[] = { 108, 237, 43, 259, 39, 255, 32, 253, 23, 255, 18, 261, 13, 270, 11, 280, 16, 286, 21, 288, 28, 287, 35, 284, 36, 281, 107, 257 };
	
	htmlWriter.MapStart("RemoteControlMap");
	
	htmlWriter.MapArea(shPolygon,homeCoords,sizeof(homeCoords)/sizeof(*homeCoords),
		fPageOptions.getPageLinkInfo(htmlHomePage).GetLinkURL(fPageOptions).c_str());
		
	htmlWriter.MapArea(shPolygon,hubCoords,sizeof(hubCoords)/sizeof(*hubCoords),
		fPageOptions.getPageLinkInfo(htmlHubPage).GetLinkURL(fPageOptions).c_str());
		
	htmlWriter.MapArea(shPolygon,draftRankingCoords,
		sizeof(draftRankingCoords)/sizeof(*draftRankingCoords),
		fPageOptions.getPageLinkInfo(htmlDraftRankingsPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shPolygon,draftResultsCoords,
		sizeof(draftResultsCoords)/sizeof(*draftResultsCoords),
		fPageOptions.getPageLinkInfo(htmlDraftResultsPage).GetLinkURL(fPageOptions).c_str());

	htmlWriter.MapArea(shPolygon,teamsCoords,sizeof(teamsCoords)/sizeof(*teamsCoords),
		fPageOptions.getPageLinkInfo(htmlTeamsPage).GetLinkURL(fPageOptions).c_str());
		
	htmlWriter.MapEnd();

	htmlWriter.Image(fPageOptions.buildImagePath("RemoteDraft_123x400.gif").c_str(),
		"","#RemoteControlMap",aiDefault,THtmlWidthValue(123),
		THtmlHeightValue(400));
}

/******************************************************************************/
/******************************************************************************/

void TSeasonTextNavLineHTMLView::Build(THTMLWriter& htmlWriter,
	const THtmlPageOptions& pageOptions)
{
	TSeasonTextNavLineHTMLView htmlView(pageOptions);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TSeasonTextNavLineHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.FontStart(2, fcAbsolute, ASFantasyStandardFont(), clDefault);
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlHomePage);
//BOB	htmlWriter.Link("/ASFootball/Default.html", "", "Home");	//BOB hard-code for now
	
	htmlWriter.TextString(" | ");

	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlHubPage);
	htmlWriter.TextString(" | ");

	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlSchedulePage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLineupPage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlGameResultsPage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlStandingsPage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlFreeAgentPage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlTradePage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlTeamsPage);
		
	htmlWriter.FontEnd();
}

/******************************************************************************/
/******************************************************************************/

void TDraftTextNavLineHTMLView::Build(THTMLWriter& htmlWriter,
	const THtmlPageOptions& pageOptions)
{
	TDraftTextNavLineHTMLView htmlView(pageOptions);
	htmlView.Write(htmlWriter);
}

/******************************************************************************/

void TDraftTextNavLineHTMLView::Write(THTMLWriter& htmlWriter)
{
	htmlWriter.FontStart(2, fcAbsolute, ASFantasyStandardFont(), clDefault);
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlHomePage);
//BOB	htmlWriter.Link("/ASFootball/Default.html", "", "Home");	//BOB hard-code for now

	htmlWriter.TextString(" | ");

	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlHubPage);
	htmlWriter.TextString(" | ");

	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftResultsPage);
	htmlWriter.TextString(" | ");
	
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlTeamsPage);

	htmlWriter.FontEnd();
}

/******************************************************************************/
/******************************************************************************/

void TFootballIconNavColumnHTMLView::Write(THTMLWriter& htmlWriter)
{
	if(fPageOptions.isSeasonView())
		TSeasonIconNavColumnHTMLView::Build(htmlWriter,fPageOptions);
	else
		TDraftIconNavColumnHTMLView::Build(htmlWriter,fPageOptions);
}

/******************************************************************************/
/******************************************************************************/

void TFootballRemoteControlHtmlView::Write(THTMLWriter& htmlWriter)
{
	if(fPageOptions.isSeasonView() || fPageOptions.isBackdoorAccess())
		TSeasonRemoteControlHtmlView::Build(htmlWriter,fPageOptions);
	else
		TDraftRemoteControlHtmlView::Build(htmlWriter,fPageOptions);
}

/******************************************************************************/
/******************************************************************************/

void TFootballTextNavLineHTMLView::Write(THTMLWriter& htmlWriter)
{
	if(fPageOptions.isSeasonView() || fPageOptions.isBackdoorAccess())
		TSeasonTextNavLineHTMLView::Build(htmlWriter,fPageOptions);
	else
		TDraftTextNavLineHTMLView::Build(htmlWriter,fPageOptions);
}

/******************************************************************************/
/******************************************************************************/

void TFootballTypeAlphaPageHTMLView::writeFooterView(THTMLWriter& htmlWriter)
{
	int iconNavColWidth = fPageOptions.getTypeAlphaIconNavColWidth();

	htmlWriter.TableStart(SHOW_BORDER,THtmlWidth(ntPercent,100));
	
	// Spacing from above
	htmlWriter.TableRowStart();
	
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,
		THtmlWidthValue(iconNavColWidth),THtmlHeightValue(30));
	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,
		THtmlWidth(),THtmlHeightValue(30));

	htmlWriter.TableRowEnd();

	// Footer View	
	htmlWriter.TableRowStart();

	TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,
		THtmlWidthValue(iconNavColWidth));
	
	htmlWriter.TableCellStart(0,0,
		THtmlWidthValue(fPageOptions.getTypeAlphaPageWidth() - iconNavColWidth),
		THtmlHeight(),ahCenter);
	fFooterView.Write(htmlWriter);
	htmlWriter.TableCellEnd();

	htmlWriter.TableRowEnd();

	htmlWriter.TableEnd(); 

	
	TTypeAlphaPageHTMLView::writeFooterView(htmlWriter);
}

#endif
/******************************************************************************/
/******************************************************************************/

void ASFootballFooterViewIcons::writeSponsorIcon(THTMLWriter& htmlWriter)
{
	htmlWriter.LinkStart("http://www.mplayer.com","mplayer.com");
	htmlWriter.Image(fPageOptions.buildSiteImagePath("Mplayer_115x115.gif").c_str(),
		"mplayer.com","",aiDefault,THtmlWidthValue(60),THtmlHeightValue(60));
	htmlWriter.LinkEnd();
}

/******************************************************************************/

void ASFootballFooterViewIcons::writeSponsorText(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString("Access ");
	htmlWriter.TextString(fPageOptions.getAppNameAbbr().c_str());
	htmlWriter.LineBreak();
	htmlWriter.TextString(" through mplayer.com.");
}

/******************************************************************************/

void ASFootballFooterViewIcons::writePlayerAssocIcon(THTMLWriter& htmlWriter)
{
	htmlWriter.LinkStart("http://www.nflplayers.com","NFL Players, Inc.");
	htmlWriter.Image(fPageOptions.buildImagePath("NFLPlayersInc.gif").c_str(),
		"NFL Players, Inc.","",aiDefault,THtmlWidthValue(65),THtmlHeightValue(60));
	htmlWriter.LinkEnd();
}

/******************************************************************************/

void ASFootballFooterViewIcons::writePlayerAssocText(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString(fPageOptions.getAppNameAbbr().c_str());
	htmlWriter.TextString(" is an officially licensed");
	htmlWriter.LineBreak();
	htmlWriter.TextString("product of the NFL Players.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("Players Inc logo is a registered");
	htmlWriter.LineBreak();
	htmlWriter.TextString("trademark of the NFL Players.");
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
