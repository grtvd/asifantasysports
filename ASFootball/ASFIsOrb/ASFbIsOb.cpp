/* ASFbIsOb.cpp */

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
USEUNIT("..\..\..\CBldComm\Source\Streamable.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectBuilder.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\BinaryFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataSetRecord.cpp");
USEUNIT("..\..\..\CBldComm\Source\ObjectStore.cpp");
USEUNIT("..\..\..\CBldComm\Source\HtmlView.cpp");
USEUNIT("..\..\..\CBldComm\Source\HTMLWriter.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpData.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpServer.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpDll.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\ErrorLog.cpp");
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\..\CBldComm\Source\RequesterError.cpp");
USEUNIT("..\..\..\CBldComm\Source\FulfillerNotify.cpp");
USEUNIT("..\..\..\CBldComm\Source\StreamFulfiller.cpp");
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
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyOrbFulfiller.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyHtmlObjectServer.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyMiscRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyDraftRankingQueryRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyDraftRankingUpdateRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyDraftResultRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyPlayerScoutRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyLeagueSignupRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasySignupLeagueListRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyScheduleRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyLineupQueryRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyLineupUpdateRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyStandingsRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyGameResultsRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyFreeAgentQueryRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyFreeAgentUpdateRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyTradeProposeQueryRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyTradeProposeTeamRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyTradeProposeUpdateRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyTradeReceiveUpdateRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyTradeProtestUpdateRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyPlayoffRqst.cpp");
USEUNIT("..\Shared\Source\ASFootballAppOptions.cpp");
USEUNIT("..\Shared\Source\ASFootballType.cpp");
USEUNIT("..\Shared\Source\ASFootballObjectBuilder.cpp");
USEUNIT("..\Shared\Source\ASFootballObjectShelf.cpp");
USEUNIT("..\Shared\Source\ASFootballObjectStore.cpp");
USEUNIT("Source\ASFootballHtmlObjectServer.cpp");
USEUNIT("Source\ASFootballOrbFulfiller.cpp");
USEUNIT("Source\ASFootballMiscRqst.cpp");
USEUNIT("Source\ASFootballPlayerScoutRqst.cpp");
USEUNIT("Source\ASFootballLineupQueryRqst.cpp");
USEUNIT("Source\ASFootballLineupUpdateRqst.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASFbIsOb.dll");
}

/******************************************************************************/

int WINAPI DllEntryPoint(HINSTANCE hinst,unsigned long reason,void*)
{
	return(IsHttpDllEntryPoint(hinst,reason,NULL));
}

/******************************************************************************/
/******************************************************************************/
