/* ParticUpgradeRqst.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ParticUpgradeRqstH
#define ParticUpgradeRqstH

#include "NewSignupRqst.h"

using namespace tag;
using namespace asmember;

namespace asfantasy
{

/******************************************************************************/

class ParticUpgradeRqst : public NewSignupRqst
{
protected:
	TParticID fParticID;

public:
	virtual void readFromFiler(TDataFiler& filer);
	virtual void writeToFiler(TDataFiler& filer);

	void setParticID(TParticID particID) { fParticID = particID; }
	
	virtual NewSignupResp* fulfillRequest();

protected:
	virtual void validateRequest();
};

/******************************************************************************/

}; //namespace asfantasy

#endif
/******************************************************************************/
/******************************************************************************/
