/* ASFantasyNewSignupRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyNewSignupRqstH
#define ASFantasyNewSignupRqstH

#include "CommType.h"
#include "Requestable.h"
#include "RequesterError.h"
#include "ASMemberType.h"
#include "ASFantasyType.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyNewSignupResp : public TStreamable
{
private:
	bool fSuccess;
	asmember::TMemberID fMemberID;
	TEncodedParticID fEncodedParticID;
	TRegionName fRegionName;
	TTeamName fTeamName;
	TManagerName fManagerName;
	
	AnsiString fReasonFailed;

public:
	ASFantasyNewSignupResp(bool success, asmember::TMemberID memberID,
		const TEncodedParticID& encodedParticID, const char* regionName,
		const char* teamName, const char* managerName, const char* reasonFailed) :
		fSuccess(success), fMemberID(memberID), fEncodedParticID(encodedParticID),
		fRegionName(regionName), fTeamName(teamName), fManagerName(managerName),
		fReasonFailed(reasonFailed) {}
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	bool getSuccess() const { return(fSuccess); }
	TMemberID getMemberID() const { return(fMemberID); }
	TEncodedParticID getEncodedParticID() const { return(fEncodedParticID); }
	const char* getRegionName() const { return(fRegionName); }
	const char* getTeamName() const { return(fTeamName); }
	const char* getManagerName() const { return(fManagerName); }
	const char* getReasonFailed() const { return(fReasonFailed.c_str()); }
};

/******************************************************************************/

class ASFantasyNewSignupRqst : public TRequestable
{
protected:
	/* Game Info */
	bool fPrizeEligible;
	TGameLevel fGameLevel;
	double fGamePrice;
	
	/* User Info */
	asmember::TMemberID fMemberID;

	/* Personal Info */
	TFullName fName;
	
	TAddrStreet fAddrStreet1;
	TAddrStreet fAddrStreet2;
	TAddrCity fAddrCity;
	TAddrState fAddrState;
	TAddrZip fAddrZip;
	TAddrCountry fAddrCountry;
	
	TEmail fEmail;

	/* Team Info */
	TRegionName fRegionName;
	TTeamName fTeamName;
	TManagerName fManagerName;

	/* Credit Card Info */
	bool fCCardViaFaxPhone;
	CStr31 fCCardType;
	TCCardNumber fCCardNumber;
	TCCardExpDate fCCardExpDate;
	TCCardNameOn fCCardNameOn;
	
public:
	ASFantasyNewSignupRqst() { fPrizeEligible = false; fGamePrice = 0.0;
		fCCardViaFaxPhone = false; }

	void setPrizeEligible(const bool prizeEligible) { fPrizeEligible = prizeEligible; }
	void setGameLevel(const TGameLevel gameLevel) { fGameLevel = gameLevel; }
	void setGamePrice(const double gamePrice) { fGamePrice = gamePrice; }

	void setMemberID(asmember::TMemberID memberID) { fMemberID = memberID; }

	TFullName& getName() { return(fName); }

	void setAddrStreet1(const char* addrStreet1) { fAddrStreet1.Copy(addrStreet1); }
	void setAddrStreet2(const char* addrStreet2) { fAddrStreet2.Copy(addrStreet2); }
	void setAddrCity(const char* addrCity) { fAddrCity.Copy(addrCity); }
	void setAddrState(const char* addrState) { fAddrState.Copy(addrState); }
	void setAddrZip(const char* addrZip) { fAddrZip.Copy(addrZip); }
	void setAddrCountry(const char* addrCountry) { fAddrCountry.Copy(addrCountry); }
	
	void setEmail(const char* email) { fEmail = email; }

	void setRegionName(const char* regionName) { fRegionName = regionName; }
	void setTeamName(const char* teamName) { fTeamName = teamName; }
	void setManagerName(const char* managerName) { fManagerName = managerName; }
	
	void setCCardViaFaxPhone(bool cCardViaFaxPhone) { fCCardViaFaxPhone = cCardViaFaxPhone; }
	void setCCardType(const char* cCardType) { fCCardType = cCardType; }
	void setCCardNumber(const char* cCardNumber) { fCCardNumber = cCardNumber; }
	void setCCardExpDate(const char* cCardExpDate) { fCCardExpDate = cCardExpDate; }
	void setCCardNameOn(const char* cCardNameOn) { fCCardNameOn = cCardNameOn; }
	
protected:
	virtual void validateRequestAddress();
	virtual void validateRequestTeam();
	virtual void validateRequestCreditCard();
	virtual void validateRequest();

	void updateMember(TMemberPtr memberPtr);
	void createNewPartic(const TMemberPtr& memberPtr,TParticPtr& particPtr,
		TTeamPtr& teamPtr,bool needCreditCardInfo);
	void setupDraftRanking(const TTeamPtr& teamPtr);
	void sendWelcomeEmail(const TMemberPtr memberPtr,const TTeamPtr teamPtr,
		bool isNewMember);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyNewSignupRqstH
/******************************************************************************/
/******************************************************************************/ 
