/* ASFantasyTradeProposeTeamRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyMiscRqst.h"
#include "ASFantasyTradeProposeTeamRqst.h"

namespace asfantasy
{

/******************************************************************************/

class TradeProposeTeamResp : public TStreamable
{
private:
	PlayerInfoVector fPlayerInfoVector;

public:
	TradeProposeTeamResp(PlayerInfoVector& playerInfoVector);

	virtual const char* className() const { return("TradeProposeTeamResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

TradeProposeTeamResp::TradeProposeTeamResp(PlayerInfoVector& playerInfoVector)
{
	fPlayerInfoVector = playerInfoVector;
}

/******************************************************************************/

void TradeProposeTeamResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProposeTeamResp::readFromFiler: not supported");
}

/******************************************************************************/

void TradeProposeTeamResp::writeToFiler(TDataFiler& filer)
{
	fPlayerInfoVector.writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

void TradeProposeTeamRqst::readFromFiler(TDataFiler& filer)
{
	fEncodedParticID = filer.readString().c_str();
	fProposeToTeamID = filer.readLong();
}

/******************************************************************************/

void TradeProposeTeamRqst::writeToFiler(TDataFiler& /*filer*/)
{
	throw ASIException("TradeProposeTeamRqst::writeToFiler: not supported");
}

/******************************************************************************/

TStreamable* TradeProposeTeamRqst::fulfillRequest()
{
	auto_ptr<TradeProposeTeamResp> pResponse;
	PlayerInfoVector playerInfoVector;
	TParticPtr particPtr;
	
	particPtr = TPartic::createGetByEncoded(fEncodedParticID,cam_MustExist);

	FillPlayerInfoExtVector(fProposeToTeamID,playerInfoVector);

	pResponse.reset(new TradeProposeTeamResp(playerInfoVector));
	return (pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
