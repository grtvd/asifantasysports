/* ASHockeyAppOptions.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyAppOptionsH
#define ASHockeyAppOptionsH

#include "ASFantasyAppOptions.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

#define ASHockeyHomeDir()		(ASHockeyAppOptions::getThe().getAppHomeDir())

/******************************************************************************/

class ASHockeyAppOptions : public ASFantasyAppOptions
{
protected:
	ASHockeyAppOptions() { loadAllStatics(); }
	
public:
	static ASHockeyAppOptions& getThe()
		{ return(dynamic_cast<ASHockeyAppOptions&>(ASFantasyAppOptions::getThe())); }

protected:
	virtual void loadAllStatics();

public:
	virtual const char* getRegistryRoot() const { return("SOFTWARE\\ASHockey"); }
	
	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Hockey"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFH"); }
	virtual DirSpec getAppHomeDir() const;

	virtual bool getParticGamePriceAllowedForMembers() const { return(true); }

	virtual int getNumProfWeeks() const { return(27); }

	virtual int getMaxPlayersPerTeam() const { return(17); }
	virtual int getMaxPlayersInLineup(int lineup) const;
	virtual int getMaxPlayersOfTypeInGameResult() const { return(10); }

//BOB	virtual int getPreDraftLength() const { return(2); }
	virtual int getDraftLength() const { return(4); }
	virtual int getMaxDraftPlayersForPosition(int pos) const;
	virtual int getPlayoffSeriesLength() const { return(7); }
	virtual int getPlayoffSeriesDays() const { return(4); }
		
	virtual const char* getPrimaryDatabaseName() const { return("ASHockey"); };

	friend AppOptions& tag::getTheAppOptions();
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyAppOptionsH
/******************************************************************************/
/******************************************************************************/

