/* ASFootballUtilManager.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballUtilManagerH
#define ASFootballUtilManagerH

#include "ASFantasyUtilManager.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballUtilManager : public ASFantasyUtilManager
{
protected:
	virtual void promptChoices();
	virtual bool doesChoiceNeedTransaction(int choice);
	virtual void doChoice(int choice);

	virtual int getNumCompAccountInfo();
	virtual const CompAccountInfo* getCompAccountInfo(int offset);
};

/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballUtilManagerH
/******************************************************************************/
/******************************************************************************/
