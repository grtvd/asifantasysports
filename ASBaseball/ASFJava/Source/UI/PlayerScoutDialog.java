/* PlayerScoutDialog.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class PlayerScoutDialog extends ASFantasyPlayerScoutDialog
{
	protected java.awt.Checkbox fFirstBasemenChk;
	protected java.awt.Checkbox fSecondBasemenChk;
	protected java.awt.Checkbox fShortStopsChk;
	protected java.awt.Checkbox fThirdBasemenChk;
	protected java.awt.Checkbox fCatchersChk;
	protected java.awt.Checkbox fOutfieldersChk;
	protected java.awt.Checkbox fDesignatedHittersChk;
	protected java.awt.Checkbox fStartingPitchersChk;
	protected java.awt.Checkbox fReliefPitchersChk;

	/**************************************************************************/

	public PlayerScoutDialog(Component component,DialogClient dialogClient,
		PlayerScoutRqst playerScoutRqst,TGameLevel gameLevel)
	{
		super(component,dialogClient,playerScoutRqst,gameLevel);
	}

	/**************************************************************************/

	protected String getProfTeamLblText()
	{
		return("MLB Team");
	}

	/**************************************************************************/

	protected void addProfTeamChoiceItems(java.awt.Choice profTeamChc)
	{
		profTeamChc.addItem("ANA");
		profTeamChc.addItem("ARI");
		profTeamChc.addItem("ATL");
		profTeamChc.addItem("BAL");
		profTeamChc.addItem("BOS");
		profTeamChc.addItem("CHA");
		profTeamChc.addItem("CHN");
		profTeamChc.addItem("CIN");
		profTeamChc.addItem("CLE");
		profTeamChc.addItem("COL");
		profTeamChc.addItem("DET");
		profTeamChc.addItem("FLA");
		profTeamChc.addItem("HOU");
		profTeamChc.addItem("KC");
		profTeamChc.addItem("LA");
		profTeamChc.addItem("MIL");
		profTeamChc.addItem("MIN");
		profTeamChc.addItem("MON");
		profTeamChc.addItem("NYA");
		profTeamChc.addItem("NYN");
		profTeamChc.addItem("OAK");
		profTeamChc.addItem("PHI");
		profTeamChc.addItem("PIT");
		profTeamChc.addItem("SD");
		profTeamChc.addItem("SEA");
		profTeamChc.addItem("SFR");
		profTeamChc.addItem("STL");
		profTeamChc.addItem("TB");
		profTeamChc.addItem("TEX");
		profTeamChc.addItem("TOR");
	}

	/**************************************************************************/

	protected void createPositionCheckboxes(
		symantec.itools.awt.BorderPanel positionPnl)
	{
		fFirstBasemenChk = new java.awt.Checkbox("1B"); 	//"First Basemen"
		fFirstBasemenChk.reshape(0,0,85,14);
		positionPnl.add(fFirstBasemenChk);

		fSecondBasemenChk = new java.awt.Checkbox("2B");	//"Second Basemen"
		fSecondBasemenChk.reshape(0,25,85,14);
		positionPnl.add(fSecondBasemenChk);

		fShortStopsChk = new java.awt.Checkbox("SS");	//Short Stops"
		fShortStopsChk.reshape(0,50,85,14);
		positionPnl.add(fShortStopsChk);

		fThirdBasemenChk = new java.awt.Checkbox("3B");	//"Third Basemen"
		fThirdBasemenChk.reshape(95,0,85,14);
		positionPnl.add(fThirdBasemenChk);

		fCatchersChk = new java.awt.Checkbox("C");	//"Catchers"
		fCatchersChk.reshape(95,25,85,14);
		positionPnl.add(fCatchersChk);

		fOutfieldersChk = new java.awt.Checkbox("OF");	//"Outfielders"
		fOutfieldersChk.reshape(95,50,85,14);
		positionPnl.add(fOutfieldersChk);

		fDesignatedHittersChk = new java.awt.Checkbox("DH");	//"Designated Hitters"
		fDesignatedHittersChk.reshape(190,0,85,14);
		positionPnl.add(fDesignatedHittersChk);

		fStartingPitchersChk = new java.awt.Checkbox("SP");	//"Starting Pitchers"
		fStartingPitchersChk.reshape(190,25,85,14);
		positionPnl.add(fStartingPitchersChk);

		fReliefPitchersChk = new java.awt.Checkbox("RP");	//"Relief Pitchers"
		fReliefPitchersChk.reshape(190,50,85,14);
		positionPnl.add(fReliefPitchersChk);
	}

	/**************************************************************************/

	protected void addStatTypeChoiceItems(java.awt.Choice statTypeChc)
	{
		statTypeChc.addItem("Total Points");
		statTypeChc.addItem("Games Played");
		statTypeChc.addItem("Games Started");
		statTypeChc.addItem("Errors");
		statTypeChc.addItem("Average (Bat)");
		statTypeChc.addItem("At Bats (Bat)");
		statTypeChc.addItem("Hits (Bat)");
		statTypeChc.addItem("Doubles (Bat)");
		statTypeChc.addItem("Triples (Bat)");
		statTypeChc.addItem("1-Run Homers (Bat)");
		statTypeChc.addItem("2-Run Homers (Bat)");
		statTypeChc.addItem("3-Run Homers (Bat)");
		statTypeChc.addItem("GrandSlams (Bat)");
		statTypeChc.addItem("Runs Scored (Bat)");
		statTypeChc.addItem("Runs Batted In (Bat)");
		statTypeChc.addItem("Sacrifices (Bat)");
		statTypeChc.addItem("Hit By Picth (Bat)");
		statTypeChc.addItem("Walks (Bat)");
		statTypeChc.addItem("Strikeouts (Bat)");
		statTypeChc.addItem("Stolen Bases (Bat)");
		statTypeChc.addItem("Caught Stealing (Bat)");
		statTypeChc.addItem("Grounded Into Double Play (Bat)");
		statTypeChc.addItem("Hit For Cycle (Bat)");
		statTypeChc.addItem("ERA (Pit)");
		statTypeChc.addItem("Wins (Pit)");
		statTypeChc.addItem("Losses (Pit)");
		statTypeChc.addItem("Saves (Pit)");
		statTypeChc.addItem("Innings Pitched (Pit)");
		statTypeChc.addItem("Hits (Pit)");
		statTypeChc.addItem("Doubles (Pit)");
		statTypeChc.addItem("Triples (Pit)");
		statTypeChc.addItem("1-Run Homers (Pit)");
		statTypeChc.addItem("2-Run Homers (Pit)");
		statTypeChc.addItem("3-Run Homers (Pit)");
		statTypeChc.addItem("GrandSlams (Pit)");
		statTypeChc.addItem("Runs (Pit)");
		statTypeChc.addItem("Earned Runs (Pit)");
		statTypeChc.addItem("Sacrifices (Pit)");
		statTypeChc.addItem("Hit Batsmen (Pit)");
		statTypeChc.addItem("Walks (Pit)");
		statTypeChc.addItem("Strikeouts (Pit)");
		statTypeChc.addItem("Wild Pitches (Pit)");
		statTypeChc.addItem("Balks (Pit)");
		statTypeChc.addItem("Complete Games (Pit)");
		statTypeChc.addItem("Shutouts (Pit)");
		statTypeChc.addItem("No Hitters (Pit)");
		statTypeChc.addItem("Perfect Games (Pit)");
	}

	/**************************************************************************/

	protected void loadAllPositions()
	{
		loadPosition(fFirstBasemenChk,TPosition.pos_FirstBaseman,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fSecondBasemenChk,TPosition.pos_SecondBaseman,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fShortStopsChk,TPosition.pos_ShortStop,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fThirdBasemenChk,TPosition.pos_ThirdBaseman,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fCatchersChk,TPosition.pos_Catcher,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fOutfieldersChk,TPosition.pos_Outfielder,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fDesignatedHittersChk,TPosition.pos_DesignatedHitter,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fStartingPitchersChk,TPosition.pos_StartingPitcher,
			fPlayerScoutRqst.fPositionVector);
		loadPosition(fReliefPitchersChk,TPosition.pos_ReliefPitcher,
			fPlayerScoutRqst.fPositionVector);
	}

	/**************************************************************************/

	protected void unloadAllPositions()
	{
		unloadPosition(fFirstBasemenChk,TPosition.pos_FirstBaseman,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fSecondBasemenChk,TPosition.pos_SecondBaseman,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fShortStopsChk,TPosition.pos_ShortStop,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fThirdBasemenChk,TPosition.pos_ThirdBaseman,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fCatchersChk,TPosition.pos_Catcher,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fOutfieldersChk,TPosition.pos_Outfielder,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fDesignatedHittersChk,TPosition.pos_DesignatedHitter,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fStartingPitchersChk,TPosition.pos_StartingPitcher,
			fPlayerScoutRqst.fPositionVector);
		unloadPosition(fReliefPitchersChk,TPosition.pos_ReliefPitcher,
			fPlayerScoutRqst.fPositionVector);
	}

}

/******************************************************************************/
/******************************************************************************/
