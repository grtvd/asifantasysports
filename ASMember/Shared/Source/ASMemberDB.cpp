/* ASMemberDB.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "CommDB.h"
#include "ASMemberDB.h"

namespace asmember
{

/******************************************************************************/

static void LoadParticVectorByWhereStr(const char* whereStr,
	TParticVector& particVector);

/******************************************************************************/
/******************************************************************************/

double GamePrice(const TMemberID memberID,bool isPremium)
{
	TParticVector particVector;

	if(!memberID.isUndefined())
	{
		if(ParticGamePriceAllowedForMembers())
		{
			if(isPremium)
				return(GamePriceParticPremium());

			return(GamePriceParticStandard());
		}

		LoadParticVectorByMemberIDGameID(memberID,CurrentGameID(),particVector);

		if(particVector.size() > 0)
		{
			if(isPremium)
				return(GamePriceParticPremium());

			return(GamePriceParticStandard());
		}
	}

	if(isPremium)
		return(GamePriceMemberPremium());

	return(GamePriceMemberStandard());
}

/******************************************************************************/

double UpgradePrice(const TParticPtr particPtr)
{
	TParticVector particVector;
	double gamePrice = GamePriceMemberPremium();

	LoadParticVectorByMemberIDGameID(particPtr->getMemberID(),CurrentGameID(),
		particVector);
	particVector.sortByID();

	if(particVector.size() > 0)	//should never equal 0
		if(particVector[0]->getParticID() != particPtr->getParticID())
			gamePrice = GamePriceParticPremium();

	return(gamePrice - particPtr->getGamePrice());	//deduct already paid
}

/******************************************************************************/
/******************************************************************************/

void LoadParticVectorByWhereStr(const char* whereStr,TParticVector& particVector)
{
	TQuery* pQuery = NULL;
	CStrVar str;
	TParticPtr particPtr;

	// Find all Partics
	try
	{
		particVector.erase(particVector.begin(),particVector.end());
		
		str.copy("select * from Partic");
		if(tStrHasLen(whereStr))
			str.concatVarg(" where %s",whereStr);
		pQuery = OpenQuery(MemberDatabaseName(),str.c_str());
		
		pQuery->First();
		while(!pQuery->Eof)
		{
			particPtr = TPartic::newInstance();
			particPtr->load(*pQuery);
			particVector.push_back(particPtr);
			
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

void LoadParticVectorByParticIDVector(const TParticIDVector& particIDVector,
	TParticVector& particVector)
{
	TParticIDVector::const_iterator iter;
	CStrVar str;
	CStrVar idStr;

	if(particIDVector.size() == 0)
	{
		particVector.erase(particVector.begin(),particVector.end());
		return;
	}

	for(iter = particIDVector.begin(); iter != particIDVector.end(); iter++)
	{
		if(idStr.hasLen())
			idStr.concat(",");
		idStr.concat((*iter).c_str());
	}

	str.copyVarg("ParticID in (%s)",idStr.c_str());
	LoadParticVectorByWhereStr(str,particVector);
}

/******************************************************************************/

void LoadParticVectorByMemberIDGameID(const TMemberID memberID,
	const TGameID gameID,TParticVector& particVector)
{
	CStrVar str;

	str.copyVarg("((MemberID = \"%s\")",memberID.c_str());
	str.concatVarg("and (GameID = \"%s\"))",gameID.c_str());
	LoadParticVectorByWhereStr(str,particVector);
}

/******************************************************************************/

};	// namespace asmember

/******************************************************************************/
/******************************************************************************/
