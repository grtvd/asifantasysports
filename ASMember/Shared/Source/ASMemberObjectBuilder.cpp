/* ASMemberObjectBuilder.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASMemberObjectBuilder.h"
#include "ASMemberType.h"

using namespace asmember;

/******************************************************************************/
/******************************************************************************/
#if defined(USE_ASMEMBER_ONLY)

// Declared in ObjectBuilder.h, used to implement Singleton in derived classes.

ObjectBuilder& tag::getTheObjectBuilder()
{
	static ASMemberObjectBuilder builder;
	return(builder);
}

#endif
/******************************************************************************/
/******************************************************************************/

void* ASMemberObjectBuilder::newInstance(const char* type)
{
	if(mobt_TMember == type)
		return(new TMember);

	if(mobt_TPartic == type)
		return(new TPartic);
		
	if(mobt_TPayHistory == type)
		return(new TPayHistory);

	if(obt_TSendMail == type)
		return(new TASMemberSendMail);

	if(obt_TErrorLog == type)
		return(new TASMemberErrorLog);

	return(ObjectBuilder::newInstance(type));
}

/******************************************************************************/
/******************************************************************************/
