/* ICVerifySaleResp.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include "CBldComm.h"

#include "ICVerifySaleResp.h"

namespace asmember
{

/******************************************************************************/

void TICVerifySaleResp::readFromFiler( TDataFiler& filer )
{
	fResponse = filer.readString().c_str();
}

/******************************************************************************/

void TICVerifySaleResp::writeToFiler( TDataFiler& filer )
{
	filer.writeString(fResponse.c_str());
}

/******************************************************************************/

bool TICVerifySaleResp::isApproved()
{
	char apprv;

	if(!fResponse.hasLen())
		throw ASIException("TICVerifySaleResp::isApproved: Empty response field");

	apprv = (char) toupper( fResponse[0] );
	if ((apprv != 'Y') && (apprv != 'N'))
		throw ASIException("TICVerifySaleResp::isApproved: Invalid response: %s",fResponse.c_str());

	return ((apprv == 'Y') ? TRUE : FALSE);
}

/******************************************************************************/

const char* TICVerifySaleResp::getReference()
{
	// empty string
	if (fResponse.len() <= 1)
		return("");

	// return data after approval flag
	return(fResponse.c_str() + 1);
}

/******************************************************************************/

}; //namespace asmember

/******************************************************************************/
/******************************************************************************/
