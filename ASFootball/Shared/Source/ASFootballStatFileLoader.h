/* ASFootballStatFileLoader.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballStatFileLoaderH
#define ASFootballStatFileLoaderH

#include "ASFantasyStatFileLoader.h"
#include "ASFootballType.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class PlayerInfoStatFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TFootballPosition fPos;
	TProfTeamID fProfTeamID;
	
	TCollegeName fCollegeName;
	short fYearsPro;

	TDateTime fLastUpdated;
	TInjuryStatus fInjuryStatus;
	TRosterStatus fRosterStatus;
	
public:
	virtual void clear();
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual void process();
};

/******************************************************************************/

class PlayerInfoStatFileLoader : public StatFileLoader
{
public:
	PlayerInfoStatFileLoader(const DirSpec& dirSpec,const TDateTime fileNameDate) :
		StatFileLoader(dirSpec,"asfb","sta",fileNameDate) {}
	virtual ~PlayerInfoStatFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate)
		{ return(new PlayerInfoStatFileLoader(dirSpec,fileNameDate)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new PlayerInfoStatFileLine()); }
};

/******************************************************************************/
/******************************************************************************/

class OffGameStatFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TFootballPosition fPos;
	TProfTeamID fProfTeamID;

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
protected:
	void readYardageBucketsFromFiler(TDataFiler& filer,
		YardageBuckets& yardageBuckets);
public:
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
		StatFileLoader(dirSpec,"asfb","off",fileNameDate),
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
	TRegionName fRegionName;
	TTeamName fTeamName;
	TProfTeamID fProfTeamID;

	TDefGameStatDetail fStatDetail;

	// don't clear
	TStatPeriod fStatPeriod;
	TDateTime fStatDate;
	bool fSkipUnknownPlayers;
		
public:
	DefGameStatFileLine(const TStatPeriod statPeriod,const TDateTime statDate,
		const bool skipUnknownPlayers) : fStatPeriod(statPeriod),
		fStatDate(statDate),fSkipUnknownPlayers(skipUnknownPlayers) {}
	
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
	bool fSkipUnknownPlayers;
	
protected:
	DefGameStatFileLoader(const DirSpec& dirSpec,const TDateTime fileNameDate,
		const TStatPeriod statPeriod,const bool skipUnknownPlayers) :
		StatFileLoader(dirSpec,"asfb","def",fileNameDate),
		fStatPeriod(statPeriod),fSkipUnknownPlayers(skipUnknownPlayers) {}
	virtual ~DefGameStatFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate,const TStatPeriod statPeriod,
		const bool skipUnknownPlayers) { return(new DefGameStatFileLoader(
		dirSpec,fileNameDate,statPeriod,skipUnknownPlayers)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new DefGameStatFileLine(fStatPeriod,fFileNameDate,
			fSkipUnknownPlayers)); }
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballStatFileLoaderH
/******************************************************************************/
/******************************************************************************/
