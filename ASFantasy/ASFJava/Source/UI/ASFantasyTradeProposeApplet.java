/* ASFantasyTradeProposeApplet.java */

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

public class ASFantasyTradeProposeApplet extends ASFantasyTradeBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	java.awt.Button fSubmitBtn;
	java.awt.Button fClearBtn;
	jclass.bwt.JCLabel fProposeToLbl;
	java.awt.Choice fProposeToChc;
	symantec.itools.awt.BorderPanel fGivePlayersPnl;
	symantec.itools.awt.BorderPanel fGetPlayersPnl;
	//}}

	private ASFantasyTradeGiveReleasePnl fTradeGiveReleasePnl;
	private ASFantasyTradeGetPnl fTradeGetPnl;

	private boolean fEnableSubmit;
	private boolean fEnableClear;
	
	/**************************************************************************/

	public void open() throws Exception
	{
		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getTradePropose();

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(600,450);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,600,450);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setIPadTop(1);
		fBorderPnl.setIPadBottom(1);
		fBorderPnl.setIPadSides(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fSubmitBtn = new java.awt.Button("Submit");
		fSubmitBtn.reshape(8,8,70,20);
		fSubmitBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fSubmitBtn);
		fClearBtn = new java.awt.Button("Clear");
		fClearBtn.reshape(86,8,70,20);
		fClearBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fClearBtn);
		fProposeToLbl = new jclass.bwt.JCLabel();
		fProposeToLbl.reshape(164,6,130,18);
		fProposeToLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fProposeToLbl);
		fProposeToLbl.setAlignment(jclass.bwt.JCLabel.BOTTOMRIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Propose Trade To");
			fProposeToLbl.setTextList(tempString);
		}
		fProposeToChc = new java.awt.Choice();
		fBorderPnl.add(fProposeToChc);
		fProposeToChc.reshape(302,4,280,23);
		fGivePlayersPnl = new symantec.itools.awt.BorderPanel();
		fGivePlayersPnl.setLayout(null);
		fGivePlayersPnl.reshape(7,32,288,406);
		fBorderPnl.add(fGivePlayersPnl);
		fGivePlayersPnl.setPaddingTop(1);
		fGivePlayersPnl.setPaddingBottom(1);
		fGivePlayersPnl.setPaddingLeft(1);
		fGivePlayersPnl.setPaddingRight(1);
		fGivePlayersPnl.setIPadTop(1);
		fGivePlayersPnl.setIPadBottom(1);
		fGivePlayersPnl.setIPadSides(1);
		fGivePlayersPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fGetPlayersPnl = new symantec.itools.awt.BorderPanel();
		fGetPlayersPnl.setLayout(null);
		fGetPlayersPnl.reshape(301,32,288,406);
		fBorderPnl.add(fGetPlayersPnl);
		fGetPlayersPnl.setPaddingTop(1);
		fGetPlayersPnl.setPaddingBottom(1);
		fGetPlayersPnl.setPaddingLeft(1);
		fGetPlayersPnl.setPaddingRight(1);
		fGetPlayersPnl.setIPadTop(1);
		fGetPlayersPnl.setIPadBottom(1);
		fGetPlayersPnl.setIPadSides(1);
		fGetPlayersPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		//}}

		fTradeGiveReleasePnl = new ASFantasyTradeGiveReleasePnl(fGameLevel);
		fTradeGiveReleasePnl.setLayout(null);
		fTradeGiveReleasePnl.move(0, 0);
		fGivePlayersPnl.add(fTradeGiveReleasePnl);
		fTradeGiveReleasePnl.open();

		loadData();
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fSubmitBtn)
			{
				fSubmitBtn.enable(false);
				enable(false);
				if(unloadData())
					updateTradePropose(false);
				enable(true);
				fSubmitBtn.enable(fEnableSubmit);
			}
			else if(evt.target == fClearBtn)
			{
				fClearBtn.enable(false);
				enable(false);
				updateTradePropose(true);
				enable(true);
				fClearBtn.enable(fEnableClear);
			}
			else if(evt.target == fProposeToChc)
			{
				showProposeToTeam();
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void getTradePropose() throws IOException
	{
		TradeProposeQueryResp pResponse;

		getTradeID();
		pResponse = ((ASFantasySeasonRequestor)
			fAppRequestor).tradeProposeQueryRequest(fTradeID);

		if(pResponse == null)
		{
			String msg = "Unable to access your trade and roster information.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameLevel = pResponse.fGameLevel;

		fTradeID = pResponse.fTradeID;
		if(fTradeID == 0)
		{
			fEnableSubmit = true;
			fEnableClear = true;
		}
		else
		{
			fEnableSubmit = false;
			fEnableClear = pResponse.fEnableChanges;
		}
		fTeamID = pResponse.fTeamID;
		fProposeToTeamID = pResponse.fProposeToTeamID;
		fGetPlayerIDVector = pResponse.fGetPlayerIDVector;
		fGivePlayerIDVector = pResponse.fGivePlayerIDVector;
		fReleasePlayerIDVector = pResponse.fReleasePlayerIDVector;

		fTeamInfoVector = pResponse.fTeamInfoVector;
		fMyPlayerInfoVector = pResponse.fMyPlayerInfoVector;
		fTheirPlayerInfoVector = pResponse.fTheirPlayerInfoVector;

		TAGVectorSorter.quickSort(fMyPlayerInfoVector,new PlayerInfoByNameCmpr());
		TAGVectorSorter.quickSort(fTheirPlayerInfoVector,new PlayerInfoByNameCmpr());

		// Remove self from TeamInfoVector
		fTeamInfoVector.removeByID(fTeamID);
	}

	/**************************************************************************/

	protected void updateTradePropose(boolean clear)
	{
		TradeProposeUpdateResp pResponse;
		int proposeToTeamID = fProposeToTeamID;
		String msg;

		if(clear)
		{
			proposeToTeamID = 0;
			fGetPlayerIDVector.removeAllElements();
			fGivePlayerIDVector.removeAllElements();
			fReleasePlayerIDVector.removeAllElements();
		}
				
		if((clear && (fTradeID != 0)) || !clear)
//		if((clear && (fTradeID != 0)) || (!clear && (fTradeID == 0)))
		{
			pResponse = ((ASFantasySeasonRequestor)
				fAppRequestor).tradeProposeUpdateRequest(fTradeID,
				proposeToTeamID,fGetPlayerIDVector,fGivePlayerIDVector,
				fReleasePlayerIDVector);

			if(pResponse == null)
			{
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"Unable to " + (clear ? "clear" : "save") +
					" your trade proposal.  Please try again later.");
				return;
			}

			fTradeID = pResponse.fTradeID;
		}

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
			"Your trade proposal has been " + (clear ? "cleared." : "saved."));

		if(clear)
		{
			fProposeToTeamID = 0;
			fProposeToChc.select(0);
			if(fTradeGiveReleasePnl != null)
				fTradeGiveReleasePnl.clear();
			closeTradeGetPnl();
		}

		fEnableSubmit = (fTradeID == 0);
		fEnableClear = true;
		enableData();
	}
	
	/**************************************************************************/

	protected void getTradeProposeTeam(int proposeToTeamID) throws IOException
	{
		TradeProposeTeamResp pResponse = ((ASFantasySeasonRequestor)
			fAppRequestor).tradeProposeTeamRequest(proposeToTeamID);

		if(pResponse == null)
		{
			String msg = "Unable to access team's roster information.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fProposeToTeamID = proposeToTeamID;
		fGetPlayerIDVector.removeAllElements();
		fTheirPlayerInfoVector = pResponse.fPlayerInfoVector;

		TAGVectorSorter.quickSort(fTheirPlayerInfoVector,new PlayerInfoByNameCmpr());
	}

	/**************************************************************************/

	protected void showProposeToTeam()
	{
		int pos = fProposeToChc.getSelectedIndex();

		if((pos >= 1) && (pos <= fTeamInfoVector.size()))
		{
			int teamID = ((TeamInfoName)fTeamInfoVector.elementAt(pos - 1)).fTeamID;
			
			if(teamID != fProposeToTeamID)
			{
				enable(false);
				try
				{
					getTradeProposeTeam(teamID);
					openTradeGetPnl();
				}
				catch(Exception e)
				{
				}
				enable(true);
			}
		}
		else
		{
			fProposeToTeamID = 0;
			closeTradeGetPnl();
		}
	}
	
	/**************************************************************************/

	protected void loadData() throws Exception
	{
		loadProposeToTeams();

		fTradeGiveReleasePnl.loadData(fMyPlayerInfoVector,fGivePlayerIDVector,
			fReleasePlayerIDVector);

		if(fProposeToTeamID != 0)
			openTradeGetPnl();

		enableData();
	}
	
	/**************************************************************************/

	protected void loadProposeToTeams() throws Exception
	{
		TeamInfoName teamInfo;
		int i,numItems;
		int pos;
		
		// Load fShowLinupChc.
		fProposeToChc.addItem("<Select Team>");

		numItems = fTeamInfoVector.size();
		for(i = 0; i < numItems; i++)
		{
			teamInfo = (TeamInfoName)fTeamInfoVector.elementAt(i);
			fProposeToChc.addItem(teamInfo.buildName());
		}

		// Select team to be shown
		if(fProposeToTeamID != 0)
		{
			pos = fTeamInfoVector.getPosByID(fProposeToTeamID);

			if(pos == -1)
				throw new Exception("TradeProposeApplet.loadProposeToTeams: propose to team not found");
				
			fProposeToChc.select(pos + 1);
		}
	}

	/**************************************************************************/

	protected void enableData()
	{
		fSubmitBtn.enable(fEnableSubmit);
		fClearBtn.enable(fEnableClear);
		fProposeToChc.enable(fEnableSubmit);

		fTradeGiveReleasePnl.enablePlayers(fEnableSubmit,fEnableSubmit);

		if(fTradeGetPnl != null)
			fTradeGetPnl.enablePlayers(fEnableSubmit);
	}

	/**************************************************************************/

	protected boolean unloadData()
	{
		if(fProposeToTeamID == 0)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You have not selected the team for your trade proposal.");
			return(false);
		}

		// Should not happen.
		if((fTradeGiveReleasePnl == null) || (fTradeGetPnl == null))
			return(false);

		fTradeGiveReleasePnl.unloadData(fMyPlayerInfoVector,fGivePlayerIDVector,
			fReleasePlayerIDVector);
		fTradeGetPnl.unloadData(fTheirPlayerInfoVector,fGetPlayerIDVector);

		if(fGetPlayerIDVector.size() == 0)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You must select at least one player to receive in the trade.");
			return(false);
		}

		if(fGetPlayerIDVector.doesContainDups(true))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You have selected to receive the same player multiple times.  This is not allowed.");
			return(false);
		}


		if(fGivePlayerIDVector.size() == 0)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You must select at least one player to give away in the trade.");
			return(false);
		}

		if(fGivePlayerIDVector.doesContainDups(true))
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You have selected to give away the same player multiple times.  This is not allowed.");
			return(false);
		}

		return(validateReleasePlayers());
	}

	/**************************************************************************/

	protected void openTradeGetPnl() throws Exception
	{
		closeTradeGetPnl();

		fTradeGetPnl = new ASFantasyTradeGetPnl(fGameLevel);
		fTradeGetPnl.show(false);
		fTradeGetPnl.setLayout(null);
		fTradeGetPnl.move(0, 0);
		fGetPlayersPnl.add(fTradeGetPnl);
		fTradeGetPnl.open();

		fTradeGetPnl.loadData(fTheirPlayerInfoVector,fGetPlayerIDVector);
		fTradeGetPnl.show(true);
	}

	/**************************************************************************/

	protected void closeTradeGetPnl()
	{
		if(fTradeGetPnl != null)
		{
			fTradeGetPnl.show(false);
			fTradeGetPnl.remove(fGetPlayersPnl);
			fTradeGetPnl = null;
		}
	}

}

/******************************************************************************/
/******************************************************************************/

