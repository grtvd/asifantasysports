/* ASHockeyAppOptions.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop
#include <stdexcep.h>

#include "RegistryExt.h"
#include "ASHockeyAppOptions.h"
#include "ASHockeyType.h"

namespace ashockey
{

/******************************************************************************/
/******************************************************************************/

// Declared in AppOptions.h, used to implement Singleton in derived classes.

AppOptions& tag::getTheAppOptions()
{
	static ashockey::ASHockeyAppOptions options;
	return(options);
}

/******************************************************************************/

// Load Registry entries that won't change while program is running.

void ASHockeyAppOptions::loadAllStatics()
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
		throw ASIException("ASHockeyAppOptions::loadAllStatics: invalid "
			"getRegistryRoot(%s)",root);
}

/******************************************************************************/

DirSpec ASHockeyAppOptions::getAppHomeDir() const
{
#if 1
/* BOB UNC names cannot be used from code called inside an ISAPI DLL. 
	ISAPI.DLL has SYSTEM account access (which cannot access the network). */
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
	{
		hostMachine.SetFromString(fRegistryHost);
		if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASHockey"))
			throw ASIException("ASHockeyAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");
	}
	else
		dirSpec.SetFromString("C:\\Program Files\\ASHockey");
	
	return(dirSpec);
#else
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fRegistryHost.HasLen())
		hostMachine.SetFromString(fRegistryHost);
	else
		hostMachine.SetFromString(getLocalHostName());
	
	if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASHockey"))
		throw ASIException("ASHockeyAppOptions::getAppHomeDir: dirSpec.SetFromParent failed");

	return(dirSpec);
#endif
}

/******************************************************************************/

int ASHockeyAppOptions::getMaxDraftPlayersForPosition(int pos) const
{
	if(pos == pos_Winger)
		return(6);

	if(pos == pos_Center)
		return(3);

	if(pos == pos_Defenseman)
		return(6);

	if(pos == pos_Goalie)
		return(2);

	throw ASIException("ASHockeyAppOptions::getMaxDraftPlayersForPosition: invalid position");
}

/******************************************************************************/

int ASHockeyAppOptions::getMaxPlayersInLineup(int lineup) const
{
	if(lineup == lut_Skater)
		return(10);

	if(lineup == lut_Goalie)
		return(1);

	throw ASIException("ASHockeyAppOptions::getMaxPlayersInLineup: invalid lineup");
}

/******************************************************************************/

}; //namespace ashockey

/******************************************************************************/
/******************************************************************************/
