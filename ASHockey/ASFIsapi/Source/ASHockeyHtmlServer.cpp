/* ASHockeyHtmlServer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDir.h"

#include "ASHockeyAppOptions.h"
#include "ASHockeyHtmlServer.h"

namespace ashockey
{

/******************************************************************************/

CStrVar ASHockeyHtmlServer::commErrFileName()
{
	return(BuildFullFileName(ASHockeyHomeDir(),"ASHkIsa.out"));
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
