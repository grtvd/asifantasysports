/* ASFantasyTradePage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyTradePage.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyTradeJavaPanelHtmlView : public TJavaPanelHtmlView
{
protected:
	TTradeID fTradeID;

public:
	ASFantasyTradeJavaPanelHtmlView(THtmlPageOptions& pageOptions,
		ASFantasyJavaArchive javaArchive,const char* javaClass,int javaWidth,
		int javaHeight,TTradeID tradeID) : TJavaPanelHtmlView(pageOptions,
		javaArchive,javaClass,javaWidth,javaHeight),fTradeID(tradeID) {}

protected:
	virtual void WriteParameters(THTMLWriter& htmlWriter);
};

/******************************************************************************/

void ASFantasyTradeJavaPanelHtmlView::WriteParameters(THTMLWriter& htmlWriter)
{
	if(!fTradeID.isUndefined())
		htmlWriter.JavaParamString("TradeID",fTradeID.c_str());
}

/******************************************************************************/
/******************************************************************************/

void ASFantasyTradePageHtmlView::initialize()
{
	TLeaguePtr leaguePtr = fPageOptions.getRqstLeague();
	TTeamPtr teamPtr = fPageOptions.getRqstTeam();
	TTradePtr tradePtr;
	int protestsRemaining;

	TTypeGammaPageHtmlView::initialize();

	fTradeID = fIsHtmlServer.getNumericField("TradeID",cam_MayNotExist);

	if(fTradeID.isUndefined())
	{
		TTradeVector tradeVector;

		LoadOpenTradesByTeamID(teamPtr->getTeamID(),tradeVector);
		if(tradeVector.size() > 0)
		{
			tradePtr = *tradeVector.begin();
			fTradeID = tradePtr->getTradeID();
		}
	}
	else
		tradePtr = TTrade::createGet(fTradeID,cam_MustExist);

	if(tradePtr.isNull())
	{
		if(TDateTime::CurrentDate() > TradingEndDate())
		{
			fInstructions.copy("Trading is no longer available.");
			return;
		}
		
		if(TDateTime::CurrentDate() < TradingStartDate())
		{
			fInstructions.copyVarg("Trading will be available beginning %s.",
				TradingStartDate().FormatString(ASFantasyStandardDateFormat()
				).c_str());
			return;
		}

		fJavaClass.copy("TradeProposeApplet");
		fInstructions.copy("Propose a new trade offer.");
	}
	else
	{
		if(tradePtr->getTeamID() == teamPtr->getTeamID())
		{
			fJavaClass.copy("TradeProposeApplet");

			if(tradePtr->getStatus() == trs_Proposed)
			{
				fInstructions.copy("Your previously proposed trade "
					"has not yet been accepted or declined. "
					"The trade must be accepted by ");

				fInstructions.concat(NextProcessingDateTime(
					tradePtr->getProposedDate(),MaxTradeProposeDays
					).FormatString(ASFantasyStandardDateTimeFormat()).c_str());

				fInstructions.concat(" or it will expire. ");
			}
			else if(tradePtr->getStatus() == trs_Accepted)
			{
				fInstructions.copy("Your previously proposed trade "
					"has been accepted. ");

				fInstructions.concat("Other league Owners have until ");

				fInstructions.concat(NextProcessingDateTime(
					tradePtr->getAcceptedDate(),MaxTradeProtestDays
					).FormatString(ASFantasyStandardDateTimeFormat()).c_str());

				fInstructions.concat(" to protest the trade. ");
			}
			else
				throw ASIException("ASFantasyTradePageHtmlView::initialize: my trade, bad status");
		}
		else if(tradePtr->getProposeToTeamID() == teamPtr->getTeamID())
		{
			fJavaClass.copy("TradeReceiveApplet");

			if(tradePtr->getStatus() == trs_Proposed)
			{
				fInstructions.copy("You must accept or decline the "
					"proposed trade. The trade must be accepted by ");

				fInstructions.concat(NextProcessingDateTime(
					tradePtr->getProposedDate(),MaxTradeProposeDays
					).FormatString(ASFantasyStandardDateTimeFormat()).c_str());

				fInstructions.concat(" or it will expire. ");
			}
			else if(tradePtr->getStatus() == trs_Accepted)
			{
				fInstructions.copy("You have already accepted "
					"the proposed trade. ");

				fInstructions.concat("Other league Owners have until ");

				fInstructions.concat(NextProcessingDateTime(
					tradePtr->getAcceptedDate(),MaxTradeProtestDays
					).FormatString(ASFantasyStandardDateTimeFormat()).c_str());

				fInstructions.concat(" to protest the trade. ");
			}
			else
				throw ASIException("ASFantasyTradePageHtmlView::initialize: their trade, bad status");
		}
		else
		{
			fJavaClass.copy("TradeProtestApplet");

			if(!tradePtr->hasTeamProtestedTrade(teamPtr->getTeamID()))
			//BOB if(find(tradePtr->protestTeamIDVector().begin(),
			//BOB 	tradePtr->protestTeamIDVector().end(),
			//BOB 	teamPtr->getTeamID()) == tradePtr->protestTeamIDVector().end())
			{
				fInstructions.copyVarg("Please review the proposed trade. "
					"If you feel the trade is unjust, you may protest it. "
					"Each Owner is allowed %d protests for the season. ",
					(int)(MaxTradeProtestsAllowed));

				protestsRemaining = MaxTradeProtestsAllowed -
					teamPtr->getNumTradeProtests();
				if(protestsRemaining > 0)
				{
					fInstructions.concatVarg("You currently have %d protest",
						(int)protestsRemaining);

					if(protestsRemaining > 1)
						fInstructions.concat("s");

					fInstructions.concat(" remaining. You have until ");

					fInstructions.concat(NextProcessingDateTime(
						tradePtr->getAcceptedDate(),MaxTradeProtestDays
						).FormatString(ASFantasyStandardDateTimeFormat()).c_str());

					fInstructions.concat(" to protest this trade. ");
				}
				else
					fInstructions.concat("You have no protests remaining.");
			}
			else
				fInstructions.concat("You have already protested this trade.");
		}
	}

	if(!fJavaClass.hasLen())
		throw ASIException("ASFantasyTradePageHtmlView::initialize: need JavaClass");

	fAreTradesAvail = true;
}

/******************************************************************************/

void ASFantasyTradePageHtmlView::writeBodyViewBody()
{
	if(fAreTradesAvail)
	{
		ASFantasyTradeJavaPanelHtmlView htmlView(fPageOptions,fja_Season,
			fJavaClass,getBodyViewWidth(),getBodyViewBodyHeight(),fTradeID);

		fHtmlWriter.WriteView(htmlView);
	}
	else
		TTypeGammaPageHtmlView::writeBodyViewBody();
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
