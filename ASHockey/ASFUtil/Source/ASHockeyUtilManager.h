/* ASHockeyUtilManager.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyUtilManagerH
#define ASHockeyUtilManagerH

#include "ASFantasyUtilManager.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyUtilManager : public ASFantasyUtilManager
{
protected:
	virtual void promptChoices();
	virtual bool doesChoiceNeedTransaction(int choice);
	virtual void doChoice(int choice);

	virtual int getNumCompAccountInfo();
	virtual const CompAccountInfo* getCompAccountInfo(int offset);
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyUtilManagerH
/******************************************************************************/
/******************************************************************************/
