/* ASFantasySignupLeagueListRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CommType.h"
#include "CommDB.h"

#include "ASFantasyDB.h"
#include "ASFantasySignupLeagueListRqst.h"

namespace asfantasy
{

/******************************************************************************/

class SignupLeagueListElement : public TStreamable
{
private:
	TLeagueID fLeagueID;
	TLeagueName fLeagueName;
	TManagerName fCommisName;
	
public:
	SignupLeagueListElement() {}
	SignupLeagueListElement(TLeagueID leagueID,TLeagueName leagueName,
		TManagerName commisName) : fLeagueID(leagueID), fLeagueName(leagueName),
		fCommisName(commisName) {}

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/

typedef std::vector<SignupLeagueListElement> SignupLeagueList;

class SignupLeagueListResp : public TStreamable
{
private:
	SignupLeagueList fLeagueList;
	
public:
	SignupLeagueList& getSignupLeagueList() { return(fLeagueList); }
	
	virtual const char* className() const { return("SignupLeagueListResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
};

/******************************************************************************/
/******************************************************************************/

void SignupLeagueListElement::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("SignupLeagueListElement::readFromFiler: not supported");
}

/******************************************************************************/

void SignupLeagueListElement::writeToFiler(TDataFiler& filer)
{
	filer.writeLong(fLeagueID.getID());
	filer.writeString(fLeagueName.c_str());
	filer.writeString(fCommisName.c_str());
}

/******************************************************************************/
/******************************************************************************/

void SignupLeagueListResp::readFromFiler(TDataFiler& /*filer*/)
{
	throw ASIException("SignupLeagueListResp::readFromFiler: not supported");
}

/******************************************************************************/

void SignupLeagueListResp::writeToFiler(TDataFiler& filer)
{
	int i,numItems = fLeagueList.size();

	filer.writeShort(numItems);
	for(i = 0; i < numItems; i++)
		fLeagueList[i].writeToFiler(filer);
}

/******************************************************************************/
/******************************************************************************/

void SignupLeagueListRqst::readFromFiler(TDataFiler& filer)
{
	fPartialLeagueName.Copy(filer.readString().c_str());
}

/******************************************************************************/

void SignupLeagueListRqst::writeToFiler(TDataFiler& filer)
{
	throw ASIException("SignupLeagueListRqst::writeToFiler: not supported");
} 

/******************************************************************************/

TStreamable* SignupLeagueListRqst::fulfillRequest()
{
	auto_ptr<SignupLeagueListResp> pResponse(new SignupLeagueListResp());
	SignupLeagueList& leagueList = pResponse->getSignupLeagueList();

	TLeagueVector leagueVector;
	TLeagueVector::iterator iter;
	TLeaguePtr leaguePtr;

	LoadLeagueVectorByEnrollPrivatePartialName(fPartialLeagueName,leagueVector);
	leagueVector.sortByName();

	for(iter = leagueVector.begin(); iter != leagueVector.end(); ++iter)
	{
		leaguePtr = *iter;
		leagueList.push_back(SignupLeagueListElement(leaguePtr->getLeagueID(),
			leaguePtr->getName(),""));
	}

	return(pResponse.release());
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
