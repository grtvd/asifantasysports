/* ASManager.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "NTService.h"
#include "ASMemberAppOptions.h"

using namespace asmember;

/******************************************************************************/

USEUNIT("..\..\..\CBldComm\Source\CommType.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommMisc.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommErr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommStr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommFormat.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDB.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDir.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommTick.cpp");
USEUNIT("..\..\..\CBldComm\Source\Streamable.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectBuilder.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataSetRecord.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\ErrorLog.cpp");
USEUNIT("..\..\..\CBldComm\Source\Mailer.cpp");
USEUNIT("..\..\..\CBldComm\Source\SMTPMailer.cpp");
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommCon.cpp");
USEUNIT("..\..\..\CBldComm\Source\NTService.cpp");
USEUNIT("..\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("..\Shared\Source\ASMemberType.cpp");
USEUNIT("..\Shared\Source\ASMemberObjectBuilder.cpp");
USEUNIT("Source\ASMemberManager.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASManager.exe");
}

/******************************************************************************/

#pragma argsused
int main(int argc, char* argv[])
{
	return(TNTService::main(ASMemberHomeDir(),"ASManager",argc,argv));
}

/******************************************************************************/
/******************************************************************************/
