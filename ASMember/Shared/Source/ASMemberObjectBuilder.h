/* ASMemberObjectBuilder.h*/

/******************************************************************************/
/******************************************************************************/
#ifndef ASMemberObjectBuilderH
#define ASMemberObjectBuilderH

#include "ObjectBuilder.h"
#include "ASMemberType.h"

namespace asmember
{

/******************************************************************************/

/* ASMemberObjectBuilder Types */
const CStr31 mobt_TMember("TMember");
const CStr31 mobt_TPartic("TPartic");
const CStr31 mobt_TPayHistory("TPayHistory");

/******************************************************************************/

class ASMemberObjectBuilder : public ObjectBuilder
{
protected:
	ASMemberObjectBuilder() {}
	
public:
	static ASMemberObjectBuilder& getThe()
		{ return(dynamic_cast<ASMemberObjectBuilder&>(ObjectBuilder::getThe())); }

	virtual void* newInstance(const char* type);

	/* Helper Functions */
	TMemberPtr newMember()
		{ return(TMemberPtr(static_cast<TMember*>(newInstance(mobt_TMember)))); }
		
	TParticPtr newPartic()
		{ return(TParticPtr(static_cast<TPartic*>(newInstance(mobt_TPartic)))); }

	TPayHistoryPtr newPayHistory()
		{ return(TPayHistoryPtr(static_cast<TPayHistory*>(newInstance(mobt_TPayHistory)))); }

	friend ObjectBuilder& tag::getTheObjectBuilder();
};

/******************************************************************************/

}; //namespace tag

#endif //ASMemberObjectBuilderH
/******************************************************************************/
/******************************************************************************/

