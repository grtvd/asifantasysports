/* ASFantasyStatFileLoader.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "PipeTextFiler.h"
#include "ASFantasyStatFileLoader.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

FileNameSpec StatFileLoader::buildFileName() const
{
	FileNameSpec fileNameSpec;

	fileNameSpec.CopyVarg("%s_%s_%s.txt",fAppFileName.c_str(),
		fSubFileName.c_str(),
		const_cast<TDateTime&>(fFileNameDate).FormatString("yyyymmdd").c_str());

	return(fileNameSpec);
}

/******************************************************************************/

CStrVar StatFileLoader::buildFullFileNameInDir(const DirSpec& dirSpec) const
{
	return(BuildFullFileName(dirSpec,buildFileName()));
}

/******************************************************************************/

CStrVar StatFileLoader::buildFullFileName() const
{
	return(buildFullFileNameInDir(fDirSpec));
}

/******************************************************************************/

bool StatFileLoader::doesFileExistInDir(const DirSpec& dirSpec) const
{
	return(tDoesFileExistInDir(dirSpec,buildFileName().c_str()));
}

/******************************************************************************/

bool StatFileLoader::doesFileExist() const
{
	return(doesFileExistInDir(fDirSpec));
}

/******************************************************************************/

void StatFileLoader::load()
{
	auto_ptr<TFileStream> fileStream;
	auto_ptr<TPipeTextFiler> dataFiler;
	CStrVar fullFileName;
	auto_ptr<StatFileLine> pLine;
	
	fullFileName = buildFullFileName();
	
	fileStream.reset(new TFileStream(fullFileName.c_str(),fmOpenRead | fmShareExclusive));
	dataFiler.reset(new TPipeTextFiler(fileStream.release(),true));

	pLine.reset(newLineInstance());

	while(dataFiler->isMoreDataAvailable())
	{
		pLine->clear();
		pLine->readFromFiler(*dataFiler);
		dataFiler->readEOL();
		
		pLine->process();
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
