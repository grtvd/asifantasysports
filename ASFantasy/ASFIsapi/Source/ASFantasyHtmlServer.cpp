/* ASFantasyHtmlServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommType.h"
#include "CommDB.h"
#include "PasswordEncode.h"

#include "ASMemberDB.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyType.h"

#include "ASFantasyHtmlServer.h"

#include "ASFantasySignupIntroPage.h"
#include "ASFantasySignupWhichPage.h"
#include "ASFantasyNewMemberSignupPage.h"
#include "ASFantasyNewParticSignupPage.h"
#if 0	//BOB
#include "ParticUpgradePage.h"
#include "ParticPremiumTrialPage.h"
#endif

#include "ASFantasyPickParticPage.h"
#include "ASFantasyHubPage.h"
#include "ASFantasyCustomPage.h"
#include "ASFantasyLeagueSignupPage.h"
#include "ASFantasyTeamsPage.h"

#include "ASFantasyDraftRankingsPage.h"
#include "ASFantasyDraftResultsPage.h"

#include "ASFantasySchedulePage.h"
#include "ASFantasyLineupPage.h"
#include "ASFantasyGameResultsPage.h"
#include "ASFantasyStandingsPage.h"
#include "ASFantasyFreeAgentPage.h"
#include "ASFantasyTradePage.h"
#include "ASFantasyPlayoffPage.h"

using namespace asmember;

namespace asfantasy
{

/******************************************************************************/

const char* gInvalidPageMsg = "Oops! The page you are requesting is no "
	"longer valid.";

/******************************************************************************/
/******************************************************************************/

ASFantasyHtmlServer::~ASFantasyHtmlServer()
{
//BOB	CloseDatabase(fDatabase);
}

/******************************************************************************/

void ASFantasyHtmlServer::buildPage(const char* pageName)
{
	THtmlPageOptions& pageOptions = getPageOptions();
	THTMLWriter htmlWriter(fContent.get());
	TMemberID memberID;
	ASFantasyBasePageHtmlViewPtr pageHtmlViewPtr;
	int htmlPageID;

	if(InSystemMaintMode())
	{
		CStrVar msg;

		msg.copy("Sorry, ");
		msg.concat(pageOptions.getAppNameAbbr());
		msg.concat(" is currently in system maintenance mode and, as a "
			"result, your request cannot be fulfilled.\r\n\r\nThe system "
			"should be back up again shortly.\r\n\r\nThank you.");
			
		pageHtmlViewPtr = createMessagePage(pageOptions,htmlWriter,false,msg);
		pageHtmlViewPtr->process();
		return;
	}
	
	OpenDatabase(MemberDatabaseName());
	OpenDatabase(MemberMiscDatabaseName());
	OpenDatabase(PrimaryDatabaseName());
	
	try
	{
		setUpPageOptions();
		fContent->Position = 0;

		if(getQuery().len() == 0)
		{
			pageHtmlViewPtr = createMessagePage(pageOptions,htmlWriter,true,
				"Unknown Request.");
			pageHtmlViewPtr->process();
		}
		else
		{
			try
			{
				htmlPageID = pageOptions.getPageLinkInfoEnum(pageName);
			}
			catch(...)
			{
				CommErrMsg(cel_Warning,"ASFantasyHtmlServer::buildPage: "
					"Invalid Page(%s)",pageName);
				pageHtmlViewPtr = createMessagePage(pageOptions,htmlWriter,
					true,gInvalidPageMsg);
				pageHtmlViewPtr->process();
				return;
			}

			// If Partic is already set, make sure it is current
			if(pageOptions.isRqstParticSet())
				if(!determineRqstParticActive(htmlWriter))
					return;

			// If Hub page was selected without a User, determine who User should be.
			if((htmlPageID == htmlHubPage) && !pageOptions.isRqstParticSet())
				if(!determineRqstPartic(htmlWriter))
					return;

			determineGameView();
					
			{
				const THTMLPageLinkInfo& pageLinkInfo =
					pageOptions.getPageLinkInfo(htmlPageID);

				if(pageLinkInfo.IsMemberNeeded())
				{
					if(!pageOptions.isRqstMemberSet())
						throw ASIException("ASFantasyHtmlServer::buildPage: attempting to access a secured page");
				}
			
				if(pageLinkInfo.IsParticNeeded())
				{
					if(!pageOptions.isRqstParticSet())
						throw ASIException("ASFantasyHtmlServer::buildPage: user required to access page");

					if(!determineRqstParticActive(htmlWriter))
						return;
				}
			}
		
			pageHtmlViewPtr = createNewPage(htmlPageID,pageOptions,htmlWriter);
			pageHtmlViewPtr->process();
		}

		return;
	}
	catch(MemberParticMismatchException&)
	{
	}
	
	buildMemberParticMismatchPage(htmlWriter);
}

/******************************************************************************/

ASFantasyBasePageHtmlViewPtr ASFantasyHtmlServer::createMessagePage(
	THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter,const bool isError,
	const char* message)
{
	if(isError)
		return(ASFantasyBasePageHtmlViewPtr(new TErrorPageHtmlView(*this,
			pageOptions,htmlWriter,message)));

	return(ASFantasyBasePageHtmlViewPtr(new TMessagePageHtmlView(*this,
		pageOptions,htmlWriter,message)));
}

/******************************************************************************/

ASFantasyBasePageHtmlViewPtr ASFantasyHtmlServer::createNewPage(int htmlPage,
	THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter)
{
	if(htmlPage == htmlSignupIntroGetPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasySignupIntroGetPage(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlSignupWhichGetPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasySignupWhichGetPage(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlNewMemberSignupPremiumGetPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyNewMemberSignupPremiumGetPage(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlNewMemberSignupPostPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyNewMemberSignupPostPage(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlNewParticSignupPremiumGetPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyNewParticSignupPremiumGetPage(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlNewParticSignupPostPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyNewParticSignupPostPage(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlHubPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyHubPageHtmlView(*this,
			pageOptions,htmlWriter)));

	if(htmlPage == htmlCustomPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyCustomPageHtmlView(*this,
			pageOptions,htmlWriter)));

	if(htmlPage == htmlLeagueSignupPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyLeagueSignupPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlTeamsPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyTeamsPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlDraftRankingsPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyDraftRankingsPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlDraftResultsPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyDraftResultsPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlSchedulePage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasySchedulePageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlLineupPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyLineupPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlGameResultsPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyGameResultsPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlStandingsPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyStandingsPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlFreeAgentPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyFreeAgentPageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlTradePage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyTradePageHtmlView(
			*this,pageOptions,htmlWriter)));

	if(htmlPage == htmlPlayoffPage)
		return(ASFantasyBasePageHtmlViewPtr(new ASFantasyPlayoffPageHtmlView(
			*this,pageOptions,htmlWriter)));

	CommErrMsg(cel_Error,"ASFantasyHtmlServer::createNewPage: unknown page(%d)",
		htmlPage);
	return(createMessagePage(pageOptions,htmlWriter,true,gInvalidPageMsg));
}

/******************************************************************************/

void ASFantasyHtmlServer::setUpPageOptions()
{
	THtmlPageOptions& pageOptions = getPageOptions();
	TMemberID memberID;
	TParticID particID;
	TPassword password;
	TEncodedParticID user;
	CStrVar tempStr;

	tempStr = getStringField("Backdoor",cam_MayNotExist);
	if(tempStr.hasLen())
		pageOptions.setBackdoorAccess(TBooleanType(tempStr));
	
	memberID = getEnvVar(EnvVarRemoteUser).c_str();
	if(!memberID.isUndefined())
		pageOptions.setRqstMemberID(memberID);
	
	user = getStringField(gURLUserFieldStr,cam_MayNotExist).c_str();
	if(user.Len() > 0)
	{
		TPartic::decodeParticID(user, particID, password);
			
		pageOptions.setRqstPartic(particID,password);
	}
}

/******************************************************************************/

void ASFantasyHtmlServer::determineGameView()
{
	THtmlPageOptions& pageOptions = getPageOptions();
	
	// Determine Season or Draft View
	if(pageOptions.isRqstLeagueSet())
	{
		TLeaguePtr leaguePtr = pageOptions.getRqstLeague();
		TGamePhase gamePhase = leaguePtr->getGamePhase();

		if((gamePhase != gmph_Enrollment) && (gamePhase != gmph_PreDraft) &&
				(gamePhase != gmph_Draft))
			pageOptions.setSeasonView(true);
	}
}

/******************************************************************************/

/* Fetched all Partics for Member.  If one is found then, RqstPartic is set.
	If multiple are found, the PickParticPage is built.

	Returning false means page has already been built and caller should not
	build a page. */
	
bool ASFantasyHtmlServer::determineRqstPartic(THTMLWriter& htmlWriter)
{
	THtmlPageOptions& pageOptions = getPageOptions();
	ASFantasyBasePageHtmlViewPtr pageHtmlViewPtr;
	TMemberID memberID;
	TParticVector particVector;
	
	if(!pageOptions.isRqstMemberSet())
		throw ASIException("ASFantasyHtmlServer::determineRqstPartic: attempting to access a secured page");
	memberID = pageOptions.getRqstMemberID();

	LoadParticVectorByMemberIDGameID(memberID,CurrentGameID(),particVector);

	if(particVector.size() == 1)
	{
		TParticPtr particPtr = *particVector.begin();
		pageOptions.setRqstPartic(particPtr->getParticID(),particPtr->getPassword());
	}
	else
	{
		pageHtmlViewPtr = ASFantasyBasePageHtmlViewPtr(
			new ASFantasyPickParticPageHtmlView(*this,pageOptions,htmlWriter,
			particVector));
		pageHtmlViewPtr->process();

		return(false);
	}

	return(true);
}

/******************************************************************************/

bool ASFantasyHtmlServer::determineRqstParticActive(THTMLWriter& htmlWriter)
{
	THtmlPageOptions& pageOptions = getPageOptions();
	TParticPtr particPtr = pageOptions.getRqstPartic();
	ASFantasyBasePageHtmlViewPtr pageHtmlViewPtr;
	CStrVar msg;
	bool isError = false;

	if((particPtr->getStatus() == pts_Disabled) ||
		(particPtr->getStatus() == pts_GameOver) ||
		(particPtr->getGameID() != CurrentGameID()))
	{
		if(particPtr->getGameID() != CurrentGameID())
		{
			CommErrMsg(cel_Warning,"ASFantasyHtmlServer::determineRqstParticActive: "
				"Accessing old ParticID(%s)",particPtr->getParticID().c_str());
			msg.copyVarg(gInvalidPageMsg);
			isError = true;
		}
		else if(particPtr->getStatus() == pts_Disabled)
		{
			msg.copyVarg("ALERT! Your %s account has been disabled.",
				pageOptions.getAppNameAbbr().c_str());
			isError = true;
		}
		else
		{
			msg.copyVarg("The %s season is complete and access to your team "
				"is no longer available.\r\n\r\nThanks for playing.  See you "
				"next year.",pageOptions.getAppNameAbbr().c_str());
		}

		pageHtmlViewPtr = createMessagePage(pageOptions,htmlWriter,isError,msg);
		pageHtmlViewPtr->process();
		return(false);
	}

	return(true);
}

/******************************************************************************/

void ASFantasyHtmlServer::buildMemberParticMismatchPage(THTMLWriter& htmlWriter)
{
	THtmlPageOptions& pageOptions = getPageOptions();
	ASFantasyBasePageHtmlViewPtr pageHtmlViewPtr;
	TMemberID loggedInMemberID;
	TMemberID particMemberID;
	TEncodedParticID user;
	TParticPtr particPtr;
	CStrVar msg;

	loggedInMemberID = getEnvVar(EnvVarRemoteUser).c_str();
	if(loggedInMemberID.isUndefined())
		throw ASIException("ASFantasyHtmlServer::buildMemberParticMismatchPage: loggedInMemberID.isUndefined()");
	loggedInMemberID.ToUpper();

	user = getStringField(gURLUserFieldStr,cam_MayNotExist).c_str();
	if(user.Len() > 0)
		particPtr = TPartic::createGetByEncoded(user,cam_MustExist);
	else
		throw ASIException("ASFantasyHtmlServer::buildMemberParticMismatchPage: user.Len() == 0");
	particMemberID = particPtr->getMemberID();
	particMemberID.ToUpper();
	
	msg.copy("Error: You are attempting to access information for User \"");
	msg.concat(particMemberID.c_str());
	msg.concat("\" but you are logged in as User \"");
	msg.concat(loggedInMemberID.c_str());
	msg.concat("\".\r\n\r\n");
	msg.concat("You must restart your browser and re-login as User \"");
	msg.concat(particMemberID.c_str());
	msg.concat("\".");
	
	pageHtmlViewPtr = createMessagePage(pageOptions,htmlWriter,true,msg);
	pageHtmlViewPtr->process();
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
