/* ASBaseballPlayerScoutRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBaseballPlayerScoutRqstH
#define ASBaseballPlayerScoutRqstH

#include "ASBaseballType.h"
#include "ASFantasyPlayerScoutRqst.h"

using namespace asfantasy;

namespace asbaseball
{

/******************************************************************************/

class ASBaseballPlayerScoutRqst : public PlayerScoutRqst
{
protected:
	virtual PlayerStatValue getDefaultPlayerStatValue(int playerStatType);
	virtual bool isPlayerStatTypeOffensive(int playerStatType);
	virtual bool isPlayerStatTypeDefensive(int playerStatType);
};

/******************************************************************************/

}; //namespace asbaseball

#endif //ASBaseballPlayerScoutRqstH
/******************************************************************************/
/******************************************************************************/ 
