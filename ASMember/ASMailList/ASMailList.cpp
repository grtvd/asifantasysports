/* ASMailList.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "AppOptions.h"
#include "IsHttpDll.h"

using namespace tag;

/******************************************************************************/
/******************************************************************************/

USEUNIT("..\..\..\CBldComm\Source\CommType.cpp");
USEUNIT("..\..\..\CbldComm\Source\CommMisc.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommErr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommStr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommFormat.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDir.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDB.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommTick.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\HtmlWriter.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpData.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpServer.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpDll.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("Source\ASMailListHtmlServer.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASMailList.dll");
}

/******************************************************************************/

int WINAPI DllEntryPoint(HINSTANCE hinst,unsigned long reason,void*)
{
	return(IsHttpDllEntryPoint(hinst,reason,NULL));
}

/******************************************************************************/
/******************************************************************************/
