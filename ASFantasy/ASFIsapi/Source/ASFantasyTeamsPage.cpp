/* ASFantasyTeamsPage.cpp */

/******************************************************************************/
/******************************************************************************/

#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyDB.h"
#include "ASFantasyTeamsPage.h"

namespace asfantasy
{

/******************************************************************************/

void ASFantasyTeamsPageHtmlView::writeBodyViewBody()
{
	TMemberPtr memberPtr;
	TParticPtr particPtr;
	TTeamVector teamVector;
	TTeamVector::iterator iter;
	TTeamPtr teamPtr;
	CStrVar allEmailStr;

	if(!fPageOptions.isRqstLeagueSet())
	{
		fHtmlWriter.TableStart(SHOW_BORDER,THtmlWidthValue(getBodyViewWidth()));
		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableCellStart();
		fHtmlWriter.TextString("You are currently not in any League.  See ");
		TTextNavHTMLView::Build(fHtmlWriter,fPageOptions,htmlHubPage);
		fHtmlWriter.TextString(" for more details.");
		fHtmlWriter.TableCellEnd();
		fHtmlWriter.TableRowEnd();
		fHtmlWriter.TableEnd(); 
	}
	else
	{
		LoadTeamVectorByLeagueID(fPageOptions.getRqstLeague()->getLeagueID(),
			teamVector);
		teamVector.sortByName();
	
		fHtmlWriter.TableStart(2,THtmlWidthValue(getBodyViewWidth()),2,2);

		fHtmlWriter.TableRowStart();
		fHtmlWriter.TableHeading("Team");
		fHtmlWriter.TableHeading("Owner");
		fHtmlWriter.TableHeading("Email");
		fHtmlWriter.TableRowEnd();

		for(iter = teamVector.begin(); iter != teamVector.end(); iter++)
		{
			teamPtr = *iter;
			
			fHtmlWriter.TableRowStart();
			
			fHtmlWriter.TableCellStart();

			fHtmlWriter.TextString(teamPtr->getRegionName());
			fHtmlWriter.TextString(" ");
			fHtmlWriter.TextString(teamPtr->getTeamName());

			fHtmlWriter.TableCellEnd();
			
			fHtmlWriter.TableCellString(teamPtr->getManagerName());

			particPtr = TPartic::createGet(teamPtr->getParticID(),cam_MustExist);
			memberPtr = TMember::createGet(particPtr->getMemberID(),cam_MustExist);

			fHtmlWriter.TableCellStart();
			fHtmlWriter.WriteView(TMailToHtmlView(fPageOptions,memberPtr->getEmail()));
			fHtmlWriter.TableCellEnd();

			fHtmlWriter.TableRowEnd();

			if(fPageOptions.getRqstTeam()->getTeamID() != teamPtr->getTeamID())
			{
				if(allEmailStr.hasLen())
					allEmailStr.concat(",");
				allEmailStr.concat(memberPtr->getEmail());
			}
		}
		
		if(allEmailStr.hasLen())
		{
			fHtmlWriter.TableRowStart();
			fHtmlWriter.TableCellView(TMailToHtmlView(fPageOptions,allEmailStr,
				"Email to All"),0,3);
			fHtmlWriter.TableRowEnd();
		}

		fHtmlWriter.TableEnd(); 
	}
}

/******************************************************************************/

}; //namespace asfantasy

/******************************************************************************/
/******************************************************************************/
