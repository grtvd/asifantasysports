/* PVVOptions.h */

/******************************************************************************/
/******************************************************************************/
#ifndef PVVOptionsH
#define PVVOptionsH

#include "ASFantasyType.h"

#if 0
class PVVUserID : public tag::TParticID
{
public:
	PVVUserID() {}
	PVVUserID(const char* userID) { fID = atoi(userID); }
	const char* c_str() const { return(AnsiString((int)fID).c_str()); }
};
#endif
typedef tag::TMemberID PVVUserID;
typedef tag::TPassword PVVPassword;

#define MAX_PVV_SIZE		256

const char *gDatabaseName = "ASMember";
const char *gTableName = "Member";
const char *gUserIDFieldName = "MemberID";
const char *gPasswordFieldName = "Passwd";

#endif //PVVOptionsH
/******************************************************************************/
/******************************************************************************/

