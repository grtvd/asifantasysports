/* ASFootballAppOptions.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <stdexcep.h>

#include "RegistryExt.h"
#include "ASFootballAppOptions.h"
#include "ASFootballType.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

// Declared in AppOptions.h, used to implement Singleton in derived classes.

AppOptions& tag::getTheAppOptions()
{
	static asfootball::ASFootballAppOptions options;
	return(options);
}

/******************************************************************************/

// Load Registry entries that won't change while program is running.

void ASFootballAppOptions::loadAllStatics()
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
		throw ASIException("ASFootballAppOptions::loadAllStatics: invalid "
			"getRegistryRoot(%s)",root);
}

/******************************************************************************/

DirSpec ASFootballAppOptions::getAppHomeDir() const
{
#if 1
/* BOB UNC names cannot be used from code called inside an ISAPI DLL. 
	ISAPI.DLL has SYSTEM account access (which cannot access the network). */
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
	{
		hostMachine.SetFromString(fRegistryHost);
		if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASFootball"))
			throw ASIException("ASFootballAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");
	}
	else
		dirSpec.SetFromString("C:\\Program Files\\ASFootball");
	
	return(dirSpec);
#else
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
		hostMachine.SetFromString(fRegistryHost);
	else
		hostMachine.SetFromString(getLocalHostName());
	
	if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASFootball"))
		throw ASIException("ASFootballAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");

	return(dirSpec);
#endif
}

/******************************************************************************/

int ASFootballAppOptions::getMaxDraftPlayersForPosition(int pos) const
{
	if((pos == pos_Quarterback) ||
			(pos == pos_TightEnd) ||
			(pos == pos_Kicker) ||
			(pos == pos_Defense))
		return(2);

	if((pos == pos_WideReceiver) ||
			(pos == pos_RunningBack))
		return(3);
		
	throw ASIException("ASFootballAppOptions::getMaxDraftPlayersForPosition: invalid position");
}

/******************************************************************************/

int ASFootballAppOptions::getMaxPlayersInLineup(int lineup) const
{
	if(lineup == lut_Starting)
		return(8);

	throw ASIException("ASFootballAppOptions::getMaxPlayersInLineup: invalid lineup");
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
