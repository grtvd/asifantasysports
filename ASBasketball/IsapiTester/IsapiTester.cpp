#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyIsapiDllTester.h"

using namespace tag;
using namespace asfantasy;

//---------------------------------------------------------------------------
USEUNIT("..\..\..\CBldComm\Source\IsapiDllTester.cpp");
USEUNIT("..\Shared\Source\ASBasketballAppOptions.cpp");
USEUNIT("..\..\ASFantasy\Shared\Source\ASFantasyAppOptions.cpp");
USEUNIT("..\..\ASMember\Shared\Source\ASMemberAppOptions.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommDir.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommType.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommStr.cpp");
USEUNIT("..\..\..\CBldComm\Source\RegistryExt.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommErr.cpp");
USEUNIT("..\..\..\CBldComm\Source\TextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\PipeTextFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommFormat.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommMisc.cpp");
USEUNIT("..\..\..\CBldComm\Source\BinaryFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\DataFiler.cpp");
USEUNIT("..\..\..\CBldComm\Source\CommTick.cpp");
USEUNIT("..\..\ASFantasy\IsapiTester\Source\ASFantasyIsapiDllTester.cpp");
USEUNIT("..\..\..\CBldComm\Source\PasswordEncode.cpp");
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
	ASFantasyIsapiDllLoader tester("Z:\\TAG999\\ASBasketball\\ASFIsapi\\ASBkIsa.dll");
//	ASFantasyIsapiDllLoader tester("Z:\\TAG999\\ASBasketball\\ASFIsOrb\\ASBkIsOb.dll");
	tester.run();
	return 0;
}
