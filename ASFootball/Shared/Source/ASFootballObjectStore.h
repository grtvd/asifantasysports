/* ASFootballObjectStore.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballObjectStoreH
#define ASFootballObjectStoreH

#include "ASFantasyObjectStore.h"
#include "ASFootballObjectBuilder.h"
#include "ASFootballObjectShelf.h"

/******************************************************************************/

namespace asfootball
{

/******************************************************************************/

class ASFootballObjectStore : public ASFantasyObjectStore
{
private:
	ASFootballObjectStore(ASFootballObjectBuilder& builder);

public:
	static ASFootballObjectStore& getThe()
		{ return(dynamic_cast<ASFootballObjectStore&>(ASFantasyObjectStore::getThe())); }
	ASFootballObjectBuilder& getBuilder()
		{ return(dynamic_cast<ASFootballObjectBuilder&>(fBuilder)); }

	/**************************************************************************/
	
	// Functions to retrieve ObjectShelfKeys
	virtual ObjectShelfKeyType getProfTeamScheduleShelfKey(void)
		{ return(typeid(TFootballProfTeamSchedulePtr).name()); }

	// ObjectShelf Functions
	ProfTeamScheduleObjectShelf* getProfTeamScheduleShelf()
		{ return(dynamic_cast<ProfTeamScheduleObjectShelf*>
			(getShelfByKey(getProfTeamScheduleShelfKey(),gsm_MustExist))); }
	void addProfTeamScheduleShelf();
	void delProfTeamScheduleShelf() { delShelf(getProfTeamScheduleShelfKey()); }
	void delAllProfTeamScheduleShelfItems();

	/**************************************************************************/

	// ProfTeamSchedule Retrieval Functions
	void addProfTeamSchedule(TFootballProfTeamSchedulePtr profTeamSchedulePtr);
	TFootballProfTeamSchedulePtr getProfTeamSchedule(TProfGameWeek profGameWeek,
		GetItemMode getItemMode = gim_MustExist);
	void delProfTeamSchedule(TProfGameWeek profGameWeek);
	
	/**************************************************************************/
	// Utility Methods

	void loadAllProfTeamSchedules();
	
	void getProfTeamScheduleVector(TFootballProfTeamScheduleVector& profTeamScheduleVector)
		{ getProfTeamScheduleShelf()->getItemVector(profTeamScheduleVector); }

	TFootballProfTeamSchedulePtr findProfTeamScheduleByContainsGameDate(
		TDateTime gameDate,CommonAccessMode getMode)
		{ return(getProfTeamScheduleShelf()->findByContainsGameDate(gameDate,
			getMode)); }
	TFootballProfTeamSchedulePtr findCurrentProfTeamScheduleAsOfToday(
		CommonAccessMode getMode)
		{ return(getProfTeamScheduleShelf()->findCurrentAsOfToday(getMode)); }

	/**************************************************************************/
		
	friend ObjectStore& tag::getTheObjectStore();
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballObjectStoreH
/******************************************************************************/
/******************************************************************************/


