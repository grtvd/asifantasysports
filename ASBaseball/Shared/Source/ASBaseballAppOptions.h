/* ASBaseballAppOptions.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballAppOptionsH
#define ASBaseballAppOptionsH

#include "ASFantasyAppOptions.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

#define ASBaseballHomeDir()		(ASBaseballAppOptions::getThe().getAppHomeDir())

/******************************************************************************/

class ASBaseballAppOptions : public ASFantasyAppOptions
{
protected:
	ASBaseballAppOptions() { loadAllStatics(); }
	
public:
	static ASBaseballAppOptions& getThe()
		{ return(dynamic_cast<ASBaseballAppOptions&>(ASFantasyAppOptions::getThe())); }

protected:
	virtual void loadAllStatics();

public:
	virtual const char* getRegistryRoot() const { return("SOFTWARE\\ASBaseball"); }

	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Baseball"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFB"); }
	virtual DirSpec getAppHomeDir() const;

	virtual bool getParticGamePriceAllowedForMembers() const { return(true); }

	virtual int getNumProfWeeks() const { return(26); }

	virtual int getMaxPlayersPerTeam() const { return(28); }
	virtual int getMaxPlayersInLineup(int lineup) const;
	virtual int getMaxPlayersOfTypeInGameResult() const { return(9); }

//BOB	virtual int getPreDraftLength() const { return(2); }
	virtual int getDraftLength() const { return(4); }
	virtual int getMaxDraftPlayersForPosition(int pos) const;
	virtual int getPlayoffSeriesLength() const { return(7); }
	virtual int getPlayoffSeriesDays() const { return(4); }

	virtual const char* getPrimaryDatabaseName() const { return("ASBaseball"); };

	friend AppOptions& tag::getTheAppOptions();
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballAppOptionsH
/******************************************************************************/
/******************************************************************************/

