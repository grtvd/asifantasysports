/* LineupApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.util.*;

/******************************************************************************/
/******************************************************************************/

public class LineupApplet extends ASFantasyLineupApplet
{
	protected jclass.bwt.JCLabel fQBLbl;
	protected jclass.bwt.JCLabel fRB1Lbl;
	protected jclass.bwt.JCLabel fRB2Lbl;
	protected jclass.bwt.JCLabel fWR1Lbl;
	protected jclass.bwt.JCLabel fWR2Lbl;
	protected jclass.bwt.JCLabel fTELbl;
	protected jclass.bwt.JCLabel fKLbl;
	protected jclass.bwt.JCLabel fDefLbl;

	protected java.awt.Choice fQBChc;
	protected java.awt.Choice fRB1Chc;
	protected java.awt.Choice fRB2Chc;
	protected java.awt.Choice fWR1Chc;
	protected java.awt.Choice fWR2Chc;
	protected java.awt.Choice fTEChc;
	protected java.awt.Choice fKChc;
	protected java.awt.Choice fDefChc;

	// This correspond to the lineup Choice components.
	protected Vector fQBPlayers = new Vector();
	protected Vector fRB1Players = new Vector();
	protected Vector fRB2Players = new Vector();
	protected Vector fWR1Players = new Vector();
	protected Vector fWR2Players = new Vector();
	protected Vector fTEPlayers = new Vector();
	protected Vector fKPlayers = new Vector();
	protected Vector fDefPlayers = new Vector();

	/**************************************************************************/

	protected void createWhichLineup(symantec.itools.awt.BorderPanel panel,
		int left,int top) throws Exception
	{
	}

	/**************************************************************************/

	protected void createLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		fQBLbl = new jclass.bwt.JCLabel();
		fQBLbl.reshape(8,12,40,14);
		fQBLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fQBLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("QB");
			fQBLbl.setTextList(tempString);
		}
		fRB1Lbl = new jclass.bwt.JCLabel();
		fRB1Lbl.reshape(8,42,40,14);
		fRB1Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fRB1Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("RB");
			fRB1Lbl.setTextList(tempString);
		}
		fRB2Lbl = new jclass.bwt.JCLabel();
		fRB2Lbl.reshape(2,72,52,14);
		fRB2Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fRB2Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("RB/WR");
			fRB2Lbl.setTextList(tempString);
		}
		fWR1Lbl = new jclass.bwt.JCLabel();
		fWR1Lbl.reshape(8,102,40,14);
		fWR1Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fWR1Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("WR");
			fWR1Lbl.setTextList(tempString);
		}
		fWR2Lbl = new jclass.bwt.JCLabel();
		fWR2Lbl.reshape(8,132,40,14);
		fWR2Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fWR2Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("WR");
			fWR2Lbl.setTextList(tempString);
		}
		fTELbl = new jclass.bwt.JCLabel();
		fTELbl.reshape(8,162,40,14);
		fTELbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fTELbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("TE");
			fTELbl.setTextList(tempString);
		}
		fKLbl = new jclass.bwt.JCLabel();
		fKLbl.reshape(8,192,40,14);
		fKLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fKLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("K");
			fKLbl.setTextList(tempString);
		}
		fDefLbl = new jclass.bwt.JCLabel();
		fDefLbl.reshape(8,222,40,14);
		fDefLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fDefLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Def");
			fDefLbl.setTextList(tempString);
		}
	}

	/**************************************************************************/

	protected void removeLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(fQBLbl);
		panel.remove(fRB1Lbl);
		panel.remove(fRB2Lbl);
		panel.remove(fWR1Lbl);
		panel.remove(fWR2Lbl);
		panel.remove(fTELbl);
		panel.remove(fKLbl);
		panel.remove(fDefLbl);
	
		fQBLbl = null;
		fRB1Lbl = null;
		fRB2Lbl = null;
		fWR1Lbl = null;
		fWR2Lbl = null;
		fTELbl = null;
		fKLbl = null;
		fDefLbl = null;
	}

	/**************************************************************************/

	protected void createLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		fQBChc = new java.awt.Choice();
		fLineupPnl.add(fQBChc);
		fQBChc.reshape(55,8,130,23);
		fQBChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fRB1Chc = new java.awt.Choice();
		fLineupPnl.add(fRB1Chc);
		fRB1Chc.reshape(55,38,130,23);
		fRB1Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fRB2Chc = new java.awt.Choice();
		fLineupPnl.add(fRB2Chc);
		fRB2Chc.reshape(55,68,130,23);
		fRB2Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fWR1Chc = new java.awt.Choice();
		fLineupPnl.add(fWR1Chc);
		fWR1Chc.reshape(55,98,130,23);
		fWR1Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fWR2Chc = new java.awt.Choice();
		fLineupPnl.add(fWR2Chc);
		fWR2Chc.reshape(55,128,130,23);
		fWR2Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fTEChc = new java.awt.Choice();
		fLineupPnl.add(fTEChc);
		fTEChc.reshape(55,158,130,23);
		fTEChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fKChc = new java.awt.Choice();
		fLineupPnl.add(fKChc);
		fKChc.reshape(55,188,130,23);
		fKChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fDefChc = new java.awt.Choice();
		fLineupPnl.add(fDefChc);
		fDefChc.reshape(55,218,130,23);
		fDefChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
	}

	/**************************************************************************/

	protected void removeLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(fQBChc);
		panel.remove(fRB1Chc);
		panel.remove(fRB2Chc);
		panel.remove(fWR1Chc);
		panel.remove(fWR2Chc);
		panel.remove(fTEChc);
		panel.remove(fKChc);
		panel.remove(fDefChc);
	
		fQBChc = null;
		fRB1Chc = null;
		fRB2Chc = null;
		fWR1Chc = null;
		fWR2Chc = null;
		fTEChc = null;
		fKChc = null;
		fDefChc = null;
	}

	/**************************************************************************/

	protected void enableLineupChoices() throws Exception
	{
		fQBChc.enable(fLineupEnabled);
		fRB1Chc.enable(fLineupEnabled);
		fRB2Chc.enable(fLineupEnabled);
		fWR1Chc.enable(fLineupEnabled);
		fWR2Chc.enable(fLineupEnabled);
		fTEChc.enable(fLineupEnabled);
		fKChc.enable(fLineupEnabled);
		fDefChc.enable(fLineupEnabled);
	}

	/**************************************************************************/

	protected int getNumRosterListCols()
	{
		return(7);
	}

	/**************************************************************************/

	protected String getRosterListColLabel(int col)
	{
		if(col == 0)
			return("Player");
		else if(col == 1)
			return("PT");
		else if(col == 2)
			return("Pos");
		else if(col == 3)
			return("Pts");
		else if(col == 4)
			return("LW");
		else if(col == 5)
			return("S");
		else if(col == 6)
			return("Opp");
		return("");
	}

	/**************************************************************************/

	protected int getRosterListColWidth(int col)
	{
		if(col == 0)
			return(105);
		else if(col == 1)
			return(37);
		else if(col == 2)
			return(37);
		else if(col == 3)
			return(35);
		else if(col == 4)
			return(35);
		else if(col == 5)
			return(35);
		else if(col == 6)
			return(51);
		return(0);
	}

	/**************************************************************************/

	protected void emptyLineupVectors() throws Exception
	{
		fQBPlayers.removeAllElements();
		fRB1Players.removeAllElements();
		fRB2Players.removeAllElements();
		fWR1Players.removeAllElements();
		fWR2Players.removeAllElements();
		fTEPlayers.removeAllElements();
		fKPlayers.removeAllElements();
		fDefPlayers.removeAllElements();
	}

	/**************************************************************************/

	protected void addOpenSlotToAllLineupVectorChoices() throws Exception
	{
		// Add 'open slot' to all Choices
		String emptyStr = "<open slot>";
		Integer zeroID = new Integer(0);

		addToLineupVectorChoice(fQBPlayers,fQBChc,zeroID,emptyStr);
		addToLineupVectorChoice(fRB1Players,fRB1Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fRB2Players,fRB2Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fWR1Players,fWR1Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fWR2Players,fWR2Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fTEPlayers,fTEChc,zeroID,emptyStr);
		addToLineupVectorChoice(fKPlayers,fKChc,zeroID,emptyStr);
		addToLineupVectorChoice(fDefPlayers,fDefChc,zeroID,emptyStr);
	}

	/**************************************************************************/

	protected void addPlayerToSelectLineupVectorChoices(LineupPlayer player)
		throws Exception
	{
		if(player.fPosition == TPosition.pos_Quarterback)
		{
			addPlayerToLineupVectorChoice(fQBPlayers,fQBChc,player);
		}
		else if(player.fPosition == TPosition.pos_RunningBack)
		{
			addPlayerToLineupVectorChoice(fRB1Players,fRB1Chc,player);
			addPlayerToLineupVectorChoice(fRB2Players,fRB2Chc,player);
		}
		else if(player.fPosition == TPosition.pos_WideReceiver)
		{
			addPlayerToLineupVectorChoice(fRB2Players,fRB2Chc,player);
			addPlayerToLineupVectorChoice(fWR1Players,fWR1Chc,player);
			addPlayerToLineupVectorChoice(fWR2Players,fWR2Chc,player);
		}
		else if(player.fPosition == TPosition.pos_TightEnd)
		{
			addPlayerToLineupVectorChoice(fTEPlayers,fTEChc,player);
		}
		else if(player.fPosition == TPosition.pos_Kicker)
		{
			addPlayerToLineupVectorChoice(fKPlayers,fKChc,player);
		}
		else if(player.fPosition == TPosition.pos_Defense)
		{
			addPlayerToLineupVectorChoice(fDefPlayers,fDefChc,player);
		}
		else
			throw new Exception("LineupApplet.addPlayerToSelectLineupVectorChoices: unknown position");
	}

	/**************************************************************************/

	// Set Choices based on lineup (fPlayerIDArray)

	protected void selAllLineupChoices() throws Exception
	{
		PlayerIDVector playerIDVector;
		int lineup = 0;

		if(lineup >= fPlayerIDArray.size())
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(lineup);
		if(playerIDVector.size() != 8)
			throw new Exception("LineupApplet.selAllLineupChoices: invalid lineup size");

		selLineupChoiceByID(fQBPlayers,fQBChc,(Integer)playerIDVector.elementAt(0));
		selLineupChoiceByID(fRB1Players,fRB1Chc,(Integer)playerIDVector.elementAt(1));
		selLineupChoiceByID(fRB2Players,fRB2Chc,(Integer)playerIDVector.elementAt(2));
		selLineupChoiceByID(fWR1Players,fWR1Chc,(Integer)playerIDVector.elementAt(3));
		selLineupChoiceByID(fWR2Players,fWR2Chc,(Integer)playerIDVector.elementAt(4));
		selLineupChoiceByID(fTEPlayers,fTEChc,(Integer)playerIDVector.elementAt(5));
		selLineupChoiceByID(fKPlayers,fKChc,(Integer)playerIDVector.elementAt(6));
		selLineupChoiceByID(fDefPlayers,fDefChc,(Integer)playerIDVector.elementAt(7));
	}
	
	/**************************************************************************/

	protected boolean unloadAllLineupChoices() throws Exception
	{
		PlayerIDVector playerIDVector;
		int lineup = 0;

		if(lineup >= fPlayerIDArray.size())
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(lineup);
		if(playerIDVector.size() != 8)
			throw new Exception("LineupApplet.unloadAllLineupChoices: invalid lineup size");

		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fQBPlayers,fQBChc),0);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fRB1Players,fRB1Chc),1);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fRB2Players,fRB2Chc),2);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWR1Players,fWR1Chc),3);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWR2Players,fWR2Chc),4);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fTEPlayers,fTEChc),5);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fKPlayers,fKChc),6);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fDefPlayers,fDefChc),7);

		if(playerIDVector.doesContainDups(true))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Your lineup contains duplicate players.  Duplicate players are not allowed.");
			return(false);
		}

		return(true);
	}

	/**************************************************************************/

	protected JCVector createRosterListPlayer(LineupPlayer player)
	{
		JCVector row;
		
		row = new JCVector();
		row.addElement(player.fName.buildRevFullName());
		row.addElement(player.fProfTeamAbbr);
		row.addElement(player.fPosition.toString());
		row.addElement(new Integer(player.fTotalPoints));
		row.addElement(new Integer(player.fLastWeeksPoints));
		row.addElement(player.getStatus());
		row.addElement(player.fOppProfTeamGame);

		return(row);
	}
}

/******************************************************************************/
/******************************************************************************/
