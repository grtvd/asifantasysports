/* ASFootballObjectShelf.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFootballObjectShelf.h"

namespace asfootball
{

/******************************************************************************/
/******************************************************************************/

TFootballProfTeamSchedulePtr ProfTeamScheduleObjectShelf::findByContainsGameDate(
	TDateTime gameDate,CommonAccessMode getMode)
{
	TFootballProfTeamScheduleVector profTeamScheduleVector;

	getItemVector(profTeamScheduleVector);
	return(profTeamScheduleVector.findByContainsGameDate(gameDate,getMode));
}

/******************************************************************************/

TFootballProfTeamSchedulePtr ProfTeamScheduleObjectShelf::findCurrentAsOfToday(
	CommonAccessMode getMode)
{
	TFootballProfTeamScheduleVector profTeamScheduleVector;

	getItemVector(profTeamScheduleVector);
	return(profTeamScheduleVector.findCurrentAsOfToday(getMode));
}

/******************************************************************************/

}; //namespace asfootball

/******************************************************************************/
/******************************************************************************/
