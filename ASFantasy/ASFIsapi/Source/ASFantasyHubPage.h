/* ASFantasyHubPage.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyHubPageH
#define ASFantasyHubPageH

#include "ASFantasyHtmlPageBuilder.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyHubLineItemHtmlView : public THtmlView
{
protected:
	THtmlPageOptions& fPageOptions;

protected:
	ASFantasyHubLineItemHtmlView(THtmlPageOptions& pageOptions) : 
		THtmlView(pageOptions), fPageOptions(pageOptions) {}

public:		
	virtual bool show() { return(true); }
};

/******************************************************************************/

class ASFantasyGlobalMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyGlobalMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyBadEmailMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	TMemberPtr fMemberPtr;

public:
	ASFantasyBadEmailMessageHtmlView(THtmlPageOptions& pageOptions,
		TMemberPtr memberPtr) : ASFantasyHubLineItemHtmlView(pageOptions),
		fMemberPtr(memberPtr) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyHubParticStatusHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	TParticStatus fStatus;

public:
	ASFantasyHubParticStatusHtmlView(THtmlPageOptions& pageOptions,
		TParticStatus status) : ASFantasyHubLineItemHtmlView(pageOptions),
		fStatus(status) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyHubSignupMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	ASFantasyBasePageHtmlView& fPage;

public:
	ASFantasyHubSignupMessageHtmlView(ASFantasyBasePageHtmlView& page) :
		ASFantasyHubLineItemHtmlView(page.getPageOptions()),fPage(page) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

enum ASFantasyHubUpgradeMessageTypeEnum
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
class ASFantasyHubUpgradeMessageType : public EnumType<ASFantasyHubUpgradeMessageTypeEnum,
	humt_Undefined,humt_Last>
{
public:
	ASFantasyHubUpgradeMessageType(int t = humt_Undefined) :
		EnumType<ASFantasyHubUpgradeMessageTypeEnum,humt_Undefined,
		humt_Last>(t) {}
};

class ASFantasyHubUpgradeMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
private:
	ASFantasyHubUpgradeMessageType fUpgradeMessageType;
	double fDaysRemaining;

public:
	ASFantasyHubUpgradeMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions),fDaysRemaining(0.0) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyHubDraftDateMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyHubDraftDateMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyScheduleMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyScheduleMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyLineupMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	const TScheduleDayVector& fScheduleDayVector;
	TScheduleDayPtr fScheduleDayPtr;
	bool fLineupIsLocked;

public:
	ASFantasyLineupMessageHtmlView(THtmlPageOptions& pageOptions,
		const TScheduleDayVector& scheduleDayVector) : 
		ASFantasyHubLineItemHtmlView(pageOptions),
		fScheduleDayVector(scheduleDayVector),fLineupIsLocked(false) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyInProgressGameResultMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	const TScheduleDayVector& fScheduleDayVector;
	TScheduleDayPtr fScheduleDayPtr;

public:
	ASFantasyInProgressGameResultMessageHtmlView(THtmlPageOptions& pageOptions,
		const TScheduleDayVector& scheduleDayVector) : 
		ASFantasyHubLineItemHtmlView(pageOptions),
		fScheduleDayVector(scheduleDayVector) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyCompletedGameResultMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	const TScheduleDayVector& fScheduleDayVector;
	TScheduleDayPtr fScheduleDayPtr;

public:
	ASFantasyCompletedGameResultMessageHtmlView(THtmlPageOptions& pageOptions,
		const TScheduleDayVector& scheduleDayVector) : 
		ASFantasyHubLineItemHtmlView(pageOptions),
		fScheduleDayVector(scheduleDayVector) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyFreeAgentGeneralMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyFreeAgentGeneralMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyFreeAgentPendingMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	TFreeAgentClaimPtr fFreeAgentClaimPtr;

public:
	ASFantasyFreeAgentPendingMessageHtmlView(THtmlPageOptions& pageOptions,
		TFreeAgentClaimPtr freeAgentClaimPtr) : 
		ASFantasyHubLineItemHtmlView(pageOptions),
		fFreeAgentClaimPtr(freeAgentClaimPtr) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyFreeAgentFinalMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	TFreeAgentClaimPtr fFreeAgentClaimPtr;

public:
	ASFantasyFreeAgentFinalMessageHtmlView(THtmlPageOptions& pageOptions,
		TFreeAgentClaimPtr freeAgentClaimPtr) : 
		ASFantasyHubLineItemHtmlView(pageOptions),
		fFreeAgentClaimPtr(freeAgentClaimPtr) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyTradeGeneralMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyTradeGeneralMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyTradeBaseMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
protected:
	TTradePtr fTradePtr;

public:
	ASFantasyTradeBaseMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : ASFantasyHubLineItemHtmlView(pageOptions),
			fTradePtr(tradePtr) {}

	void writeLinkToTrade(THTMLWriter& htmlWriter);
	void writeTrailer(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyTradeInvolvedMessageHtmlView :
	public ASFantasyTradeBaseMessageHtmlView
{
public:
	ASFantasyTradeInvolvedMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : ASFantasyTradeBaseMessageHtmlView(pageOptions,
			tradePtr) {}
};

/******************************************************************************/

class ASFantasyTradeInitiatedMessageHtmlView :
	public ASFantasyTradeInvolvedMessageHtmlView
{
public:
	ASFantasyTradeInitiatedMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : ASFantasyTradeInvolvedMessageHtmlView(pageOptions,
			tradePtr) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyTradeReceivedMessageHtmlView :
	public ASFantasyTradeInvolvedMessageHtmlView
{
public:
	ASFantasyTradeReceivedMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : ASFantasyTradeInvolvedMessageHtmlView(pageOptions,
			tradePtr) {}
	
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyTradeProtestMessageHtmlView :
	public ASFantasyTradeBaseMessageHtmlView
{
public:
	ASFantasyTradeProtestMessageHtmlView(THtmlPageOptions& pageOptions,
		TTradePtr tradePtr) : ASFantasyTradeBaseMessageHtmlView(pageOptions,
			tradePtr) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyPrizeWinnersMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyPrizeWinnersMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyOverallLeadersMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyOverallLeadersMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyPlayoffMessageHtmlView : public ASFantasyHubLineItemHtmlView
{
public:
	ASFantasyPlayoffMessageHtmlView(THtmlPageOptions& pageOptions) :
		ASFantasyHubLineItemHtmlView(pageOptions) {}
	
	virtual bool show();
	virtual void write(THTMLWriter& htmlWriter);
};

/******************************************************************************/

class ASFantasyHubPageHtmlView : public TTypeGammaPageHtmlView
{
protected:
	TMemberPtr fMemberPtr;
	bool fAnyPendingFreeAgentClaim;
	bool fAnyInvolvedTradeMessages;

protected:
	ASFantasyHubPageHtmlView(IsHtmlServer& isHtmlServer,
		THtmlPageOptions& pageOptions,THTMLWriter& htmlWriter) :
		TTypeGammaPageHtmlView(isHtmlServer,pageOptions,htmlWriter),
		fAnyPendingFreeAgentClaim(false),fAnyInvolvedTradeMessages(false) {}
	
	virtual CStrVar getPageTitle(void) const { return("Front Office"); }

	virtual ASFantasyBodyViewTitleType getBodyViewTitleType()
		{ return(tt_None); }

	void writeItemRow(ASFantasyHubLineItemHtmlView& lineItemHtmlView);
	bool buildParticStatusMessages();
	void buildDraftMessages();

	virtual void buildCompletedGameResultMessage(
		const TScheduleDayVector& scheduleDayVector);
	virtual void buildInProgressGameResultMessage(
		const TScheduleDayVector& scheduleDayVector);
	virtual void buildLineupMessage(
		const TScheduleDayVector& scheduleDayVector);
	void buildSeasonMessages();

	void buildFreeAgentClaimMessages();

	void buildMyTradeMessages(TTradeVector& tradeVector);
	void buildOtherTradeMessages(TTradeVector& tradeVector);
	void buildTradeMessages();

	virtual void writeBodyViewBody();

	friend class ASFantasyHtmlServer;
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyHubPageH
/******************************************************************************/
/******************************************************************************/
