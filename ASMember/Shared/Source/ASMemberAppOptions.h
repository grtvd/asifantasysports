/* ASMemberAppOptions.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASMemberAppOptionsH
#define ASMemberAppOptionsH

#include "AppOptions.h"
#include "CommType.h"
#include "CommDir.h"
#include "RegistryExt.h"

using namespace tag;

namespace asmember
{

/******************************************************************************/

#define ASMemberHomeDir()			(ASMemberAppOptions::getThe().getASMemberHomeDir())
#define ASMemberStatDownloadDir()	(ASMemberAppOptions::getThe().getASMemberStatDownloadDir())

#define MemberDatabaseName()		(ASMemberAppOptions::getThe().getMemberDatabaseName())
#define MemberMiscDatabaseName()	(ASMemberAppOptions::getThe().getMemberMiscDatabaseName())

#define MailProfile()				(ASMemberAppOptions::getThe().getMailProfile())
#define MailHostName()				(ASMemberAppOptions::getThe().getMailHostName())
#define MailUserID()				(ASMemberAppOptions::getThe().getMailUserID())

#define CurrentGameID()				(ASMemberAppOptions::getThe().getGameID())
#define GamePriceMemberPremium()	(ASMemberAppOptions::getThe().getGamePriceMemberPremium())
#define GamePriceMemberStandard()	(ASMemberAppOptions::getThe().getGamePriceMemberStandard())
#define GamePriceParticPremium()	(ASMemberAppOptions::getThe().getGamePriceParticPremium())
#define GamePriceParticStandard()	(ASMemberAppOptions::getThe().getGamePriceParticStandard())
#define ParticGamePriceAllowedForMembers()	(ASMemberAppOptions::getThe().getParticGamePriceAllowedForMembers())

#define MemberDailyBackupTime()			(ASMemberAppOptions::getThe().getMemberDailyBackupTime())
#define MemberLastBackupDate()			(ASMemberAppOptions::getThe().getMemberLastBackupDate())
#define SetMemberLastBackupDate(date)	(ASMemberAppOptions::getThe().setMemberLastBackupDate(date))

#define GetMemberCommErrFileList(list)	(ASMemberAppOptions::getThe().getMemberCommErrFileList(list))

#define MemberStatusEmailIntSecs()		(ASMemberAppOptions::getThe().getMemberStatusEmailIntSecs())

/******************************************************************************/

class ASMemberAppOptions : public AppOptions
{
protected:
	CStr63 fMemberRegistryHost;	// Machine with master registry
	CStrVar fMemberSysOpEmail;

	TDateTime fMemberDailyBackupTime;
	int fMemberStatusEmailIntSecs;	// (seconds) Interval to send Status Email.

protected:
	#if defined(USE_ASMEMBER_ONLY)
	ASMemberAppOptions() { loadAllStatics(); }
	#else
	ASMemberAppOptions() {}
	#endif
	
public:
	static ASMemberAppOptions& getThe()
		{ return(dynamic_cast<ASMemberAppOptions&>(AppOptions::getThe())); }

protected:
	virtual void loadAllStatics();
		
public:
	virtual const char* getMemberRegistryRoot() const { return("SOFTWARE\\ASMember"); }

	virtual const char* getPrimaryDatabasePassword() const { return("!!!!!!!!"); };
	virtual const char* getMemberDatabaseName() const { return("ASMember"); };
	virtual const char* getMemberMiscDatabaseName() const { return("ASMemberMisc"); };

	#if defined(USE_ASMEMBER_ONLY)
	virtual DirSpec getAppHomeDir() const { return(getASMemberHomeDir()); }
	#endif

	//BOB Move these into Registry
	virtual CStrVar getTechSupportPhoneNumber() const { return("(610) 783-6467"); }
	virtual CStrVar getTechSupportFaxNumber() const { return("(610) 783-4637"); }
	virtual CStrVar getTechSupportName() const { return("The Ref"); }
	virtual CStrVar getTechSupportEmail() const { return("TheRef@affinitysports.com"); }
	virtual CStrVar getSysOpEmail() const { return(fMemberSysOpEmail); }

	CStrVar getLocalHostName() const;
	DirSpec getASMemberHomeDir() const;
	DirSpec getASMemberStatDownloadDir() const;
	virtual CStrVar getMailProfile() const;
	virtual CStrVar getMailHostName() const;
	virtual CStrVar getMailUserID() const;

	#if defined(USE_ASMEMBER_ONLY)
	virtual CStrVar getAppNameFull() const { return(""); }
	virtual CStrVar getAppNameAbbr() const { return(""); }
	virtual const char* getGameID() const { return(""); }	//BOB must fix
	#else
	virtual const char* getGameID() const = 0;
	virtual double getGamePriceMemberPremium() const = 0;
	virtual double getGamePriceMemberStandard() const = 0;
	virtual double getGamePriceParticPremium() const = 0;
	virtual double getGamePriceParticStandard() const = 0;
	virtual bool getParticGamePriceAllowedForMembers() const = 0;
	#endif

	TDateTime getMemberDailyBackupTime() const { return(fMemberDailyBackupTime); }
	TDateTime getMemberLastBackupDate() const;
	void setMemberLastBackupDate(const TDateTime date);

	void getMemberCommErrFileList(CStrVarVector& cStrVarVector);

	int getMemberStatusEmailIntSecs() const { return(fMemberStatusEmailIntSecs); }

	friend AppOptions& tag::getTheAppOptions();
};

/******************************************************************************/

}; //namespace asmember

#endif //ASMemberAppOptionsH
/******************************************************************************/
/******************************************************************************/

