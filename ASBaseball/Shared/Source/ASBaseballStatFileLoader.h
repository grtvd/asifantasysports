/* ASBaseballStatFileLoader.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballStatFileLoaderH
#define ASBaseballStatFileLoaderH

#include "ASFantasyStatFileLoader.h"
#include "ASBaseballType.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class PlayerRosterFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;

	TBaseballPosition fPosPrimary;
	TBaseballPosition fPosSecondary;

	TRosterStatus fRosterStatus;
	
public:
	virtual void clear();
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual void process();
};

/******************************************************************************/

class PlayerRosterFileLoader : public StatFileLoader
{
protected:
	PlayerRosterFileLoader(const DirSpec& dirSpec,const TDateTime fileNameDate) :
		StatFileLoader(dirSpec,"asbb","ros",fileNameDate) {}
	virtual ~PlayerRosterFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate)
		{ return(new PlayerRosterFileLoader(dirSpec,fileNameDate)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new PlayerRosterFileLine()); }
};

/******************************************************************************/
/******************************************************************************/

class OffGameStatFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;
	TBaseballPosition fPos;

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
		StatFileLoader(dirSpec,"asbb","hit",fileNameDate),
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
	TBaseballPosition fPos;

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
		StatFileLoader(dirSpec,"asbb","pit",fileNameDate),
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
/******************************************************************************/

class InjuryFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;

	TRosterStatus fRosterStatus;
	TDateTime fStatusDate;
	CStrVar fNotes;

public:
	virtual void clear();
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual void process();
};

/******************************************************************************/

class InjuryFileLoader : public StatFileLoader
{
protected:
	InjuryFileLoader(const DirSpec& dirSpec,const TDateTime fileNameDate) :
		StatFileLoader(dirSpec,"asbb","inj",fileNameDate) {}
	virtual ~InjuryFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate)
		{ return(new InjuryFileLoader(dirSpec,fileNameDate)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new InjuryFileLine()); }
};

/******************************************************************************/
/******************************************************************************/

class TransactionFileLine : public StatFileLine
{
protected:
	TFullName fFullName;
	TPlayerID fPlayerID;
	TProfTeamID fProfTeamID;

	TRosterStatus fRosterStatus;
	TDateTime fStatusDate;
	CStrVar fNotes;

public:
	virtual void clear();
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	virtual void process();
};

/******************************************************************************/

class TransactionFileLoader : public StatFileLoader
{
protected:
	TransactionFileLoader(const DirSpec& dirSpec,const TDateTime fileNameDate) :
		StatFileLoader(dirSpec,"asbb","trn",fileNameDate) {}
	virtual ~TransactionFileLoader() {}

public:
	static StatFileLoaderPtr newInstance(const DirSpec& dirSpec,
		const TDateTime fileNameDate)
		{ return(new TransactionFileLoader(dirSpec,fileNameDate)); }

protected:
	virtual StatFileLine* newLineInstance()
		{ return(new TransactionFileLine()); }
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballStatFileLoaderH
/******************************************************************************/
/******************************************************************************/
