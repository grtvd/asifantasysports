/* ASFantasySignupLeagueListRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasySignupLeagueListRqstH
#define ASFantasySignupLeagueListRqstH

#include "Requestable.h"
#include "ASFantasyType.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class SignupLeagueListRqst : public TRequestable
{
protected:
	TLeagueName fPartialLeagueName;
	
protected:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
public:
	virtual TStreamable* fulfillRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasySignupLeagueListRqstH
/******************************************************************************/
/******************************************************************************/

