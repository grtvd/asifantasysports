/* ASMemberType.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "PasswordEncode.h"
#include "ASMemberType.h"
#include "ASMemberObjectBuilder.h"

using namespace asmember;

/******************************************************************************/
/******************************************************************************/

void TParticID::setIDFromStr(const char* strID)
{
	long num;

	if(StringToNumeric(strID,&num))
		fID = num;
	else
		throw ASIException("TParticID::setIDFromStr: invalid strID(%s)",strID);
}

/******************************************************************************/

TParticIDStr TParticID::getIDAsStr() const
{
	TParticIDStr strID;
	strID.CopyVarg("%09lu",fID);
	return(strID);
}

/******************************************************************************/
/******************************************************************************/

TCreditCardType::TCreditCardType(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "X")
		fT = cct_Undefined;
	else if(value == "MC")
		fT = cct_Mastercard;
	else if(value == "VS")
		fT = cct_Visa;
	else
		throw ASIException("TCreditCardType::TCreditCardType: invalid str");
}

/******************************************************************************/

const char* TCreditCardType::c_str() const
{
	switch(fT)
	{
		case cct_Undefined:
			return("X");
		case cct_Mastercard:
			return("MC");
		case cct_Visa:
			return("VS");
		default:
			break;
	};

	throw ASIException("TCreditCardType::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TGameLevel::TGameLevel(const char* str)
{
	CStr31 value(str);

	value.ToUpper();
	
	if(value == "P")
		fT = gml_Premium;
	else if(value == "S")
		fT = gml_Standard;
	else
		throw ASIException("TGameLevel::TGameLevel: invalid str");
}

/******************************************************************************/

const char* TGameLevel::c_str() const
{
	switch(fT)
	{
		case gml_Premium:
			return("P");
		case gml_Standard:
			return("S");
		default:
			break;
	};

	throw ASIException("TGameLevel::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TParticStatus::TParticStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "NI")
		fT = pts_NeedCCInfo;
	else if(value == "WA")
		fT = pts_WaitingApproval;
	else if(value == "DN")
		fT = pts_PaymentDenied;
	else if(value == "AP")
		fT = pts_PaymentApproved;
	else if(value == "AC")
		fT = pts_Active;
	else if(value == "DS")
		fT = pts_Disabled;
	else if(value == "GO")
		fT = pts_GameOver;
	else
		throw ASIException("TParticStatus::TParticStatus: invalid str");
}

/******************************************************************************/

const char* TParticStatus::c_str() const
{
	switch(fT)
	{
		case pts_NeedCCInfo:
			return("NI");
		case pts_WaitingApproval:
			return("WA");
		case pts_PaymentDenied:
			return("DN");
		case pts_PaymentApproved:
			return("AP");
		case pts_Active:
			return("AC");
		case pts_Disabled:
			return("DS");
		case pts_GameOver:
			return("GO");
		default:
			break;
	};

	throw ASIException("TParticStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TParticUpgradeStatus::TParticUpgradeStatus(const char* str)
{
	CStr31 value(str);

	value.ToUpper();

	if(value == "X")
		fT = pus_Undefined;
	else if(value == "N")
		fT = pus_NeedCCInfo;
	else if(value == "W")
		fT = pus_WaitingApproval;
	else if(value == "D")
		fT = pus_PaymentDenied;
	else if(value == "A")
		fT = pus_PaymentApproved;
	else
		throw ASIException("TParticUpgradeStatus::TParticUpgradeStatus: invalid str");
}

/******************************************************************************/

const char* TParticUpgradeStatus::c_str() const
{
	switch(fT)
	{
		case pus_Undefined:
			return("X");
		case pus_NeedCCInfo:
			return("N");
		case pus_WaitingApproval:
			return("W");
		case pus_PaymentDenied:
			return("D");
		case pus_PaymentApproved:
			return("A");
		default:
			break;
	};

	throw ASIException("TParticUpgradeStatus::c_str: invalid fT");
}

/******************************************************************************/
/******************************************************************************/

TMemberPtr TMember::newInstance()
{
	TMemberPtr memberPtr = ASMemberObjectBuilder::getThe().newMember();
	memberPtr->clear();
	return(memberPtr);
}

/******************************************************************************/

void TMember::clear()
{
	TQueryDataSetRecord::clear();
	
	fMemberID.Clear();
	fPassword.Clear();

	fName.clear();
	
	fAddrStreet1.Clear();
	fAddrStreet2.Clear();
	fAddrCity.Clear();
	fAddrState.Clear();
	fAddrZip.Clear();
	fAddrCountry.Clear();
	
	fEmail.Clear();
	fEmailInvalid = false;

	fCCardType.clear();
	fCCardNumber.Clear();
	fCCardExpDate.Clear();
	fCCardNameOn.Clear();

	fSignupSource.Clear();
}

/******************************************************************************/

void TMember::readFromDataSet(TDataSet& dataSet)
{
	fMemberID.setID(dataSet.FieldByName("MemberID")->AsString.c_str());
	fPassword = dataSet.FieldByName("Passwd")->AsString.c_str();

	fName.fFirstName = dataSet.FieldByName("FirstName")->AsString.c_str();
	fName.fLastName = dataSet.FieldByName("LastName")->AsString.c_str();
	
	fAddrStreet1 = dataSet.FieldByName("AddrStreet1")->AsString.c_str();
	fAddrStreet2 = dataSet.FieldByName("AddrStreet2")->AsString.c_str();
	fAddrCity = dataSet.FieldByName("AddrCity")->AsString.c_str();
	fAddrState = dataSet.FieldByName("AddrState")->AsString.c_str();
	fAddrZip = dataSet.FieldByName("AddrZip")->AsString.c_str();
	fAddrCountry = dataSet.FieldByName("AddrCountry")->AsString.c_str();
	
	fEmail = dataSet.FieldByName("Email")->AsString.c_str();
	fEmailInvalid = TBooleanType(dataSet.FieldByName("EmailInvalid")->AsString.c_str());

	fCCardType = dataSet.FieldByName("CCardType")->AsString.c_str();
	fCCardNumber = dataSet.FieldByName("CCardNumber")->AsString.c_str();
	fCCardExpDate = dataSet.FieldByName("CCardExpDate")->AsString.c_str();
	fCCardNameOn = dataSet.FieldByName("CCardNameOn")->AsString.c_str();

	fSignupSource = dataSet.FieldByName("SignupSource")->AsString.c_str();
}

/******************************************************************************/

void TMember::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("MemberID")->AsString = fMemberID.getID();
	dataSet.FieldByName("Passwd")->AsString = fPassword.c_str();
	
	dataSet.FieldByName("FirstName")->AsString = fName.fFirstName.c_str();
	dataSet.FieldByName("LastName")->AsString = fName.fLastName.c_str();
	
	dataSet.FieldByName("AddrStreet1")->AsString = fAddrStreet1.c_str();
	dataSet.FieldByName("AddrStreet2")->AsString = fAddrStreet2.c_str();
	dataSet.FieldByName("AddrCity")->AsString = fAddrCity.c_str();
	dataSet.FieldByName("AddrState")->AsString = fAddrState.c_str();
	dataSet.FieldByName("AddrZip")->AsString = fAddrZip.c_str();
	dataSet.FieldByName("AddrCountry")->AsString = fAddrCountry.c_str();
	
	dataSet.FieldByName("Email")->AsString = fEmail.c_str();
	dataSet.FieldByName("EmailInvalid")->AsString = fEmailInvalid.c_str();
	
	dataSet.FieldByName("CCardType")->AsString = fCCardType.c_str();
	dataSet.FieldByName("CCardNumber")->AsString = fCCardNumber.c_str();
	dataSet.FieldByName("CCardExpDate")->AsString = fCCardExpDate.c_str();
	dataSet.FieldByName("CCardNameOn")->AsString = fCCardNameOn.c_str();

	dataSet.FieldByName("SignupSource")->AsString = fSignupSource.c_str();
}

/******************************************************************************/

void TMember::validateForUpdate()
{
	if(fMemberID.isUndefined())
		throw ASIException("TMember::validateForUpdate: fMemberID.isUndefined()");
	if(fPassword.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fPassword.Len() == 0");
	
	if(fName.fFirstName.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fName.fFirstName.Len() == 0");
	if(fName.fLastName.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fName.fLastName.Len() == 0");
	
	if(fAddrStreet1.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fAddrStreet1.Len() == 0");
	if(fAddrCity.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fAddrCity.Len() == 0");
	if(fAddrState.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fAddrState.Len() == 0");
	if(fAddrZip.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fAddrZip.Len() == 0");
	if(fAddrCountry.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fAddrCountry.Len() == 0");
		
	if(fEmail.Len() == 0)
		throw ASIException("TMember::validateForUpdate: fEmail.Len() == 0");

	//CCardType
	//if(fCCardNumber.Len() == 0)
	//	throw ASIException("TMember::validateForUpdate: fCCardNumber.Len() == 0");
	//if(fCCardExpDate.Len() == 0)
	//	throw ASIException("TMember::validateForUpdate: fCCardExpDate.Len() == 0");
	//if(fCCardNameOn.Len() == 0)
	//	throw ASIException("TMember::validateForUpdate: fCCardNameOn.Len() == 0");
}

/******************************************************************************/

CStrVar TMember::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(MemberID = \"%s\")",fMemberID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

/* Fetches TPartic based on TEncodedParticID.  Will return isNull() if getMode
	is cam_MayNotExist and either TParticID or TPassword is incorrect. Will
	throw exception if getMode is cam_MustExist and either TParticID or
	TPassword is incorrect. */
	
TParticPtr TPartic::createGetByEncoded(TEncodedParticID encodedParticID,
	CommonAccessMode getMode)
{
	TParticPtr particPtr;
	TParticID particID;
	TPassword password;

	decodeParticID(encodedParticID, particID, password);
	particPtr = createGet(particID,getMode);
	if(!particPtr.isNull())
	{
		if(particPtr->getPassword() != password)
		{
			if(getMode == cam_MustExist)
				throw ASIException("TPartic::createGetByEncoded: invalid encodedParticID");

			particPtr = NULL;
		}
	}

	return(particPtr);
}

/******************************************************************************/

TParticPtr TPartic::newInstance()
{
	TParticPtr particPtr = ASMemberObjectBuilder::getThe().newPartic();
	particPtr->clear();
	return(particPtr);
}

/******************************************************************************/

void TPartic::clear()
{
	TQueryDataSetRecord::clear();
	
	fParticID.clear();
	fMemberID.Clear();
	fPassword.Clear();
	
	fGameID.Copy(CurrentGameID());
	fGameLevel.clear();
	fGamePrice = 0.0;
	fPrizeEligible = false;
	fUpgradeDate = TDateTime();
	fUpgradePrice = 0.0;
	fUpgradeStatus = TParticUpgradeStatus();

	fStatus = TParticStatus();
	
	fTeamID.clear();
	fSignupDate = TDateTime();
	fLastTransDateTime = TDateTime();

	fTrialDateTime = TDateTime();
}

/******************************************************************************/

TEncodedParticID TPartic::encodeParticID()
{
	if(fEncodedParticID.Len() == 0)
	{
		TParticIDStr particIDStr = fParticID.getIDAsStr();
		
		EncodeUserIDPasswordType<TEncodedParticID>(particIDStr.c_str(),
			fPassword.c_str(),fEncodedParticID);
	}
	return(fEncodedParticID);
}

/******************************************************************************/

void TPartic::decodeParticID(const TEncodedParticID& encodedParticID,
	TParticID& particID,TPassword& password)
{
	TParticIDStr particIDStr;
	
	DecodeUserIDPasswordType<TParticIDStr,TPassword>(encodedParticID.c_str(),
		particIDStr,password);

	particID.setIDFromStr(particIDStr);
}

/******************************************************************************/

void TPartic::readFromDataSet(TDataSet& dataSet)
{
	fParticID = dataSet.FieldByName("ParticID")->AsInteger;
	fMemberID = dataSet.FieldByName("MemberID")->AsString.c_str();
	fPassword = dataSet.FieldByName("Passwd")->AsString.c_str();

	fGameID = dataSet.FieldByName("GameID")->AsString.c_str();
	fGameLevel = dataSet.FieldByName("GameLevel")->AsString.c_str();
	fGamePrice = dataSet.FieldByName("GamePrice")->AsFloat;
	fPrizeEligible = TBooleanType(dataSet.FieldByName("PrizeEligible")->AsString.c_str());
	fUpgradeDate = DataSetReadDateTime(dataSet,"UpgradeDate");
	fUpgradePrice = dataSet.FieldByName("UpgradePrice")->AsFloat;
	fUpgradeStatus = dataSet.FieldByName("UpgradeStatus")->AsString.c_str();

	fStatus = dataSet.FieldByName("Status")->AsString.c_str();
	
	fTeamID = dataSet.FieldByName("TeamID")->AsInteger;
	fSignupDate = DataSetReadDateTime(dataSet,"SignupDate");
	fLastTransDateTime = DataSetReadDateTime(dataSet,"LastTransDateTime");

	fTrialDateTime = DataSetReadDateTime(dataSet,"TrialDateTime");
}

/******************************************************************************/

void TPartic::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("ParticID")->AsInteger = fParticID.getID();
	dataSet.FieldByName("MemberID")->AsString = fMemberID.c_str();
	dataSet.FieldByName("Passwd")->AsString = fPassword.c_str();
	
	dataSet.FieldByName("GameID")->AsString = fGameID.c_str();
	dataSet.FieldByName("GameLevel")->AsString = fGameLevel.c_str();
	dataSet.FieldByName("GamePrice")->AsFloat = fGamePrice;
	dataSet.FieldByName("PrizeEligible")->AsString = fPrizeEligible.c_str();
	DataSetWriteDateTime(dataSet,"UpgradeDate",fUpgradeDate);
	dataSet.FieldByName("UpgradePrice")->AsFloat = fUpgradePrice;
	dataSet.FieldByName("UpgradeStatus")->AsString = fUpgradeStatus.c_str();

	dataSet.FieldByName("Status")->AsString = fStatus.c_str();

	dataSet.FieldByName("TeamID")->AsInteger = fTeamID.getID();
	DataSetWriteDateTime(dataSet,"SignupDate",fSignupDate);
	DataSetWriteDateTime(dataSet,"LastTransDateTime",fLastTransDateTime);

	DataSetWriteDateTime(dataSet,"TrialDateTime",fTrialDateTime);
}

/******************************************************************************/

void TPartic::validateForUpdate()
{
	if(fIsNewRecord)
		fParticID = GetNextNum(getDatabaseName(),getTableName());

	if(fParticID.isUndefined())
		throw ASIException("TPartic::validateForUpdate: fParticID.isUndefined()");
	if(fMemberID.isUndefined())
		throw ASIException("TPartic::validateForUpdate: fMemberID.isUndefined()");
	if(fPassword.Len() == 0)
		throw ASIException("TPartic::validateForUpdate: fPassword.Len() == 0");

	if(fGameID.Len() == 0)
		throw ASIException("TPartic::validateForUpdate: fGameID.Len() == 0");
	if(fGameLevel.isUndefined())
		throw ASIException("TPartic::validateForUpdate: fGameLevel.isUndefined()");
//BOB	if(fGamePrice == 0.0)
//BOB		throw ASIException("TPartic::validateForUpdate: fGamePrice == 0.0");
	if(fStatus.isUndefined())
		throw ASIException("TPartic::validateForUpdate: fStatus.isUndefined()");

	if(fTeamID.isUndefined())
		throw ASIException("TPartic::validateForUpdate: fTeamID.isUndefined()");
}

/******************************************************************************/

CStrVar TPartic::getWhereStr(void)
{
	CStrVar str;
	
	str.copyVarg("(ParticID = \"%s\")",fParticID.c_str());
	
	return(str);
}

/******************************************************************************/
/******************************************************************************/

void TPayHistory::clear()
{
	TTableDataSetRecord::clear();
	
	fMemberID.Clear();
	fTransDateTime = TDateTime();

	fParticID.clear();
	fGameID.Clear();

	fCCardType.clear();
	fCCardNumber.Clear();
	fCCardExpDate.Clear();
	fCCardNameOn.Clear();

	memset(fSaleCommand,0,sizeof(fSaleCommand));
	memset(fClerk,0,sizeof(fClerk));
	memset(fComment,0,sizeof(fComment));
	fAmount = 0.0;

	fApproved = false;
	fResponse.clear();
}

/******************************************************************************/

TPayHistoryPtr TPayHistory::newInstance()
{
	TPayHistoryPtr payHistoryPtr = ASMemberObjectBuilder::getThe().newPayHistory();
	payHistoryPtr->clear();
	return(payHistoryPtr);
}

/******************************************************************************/

void TPayHistory::readFromDataSet(TDataSet& dataSet)
{
	fMemberID.setID(dataSet.FieldByName("MemberID")->AsString.c_str());
	fTransDateTime = DataSetReadDateTime(dataSet,"TransDateTime");
	
	fParticID = dataSet.FieldByName("ParticID")->AsInteger;
	fGameID = dataSet.FieldByName("GameID")->AsString.c_str();
	
	/* Credit Card Info */
	fCCardType = dataSet.FieldByName("CCardType")->AsString.c_str();
	fCCardNumber = dataSet.FieldByName("CCardNumber")->AsString.c_str();
	fCCardExpDate = dataSet.FieldByName("CCardExpDate")->AsString.c_str();
	fCCardNameOn = dataSet.FieldByName("CCardNameOn")->AsString.c_str();
	
	/* Request Info */
	tStrCpy(fSaleCommand,sizeof(fSaleCommand),dataSet.FieldByName("SaleCommand")->AsString.c_str());
	tStrCpy(fClerk,sizeof(fClerk),dataSet.FieldByName("Clerk")->AsString.c_str());
	tStrCpy(fComment,sizeof(fComment),dataSet.FieldByName("Comment")->AsString.c_str());
	fAmount = dataSet.FieldByName("Amount")->AsFloat;
	
	/* Response Info */
	fApproved = TBooleanType(dataSet.FieldByName("Approved")->AsString.c_str());
	fResponse = dataSet.FieldByName("Response")->AsString.c_str();
}

/******************************************************************************/

void TPayHistory::writeToDataSet(TDataSet& dataSet)
{
	dataSet.FieldByName("MemberID")->AsString = fMemberID.c_str();
	DataSetWriteDateTime(dataSet,"TransDateTime",fTransDateTime);

	dataSet.FieldByName("ParticID")->AsInteger = fParticID.getID();
	dataSet.FieldByName("GameID")->AsString = fGameID.c_str();
	
	/* Credit Card Info */
	dataSet.FieldByName("CCardType")->AsString = fCCardType.c_str();
	dataSet.FieldByName("CCardNumber")->AsString = fCCardNumber.c_str();
	dataSet.FieldByName("CCardExpDate")->AsString = fCCardExpDate.c_str();
	dataSet.FieldByName("CCardNameOn")->AsString = fCCardNameOn.c_str();
	
	/* Request Info */
	dataSet.FieldByName("SaleCommand")->AsString = fSaleCommand;
	dataSet.FieldByName("Clerk")->AsString = fClerk;
	dataSet.FieldByName("Comment")->AsString = fComment;
	dataSet.FieldByName("Amount")->AsFloat = fAmount;
	
	/* Response Info */
	dataSet.FieldByName("Approved")->AsString = TBooleanType(fApproved).c_str();
	dataSet.FieldByName("Response")->AsString = fResponse.c_str();
}

/******************************************************************************/

void TPayHistory::validateForUpdate()
{
	if(fMemberID.isUndefined())
		throw ASIException("TPayHistory::validateForUpdate: fMemberID.isUndefined()");
	if(fTransDateTime == TDateTime())
		throw ASIException("TPayHistory::validateForUpdate: fTransDateTime == TDateTime()");

	if(fParticID.isUndefined())
		throw ASIException("TPayHistory::validateForUpdate: fParticID.isUndefined()");
	if(fGameID.Len() == 0)
		throw ASIException("TPayHistory::validateForUpdate: fGameID.Len() == 0");
}

/******************************************************************************/

bool TPayHistory::findInTable(TTable& table)
{
	table.IndexName = "";
	return(table.FindKey(OPENARRAY(TVarRec,(fMemberID.getID(),
		(Extended)fTransDateTime))));
}

/******************************************************************************/
/******************************************************************************/

