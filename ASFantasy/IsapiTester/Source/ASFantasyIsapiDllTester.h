/* ASFantasyIsapiDllTester.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyIsapiDllTesterH
#define ASFantasyIsapiDllTesterH

#include "IsapiDllTester.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class ASFantasyIsapiDllLoader : public IsapiDllLoader
{
public:
	ASFantasyIsapiDllLoader(const char* isapiDllName,
		const char* remoteUser = "rdavidson",
		const DirSpec outputDir = DirSpec()) :
		IsapiDllLoader(isapiDllName,remoteUser,outputDir) {}

	virtual void printAllPages() const;
	virtual const char* getPageName(int pageNo) const;
	virtual bool isPageDataBinary(int pageNo) const;
	virtual const char* promptOther(int pageNo,bool repeatLast) const;
	virtual const char* promptUserID() const;
	virtual CStrVar promptEncodedPartic() const;
	virtual void promptBinaryFiler(int pageNo,TBinaryFiler &binaryFiler);
	virtual ulong promptBinaryData(int pageNo,void* lpbDataBuffer,
		ulong lpbDataBufferSize);
};

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyIsapiDllTesterH
/******************************************************************************/
/******************************************************************************/
