/* ASFantasyStatFileLoader.h */

/******************************************************************************/
/******************************************************************************/
#ifndef ASFantasyStatFileLoaderH
#define ASFantasyStatFileLoaderH

#include "CommDir.h"
#include "RefCountObject.h"
#include "Streamable.h"

using namespace tag;

namespace asfantasy
{

/******************************************************************************/

class StatFileLine : public TStreamable
{
public:
	virtual void clear() = 0;
	virtual void readFromFiler(TDataFiler& filer) = 0;
	virtual void writeToFiler(TDataFiler& filer) = 0;

	virtual void process() = 0;
};

/******************************************************************************/

class StatFileLoader;	//forward reference
typedef RefCountPtr<StatFileLoader> StatFileLoaderPtr;

class StatFileLoader : public RefCountObject
{
protected:
	DirSpec fDirSpec;
	CStr31 fAppFileName;
	CStr31 fSubFileName;
	TDateTime fFileNameDate;
	
protected:
	StatFileLoader(const DirSpec& dirSpec,const char* appFileName,
		const char* subFileName,const TDateTime fileNameDate) :
		fDirSpec(dirSpec),fAppFileName(appFileName),fSubFileName(subFileName),
		fFileNameDate(fileNameDate) {}
	virtual ~StatFileLoader() {}

private:
	StatFileLoader(const StatFileLoader&);						// don't allow copy constructor
	const StatFileLoader& operator=(const StatFileLoader&);		// or operator=

public:
	void setDirSpec(const DirSpec& dirSpec)
		{ fDirSpec = dirSpec; }
	void setFileNameDate(const TDateTime fileNameDate)
		{ fFileNameDate = fileNameDate; }
		
protected:
	virtual StatFileLine* newLineInstance() = 0;
	
public:
	FileNameSpec buildFileName() const;
	CStrVar buildFullFileNameInDir(const DirSpec& dirSpec) const;
	CStrVar buildFullFileName() const;

	bool doesFileExist() const;
	bool doesFileExistInDir(const DirSpec& dirSpec) const;
	void load();

	friend class RefCountPtr<StatFileLoader>;
};

typedef std::vector<StatFileLoaderPtr> StatFileLoaderVector;

/******************************************************************************/

}; //namespace asfantasy

#endif //ASFantasyStatFileLoaderH
/******************************************************************************/
/******************************************************************************/

