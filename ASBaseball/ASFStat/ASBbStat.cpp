/* ASBbStat.cpp */

/******************************************************************************/
/******************************************************************************/

//#include <condefs.h>
#include "CBldVCL.h"
#pragma hdrstop

#include "ASBaseballStatManager.h"

using namespace asbaseball;

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
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\BinaryFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataSetRecord.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectStore.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\ErrorLog.cpp");
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberType.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberObjectBuilder.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberDB.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyAppOptions.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyType.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectBuilder.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyDB.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectStore.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectShelf.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyStatFileLoader.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyStatSummaryBuilder.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyDraftRanking.cpp");
USEUNIT("..\Shared\Source\ASBaseballAppOptions.cpp");
USEUNIT("..\Shared\Source\ASBaseballType.cpp");
USEUNIT("..\Shared\Source\ASBaseballObjectBuilder.cpp");
USEUNIT("..\Shared\Source\ASBaseballObjectStore.cpp");
USEUNIT("..\Shared\Source\ASBaseballStatFileLoader.cpp");
USEUNIT("..\Shared\Source\ASBaseballDraftRanking.cpp");
USEUNIT("Source\ASBaseballStatManager.cpp");
//---------------------------------------------------------------------------

const char* tag::GetExeDllName()
{
	return("ASBbStat.exe");
}

/******************************************************************************/

#pragma argsused
int main(int argc, char* argv[])
{
	ASBaseballStatManager statManager;
	
	statManager.run();
}

/******************************************************************************/
/******************************************************************************/

