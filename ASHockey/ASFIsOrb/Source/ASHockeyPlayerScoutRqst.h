/* ASHockeyPlayerScoutRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASHockeyPlayerScoutRqstH
#define ASHockeyPlayerScoutRqstH

#include "ASHockeyType.h"
#include "ASFantasyPlayerScoutRqst.h"

using namespace asfantasy;

namespace ashockey
{

/******************************************************************************/

class ASHockeyPlayerScoutRqst : public PlayerScoutRqst
{
protected:
	virtual PlayerStatValue getDefaultPlayerStatValue(int playerStatType);
	virtual bool isPlayerStatTypeOffensive(int playerStatType);
	virtual bool isPlayerStatTypeDefensive(int playerStatType);
};

/******************************************************************************/

}; //namespace ashockey

#endif //ASHockeyPlayerScoutRqstH
/******************************************************************************/
/******************************************************************************/ 
