/* ASFantasySignupErrorPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasySignupErrorPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasySignupErrorGetPage::writeBodyRows()
{
	CStrVar str;

	writeBodyLineRow();

	str.copyVarg("Sorry, your sign-up request could not be completed."
		"\r\n\r\nReason: \"%s\".\r\n\r\nPlease correct your data and "
		"try again.",fErrorMsg.c_str());

	writeBodySectionTextRow(str);

	writeBodyEmptyRow(50);
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
