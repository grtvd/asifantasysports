/* ASFootballPlayerScoutRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFootballPlayerScoutRqstH
#define ASFootballPlayerScoutRqstH

#include "ASFootballType.h"
#include "ASFantasyPlayerScoutRqst.h"

using namespace asfantasy;

namespace asfootball
{

/******************************************************************************/

class ASFootballPlayerScoutRqst : public PlayerScoutRqst
{
protected:
	virtual PlayerStatValue getDefaultPlayerStatValue(int playerStatType);
	virtual bool isPlayerStatTypeOffensive(int playerStatType);
	virtual bool isPlayerStatTypeDefensive(int playerStatType);
};


/******************************************************************************/

}; //namespace asfootball

#endif //ASFootballPlayerScoutRqstH
/******************************************************************************/
/******************************************************************************/ 
