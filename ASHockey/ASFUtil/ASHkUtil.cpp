/* ASHkUtil.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASHockeyAppOptions.h"
#include "ASHockeyUtilManager.h"

using namespace ashockey;

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
USEUNIT("..\Shared\Source\ASHockeyAppOptions.cpp");
USEUNIT("..\Shared\Source\ASHockeyType.cpp");
USEUNIT("..\Shared\Source\ASHockeyObjectBuilder.cpp");
USEUNIT("..\Shared\Source\ASHockeyObjectStore.cpp");
USEUNIT("..\Shared\Source\ASHockeyStatFileLoader.cpp");
USEUNIT("..\Shared\Source\ASHockeyDraftRanking.cpp");
USEUNIT("Source\ASHockeyUtilManager.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASHkUtil.exe");
}

/******************************************************************************/

#pragma argsused
int main(int argc, char* argv[])
{
	ASHockeyUtilManager utilManager;
	
	utilManager.main(ASHockeyHomeDir(),"ASHkUtil");
}

/******************************************************************************/
/******************************************************************************/
