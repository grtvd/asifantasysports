/* ASFantasyHubPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyHubPage.h"

namespace asfantasy
{

/******************************************************************************/

static const char* gGlobalMessageFileName = "GlobalMessage.txt";
static const char* gPrizeWinnersFileName = "PrizeWinners.txt";
static const char* gOverallLeadersFileName = "OverallLeaders.txt";

/******************************************************************************/
/******************************************************************************/

bool ASFantasyGlobalMessageHtmlView::show()
{
	return(FileExists(BuildFullFileName(AppHomeDir(),gGlobalMessageFileName).c_str()));
}

/******************************************************************************/

void ASFantasyGlobalMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.InsertFile(BuildFullFileName(AppHomeDir(),gGlobalMessageFileName));
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyBadEmailMessageHtmlView::show()
{
	return(fMemberPtr->isEmailInvalid());
}

/******************************************************************************/

void ASFantasyBadEmailMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.Font("ATTENTION: ",0,fcAbsolute,ASFantasyStandardFont(),clRed);
	htmlWriter.TextString("Emails sent to your ");
	htmlWriter.Font(fMemberPtr->getEmail(),0,fcAbsolute,ASFantasyStandardFont(),clBlue);
	htmlWriter.TextString(" account have been returned. Please contact ");
	htmlWriter.WriteView(TMailToTheRefHtmlView(fPageOptions));
	htmlWriter.TextString(" with a valid email account.");
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyHubParticStatusHtmlView::write(THTMLWriter& htmlWriter)
{
	if((fStatus == pts_NeedCCInfo) || (fStatus == pts_WaitingApproval))
	{
		if(fStatus == pts_NeedCCInfo)
		{
	
			htmlWriter.TextString("Your credit card information is not on "
				"file. You must send your credit card information via fax at ");
			
			htmlWriter.TextString(TechSupportFaxNumber());

			htmlWriter.TextString(" or call ");
			htmlWriter.TextString(fViewOptions.getAppNameAbbr());
			htmlWriter.TextString(" at ");
			
			htmlWriter.TextString(TechSupportPhoneNumber());
			htmlWriter.TextString(". ");
		}
		else
		{
			htmlWriter.TextString("Your payment has not yet been approved. ");
		}

		htmlWriter.TextString("You will not be able to join a league until "
			"your payment has been processed. In the meantime, you can "
			"begin scouting players on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" page.");
	}
	else if(fStatus == pts_PaymentDenied)
	{
		htmlWriter.TextString("ALERT! Your payment has been denied. Please "
			"contact ");
		htmlWriter.TextString(fViewOptions.getAppNameAbbr());
		htmlWriter.TextString(" Tech Support immediately by phone at ");
		htmlWriter.TextString(TechSupportPhoneNumber());
		htmlWriter.TextString(" so this issue can be resolved.");
	}
	//BOB else if(fStatus == pts_PaymentApproved)
	else if(fStatus == pts_Disabled)
	{
		htmlWriter.TextString("ALERT! Your ");
		htmlWriter.TextString(fViewOptions.getAppNameAbbr());
		htmlWriter.TextString(" account has been disabled. Please contact ");
		htmlWriter.WriteView(TMailToTheRefHtmlView(fPageOptions));
		htmlWriter.TextString(" for more information.");
	}
	else if(fStatus == pts_GameOver)
	{
		htmlWriter.Paragraph("The ");
		htmlWriter.TextString(fViewOptions.getAppNameAbbr());
		htmlWriter.Paragraph(" season is complete and access to your team "
			"is no longer available.",ahLeft);
		
		htmlWriter.Paragraph("Thanks for playing. See you next year.",ahLeft);
	}
	else
		throw ASIException("THubParticStatusHtmlView::Write: unknown fStatus");
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyHubSignupMessageHtmlView::show()
{
	TDateTime today = TDateTime::CurrentDate();

	if((today >= SignupStartDate()) && (today <= SignupEndDate()))
		return(true);

	return(false);
}

/******************************************************************************/

void ASFantasyHubSignupMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.WriteView(TSignupTextNavHtmlView(fPage));
//	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlSignupIntroGetPage);
	htmlWriter.TextString(" now for another ");
	htmlWriter.TextString(fViewOptions.getAppNameAbbr());
	htmlWriter.TextString(" team.");
}

/******************************************************************************/
/******************************************************************************/

#define PremiumTrialDays()		(7)		//BOB move to AppOptions

bool ASFantasyHubUpgradeMessageHtmlView::show()
{
	TParticPtr particPtr = fPageOptions.getRqstPartic();

	if(particPtr->getStatus() == pts_Active)
	{
		if(particPtr->getUpgradeStatus() == pus_Undefined)
		{
			if(particPtr->getGameLevel() == gml_Standard)
			{
				if(particPtr->getTrialDateTime() == TDateTime())
				{
					if(fPageOptions.isSeasonView() && PremiumTrialAvailable())
					{
						fUpgradeMessageType = humt_PremiumTrialAvailable;
						return(true);
					}
					
					if(UpgradeAvailable())
					{
						fUpgradeMessageType = humt_UpgradeAvailable;
						return(true);
					}
				}
				else
				{
					TDateTime expireDateTime = NextProcessingDateTime(
						particPtr->getTrialDateTime(),PremiumTrialDays());

					// Has the trial expired over 7 days ago?
					if(TDateTime::CurrentDateTime() > expireDateTime + 7)
					{
						if(UpgradeAvailable())
						{
							fUpgradeMessageType = humt_UpgradeAvailable;
							return(true);
						}
					}
					// Has the trial expired?
					else if(TDateTime::CurrentDateTime() > expireDateTime)
					{
						if(UpgradeAvailable())
						{
							fUpgradeMessageType = humt_PremiumTrialExpired;
							return(true);
						}
					}
					else
						throw ASIException("ASFantasyHubUpgradeMessageHtmlView::show: invalid TrialDateTime");
				}
			}
			else if(particPtr->getGameLevel() == gml_Premium)
			{
				if(particPtr->getTrialDateTime() == TDateTime())
				{
					// Don't show message
				}
				else
				{
					TDateTime expireDateTime = NextProcessingDateTime(
						particPtr->getTrialDateTime(),PremiumTrialDays());

					fDaysRemaining = expireDateTime - TDateTime::CurrentDateTime();

					if(fDaysRemaining < 1.0)
						fUpgradeMessageType = humt_PremiumTrialWillExpire;
					else
						fUpgradeMessageType = humt_PremiumTrialDaysLeft;

					return(true);
				}
			}
			else
				throw ASIException("ASFantasyHubUpgradeMessageHtmlView::show: unknow GameLevel");
		}
		else
		{
			fUpgradeMessageType = humt_UpgradeStatus;

			if(particPtr->getUpgradeStatus() == pus_PaymentApproved)
			{
				// Only show successful upgrade for 7 days.
				if(TDateTime::CurrentDate() < particPtr->getUpgradeDate() + 7)
					return(true);
			}
			else
				return(true);
		}
	}

	return(false);
}

/******************************************************************************/

void ASFantasyHubUpgradeMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& upgradePageLinkInfo(fPageOptions.getPageLinkInfo(htmlParticUpgradeGetPage));
	TParticPtr particPtr = fPageOptions.getRqstPartic();

	if(fUpgradeMessageType == humt_UpgradeAvailable)
	{
		htmlWriter.TextString("Get the competitive advantage. ");
		htmlWriter.Link(upgradePageLinkInfo.GetSecureAbsoluteLinkURLToEncodedParticID(0,
			fPageOptions,particPtr->encodeParticID()).c_str(), "",
			upgradePageLinkInfo.GetLinkDesc().c_str());
		htmlWriter.TextString(" this team to the premium version.");
	}
	else if(fUpgradeMessageType == humt_UpgradeStatus)
	{
		if(particPtr->getUpgradeStatus() == pus_NeedCCInfo)
		{
			htmlWriter.TextString("Your ");
			htmlWriter.TextEffect(efEmphasized,"Upgrade");
			htmlWriter.TextString(" payment cannot be approved until we receive "
				"your credit card information. You must send your credit card "
				"information via fax at ");
			
			htmlWriter.TextString(TechSupportFaxNumber());

			htmlWriter.TextString(" or call ");
			htmlWriter.TextString(fViewOptions.getAppNameAbbr());
			htmlWriter.TextString(" at ");
			
			htmlWriter.TextString(TechSupportPhoneNumber());
			htmlWriter.TextString(".  ");
		}
		else if(particPtr->getUpgradeStatus() == pus_WaitingApproval)
		{
			htmlWriter.TextString("Your ");
			htmlWriter.TextEffect(efEmphasized,"Upgrade");
			htmlWriter.TextString(" payment has not yet been approved. "
				"Please check back periodically.");
		}
		else if(particPtr->getUpgradeStatus() == pus_PaymentDenied)
		{
			htmlWriter.TextString("ALERT! Your ");
			htmlWriter.TextEffect(efEmphasized,"Upgrade");
			htmlWriter.TextString(" payment has been denied. Please contact ");
			htmlWriter.TextString(fViewOptions.getAppNameAbbr());
			htmlWriter.TextString("Tech Support immediately by phone at ");
			htmlWriter.TextString(TechSupportPhoneNumber());
			htmlWriter.TextString(" so this issue can be resolved.");
		}
		else if(particPtr->getUpgradeStatus() == pus_PaymentApproved)
		{
			htmlWriter.TextString("Congratulations! Your ");
			htmlWriter.TextEffect(efEmphasized,"Upgrade");
			htmlWriter.TextString(" payment has been approved and your team is "
				"now using the premium version.");
		}
		else
			throw ASIException("ASFantasyHubUpgradeMessageHtmlView::Write: invalid UpgradeStatus");
	}
	else if(fUpgradeMessageType == humt_PremiumTrialAvailable)
	{
		htmlWriter.TextString("Sign-up for a ");
		htmlWriter.Font("FREE 1 WEEK ",0,fcAbsolute,ASFantasyStandardFont(),clRed);
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlParticPremiumTrialGetPage);
		htmlWriter.TextString(" of the premium version. Or ");
		htmlWriter.Link(upgradePageLinkInfo.GetSecureAbsoluteLinkURLToEncodedParticID(0,
			fPageOptions,particPtr->encodeParticID()).c_str(), "",
			upgradePageLinkInfo.GetLinkDesc().c_str());
		htmlWriter.TextString(" this team to the premium version now.");
	}
	else if(fUpgradeMessageType == humt_PremiumTrialDaysLeft)
	{
		htmlWriter.TextString("You have ");
		if(floor(fDaysRemaining) == 1)
			htmlWriter.TextString("1 day");
		else
		{
			htmlWriter.TextNumeric(floor(fDaysRemaining));
			htmlWriter.TextString(" days");
		}
		htmlWriter.TextString(" left on your free trial of the premium version. ");
		htmlWriter.TextString("Keep the competitive advantage. ");

		htmlWriter.Link(upgradePageLinkInfo.GetSecureAbsoluteLinkURLToEncodedParticID(0,
			fPageOptions,particPtr->encodeParticID()).c_str(), "",
			upgradePageLinkInfo.GetLinkDesc().c_str());
		htmlWriter.TextString(" now to the premium version.");
	}
	else if(fUpgradeMessageType == humt_PremiumTrialWillExpire)
	{
		htmlWriter.TextEffect(efEmphasized,"WARNING: ");
		htmlWriter.TextString("Your free trial of the premium version is about to expire. ");

		htmlWriter.Link(upgradePageLinkInfo.GetSecureAbsoluteLinkURLToEncodedParticID(0,
			fPageOptions,particPtr->encodeParticID()).c_str(), "",
			upgradePageLinkInfo.GetLinkDesc().c_str());
		htmlWriter.TextString(" now!");
	}
	else if(fUpgradeMessageType == humt_PremiumTrialExpired)
	{
		htmlWriter.TextEffect(efEmphasized,"WARNING: ");
		htmlWriter.TextString("Your free trial of the premium version has expired. ");
		htmlWriter.Link(upgradePageLinkInfo.GetSecureAbsoluteLinkURLToEncodedParticID(0,
			fPageOptions,particPtr->encodeParticID()).c_str(), "",
			upgradePageLinkInfo.GetLinkDesc().c_str());
		htmlWriter.TextString(" now to resume a competitive advantage.");
	}
	else
		throw ASIException("ASFantasyHubUpgradeMessageHtmlView::Write: invalid UpgradeMessageType");
}

/******************************************************************************/
/******************************************************************************/

// Message about DraftDate, either not set, upcoming, or results available.

void ASFantasyHubDraftDateMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr;
	TDateTime draftDate;
	TDateTime draftDateTime;
	TDateTime tempDate;
	TDateTime curDateTime = TDateTime::CurrentDateTime();
	TDateTime curDate = GetDateOnly(curDateTime);
	TDateTime curTime = GetTimeOnly(curDateTime);
	int curDraftDay;

	if(fPageOptions.isRqstLeagueSet())
	{
		leaguePtr = fPageOptions.getRqstLeague();
		draftDate = leaguePtr->getDraftDate();
		draftDateTime = draftDate + NightlyProcessingTime();
	}
	
	// Has not joined league
	if(leaguePtr.isNull())
	{
		htmlWriter.TextString("Prepare your ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" for the Draft. When your ranking is ready, "
			"you should join a league on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLeagueSignupPage);
		htmlWriter.TextString(" page. ");

		// Before DropDead processing time
		tempDate = DropDeadDate() + NightlyProcessingTime();
		if(curDateTime < tempDate)
		{
			tempDate = RegularStartDate() + NightlyProcessingTime();
			if(curDateTime < tempDate)
			{
				htmlWriter.TextString("Your earliest possible first Draft "
					"day is ");
				htmlWriter.TextString(FormatDateTimeStr(tempDate,
					ASFantasyStandardDateTimeFormat()));
				htmlWriter.TextString(".");
			}
			else
			{
				htmlWriter.TextString("Join soon to receive a full season "
					"of ");
				htmlWriter.TextString(fViewOptions.getAppNameAbbr());
				htmlWriter.TextString(". Your first Draft day will take "
					"place as soon as your league fills.");
			}
		}
		else
		{
			htmlWriter.TextString("Join soon to receive the fullest possible "
				"season of ");
			htmlWriter.TextString(fViewOptions.getAppNameAbbr());
			htmlWriter.TextString(". Your first Draft day will take place as "
				"soon as your league fills.");
		}
	}
	// Draft Date not set
	else if(draftDate == TDateTime())
	{
		htmlWriter.TextString("Your first Draft day has not been set. ");

		// Reserved league
		if(leaguePtr->isReserved())
		{
			int numTeams = leaguePtr->getNumTeamsInLeague();
			TDateTime nextProcessingTime;

			if(curDate < RegularStartDate())
			{
				nextProcessingTime = RegularStartDate() + NightlyProcessingTime();
			}
			else if(curDate == RegularStartDate())
			{
				if(curTime < NightlyProcessingTime())
					nextProcessingTime = RegularStartDate() + NightlyProcessingTime();
				else
					nextProcessingTime = RegularStartDate() + NightlyProcessingTime() + 1.0;
			}
			else
			{
				if(curTime < NightlyProcessingTime())
					nextProcessingTime = curDate + NightlyProcessingTime();
				else
					nextProcessingTime = curDate + NightlyProcessingTime() + 1.0;
			}
			
			tempDate = leaguePtr->getEarliestDraftDate(false) + NightlyProcessingTime();

			htmlWriter.TextString("If the ");
			htmlWriter.TextString(leaguePtr->getName());
			htmlWriter.TextString(" League has ");
			
			if(numTeams < MinTeamsPerPrivateLeague())
				htmlWriter.TextString(CStrVar::build("at least %d teams by ",
					(int)MinTeamsPerPrivateLeague()));
			else
				htmlWriter.TextString("an even number of teams on ");

			htmlWriter.TextString(FormatDateTimeStr(nextProcessingTime,
				ASFantasyStandardDateTimeFormat()));
			htmlWriter.TextString(", then your first Draft day will take place ");
			
			if(tempDate == nextProcessingTime)
			{
				htmlWriter.TextString("at that time. ");
			}
			else
			{
				htmlWriter.TextString("on ");
				htmlWriter.TextString(FormatDateTimeStr(tempDate,
					ASFantasyStandardDateTimeFormat()));
				htmlWriter.TextString(". ");
			}
		}
		else
		{
			htmlWriter.TextString("Your first Draft day will be set once the ");
			htmlWriter.TextString(leaguePtr->getName());
			htmlWriter.TextString(" League fills. ");

			tempDate = leaguePtr->getEarliestDraftDate(false) + NightlyProcessingTime();
			
			htmlWriter.TextString("The ");
			htmlWriter.TextString(leaguePtr->getName());
			htmlWriter.TextString(" League's earliest possible first Draft "
				"day is ");
			
			htmlWriter.TextString(FormatDateTimeStr(tempDate,
				ASFantasyStandardDateTimeFormat()));
			htmlWriter.TextString(". ");
		}

		htmlWriter.TextString("In the meantime, you can continue to scout players on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" page. ");
	}
	// Draft upcoming
	else if(curDateTime < draftDateTime)
	{
		htmlWriter.TextString("YOUR FIRST DRAFT DAY HAS BEEN SET. The first "
			"Draft day for the ");
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League will take place on ");

		htmlWriter.TextString(FormatDateTimeStr(draftDateTime,
			ASFantasyStandardDateTimeFormat()));
			
		htmlWriter.TextString(". You can continue to scout players on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" page right up until Draft time.");
	}
	// Draft Results Available
	else if((curDateTime >= draftDateTime) &&
		(curDateTime < draftDateTime + NumDraftDays() - 1))
	{
		curDraftDay = (int)(curDateTime - draftDateTime + 1);

		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League Draft Day ");

		htmlWriter.TextString(CStr31().CopyVarg("%d",curDraftDay).c_str());
		
		htmlWriter.TextString(" results are now available. See the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftResultsPage);
		htmlWriter.TextString(" page for details. ");

		htmlWriter.TextString("You can still adjust your draft rankings on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);

		htmlWriter.TextString(" page for the ");
		if(curDraftDay == NumDraftDays() - 1)
		{
			htmlWriter.TextString(" remaining draft day.");
		}
		else
		{
			htmlWriter.TextString(CStr31().CopyVarg("%d",
				NumDraftDays() - curDraftDay).c_str());
			htmlWriter.TextString(" remaining draft days.");
		}
	}
	// Show message for Final Draft Results for 7 days after end of Draft
	else if((curDateTime >= draftDateTime + NumDraftDays() - 1) &&
		(curDateTime < draftDateTime + NumDraftDays() + 6))
	{
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League's Final Draft results can been seen on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftResultsPage);
		htmlWriter.TextString(" page.");
	}
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyScheduleMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	
	htmlWriter.TextString(leaguePtr->getName());
	htmlWriter.TextString(" League's season schedule has been set.  Check it out on the ");
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlSchedulePage);
	htmlWriter.TextString(" page.");
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyLineupMessageHtmlView::show()
{
	TScheduleDayGame scheduleDayGame;
	
	fScheduleDayPtr = fScheduleDayVector.getFirstNotStartedScheduleDay();

	if(!fScheduleDayPtr.isNull())
	{
		if(fScheduleDayPtr->getScheduleDayGameByTeamID(
			fPageOptions.getRqstTeam()->getTeamID(),scheduleDayGame))
		{
			return(true);
		}
	}

	return(false);
}

/******************************************************************************/

void ASFantasyLineupMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TDateTime lineupLockoutTime;

	// For most games, the lineup will never be considered locked.
	if(fLineupIsLocked)
	{
		htmlWriter.TextString("Your lineup for ");
		if(leaguePtr->getGamePhase() == gmph_Playoffs)
		{
			if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 1)
				htmlWriter.TextString("the Semi-Final Games ");
			else
				htmlWriter.TextString("the Final Game ");
		}
		else
		{
			htmlWriter.TextString("Game ");
			htmlWriter.TextString(fScheduleDayPtr->getProfGameWeek().c_str());
		}
		htmlWriter.TextString(" is now locked but it can still be viewed on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLineupPage);
		htmlWriter.TextString(" page.");
	}
	else
	{
		lineupLockoutTime = fScheduleDayPtr->getEarlyProfGameDate()
			+ fScheduleDayPtr->getEarlyProfGameTime();

		htmlWriter.TextString("Set your lineup for ");
		if(leaguePtr->getGamePhase() == gmph_Playoffs)
		{
			if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 1)
				htmlWriter.TextString("the Semi-Final Games ");
			else
				htmlWriter.TextString("the Final Game ");
		}
		else
		{
			htmlWriter.TextString("Game ");
			htmlWriter.TextString(fScheduleDayPtr->getProfGameWeek().c_str());
		}

		htmlWriter.TextString(" on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLineupPage);
		htmlWriter.TextString(" page. Your lineup can be changed until ");

		htmlWriter.TextString(FormatDateTimeStr(lineupLockoutTime,
			ASFantasyStandardDateTimeFormat()).c_str());
		htmlWriter.TextString(". ");

		if(leaguePtr->getGamePhase() == gmph_Playoffs)
		{
			if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 1)
				htmlWriter.TextString("The Semi-Final Games");
			else
				htmlWriter.TextString("The Final Game");
		}
		else
		{
			htmlWriter.TextString("Game ");
			htmlWriter.TextString(fScheduleDayPtr->getProfGameWeek().c_str());
		}
		htmlWriter.TextString(" will completed by ");

		htmlWriter.TextString(FormatDateTimeStr(
			fScheduleDayPtr->getLateProfGameDate() + 1.0 + NightlyProcessingTime(),
			ASFantasyStandardDateTimeFormat()).c_str());
		htmlWriter.TextString(".");
	}
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyInProgressGameResultMessageHtmlView::show()
{
	TScheduleDayGame scheduleDayGame;
	
	fScheduleDayPtr = fScheduleDayVector.getInProgressScheduleDay();

	if(!fScheduleDayPtr.isNull())
	{
		// During playoffs, alwasy show message
		if(fScheduleDayPtr->getProfGameWeek() > NumProfWeeks())
		{
			if(fScheduleDayPtr->scheduleDayGameVector().size() > 0)
				return(true);
		}
		else	// Only show message if team has game
		{
			if(fScheduleDayPtr->getScheduleDayGameByTeamID(
				fPageOptions.getRqstTeam()->getTeamID(),scheduleDayGame))
			{
				return(true);
			}
		}
	}

	return(false);
}

/******************************************************************************/

void ASFantasyInProgressGameResultMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	CStrVar parameters;
	CStr31 gameWeek;
	
	if(fScheduleDayPtr->getProfGameWeek() <= NumProfWeeks())
	{
		gameWeek.Copy("Game ");
		gameWeek.Concat(fScheduleDayPtr->getProfGameWeek().c_str());
	}
	else if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 1)
		gameWeek.Copy("The Semi-Final Games");
	else if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 2)
		gameWeek.Copy("The Final Game");
	else
		throw ASIException("ASFantasyInProgressGameResultMessageHtmlView::"
			"write: unknown fScheduleDayPtr->getProfGameWeek(%d)",
			(int)fScheduleDayPtr->getProfGameWeek().c_str());

	htmlWriter.TextString(gameWeek);
	htmlWriter.Font(" In-Progress",0,fcAbsolute,ASFantasyStandardFont(),clRed);
	htmlWriter.TextString(" Results are now available on the ");

	parameters.copyVarg("GameDate=%s",
		FormatDateOnlyStr(fScheduleDayPtr->getGameDate()).c_str());
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlGameResultsPage,parameters);
	htmlWriter.TextString(" page. ");

	htmlWriter.TextString(gameWeek);
	htmlWriter.TextString(" will completed by ");

	htmlWriter.TextString(FormatDateTimeStr(
		fScheduleDayPtr->getLateProfGameDate() + 1.0 + NightlyProcessingTime(),
		ASFantasyStandardDateTimeFormat()).c_str());
	htmlWriter.TextString(".");
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyCompletedGameResultMessageHtmlView::show()
{
	TScheduleDayGame scheduleDayGame;
	bool show = false;

	fScheduleDayPtr = fScheduleDayVector.getLastCompletedScheduleDay();

	if(!fScheduleDayPtr.isNull())
	{
		// During playoffs, alwasy show message
		if(fScheduleDayPtr->getProfGameWeek() > NumProfWeeks())
		{
			if(fScheduleDayPtr->scheduleDayGameVector().size() > 0)
				show = true;
		}
		else	// Only show message if team has game
		{
			if(fScheduleDayPtr->getScheduleDayGameByTeamID(
				fPageOptions.getRqstTeam()->getTeamID(),scheduleDayGame))
			{
				show = true;
			}
		}

		if(show)
		{
			// Show for three days
			if((TDateTime::CurrentDate() >= fScheduleDayPtr->getGameDate()) &&
					(TDateTime::CurrentDate() <= fScheduleDayPtr->getGameDate() + 2))
				return(true);
		}
	}

	return(false);
}

/******************************************************************************/

void ASFantasyCompletedGameResultMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	CStrVar parameters;
	CStr31 gameWeek;

	if(fScheduleDayPtr->getProfGameWeek() <= NumProfWeeks())
	{
		gameWeek.Copy("Game ");
		gameWeek.Concat(fScheduleDayPtr->getProfGameWeek().c_str());
	}
	else if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 1)
		gameWeek.Copy("The Semi-Final Games");
	else if(fScheduleDayPtr->getProfGameWeek() == NumProfWeeks() + 2)
		gameWeek.Copy("The Final Game");
	else
		throw ASIException("ASFantasyCompletedGameResultMessageHtmlView::"
			"write: unknown fScheduleDayPtr->getProfGameWeek(%d)",
			(int)fScheduleDayPtr->getProfGameWeek().c_str());

	htmlWriter.TextString(gameWeek);
	htmlWriter.TextEffect(efEmphasized," Final");
	htmlWriter.TextString(" Results are now available on the ");

	parameters.copyVarg("GameDate=%s",
		FormatDateOnlyStr(fScheduleDayPtr->getGameDate()).c_str());
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlGameResultsPage,parameters);
	htmlWriter.TextString(" page.");
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyFreeAgentGeneralMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString("Players can be claimed off Waivers on the ");
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlFreeAgentPage);
	htmlWriter.TextString(" page.");

	htmlWriter.TextString("  You may have ");
	htmlWriter.Font("only one",0,fcAbsolute,ASFantasyStandardFont(),clRed);
	htmlWriter.TextString(" free agent claim pending at a time.  Submitting a "
		"second claim overwrites any previous pending claim.");
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyFreeAgentPendingMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TProfPlayerPtr claimProfPlayerPtr = TProfPlayer::createGet(
		fFreeAgentClaimPtr->getClaimPlayerID(),cam_MustExist);
	TProfPlayerPtr releaseProfPlayerPtr = TProfPlayer::createGet(
		fFreeAgentClaimPtr->getReleasePlayerID(),cam_MustExist);

	htmlWriter.TextString("Your free agent claim for ");
	htmlWriter.TextString(claimProfPlayerPtr->getName().buildFullName().c_str());
	htmlWriter.TextString(" has ");

	if(fFreeAgentClaimPtr->getProcessedStatus() == fcps_NotProcessed)
	{
		htmlWriter.Font("not yet been processed",0,fcAbsolute,ASFantasyStandardFont(),clRed);
	htmlWriter.TextString(". ");
	}
	else
	{
		htmlWriter.TextString("been ");
		htmlWriter.Font("held up",0,fcAbsolute,ASFantasyStandardFont(),clRed);
		htmlWriter.TextString(" because ");

		if(fFreeAgentClaimPtr->getProcessedStatus() == fcps_NewFreeAgent)
		{
			htmlWriter.TextString(claimProfPlayerPtr->getName().buildFullName().c_str());
			htmlWriter.TextString(" is a new free agent. ");
		}
		else if(fFreeAgentClaimPtr->getProcessedStatus() == fcps_InTrade)
		{
			htmlWriter.TextString("the player your are releasing, ");
			htmlWriter.TextString(releaseProfPlayerPtr->getName().buildFullName().c_str());
			htmlWriter.TextString(", is involved in a trade. ");
		}
		else if(fFreeAgentClaimPtr->getProcessedStatus() == fcps_Locked)
		{
			htmlWriter.TextString("the player your are releasing, ");
			htmlWriter.TextString(releaseProfPlayerPtr->getName().buildFullName().c_str());
			htmlWriter.TextString(", is involved in an ");
			htmlWriter.TextEffect(efEmphasized,"in-progress");
			htmlWriter.TextString(" game. ");
		}
	}

	htmlWriter.TextString("Access your claim on the ");
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlFreeAgentPage);
	htmlWriter.TextString(" page.");
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyFreeAgentFinalMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TProfPlayerPtr profPlayerPtr = TProfPlayer::createGet(
		fFreeAgentClaimPtr->getClaimPlayerID(),cam_MustExist);

	htmlWriter.TextString("Your free agent claim for ");
	htmlWriter.TextString(profPlayerPtr->getName().buildFullName().c_str());
	htmlWriter.TextString(" has been ");

	if(fFreeAgentClaimPtr->getStatus() == facs_Completed)
	{
		htmlWriter.Font("completed",0,fcAbsolute,ASFantasyStandardFont(),clRed);
		htmlWriter.TextString(".");
	}
	else if(fFreeAgentClaimPtr->getStatus() == facs_Invalidated)
	{
		htmlWriter.Font("invalidated",0,fcAbsolute,ASFantasyStandardFont(),clRed);
		htmlWriter.TextString(" through another free agent claim or trade.");
	}
	else
		throw ASIException("ASFantasyFreeAgentFinalMessageHtmlView::write: invalid status");
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyTradeGeneralMessageHtmlView::show()
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();

	if((TDateTime::CurrentDate() >= TradingStartDate()) &&
			(TDateTime::CurrentDate() <= TradingEndDate()) &&
			(leaguePtr->getGamePhase() == gmph_Season))
		return(true);

	return(false);
}

/******************************************************************************/

void ASFantasyTradeGeneralMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	CStrVar str;

	if(TDateTime::CurrentDate() >= TradingEndDate() - 14)
	{
		htmlWriter.TextEffect(efEmphasized,"ATTENTION: ");
		htmlWriter.TextString("The Trading deadline nears. ");
		htmlWriter.LineBreak();

		str.copyVarg("Trades must be proposed by %s on the ",FormatDateTimeStr(
			TradingEndDate(),ASFantasyStandardDateFormat()).c_str());
		htmlWriter.TextString(str);
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlTradePage);
		htmlWriter.TextString(" page.");
	}
	else
	{
		htmlWriter.TextString("Let's make a deal. Propose a trade to a fellow ");
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League Owner on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlTradePage);
		htmlWriter.TextString(" page.");
	}
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyTradeBaseMessageHtmlView::writeLinkToTrade(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlTradePage));
	CStr255 url = pageLinkInfo.GetLinkURL(fPageOptions).c_str();

	url.ConcatVarg("&TradeID=%s",fTradePtr->getTradeID().c_str());

	htmlWriter.Link(url.c_str(),"","Click Here");
	htmlWriter.TextString(" to view this trade.");
}

/******************************************************************************/

void ASFantasyTradeBaseMessageHtmlView::writeTrailer(THTMLWriter& htmlWriter)
{
	htmlWriter.TextString(" has ");

	switch(fTradePtr->getStatus())
	{
		case trs_Proposed:
			htmlWriter.TextEffect(efEmphasized,"not yet been accepted or declined");
			htmlWriter.TextString(". ");

			htmlWriter.TextString("The trade must be accepted by ");

			htmlWriter.TextString(FormatDateTimeStr(NextProcessingDateTime(
				fTradePtr->getProposedDate(),MaxTradeProposeDays),
				ASFantasyStandardDateTimeFormat()).c_str());

			htmlWriter.TextString(" or it will expire. ");

			writeLinkToTrade(htmlWriter);
			break;
		case trs_Cleared:
			htmlWriter.TextString("been ");
			htmlWriter.Font("withdrawn",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(".");
			break;
		case trs_Declined:
			htmlWriter.TextString("been ");
			htmlWriter.Font("declined",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(".");
			break;
		case trs_Accepted:
			htmlWriter.TextString("been ");
			htmlWriter.Font("accepted",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(". ");

			htmlWriter.TextString("Other league Owners have until ");

			htmlWriter.TextString(FormatDateTimeStr(NextProcessingDateTime(
				fTradePtr->getAcceptedDate(),MaxTradeProtestDays),
				ASFantasyStandardDateTimeFormat()).c_str());

			htmlWriter.TextString(" to protest the trade. ");

			writeLinkToTrade(htmlWriter);
			break;
		case trs_Expired:
			htmlWriter.Font("expired",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(".");
			break;
		case trs_Protested:
			htmlWriter.TextString("been ");
			htmlWriter.Font("protested",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(" by the league Owners.");
			break;
		case trs_Invalidated:
			htmlWriter.TextString("been ");
			htmlWriter.Font("invalidated",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(" by another roster move.");
			break;
		case trs_Completed:
			htmlWriter.TextString("been ");
			htmlWriter.Font("completed",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			htmlWriter.TextString(".");
			break;
		default:
			TOOLDEBUG( tErrorMsg("ASFantasyTradeBaseMessageHtmlView::writeTrailer: bad status"); );
			break;
	}
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyTradeInitiatedMessageHtmlView::show()
{
	return(fTradePtr->getStatus() != trs_Cleared);
}

/******************************************************************************/

void ASFantasyTradeInitiatedMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TTeamPtr proposedToTeamPtr = TTeam::createGet(fTradePtr->getProposeToTeamID(),
		cam_MustExist);

	htmlWriter.TextString("Your trade proposed on ");
	htmlWriter.TextString(FormatDateTimeStr(fTradePtr->getProposedDate(),
		ASFantasyStandardDateTimeFormat()).c_str());

	htmlWriter.TextString(" to the ");
	htmlWriter.TextEffect(efEmphasized,proposedToTeamPtr->getFullTeamName().c_str());
	writeTrailer(htmlWriter);
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyTradeReceivedMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TTeamPtr teamPtr = TTeam::createGet(fTradePtr->getTeamID(),cam_MustExist);

	if(fTradePtr->getStatus() == trs_Proposed)
	{
		htmlWriter.TextEffect(efEmphasized,"ATTENTION: ");
		htmlWriter.TextString("A trade offer has been received from the ");
		htmlWriter.TextEffect(efEmphasized,teamPtr->getFullTeamName().c_str());
		htmlWriter.TextString(". It");
	}
	else
	{
		htmlWriter.TextString("The trade offer received from the ");
		htmlWriter.TextEffect(efEmphasized,teamPtr->getFullTeamName().c_str());
		htmlWriter.TextString(", that was proposed on ");
		htmlWriter.TextString(FormatDateTimeStr(fTradePtr->getProposedDate(),
			ASFantasyStandardDateTimeFormat()).c_str());
		htmlWriter.TextString(",");
	}
	writeTrailer(htmlWriter);
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyTradeProtestMessageHtmlView::show()
{
	return((fTradePtr->getStatus() == trs_Accepted) ||
		(fTradePtr->getStatus() == trs_Protested) ||
		(fTradePtr->getStatus() == trs_Invalidated) ||
		(fTradePtr->getStatus() == trs_Completed));
}

/******************************************************************************/

void ASFantasyTradeProtestMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TTeamPtr teamPtr = TTeam::createGet(fTradePtr->getTeamID(),cam_MustExist);
	TTeamPtr proposedToTeamPtr = TTeam::createGet(fTradePtr->getProposeToTeamID(),
		cam_MustExist);
	TDateTime protestEnd;

	if(fTradePtr->getStatus() == trs_Accepted)
	{
		htmlWriter.TextString("The ");
		htmlWriter.TextEffect(efEmphasized,proposedToTeamPtr->getFullTeamName().c_str());
		htmlWriter.TextString(" have accepted a trade from the ");
		htmlWriter.TextEffect(efEmphasized,teamPtr->getFullTeamName().c_str());
			htmlWriter.TextString(". ");

		protestEnd = NextProcessingDateTime(fTradePtr->getAcceptedDate(),
			MaxTradeProtestDays);

		// If protest period has past, then trade must have been held up
		//	by a locked player.
		if(TDateTime::CurrentDateTime() > protestEnd)
		{
			htmlWriter.TextString("This trade has past the protest period and will "
				"be completed at the end of the lockout period. ");
		}
		else
		{
			// Have you already protested this trade?
			if(fTradePtr->protestTeamIDVector().contains(
				fPageOptions.getRqstTeam()->getTeamID()))
			{
				htmlWriter.TextString("You have already protested this trade. ");
			}
			else
			{
				htmlWriter.TextString("You have until ");

				htmlWriter.TextString(FormatDateTimeStr(protestEnd,
					ASFantasyStandardDateTimeFormat()).c_str());

				htmlWriter.TextString(" to protest this trade. ");
			}
			writeLinkToTrade(htmlWriter);
		}
	}
	else
	{
		htmlWriter.TextString("The trade proposed by the ");
		htmlWriter.TextEffect(efEmphasized,teamPtr->getFullTeamName().c_str());
		htmlWriter.TextString(" to the ");
		htmlWriter.TextEffect(efEmphasized,proposedToTeamPtr->getFullTeamName().c_str());
		writeTrailer(htmlWriter);
	}
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyPrizeWinnersMessageHtmlView::show()
{
	return(FileExists(BuildFullFileName(AppHomeDir(),gPrizeWinnersFileName).c_str()));
}

/******************************************************************************/

void ASFantasyPrizeWinnersMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlCustomPage));
	CStr255 url = pageLinkInfo.GetLinkURL(fPageOptions).c_str();

	url.ConcatVarg("&CustomPageTitle=Prize+Winners&CustomBodyViewWidth=650&"
		"CustomFileName=%s",gPrizeWinnersFileName);

	htmlWriter.TextString("Congratulations to this year's ");
	htmlWriter.TextString(fViewOptions.getAppNameAbbr());
	htmlWriter.TextString(" ");
	htmlWriter.Link(url.c_str(),"","Prize Winners");
	htmlWriter.TextString(".");
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyOverallLeadersMessageHtmlView::show()
{
	return(FileExists(BuildFullFileName(AppHomeDir(),gOverallLeadersFileName).c_str()));
}

/******************************************************************************/

void ASFantasyOverallLeadersMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlCustomPage));
	CStr255 url = pageLinkInfo.GetLinkURL(fPageOptions).c_str();

	url.ConcatVarg("&CustomPageTitle=Overall+Leaders&CustomBodyViewWidth=650&"
		"CustomFileName=%s",gOverallLeadersFileName);

	htmlWriter.TextString("Total points leaders can be viewed on the ");
	htmlWriter.Link(url.c_str(),"","Overall Leaders");
	htmlWriter.TextString(" page.");
}

/******************************************************************************/
/******************************************************************************/

bool ASFantasyPlayoffMessageHtmlView::show()
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();

	return((leaguePtr->getGamePhase() == gmph_Playoffs) ||
		(leaguePtr->getGamePhase() == gmph_PostSeason));
}

/******************************************************************************/

void ASFantasyPlayoffMessageHtmlView::write(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TTeamPtr teamPtr;

	if(leaguePtr->getGamePhase() == gmph_Playoffs)
	{
		htmlWriter.TextString("Its ");

		htmlWriter.TextEffectStart(efEmphasized);
		htmlWriter.Font("PLAYOFF",0,fcAbsolute,ASFantasyStandardFont(),clRed);
		htmlWriter.TextEffectEnd(efEmphasized);

		htmlWriter.TextString(" time!  See who goes on and see who goes home on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlPlayoffPage);
		htmlWriter.TextString(" page.  Who will be crowned League Champ!");
	}
	else
	{
		teamPtr = TTeam::createGet(leaguePtr->getLeagueChampTeamID(),cam_MustExist);

		htmlWriter.TextString("Congratulations to the ");

		htmlWriter.TextEffectStart(efEmphasized);
		htmlWriter.Font(teamPtr->getFullTeamName().c_str(),0,fcAbsolute,
			ASFantasyStandardFont(),clRed);
		htmlWriter.TextEffectEnd(efEmphasized);

		htmlWriter.TextString(" for becoming League Champ of the ");
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League.  ");

		htmlWriter.TextString("See the playoff breakdown on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlPlayoffPage);

		htmlWriter.TextString(" Page. Thanks to all who played.  See you next year.");
	}
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyHubPageHtmlView::writeItemRow(
	ASFantasyHubLineItemHtmlView& lineItemHtmlView)
{
	if(lineItemHtmlView.show())
	{
		fHtmlWriter.TableRowStart();

		fHtmlWriter.TableCellStart(0,0,THtmlWidth() /*BOB Value(30)*/,THtmlHeight(),ahLeft,avTop);
		fHtmlWriter.Image(fPageOptions.buildImagePath(
			fPageOptions.getStandardImageName(listBulletImage)).c_str());
		fHtmlWriter.TableCellEnd();
	
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(/*BOB ntPercent,100*/),THtmlHeight(),ahLeft,avTop);
		fHtmlWriter.TextEffectStart(efStrong);
		fHtmlWriter.FontStart(2,fcAbsolute,ASFantasyStandardFont());
		lineItemHtmlView.write(fHtmlWriter);
		fHtmlWriter.FontEnd();
		fHtmlWriter.TextEffectEnd(efStrong);
		fHtmlWriter.TableCellEnd();
	
		fHtmlWriter.TableRowEnd();

		// Blank line	
		fHtmlWriter.TableRowStart();
		TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,THtmlWidth(),
			THtmlHeightValue(10));
		TEmptyTableCellHTMLView::Build(fHtmlWriter,fPageOptions,THtmlWidth(),
			THtmlHeightValue(10));
		fHtmlWriter.TableRowEnd();
	}
}

/******************************************************************************/

bool ASFantasyHubPageHtmlView::buildParticStatusMessages()
{
	TParticStatus status = fPageOptions.getRqstPartic()->getStatus();
	bool showMoreItems = false;
	
	if((status == pts_NeedCCInfo) ||
		(status == pts_WaitingApproval))
	{
		writeItemRow(ASFantasyHubParticStatusHtmlView(fPageOptions,status));
	}
	else if((status == pts_PaymentApproved) ||
		(status == pts_Active))
	{
		showMoreItems = true;
	}
	else if((status == pts_PaymentDenied) ||
		(status == pts_Disabled) ||
		(status == pts_GameOver))
	{
		writeItemRow(ASFantasyHubParticStatusHtmlView(fPageOptions,status));
	}
	else
		throw ASIException("ASFantasyHubPageHtmlView::buildParticStatusMessages: unknown status");
	
	return(showMoreItems);
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildDraftMessages()
{
	TParticStatus status = fPageOptions.getRqstPartic()->getStatus();

	writeItemRow(ASFantasyGlobalMessageHtmlView(fPageOptions));

	writeItemRow(ASFantasyBadEmailMessageHtmlView(fPageOptions,fMemberPtr));

	// Show Draft Rankings, League Sign-up	
	writeItemRow(ASFantasyHubDraftDateMessageHtmlView(fPageOptions));

	// Show upgrade team to premium
	writeItemRow(ASFantasyHubUpgradeMessageHtmlView(fPageOptions));

	// Show signup another team message
	writeItemRow(ASFantasyHubSignupMessageHtmlView(*this));
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildCompletedGameResultMessage(
	const TScheduleDayVector& scheduleDayVector)
{
	writeItemRow(ASFantasyCompletedGameResultMessageHtmlView(fPageOptions,
		scheduleDayVector));
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildInProgressGameResultMessage(
	const TScheduleDayVector& scheduleDayVector)
{
	writeItemRow(ASFantasyInProgressGameResultMessageHtmlView(fPageOptions,
		scheduleDayVector));
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildLineupMessage(
	const TScheduleDayVector& scheduleDayVector)
{
	writeItemRow(ASFantasyLineupMessageHtmlView(fPageOptions,scheduleDayVector));
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildSeasonMessages()
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TDateTime draftDateTime = leaguePtr->getDraftDate() + NightlyProcessingTime();
	TDateTime curDateTime = TDateTime::CurrentDateTime();
	TScheduleDayVector scheduleDayVector;

	LoadScheduleDayVectorByLeagueID(leaguePtr->getLeagueID(),scheduleDayVector);
	scheduleDayVector.sortByGameDate();

	writeItemRow(ASFantasyGlobalMessageHtmlView(fPageOptions));

	writeItemRow(ASFantasyBadEmailMessageHtmlView(fPageOptions,fMemberPtr));

	// Show Playoff message
	writeItemRow(ASFantasyPlayoffMessageHtmlView(fPageOptions));

	// Show Prize Winners message
	writeItemRow(ASFantasyPrizeWinnersMessageHtmlView(fPageOptions));

	// Show Overall Leaders message
	writeItemRow(ASFantasyOverallLeadersMessageHtmlView(fPageOptions));

	// Show message for "completed" Game Results
	buildCompletedGameResultMessage(scheduleDayVector);
	
	// Show important messages for Trading
	buildTradeMessages();

	// Show important messages for Free Agent Claims
	buildFreeAgentClaimMessages();

	// Show message for Schedule for 7 days after end of Draft
	if((curDateTime >= draftDateTime + NumDraftDays() - 1) &&
			(curDateTime < draftDateTime + NumDraftDays() + 6))
		writeItemRow(ASFantasyScheduleMessageHtmlView(fPageOptions));
		
	// Show message for "in progress" Game Results
	buildInProgressGameResultMessage(scheduleDayVector);
	
	// Show message for Lineup
	buildLineupMessage(scheduleDayVector);

	// Show message for Free Agents
	if(!fAnyPendingFreeAgentClaim &&
			((leaguePtr->getGamePhase() == gmph_PreSeason) ||
			(leaguePtr->getGamePhase() == gmph_Season)))
		writeItemRow(ASFantasyFreeAgentGeneralMessageHtmlView(fPageOptions));

	// Show general message for Trading
	if(!fAnyInvolvedTradeMessages)
		writeItemRow(ASFantasyTradeGeneralMessageHtmlView(fPageOptions));
	
	// Show draft messages for 7 days after end of Draft
	if(curDateTime < draftDateTime + NumDraftDays() + 6)
		writeItemRow(ASFantasyHubDraftDateMessageHtmlView(fPageOptions));

	// Show upgrade team to premium
	writeItemRow(ASFantasyHubUpgradeMessageHtmlView(fPageOptions));

	// Show signup another team message
	writeItemRow(ASFantasyHubSignupMessageHtmlView(*this));
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildFreeAgentClaimMessages()
{
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	TFreeAgentClaimVector freeAgentClaimVector;
	TFreeAgentClaimVector::iterator iter;
	TFreeAgentClaimPtr freeAgentClaimPtr;

	LoadRecentFreeAgentClaimVectorByTeamID(teamPtr->getTeamID(),3,
		freeAgentClaimVector);

	// Show Pending
	for(iter = freeAgentClaimVector.begin();
		iter != freeAgentClaimVector.end(); ++iter)
	{
		freeAgentClaimPtr = *iter;

		if(freeAgentClaimPtr->getStatus() == facs_Pending)
		{
			writeItemRow(ASFantasyFreeAgentPendingMessageHtmlView(fPageOptions,
				freeAgentClaimPtr));
			fAnyPendingFreeAgentClaim = true;
		}
	}

	// Show Completed, Invalidated
	for(iter = freeAgentClaimVector.begin();
		iter != freeAgentClaimVector.end(); ++iter)
	{
		freeAgentClaimPtr = *iter;

		if((freeAgentClaimPtr->getStatus() == facs_Invalidated) ||
				(freeAgentClaimPtr->getStatus() == facs_Completed))
			writeItemRow(ASFantasyFreeAgentFinalMessageHtmlView(fPageOptions,
				freeAgentClaimPtr));
	}
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildMyTradeMessages(TTradeVector& tradeVector)
{
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	TTradePtr tradePtr;
	TTradeVector::iterator iter;

	for(iter = tradeVector.begin(); iter != tradeVector.end(); ++iter)
	{
		tradePtr = *iter;

		if(tradePtr->getTeamID() == teamPtr->getTeamID())
		{
			ASFantasyTradeInitiatedMessageHtmlView htmlView(fPageOptions,tradePtr);

			if(htmlView.show())
				fAnyInvolvedTradeMessages = true;

			writeItemRow(htmlView);
		}
		else if(tradePtr->getProposeToTeamID() == teamPtr->getTeamID())
		{
			writeItemRow(ASFantasyTradeReceivedMessageHtmlView(fPageOptions,tradePtr));
			fAnyInvolvedTradeMessages = true;
		}
	}
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildOtherTradeMessages(TTradeVector& tradeVector)
{
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	TTradePtr tradePtr;
	TTradeVector::iterator iter;

	for(iter = tradeVector.begin(); iter != tradeVector.end(); iter++)
	{
		tradePtr = *iter;

		if(!tradePtr->isTeamInvolvedInTrade(teamPtr->getTeamID()))
			writeItemRow(ASFantasyTradeProtestMessageHtmlView(fPageOptions,tradePtr));
	}
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::buildTradeMessages()
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TTradeVector tradeVector;

	if(leaguePtr->getGamePhase() != gmph_Season)
		return;

	LoadRecentTradesByLeagueID(leaguePtr->getLeagueID(),tradeVector);
	if(tradeVector.size() > 0)
	{
		buildMyTradeMessages(tradeVector);

		buildOtherTradeMessages(tradeVector);
	}
}

/******************************************************************************/

void ASFantasyHubPageHtmlView::writeBodyViewBody()
{
	bool showMoreItems;

	fMemberPtr = TMember::createGet(fPageOptions.getRqstMemberID(),cam_MustExist);

	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(
		(int)((double)getPageWidth() * 0.75)));

	showMoreItems = buildParticStatusMessages();

	if(showMoreItems)
	{
		if(fPageOptions.isSeasonView())
			buildSeasonMessages();
		else
			buildDraftMessages();
	}	
	
	fHtmlWriter.TableEnd(); 
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
