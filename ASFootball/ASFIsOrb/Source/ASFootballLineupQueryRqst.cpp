/* ASFootballLineupQueryRqst.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballType.h"
#include "ASFootballObjectStore.h"
#include "ASFootballLineupQueryRqst.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

ASFootballLineupPlayer::ASFootballLineupPlayer(
	const TProfPlayerPtr profPlayerPtr,
	TFootballProfTeamSchedulePtr profTeamSchedulePtr) :
	LineupPlayer(profPlayerPtr)
{
	ASFootballObjectStore& store = ASFootballObjectStore::getThe();
	const TFootballProfPlayerPtr footballProfPlayerPtr =
		TFootballProfPlayerPtr(profPlayerPtr);
	TProfTeamPtr profTeamPtr;
	TProfTeamGame profTeamGame;

	if(!profTeamSchedulePtr.isNull())	//will be NULL during Playoffs
	{
		if(profTeamSchedulePtr->getProfTeamGameByProfTeamID(
			profPlayerPtr->getProfTeamID(),profTeamGame))
		{
			if(profPlayerPtr->getProfTeamID() == profTeamGame.getHomeTeamID())
				fOppProfTeamGame.Copy("vs ");
			else
				fOppProfTeamGame.Copy("at ");
			
			profTeamPtr = store.getProfTeam(profTeamGame.getOppTeamID(
				profPlayerPtr->getProfTeamID()),ObjectStore::gim_MustExist);

			fOppProfTeamGame.Concat(profTeamPtr->getProfTeamAbbr());
		}
		else
			fOppProfTeamGame.Copy("bye");
	}
}

/******************************************************************************/

void ASFootballLineupPlayer::clear()
{
	LineupPlayer::clear();

	fOppProfTeamGame.Clear();
}

/******************************************************************************/

void ASFootballLineupPlayer::readFromFiler(TDataFiler& filer)
{
	throw ASIException("ASFootballLineupPlayer::readFromFiler: not supported");
}

/******************************************************************************/

void ASFootballLineupPlayer::writeToFiler(TDataFiler& filer)
{
	LineupPlayer::writeToFiler(filer);

	filer.writeString(fOppProfTeamGame.c_str());
}

/******************************************************************************/
/******************************************************************************/

void ASFootballLineupQueryRqst::fillPlayerIDArray(const TTeamPtr teamPtr,
	std::vector<TPlayerIDVector>& playerIDArray)
{
	playerIDArray.push_back(teamPtr->lineupConst(lut_Starting));
}

/******************************************************************************/

TFootballProfTeamSchedulePtr ASFootballLineupQueryRqst::getProfTeamSchedulePtr()
{
	if(!fIsProfTeamScheduleLoaded)
	{
		ASFootballObjectStore& store = ASFootballObjectStore::getThe();

		fProfTeamSchedulePtr = store.findCurrentProfTeamScheduleAsOfToday(
			cam_MayNotExist);	// Will be NULL during Playoffs
		fIsProfTeamScheduleLoaded = true;
	}

	return(fProfTeamSchedulePtr);
}

/******************************************************************************/

}; //asfootball

/******************************************************************************/
/******************************************************************************/
