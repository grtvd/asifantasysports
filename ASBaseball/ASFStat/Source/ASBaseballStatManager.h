/* ASBaseballStatManager.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballStatManagerH
#define ASBaseballStatManagerH

#include "CommType.h"

#include "ASBaseballStatFileLoader.h"

using namespace tag;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballStatManager
{
public:
	void run(void);

protected:
	void mainLoop();
	void doChoice(int choice);
	TStatPeriod promptStatPeriod();
	void loadStat(StatFileLoaderPtr loader);
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballStatManagerH
/******************************************************************************/
/******************************************************************************/
