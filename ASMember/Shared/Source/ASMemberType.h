/* ASMemberType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASMemberTypeH
#define ASMemberTypeH

#include <stdexcep.h>
#include <vector.h>

//BOB #include "TString.h"
#include "CommType.h"
#include "DataSetRecord.h"
#include "ObjectBuilderDataSetRecord.h "
#include "SendMail.h"
#include "ErrorLog.h"

#include "ASMemberAppOptions.h "

using namespace std;
using namespace tag;

namespace asmember
{

/******************************************************************************/

#define MinMemberIDLen			6
#define MinMemberPasswordLen	6

/******************************************************************************/

/* ID classes */
DefineTStringIDClass(TMemberID,TMemberIDBase,16);
#define DemoMemberID()			TMemberID("FANTASY")

DefineFixStrClass(TParticIDStr,16);		//only for run-time conversions.
class TParticID : public TNumericID<unsigned long>
{
public:
	TParticID(unsigned long id = 0) : TNumericID<unsigned long>(id) {}

	void setIDFromStr(const char* strID);
	TParticIDStr getIDAsStr() const;
};
DefineFixStrClass(TEncodedParticID,64);
DefineTStringIDClass(TGameID,TGameIDBase,12);

typedef TNumericID<unsigned long> TTeamID;

/* Field classes */
DefineFixStrClass(TCCardNumber,20);
DefineFixStrClass(TCCardExpDate,8);
DefineFixStrClass(TCCardNameOn,42);

typedef CStr31 TMemberSignupSource;

/******************************************************************************/

enum TCreditCardTypeEnum
{
	cct_Undefined,
	cct_Mastercard,
	cct_Visa
};
class TCreditCardType : public EnumType<TCreditCardTypeEnum,cct_Undefined,
	cct_Visa>
{
public:
	TCreditCardType(int t = cct_Undefined) :
		EnumType<TCreditCardTypeEnum,cct_Undefined,cct_Visa>(t) {}
	TCreditCardType(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TGameLevelEnum
{
	gml_Undefined,
	gml_Premium,
	gml_Standard
};
#define gml_Last gml_Standard
class TGameLevel : public EnumType<TGameLevelEnum,gml_Undefined,gml_Last>
{
public:
	TGameLevel(int t = gml_Undefined) :
		EnumType<TGameLevelEnum,gml_Undefined,gml_Last>(t) {}
	TGameLevel(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TParticStatusEnum
{
	pts_Undefined,			// not stored
	pts_NeedCCInfo,			// Signed-Up but did not enter CC. Must send via Fax/Phone.
	pts_WaitingApproval,	// Signed-Up, entered CC, but CC not approved yet.
	pts_PaymentDenied,		// CC failed approval.
	pts_PaymentApproved,	// CC approved.
	pts_Active,				// Has joined league.
	pts_Disabled,			// Disabled by Affinity.
	pts_GameOver			// Game Over, no longer has access.
};
class TParticStatus : public EnumType<TParticStatusEnum,pts_Undefined,pts_GameOver>
{
public:
	TParticStatus(int t = pts_Undefined) :
		EnumType<TParticStatusEnum,pts_Undefined,pts_GameOver>(t) {}
	TParticStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

enum TParticUpgradeStatusEnum
{
	pus_Undefined = 100,	//BOB separate all enums into numeric groups
	pus_NeedCCInfo,			// Updgrade has been requested but did not enter CC. Must send via Fax/Phone.
	pus_WaitingApproval,	// Updgrade has been requested.
	pus_PaymentDenied,		// CC failed approval.
	pus_PaymentApproved		// CC approved.
};
#define pus_Last pus_PaymentApproved
class TParticUpgradeStatus : public EnumType<TParticUpgradeStatusEnum,
	pus_Undefined,pus_Last>
{
public:
	TParticUpgradeStatus(int t = pus_Undefined) :
		EnumType<TParticUpgradeStatusEnum,pus_Undefined,pus_Last>(t) {}
	TParticUpgradeStatus(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

typedef std::vector<TParticID> TParticIDVector;

/******************************************************************************/

class TMember;	//forward reference
typedef TDataSetRecordPtr<TMember,TMemberID> TMemberPtr;

class TMember : public TQueryDataSetRecord
{
	TMemberID fMemberID;
	TPassword fPassword;

	TFullName fName;

	TAddrStreet fAddrStreet1;
	TAddrStreet fAddrStreet2;
	TAddrCity fAddrCity;
	TAddrState fAddrState;
	TAddrZip fAddrZip;
	TAddrCountry fAddrCountry;
	
	TEmail fEmail;
	TBooleanType fEmailInvalid;

	TCreditCardType fCCardType;
	TCCardNumber fCCardNumber;
	TCCardExpDate fCCardExpDate;
	TCCardNameOn fCCardNameOn;

	TMemberSignupSource fSignupSource;
	
protected:
	TMember() {}
	virtual ~TMember(void) {}	// Destroyed by self, ~RefCountObject()
	
private:
	TMember(const TMember&);						// don't allow copy constructor
	const TMember& operator=(const TMember&);		// or operator=

public:
	virtual void clear();
		
	void setMemberID(TMemberID particID)
	{
		// Can only change fMemberID for new records.
		if(!fIsNewRecord)
			throw ASIException("TMember::setMemberID: can't change");
			
		fMemberID = particID;
		setHasChanged();
	}
	TMemberID getMemberID(void) const { return(fMemberID); }

	void setPassword(const char* password) { fPassword.Copy(password);
		setHasChanged(); }
	const char* getPassword() const { return(fPassword); }
	
	const TFullName& getName() const { return(fName); }
	TFullName& getName() { setHasChanged(); return(fName); }
	void setName(const TFullName& name) { fName = name; setHasChanged(); }
	
	void setAddrStreet1(const char* addrStreet1) { fAddrStreet1.Copy(addrStreet1); setHasChanged(); }
	const char* getAddrStreet1() const { return(fAddrStreet1); }
	
	void setAddrStreet2(const char* addrStreet2) { fAddrStreet2.Copy(addrStreet2); setHasChanged(); }
	const char* getAddrStreet2() const { return(fAddrStreet2); }
	
	void setAddrCity(const char* addrCity) { fAddrCity.Copy(addrCity); setHasChanged(); }
	const char* getAddrCity() const { return(fAddrCity); }
	
	void setAddrState(const char* addrState) { fAddrState.Copy(addrState); setHasChanged(); }
	const char* getAddrState() const { return(fAddrState); }
	
	void setAddrZip(const char* addrZip) { fAddrZip.Copy(addrZip); setHasChanged(); }
	const char* getAddrZip() const { return(fAddrZip); }
	
	void setAddrCountry(const char* addrCountry) { fAddrCountry.Copy(addrCountry); setHasChanged(); }
	const char* getAddrCountry() const { return(fAddrCountry); }
	
	void setEmail(const char* email) { fEmail.Copy(email); setHasChanged(); }
	const char* getEmail() const { return(fEmail); }

	void setIsEmailInvalid(bool emailInvalid)
		{ fEmailInvalid = emailInvalid; setHasChanged(); }
	bool isEmailInvalid() const { return(fEmailInvalid); }

	void setCCardType(TCreditCardType cCardType) { fCCardType = cCardType;
		setHasChanged(); }
	TCreditCardType getCCardType() const { return(fCCardType); }
	
	void setCCardNumber(const char* cCardNumber) { fCCardNumber.Copy(cCardNumber);
		setHasChanged(); }
	const char* getCCardNumber() const { return(fCCardNumber); }
	
	void setCCardExpDate(const char* cCardExpDate) { fCCardExpDate.Copy(cCardExpDate);
		setHasChanged(); }
	const char* getCCardExpDate() const { return(fCCardExpDate); }
	
	void setCCardNameOn(const char* cCardNameOn) { fCCardNameOn.Copy(cCardNameOn);
		setHasChanged(); }
	const char* getCCardNameOn() const { return(fCCardNameOn); }
	
	void setSignupSource(const char* signupSource)
		{ fSignupSource = signupSource; setHasChanged(); }
	const char* getSignupSource() const { return(fSignupSource); }

	// Helper/Template Functions
	static TMemberPtr createGet(TMemberID particID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TMember,TMemberID,TMemberPtr>(particID,getMode)); }
	static TMemberPtr newInstance();
	TMemberID getKey() const { return(getMemberID()); }
	void setKey(TMemberID particID) { setMemberID(particID); }

protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(MemberDatabaseName()); }
	virtual const char* getTableName() { return("Member"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TMember>;
	friend class ASMemberObjectBuilder;
};

/******************************************************************************/

class TPartic;	//forward reference
typedef TDataSetRecordPtr<TPartic,TParticID> TParticPtr;

class TPartic : public TQueryDataSetRecord
{
	TParticID fParticID;
	asmember::TMemberID fMemberID;
	TPassword fPassword;

	TGameID fGameID;
	TGameLevel fGameLevel;
	double fGamePrice;
	TBooleanType fPrizeEligible;
	TDateTime fUpgradeDate;
	double fUpgradePrice;
	TParticUpgradeStatus fUpgradeStatus;

	TParticStatus fStatus;
	
	TTeamID fTeamID;
	TDateTime fSignupDate;
	TDateTime fLastTransDateTime;	// stores both Date and Time info.

	TDateTime fTrialDateTime;	// Date/time trial was started

private:
	TEncodedParticID fEncodedParticID;	// Runtime only - for speed.
										// Always use encodedParticID()
	
protected:
	TPartic() { fGamePrice = 0.0; fUpgradeDate = 0.0; }
	virtual ~TPartic(void) {}	// Destroyed by self, ~RefCountObject()
	
private:
	TPartic(const TPartic&);						// don't allow copy constructor
	const TPartic& operator=(const TPartic&);		// or operator=

public:
	virtual void clear();
		
	void setParticID(TParticID particID)
	{
		// Can only change fParticID for new records.
		if(!fIsNewRecord)
			throw ASIException("TPartic::setParticID: can't change");
			
		fParticID = particID;
		fEncodedParticID.Clear();
		setHasChanged();
	}
	TParticID getParticID(void) const { return(fParticID); }

	void setMemberID(asmember::TMemberID memberID)
	{
		// Can only change fMemberID for new records.
		if(!fIsNewRecord)
			throw ASIException("TPartic::setMemberID: can't change");
			
		fMemberID = memberID;
		setHasChanged();
	}
	asmember::TMemberID getMemberID(void) const { return(fMemberID); }

	void setPassword(const char* password) { fPassword.Copy(password); 
		fEncodedParticID.Clear(); setHasChanged(); }
	const char* getPassword() const { return(fPassword); }

	void setGameID(const char* gameID) { fGameID.Copy(gameID); setHasChanged(); }
	TGameID getGameID() const { return(fGameID); }
	
	void setGameLevel(TGameLevel gameLevel)
		{ fGameLevel = gameLevel; setHasChanged(); }
	TGameLevel getGameLevel(void) const { return (fGameLevel); }

	void setGamePrice(double gamePrice) { fGamePrice = gamePrice; setHasChanged(); }
	double getGamePrice(void) const { return(fGamePrice); }
	
	void setPrizeEligible(bool prizeEligible)
		{ fPrizeEligible = prizeEligible; setHasChanged(); }
	bool getPrizeEligible() const { return(fPrizeEligible); }

	void setUpgradeDate(TDateTime upgradeDate)
		{ fUpgradeDate = upgradeDate; setHasChanged(); }
	TDateTime getUpgradeDate(void) const { return(fUpgradeDate); }

	void setUpgradePrice(double upgradePrice)
		{ fUpgradePrice = upgradePrice; setHasChanged(); }
	double getUpgradePrice(void) const { return(fUpgradePrice); }

	void setUpgradeStatus(TParticUpgradeStatus upgradeStatus)
		{ fUpgradeStatus = upgradeStatus; setHasChanged(); }
	TParticUpgradeStatus getUpgradeStatus(void) const { return (fUpgradeStatus); }

	void setStatus(TParticStatus status)
		{ fStatus = status; setHasChanged(); }
	TParticStatus getStatus(void) const { return (fStatus); }
	
	void setTeamID(TTeamID teamID)
		{ fTeamID = teamID; setHasChanged(); }
	TTeamID getTeamID(void) const { return(fTeamID); }
	
	void setSignupDate(TDateTime signupDate)
		{ fSignupDate = signupDate; setHasChanged(); }
	TDateTime getSignupDate(void) const { return(fSignupDate); }
	
	void setLastTransDateTime(TDateTime lastTransDateTime)
		{ fLastTransDateTime = lastTransDateTime; setHasChanged(); }
	TDateTime getLastTransDateTime(void) const { return(fLastTransDateTime); }

	void setTrialDateTime(TDateTime trialDateTime)
		{ fTrialDateTime = trialDateTime; setHasChanged(); }
	TDateTime getTrialDateTime(void) const { return(fTrialDateTime); }

	
	// Helper/Template Functions
	static TParticPtr createGet(TParticID particID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TPartic,TParticID,TParticPtr>(particID,getMode)); }
	static TParticPtr createGetByEncoded(TEncodedParticID encodedParticID,
		CommonAccessMode getMode);
	static TParticPtr newInstance();
	TParticID getKey() const { return(getParticID()); }
	void setKey(TParticID particID) { setParticID(particID); }

	TEncodedParticID encodeParticID();
	static void decodeParticID(const TEncodedParticID& encodedParticID,
		TParticID& particID,TPassword& password);
protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(MemberDatabaseName()); }
	virtual const char* getTableName() { return("Partic"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual CStrVar getWhereStr(void);

	friend class RefCountPtr<TPartic>;
	friend class ASMemberObjectBuilder;
};

/******************************************************************************/

class TParticVector : public std::vector<TParticPtr>
{
public:
	void sortByID() { std::sort(begin(),end(), sortIDCompare() ); }
		
protected:
	struct sortIDCompare
	{
		bool operator() (const TParticPtr& x, const TParticPtr& y) const
		{
			return(x->getParticID() < y->getParticID());
		}
	};
};

/******************************************************************************/

class TPayHistoryID
{
public:
	asmember::TMemberID fMemberID;
	TDateTime fTransDateTime;

	TPayHistoryID() { clear(); }
	TPayHistoryID(asmember::TMemberID memberID,TDateTime transDateTime)
		{ clear(); fMemberID = memberID; fTransDateTime = transDateTime; }
	
	void clear() { fMemberID.Clear(); fTransDateTime = TDateTime(); };
};

class TPayHistory;	//forward reference
typedef TDataSetRecordPtr<TPayHistory,TPayHistoryID> TPayHistoryPtr;

class TPayHistory : public TTableDataSetRecord
{
protected:
	asmember::TMemberID fMemberID;
	TDateTime fTransDateTime;

	TParticID fParticID;
	TGameID fGameID;

	/* Credit Card Info */
	TCreditCardType fCCardType;
	TCCardNumber fCCardNumber;
	TCCardExpDate fCCardExpDate;
	TCCardNameOn fCCardNameOn;

	/* Request Info */
	char fSaleCommand[4];
	char fClerk[16];
	char fComment[26];
	double fAmount;

	/* Response Info */
	bool fApproved;
	CStrVar fResponse;
	
protected:
	TPayHistory() { memset(fSaleCommand,0,sizeof(fSaleCommand));
		memset(fClerk,0,sizeof(fClerk)); memset(fComment,0,sizeof(fComment));
		fAmount = 0.0; }
	virtual ~TPayHistory(void) {}	// Destroyed by self, ~RefCountObject()
	
private:
	TPayHistory(const TPayHistory&);						// don't allow copy constructor
	const TPayHistory& operator=(const TPayHistory&);		// or operator=

public:
	virtual void clear();

	void setMemberID(asmember::TMemberID memberID)
	{
		// Can only change fMemberID for new records.
		if(!fIsNewRecord)
			throw ASIException("TPayHistory::setMemberID: can't change");
			
		fMemberID = memberID;
		setHasChanged();
	}
	asmember::TMemberID getMemberID(void) const { return(fMemberID); }

	void setTransDateTime(TDateTime transDateTime)
	{
		// Can only change fTransDateTime for new records.
		if(!fIsNewRecord)
			throw ASIException("TPayHistory::setTransDateTime: can't change");
			
		fTransDateTime = transDateTime;
		setHasChanged();
	}
	TDateTime getTransDateTime(void) const { return(fTransDateTime); }
		
	void setParticID(TParticID particID)
		{ fParticID = particID; setHasChanged(); }
	TParticID getParticID(void) const { return(fParticID); }

	void setGameID(const char* gameID) { fGameID.Copy(gameID); setHasChanged(); }
	TGameID getGameID() const { return(fGameID); }

	
	/* Credit Card Info */
	
	void setCCardType(TCreditCardType cCardType) { fCCardType = cCardType;
		setHasChanged(); }
	TCreditCardType getCCardType() const { return(fCCardType); }
	
	void setCCardNumber(const char* cCardNumber) { fCCardNumber.Copy(cCardNumber);
		setHasChanged(); }
	const char* getCCardNumber() const { return(fCCardNumber); }
	
	void setCCardExpDate(const char* cCardExpDate) { fCCardExpDate.Copy(cCardExpDate);
		setHasChanged(); }
	const char* getCCardExpDate() const { return(fCCardExpDate); }
	
	void setCCardNameOn(const char* cCardNameOn) { fCCardNameOn.Copy(cCardNameOn);
		setHasChanged(); }
	const char* getCCardNameOn() const { return(fCCardNameOn); }

	/* Request Info */
	void setSaleCommand( const char * saleCommand )
		{ tStrCpy(fSaleCommand,sizeof(fSaleCommand),saleCommand); setHasChanged(); }
	const char* getSaleCommand() const { return(fSaleCommand); }
	
	void setClerk( const char * clerk )
		{ tStrCpy(fClerk,sizeof(fClerk),clerk); setHasChanged(); }
	const char* getClerk() const { return(fClerk); }
	
	void setComment( const char * comment )
		{ tStrCpy(fComment,sizeof(fComment),comment); setHasChanged(); }
	const char* getComment() const { return(fComment); }
	
	void setAmount( double amount ) { fAmount = amount; setHasChanged(); }
	double getAmount() const { return(fAmount); }
	
	/* Response Info */
	void setApproved(bool approved) { fApproved = approved; setHasChanged(); }
	bool getApproved() const { return(fApproved); }
	
	void setResponse( const char * response )
		{ fResponse.copy(response); setHasChanged(); }
	const char* getResponse() const { return(fResponse); }
	
	
	TPayHistoryID getPayHistoryID(void) const
		{ return(TPayHistoryID(fMemberID,fTransDateTime)); }
	
	// Helper/Template Functions
	static TPayHistoryPtr createGet(TPayHistoryID payHistoryID,CommonAccessMode getMode)
		{ return(CreateGetRecord<TPayHistory,TPayHistoryID,TPayHistoryPtr>(payHistoryID,getMode)); }
	static TPayHistoryPtr newInstance();
	TPayHistoryID getKey() const { return(getPayHistoryID()); }
	void setKey(TPayHistoryID payHistoryID) { setMemberID(payHistoryID.fMemberID);
		setTransDateTime(payHistoryID.fTransDateTime); }

protected:
	/* DataSetRecord methods */
	virtual const char* getDatabaseName() { return(MemberDatabaseName()); }
	virtual const char* getTableName() { return("PayHistory"); }
	
	virtual void readFromDataSet(TDataSet& dataSet);
	virtual void writeToDataSet(TDataSet& dataSet);
	virtual void validateForUpdate();
	virtual bool findInTable(TTable& table);

	friend class RefCountPtr<TPayHistory>;
	friend class ASMemberObjectBuilder;
};

/******************************************************************************/

typedef std::vector<TPayHistoryPtr> TPayHistoryVector;

/******************************************************************************/
/******************************************************************************/

class TASMemberSendMail : public TSendMail
{
public:
	virtual const char* getDatabaseName() { return(MemberMiscDatabaseName()); }
};

/******************************************************************************/
/******************************************************************************/

class TASMemberErrorLog : public TErrorLog
{
public:
	virtual const char* getDatabaseName() { return(MemberMiscDatabaseName()); }
};

/******************************************************************************/

}; //namespace tag

#endif //ASMemberTypeH
/******************************************************************************/
/******************************************************************************/

