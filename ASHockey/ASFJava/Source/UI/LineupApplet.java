/* LineupApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class LineupApplet extends ASFantasyLineupApplet
{
	protected java.awt.Choice fWhichLineupChc;
	protected int fLastWhichLineup;

	protected jclass.bwt.JCLabel fWinger1Lbl;
	protected jclass.bwt.JCLabel fWinger2Lbl;
	protected jclass.bwt.JCLabel fWinger3Lbl;
	protected jclass.bwt.JCLabel fWinger4Lbl;
	protected jclass.bwt.JCLabel fCenter1Lbl;
	protected jclass.bwt.JCLabel fCenter2Lbl;

	protected java.awt.Choice fWinger1Chc;
	protected java.awt.Choice fWinger2Chc;
	protected java.awt.Choice fWinger3Chc;
	protected java.awt.Choice fWinger4Chc;
	protected java.awt.Choice fCenter1Chc;
	protected java.awt.Choice fCenter2Chc;

	
	// This correspond to the lineup Choice components.
	protected Vector fWinger1Players = new Vector();
	protected Vector fWinger2Players = new Vector();
	protected Vector fWinger3Players = new Vector();
	protected Vector fWinger4Players = new Vector();
	protected Vector fCenter1Players = new Vector();
	protected Vector fCenter2Players = new Vector();

	/**************************************************************************/

	protected void createWhichLineup(symantec.itools.awt.BorderPanel panel,
		int left,int top) throws Exception
	{
		fWhichLineupChc = new java.awt.Choice();
		panel.add(fWhichLineupChc);
		fWhichLineupChc.reshape(left,top,130,23);
		fWhichLineupChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

		fWhichLineupChc.addItem("Offense");
		fWhichLineupChc.addItem("Defense");
		fWhichLineupChc.select(0);
		fLastWhichLineup = 0;
	}

	/**************************************************************************/

	protected void createLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		fWinger1Lbl = new jclass.bwt.JCLabel();
		fWinger1Lbl.reshape(8,12,40,14);
		fWinger1Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fWinger1Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "W" : "D");
			fWinger1Lbl.setTextList(tempString);
		}
		fWinger2Lbl = new jclass.bwt.JCLabel();
		fWinger2Lbl.reshape(8,42,40,14);
		fWinger2Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fWinger2Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "W" : "D");
			fWinger2Lbl.setTextList(tempString);
		}
		fWinger3Lbl = new jclass.bwt.JCLabel();
		fWinger3Lbl.reshape(2,72,52,14);
		fWinger3Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fWinger3Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "W" : "D");
			fWinger3Lbl.setTextList(tempString);
		}
		fWinger4Lbl = new jclass.bwt.JCLabel();
		fWinger4Lbl.reshape(8,102,40,14);
		fWinger4Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fWinger4Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "W" : "D");
			fWinger4Lbl.setTextList(tempString);
		}
		fCenter1Lbl = new jclass.bwt.JCLabel();
		fCenter1Lbl.reshape(8,132,40,14);
		fCenter1Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fCenter1Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "C" : "G");
			fCenter1Lbl.setTextList(tempString);
		}
		if(fLastWhichLineup == 0)
		{
			fCenter2Lbl = new jclass.bwt.JCLabel();
			fCenter2Lbl.reshape(8,162,40,14);
			fCenter2Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
			panel.add(fCenter2Lbl);
			{
				java.lang.String[] tempString = new java.lang.String[1];
				tempString[0] = new java.lang.String("C");
				fCenter2Lbl.setTextList(tempString);
			}
		}
	}

	/**************************************************************************/

	protected void removeLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(fWinger1Lbl);
		panel.remove(fWinger2Lbl);
		panel.remove(fWinger3Lbl);
		panel.remove(fWinger4Lbl);
		panel.remove(fCenter1Lbl);
		if(fCenter2Lbl != null)
			panel.remove(fCenter2Lbl);
	
		fWinger1Lbl = null;
		fWinger2Lbl = null;
		fWinger3Lbl = null;
		fWinger4Lbl = null;
		fCenter1Lbl = null;
		fCenter2Lbl = null;
	}

	/**************************************************************************/

	protected void createLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		fWinger1Chc = new java.awt.Choice();
		panel.add(fWinger1Chc);
		fWinger1Chc.reshape(55,8,130,23);
		fWinger1Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fWinger2Chc = new java.awt.Choice();
		panel.add(fWinger2Chc);
		fWinger2Chc.reshape(55,38,130,23);
		fWinger2Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fWinger3Chc = new java.awt.Choice();
		panel.add(fWinger3Chc);
		fWinger3Chc.reshape(55,68,130,23);
		fWinger3Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fWinger4Chc = new java.awt.Choice();
		panel.add(fWinger4Chc);
		fWinger4Chc.reshape(55,98,130,23);
		fWinger4Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fCenter1Chc = new java.awt.Choice();
		panel.add(fCenter1Chc);
		fCenter1Chc.reshape(55,128,130,23);
		fCenter1Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		if(fLastWhichLineup == 0)
		{
			fCenter2Chc = new java.awt.Choice();
			panel.add(fCenter2Chc);
			fCenter2Chc.reshape(55,158,130,23);
			fCenter2Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		}
	}

	/**************************************************************************/

	protected void removeLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(fWinger1Chc);
		panel.remove(fWinger2Chc);
		panel.remove(fWinger3Chc);
		panel.remove(fWinger4Chc);
		panel.remove(fCenter1Chc);
		if(fCenter2Chc != null)
			panel.remove(fCenter2Chc);
	
		fWinger1Chc = null;
		fWinger2Chc = null;
		fWinger3Chc = null;
		fWinger4Chc = null;
		fCenter1Chc = null;
		fCenter2Chc = null;
	}

	/**************************************************************************/

	protected void enableLineupChoices() throws Exception
	{
		fWinger1Chc.enable(fLineupEnabled);
		fWinger2Chc.enable(fLineupEnabled);
		fWinger3Chc.enable(fLineupEnabled);
		fWinger4Chc.enable(fLineupEnabled);
		fCenter1Chc.enable(fLineupEnabled);
		if(fCenter2Chc != null)
			fCenter2Chc.enable(fLineupEnabled);
	}

	/**************************************************************************/
	
	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fWhichLineupChc)
			{
				showOtherLineup();
			}
			else
				return super.action(evt,arg);
		}
		else
			return super.action(evt,arg);

		return true;
	}

	/**************************************************************************/

	protected void showOtherLineup()
	{
		int pos = fWhichLineupChc.getSelectedIndex();

		if(((pos >= 0) && (pos < 2)) && (pos != fLastWhichLineup))
		{
			try
			{
				pos = fLastWhichLineup;

				if(unloadAllLineupChoices())
				{
					fLastWhichLineup = fWhichLineupChc.getSelectedIndex();
					loadLineupChoices(false);
					enableLineupChoices();

					return;
				}
			}
			catch(Exception e)
			{
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"Unable to show your lineup. Internal Error: " + e.getMessage());
				fLastWhichLineup = pos;
			}
		}

		fWhichLineupChc.select(fLastWhichLineup);
	}
	
	/**************************************************************************/

	protected void emptyLineupVectors() throws Exception
	{
		fWinger1Players.removeAllElements();
		fWinger2Players.removeAllElements();
		fWinger3Players.removeAllElements();
		fWinger4Players.removeAllElements();
		fCenter1Players.removeAllElements();
		fCenter2Players.removeAllElements();
	}

	/**************************************************************************/

	protected void addOpenSlotToAllLineupVectorChoices() throws Exception
	{
		// Add 'open slot' to all Choices
		String emptyStr = "<open slot>";
		Integer zeroID = new Integer(0);

		addToLineupVectorChoice(fWinger1Players,fWinger1Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fWinger2Players,fWinger2Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fWinger3Players,fWinger3Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fWinger4Players,fWinger4Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fCenter1Players,fCenter1Chc,zeroID,emptyStr);
		if(fCenter2Chc != null)
			addToLineupVectorChoice(fCenter2Players,fCenter2Chc,zeroID,emptyStr);
	}

	/**************************************************************************/

	protected void addPlayerToSelectLineupVectorChoices(LineupPlayer player)
		throws Exception
	{
		if(fLastWhichLineup == 0)
		{
			if(player.fPosition == TPosition.pos_Winger)
			{
				addPlayerToLineupVectorChoice(fWinger1Players,fWinger1Chc,player);
				addPlayerToLineupVectorChoice(fWinger2Players,fWinger2Chc,player);
				addPlayerToLineupVectorChoice(fWinger3Players,fWinger3Chc,player);
				addPlayerToLineupVectorChoice(fWinger4Players,fWinger4Chc,player);
			}
			else if(player.fPosition == TPosition.pos_Center)
			{
				addPlayerToLineupVectorChoice(fCenter1Players,fCenter1Chc,player);
				addPlayerToLineupVectorChoice(fCenter2Players,fCenter2Chc,player);
			}
			else if(player.fPosition == TPosition.pos_Defenseman)
			{
			}
			else if(player.fPosition == TPosition.pos_Goalie)
			{
			}
			else
				throw new Exception("LineupApplet.addPlayerToSelectLineupVectorChoices: unknown position");
		}
		else
		{
			if(player.fPosition == TPosition.pos_Winger)
			{
			}
			else if(player.fPosition == TPosition.pos_Center)
			{
			}
			else if(player.fPosition == TPosition.pos_Defenseman)
			{
				addPlayerToLineupVectorChoice(fWinger1Players,fWinger1Chc,player);
				addPlayerToLineupVectorChoice(fWinger2Players,fWinger2Chc,player);
				addPlayerToLineupVectorChoice(fWinger3Players,fWinger3Chc,player);
				addPlayerToLineupVectorChoice(fWinger4Players,fWinger4Chc,player);
			}
			else if(player.fPosition == TPosition.pos_Goalie)
			{
				addPlayerToLineupVectorChoice(fCenter1Players,fCenter1Chc,player);
			}
			else
				throw new Exception("LineupApplet.addPlayerToSelectLineupVectorChoices: unknown position");
		}
	}

	/**************************************************************************/

	// Set Choices based on lineup (fPlayerIDArray)

	protected void selAllLineupChoices() throws Exception
	{
		PlayerIDVector playerIDVector;
		int lineup = fWhichLineupChc.getSelectedIndex();

		if(fPlayerIDArray.size() != 2)
			throw new Exception("LineupApplet.selAllLineupChoices: fPlayerIDArray.size() != 2");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(0);
		if(playerIDVector.size() != 10)
			throw new Exception("LineupApplet.selAllLineupChoices: invalid lineup size");

		if(lineup == 0)
		{
			selLineupChoiceByID(fWinger1Players,fWinger1Chc,(Integer)playerIDVector.elementAt(0));		// Winger
			selLineupChoiceByID(fWinger2Players,fWinger2Chc,(Integer)playerIDVector.elementAt(1));		// Winger
			selLineupChoiceByID(fWinger3Players,fWinger3Chc,(Integer)playerIDVector.elementAt(2));		// Winger
			selLineupChoiceByID(fWinger4Players,fWinger4Chc,(Integer)playerIDVector.elementAt(3));		// Winger
			selLineupChoiceByID(fCenter1Players,fCenter1Chc,(Integer)playerIDVector.elementAt(4));		// Center
			selLineupChoiceByID(fCenter2Players,fCenter2Chc,(Integer)playerIDVector.elementAt(5));		// Center
		}
		else if(lineup == 1)
		{
			selLineupChoiceByID(fWinger1Players,fWinger1Chc,(Integer)playerIDVector.elementAt(6));		// Defenseman
			selLineupChoiceByID(fWinger2Players,fWinger2Chc,(Integer)playerIDVector.elementAt(7));		// Defenseman
			selLineupChoiceByID(fWinger3Players,fWinger3Chc,(Integer)playerIDVector.elementAt(8));		// Defenseman
			selLineupChoiceByID(fWinger4Players,fWinger4Chc,(Integer)playerIDVector.elementAt(9));		// Defenseman

			playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(1);
			if(playerIDVector.size() != 1)
				throw new Exception("LineupApplet.selAllLineupChoices: invalid lineup size");

			selLineupChoiceByID(fCenter1Players,fCenter1Chc,(Integer)playerIDVector.elementAt(0));		// Goalie
		}
		else
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");
	}
	
	/**************************************************************************/

	protected boolean unloadAllLineupChoices() throws Exception
	{
		PlayerIDVector playerIDVector;
		boolean hasDups = false;

		if(fPlayerIDArray.size() != 2)
			throw new Exception("LineupApplet.unloadAllLineupChoices: fPlayerIDArray.size() != 2");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(0);
		if(playerIDVector.size() != 10)
			throw new Exception("LineupApplet.unloadAllLineupChoices: invalid lineup size");

		if(fLastWhichLineup == 0)
		{
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger1Players,fWinger1Chc),0);		// Winger
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger2Players,fWinger2Chc),1);		// Winger
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger3Players,fWinger3Chc),2);		// Winger
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger4Players,fWinger4Chc),3);		// Winger
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fCenter1Players,fCenter1Chc),4);		// Center
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fCenter2Players,fCenter2Chc),5);		// Center

			if(playerIDVector.doesContainDups(true))
				hasDups = true;
		}
		else if(fLastWhichLineup == 1)
		{
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger1Players,fWinger1Chc),6);		// Defenseman
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger2Players,fWinger2Chc),7);		// Defenseman
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger3Players,fWinger3Chc),8);		// Defenseman
			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fWinger4Players,fWinger4Chc),9);		// Defenseman

			if(playerIDVector.doesContainDups(true))
				hasDups = true;

			playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(1);
			if(playerIDVector.size() != 1)
				throw new Exception("LineupApplet.unloadAllLineupChoices: invalid lineup size");

			playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fCenter1Players,fCenter1Chc),0);		// Goalie
		}
		else
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");

		if(hasDups)
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
