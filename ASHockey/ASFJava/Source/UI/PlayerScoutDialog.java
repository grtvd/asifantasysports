/* PlayerScoutDialog.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class PlayerScoutDialog extends ASFantasyPlayerScoutDialog
{
	protected java.awt.Checkbox fWingersChk;
	protected java.awt.Checkbox fCentersChk;
	protected java.awt.Checkbox fDefensemenChk;
	protected java.awt.Checkbox fGoaliesChk;

	/**************************************************************************/

	public PlayerScoutDialog(Component component,DialogClient dialogClient,
		PlayerScoutRqst playerScoutRqst,TGameLevel gameLevel)
	{
		super(component,dialogClient,playerScoutRqst,gameLevel);
	}

	/**************************************************************************/

	protected String getProfTeamLblText()
	{
		return("NHL Team");
	}

	/**************************************************************************/

	protected void addProfTeamChoiceItems(java.awt.Choice profTeamChc)
	{
		profTeamChc.addItem("Bos");
		profTeamChc.addItem("Buf");
		profTeamChc.addItem("Cgy");
		profTeamChc.addItem("Chi");
		profTeamChc.addItem("Det");
		profTeamChc.addItem("Edm");
		profTeamChc.addItem("Car");
		profTeamChc.addItem("LA");
		profTeamChc.addItem("Dal");
		profTeamChc.addItem("Mon");
		profTeamChc.addItem("NJ");
		profTeamChc.addItem("NYI");
		profTeamChc.addItem("NYR");
		profTeamChc.addItem("Ott");
		profTeamChc.addItem("Phi");
		profTeamChc.addItem("Pit");
		profTeamChc.addItem("Col");
		profTeamChc.addItem("SJ");
		profTeamChc.addItem("StL");
		profTeamChc.addItem("TB");
		profTeamChc.addItem("Tor");
		profTeamChc.addItem("Van");
		profTeamChc.addItem("Was");
		profTeamChc.addItem("Pho");
		profTeamChc.addItem("Anh");
		profTeamChc.addItem("Fla");
		profTeamChc.addItem("Nsh");
	}

	/**************************************************************************/

	protected void createPositionCheckboxes(
		symantec.itools.awt.BorderPanel positionPnl)
	{
		fWingersChk = new java.awt.Checkbox("Wingers");
		fWingersChk.reshape(0,0,125,14);
		positionPnl.add(fWingersChk);

		fCentersChk = new java.awt.Checkbox("Centers");
		fCentersChk.reshape(0,25,125,14);
		positionPnl.add(fCentersChk);

		fDefensemenChk = new java.awt.Checkbox("Defensemen");
		fDefensemenChk.reshape(140,0,125,14);
		positionPnl.add(fDefensemenChk);

		fGoaliesChk = new java.awt.Checkbox("Goalies");
		fGoaliesChk.reshape(140,25,125,14);
		positionPnl.add(fGoaliesChk);
	}

	/**************************************************************************/

	protected void addStatTypeChoiceItems(java.awt.Choice statTypeChc)
	{
		statTypeChc.addItem("Total Points");
		statTypeChc.addItem("Games Played");
		statTypeChc.addItem("Goals");
		statTypeChc.addItem("Assists");
		statTypeChc.addItem("Penalty Minutes");
		statTypeChc.addItem("Shots");
		statTypeChc.addItem("Plus/Minus");
		statTypeChc.addItem("Power Play Goals");
		statTypeChc.addItem("Power Play Assists");
		statTypeChc.addItem("Short Handed Goals");
		statTypeChc.addItem("Short Handed Assists");
		statTypeChc.addItem("Game Winning Goals");
		statTypeChc.addItem("Game Tying Goals");
		statTypeChc.addItem("Overtime Goals");
		statTypeChc.addItem("Hat Tricks");
		statTypeChc.addItem("Games Started (G)");
		statTypeChc.addItem("Wins (G)");
		statTypeChc.addItem("Losses (G)");
		statTypeChc.addItem("Ties (G)");
		statTypeChc.addItem("Goals Against (G)");
		statTypeChc.addItem("Saves (G)");
		statTypeChc.addItem("Shutouts (G)");
	}

	/**************************************************************************/

	protected void loadAllPositions()
	{
		loadPosition(fWingersChk,TPosition.pos_Winger,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fCentersChk,TPosition.pos_Center,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fDefensemenChk,TPosition.pos_Defenseman,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fGoaliesChk,TPosition.pos_Goalie,
			fPlayerScoutRqst.fPositionVector);
	}

	/**************************************************************************/

	protected void unloadAllPositions()
	{
		unloadPosition(fWingersChk,TPosition.pos_Winger,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fCentersChk,TPosition.pos_Center,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fDefensemenChk,TPosition.pos_Defenseman,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fGoaliesChk,TPosition.pos_Goalie,
			fPlayerScoutRqst.fPositionVector);
	}

}

/******************************************************************************/
/******************************************************************************/
