/* ASMemberAppOptions.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "RegistryExt.h"

#include "ASMemberAppOptions.h"

using namespace asmember;

/******************************************************************************/
/******************************************************************************/
#if defined(USE_ASMEMBER_ONLY)

// Declared in AppOptions.h, used to implement Singleton in derived classes.

AppOptions& tag::getTheAppOptions()
{
	static ASMemberAppOptions options;
	return(options);
}

#endif
/******************************************************************************/
/******************************************************************************/

// Load Registry entries that won't change while program is running.

void ASMemberAppOptions::loadAllStatics()
{
	fMemberRegistryHost = TRegistryExt::KeyReadString(getMemberRegistryRoot(),
		"RegistryHost").c_str();

	fMemberSysOpEmail = TRegistryExt::RemoteKeyReadString(fMemberRegistryHost,
		getMemberRegistryRoot(),"SysOpEmail").c_str();

	fMemberDailyBackupTime = TRegistryExt::RemoteKeyReadTimeAsString(
		fMemberRegistryHost,getMemberRegistryRoot(),"DailyBackupTime");
	fMemberStatusEmailIntSecs = TRegistryExt::RemoteKeyReadInteger(
		fMemberRegistryHost,getMemberRegistryRoot(),"StatusEmailIntSecs");
}

/******************************************************************************/

CStrVar ASMemberAppOptions::getLocalHostName() const
{
	char localHost[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD localHostSize = sizeof(localHost);
	CStrVar result("\\\\");

	if(!GetComputerName(localHost,&localHostSize))
		throw ASIException("ASMemberAppOptions::getLocalHostName: GetComputerName failed");

	result.concat(localHost);
	return(result);
}

/******************************************************************************/

DirSpec ASMemberAppOptions::getASMemberHomeDir() const
{
#if 1
/* BOB There appears to be some issue with using UNC names from code called
	inside an ISAPI DLL. I doesn't work. */
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fMemberRegistryHost.HasLen())
	{
		hostMachine.SetFromString(fMemberRegistryHost);
		if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASMember"))
			throw ASIException("ASMemberAppOptions::getASMemberHomeDir: dirSpec.SetFromParent failed");
	}
	else
		dirSpec.SetFromString("C:\\Program Files\\ASMember");

	return(dirSpec);
#else
	DirSpec hostMachine;
	DirSpec dirSpec;

	if(fMemberRegistryHost.HasLen())
		hostMachine.SetFromString(fMemberRegistryHost);
	else
		hostMachine.SetFromString(getLocalHostName());
	
	if(!dirSpec.SetFromParent(hostMachine,"C$\\Program Files\\ASMember"))
		throw ASIException("ASMemberAppOptions::getASMemberHomeDir: dirSpec.SetFromParent failed");

	return(dirSpec);
#endif
}

/******************************************************************************/

DirSpec ASMemberAppOptions::getASMemberStatDownloadDir() const
{
	DirSpec dirSpec;

	dirSpec.SetFromString(TRegistryExt::RemoteKeyReadString(fMemberRegistryHost,
		getMemberRegistryRoot(),"StatDownloadDir"));

	return(dirSpec);
}

/******************************************************************************/

CStrVar ASMemberAppOptions::getMailProfile() const
{
	return(TRegistryExt::RemoteKeyReadString(fMemberRegistryHost,
		getMemberRegistryRoot(),"MailProfile"));
}

/******************************************************************************/

CStrVar ASMemberAppOptions::getMailHostName() const
{
	return(TRegistryExt::RemoteKeyReadString(fMemberRegistryHost,
		getMemberRegistryRoot(),"MailHostName"));
}

/******************************************************************************/

CStrVar ASMemberAppOptions::getMailUserID() const
{
	return(TRegistryExt::RemoteKeyReadString(fMemberRegistryHost,
		getMemberRegistryRoot(),"MailUserID"));
}

/******************************************************************************/

TDateTime ASMemberAppOptions::getMemberLastBackupDate() const
{
	return(TRegistryExt::RemoteKeyReadDateAsString(fMemberRegistryHost,
		getMemberRegistryRoot(),"LastBackupDate"));
}

/******************************************************************************/

void ASMemberAppOptions::setMemberLastBackupDate(const TDateTime date)
{
	TRegistryExt::RemoteKeyWriteDateAsString(fMemberRegistryHost,
		getMemberRegistryRoot(),"LastBackupDate",date);
}

/******************************************************************************/

void ASMemberAppOptions::getMemberCommErrFileList(CStrVarVector& cStrVarVector)
{
	CStrVar key = getMemberRegistryRoot();

	key.concat("\\CommErrFileList");

	TRegistryExt::RemoteKeyReadCStrVarVector(fMemberRegistryHost,key,
		cStrVarVector);
}

/******************************************************************************/
/******************************************************************************/

