/* ASBkUtil.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASBasketballAppOptions.h"
#include "ASBasketballUtilManager.h"

using namespace asbasketball;

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
USEUNIT("..\..\..\CBldComm\Source\BinaryFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataSetRecord.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectStore.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\ErrorLog.cpp");
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\..\CBldComm\Source\RequesterError.cpp");
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
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyNewSignupRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyNewMemberSignupRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyLeagueSignupRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFUtil\Source\ASFantasyUtilManager.cpp");
USEUNIT("..\Shared\Source\ASBasketballAppOptions.cpp");
USEUNIT("..\Shared\Source\ASBasketballType.cpp");
USEUNIT("..\Shared\Source\ASBasketballObjectBuilder.cpp");
USEUNIT("..\Shared\Source\ASBasketballObjectStore.cpp");
USEUNIT("..\Shared\Source\ASBasketballStatFileLoader.cpp");
USEUNIT("..\Shared\Source\ASBasketballDraftRanking.cpp");
USEUNIT("Source\ASBasketballUtilManager.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASBkUtil.exe");
}

/******************************************************************************/

#pragma argsused
int main(int argc, char* argv[])
{
	ASBasketballUtilManager utilManager;
	
	utilManager.main(ASBasketballHomeDir(),"ASBkUtil");
}

/******************************************************************************/
/******************************************************************************/
