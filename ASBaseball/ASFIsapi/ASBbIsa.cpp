/* ASBbIsa.cpp */

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
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataSetRecord.cpp");
USEUNIT("..\..\..\CBldComm\Source\HtmlView.cpp");
USEUNIT("..\..\..\CBldComm\Source\HtmlWriter.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpData.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpServer.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
USEUNIT("..\..\..\CBldComm\Source\IsHttpDll.cpp");
USEUNIT("..\..\..\CBldComm\Source\RequesterError.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\ErrorLog.cpp");
USEUNIT("..\..\..\CBldComm\Source\Mailer.cpp");
USEUNIT("..\..\..\CBldComm\Source\SendMail.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberType.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberObjectBuilder.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberDB.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyAppOptions.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyType.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyObjectBuilder.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyDB.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyHtmlServer.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyHtmlPageBuilder.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyNewSignupPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasySignupErrorPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasySignupIntroPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasySignupWhichPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyNewMemberSignupPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyNewParticSignupPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyPickParticPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyHubPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyCustomPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyLeagueSignupPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyTeamsPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyDraftRankingsPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyDraftResultsPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasySchedulePage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyLineupPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyGameResultsPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyStandingsPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyFreeAgentPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyTradePage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsapi\Source\ASFantasyPlayoffPage.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyNewSignupRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyNewMemberSignupRqst.cpp");
USEUNIT("..\..\ASFantasy\ASFIsOrb\Source\ASFantasyNewParticSignupRqst.cpp");
USEUNIT("..\Shared\Source\ASBaseballAppOptions.cpp");
USEUNIT("..\Shared\Source\ASBaseballType.cpp");
USEUNIT("..\Shared\Source\ASBaseballObjectBuilder.cpp");
USEUNIT("Source\ASBaseballHtmlServer.cpp");
USEUNIT("Source\ASBaseballHtmlPageBuilder.cpp");
//---------------------------------------------------------------------------
const char* tag::GetExeDllName()
{
	return("ASBbIsa.dll");
}

/******************************************************************************/

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
	return(IsHttpDllEntryPoint(hinst,reason,NULL));
}

/******************************************************************************/
/******************************************************************************/
