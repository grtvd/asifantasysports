/* ASBasketballUtilManager.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballUtilManagerH
#define ASBasketballUtilManagerH

#include "ASFantasyUtilManager.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballUtilManager : public ASFantasyUtilManager
{
protected:
	virtual void promptChoices();
	virtual bool doesChoiceNeedTransaction(int choice);
	virtual void doChoice(int choice);

	virtual int getNumCompAccountInfo();
	virtual const CompAccountInfo* getCompAccountInfo(int offset);
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballUtilManagerH
/******************************************************************************/
/******************************************************************************/
