/* ASFantasyLeagueSignupRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyLeagueSignupRqstH
#define ASFantasyLeagueSignupRqstH

#include "Requestable.h"
#include "RequesterError.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class LeagueSignupResp : public TStreamable
{
private:
	bool fSuccess;
	TLeagueName fLeagueName;
	CStrVar fReasonFailed;

public:
	LeagueSignupResp(bool success, const char* leagueName,
		const char* reasonFailed) : fSuccess(success), fLeagueName(leagueName),
		fReasonFailed(reasonFailed) {}
	
	virtual const char* className() const { return("LeagueSignupResp"); }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	bool getSuccess() const { return(fSuccess); }
	const char* getLeagueName() const { return(fLeagueName); }
	const char* getReasonFailed() const { return(fReasonFailed); }
};

/******************************************************************************/

/* LeagueSignup Type/Enum - Never use LeagueSignupEnum always use 
	LeagueSignupType*/
enum LeagueSignupEnum
{
	lst_JoinOpenPublic = 0,
	lst_CreatePrivate,
	lst_JoinPrivate
};
class LeagueSignupType : public EnumType<LeagueSignupEnum,lst_JoinOpenPublic,
	lst_JoinPrivate>
{
public:
	LeagueSignupType(int t = lst_JoinOpenPublic) :
		EnumType<LeagueSignupEnum,lst_JoinOpenPublic,lst_JoinPrivate>(t) {}
};

/******************************************************************************/

class LeagueSignupRqst : public TRequestable
{
private:
	LeagueSignupType fLst;

	/* Partic Info */
	TEncodedParticID fEncodedParticID;
	
	/* League Info */
	TLeagueID fLeagueID;
	TPassword fLeaguePassword;
	
public:
	LeagueSignupRqst() {}

	void setLeagueSignupType(const LeagueSignupType lst) { fLst = lst; }

	void setEncodedParticID(const TEncodedParticID encodedParticID)
		{ fEncodedParticID = encodedParticID; }

	void setLeagueID(const TLeagueID leagueID) { fLeagueID = leagueID; }
	void setLeaguePassword(const char* leaguePassword)
		{ fLeaguePassword = leaguePassword; }

	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual TStreamable* fulfillRequest();

protected:
	void validateRequest(TParticPtr& particPtr,TTeamPtr& teamPtr);
	
	TLeaguePtr createNewLeague(const TPassword& password = TPassword(),
		bool reserved = false);
	TLeagueName selectLeagueName();
	TLeaguePtr getOpenPublicLeague(const TParticPtr teamParticPtr);
	void addTeamToLeague(TTeamPtr teamPtr,TLeaguePtr leaguePtr);
	
	void joinPublicLeague(const TParticPtr particPtr,TTeamPtr teamPtr,
		TLeaguePtr& leaguePtr);
	void createPrivateLeague(TTeamPtr teamPtr,const TPassword& leaguePassword,
		TLeaguePtr& leaguePtr);
	void joinPrivateLeague(TTeamPtr teamPtr,TLeagueID leagueID,
		const TPassword& leaguePassword,TLeaguePtr& leaguePtr);
};

/******************************************************************************/

}; //namespace asfantasy

#endif
/******************************************************************************/
/******************************************************************************/
