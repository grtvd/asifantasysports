/* LineupApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class LineupApplet extends ASFantasyLineupApplet
{
	protected jclass.bwt.JCLabel fPGLbl;
	protected jclass.bwt.JCLabel fPGSGLbl;
	protected jclass.bwt.JCLabel fSGLbl;
	protected jclass.bwt.JCLabel fSGSFLbl;
	protected jclass.bwt.JCLabel fSFLbl;
	protected jclass.bwt.JCLabel fSFPFLbl;
	protected jclass.bwt.JCLabel fPFLbl;
	protected jclass.bwt.JCLabel fPFCLbl;
	protected jclass.bwt.JCLabel fCLbl;

	protected java.awt.Choice fPGChc;
	protected java.awt.Choice fPGSGChc;
	protected java.awt.Choice fSGChc;
	protected java.awt.Choice fSGSFChc;
	protected java.awt.Choice fSFChc;
	protected java.awt.Choice fSFPFChc;
	protected java.awt.Choice fPFChc;
	protected java.awt.Choice fPFCChc;
	protected java.awt.Choice fCChc;

	// This correspond to the lineup Choice components.
	protected Vector fPGPlayers = new Vector();
	protected Vector fPGSGPlayers = new Vector();
	protected Vector fSGPlayers = new Vector();
	protected Vector fSGSFPlayers = new Vector();
	protected Vector fSFPlayers = new Vector();
	protected Vector fSFPFPlayers = new Vector();
	protected Vector fPFPlayers = new Vector();
	protected Vector fPFCPlayers = new Vector();
	protected Vector fCPlayers = new Vector();

	/**************************************************************************/

	protected void createWhichLineup(symantec.itools.awt.BorderPanel panel,
		int left,int top) throws Exception
	{
	}

	/**************************************************************************/

	protected void createLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		fPGLbl = new jclass.bwt.JCLabel();
		fPGLbl.reshape(2,12,52,14);
		fPGLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fPGLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("PG");
			fPGLbl.setTextList(tempString);
		}
		fPGSGLbl = new jclass.bwt.JCLabel();
		fPGSGLbl.reshape(2,42,52,14);
		fPGSGLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fPGSGLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("PG/SG");
			fPGSGLbl.setTextList(tempString);
		}
		fSGLbl = new jclass.bwt.JCLabel();
		fSGLbl.reshape(2,72,52,14);
		fSGLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fSGLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("SG");
			fSGLbl.setTextList(tempString);
		}
		fSGSFLbl = new jclass.bwt.JCLabel();
		fSGSFLbl.reshape(2,102,52,14);
		fSGSFLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fSGSFLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("SG/SF");
			fSGSFLbl.setTextList(tempString);
		}
		fSFLbl = new jclass.bwt.JCLabel();
		fSFLbl.reshape(2,132,52,14);
		fSFLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fSFLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("SF");
			fSFLbl.setTextList(tempString);
		}
		fSFPFLbl = new jclass.bwt.JCLabel();
		fSFPFLbl.reshape(2,162,52,14);
		fSFPFLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fSFPFLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("SF/PF");
			fSFPFLbl.setTextList(tempString);
		}
		fPFLbl = new jclass.bwt.JCLabel();
		fPFLbl.reshape(2,192,52,14);
		fPFLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fPFLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("PF");
			fPFLbl.setTextList(tempString);
		}
		fPFCLbl = new jclass.bwt.JCLabel();
		fPFCLbl.reshape(2,222,52,14);
		fPFCLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fPFCLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("PF/C");
			fPFCLbl.setTextList(tempString);
		}
		fCLbl = new jclass.bwt.JCLabel();
		fCLbl.reshape(2,252,52,14);
		fCLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fLineupPnl.add(fCLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("C");
			fCLbl.setTextList(tempString);
		}
	}

	/**************************************************************************/

	protected void removeLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(fPGLbl);
		panel.remove(fPGSGLbl);
		panel.remove(fSGLbl);
		panel.remove(fSGSFLbl);
		panel.remove(fSFLbl);
		panel.remove(fSFPFLbl);
		panel.remove(fPFLbl);
		panel.remove(fPFCLbl);
		panel.remove(fCLbl);
	
		fPGLbl = null;
		fPGSGLbl = null;
		fSGLbl = null;
		fSGSFLbl = null;
		fSFLbl = null;
		fSFPFLbl = null;
		fPFLbl = null;
		fPFCLbl = null;
		fCLbl = null;
	}

	/**************************************************************************/

	protected void createLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		fPGChc = new java.awt.Choice();
		fLineupPnl.add(fPGChc);
		fPGChc.reshape(55,8,130,23);
		fPGChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fPGSGChc = new java.awt.Choice();
		fLineupPnl.add(fPGSGChc);
		fPGSGChc.reshape(55,38,130,23);
		fPGSGChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSGChc = new java.awt.Choice();
		fLineupPnl.add(fSGChc);
		fSGChc.reshape(55,68,130,23);
		fSGChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSGSFChc = new java.awt.Choice();
		fLineupPnl.add(fSGSFChc);
		fSGSFChc.reshape(55,98,130,23);
		fSGSFChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSFChc = new java.awt.Choice();
		fLineupPnl.add(fSFChc);
		fSFChc.reshape(55,128,130,23);
		fSFChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSFPFChc = new java.awt.Choice();
		fLineupPnl.add(fSFPFChc);
		fSFPFChc.reshape(55,158,130,23);
		fSFPFChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fPFChc = new java.awt.Choice();
		fLineupPnl.add(fPFChc);
		fPFChc.reshape(55,188,130,23);
		fPFChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fPFCChc = new java.awt.Choice();
		fLineupPnl.add(fPFCChc);
		fPFCChc.reshape(55,218,130,23);
		fPFCChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fCChc = new java.awt.Choice();
		fLineupPnl.add(fCChc);
		fCChc.reshape(55,248,130,23);
		fCChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
	}

	/**************************************************************************/

	protected void removeLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(fPGChc);
		panel.remove(fPGSGChc);
		panel.remove(fSGChc);
		panel.remove(fSGSFChc);
		panel.remove(fSFChc);
		panel.remove(fSFPFChc);
		panel.remove(fPFChc);
		panel.remove(fPFCChc);
		panel.remove(fCChc);
	
		fPGChc = null;
		fPGSGChc = null;
		fSGChc = null;
		fSGSFChc = null;
		fSFChc = null;
		fSFPFChc = null;
		fPFChc = null;
		fPFCChc = null;
		fCChc = null;
	}

	/**************************************************************************/

	protected void enableLineupChoices() throws Exception
	{
		fPGChc.enable(fLineupEnabled);
		fPGSGChc.enable(fLineupEnabled);
		fSGChc.enable(fLineupEnabled);
		fSGSFChc.enable(fLineupEnabled);
		fSFChc.enable(fLineupEnabled);
		fSFPFChc.enable(fLineupEnabled);
		fPFChc.enable(fLineupEnabled);
		fPFCChc.enable(fLineupEnabled);
		fCChc.enable(fLineupEnabled);
	}

	/**************************************************************************/

	protected void emptyLineupVectors() throws Exception
	{
		fPGPlayers.removeAllElements();
		fPGSGPlayers.removeAllElements();
		fSGPlayers.removeAllElements();
		fSGSFPlayers.removeAllElements();
		fSFPlayers.removeAllElements();
		fSFPFPlayers.removeAllElements();
		fPFPlayers.removeAllElements();
		fPFCPlayers.removeAllElements();
		fCPlayers.removeAllElements();
	}

	/**************************************************************************/

	protected void addOpenSlotToAllLineupVectorChoices() throws Exception
	{
		// Add 'open slot' to all Choices
		String emptyStr = "<open slot>";
		Integer zeroID = new Integer(0);

		addToLineupVectorChoice(fPGPlayers,fPGChc,zeroID,emptyStr);
		addToLineupVectorChoice(fPGSGPlayers,fPGSGChc,zeroID,emptyStr);
		addToLineupVectorChoice(fSGPlayers,fSGChc,zeroID,emptyStr);
		addToLineupVectorChoice(fSGSFPlayers,fSGSFChc,zeroID,emptyStr);
		addToLineupVectorChoice(fSFPlayers,fSFChc,zeroID,emptyStr);
		addToLineupVectorChoice(fSFPFPlayers,fSFPFChc,zeroID,emptyStr);
		addToLineupVectorChoice(fPFPlayers,fPFChc,zeroID,emptyStr);
		addToLineupVectorChoice(fPFCPlayers,fPFCChc,zeroID,emptyStr);
		addToLineupVectorChoice(fCPlayers,fCChc,zeroID,emptyStr);
	}

	/**************************************************************************/

	protected void addPlayerToSelectLineupVectorChoices(LineupPlayer player)
		throws Exception
	{
		if(player.fPosition == TPosition.pos_PointGuard)
		{
			addPlayerToLineupVectorChoice(fPGPlayers,fPGChc,player);
			addPlayerToLineupVectorChoice(fPGSGPlayers,fPGSGChc,player);
		}
		else if(player.fPosition == TPosition.pos_ShootingGuard)
		{
			addPlayerToLineupVectorChoice(fPGSGPlayers,fPGSGChc,player);
			addPlayerToLineupVectorChoice(fSGPlayers,fSGChc,player);
			addPlayerToLineupVectorChoice(fSGSFPlayers,fSGSFChc,player);
		}
		else if(player.fPosition == TPosition.pos_SmallForward)
		{
			addPlayerToLineupVectorChoice(fSGSFPlayers,fSGSFChc,player);
			addPlayerToLineupVectorChoice(fSFPlayers,fSFChc,player);
			addPlayerToLineupVectorChoice(fSFPFPlayers,fSFPFChc,player);
		}
		else if(player.fPosition == TPosition.pos_PowerForward)
		{
			addPlayerToLineupVectorChoice(fSFPFPlayers,fSFPFChc,player);
			addPlayerToLineupVectorChoice(fPFPlayers,fPFChc,player);
			addPlayerToLineupVectorChoice(fPFCPlayers,fPFCChc,player);
		}
		else if(player.fPosition == TPosition.pos_Center)
		{
			addPlayerToLineupVectorChoice(fPFCPlayers,fPFCChc,player);
			addPlayerToLineupVectorChoice(fCPlayers,fCChc,player);
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
		if(playerIDVector.size() != 9)
			throw new Exception("LineupApplet.selAllLineupChoices: invalid lineup size");

		selLineupChoiceByID(fPGPlayers,fPGChc,(Integer)playerIDVector.elementAt(0));
		selLineupChoiceByID(fPGSGPlayers,fPGSGChc,(Integer)playerIDVector.elementAt(1));
		selLineupChoiceByID(fSGPlayers,fSGChc,(Integer)playerIDVector.elementAt(2));
		selLineupChoiceByID(fSGSFPlayers,fSGSFChc,(Integer)playerIDVector.elementAt(3));
		selLineupChoiceByID(fSFPlayers,fSFChc,(Integer)playerIDVector.elementAt(4));
		selLineupChoiceByID(fSFPFPlayers,fSFPFChc,(Integer)playerIDVector.elementAt(5));
		selLineupChoiceByID(fPFPlayers,fPFChc,(Integer)playerIDVector.elementAt(6));
		selLineupChoiceByID(fPFCPlayers,fPFCChc,(Integer)playerIDVector.elementAt(7));
		selLineupChoiceByID(fCPlayers,fCChc,(Integer)playerIDVector.elementAt(8));
	}
	
	/**************************************************************************/

	protected boolean unloadAllLineupChoices() throws Exception
	{
		PlayerIDVector playerIDVector;
		int lineup = 0;

		if(lineup >= fPlayerIDArray.size())
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(lineup);
		if(playerIDVector.size() != 9)
			throw new Exception("LineupApplet.unloadAllLineupChoices: invalid lineup size");

		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fPGPlayers,fPGChc),0);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fPGSGPlayers,fPGSGChc),1);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fSGPlayers,fSGChc),2);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fSGSFPlayers,fSGSFChc),3);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fSFPlayers,fSFChc),4);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fSFPFPlayers,fSFPFChc),5);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fPFPlayers,fPFChc),6);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fPFCPlayers,fPFCChc),7);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fCPlayers,fCChc),8);

		if(playerIDVector.doesContainDups(true))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Your lineup contains duplicate players.  Duplicate players are not allowed.");
			return(false);
		}

		return(true);
	}

	/**************************************************************************/
}

/******************************************************************************/
/******************************************************************************/
