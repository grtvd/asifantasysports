/* ASBasketballPlayerScoutRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASBasketballPlayerScoutRqstH
#define ASBasketballPlayerScoutRqstH

#include "ASBasketballType.h"
#include "ASFantasyPlayerScoutRqst.h"

using namespace asfantasy;

namespace asbasketball
{

/******************************************************************************/

class ASBasketballPlayerScoutRqst : public PlayerScoutRqst
{
protected:
	virtual PlayerStatValue getDefaultPlayerStatValue(int playerStatType);
	virtual bool isPlayerStatTypeOffensive(int playerStatType);
	virtual bool isPlayerStatTypeDefensive(int playerStatType);
};

/******************************************************************************/

}; //namespace asbasketball

#endif //ASBasketballPlayerScoutRqstH
/******************************************************************************/
/******************************************************************************/ 
