/* IsHttpAuthOptions.h */

/******************************************************************************/
/******************************************************************************/
#ifndef IsHttpAuthOptionsH
#define IsHttpAuthOptionsH

#include "ASMemberType.h"

typedef asmember::TMemberID IHAUserID;
typedef tag::TPassword IHAPassword;

#define MAX_IHA_SIZE		256

const char *gDLLName = "ASMHttpAuth";
const char *gDLLDescription = "ASMember Http Authentication DLL";
const char *gCommErrFileName = "C:\\Program Files\\ASMember\\ASMHttpAuth.out";
const char *gDatabaseName = "ASMember";
const char *gTableName = "Member";
const char *gUserIDFieldName = "MemberID";
const char *gPasswordFieldName = "Passwd";

const char* gAuthUserID = "iusr_mmpicks";	//BOB change to iusr_secure
const char* gAuthPassword = "hoops";

#endif //IsHttpAuthOptionsH
/******************************************************************************/
/******************************************************************************/
