/* ASFootballAppOptions.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballAppOptionsH
#define ASFootballAppOptionsH

#include "ASFantasyAppOptions.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

#define ASFootballHomeDir()		(ASFootballAppOptions::getThe().getAppHomeDir())

/******************************************************************************/

class ASFootballAppOptions : public ASFantasyAppOptions
{
protected:
	ASFootballAppOptions() { loadAllStatics(); }
	
public:
	static ASFootballAppOptions& getThe()
		{ return(dynamic_cast<ASFootballAppOptions&>(ASFantasyAppOptions::getThe())); }

protected:
	virtual void loadAllStatics();

public:
	virtual const char* getRegistryRoot() const { return("SOFTWARE\\ASFootball"); }
	
	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Football"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFF"); }
	virtual DirSpec getAppHomeDir() const;

	virtual bool getParticGamePriceAllowedForMembers() const { return(true); }

	virtual int getNumProfWeeks() const { return(17); }

	virtual int getMaxPlayersPerTeam() const { return(14); }
	virtual int getMaxPlayersInLineup(int lineup) const;
	virtual int getMaxPlayersOfTypeInGameResult() const { return(8); }

//BOB	virtual int getPreDraftLength() const { return(2); }
	virtual int getDraftLength() const { return(4); }
	virtual int getMaxDraftPlayersForPosition(int pos) const;
	virtual int getPlayoffSeriesLength() const { return(7); };
	virtual int getPlayoffSeriesDays() const { return(4); };
		
	virtual const char* getPrimaryDatabaseName() const { return("ASFootball"); };

	friend AppOptions& tag::getTheAppOptions();
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballAppOptionsH
/******************************************************************************/
/******************************************************************************/

