/* ASFantasyTradeProposeUpdateRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommMisc.h"

#include "ASFantasyAppOptions.h"
#include "ASFantasyDB.h"
#include "ASFantasyObjectStore.h"
#include "ASFantasyTradeProposeUpdateRqst.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProposeUpdateResp : public TStreamable
{
private:
	TTradeID fTradeID;

public:
	TradeProposeUpdateResp(TTradeID tradeID) { fTradeID = tradeID; }

	virtual const char* className() const { return("TradeProposeUpdateResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void TradeProposeUpdateResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProposeUpdateResp::readFromFiler: not supported");
}

/******************************************************************************/

void TradeProposeUpdateResp::writeToFiler(TDataFiler& filer)
{
	filer.writeLong(fTradeID.getID());
}

/******************************************************************************/
/******************************************************************************/

void TradeProposeUpdateRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();

	fTradeID = filer.readLong();
	fProposeToTeamID = filer.readLong();
	fGetPlayerIDVector.readFromFiler(filer);
	fGivePlayerIDVector.readFromFiler(filer);
	fReleasePlayerIDVector.readFromFiler(filer);
}

/******************************************************************************/

void TradeProposeUpdateRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProposeUpdateRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* TradeProposeUpdateRqst::fulfillRequest()
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	auto_ptr<TradeProposeUpdateResp> pResponse;
	TTradeID tradeID;
	TPlayerIDVector teamPlayerIDVector;
	TParticPtr particPtr;
	TTradePtr tradePtr;
	int newRosterSize;

	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);

	// fProposeToTeamID controls a new trade vs. a clear.
	if(!fProposeToTeamID.isUndefined())
	{
		// Only new trades can be submitted. Existing trades must be cleared.
		if(!fTradeID.isUndefined())
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: fTradeID is defined");

		tradePtr = TTrade::newInstance();
		tradePtr->setTeamID(particPtr->getTeamID());
		tradePtr->setProposeToTeamID(fProposeToTeamID);

		// Sanity Check - Teams ID are different
		if(tradePtr->getTeamID() == tradePtr->getProposeToTeamID())
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: teamIDs are the same");

//			teamPtr = TTeam::createGet(tradePtr->getTeamID(), cam_MustExist);
//			proposeToTeamPtr = TTeam::createGet(tradePtr->getProposeToTeamID(), cam_MustExist);

		// each team must trade at least one player
		if((fGetPlayerIDVector.size() == 0) || (fGivePlayerIDVector.size() == 0))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: TPlayerIDVector is empty");

		// verifies no duplicates
		if (fGetPlayerIDVector.doesContainDups(true) ||
				fGivePlayerIDVector.doesContainDups(true) ||
				fReleasePlayerIDVector.doesContainDups(true))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: duplicate TPlayerID");

		// verify player IDs
		if(!store.isPlayerIDVectorValidForProfPlayers(fGetPlayerIDVector,true) ||
				!store.isPlayerIDVectorValidForProfPlayers(fGivePlayerIDVector,true) ||
				!store.isPlayerIDVectorValidForProfPlayers(fReleasePlayerIDVector,true))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: invalid TPlayerID");

		// verity players being released are not involved in trade
		if(fGivePlayerIDVector.containsAny(fReleasePlayerIDVector))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: release players involved in trade");

		// verifies that players are on the specified team
		LoadPlayerIDVectorByTeamID( tradePtr->getTeamID(), teamPlayerIDVector );
		if (!teamPlayerIDVector.contains( fGivePlayerIDVector, true ) ||
				!teamPlayerIDVector.contains( fReleasePlayerIDVector, true ))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: player not on specified team");

		// verify new roster size - fail if new size > normal or
		//	new size < normal but players are being released.
		newRosterSize = MaxPlayersPerTeam() /*teamPlayerIDVector.size()*/
			+ fGetPlayerIDVector.size()
			- fGivePlayerIDVector.size() - fReleasePlayerIDVector.size();
		if((newRosterSize > MaxPlayersPerTeam()) ||
				((newRosterSize < MaxPlayersPerTeam()) &&
				(fReleasePlayerIDVector.size() > 0)))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: invalid new roster size");

		LoadPlayerIDVectorByTeamID( tradePtr->getProposeToTeamID(), teamPlayerIDVector );
		if (!teamPlayerIDVector.contains( fGetPlayerIDVector, true ))
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: player not on specified team");

		// save the trade info
		tradePtr->setProposedDate(TDateTime::CurrentDateTime());
		tradePtr->setStatus(trs_Proposed);

		tradePtr->getPlayerIDVector() = fGetPlayerIDVector;
		tradePtr->givePlayerIDVector() = fGivePlayerIDVector;
		tradePtr->proposeRelPlayerIDVector() = fReleasePlayerIDVector;
		tradePtr->update();
		tradeID = tradePtr->getTradeID();

		sendEmailNotification(tradePtr);
	}
	else	// Clear Trade Proposal
	{
		tradePtr = TTrade::createGet(fTradeID,cam_MustExist);

		if(tradePtr->getStatus() != trs_Proposed)
			throw ASIException("TradeProposeUpdateRqst::fulfillRequest: can only clear proposed trades");
			
		tradePtr->setStatus(trs_Cleared);
		tradePtr->update();
		tradeID.clear();
	}
	
	pResponse.reset(new TradeProposeUpdateResp(tradeID));
	return (pResponse.release());
}

/******************************************************************************/

void TradeProposeUpdateRqst::sendEmailNotification(const TTradePtr tradePtr)
{
	TTeamPtr teamPtr;
	TMemberPtr proposeToMemberPtr;
	TParticPtr proposeToParticPtr;
	TTeamPtr proposeToTeamPtr;

	TSendMailPtr sendMailPtr;
	CStrVar str;

	proposeToTeamPtr = TTeam::createGet(tradePtr->getProposeToTeamID(),cam_MustExist);
	proposeToParticPtr = TPartic::createGet(proposeToTeamPtr->getParticID(),cam_MustExist);
	if(proposeToParticPtr->getGameLevel() == gml_Premium)
	{
		proposeToMemberPtr = TMember::createGet(proposeToParticPtr->getMemberID(),
			cam_MustExist);

		if(!proposeToMemberPtr->isEmailInvalid())
		{
			teamPtr = TTeam::createGet(tradePtr->getTeamID(), cam_MustExist);

			sendMailPtr = TSendMail::newInstance();
			sendMailPtr->setCreatedDateTime();
			sendMailPtr->setSender(TechSupportEmail());
			sendMailPtr->setRecipient(proposeToMemberPtr->getEmail());

			str.copyVarg("%s: Trade Proposed",AppNameAbbr().c_str());
			sendMailPtr->setSubject(str);

			str.copyVarg("The %s have proposed a trade to the %s.\r\n\r\n",
				teamPtr->getFullTeamName().c_str(),
				proposeToTeamPtr->getFullTeamName().c_str());

			str.concatVarg("They request ");
			str.concat(sendEmailNotificationPlayers(tradePtr->getPlayerIDVector()));

			str.concatVarg(" in exchange for ");
			str.concat(sendEmailNotificationPlayers(tradePtr->givePlayerIDVector()));

			str.concat(".\r\n\r\n");
			str.concat("To accept or decline this offer, proceed to the "
				"Front Office and follow the instructions.\r\n");

			str.concat("\r\n\r\n***\r\n\r\n");
			str.concat("Access your team at http://www.affinitysports.com\r\n\r\n");

			sendMailPtr->setBodyText(CharWordWrapString(str,MailerStandardBodyTextWidth()));
			sendMailPtr->update();
		}
	}
}

/******************************************************************************/

CStrVar TradeProposeUpdateRqst::sendEmailNotificationPlayers(
	const TPlayerIDVector& playerIDVector)
{
	ASFantasyObjectStore& store = ASFantasyObjectStore::getThe();
	TProfPlayerPtr profPlayerPtr;
	CStrVar str;
	unsigned int i;

	for(i = 0; i < playerIDVector.size(); i++)
	{
		profPlayerPtr = store.getProfPlayer(playerIDVector[i]);
		if(i > 0)
		{
			if(i < playerIDVector.size() - 1)
				str.concat(", ");
			else
				str.concat(" and ");
		}
		str.concat(profPlayerPtr->getName().buildFullName());
	}

	return(str);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
