/* ASFbEng.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "NTService.h"
#include "ASFootballAppOptions.h"

using namespace tag;
using namespace asfootball;

/******************************************************************************/
//---------------------------------------------------------------------------
USEUNIT("..\..\..\CBldComm\Source\CommType.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommMisc.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommErr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommStr.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommFormat.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDir.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDB.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommTick.cpp");
USEUNIT("..\..\..\CBldComm\Source\Streamable.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectBuilder.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataSetRecord.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectStore.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\..\CBldComm\Source\ErrorLog.cpp");
USEUNIT("..\..\..\CBldComm\Source\NTService.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommCon.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberType.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberObjectBuilder.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberDB.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyAppOptions.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyType.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectBuilder.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyDB.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectShelf.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectStore.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyStatFileLoader.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyStatSummaryBuilder.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyCreateDraftOrder.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyDraftResolver.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyBuildSchedule.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyCreateLineup.cpp");
USEUNIT("..\..\ASFantasy\ASFEng\Source\ASFantasyEngine.cpp");
USEUNIT("..\Shared\Source\ASFootballAppOptions.cpp");
USEUNIT("..\Shared\Source\ASFootballType.cpp");
USEUNIT("..\Shared\Source\ASFootballObjectBuilder.cpp");
USEUNIT("..\Shared\Source\ASFootballObjectShelf.cpp");
USEUNIT("..\Shared\Source\ASFootballObjectStore.cpp");
USEUNIT("..\Shared\Source\ASFootballStatFileLoader.cpp");
USEUNIT("..\Shared\Source\ASFootballBuildSchedule.cpp");
USEUNIT("Source\ASFootballEngine.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASFbEng.exe");
}

/******************************************************************************/

#pragma argsused
int main(int argc, char* argv[])
{
	return(TNTService::main(ASFootballHomeDir(),"ASFbEng",argc,argv));
}

/******************************************************************************/
/******************************************************************************/
