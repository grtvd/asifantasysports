/* ASFantasyTradeReceiveApplet.java */

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

public class ASFantasyTradeReceiveApplet extends ASFantasyTradeBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	java.awt.Button fAcceptBtn;
	java.awt.Button fDeclineBtn;
	jclass.bwt.JCLabel fProposedByTagLbl;
	jclass.bwt.JCLabel fProposedByLbl;
	symantec.itools.awt.BorderPanel fGivePlayersPnl;
	symantec.itools.awt.BorderPanel fGetPlayersPnl;
	//}}

	ASFantasyTradeGiveReleasePnl fTradeGiveReleasePnl;
	ASFantasyTradeGetPnl fTradeGetPnl;

	boolean fEnable;
	
	/**************************************************************************/

	public void open() throws Exception
	{
		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getTradeReceive();

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(600,450);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,600,450);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fBorderPnl.setBackground(new Color(12632256));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setIPadTop(1);
		fBorderPnl.setIPadBottom(1);
		fBorderPnl.setIPadSides(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fAcceptBtn = new java.awt.Button("Accept");
		fAcceptBtn.reshape(8,8,70,20);
		fAcceptBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fAcceptBtn);
		fDeclineBtn = new java.awt.Button("Decline");
		fDeclineBtn.reshape(86,8,70,20);
		fDeclineBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fDeclineBtn);
		fProposedByTagLbl = new jclass.bwt.JCLabel();
		fProposedByTagLbl.reshape(164,6,130,18);
		fProposedByTagLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fProposedByTagLbl);
		fProposedByTagLbl.setAlignment(jclass.bwt.JCLabel.BOTTOMRIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Trade Proposed By");
			fProposedByTagLbl.setTextList(tempString);
		}
		fProposedByLbl = new jclass.bwt.JCLabel();
		fProposedByLbl.reshape(301,6,288,18);
		fBorderPnl.add(fProposedByLbl);
		fProposedByLbl.setAlignment(jclass.bwt.JCLabel.BOTTOMLEFT);
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

		fTradeGetPnl = new ASFantasyTradeGetPnl(fGameLevel);
		fTradeGetPnl.setLayout(null);
		fTradeGetPnl.move(0, 0);
		fGetPlayersPnl.add(fTradeGetPnl);
		fTradeGetPnl.open();

		loadData();
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fAcceptBtn)
			{
				fAcceptBtn.enable(false);
				enable(false);
				if(unloadData())
					updateTradeReceive(false);
				enable(true);
				fAcceptBtn.enable(fEnable);
			}
			else if(evt.target == fDeclineBtn)
			{
				fDeclineBtn.enable(false);
				enable(false);
				updateTradeReceive(true);
				enable(true);
				fDeclineBtn.enable(fEnable);
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void getTradeReceive() throws IOException
	{
		TradeProposeQueryResp pResponse;

		getTradeID();
		pResponse = ((ASFantasySeasonRequestor)
			fAppRequestor).tradeProposeQueryRequest(fTradeID);

		if(pResponse == null)
		{
			String msg = "Unable to access the trade information.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameLevel = pResponse.fGameLevel;

		fTradeID = pResponse.fTradeID;
		if(fTradeID == 0)
			throw new IOException("Unknown trade ID.");

		fEnable = pResponse.fEnableChanges;
		fTeamID = pResponse.fTeamID;
		fProposeToTeamID = pResponse.fProposeToTeamID;

		// Since this is received trade, the get and give must be flipped
		fGetPlayerIDVector = pResponse.fGivePlayerIDVector;			//flipped
		fGivePlayerIDVector = pResponse.fGetPlayerIDVector;			//flipped
		fReleasePlayerIDVector = pResponse.fReleasePlayerIDVector;

		fTeamInfoVector = pResponse.fTeamInfoVector;
		fMyPlayerInfoVector = pResponse.fTheirPlayerInfoVector;		//flipped
		fTheirPlayerInfoVector = pResponse.fMyPlayerInfoVector;		//flipped

		TAGVectorSorter.quickSort(fMyPlayerInfoVector,new PlayerInfoByNameCmpr());
		TAGVectorSorter.quickSort(fTheirPlayerInfoVector,new PlayerInfoByNameCmpr());
	}

	/**************************************************************************/

	protected void updateTradeReceive(boolean decline)
	{
		TradeReceiveUpdateResp pResponse;

		pResponse = ((ASFantasySeasonRequestor)
			fAppRequestor).tradeReceiveUpdateRequest(fTradeID,!decline,
			fReleasePlayerIDVector);

		if(pResponse == null)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Unable to save your trade response.  Please try again later.");
			return;
		}

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
			"Your " + (decline ? "'decline'" : "'accept'") + " trade response has been saved.");

		fEnable = false;
		enableData();
	}
	
	/**************************************************************************/

	protected void loadData() throws Exception
	{
		loadProposedByTeam();

		fTradeGiveReleasePnl.loadData(fMyPlayerInfoVector,fGivePlayerIDVector,
			fReleasePlayerIDVector);
		fTradeGetPnl.loadData(fTheirPlayerInfoVector,fGetPlayerIDVector);

		enableData();
	}
	
	/**************************************************************************/

	protected void loadProposedByTeam() throws Exception
	{
		TeamInfoName teamInfo;

		// Propose By Team
		teamInfo = fTeamInfoVector.getByID(fTeamID);
		if(teamInfo == null)
			throw new Exception("TradeReceiveApplet.loadTradeTeams: propose by team not found");
				
		fProposedByLbl.setText(teamInfo.buildName());
	}

	/**************************************************************************/

	protected void enableData()
	{
		fAcceptBtn.enable(fEnable);
		fDeclineBtn.enable(fEnable);

		fTradeGiveReleasePnl.enablePlayers(false,fEnable);
		fTradeGetPnl.enablePlayers(false);
	}

	/**************************************************************************/

	protected boolean unloadData()
	{
		fTradeGiveReleasePnl.unloadData(fMyPlayerInfoVector,fGivePlayerIDVector,
			fReleasePlayerIDVector);

		return(validateReleasePlayers());
	}

}

/******************************************************************************/
/******************************************************************************/

