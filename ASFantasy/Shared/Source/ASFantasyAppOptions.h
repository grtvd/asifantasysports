/* ASFantasyAppOptions.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyAppOptionsH
#define ASFantasyAppOptionsH

#include "ASMemberAppOptions.h"
#include "ASMemberType.h"

using namespace asmember;

namespace asfantasy
{

/******************************************************************************/

#define StatHomeDir()				(ASFantasyAppOptions::getThe().getStatHomeDir())

#define InSystemMaintMode()			(ASFantasyAppOptions::getThe().getInSystemMaintMode())
#define InManualSystemMaintMode()	(ASFantasyAppOptions::getThe().getInManualSystemMaintMode())
#define InNightlyProcessing()		(ASFantasyAppOptions::getThe().getInNightlyProcessing())
#define SetInNightlyProcessing(set)	(ASFantasyAppOptions::getThe().setInNightlyProcessing(set))
#define NightlyProcessingTime()		(ASFantasyAppOptions::getThe().getNightlyProcessingTime())
#define HoldNightlyProcessing()		(ASFantasyAppOptions::getThe().getHoldNightlyProcessing())
#define LastProcessingDate()		(ASFantasyAppOptions::getThe().getLastProcessingDate())
#define SetLastProcessingDate(date)	(ASFantasyAppOptions::getThe().setLastProcessingDate(date))
#define LastBackupDate()			(ASFantasyAppOptions::getThe().getLastBackupDate())
#define SetLastBackupDate(date)		(ASFantasyAppOptions::getThe().setLastBackupDate(date))

#define SignupStartDate()			(ASFantasyAppOptions::getThe().getSignupStartDate())
#define SignupEndDate()				(ASFantasyAppOptions::getThe().getSignupEndDate())
#define UpgradeAvailable()			(ASFantasyAppOptions::getThe().getUpgradeAvailable())
#define PremiumTrialAvailable()		(ASFantasyAppOptions::getThe().getPremiumTrialAvailable())

#define StatStartDate()				(ASFantasyAppOptions::getThe().getStatStartDate())
#define StatEndDate()				(ASFantasyAppOptions::getThe().getStatEndDate())
#define LastStatLoadDate()			(ASFantasyAppOptions::getThe().getLastStatLoadDate())
#define SetLastStatLoadDate(date)	(ASFantasyAppOptions::getThe().setLastStatLoadDate(date))

#define RegularStartDate()			(ASFantasyAppOptions::getThe().getRegularStartDate())
#define DropDeadDate()				(ASFantasyAppOptions::getThe().getDropDeadDate())
#define SeasonOpener()				(ASFantasyAppOptions::getThe().getSeasonOpener())
#define TradingStartDate()			(ASFantasyAppOptions::getThe().getTradingStartDate())
#define TradingEndDate()			(ASFantasyAppOptions::getThe().getTradingEndDate())
#define PlayoffStartDate()			(ASFantasyAppOptions::getThe().getPlayoffStartDate())
#define NumProfWeeks()				(ASFantasyAppOptions::getThe().getNumProfWeeks())

#define MaxTeamsPerPrivateLeague()	(ASFantasyAppOptions::getThe().getMaxTeamsPerPrivateLeague())
#define MinTeamsPerPrivateLeague()	(ASFantasyAppOptions::getThe().getMinTeamsPerPrivateLeague())
#define NumTeamsPerPublicLeague()	(ASFantasyAppOptions::getThe().getNumTeamsPerPublicLeague())
#define MaxTeamsPerDivision()		(ASFantasyAppOptions::getThe().getMaxTeamsPerDivision())
#define MaxGamesPerDay()			(ASFantasyAppOptions::getThe().getMaxGamesPerDay())

#define MaxPlayersPerTeam()			(ASFantasyAppOptions::getThe().getMaxPlayersPerTeam())
#define NumDraftRounds()			(ASFantasyAppOptions::getThe().getNumDraftRounds())
#define NumDraftRoundsPerDay()		(ASFantasyAppOptions::getThe().getNumDraftRoundsPerDay())
#define NumDraftDays()				(ASFantasyAppOptions::getThe().getNumDraftDays())
#define MaxDraftRankingPlayers()	(ASFantasyAppOptions::getThe().getMaxDraftRankingPlayers())
#define MaxPlayersInLineup(lut)		(ASFantasyAppOptions::getThe().getMaxPlayersInLineup(lut))
#define MaxPlayersOfTypeInGameResult() (ASFantasyAppOptions::getThe().getMaxPlayersOfTypeInGameResult())

//BOB #define PreDraftLength()			(ASFantasyAppOptions::getThe().getPreDraftLength())
#define DraftLength()				(ASFantasyAppOptions::getThe().getDraftLength())
#define MaxDraftPlayersForPosition(pos) (ASFantasyAppOptions::getThe().getMaxDraftPlayersForPosition(pos))
#define PlayoffSeriesLength()		(ASFantasyAppOptions::getThe().getPlayoffSeriesLength())
#define PlayoffSeriesDays()			(ASFantasyAppOptions::getThe().getPlayoffSeriesDays())

/******************************************************************************/

enum THoldProcessingEnum
{
	hpr_NoHold,
	hpr_HoldAfterBegin,
	hpr_HoldDontBegin
};
class THoldProcessing : public EnumType<THoldProcessingEnum,hpr_NoHold,hpr_HoldDontBegin>
{
public:
	explicit THoldProcessing(THoldProcessingEnum t = hpr_NoHold) :
		EnumType<THoldProcessingEnum,hpr_NoHold,hpr_HoldDontBegin>(t) {}
	explicit THoldProcessing(const char* str);
	
	const char* c_str() const;
};

/******************************************************************************/

class ASFantasyAppOptions : public ASMemberAppOptions
{
protected:
	CStr63 fRegistryHost;	// Machine with master registry

	TGameID fGameID;
	double fGamePriceMemberPremium;
	double fGamePriceMemberStandard;
	double fGamePriceParticPremium;
	double fGamePriceParticStandard;
	
	TDateTime fNightlyProcessingTime;
	
	TDateTime fSignupStartDate;
	TDateTime fSignupEndDate;
	bool fUpgradeAvailable;
	bool fPremiumTrialAvailable;

	TDateTime fStatStartDate;
	TDateTime fStatEndDate;

	TDateTime fRegularStartDate;
	TDateTime fDropDeadDate;
	TDateTime fSeasonOpener;
	TDateTime fTradingStartDate;
	TDateTime fTradingEndDate;
	TDateTime fPlayoffStartDate;
	
protected:
	ASFantasyAppOptions() {}
	
public:
	static ASFantasyAppOptions& getThe()
		{ return(dynamic_cast<ASFantasyAppOptions&>(ASMemberAppOptions::getThe())); }

protected:
	virtual void loadAllStatics();
		
public:
	/*BOB Need to add this because CPPB was crashing when calling this
		VIRTUAL function. It is defined in ASFootballAppOption. */
//	virtual const char* getRegistryRoot() const { return("SOFTWARE\\ASFootball"); }
	virtual const char* getRegistryRoot() const = 0;

	virtual DirSpec getStatHomeDir() const;
	
	/* Static Runtime Options */
	virtual const char* getGameID() const { return(fGameID); }
	virtual double getGamePriceMemberPremium() const { return(fGamePriceMemberPremium); }
	virtual double getGamePriceMemberStandard() const { return(fGamePriceMemberStandard); }
	virtual double getGamePriceParticPremium() const { return(fGamePriceParticPremium); }
	virtual double getGamePriceParticStandard() const { return(fGamePriceParticStandard); }
	
	TDateTime getNightlyProcessingTime() const { return(fNightlyProcessingTime); }
	
	TDateTime getSignupStartDate() const { return(fSignupStartDate); }
	TDateTime getSignupEndDate() const { return(fSignupEndDate); }
	bool getUpgradeAvailable() const { return(fUpgradeAvailable); }
	bool getPremiumTrialAvailable() const { return(fPremiumTrialAvailable); }

	TDateTime getStatStartDate() const { return(fStatStartDate); }
	TDateTime getStatEndDate() const { return(fStatEndDate); }

	TDateTime getRegularStartDate() const { return(fRegularStartDate); }
	TDateTime getDropDeadDate() const { return(fDropDeadDate); }
	TDateTime getSeasonOpener() const { return(fSeasonOpener); }
	TDateTime getTradingStartDate() const { return(fTradingStartDate); }
	TDateTime getTradingEndDate() const { return(fTradingEndDate); }
	TDateTime getPlayoffStartDate() const { return(fPlayoffStartDate); }
	virtual int getNumProfWeeks() const = 0;


	virtual int getMaxTeamsPerPrivateLeague() const { return(12); }
	virtual int getMinTeamsPerPrivateLeague() const { return(8); }
	virtual int getNumTeamsPerPublicLeague() const { return(10); }
	virtual int getMaxTeamsPerDivision() const { return(6); }
	virtual int getMaxGamesPerDay() const
		{ return(getMaxTeamsPerPrivateLeague() / 2); }

	virtual int getMaxPlayersPerTeam() const = 0;
	virtual int getNumDraftRounds() const { return(getMaxPlayersPerTeam()); }
	virtual int getNumDraftRoundsPerDay() const					// round up/down based rounds/days
		{ return(floor(((double)getNumDraftRounds()/
			(double)getNumDraftDays())+0.5)); }
	virtual int getNumDraftDays() const { return(4); }
	virtual int getMaxDraftRankingPlayers() const
		{ return(getMaxTeamsPerPrivateLeague() * getMaxPlayersPerTeam()); }
	virtual int getMaxPlayersInLineup(int lineup) const = 0;
	virtual int getMaxPlayersOfTypeInGameResult() const = 0;	//max of Offensive or Defensive players

//BOB	virtual int getPreDraftLength() const = 0;
	virtual int getDraftLength() const = 0;
	virtual int getMaxDraftPlayersForPosition(int pos) const = 0;
	virtual int getPlayoffSeriesLength() const = 0;
	virtual int getPlayoffSeriesDays() const = 0;

	
	/* Dynamic Runtime Options */
	bool getInSystemMaintMode() { return(getInManualSystemMaintMode() ||
		getInNightlyProcessing()); }
	bool getInManualSystemMaintMode();
	
	bool getInNightlyProcessing();
	void setInNightlyProcessing(bool set);

	THoldProcessing getHoldNightlyProcessing();
	//BOB void setHoldNightlyProcessing(THoldProcessing holdProcessing);
	
	TDateTime getLastProcessingDate();
	void setLastProcessingDate(TDateTime date);

	TDateTime getLastBackupDate() const;
	void setLastBackupDate(const TDateTime date);

	TDateTime getLastStatLoadDate() const;
	void setLastStatLoadDate(const TDateTime date);
};


/******************************************************************************/

TDateTime NextProcessingDateTime(TDateTime fromDateTime,int plusDays);

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyAppOptionsH
/******************************************************************************/
/******************************************************************************/

