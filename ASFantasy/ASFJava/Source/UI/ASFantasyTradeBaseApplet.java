/* ASFantasyTradeBaseApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.applet.*;
import java.io.*;
import java.util.*;
import jclass.bwt.*;
import jclass.util.*;

/******************************************************************************/
/******************************************************************************/

public abstract class ASFantasyTradeBaseApplet extends ASFBaseApplet
{
	protected TGameLevel fGameLevel = TGameLevel.gml_Standard;

	protected int fTradeID;
	protected int fTeamID;
	protected int fProposeToTeamID;
	protected PlayerIDVector fGetPlayerIDVector;		// first person relative
	protected PlayerIDVector fGivePlayerIDVector;		// first person relative
	protected PlayerIDVector fReleasePlayerIDVector;	// first person relative

	protected TeamInfoNameVector fTeamInfoVector = new TeamInfoNameVector();
	protected PlayerInfoVector fMyPlayerInfoVector = new PlayerInfoVector();		// first person relative
	protected PlayerInfoVector fTheirPlayerInfoVector = new PlayerInfoVector();	// first person relative
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Trade");
	}

	/**************************************************************************/

	protected ASFantasyRequestor newFantasyRequestor(String hostName,
		int hostPortID,String requestDll,String encodedParticID)
	{
		return(new ASFantasySeasonRequestor(hostName,hostPortID,requestDll,
			encodedParticID));
	}

	/**************************************************************************/

	protected void getTradeID()
	{
		String tradeIDStr = getParameter("TradeID");

		fTradeID = 0;
		if(tradeIDStr != null)
			fTradeID = Integer.parseInt(tradeIDStr);
	}

	/**************************************************************************/

	private void releasePlayerMessage(int numPlayers,boolean mustRelease)
	{
		String msg = "You ";

		if(mustRelease)
			msg += "must ";
		else
			msg += "may only ";

		if(numPlayers == 1)
			msg += "release 1 player. The player will not be released if your roster has room at the time the trade is processed.";
		else
			msg += "release of total of " + numPlayers + " players. The players will be release, as needed, in the order specified to make room on your roster at the time the trade is processed.";

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,msg);
	}

	/**************************************************************************/

	protected boolean validateReleasePlayers()
	{
		int newRosterSize;
		int numPlayers;
		String msg;
		int MaxPlayersPerTeam = 14;	//BOB move to AppOptions

		if(fReleasePlayerIDVector.doesContainDups(true))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You have selected to release the same player multiple times.  This is not allowed.");
			return(false);
		}

		// Determine if trade creates and inbalanced lineup. Always base on 
		// MaxPlayersPerTeam and not current roster size.
		newRosterSize = MaxPlayersPerTeam /*fMyPlayerInfoVector.size()*/
			+ fGetPlayerIDVector.size()
			- fGivePlayerIDVector.size() - fReleasePlayerIDVector.size();
		if(newRosterSize > MaxPlayersPerTeam)
		{
			numPlayers = /*fMyPlayerInfoVector.size() - MaxPlayersPerTeam + */
				fGetPlayerIDVector.size() - fGivePlayerIDVector.size();

			releasePlayerMessage(numPlayers,true);
			/*
			if(numPlayers == 1)
				msg = "You must release 1 player.";
			else
				msg = "You must release of total of " + numPlayers + " players.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*,msg);
			*/
			return(false);
		}
		else if(newRosterSize < MaxPlayersPerTeam)
		{
			if(MaxPlayersPerTeam /*fMyPlayerInfoVector.size()*/ + fGetPlayerIDVector.size()
				- fGivePlayerIDVector.size() > MaxPlayersPerTeam)
			{
				numPlayers = /*fMyPlayerInfoVector.size() - MaxPlayersPerTeam + */
					fGetPlayerIDVector.size() - fGivePlayerIDVector.size();

				releasePlayerMessage(numPlayers,false);
				/*
				if(numPlayers == 1)
					msg = "You may only release 1 player.";
				else
					msg = "You may only release of total of " + numPlayers + " players.";

				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*,msg);
				*/
				return(false);
			}
			else if(fReleasePlayerIDVector.size() > 0)
			{
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"You may not release any players for this trade.");
				return(false);
			}
		}

		// Are players being traded that are also being released?
		if(fGivePlayerIDVector.containsAny(fReleasePlayerIDVector,true))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You may not release players that are involved in the trade.");
			return(false);
		}

		return(true);
	}

}

/******************************************************************************/
/******************************************************************************/

