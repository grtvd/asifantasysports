/* HubPageBuilder.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFootballType.h"
#include "FreeAgentPageBuilder.h"
#include "HubPageBuilder.h"

using namespace asfootball;

/******************************************************************************/

static const char* gGlobalMessageFile = "C:\\Program Files\\ASFootball\\GlobalMessage.txt";

/******************************************************************************/
/******************************************************************************/

class THubParticStatusHtmlView : public THubLineItemHtmlView
{
protected:
	TParticStatus fStatus;

public:
	THubParticStatusHtmlView(THtmlPageOptions& pageOptions,TParticStatus status) :
		THubLineItemHtmlView(pageOptions), fStatus(status) {}
	
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubSignupMessageHtmlView : public THubLineItemHtmlView
{
public:
	THubSignupMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

enum THubUpgradeMessageTypeEnum
{
	humt_Undefined,
	humt_UpgradeAvailable,			// General "can upgrade" message
	humt_UpgradeStatus,				// Upgrade status is not undefined
	humt_PremiumTrialAvailable,		// Premium trial can be taken
	humt_PremiumTrialDaysLeft,		// More than 1 day left on trial
	humt_PremiumTrialWillExpire,	// Less than 1 day left on trial
	humt_PremiumTrialExpired,		// Premium trial has expired
};
#define humt_Last humt_PremiumTrialExpired
class THubUpgradeMessageType : public EnumType<THubUpgradeMessageTypeEnum,
	humt_Undefined,humt_Last>
{
public:
	explicit THubUpgradeMessageType(int t = humt_Undefined) :
		EnumType<THubUpgradeMessageTypeEnum,humt_Undefined,humt_Last>(t) {}
};

class THubUpgradeMessageHtmlView : public THubLineItemHtmlView
{
private:
	THubUpgradeMessageType fUpgradeMessageType;
	double fDaysRemaining;

public:
	THubUpgradeMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions),fDaysRemaining(0.0) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubDraftDateMessageHtmlView : public THubLineItemHtmlView
{
protected:
	bool fHasJoinedLeague;
	
public:
	THubDraftDateMessageHtmlView(THtmlPageOptions& pageOptions,
		bool hasJoinedLeague) : THubLineItemHtmlView(pageOptions),
		fHasJoinedLeague(hasJoinedLeague) {}
	
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
protected:
	virtual void WriteContinueScout(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubScheduleMessageHtmlView : public THubLineItemHtmlView
{
public:
	THubScheduleMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubGameResultsMessageHtmlView : public THubLineItemHtmlView
{
protected:
	TFootballScheduleDayPtr fScheduleDayPtr;

public:
	THubGameResultsMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubLineupMessageHtmlView : public THubLineItemHtmlView
{
protected:
	TFootballScheduleDayPtr fScheduleDayPtr;
//	TFileStream* fFileStream;

public:
	THubLineupMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubFreeAgentMessageHtmlView : public THubLineItemHtmlView
{
public:
	THubFreeAgentMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubTradeGeneralMessageHtmlView : public THubLineItemHtmlView
{
public:
	THubTradeGeneralMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubTradeBaseMessageHtmlView : public THubLineItemHtmlView
{
protected:
	TTradePtr fTradePtr;

public:
	THubTradeBaseMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : THubLineItemHtmlView(pageOptions),
			fTradePtr(tradePtr) {}

	void writeLinkToTrade(THTMLWriter& htmlWriter) throw(Exception);
	void writeTrailer(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubTradeInvolvedMessageHtmlView : public THubTradeBaseMessageHtmlView
{
public:
	THubTradeInvolvedMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : THubTradeBaseMessageHtmlView(pageOptions,
			tradePtr) {}
};

/******************************************************************************/

class THubTradeInitiatedMessageHtmlView : public THubTradeInvolvedMessageHtmlView
{
public:
	THubTradeInitiatedMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : THubTradeInvolvedMessageHtmlView(pageOptions,
			tradePtr) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubTradeReceivedMessageHtmlView : public THubTradeInvolvedMessageHtmlView
{
public:
	THubTradeReceivedMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : THubTradeInvolvedMessageHtmlView(pageOptions,
			tradePtr) {}
	
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubTradeProtestMessageHtmlView : public THubTradeBaseMessageHtmlView
{
public:
	THubTradeProtestMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : THubTradeBaseMessageHtmlView(pageOptions,
			tradePtr) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubPlayoffMessageHtmlView : public THubLineItemHtmlView
{
public:
	THubPlayoffMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/

class THubGlobalMessageHtmlView : public THubLineItemHtmlView
{
public:
	THubGlobalMessageHtmlView(THtmlPageOptions& pageOptions) :
		THubLineItemHtmlView(pageOptions) {}
	
	virtual bool show() throw(Exception);
	virtual void Write(THTMLWriter& htmlWriter) throw(Exception);
};

/******************************************************************************/
/******************************************************************************/

void THubParticStatusHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	if((fStatus == pts_NeedCCInfo) || (fStatus == pts_WaitingApproval))
	{
		if(fStatus == pts_NeedCCInfo)
		{
	
			htmlWriter.TextString("Your credit card information is not on file.  "
				"You must send your credit card information via fax at ");
			
			//BOB htmlWriter.Text(fPageOptions.getTechSupportFaxNumber());
			htmlWriter.TextString(fPageOptions.getTechSupportFaxNumber().c_str());

			htmlWriter.TextString(" or call WWFF at ");	//BOB AppName
			
			htmlWriter.TextString(fPageOptions.getTechSupportPhoneNumber().c_str());
			htmlWriter.TextString(".  ");
		}
		else
		{
			htmlWriter.TextString("Your payment has not yet been approved.  ");
		}

		htmlWriter.TextString("You will not be able to join a league until your "
			"payment has  been processed.  In the meantime, you can begin "
			"scouting players on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" page.");
	}
	else if(fStatus == pts_PaymentDenied)
	{
		htmlWriter.TextString("ALERT! Your payment has been denied. Please contact "
			"WWFF Tech Support immediately by phone at ");
		htmlWriter.TextString(fPageOptions.getTechSupportPhoneNumber().c_str());
		htmlWriter.TextString(" so this issue can be resolved.");
	}
	else if(fStatus == pts_PaymentApproved)
	{
		htmlWriter.TextString("Your payment has been approved.  You should join a "
			"league as soon as possible on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLeagueSignupPage);
		htmlWriter.TextString(" page.");
	}
	else if(fStatus == pts_Disabled)
	{
		htmlWriter.TextString("ALERT! Your WWFF account has been disabled.  Please "
			"contact ");
		TMailToTheRefHtmlView::Build(htmlWriter);
		htmlWriter.TextString(" for more information.");
	}
	else if(fStatus == pts_GameOver)
	{
		htmlWriter.Paragraph("The WWFF season is complete and access to your "
			"team is no longer available.",ahLeft);
			
		htmlWriter.Paragraph("Thanks for playing.  See you next year.",ahLeft);
	}
	else
		throw Exception("THubParticStatusHtmlView::Write: unknown fStatus");
}

/******************************************************************************/
/******************************************************************************/

bool THubSignupMessageHtmlView::show() throw(Exception)
{
	TDateTime today = TDateTime::CurrentDate();

	if((today >= SignupStartDate()) && (today <= SignupEndDate()))
		return(true);

	return(false);
}

/******************************************************************************/

void THubSignupMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlNewParticSignupGetPage);
	htmlWriter.TextString(" now for another WWFF team.");
}

/******************************************************************************/
/******************************************************************************/

#define PremiumTrialDays()		(7)		//BOB move to AppOptions

bool THubUpgradeMessageHtmlView::show() throw(Exception)
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
						throw Exception("THubUpgradeMessageHtmlView::show: invalid TrialDateTime");
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
				throw Exception("THubUpgradeMessageHtmlView::show: unknow GameLevel");
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

void THubUpgradeMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
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
			
			//BOB htmlWriter.Text(fPageOptions.getTechSupportFaxNumber());
			htmlWriter.TextString(fPageOptions.getTechSupportFaxNumber().c_str());

			htmlWriter.TextString(" or call WWFF at ");	//BOB AppName
			
			htmlWriter.TextString(fPageOptions.getTechSupportPhoneNumber().c_str());
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
			htmlWriter.TextString(" payment has been denied. Please contact WWFF "
				"Tech Support immediately by phone at ");
			htmlWriter.TextString(fPageOptions.getTechSupportPhoneNumber().c_str());
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
			throw Exception("THubUpgradeMessageHtmlView::Write: invalid UpgradeStatus");
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
		throw Exception("THubUpgradeMessageHtmlView::Write: invalid UpgradeMessageType");
}

/******************************************************************************/
/******************************************************************************/

// Message about DraftDate, either not set, upcoming, or results available.

void THubDraftDateMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	TLeaguePtr leaguePtr;
	TDateTime draftDate;
	TDateTime tempDate;
	TDateTime curDate = TDateTime::CurrentDate();
	TDateTime curTime = TDateTime::CurrentTime();
	TDateTime curDateTime = curDate + curTime;

	if(fPageOptions.isRqstLeagueSet())
	{
		leaguePtr = fPageOptions.getRqstLeague();
		draftDate = leaguePtr->getDraftDate();

//		if(draftDate != TDateTime())
//			draftDate += NightlyProcessingTime();
	}
	
	// Draft Date not set
	if(!fHasJoinedLeague || (draftDate == TDateTime()))
	{
		htmlWriter.TextString("Your Draft date has not been set.  ");

		if(!leaguePtr.isNull() && leaguePtr->isReserved())
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
			
			if(numTeams < MinTeamsPerPrivateLeague)
				htmlWriter.TextString("at least 8 teams by ");
			else
				htmlWriter.TextString("an even number of teams on ");

			htmlWriter.TextString(nextProcessingTime.FormatString(
				fPageOptions.getDateTimeFormat()).c_str());
			htmlWriter.TextString(", then your first Draft day will take place on ");
			htmlWriter.TextString(tempDate.FormatString(
				fPageOptions.getDateTimeFormat()).c_str());
			htmlWriter.TextString(".  ");
		}
		else
		{
			htmlWriter.TextString("Your Draft date will be set once ");
			
			// Not in league
			if(!fHasJoinedLeague)
			{
				htmlWriter.TextString("you join a league and that league fills.  ");
			}
			// Draft Date not set
			else
			{
				htmlWriter.TextString("the ");
				htmlWriter.TextString(leaguePtr->getName());
				htmlWriter.TextString(" League fills.  ");

				tempDate = leaguePtr->getEarliestDraftDate(false) + NightlyProcessingTime();
				 
				htmlWriter.LineBreak();
				htmlWriter.TextString("The ");
				htmlWriter.TextString(leaguePtr->getName());
				htmlWriter.TextString(" League's earliest possible Draft date is ");
				htmlWriter.TextString(tempDate.FormatString(
					fPageOptions.getDateTimeFormat()).c_str());
				htmlWriter.TextString(".  ");
			}
		}

		WriteContinueScout(htmlWriter);
	}
	// Draft upcoming
	else if(curDateTime < draftDate + NightlyProcessingTime())
	{
		htmlWriter.TextString("YOUR DRAFT DATE HAS BEEN SET.  The first Draft day "
			"for the ");
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League will take place on ");
		htmlWriter.TextString((draftDate + NightlyProcessingTime()).FormatString(
			fPageOptions.getDateTimeFormat()).c_str());
		htmlWriter.TextString(".  You can continue to scout players on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" page right up until Draft time.");
	}
	// Draft Results Available
	else if((curDate >= draftDate) && (curDate < draftDate + NumDraftDays - 1))
	{
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League Draft Day ");

		htmlWriter.TextString(CStr31().CopyVarg("%d",
			(int)(curDate - draftDate + 1)).c_str());
		
		htmlWriter.TextString(" results are now available.  See the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftResultsPage);
		htmlWriter.TextString(" page for details.  ");

		htmlWriter.TextString("You can still adjust your draft rankings on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
		htmlWriter.TextString(" page for the remaining draft rounds.");
	}
	// Show message for Final Draft Results for 7 days after end of Draft
	else if((curDate >= draftDate + NumDraftDays - 1) && (curDate < draftDate + 7))
	{
		htmlWriter.TextString(leaguePtr->getName());
		htmlWriter.TextString(" League's Final Draft results can been seen on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftResultsPage);
		htmlWriter.TextString(" page.");
	}
}

/******************************************************************************/

void THubDraftDateMessageHtmlView::WriteContinueScout(THTMLWriter& htmlWriter)
	throw(Exception)
{
	htmlWriter.TextString("In the meantime, you can continue to scout players on the ");
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlDraftRankingsPage);
	htmlWriter.TextString(" page.  ");
}

/******************************************************************************/
/******************************************************************************/

void THubScheduleMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	
	htmlWriter.TextString(leaguePtr->getName());
	htmlWriter.TextString(" League's season schedule has been set.  Check it out on the ");
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlSchedulePage);
	htmlWriter.TextString(" page.");
}

/******************************************************************************/
/******************************************************************************/

bool THubGameResultsMessageHtmlView::show() throw(Exception)
{
	TScheduleDayGame scheduleDayGame;
	
	fScheduleDayPtr = GetLastCompleteScheduleDayForLeagueID(
		fPageOptions.getRqstLeague()->getLeagueID(),
		TDateTime::CurrentTime() < NightlyProcessingTime());

	if(!fScheduleDayPtr.isNull())
	{
		if(fScheduleDayPtr->getScheduleDayGameByTeamID(
			fPageOptions.getRqstTeam()->getTeamID(),scheduleDayGame))
		{
			if(scheduleDayGame.wasGamePlayed())
			{
				// Show for three days
				if((TDateTime::CurrentDate() >= fScheduleDayPtr->getGameDate()) &&
						(TDateTime::CurrentDate() <= fScheduleDayPtr->getGameDate() + 2))
					return(true);
			}
		}
	}

	return(false);
}

/******************************************************************************/

void THubGameResultsMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	if(!fScheduleDayPtr.isNull())
	{
		htmlWriter.TextString("Game ");
		htmlWriter.TextString(fScheduleDayPtr->getNFLWeek().c_str());
		htmlWriter.TextString(" results are now available on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlGameResultsPage);
		htmlWriter.TextString(" page.");
	}
}

/******************************************************************************/
/******************************************************************************/

bool THubLineupMessageHtmlView::show() throw(Exception)
{
	TScheduleDayGame scheduleDayGame;
	
	fScheduleDayPtr = GetNextScheduleDayForLeagueID(
		fPageOptions.getRqstLeague()->getLeagueID(),
		TDateTime::CurrentTime() > NightlyProcessingTime());

	if(!fScheduleDayPtr.isNull())
	{
		if(fScheduleDayPtr->getScheduleDayGameByTeamID(
			fPageOptions.getRqstTeam()->getTeamID(),scheduleDayGame))
		{
			// This condition is for leagues that started late and end
			// their draft during the lockout period.
			//BOB TEST THIS
			//BOB if(fPageOptions.getRqstLeague()->getSeasonDate() <=
			//BOB 		fScheduleDayPtr->getGameDate())
				return(true);
		}
	}

	return(false);
}

/******************************************************************************/

void THubLineupMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	#if 0
	TFootballScheduleDayPtr scheduleDayPtr =
		GetNextScheduleDayForLeagueID(leaguePtr->getLeagueID(),
		TDateTime::CurrentTime() > NightlyProcessingTime());
	#endif
	TDateTime lineupLockoutTime = fScheduleDayPtr->getEarlyProfGameDate()
		+ LineupLockoutTime();

	if(TDateTime::CurrentDateTime() > lineupLockoutTime)
	{
		htmlWriter.TextString("Your lineup for this week's game is now locked but "
			"it can still be viewed on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLineupPage);
		htmlWriter.TextString(" page.  ");
	}
	else
	{
		htmlWriter.TextString("Set your lineup for this week's game on the ");
		TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlLineupPage);
		htmlWriter.TextString(" page.  Your lineup can be changed until ");

		htmlWriter.TextString(lineupLockoutTime.FormatString(
			fPageOptions.getDateTimeFormat()).c_str());
		htmlWriter.TextString(". ");
	}

	if(leaguePtr->getGamePhase() == gmph_Playoffs)
	{
		if(fScheduleDayPtr->getNFLWeek() == NumNFLWeeks + 1)
			htmlWriter.TextString("The Semi-Final Games ");
		else
			htmlWriter.TextString("The Final Game ");
	}
	else
	{
		htmlWriter.TextString("Game ");
		htmlWriter.TextString(fScheduleDayPtr->getNFLWeek().c_str());
	}
	htmlWriter.TextString(" will take place on ");

	htmlWriter.TextString((fScheduleDayPtr->getLateProfGameDate() + 1.0
		+ NightlyProcessingTime()).FormatString(
		fPageOptions.getDateTimeFormat()).c_str());
	
	htmlWriter.TextString(".  Game results will be available shortly thereafter.");
}

/******************************************************************************/
/******************************************************************************/

bool THubFreeAgentMessageHtmlView::show() throw(Exception)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();

	return((leaguePtr->getGamePhase() == gmph_PreSeason) ||
		(leaguePtr->getGamePhase() == gmph_Season));
}

/******************************************************************************/

void THubFreeAgentMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	htmlWriter.TextString("Players can be claimed off Waivers on the ");
	TTextNavHTMLView::Build(htmlWriter,fPageOptions,htmlFreeAgentPage);
	htmlWriter.TextString(" page.");


	htmlWriter.TextString("  You may have ");
	//BOBhtmlWriter.TextEffectStart(efStrong);
	htmlWriter.Font("only one",0,fcAbsolute,ASFantasyStandardFont(),clRed);
	//BOBhtmlWriter.TextEffectEnd(efStrong);
	htmlWriter.TextString(" free agent claim pending at a time.  Submitting a "
		"second claim overwrites any previous pending claim.");
//BOB		"second claim overwrites any previous pending claim.  The next free "
//BOB		"agent claim processing will take place on ");
//BOB	htmlWriter.Text(NextFreeAgentProcessingDateTime(
//BOB		fPageOptions.getRqstLeague()).FormatString(
//BOB		fPageOptions.getDateTimeFormat()).c_str());
//BOB	htmlWriter.Text(".");
}

/******************************************************************************/
/******************************************************************************/

bool THubTradeGeneralMessageHtmlView::show() throw(Exception)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();

	if((TDateTime::CurrentDate() >= TradingStartDate()) &&
			(TDateTime::CurrentDate() <= TradingEndDate()) &&
			(leaguePtr->getGamePhase() == gmph_Season))
		return(true);

	return(false);
}

/******************************************************************************/

void THubTradeGeneralMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
const char* getDateFormat = "dddd', 'mmmm' 'd'";	//BOB in fPageOptions
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	CStrVar str;

//	htmlWriter.Text("Trading will be available this week. We are sorry for the inconvenience.");

	if(TDateTime::CurrentDate() >= TradingEndDate() - 14)
	{
		htmlWriter.TextEffect(efEmphasized,"ATTENTION: ");
		htmlWriter.TextString("The Trading deadline nears. ");
		htmlWriter.LineBreak();

		str.copyVarg("Trades must be proposed by %s on the ",
			TradingEndDate().FormatString(getDateFormat).c_str());
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

void THubTradeBaseMessageHtmlView::writeLinkToTrade(THTMLWriter& htmlWriter)
	throw(Exception)
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlTradePage));
	CStr255 url = pageLinkInfo.GetLinkURL(fPageOptions).c_str();

	url.ConcatVarg("&TradeID=%s",fTradePtr->getTradeID().c_str());

	htmlWriter.Link(url.c_str(),"","Click Here");
	htmlWriter.TextString(" to view this trade.");
}

/******************************************************************************/

void THubTradeBaseMessageHtmlView::writeTrailer(THTMLWriter& htmlWriter)
	throw(Exception)
{
	htmlWriter.TextString(" has ");

	switch(fTradePtr->getStatus())
	{
		case trs_Proposed:
			htmlWriter.TextEffect(efEmphasized,"not yet been accepted or declined");
			htmlWriter.TextString(". ");

			htmlWriter.TextString("The trade must be accepted by ");

			htmlWriter.TextString(NextProcessingDateTime(fTradePtr->getProposedDate(),
				MaxTradeProposeDays).FormatString(
				fPageOptions.getDateTimeFormat()).c_str());

			htmlWriter.TextString(" or it will expire. ");

			writeLinkToTrade(htmlWriter);
			break;
		case trs_Cleared:
			htmlWriter.TextString("been ");
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("withdrawn",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(".");
			break;
		case trs_Declined:
			htmlWriter.TextString("been ");
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("declined",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(".");
			break;
		case trs_Accepted:
			htmlWriter.TextString("been ");
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("accepted",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(". ");

			htmlWriter.TextString("Other league Owners have until ");

			htmlWriter.TextString(NextProcessingDateTime(fTradePtr->getAcceptedDate(),
				MaxTradeProtestDays).FormatString(
				fPageOptions.getDateTimeFormat()).c_str());

			htmlWriter.TextString(" to protest the trade. ");

			writeLinkToTrade(htmlWriter);
			break;
		case trs_Expired:
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("expired",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(".");
			break;
		case trs_Protested:
			htmlWriter.TextString("been ");
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("protested",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(" by the league Owners.");
			break;
		case trs_Invalidated:
			htmlWriter.TextString("been ");
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("invalidated",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(" by another roster move.");
			break;
		case trs_Completed:
			htmlWriter.TextString("been ");
			//BOBhtmlWriter.TextEffectStart(efStrong);
			htmlWriter.Font("completed",0,fcAbsolute,ASFantasyStandardFont(),clRed);
			//BOBhtmlWriter.TextEffectEnd(efStrong);
			htmlWriter.TextString(".");
			break;
		default:
			TOOLDEBUG( tErrorMsg("THubTradeBaseMessageHtmlView::writeTrailer: bad status"); );
			break;
	}
}

/******************************************************************************/
/******************************************************************************/

bool THubTradeInitiatedMessageHtmlView::show() throw(Exception)
{
	return(fTradePtr->getStatus() != trs_Cleared);
}

/******************************************************************************/

void THubTradeInitiatedMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	TTeamPtr proposedToTeamPtr = TTeam::createGet(fTradePtr->getProposeToTeamID(),
		cam_MustExist);

	htmlWriter.TextString("Your trade proposed on ");
	htmlWriter.TextString(fTradePtr->getProposedDate().FormatString(
		fPageOptions.getDateTimeFormat()).c_str());
	htmlWriter.TextString(" to the ");
	htmlWriter.TextEffect(efEmphasized,proposedToTeamPtr->getFullTeamName().c_str());
	writeTrailer(htmlWriter);
}

/******************************************************************************/
/******************************************************************************/

void THubTradeReceivedMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
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
		htmlWriter.TextString(fTradePtr->getProposedDate().FormatString(
			fPageOptions.getDateTimeFormat()).c_str());
		htmlWriter.TextString(",");
	}
	writeTrailer(htmlWriter);
}

/******************************************************************************/
/******************************************************************************/

bool THubTradeProtestMessageHtmlView::show() throw(Exception)
{
	return((fTradePtr->getStatus() == trs_Accepted) ||
		(fTradePtr->getStatus() == trs_Protested) ||
		(fTradePtr->getStatus() == trs_Invalidated) ||
		(fTradePtr->getStatus() == trs_Completed));
}

/******************************************************************************/

void THubTradeProtestMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
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
			//BOB create TTrade method: hasTeamProtestedTrade()
			/*
			if(find(fTradePtr->protestTeamIDVector().begin(),
				fTradePtr->protestTeamIDVector().end(),
				fPageOptions.getRqstTeam()->getTeamID()) !=
				fTradePtr->protestTeamIDVector().end())
			*/
			if(fTradePtr->protestTeamIDVector().contains(
				fPageOptions.getRqstTeam()->getTeamID()))
			{
				htmlWriter.TextString("You have already protested this trade. ");
			}
			else
			{
				htmlWriter.TextString("You have until ");

				htmlWriter.TextString(protestEnd.FormatString(
					fPageOptions.getDateTimeFormat()).c_str());

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

bool THubPlayoffMessageHtmlView::show() throw(Exception)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();

	return((leaguePtr->getGamePhase() == gmph_Playoffs) ||
		(leaguePtr->getGamePhase() == gmph_PostSeason));
}

/******************************************************************************/

void THubPlayoffMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
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
	
bool THubGlobalMessageHtmlView::show() throw(Exception)
{
	return(FileExists(gGlobalMessageFile));
}

/******************************************************************************/

void THubGlobalMessageHtmlView::Write(THTMLWriter& htmlWriter) throw(Exception)
{
	htmlWriter.InsertFile(gGlobalMessageFile);
}

/******************************************************************************/
/******************************************************************************/

void HubRightPanelHtmlView::writeItemRow(THubLineItemHtmlView& lineItemHtmlView,
	THTMLWriter& htmlWriter)
{
	if(lineItemHtmlView.show())
	{
		htmlWriter.TableRowStart();

		htmlWriter.TableCellStart(0,0,THtmlWidthValue(30),THtmlHeight(),ahLeft,avTop);
		htmlWriter.Image(fPageOptions.buildImagePath("Foot_30x18.gif").c_str(),
			"","",aiDefault,THtmlWidthValue(30),THtmlHeightValue(18));
		htmlWriter.TableCellEnd();
	
		htmlWriter.TableCellStart(0,0,THtmlWidth(ntPercent,100),THtmlHeight(),ahLeft,avTop);
		htmlWriter.TextEffectStart(efStrong);
		htmlWriter.FontStart(2,fcAbsolute,ASFantasyStandardFont());
		lineItemHtmlView.Write(htmlWriter);
		htmlWriter.FontEnd();
		htmlWriter.TextEffectEnd(efStrong);
		htmlWriter.TableCellEnd();
	
		htmlWriter.TableRowEnd();

		// Blank line	
		htmlWriter.TableRowStart();
		TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidth(30),THtmlHeightValue(10));
		TEmptyTableCellHTMLView::Build(htmlWriter,fPageOptions,THtmlWidth(30),THtmlHeightValue(10));
		htmlWriter.TableRowEnd();

		// Is this a Trade message involving my team?
		if(dynamic_cast<THubTradeInvolvedMessageHtmlView*>(&lineItemHtmlView) != NULL)
			fAnyInvolvedTradeMessages = true;
	}
}

/******************************************************************************/

bool HubRightPanelHtmlView::buildParticStatusMessages(THTMLWriter& htmlWriter)
	throw(Exception)
{
	TParticStatus status = fPageOptions.getRqstPartic()->getStatus();
	bool showMoreItems = false;
	
	if((status == pts_NeedCCInfo) ||
		(status == pts_WaitingApproval) ||
		(status == pts_PaymentApproved))
	{
		writeItemRow(THubParticStatusHtmlView(fPageOptions,status),htmlWriter);

		if(status == pts_PaymentApproved)
			showMoreItems = true;
	}
	else if(status == pts_Active)
	{
		showMoreItems = true;
	}
	else if((status == pts_PaymentDenied) ||
		(status == pts_Disabled) ||
		(status == pts_GameOver))
	{
		writeItemRow(THubParticStatusHtmlView(fPageOptions,status),htmlWriter);
	}
	else
		throw Exception("HubBodyHTMLView::buildParticStatusMessages: unknown status");
	
	return(showMoreItems);
}

/******************************************************************************/

void HubRightPanelHtmlView::buildDraftMessages(THTMLWriter& htmlWriter)
{
	TParticStatus status = fPageOptions.getRqstPartic()->getStatus();
	
	writeItemRow(THubDraftDateMessageHtmlView(fPageOptions,
		(status == pts_Active)),htmlWriter);

	// Show upgrade team to premium
	writeItemRow(THubUpgradeMessageHtmlView(fPageOptions),htmlWriter);

	// Show signup another team message
	writeItemRow(THubSignupMessageHtmlView(fPageOptions),htmlWriter);
}

/******************************************************************************/

void HubRightPanelHtmlView::buildSeasonMessages(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TDateTime draftDate = leaguePtr->getDraftDate();
	TDateTime curDate = TDateTime::CurrentDate();
//	TDateTime curTime = TDateTime::CurrentTime();
//	TDateTime curDateTime = curDate + curTime;

	writeItemRow(THubGlobalMessageHtmlView(fPageOptions),htmlWriter);

	// Show Playoff message
	writeItemRow(THubPlayoffMessageHtmlView(fPageOptions),htmlWriter);
	
	// Show important messages for Trading
	buildTradeMessages(htmlWriter);

	// Show message for Schedule for 7 days after end of Draft
	if((curDate >= draftDate + NumDraftDays - 1) && (curDate < draftDate + 7))
		writeItemRow(THubScheduleMessageHtmlView(fPageOptions),htmlWriter);
		
	// Show message for Game Results
	writeItemRow(THubGameResultsMessageHtmlView(fPageOptions),htmlWriter);
		
	// Show message for Lineup
	writeItemRow(THubLineupMessageHtmlView(fPageOptions),htmlWriter);

	// Show message for Free Agents
	writeItemRow(THubFreeAgentMessageHtmlView(fPageOptions),htmlWriter);

	// Show general message for Trading
	if(!fAnyInvolvedTradeMessages)
		writeItemRow(THubTradeGeneralMessageHtmlView(fPageOptions),htmlWriter);
	
	// Show draft messages for 7 days after end of Draft
	if(curDate < draftDate + 7)
		buildDraftMessages(htmlWriter);
	else // Draft messages already show Upgrade and Signup
	{
		// Show upgrade team to premium
		writeItemRow(THubUpgradeMessageHtmlView(fPageOptions),htmlWriter);

		// Show signup another team message
		writeItemRow(THubSignupMessageHtmlView(fPageOptions),htmlWriter);
	}
}

/******************************************************************************/

void HubRightPanelHtmlView::buildMyTradeMessages(THTMLWriter& htmlWriter,
	TTradeVector& tradeVector)
{
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	TTradePtr tradePtr;
	TTradeVector::iterator iter;

	for(iter = tradeVector.begin(); iter != tradeVector.end(); iter++)
	{
		tradePtr = *iter;

		if(tradePtr->getTeamID() == teamPtr->getTeamID())
			writeItemRow(THubTradeInitiatedMessageHtmlView(fPageOptions,tradePtr),
				htmlWriter);
		else if(tradePtr->getProposeToTeamID() == teamPtr->getTeamID())
			writeItemRow(THubTradeReceivedMessageHtmlView(fPageOptions,tradePtr),
				htmlWriter);
	}
}

/******************************************************************************/

void HubRightPanelHtmlView::buildOtherTradeMessages(THTMLWriter& htmlWriter,
	TTradeVector& tradeVector)
{
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	TTradePtr tradePtr;
	TTradeVector::iterator iter;

	for(iter = tradeVector.begin(); iter != tradeVector.end(); iter++)
	{
		tradePtr = *iter;

		if(!tradePtr->isTeamInvolvedInTrade(teamPtr->getTeamID()))
			writeItemRow(THubTradeProtestMessageHtmlView(fPageOptions,tradePtr),
				htmlWriter);
	}
}

/******************************************************************************/

void HubRightPanelHtmlView::buildTradeMessages(THTMLWriter& htmlWriter)
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TTradeVector tradeVector;

	if(leaguePtr->getGamePhase() != gmph_Season)
		return;

	LoadRecentTradesByLeagueID(leaguePtr->getLeagueID(),tradeVector);
	if(tradeVector.size() > 0)
	{
		buildMyTradeMessages(htmlWriter,tradeVector);

		buildOtherTradeMessages(htmlWriter,tradeVector);
	}
}

/******************************************************************************/

void HubRightPanelHtmlView::writeContentView(THTMLWriter& htmlWriter)
{
	bool showMoreItems;
	
	htmlWriter.TableStart(SHOW_BORDER,THtmlWidth(ntPercent,100));

	showMoreItems = buildParticStatusMessages(htmlWriter);

	if(showMoreItems)
	{
		if(fPageOptions.isSeasonView())
			buildSeasonMessages(htmlWriter);
		else
			buildDraftMessages(htmlWriter);
	}	
	
	htmlWriter.TableEnd(); 
}

/******************************************************************************/
/******************************************************************************/
 



