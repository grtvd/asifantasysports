/* ASHockeyStatFileLoader.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyStatFileLoaderH
#define ASHockeyStatFileLoaderH

#include "ASFantasyStatFileLoader.h"
#include "ASHockeyType.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class OffGameStatFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;
	THockeyPosition fPos;
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
		StatFileLoader(dirSpec,"asfh","pla",fileNameDate),
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
/******************************************************************************/

class DefGameStatFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;
	TRosterStatus fRosterStatus;

	TDefGameStatDetail fStatDetail;

	// don't clear
	TStatPeriod fStatPeriod;
	TDateTime fStatDate;
	bool fAddNewPlayers;
	
public:
	DefGameStatFileLine(const TStatPeriod statPeriod,const TDateTime statDate,
		const bool addNewPlayers) : fStatPeriod(statPeriod),fStatDate(statDate),
		fAddNewPlayers(addNewPlayers) {}
	
	virtual void clear();
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual void process();
};

/******************************************************************************/

class DefGameStatFileLoader : public StatFileLoader
{
protected:
	TStatPeriod fStatPeriod;
	bool fAddNewPlayers;
	
protected:
	DefGameStatFileLoader(const DirSpec& dirSpec,TDateTime fileNameDate,
		const TStatPeriod statPeriod,const bool addNewPlayers) :
		StatFileLoader(dirSpec,"asfh","goa",fileNameDate),
		fStatPeriod(statPeriod),fAddNewPlayers(addNewPlayers) {}
	virtual ~DefGameStatFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate,const TStatPeriod statPeriod,
		const bool addNewPlayers) { return(new DefGameStatFileLoader(dirSpec,
		fileNameDate,statPeriod,addNewPlayers)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new DefGameStatFileLine(fStatPeriod,fFileNameDate,
			fAddNewPlayers)); }
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyStatFileLoaderH
/******************************************************************************/
/******************************************************************************/
