/* ASBaseballHtmlPageBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballHtmlPageBuilder.h"

namespace asbaseball
{

/******************************************************************************/

// This list must be insync with the ASBaseballHtmlPage enum.

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

AnsiString ASBaseballHtmlPageOptions::getWebURLBasePath(int /*siteID*/,
	bool secure = false) const
{
	if(secure)
		return("https://www.affinitysports.com/");
	else
		return("http://www.affinitysports.com/");
}

/******************************************************************************/

CStrVar ASBaseballHtmlPageOptions::getJavaDefaultArchive(
	ASFantasyJavaArchive fja) const
{
	if(fja == fja_Draft)
		return("ASBbJavaDraft6");

	return("ASBbJavaSeason9");
}

/******************************************************************************/

const THTMLPageLinkInfo& ASBaseballHtmlPageOptions::getPageLinkInfo(int htmlPage)
	const
{
	if((htmlPage >= 0) &&
			(htmlPage < sizeof(gHTMLPageInfoList) / sizeof(*gHTMLPageInfoList)))
		return(gHTMLPageInfoList[htmlPage]);

	throw ASIException("ASBaseballHtmlPageOptions::getPageLinkInfo: invalid htmlPage");
}

/******************************************************************************/

int ASBaseballHtmlPageOptions::getPageLinkInfoEnum(const AnsiString& pageName)
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

	throw ASIException("ASBaseballHtmlPageOptions::getPageLinkInfoByName: invalid htmlPage");
}

/******************************************************************************/

CStrVar ASBaseballHtmlPageOptions::getStandardImageName(
	const int standardImage) const
{
	if(standardImage == mainBackgroundImage)
		return("ASBbackground_Tile.jpg");
	if(standardImage == main_171x114Image)
		return("WWFB_171x114.jpg");
	if(standardImage == listBulletImage)
		return("BaseballIcon_32x32.gif");

	throw ASIException("ASBaseballHtmlPageOptions::getStandardImageName: unknown standardImage");
}

/******************************************************************************/

CStrVar ASBaseballHtmlPageOptions::getStandardImageRootPath(
	const int standardImage) const
{
	return(getImageRootPath().c_str());
}

/******************************************************************************/

void ASBaseballHtmlPageOptions::loadHeaderViewNavButtonBarArray(
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

THtmlViewPtr ASBaseballHtmlPageOptions::getFooterViewIconsHtmlView(
	const bool showCompanyOnly)
{
	return(ASBaseballFooterViewIcons::newInstance(*this,showCompanyOnly));
}

/******************************************************************************/
/******************************************************************************/

void ASBaseballFooterViewIcons::writeSponsorIcon(THTMLWriter& htmlWriter)
{
	htmlWriter.LinkStart("http://www.mplayer.com","mplayer.com");
	htmlWriter.Image(fPageOptions.buildSiteImagePath("Mplayer_115x115.gif").c_str(),
		"mplayer.com","",aiDefault,THtmlWidthValue(60),THtmlHeightValue(60));
	htmlWriter.LinkEnd();
}

/******************************************************************************/

void ASBaseballFooterViewIcons::writeSponsorText(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString("Access ");
	htmlWriter.TextString(fPageOptions.getAppNameAbbr().c_str());
	htmlWriter.LineBreak();
	htmlWriter.TextString(" through mplayer.com.");
}

/******************************************************************************/

void ASBaseballFooterViewIcons::writePlayerAssocIcon(THTMLWriter& htmlWriter)
{
	htmlWriter.LinkStart("http://www.bigleaguers.com","MLB Players Assoc.");
	htmlWriter.Image(fPageOptions.buildImagePath("MLBPlayersAssoc.gif").c_str(),
		"MLB Players Assoc.","",aiDefault,THtmlWidthValue(65),THtmlHeightValue(60));
	htmlWriter.LinkEnd();
}

/******************************************************************************/

void ASBaseballFooterViewIcons::writePlayerAssocText(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString(fPageOptions.getAppNameAbbr().c_str());
	htmlWriter.TextString(" is an officially licensed");
	htmlWriter.LineBreak();
	htmlWriter.TextString("product of the MLBPA.");
	htmlWriter.LineBreak();
	htmlWriter.TextString("MLBPA logo is a registered");
	htmlWriter.LineBreak();
	htmlWriter.TextString("trademark of the MLBPA.");
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
