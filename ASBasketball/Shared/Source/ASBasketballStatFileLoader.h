/* ASBasketballStatFileLoader.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballStatFileLoaderH
#define ASBasketballStatFileLoaderH

#include "ASFantasyStatFileLoader.h"
#include "ASBasketballType.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class OffGameStatFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;
	TBasketballPosition fPos;
	TRosterStatus fRosterStatus;

	TOffGameStatDetail fStatDetail;

	// don't clear
	TStatPeriod fStatPeriod;
	TDateTime fStatDate;
	bool fAddNewPlayers;
	
public:
	OffGameStatFileLine(const TStatPeriod statPeriod,const TDateTime statDate,
		const bool addNewPlayers) : fStatPeriod(statPeriod),fStatDate(statDate),
		fAddNewPlayers(addNewPlayers) {}

	virtual void clear();
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual void process();
};

/******************************************************************************/

class OffGameStatFileLoader : public StatFileLoader
{
protected:
	TStatPeriod fStatPeriod;
	bool fAddNewPlayers;
	
protected:
	OffGameStatFileLoader(const DirSpec& dirSpec,const TDateTime fileNameDate,
		const TStatPeriod statPeriod,const bool addNewPlayers) :
		StatFileLoader(dirSpec,"asbk","pla",fileNameDate),
		fStatPeriod(statPeriod),fAddNewPlayers(addNewPlayers) {}
	virtual ~OffGameStatFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate,const TStatPeriod statPeriod,
		const bool addNewPlayers) { return(new OffGameStatFileLoader(dirSpec,
		fileNameDate,statPeriod,addNewPlayers)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new OffGameStatFileLine(fStatPeriod,fFileNameDate,
			fAddNewPlayers)); }
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballStatFileLoaderH
/******************************************************************************/
/******************************************************************************/
