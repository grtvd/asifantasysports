/* ASBaseballHtmlServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDir.h"

#include "ASBaseballAppOptions.h"
#include "ASBaseballHtmlServer.h"

namespace asbaseball
{

/******************************************************************************/

CStrVar ASBaseballHtmlServer::commErrFileName()
{
	return(BuildFullFileName(ASBaseballHomeDir(),"ASBbIsa.out"));
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
