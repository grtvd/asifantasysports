/* ICVerifySaleResp.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ICVerifySaleRespH
#define ICVerifySaleRespH

using namespace tag;

namespace asmember
{

/******************************************************************************/

class TICVerifySaleResp : public TStreamable
{
protected:
	CStrVar fResponse;

public:
	TICVerifySaleResp() : TStreamable() {}
	virtual ~TICVerifySaleResp() {}

	virtual void readFromFiler( TDataFiler& filer );
	virtual void writeToFiler( TDataFiler& filer );

	const char* getResponse() { return (fResponse); };
	bool isApproved();
	const char* getReference();
};

/******************************************************************************/

}; //namespace asmember

#endif //ICVerifySaleRespH
/******************************************************************************/
/******************************************************************************/
