/* ASFantasyNewParticSignupRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyNewParticSignupRqstH
#define ASFantasyNewParticSignupRqstH

#include "ASFantasyNewSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyNewParticSignupRqst : public ASFantasyNewSignupRqst
{
public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual ASFantasyNewSignupResp* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif
/******************************************************************************/
/******************************************************************************/
