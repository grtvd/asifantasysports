/* PlayerScoutDialog.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class PlayerScoutDialog extends ASFantasyPlayerScoutDialog
{
	protected java.awt.Checkbox fPointGuardsChk;
	protected java.awt.Checkbox fShootingGuardsChk;
	protected java.awt.Checkbox fSmallForwardsChk;
	protected java.awt.Checkbox fPowerForwardsChk;
	protected java.awt.Checkbox fCentersChk;

	/**************************************************************************/

	public PlayerScoutDialog(Component component,DialogClient dialogClient,
		PlayerScoutRqst playerScoutRqst,TGameLevel gameLevel)
	{
		super(component,dialogClient,playerScoutRqst,gameLevel);
	}

	/**************************************************************************/

	protected String getProfTeamLblText()
	{
		return("NBA Team");
	}

	/**************************************************************************/

	protected void addProfTeamChoiceItems(java.awt.Choice profTeamChc)
	{
		profTeamChc.addItem("ATL");
		profTeamChc.addItem("BOS");
		profTeamChc.addItem("CHA");
		profTeamChc.addItem("CHI");
		profTeamChc.addItem("CLE");
		profTeamChc.addItem("DAL");
		profTeamChc.addItem("DEN");
		profTeamChc.addItem("DET");
		profTeamChc.addItem("GS");
		profTeamChc.addItem("HOU");
		profTeamChc.addItem("IND");
		profTeamChc.addItem("LAC");
		profTeamChc.addItem("LAL");
		profTeamChc.addItem("MIA");
		profTeamChc.addItem("MIL");
		profTeamChc.addItem("MIN");
		profTeamChc.addItem("NJ");
		profTeamChc.addItem("NY");
		profTeamChc.addItem("ORL");
		profTeamChc.addItem("PHI");
		profTeamChc.addItem("PHO");
		profTeamChc.addItem("POR");
		profTeamChc.addItem("SA");
		profTeamChc.addItem("SAC");
		profTeamChc.addItem("SEA");
		profTeamChc.addItem("TOR");
		profTeamChc.addItem("VAN");
		profTeamChc.addItem("UTA");
		profTeamChc.addItem("WAS");
	}

	/**************************************************************************/

	protected void createPositionCheckboxes(
		symantec.itools.awt.BorderPanel positionPnl)
	{
		fPointGuardsChk = new java.awt.Checkbox("Point Guards");
		fPointGuardsChk.reshape(0,0,125,14);
		positionPnl.add(fPointGuardsChk);

		fShootingGuardsChk = new java.awt.Checkbox("Shooting Guards");
		fShootingGuardsChk.reshape(0,25,125,14);
		positionPnl.add(fShootingGuardsChk);

		fCentersChk = new java.awt.Checkbox("Centers");
		fCentersChk.reshape(0,50,125,14);
		positionPnl.add(fCentersChk);

		fSmallForwardsChk = new java.awt.Checkbox("Small Forwards");
		fSmallForwardsChk.reshape(140,0,125,14);
		positionPnl.add(fSmallForwardsChk);

		fPowerForwardsChk = new java.awt.Checkbox("Power Forwards");
		fPowerForwardsChk.reshape(140,25,125,14);
		positionPnl.add(fPowerForwardsChk);
	}

	/**************************************************************************/

	protected void addStatTypeChoiceItems(java.awt.Choice statTypeChc)
	{
		statTypeChc.addItem("Total Points");
		statTypeChc.addItem("Games Played");
		statTypeChc.addItem("Minutes Played");
		statTypeChc.addItem("Points Scored");
		statTypeChc.addItem("Field Goals Made");
		statTypeChc.addItem("Field Goals Att.");
		statTypeChc.addItem("Field Goal %");
		statTypeChc.addItem("Free Throws Made");
		statTypeChc.addItem("Free Throws Att.");
		statTypeChc.addItem("Free Throw %");
		statTypeChc.addItem("3-Pts. Made");
		statTypeChc.addItem("3-Pts. Att.");
		statTypeChc.addItem("Off. Rebounds");
		statTypeChc.addItem("Def. Rebounds");
		statTypeChc.addItem("Assists");
		statTypeChc.addItem("Steals");
		statTypeChc.addItem("Blocks");
		statTypeChc.addItem("Turnovers");
		statTypeChc.addItem("Personal Fouls");
		statTypeChc.addItem("Technical Fouls");
	}

	/**************************************************************************/

	protected void loadAllPositions()
	{
		loadPosition(fPointGuardsChk,TPosition.pos_PointGuard,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fShootingGuardsChk,TPosition.pos_ShootingGuard,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fSmallForwardsChk,TPosition.pos_SmallForward,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fPowerForwardsChk,TPosition.pos_PowerForward,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fCentersChk,TPosition.pos_Center,
			fPlayerScoutRqst.fPositionVector);
	}

	/**************************************************************************/

	protected void unloadAllPositions()
	{
		unloadPosition(fPointGuardsChk,TPosition.pos_PointGuard,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fShootingGuardsChk,TPosition.pos_ShootingGuard,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fSmallForwardsChk,TPosition.pos_SmallForward,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fPowerForwardsChk,TPosition.pos_PowerForward,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fCentersChk,TPosition.pos_Center,
			fPlayerScoutRqst.fPositionVector);
	}

}

/******************************************************************************/
/******************************************************************************/
