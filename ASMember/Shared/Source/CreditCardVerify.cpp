/* CreditCardVerify.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CreditCardVerify.h"

using namespace asmember;

/******************************************************************************/
/******************************************************************************/

bool validateCCardNumber( TCCardNumber& inputCardNum, TCreditCardTypeEnum cardType )
{
	char	cardNum[32];
	short	minLen, maxLen, i, j, length;
	char	leadingDigit;

	// strip all spaces and verify number composition
	length = inputCardNum.Len();
	for (i=j=0; i<length; i++)
	{
		if (isdigit( inputCardNum[i] ))
		{
			if (j < (sizeof(cardNum)-1))
				cardNum[j++] = inputCardNum[i];
		}
		else if (!isspace( inputCardNum[i] ))
			return (FALSE);
	}
	cardNum[j] = 0;

	// determine string characteristics
	switch( cardType )
	{
		case cct_Mastercard:
			leadingDigit = '5';
			minLen = 13;
			maxLen = 16;
			break;
		case cct_Visa:
			leadingDigit = '4';
			minLen = 13;
			maxLen = 16;
			break;
		default:
			leadingDigit = '\0';
			minLen = maxLen = 0;
			break;
	}

	// verify leading digits
	if ((leadingDigit != '\0') && (cardNum[0] != leadingDigit))
		return (FALSE);

	// verify string size and composition
	if (maxLen > 0)
	{
		length = strlen(cardNum);
		if ((length < minLen) || (length > maxLen))
			return (FALSE);
	}

	// MOD 10 check digit
	return cCardMod10( cardNum );
}

/******************************************************************************/

bool cCardMod10( const char * cardNum )
{
	short	xdigit = 0, weight[2] = { 1, 2 };
	short	i, whichWeight, temp;

	// move from last card digit to first
	for (i=strlen(cardNum)-1, whichWeight=0;  i>=0  ; i--, whichWeight++ )
	{
		// skip blanks
		if (cardNum[i] == ' ')
		{
			whichWeight--;		// use same weight for next digit
			continue;
		}

		// update check digit calc
		temp = (cardNum[i] - '0') * weight[whichWeight & 1];
		xdigit += (temp / 10) + (temp % 10);
	}

	// indicate if check is valid
	xdigit %= 10;
	return ((xdigit == 0) ? TRUE : FALSE);
}

/******************************************************************************/
/******************************************************************************/

