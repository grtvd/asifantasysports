/* ASMHttpAuth.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "AppOptions.h"
#include "IsHttpAuthDll.h"

using namespace tag;

/******************************************************************************/
/******************************************************************************/

USEUNIT("..\..\..\CBldComm\Source\CommType.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommMisc.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommErr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommStr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommFormat.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDB.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDir.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommTick.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpAuthDll.cpp");
USEUNIT("..\Shared\Source\ASMemberAppOptions.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASMHttpAuth.dll");
}

/******************************************************************************/

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return(IsHttpAuthDllEntryPoint(hinst,reason,NULL));
}

/******************************************************************************/
/******************************************************************************/
