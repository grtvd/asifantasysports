/* ASBaseballAppOptions.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <stdexcep.h>

#include "RegistryExt.h"
#include "ASBaseballAppOptions.h"
#include "ASBaseballType.h"

namespace asbaseball
{

/******************************************************************************/
/******************************************************************************/

// Declared in AppOptions.h, used to implement Singleton in derived classes.

AppOptions& tag::getTheAppOptions()
{
	static asbaseball::ASBaseballAppOptions options;
	return(options);
}

/******************************************************************************/

// Load Registry entries that won't change while program is running.

void ASBaseballAppOptions::loadAllStatics()
{
	ASFantasyAppOptions::loadAllStatics();

	auto_ptr<TRegistryExt> pReg(new TRegistryExt());
	const char* root = getRegistryRoot();

	if(pReg->OpenKey(root,false))
	{
		//BOB fField = pReg->ReadTimeAsString("Field");
		
		pReg->CloseKey();
	}
	else
		throw ASIException("ASBaseballAppOptions::loadAllStatics:"
			" invalid getRegistryRoot(%s)",root);
}

/******************************************************************************/

DirSpec ASBaseballAppOptions::getAppHomeDir() const
{
#if 1
/* BOB UNC names cannot be used from code called inside an ISAPI DLL. 
	ISAPI.DLL has SYSTEM account access (which cannot access the network). */
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
	{
		hostMachine.SetFromString(fRegistryHost);
		if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASBaseball"))
			throw ASIException("ASBaseballAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");
	}
	else
		dirSpec.SetFromString("C:\\Program Files\\ASBaseball");
	
	return(dirSpec);
#else
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
		hostMachine.SetFromString(fRegistryHost);
	else
		hostMachine.SetFromString(getLocalHostName());
	
	if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASBaseball"))
		throw ASIException("ASBaseballAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");

	return(dirSpec);
#endif
}

/******************************************************************************/

int ASBaseballAppOptions::getMaxDraftPlayersForPosition(int pos) const
{
	if((pos == pos_FirstBaseman) ||
			(pos == pos_SecondBaseman) ||
			(pos == pos_ShortStop) ||
			(pos == pos_ThirdBaseman) ||
			(pos == pos_Catcher))
		return(2);

	if(pos == pos_DesignatedHitter)
		return(1);

	if(pos == pos_Outfielder)
		return(6);

	if(pos == pos_StartingPitcher)
		return(6);

	if(pos == pos_ReliefPitcher)
		return(5);
		
	throw ASIException("ASBaseballAppOptions::getMaxDraftPlayersForPosition: invalid position");
}

/******************************************************************************/

int ASBaseballAppOptions::getMaxPlayersInLineup(int lineup) const
{
	if(lineup == lut_Batter)
		return(9);

	if(lineup == lut_Pitcher)
		return(9);

	throw ASIException("ASBaseballAppOptions::getMaxPlayersInLineup: invalid lineup");
}

/******************************************************************************/

}; //namespace asbaseball

/******************************************************************************/
/******************************************************************************/
