/* ASFantasyNewMemberSignupRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyNewMemberSignupRqstH
#define ASFantasyNewMemberSignupRqstH

#include "ASFantasyNewSignupRqst.h"

namespace asfantasy
{

/******************************************************************************/

class ASFantasyNewMemberSignupRqst : public ASFantasyNewSignupRqst
{
private:
	TMemberSignupSource fSignupSource;

	/* User Info */
	TPassword fPassword;
	TPassword fReEnteredPassword;
	
public:
	void setSignupSource(const char* signupSource) { fSignupSource = signupSource; }

	void setPassword(const char* password) { fPassword = password; }
	void setReEnteredPassword(const char* password) { fReEnteredPassword = password; }
	
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);
	
	virtual ASFantasyNewSignupResp* fulfillRequest();

protected:
	virtual void validateRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyNewMemberSignupRqstH
/******************************************************************************/
/******************************************************************************/
