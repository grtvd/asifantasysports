/* ASBasketballAppOptions.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballAppOptionsH
#define ASBasketballAppOptionsH

#include "ASFantasyAppOptions.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

#define ASBasketballHomeDir()		(ASBasketballAppOptions::getThe().getAppHomeDir())

/******************************************************************************/

class ASBasketballAppOptions : public ASFantasyAppOptions
{
protected:
	ASBasketballAppOptions() { loadAllStatics(); }
	
public:
	static ASBasketballAppOptions& getThe()
		{ return(dynamic_cast<ASBasketballAppOptions&>(ASFantasyAppOptions::getThe())); }

protected:
	virtual void loadAllStatics();

public:
	virtual const char* getRegistryRoot() const { return("SOFTWARE\\ASBasketball"); }
	
	virtual CStrVar getAppNameFull() const { return("World Wide Fantasy Basketball"); }
	virtual CStrVar getAppNameAbbr() const { return("WWFB"); }
	virtual DirSpec getAppHomeDir() const;

	virtual bool getParticGamePriceAllowedForMembers() const { return(true); }

	virtual int getNumProfWeeks() const { return(24); }

	virtual int getMaxPlayersPerTeam() const { return(12); }
	virtual int getMaxPlayersInLineup(int lineup) const;
	virtual int getMaxPlayersOfTypeInGameResult() const { return(9); }

//BOB	virtual int getPreDraftLength() const { return(2); }
	virtual int getDraftLength() const { return(4); }
	virtual int getMaxDraftPlayersForPosition(int pos) const;
	virtual int getPlayoffSeriesLength() const { return(7); }
	virtual int getPlayoffSeriesDays() const { return(4); }

	virtual const char* getPrimaryDatabaseName() const { return("ASBasketball"); };

	friend AppOptions& tag::getTheAppOptions();
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballAppOptionsH
/******************************************************************************/
/******************************************************************************/

