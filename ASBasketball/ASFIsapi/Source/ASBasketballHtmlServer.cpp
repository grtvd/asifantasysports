/* ASBasketballHtmlServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDir.h"

#include "ASBasketballAppOptions.h"
#include "ASBasketballHtmlServer.h"

namespace asbasketball
{

/******************************************************************************/

CStrVar ASBasketballHtmlServer::commErrFileName()
{
	return(BuildFullFileName(ASBasketballHomeDir(),"ASBkIsa.out"));
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
