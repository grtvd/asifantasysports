/* ASMemberDB.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASMemberDBH
#define ASMemberDBH

#include "ASMemberType.h"

namespace asmember
{

/******************************************************************************/

double GamePrice(const TMemberID memberID,bool isPremium);
double UpgradePrice(const TParticPtr particPtr);

void LoadParticVectorByParticIDVector(const TParticIDVector& particIDVector,
	TParticVector& particVector);
void LoadParticVectorByMemberIDGameID(const TMemberID memberID,
	const TGameID gameID,TParticVector& particVector);

/******************************************************************************/

}; //namespace asmember

#endif //ASMemberDBH
/******************************************************************************/
/******************************************************************************/
 
