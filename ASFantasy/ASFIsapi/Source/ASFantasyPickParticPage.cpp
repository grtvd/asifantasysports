/* ASFantasyPickParticPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyPickParticPage.h"

namespace asfantasy
{

/******************************************************************************/
/******************************************************************************/

void ASFantasyPickParticPageHtmlView::writeBodyView()
{
	const THTMLPageLinkInfo& pageLinkInfo(fPageOptions.getPageLinkInfo(htmlHubPage));
	TParticVector::const_iterator iter;
	CStr255 str;
	
	fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(ASFantasyStandardPageWidth()));

	if(fParticVector.size() > 0)
	{
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter);

//		fHtmlWriter.Heading(3,"Which Team would you like to access:");
		fHtmlWriter.FontStart(4,fcAbsolute,ASFantasyStandardFont());
		fHtmlWriter.TextEffect(efBold,"Which Team would you like to access:");
		fHtmlWriter.FontEnd();

		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();
		
		for(iter = fParticVector.begin(); iter != fParticVector.end(); iter++)
		{
			TTeamPtr teamPtr = TTeam::createGet((*iter)->getTeamID(),cam_MustExist);
			TLeaguePtr leaguePtr = (!teamPtr->getLeagueID().isUndefined() ?
				TLeague::createGet(teamPtr->getLeagueID(),cam_MustExist) : TLeaguePtr());
				
			fHtmlWriter.TableRowStart();
			fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter);

			str.Copy(teamPtr->getManagerName());
			str.Concat("'s ");
			str.Concat(teamPtr->getRegionName());
			str.Concat(" ");
			str.Concat(teamPtr->getTeamName());

			if(!leaguePtr.isNull())
			{
				str.Concat(" in the ");
				str.Concat(leaguePtr->getName());
				str.Concat(" League");
			}
			else
				str.Concat(" (not in any league)");
			
			fHtmlWriter.Link(pageLinkInfo.GetLinkURLToPartic(fPageOptions,*iter).c_str(),
				"", str.c_str());
			
			fHtmlWriter.TableCellEnd();
			fHtmlWriter.TableRowEnd();
		}
	}
	else
	{
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter);
		fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
		fHtmlWriter.TextEffect(efBold,"You are currently not signed up for any team.");
		fHtmlWriter.FontEnd();
		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();

		fHtmlWriter.TableRowStart();
		fHtmlWriter.WriteView(TEmptyTableCellHtmlView(fPageOptions,THtmlWidth(),
			THtmlHeightValue(10)));
		fHtmlWriter.TableRowEnd();

		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahCenter);
		fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
		fHtmlWriter.TextEffectStart(efBold);

		fHtmlWriter.TextString("Would you like to ");
		fHtmlWriter.WriteView(TSignupTextNavHtmlView(*this));
		fHtmlWriter.TextString(" for a new team?");

		fHtmlWriter.TextEffectEnd(efBold);
		fHtmlWriter.FontEnd();
		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();
	}
	
	fHtmlWriter.TableRowStart();
	fHtmlWriter.WriteView(TEmptyTableCellHtmlView(fPageOptions,THtmlWidth(),
		THtmlHeightValue(20)));
	fHtmlWriter.TableRowEnd();
	
	fHtmlWriter.TableEnd(); 
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
