/* ASFantasyUtilManager.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyUtilManagerH
#define ASFantasyUtilManagerH

#include "ASMemberType.h"
#include "ASFantasyType.h"
#include "ASFantasyStatFileLoader.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

/* Comp Account Info */
struct CompAccountInfo
{
	const char* fEmail;
	const char* fManagerName;
	const char* fRegionName;
	const char* fTeamName;
};

/******************************************************************************/

class ASFantasyUtilManager
{
protected:
	DirSpec fHomeDir;
	int fNumCompAccountInfo;
	int fCompAccountInfoOffset;

public:
	ASFantasyUtilManager() : fNumCompAccountInfo(0),
		fCompAccountInfoOffset(0) {}

	void main(const DirSpec& homeDir,const char* appName);

protected:
	void mainLoop();

	virtual void promptChoices() = 0;
	virtual bool doesChoiceNeedTransaction(int choice) { return(true); }
	virtual void doChoice(int choice) = 0;

	CStrVar promptString(const char* prompt);
	int promptInteger(const char* prompt);
	tag::TDate promptDate(const char* prompt);
	bool promptYesNo(const char* prompt);
	TEncodedParticID promptEncodedParticID();
	TStatPeriod promptStatPeriod();

	void createCompAccounts();
	void createOneCompAccount();
	void incCompAccountInfoOffset();
	virtual int getNumCompAccountInfo() { return(0); }
	virtual const CompAccountInfo* getCompAccountInfo(int offset)
		{ return(NULL); }
	CStrVar getCompAccountEmail();
	CStrVar getCompAccountManagerName();
	CStrVar getCompAccountRegionName();
	CStrVar getCompAccountTeamName();

	void addParticToLeague();

	void loadStat(StatFileLoaderPtr loader);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyUtilManagerH
/******************************************************************************/
/******************************************************************************/
