/* ParticPremiumTrialPage.cpp */

/******************************************************************************/
/******************************************************************************/
#include "CBldVCL.h"
#pragma hdrstop

#include "ASFantasyAppOptions.h"	//BOB refering to ASFantasy
#include "ParticPremiumTrialPage.h"

/******************************************************************************/
/******************************************************************************/

void ParticPremiumTrialGetPage::writeBodyRows()
{
	if(!PremiumTrialAvailable())
		throw ASIException("ParticPremiumTrialGetPage::writeBodyRows: trials are not available");

	fHtmlWriter.HiddenField(gURLUserFieldStr,
		fPageOptions.getPagePartic()->encodeParticID().c_str());

	writeBodyLineRow();
	writeBodySectionTextRow("You have selected to participate in the 1 week "
		"trial of the premium version. You will be able to upgrade to the "
		"premium version at anytime during the trial period. After the trial, "
		"if you have not upgraded, your team will be set back to the standard "
		"version.");

	writeBodyLineRow();
	writeBodySubmitLine();
}

/******************************************************************************/
/******************************************************************************/

void ParticPremiumTrialPostPage::initialize()
{
	TParticPtr particPtr;
	NewSignupBasePage::initialize();

	if(!PremiumTrialAvailable())
		throw ASIException("ParticPremiumTrialPostPage::initialize: trials are not available");

	if(fIsHtmlServer.getFloatField("GamePrice") != 0.0)
		throw ASIException("ParticPremiumTrialPostPage::process: game price mismatch");
	
	particPtr = fPageOptions.getRqstPartic();
	if((particPtr->getGameLevel() != gml_Standard) ||
			(particPtr->getTrialDateTime() != TDateTime()))
		throw ASIException("ParticPremiumTrialPostPage::initialize: partic cannot be set for trial");

	particPtr->setTrialDateTime(TDateTime::CurrentDateTime());
	particPtr->setGameLevel(gml_Premium);

	particPtr->update();
}

/******************************************************************************/

void ParticPremiumTrialPostPage::writeBodyRows()
{
	writeBodyLineRow();

	/**************************************************************************/

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efStrong);

	fHtmlWriter.TextString("Your 1 week trial request has been processed. "
		"You are now using the premium version.");

	fHtmlWriter.TextEffectEnd(efStrong);
	fHtmlWriter.FontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();

	/**************************************************************************/

	writeBodyEmptyRow(20);

	fHtmlWriter.TableRowStart();
	fHtmlWriter.TableCellStart(0,0,THtmlWidth(),THtmlHeight(),ahLeft,avTop);
	fHtmlWriter.FontStart(3,fcAbsolute,ASFantasyStandardFont());
	fHtmlWriter.TextEffectStart(efStrong);

	fHtmlWriter.TextString("Return to the ");
	TTextNavHTMLView::Build(fHtmlWriter,fPageOptions,htmlHubPage);
	fHtmlWriter.TextString(".");

	fHtmlWriter.TextEffectEnd(efStrong);
	fHtmlWriter.FontEnd();
	fHtmlWriter.TableCellEnd();
	fHtmlWriter.TableRowEnd();
}

/******************************************************************************/
/******************************************************************************/
