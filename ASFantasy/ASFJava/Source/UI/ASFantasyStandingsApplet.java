/* ASFantasyStandingsApplet.java */

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

public class ASFantasyStandingsApplet extends ASFBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	jclass.bwt.JCLabel fEastTeamsLbl;
	jclass.bwt.JCMultiColumnList fEastTeamsMCLst;
	jclass.bwt.JCLabel fWestTeamsLbl;
	jclass.bwt.JCMultiColumnList fWestTeamsMCLst;
	jclass.bwt.JCLabel jCLabel1;
	jclass.bwt.JCLabel jCLabel2;
	//}}
	
	TeamInfoNameVector fEastTeamVector;
	TeamInfoNameVector fWestTeamVector;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Standings");
	}

	/**************************************************************************/

	protected ASFantasyRequestor newFantasyRequestor(String hostName,
		int hostPortID,String requestDll,String encodedParticID)
	{
		return(new ASFantasySeasonRequestor(hostName,hostPortID,requestDll,
			encodedParticID));
	}

	/**************************************************************************/

	public void open() throws Exception
	{
		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getStandings();

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(510,415);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,510,415);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fEastTeamsLbl = new jclass.bwt.JCLabel();
		fEastTeamsLbl.reshape(8,8,195,14);
		fEastTeamsLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fEastTeamsLbl.setForeground(new Color(0));
		fEastTeamsLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fEastTeamsLbl);
		fEastTeamsLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("East Division Teams");
			fEastTeamsLbl.setTextList(tempString);
		}
		fEastTeamsLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_NONE);
		fEastTeamsMCLst = new jclass.bwt.JCMultiColumnList();
		fEastTeamsMCLst.reshape(8,28,485,170);
		fEastTeamsMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fEastTeamsMCLst);
		fEastTeamsMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fEastTeamsMCLst.setSelectedBackground(new Color(255));
		fWestTeamsLbl = new jclass.bwt.JCLabel();
		fWestTeamsLbl.reshape(8,208,195,14);
		fWestTeamsLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fWestTeamsLbl.setForeground(new Color(0));
		fWestTeamsLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fWestTeamsLbl);
		fWestTeamsLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("West Division Teams");
			fWestTeamsLbl.setTextList(tempString);
		}
		fWestTeamsLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_NONE);
		fWestTeamsMCLst = new jclass.bwt.JCMultiColumnList();
		fWestTeamsMCLst.reshape(8,228,485,170);
		fWestTeamsMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fWestTeamsMCLst);
		fWestTeamsMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fWestTeamsMCLst.setSelectedBackground(new Color(255));
		jCLabel1 = new jclass.bwt.JCLabel();
		jCLabel1.reshape(331,12,90,16);
		jCLabel1.setFont(new Font("Helvetica", Font.BOLD, 12));
		jCLabel1.setBackground(new Color(8421504));
		fBorderPnl.add(jCLabel1);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Div");
			jCLabel1.setTextList(tempString);
		}
		jCLabel1.setShadowType(jclass.bwt.JCLabel.SHADOW_NONE);
		jCLabel2 = new jclass.bwt.JCLabel();
		jCLabel2.reshape(331,212,90,16);
		jCLabel2.setFont(new Font("Helvetica", Font.BOLD, 12));
		jCLabel2.setBackground(new Color(8421504));
		fBorderPnl.add(jCLabel2);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Div");
			jCLabel2.setTextList(tempString);
		}
		jCLabel2.setShadowType(jclass.bwt.JCLabel.SHADOW_NONE);
		//}}

		java.awt.Font font = new java.awt.Font("Helvetica",java.awt.Font.BOLD,12);
		Color color = new Color(12632256);

		jclass.bwt.JCHeader header = fEastTeamsMCLst.getHeader();
		header.setFont(font);
		header.setBackground(color);
		header.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(6,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(7,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(8,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(9,BWTEnum.MIDDLELEFT);

		header = fWestTeamsMCLst.getHeader();
		header.setFont(font);
		header.setBackground(color);
		header.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(6,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(7,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(8,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(9,BWTEnum.MIDDLELEFT);

		{
			java.lang.String[] tempString = new java.lang.String[10];
			tempString[0] = new java.lang.String("Team");
			tempString[1] = new java.lang.String("W");
			tempString[2] = new java.lang.String("L");
			tempString[3] = new java.lang.String("T");
			tempString[4] = new java.lang.String("Pct.");
			tempString[5] = new java.lang.String("Pts.");
			tempString[6] = new java.lang.String("W");
			tempString[7] = new java.lang.String("L");
			tempString[8] = new java.lang.String("T");
			tempString[9] = new java.lang.String("Streak");

			fEastTeamsMCLst.setColumnButtons(tempString);
			fWestTeamsMCLst.setColumnButtons(tempString);
		}
		fEastTeamsMCLst.setSelectedForeground(Color.white);
		fWestTeamsMCLst.setSelectedForeground(Color.white);

		fEastTeamsMCLst.setNumColumns(10);
		fWestTeamsMCLst.setNumColumns(10);

		fEastTeamsMCLst.setColumnWidth(0,142);
		fEastTeamsMCLst.setColumnWidth(1,30);
		fEastTeamsMCLst.setColumnWidth(2,30);
		fEastTeamsMCLst.setColumnWidth(3,30);
		fEastTeamsMCLst.setColumnWidth(4,45);
		fEastTeamsMCLst.setColumnWidth(5,45);
		fEastTeamsMCLst.setColumnWidth(6,30);
		fEastTeamsMCLst.setColumnWidth(7,30);
		fEastTeamsMCLst.setColumnWidth(8,30);
		fEastTeamsMCLst.setColumnWidth(9,55);

		fWestTeamsMCLst.setColumnWidth(0,142);
		fWestTeamsMCLst.setColumnWidth(1,30);
		fWestTeamsMCLst.setColumnWidth(2,30);
		fWestTeamsMCLst.setColumnWidth(3,30);
		fWestTeamsMCLst.setColumnWidth(4,45);
		fWestTeamsMCLst.setColumnWidth(5,45);
		fWestTeamsMCLst.setColumnWidth(6,30);
		fWestTeamsMCLst.setColumnWidth(7,30);
		fWestTeamsMCLst.setColumnWidth(8,30);
		fWestTeamsMCLst.setColumnWidth(9,55);

		fEastTeamsMCLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		fEastTeamsMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(6,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(7,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(8,BWTEnum.MIDDLECENTER);
		fEastTeamsMCLst.setColumnAlignment(9,BWTEnum.MIDDLELEFT);

		fWestTeamsMCLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		fWestTeamsMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(6,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(7,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(8,BWTEnum.MIDDLECENTER);
		fWestTeamsMCLst.setColumnAlignment(9,BWTEnum.MIDDLELEFT);

		fEastTeamsMCLst.setAutoSelect(true);
		fWestTeamsMCLst.setAutoSelect(true);
		fEastTeamsMCLst.getList().setBackground(Color.white);
		fWestTeamsMCLst.getList().setBackground(Color.white);

		loadData();
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			/*
			if(evt.target == fSubmitBtn)
			{
				fSubmitBtn.enable(false);
				if(unloadPlayerIDVector())
					updateGameResult();
				fSubmitBtn.enable(true);
			}
			else
			*/
				return false;
		}
		else
			return false;

//BOB		return true;
	}

	/**************************************************************************/

	protected void getStandings() throws IOException
	{
		StandingsResp pResponse =
			((ASFantasySeasonRequestor)fAppRequestor).standingsRequest();

		if(pResponse == null)
		{
			String msg = "Unable to access your standings.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fEastTeamVector = pResponse.fEastTeamVector;
		fWestTeamVector = pResponse.fWestTeamVector;
	}

	/**************************************************************************/

	protected void loadData()
	{
		loadTeamList(fEastTeamsMCLst,fEastTeamVector);
		loadTeamList(fWestTeamsMCLst,fWestTeamVector);
	}
	
	/**************************************************************************/

	protected void loadTeamList(jclass.bwt.JCMultiColumnList teamsMCLst,
		TeamInfoNameVector teamVector)
	{
		StandingsTeam team;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = teamVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			team = (StandingsTeam)teamVector.elementAt(i);

			row = new JCVector();
			row.addElement(team.buildName());
			row.addElement(new Integer(team.fWins));
			row.addElement(new Integer(team.fLoses));
			row.addElement(new Integer(team.fTies));
			row.addElement(team.fWinPercent);
			row.addElement(new Integer(team.fTotalPoints));
			row.addElement(new Integer(team.fDivWins));
			row.addElement(new Integer(team.fDivLoses));
			row.addElement(new Integer(team.fDivTies));
			row.addElement(buildStreakString(team.fStreak));
			items.addElement(row);
		}
		
		teamsMCLst.setItems(items);
	}

	/**************************************************************************/

	protected String buildStreakString(short streak)
	{
		if(streak > 0)
			return("Won " + Integer.toString(streak));
		else if(streak < 0)
			return("Lost " + Integer.toString(-streak));
		else
			return("None");
	}
}

/******************************************************************************/
/******************************************************************************/

