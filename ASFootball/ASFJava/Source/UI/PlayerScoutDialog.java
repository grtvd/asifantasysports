/* PlayerScoutDialog.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class PlayerScoutDialog extends ASFantasyPlayerScoutDialog
{
	protected java.awt.Checkbox fQuarterbacksChk;
	protected java.awt.Checkbox fWideReceiversChk;
	protected java.awt.Checkbox fRunningBacksChk;
	protected java.awt.Checkbox fTightEndsChk;
	protected java.awt.Checkbox fKickersChk;
	protected java.awt.Checkbox fDefenseChk;

	/**************************************************************************/

	public PlayerScoutDialog(Component component,DialogClient dialogClient,
		PlayerScoutRqst playerScoutRqst,TGameLevel gameLevel)
	{
		super(component,dialogClient,playerScoutRqst,gameLevel);
	}

	/**************************************************************************/

	protected String getProfTeamLblText()
	{
		return("NFL Team");
	}

	/**************************************************************************/

	protected void addProfTeamChoiceItems(java.awt.Choice profTeamChc)
	{
		profTeamChc.addItem("ARZ");
		profTeamChc.addItem("ATL");
		profTeamChc.addItem("BAL");
		profTeamChc.addItem("BUF");
		profTeamChc.addItem("CAR");
		profTeamChc.addItem("CHI");
		profTeamChc.addItem("CIN");
		profTeamChc.addItem("DAL");
		profTeamChc.addItem("DEN");
		profTeamChc.addItem("DET");
		profTeamChc.addItem("GRE");
		profTeamChc.addItem("IND");
		profTeamChc.addItem("JAC");
		profTeamChc.addItem("KAN");
		profTeamChc.addItem("MIA");
		profTeamChc.addItem("MIN");
		profTeamChc.addItem("ENG");
		profTeamChc.addItem("NOS");
		profTeamChc.addItem("NYG");
		profTeamChc.addItem("NYJ");
		profTeamChc.addItem("OAK");
		profTeamChc.addItem("PHL");
		profTeamChc.addItem("PIT");
		profTeamChc.addItem("SDC");
		profTeamChc.addItem("SFR");
		profTeamChc.addItem("SEA");
		profTeamChc.addItem("STL");
		profTeamChc.addItem("TAM");
		profTeamChc.addItem("TEN");
		profTeamChc.addItem("WAS");
	}

	/**************************************************************************/

	protected void createPositionCheckboxes(
		symantec.itools.awt.BorderPanel positionPnl)
	{
		fQuarterbacksChk = new java.awt.Checkbox("Quarterbacks");
		fQuarterbacksChk.reshape(0,0,125,14);
		positionPnl.add(fQuarterbacksChk);

		fWideReceiversChk = new java.awt.Checkbox("Wide Receivers");
		fWideReceiversChk.reshape(0,25,125,14);
		positionPnl.add(fWideReceiversChk);

		fRunningBacksChk = new java.awt.Checkbox("Running Backs");
		fRunningBacksChk.reshape(0,50,125,14);
		positionPnl.add(fRunningBacksChk);

		fTightEndsChk = new java.awt.Checkbox("Tight Ends");
		fTightEndsChk.reshape(140,0,125,14);
		positionPnl.add(fTightEndsChk);

		fKickersChk = new java.awt.Checkbox("Kickers");
		fKickersChk.reshape(140,25,125,14);
		positionPnl.add(fKickersChk);

		fDefenseChk = new java.awt.Checkbox("Defense");
		fDefenseChk.reshape(140,50,125,14);
		positionPnl.add(fDefenseChk);
	}

	/**************************************************************************/

	protected void addStatTypeChoiceItems(java.awt.Choice statTypeChc)
	{
		statTypeChc.addItem("Total Points");
		statTypeChc.addItem("Passing Yards");
		statTypeChc.addItem("Passing TDs");
		statTypeChc.addItem("Interceptions");
		statTypeChc.addItem("2-Point Passes");
		statTypeChc.addItem("Rushing Yards");
		statTypeChc.addItem("Rushing TDs");
		statTypeChc.addItem("Fumbles");
		statTypeChc.addItem("2-Point Rushes");
		statTypeChc.addItem("Receiving Yards");
		statTypeChc.addItem("Receiving TDs");
		statTypeChc.addItem("2-Point Receptions");
		statTypeChc.addItem("Kick Return TDs");
		statTypeChc.addItem("Misc. TDs");
		statTypeChc.addItem("PATs Made");
		statTypeChc.addItem("PATs Missed");
		statTypeChc.addItem("Field Goals Made");
		statTypeChc.addItem("Field Goals Missed");
		statTypeChc.addItem("Yards Allowed (D)");
		statTypeChc.addItem("Safeties (D)");
		statTypeChc.addItem("Sacks (D)");
		statTypeChc.addItem("Blocked Kicks (D)");
		statTypeChc.addItem("Fumbles Recovered (D)");
		statTypeChc.addItem("Interceptions (D)");
		statTypeChc.addItem("Defensive TDs (D)");
	}

	/**************************************************************************/

	protected void loadAllPositions()
	{
		loadPosition(fQuarterbacksChk,TPosition.pos_Quarterback,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fWideReceiversChk,TPosition.pos_WideReceiver,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fRunningBacksChk,TPosition.pos_RunningBack,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fTightEndsChk,TPosition.pos_TightEnd,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fKickersChk,TPosition.pos_Kicker,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fDefenseChk,TPosition.pos_Defense,
			fPlayerScoutRqst.fPositionVector);
	}

	/**************************************************************************/

	protected void unloadAllPositions()
	{
		unloadPosition(fQuarterbacksChk,TPosition.pos_Quarterback,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fWideReceiversChk,TPosition.pos_WideReceiver,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fRunningBacksChk,TPosition.pos_RunningBack,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fTightEndsChk,TPosition.pos_TightEnd,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fKickersChk,TPosition.pos_Kicker,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fDefenseChk,TPosition.pos_Defense,
			fPlayerScoutRqst.fPositionVector);
	}

}

/******************************************************************************/
/******************************************************************************/
