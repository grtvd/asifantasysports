/* ASFantasyTradeProtestApplet.java */

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

public class ASFantasyTradeProtestApplet extends ASFantasyTradeBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	java.awt.Button fProtestBtn;
	jclass.bwt.JCLabel fTradeTeamsLbl;
	symantec.itools.awt.BorderPanel fGivePlayersPnl;
	symantec.itools.awt.BorderPanel fGetPlayersPnl;
	//}}

	ASFantasyTradeGiveOnlyPnl fTradeGiveOnlyPnl;
	ASFantasyTradeGetPnl fTradeGetPnl;

	boolean fEnable;

	/**************************************************************************/

	public void open() throws Exception
	{
		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getTradeProtest();

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
		fProtestBtn = new java.awt.Button("Protest");
		fProtestBtn.reshape(8,8,70,20);
		fProtestBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fProtestBtn);
		fTradeTeamsLbl = new jclass.bwt.JCLabel();
		fTradeTeamsLbl.reshape(140,6,445,18);
		fBorderPnl.add(fTradeTeamsLbl);
		fTradeTeamsLbl.setAlignment(jclass.bwt.JCLabel.BOTTOMLEFT);
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

		fTradeGiveOnlyPnl = new ASFantasyTradeGiveOnlyPnl(fGameLevel);
		fTradeGiveOnlyPnl.setLayout(null);
		fTradeGiveOnlyPnl.move(0, 0);
		fGivePlayersPnl.add(fTradeGiveOnlyPnl);
		fTradeGiveOnlyPnl.open();

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
			if(evt.target == fProtestBtn)
			{
				fProtestBtn.enable(false);
				enable(false);
				updateTradeProtest();
				enable(true);
				fProtestBtn.enable(fEnable);
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void getTradeProtest() throws IOException
	{
		TradeProposeQueryResp pResponse = null;

		getTradeID();
		if(fTradeID != 0)
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
		fEnable = pResponse.fEnableChanges;
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
	}

	/**************************************************************************/

	protected void updateTradeProtest()
	{
		TradeProtestUpdateResp pResponse;

		pResponse = ((ASFantasySeasonRequestor)
			fAppRequestor).tradeProtestUpdateRequest(fTradeID);

		if(pResponse == null)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Unable to save your trade protest.  Please try again later.");
			return;
		}

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
			"Your trade protest has been saved.");

		fEnable = false;
		enableData();
	}
	
	/**************************************************************************/

	protected void loadData() throws Exception
	{
		loadTradeTeams();

		fTradeGiveOnlyPnl.loadData(fMyPlayerInfoVector,fGivePlayerIDVector);
		fTradeGetPnl.loadData(fTheirPlayerInfoVector,fGetPlayerIDVector);

		enableData();
	}
	
	/**************************************************************************/

	protected void loadTradeTeams() throws Exception
	{
		TeamInfoName teamInfo;
		TeamInfoName proposeToTeamInfo;

		// Propose By Team
		teamInfo = fTeamInfoVector.getByID(fTeamID);
		if(teamInfo == null)
			throw new Exception("TradeProtestApplet.loadTradeTeams: propose by team not found");

		// Propose To Team
		proposeToTeamInfo = fTeamInfoVector.getByID(fProposeToTeamID);
		if(proposeToTeamInfo == null)
			throw new Exception("TradeProtestApplet.loadTradeTeams: propose to team not found");
				
		fTradeTeamsLbl.setText(teamInfo.buildName() + " are proposing a trade to the " +
			proposeToTeamInfo.buildName());
	}

	/**************************************************************************/

	protected void enableData()
	{
		fProtestBtn.enable(fEnable);

		fTradeGiveOnlyPnl.enablePlayers(false);
		fTradeGetPnl.enablePlayers(false);
	}

}

/******************************************************************************/
/******************************************************************************/

