/* ASMemberType.h */

/******************************************************************************/
/******************************************************************************/
#ifndef CreditCardVerifyH
#define CreditCardVerifyH

#include "ASMemberType.h"

using namespace asmember;

/******************************************************************************/

bool validateCCardNumber( TCCardNumber& inputCardNum, TCreditCardTypeEnum cardType );
bool cCardMod10( const char * cardNum );

/******************************************************************************/

#endif //CreditCardVerifyH
/******************************************************************************/
/******************************************************************************/

