/* ASBasketballAppOptions.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <stdexcep.h>

#include "RegistryExt.h"
#include "ASBasketballAppOptions.h"
#include "ASBasketballType.h"

namespace asbasketball
{

/******************************************************************************/
/******************************************************************************/

// Declared in AppOptions.h, used to implement Singleton in derived classes.

AppOptions& tag::getTheAppOptions()
{
	static asbasketball::ASBasketballAppOptions options;
	return(options);
}

/******************************************************************************/

// Load Registry entries that won't change while program is running.

void ASBasketballAppOptions::loadAllStatics()
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
		throw ASIException("ASBasketballAppOptions::loadAllStatics: invalid "
			"getRegistryRoot(%s)",root);
}

/******************************************************************************/

DirSpec ASBasketballAppOptions::getAppHomeDir() const
{
#if 1
/* BOB UNC names cannot be used from code called inside an ISAPI DLL. 
	ISAPI.DLL has SYSTEM account access (which cannot access the network). */
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
	{
		hostMachine.SetFromString(fRegistryHost);
		if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASBasketball"))
			throw ASIException("ASBasketballAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");
	}
	else
		dirSpec.SetFromString("C:\\Program Files\\ASBasketball");
	
	return(dirSpec);
#else
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
		hostMachine.SetFromString(fRegistryHost);
	else
		hostMachine.SetFromString(getLocalHostName());
	
	if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASBasketball"))
		throw ASIException("ASBasketballAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");

	return(dirSpec);
#endif
}

/******************************************************************************/

int ASBasketballAppOptions::getMaxDraftPlayersForPosition(int pos) const
{
	if(pos == pos_PointGuard)
		return(2);

	if(pos == pos_ShootingGuard)
		return(3);

	if(pos == pos_SmallForward)
		return(2);

	if(pos == pos_PowerForward)
		return(3);

	if(pos == pos_Center)
		return(2);

	throw ASIException("ASBasketballAppOptions::getMaxDraftPlayersForPosition: invalid position");
}

/******************************************************************************/

int ASBasketballAppOptions::getMaxPlayersInLineup(int lineup) const
{
	if(lineup == lut_Starting)
		return(9);

	throw ASIException("ASBasketballAppOptions::getMaxPlayersInLineup: invalid lineup");
}

/******************************************************************************/

}; //namespace asbasketball

/******************************************************************************/
/******************************************************************************/
