/* ICVerifySaleRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CBldComm.h"

#include "ICVerifySaleRqst.h"

namespace asmember
{

/******************************************************************************/

TICVerifySaleRqst::TICVerifySaleRqst()
{
	clear();
}

/******************************************************************************/

void TICVerifySaleRqst::clear()
{
	fSaleCommand[0] = '\0';
	fClerk[0] = '\0';
	fComment[0] = '\0';
	fAmount = 0.0;
}

/******************************************************************************/

void TICVerifySaleRqst::readFromFiler( TDataFiler& filer )
{
	// read fields to file
	tStrCpy( fSaleCommand, sizeof(fSaleCommand), filer.readString().c_str() );
	tStrCpy( fClerk, sizeof(fClerk), filer.readString().c_str() );
	tStrCpy( fComment, sizeof(fComment), filer.readString().c_str() );
	fCCardNumber = filer.readString().c_str();
	fCCardExpDate = filer.readString().c_str();
	fAmount = filer.readDouble();
	fAddrZip = filer.readString().c_str();
	fAddrStreet1 = filer.readString().c_str();
}

/******************************************************************************/

void TICVerifySaleRqst::writeToFiler( TDataFiler& filer )
{
#if 0
	// verify that critical fields have values
	if ((fSaleCommand[0] == '\0') || (fCCardNumber[0] == '\0') ||
		(fCCardExpDate[0] == '\0') || (fAmount == 0.0))
	{
		TOOLDEBUG( tErrorMsg(
			"TICVerifySaleRqst::writeToFiler() invalid data: cmd=%s, num=%s, exp=%s, amt=%lf",
			fSaleCommand, fCCardNumber.c_str(), fCCardExpDate.c_str(), fAmount ); );
		throw ASIException( "TICVerifySaleRqst::writeToFiler: Missing fields on request file write" );
	}
#endif

	// write fields to file
	filer.writeString( fSaleCommand );
	filer.writeString( fClerk );
	filer.writeString( fComment );
	filer.writeString( fCCardNumber.c_str() );
	filer.writeString( fCCardExpDate.c_str() );
	filer.writeDouble( fAmount, FTF_STANDARD, 2 );
	filer.writeString( fAddrZip.c_str() );
	filer.writeString( fAddrStreet1.c_str() );
}

/******************************************************************************/

void TICVerifySaleRqst::setSaleCommand( const char * saleCommand )
{
	tStrCpy( fSaleCommand, sizeof(fSaleCommand), saleCommand );
}

/******************************************************************************/

void TICVerifySaleRqst::setClerk( const char * clerk )
{
	tStrCpy( fClerk, sizeof(fClerk), clerk );
}

/******************************************************************************/

void TICVerifySaleRqst::setComment( const char * comment )
{
	tStrCpy( fComment, sizeof(fComment), comment );
}

/******************************************************************************/

}; //namespace asmember

/******************************************************************************/
/******************************************************************************/
