/* ICVerifySaleRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ICVerifySaleRqstH
#define ICVerifySaleRqstH

#include "ASMemberType.h"

using namespace tag;

namespace asmember
{

/******************************************************************************/

class TICVerifySaleRqst : public TStreamable
{
protected:
	char			fSaleCommand[4];
	char			fClerk[16];
	char			fComment[26];
	TCCardNumber	fCCardNumber;
	TCCardExpDate	fCCardExpDate;
	double			fAmount;
	TAddrZip		fAddrZip;
	TAddrStreet		fAddrStreet1;

public:
	TICVerifySaleRqst();
	virtual ~TICVerifySaleRqst() {}

	virtual void clear();
	virtual void readFromFiler( TDataFiler& filer );
	virtual void writeToFiler( TDataFiler& filer );

	void setSaleCommand( const char * saleCommand );
	const char* getSaleCommand() const { return(fSaleCommand); }

	void setClerk( const char * clerk );
	const char* getClerk() const { return(fClerk); }

	void setComment( const char * comment );
	const char* getComment() const { return(fComment); }

	void setCardNumber( const char* cardNumber ) { fCCardNumber = cardNumber; }
	const char* getCardNumber() const { return (fCCardNumber); }

	void setCardExpDate(const char* cardExpDate) { fCCardExpDate = cardExpDate; }
	const char* getCardExpDate() const { return (fCCardExpDate); }

	void setAmount( double amount ) { fAmount = amount; }
	double getAmount() const { return (fAmount); }

	void setAddrZip(const char* addrZip) { fAddrZip = addrZip; }
	const char* getAddrZip() const { return(fAddrZip); }
	
	void setAddrStreet1(const char* addrStreet1) { fAddrStreet1 = addrStreet1; }
	const char* getAddrStreet1() const { return(fAddrStreet1); }
};

/******************************************************************************/

}; //namespace asmember

#endif //ICVerifySaleRqstH
/******************************************************************************/
/******************************************************************************/
