/* ASBulkMailer.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "AppOptions.h"
#include "CommType.h"
#include "CommErr.h"
#include "ASMemberBulkMailer.h"

using namespace tag;
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
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommCon.cpp");
USEUNIT("..\..\..\CBldComm\Source\NTService.cpp");
USEUNIT("..\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("..\Shared\Source\ASMemberType.cpp");
USEUNIT("..\Shared\Source\ASMemberObjectBuilder.cpp");
USEUNIT("Source\ASMemberBulkMailer.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASBulkMailer.exe");
}

/******************************************************************************/

#pragma argsused
int main(int argc, char** argv)
{
	CStrVar errMsg;
	int returnCode = 1;

	CommErrInit("ASBulkMailer",ceo_File);
	try
	{
		DoBulkMailer();
	}
	catch(Exception& e)
	{
		errMsg.copy("catch: Exception: ");
		errMsg.concat(e.Message.c_str());

	}
	catch(exception& e)
	{
		errMsg.copy("catch: exception: ");
		errMsg.concat(e.what());
	}
	catch(...)
	{
		errMsg.copy("catch: ...");
	}
	
	if(errMsg.hasLen())
	{
		CommErrMsg(cel_Error,errMsg);
	}
	else
		CommErrMsg(cel_Info,"Normal Exit (%d).",returnCode);

	CommErrDispose();
	return(returnCode);
}

/******************************************************************************/
/******************************************************************************/
