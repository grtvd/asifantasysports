/* ASFootballDB.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASFootballDB.h"

namespace asfootball
{

/******************************************************************************/

static void LoadProfTeamScheduleVectorByWhereStr(const char* whereStr,
	TFootballProfTeamScheduleVector& profTeamScheduleVector);

/******************************************************************************/
/******************************************************************************/

void LoadProfTeamScheduleVectorByWhereStr(const char* whereStr,
	TFootballProfTeamScheduleVector& profTeamScheduleVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TFootballProfTeamSchedulePtr profTeamSchedulePtr;

	// Find all ProfTeamSchedules
	try
	{
		profTeamScheduleVector.erase(profTeamScheduleVector.begin(),
			profTeamScheduleVector.end());

		str.copy("select * from ProfTeamSchedule");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(PrimaryDatabaseName,str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			profTeamSchedulePtr = TFootballProfTeamSchedule::newInstance();
			profTeamSchedulePtr->load(*pQuery);
			profTeamScheduleVector.push_back(profTeamSchedulePtr);
			
			pQuery->Next();
		}

		CloseQuery(pQuery);
	}
	catch(const Exception& e)
	{
		CloseQuery(pQuery);
		throw ASIException(e.Message.c_str());
	}
	catch(...)
	{
		CloseQuery(pQuery);
		throw;
	}
}

/******************************************************************************/

void LoadProfTeamScheduleVector(TFootballProfTeamScheduleVector& profTeamScheduleVector)
{
	LoadProfTeamScheduleVectorByWhereStr("",profTeamScheduleVector);
}

/******************************************************************************/

};	// namespace asfootball

/******************************************************************************/
/******************************************************************************/


