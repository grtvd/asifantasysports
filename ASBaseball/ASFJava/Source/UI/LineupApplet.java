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

	protected jclass.bwt.JCLabel f1BLbl;
	protected jclass.bwt.JCLabel f2BLbl;
	protected jclass.bwt.JCLabel fSSLbl;
	protected jclass.bwt.JCLabel f3BLbl;
	protected jclass.bwt.JCLabel fCLbl;
	protected jclass.bwt.JCLabel fOF1Lbl;
	protected jclass.bwt.JCLabel fOF2Lbl;
	protected jclass.bwt.JCLabel fOF3Lbl;
	protected jclass.bwt.JCLabel fDHLbl;

	protected java.awt.Choice f1BChc;
	protected java.awt.Choice f2BChc;
	protected java.awt.Choice fSSChc;
	protected java.awt.Choice f3BChc;
	protected java.awt.Choice fCChc;
	protected java.awt.Choice fOF1Chc;
	protected java.awt.Choice fOF2Chc;
	protected java.awt.Choice fOF3Chc;
	protected java.awt.Choice fDHChc;

	
	// This correspond to the lineup Choice components.
	protected Vector f1BPlayers = new Vector();
	protected Vector f2BPlayers = new Vector();
	protected Vector fSSPlayers = new Vector();
	protected Vector f3BPlayers = new Vector();
	protected Vector fCPlayers = new Vector();
	protected Vector fOF1Players = new Vector();
	protected Vector fOF2Players = new Vector();
	protected Vector fOF3Players = new Vector();
	protected Vector fDHPlayers = new Vector();

	/**************************************************************************/

	protected void createWhichLineup(symantec.itools.awt.BorderPanel panel,
		int left,int top) throws Exception
	{
		fWhichLineupChc = new java.awt.Choice();
		panel.add(fWhichLineupChc);
		fWhichLineupChc.reshape(left,top,130,23);
		fWhichLineupChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

		fWhichLineupChc.addItem("Batters");
		fWhichLineupChc.addItem("Pitchers");
		fWhichLineupChc.select(0);
		fLastWhichLineup = 0;
	}

	/**************************************************************************/

	protected void createLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		f1BLbl = new jclass.bwt.JCLabel();
		f1BLbl.reshape(8,12,40,14);
		f1BLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(f1BLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "1B" : "SP");
			f1BLbl.setTextList(tempString);
		}
		f2BLbl = new jclass.bwt.JCLabel();
		f2BLbl.reshape(8,42,40,14);
		f2BLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(f2BLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "2B" : "SP");
			f2BLbl.setTextList(tempString);
		}
		fSSLbl = new jclass.bwt.JCLabel();
		fSSLbl.reshape(2,72,52,14);
		fSSLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fSSLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "SS" : "SP");
			fSSLbl.setTextList(tempString);
		}
		f3BLbl = new jclass.bwt.JCLabel();
		f3BLbl.reshape(8,102,40,14);
		f3BLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(f3BLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "3B" : "SP");
			f3BLbl.setTextList(tempString);
		}
		fCLbl = new jclass.bwt.JCLabel();
		fCLbl.reshape(8,132,40,14);
		fCLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fCLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "C" : "SP");
			fCLbl.setTextList(tempString);
		}
		fOF1Lbl = new jclass.bwt.JCLabel();
		fOF1Lbl.reshape(8,162,40,14);
		fOF1Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fOF1Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "OF" : "RP");
			fOF1Lbl.setTextList(tempString);
		}
		fOF2Lbl = new jclass.bwt.JCLabel();
		fOF2Lbl.reshape(8,192,40,14);
		fOF2Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fOF2Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "OF" : "RP");
			fOF2Lbl.setTextList(tempString);
		}
		fOF3Lbl = new jclass.bwt.JCLabel();
		fOF3Lbl.reshape(8,222,40,14);
		fOF3Lbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fOF3Lbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "OF" : "RP");
			fOF3Lbl.setTextList(tempString);
		}
		fDHLbl = new jclass.bwt.JCLabel();
		fDHLbl.reshape(8,252,40,14);
		fDHLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		panel.add(fDHLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String((fLastWhichLineup == 0) ? "DH" : "RP");
			fDHLbl.setTextList(tempString);
		}
	}

	/**************************************************************************/

	protected void removeLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(f1BLbl);
		panel.remove(f2BLbl);
		panel.remove(fSSLbl);
		panel.remove(f3BLbl);
		panel.remove(fCLbl);
		panel.remove(fOF1Lbl);
		panel.remove(fOF2Lbl);
		panel.remove(fOF3Lbl);
		panel.remove(fDHLbl);
	
		f1BLbl = null;
		f2BLbl = null;
		fSSLbl = null;
		f3BLbl = null;
		fCLbl = null;
		fOF1Lbl = null;
		fOF2Lbl = null;
		fOF3Lbl = null;
		fDHLbl = null;
	}

	/**************************************************************************/

	protected void createLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		f1BChc = new java.awt.Choice();
		panel.add(f1BChc);
		f1BChc.reshape(55,8,130,23);
		f1BChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		f2BChc = new java.awt.Choice();
		panel.add(f2BChc);
		f2BChc.reshape(55,38,130,23);
		f2BChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fSSChc = new java.awt.Choice();
		panel.add(fSSChc);
		fSSChc.reshape(55,68,130,23);
		fSSChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		f3BChc = new java.awt.Choice();
		panel.add(f3BChc);
		f3BChc.reshape(55,98,130,23);
		f3BChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fCChc = new java.awt.Choice();
		panel.add(fCChc);
		fCChc.reshape(55,128,130,23);
		fCChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fOF1Chc = new java.awt.Choice();
		panel.add(fOF1Chc);
		fOF1Chc.reshape(55,158,130,23);
		fOF1Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fOF2Chc = new java.awt.Choice();
		panel.add(fOF2Chc);
		fOF2Chc.reshape(55,188,130,23);
		fOF2Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fOF3Chc = new java.awt.Choice();
		panel.add(fOF3Chc);
		fOF3Chc.reshape(55,218,130,23);
		fOF3Chc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fDHChc = new java.awt.Choice();
		panel.add(fDHChc);
		fDHChc.reshape(55,248,130,23);
		fDHChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
	}

	/**************************************************************************/

	protected void removeLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception
	{
		panel.remove(f1BChc);
		panel.remove(f2BChc);
		panel.remove(fSSChc);
		panel.remove(f3BChc);
		panel.remove(fCChc);
		panel.remove(fOF1Chc);
		panel.remove(fOF2Chc);
		panel.remove(fOF3Chc);
		panel.remove(fDHChc);
	
		f1BChc = null;
		f2BChc = null;
		fSSChc = null;
		f3BChc = null;
		fCChc = null;
		fOF1Chc = null;
		fOF2Chc = null;
		fOF3Chc = null;
		fDHChc = null;
	}

	/**************************************************************************/

	protected void enableLineupChoices() throws Exception
	{
		f1BChc.enable(fLineupEnabled);
		f2BChc.enable(fLineupEnabled);
		fSSChc.enable(fLineupEnabled);
		f3BChc.enable(fLineupEnabled);
		fCChc.enable(fLineupEnabled);
		fOF1Chc.enable(fLineupEnabled);
		fOF2Chc.enable(fLineupEnabled);
		fOF3Chc.enable(fLineupEnabled);
		fDHChc.enable(fLineupEnabled);
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

		if(((pos >= 0) && (pos < fPlayerIDArray.size())) &&
			(pos != fLastWhichLineup))
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
		f1BPlayers.removeAllElements();
		f2BPlayers.removeAllElements();
		fSSPlayers.removeAllElements();
		f3BPlayers.removeAllElements();
		fCPlayers.removeAllElements();
		fOF1Players.removeAllElements();
		fOF2Players.removeAllElements();
		fOF3Players.removeAllElements();
		fDHPlayers.removeAllElements();
	}

	/**************************************************************************/

	protected void addOpenSlotToAllLineupVectorChoices() throws Exception
	{
		// Add 'open slot' to all Choices
		String emptyStr = "<open slot>";
		Integer zeroID = new Integer(0);

		addToLineupVectorChoice(f1BPlayers,f1BChc,zeroID,emptyStr);
		addToLineupVectorChoice(f2BPlayers,f2BChc,zeroID,emptyStr);
		addToLineupVectorChoice(fSSPlayers,fSSChc,zeroID,emptyStr);
		addToLineupVectorChoice(f3BPlayers,f3BChc,zeroID,emptyStr);
		addToLineupVectorChoice(fCPlayers,fCChc,zeroID,emptyStr);
		addToLineupVectorChoice(fOF1Players,fOF1Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fOF2Players,fOF2Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fOF3Players,fOF3Chc,zeroID,emptyStr);
		addToLineupVectorChoice(fDHPlayers,fDHChc,zeroID,emptyStr);
	}

	/**************************************************************************/

	protected void addPlayerToSelectLineupVectorChoices(LineupPlayer player)
		throws Exception
	{
		if(fLastWhichLineup == 0)
		{
			if(player.fPosition == TPosition.pos_FirstBaseman)
			{
				addPlayerToLineupVectorChoice(f1BPlayers,f1BChc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_SecondBaseman)
			{
				addPlayerToLineupVectorChoice(f2BPlayers,f2BChc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_ShortStop)
			{
				addPlayerToLineupVectorChoice(fSSPlayers,fSSChc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_ThirdBaseman)
			{
				addPlayerToLineupVectorChoice(f3BPlayers,f3BChc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_Catcher)
			{
				addPlayerToLineupVectorChoice(fCPlayers,fCChc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_Outfielder)
			{
				addPlayerToLineupVectorChoice(fOF1Players,fOF1Chc,player);
				addPlayerToLineupVectorChoice(fOF2Players,fOF2Chc,player);
				addPlayerToLineupVectorChoice(fOF3Players,fOF3Chc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_DesignatedHitter)
			{
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
			}
			else if(player.fPosition == TPosition.pos_StartingPitcher)
			{
			}
			else if(player.fPosition == TPosition.pos_ReliefPitcher)
			{
			}
			else
				throw new Exception("LineupApplet.addPlayerToSelectLineupVectorChoices: unknown position");
		}
		else
		{
			if(player.fPosition == TPosition.pos_FirstBaseman)
			{
			}
			else if(player.fPosition == TPosition.pos_SecondBaseman)
			{
			}
			else if(player.fPosition == TPosition.pos_ShortStop)
			{
			}
			else if(player.fPosition == TPosition.pos_ThirdBaseman)
			{
			}
			else if(player.fPosition == TPosition.pos_Catcher)
			{
			}
			else if(player.fPosition == TPosition.pos_Outfielder)
			{
			}
			else if(player.fPosition == TPosition.pos_DesignatedHitter)
			{
			}
			else if(player.fPosition == TPosition.pos_StartingPitcher)
			{
				addPlayerToLineupVectorChoice(f1BPlayers,f1BChc,player);
				addPlayerToLineupVectorChoice(f2BPlayers,f2BChc,player);
				addPlayerToLineupVectorChoice(fSSPlayers,fSSChc,player);
				addPlayerToLineupVectorChoice(f3BPlayers,f3BChc,player);
				addPlayerToLineupVectorChoice(fCPlayers,fCChc,player);
			}
			else if(player.fPosition == TPosition.pos_ReliefPitcher)
			{
				addPlayerToLineupVectorChoice(fOF1Players,fOF1Chc,player);
				addPlayerToLineupVectorChoice(fOF2Players,fOF2Chc,player);
				addPlayerToLineupVectorChoice(fOF3Players,fOF3Chc,player);
				addPlayerToLineupVectorChoice(fDHPlayers,fDHChc,player);
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

		if((lineup < 0) || (lineup >= fPlayerIDArray.size()))
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(lineup);
//BOB football		if(playerIDVector.size() != 8)
		if(playerIDVector.size() != 9)
			throw new Exception("LineupApplet.selAllLineupChoices: invalid lineup size");

		selLineupChoiceByID(f1BPlayers,f1BChc,(Integer)playerIDVector.elementAt(0));
		selLineupChoiceByID(f2BPlayers,f2BChc,(Integer)playerIDVector.elementAt(1));
		selLineupChoiceByID(fSSPlayers,fSSChc,(Integer)playerIDVector.elementAt(2));
		selLineupChoiceByID(f3BPlayers,f3BChc,(Integer)playerIDVector.elementAt(3));
		selLineupChoiceByID(fCPlayers,fCChc,(Integer)playerIDVector.elementAt(4));
		selLineupChoiceByID(fOF1Players,fOF1Chc,(Integer)playerIDVector.elementAt(5));
		selLineupChoiceByID(fOF2Players,fOF2Chc,(Integer)playerIDVector.elementAt(6));
		selLineupChoiceByID(fOF3Players,fOF3Chc,(Integer)playerIDVector.elementAt(7));
		selLineupChoiceByID(fDHPlayers,fDHChc,(Integer)playerIDVector.elementAt(8));
	}
	
	/**************************************************************************/

	protected boolean unloadAllLineupChoices() throws Exception
	{
		PlayerIDVector playerIDVector;

		if((fLastWhichLineup < 0) || (fLastWhichLineup >= fPlayerIDArray.size()))
			throw new Exception("LineupApplet.selAllLineupChoices: invalid selected lineup");

		playerIDVector = (PlayerIDVector)fPlayerIDArray.elementAt(fLastWhichLineup);
//BOB football		if(playerIDVector.size() != 8)
		if(playerIDVector.size() != 9)
			throw new Exception("LineupApplet.unloadAllLineupChoices: invalid lineup size");

		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(f1BPlayers,f1BChc),0);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(f2BPlayers,f2BChc),1);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fSSPlayers,fSSChc),2);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(f3BPlayers,f3BChc),3);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fCPlayers,fCChc),4);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fOF1Players,fOF1Chc),5);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fOF2Players,fOF2Chc),6);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fOF3Players,fOF3Chc),7);
		playerIDVector.setElementAt(getPlayerIDFromLineupChoice(fDHPlayers,fDHChc),8);

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
