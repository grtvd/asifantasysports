/* ASFantasyPlayoffApplet.java */

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

public class ASFantasyPlayoffApplet extends ASFBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	jclass.bwt.JCLabel fLeagueChampTeamLbl;
	jclass.bwt.JCLabel fLeagueChampTagLbl;
	jclass.bwt.JCLabel fFinalistOneTeamLbl;
	jclass.bwt.JCLabel fFinalistOneTagLbl;
	jclass.bwt.JCLabel fFinalistTwoTeamLbl;
	jclass.bwt.JCLabel fFinalistTwoTagLbl;
	jclass.bwt.JCLabel fEastWinnerTeamLbl;
	jclass.bwt.JCLabel fEastWinnerTagLbl;
	jclass.bwt.JCLabel fWestWildCardTeamLbl;
	jclass.bwt.JCLabel fWestWildCardTagLbl;
	jclass.bwt.JCLabel fWestWinnerTeamLbl;
	jclass.bwt.JCLabel fWestWinnerTagLbl;
	jclass.bwt.JCLabel fEastWildCardTeamLbl;
	jclass.bwt.JCLabel fEastWildCardTagLbl;
	symantec.itools.awt.shape.VerticalLine verticalLine1;
	symantec.itools.awt.shape.VerticalLine verticalLine2;
	symantec.itools.awt.shape.VerticalLine verticalLine3;
	symantec.itools.awt.shape.HorizontalLine horizontalLine1;
	symantec.itools.awt.shape.HorizontalLine horizontalLine2;
	symantec.itools.awt.shape.HorizontalLine horizontalLine3;
	//}}
	
	PlayoffTeams fPlayoffTeams;
	TeamInfoNameByIDVector fTeamVector;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Playoff");
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

		getPlayoffs();

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(600,370);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,600,370);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fLeagueChampTeamLbl = new jclass.bwt.JCLabel();
		fLeagueChampTeamLbl.reshape(360,160,220,26);
		fLeagueChampTeamLbl.setFont(new Font("Dialog", Font.BOLD, 14));
		fLeagueChampTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fLeagueChampTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fLeagueChampTeamLbl.setTextList(tempString);
		}
		fLeagueChampTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fLeagueChampTeamLbl.setShadowThickness(2);
		fLeagueChampTagLbl = new jclass.bwt.JCLabel();
		fLeagueChampTagLbl.reshape(360,186,220,18);
		fLeagueChampTagLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fLeagueChampTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("League Champ");
			fLeagueChampTagLbl.setTextList(tempString);
		}
		fFinalistOneTeamLbl = new jclass.bwt.JCLabel();
		fFinalistOneTeamLbl.reshape(180,60,220,22);
		fFinalistOneTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fFinalistOneTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fFinalistOneTeamLbl.setTextList(tempString);
		}
		fFinalistOneTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fFinalistOneTeamLbl.setShadowThickness(2);
		fFinalistOneTagLbl = new jclass.bwt.JCLabel();
		fFinalistOneTagLbl.reshape(180,82,220,18);
		fFinalistOneTagLbl.setFont(new Font("Helvetica", Font.BOLD, 10));
		fBorderPnl.add(fFinalistOneTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Semi-Finalist");
			fFinalistOneTagLbl.setTextList(tempString);
		}
		fFinalistTwoTeamLbl = new jclass.bwt.JCLabel();
		fFinalistTwoTeamLbl.reshape(180,260,220,22);
		fFinalistTwoTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fFinalistTwoTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fFinalistTwoTeamLbl.setTextList(tempString);
		}
		fFinalistTwoTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fFinalistTwoTeamLbl.setShadowThickness(2);
		fFinalistTwoTagLbl = new jclass.bwt.JCLabel();
		fFinalistTwoTagLbl.reshape(180,282,220,18);
		fFinalistTwoTagLbl.setFont(new Font("Helvetica", Font.BOLD, 10));
		fBorderPnl.add(fFinalistTwoTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Semi-Finalist");
			fFinalistTwoTagLbl.setTextList(tempString);
		}
		fEastWinnerTeamLbl = new jclass.bwt.JCLabel();
		fEastWinnerTeamLbl.reshape(10,10,220,22);
		fEastWinnerTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fEastWinnerTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fEastWinnerTeamLbl.setTextList(tempString);
		}
		fEastWinnerTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fEastWinnerTeamLbl.setShadowThickness(2);
		fEastWinnerTagLbl = new jclass.bwt.JCLabel();
		fEastWinnerTagLbl.reshape(10,32,220,18);
		fEastWinnerTagLbl.setFont(new Font("Helvetica", Font.BOLD, 10));
		fBorderPnl.add(fEastWinnerTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("East Div Winner");
			fEastWinnerTagLbl.setTextList(tempString);
		}
		fWestWildCardTeamLbl = new jclass.bwt.JCLabel();
		fWestWildCardTeamLbl.reshape(10,110,220,22);
		fWestWildCardTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fWestWildCardTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fWestWildCardTeamLbl.setTextList(tempString);
		}
		fWestWildCardTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fWestWildCardTeamLbl.setShadowThickness(2);
		fWestWildCardTagLbl = new jclass.bwt.JCLabel();
		fWestWildCardTagLbl.reshape(10,132,220,18);
		fWestWildCardTagLbl.setFont(new Font("Helvetica", Font.BOLD, 10));
		fBorderPnl.add(fWestWildCardTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("West Div Wild Card");
			fWestWildCardTagLbl.setTextList(tempString);
		}
		fWestWinnerTeamLbl = new jclass.bwt.JCLabel();
		fWestWinnerTeamLbl.reshape(10,210,220,22);
		fWestWinnerTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fWestWinnerTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fWestWinnerTeamLbl.setTextList(tempString);
		}
		fWestWinnerTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fWestWinnerTeamLbl.setShadowThickness(2);
		fWestWinnerTagLbl = new jclass.bwt.JCLabel();
		fWestWinnerTagLbl.reshape(10,232,220,18);
		fWestWinnerTagLbl.setFont(new Font("Helvetica", Font.BOLD, 10));
		fBorderPnl.add(fWestWinnerTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("West Div Winner");
			fWestWinnerTagLbl.setTextList(tempString);
		}
		fEastWildCardTeamLbl = new jclass.bwt.JCLabel();
		fEastWildCardTeamLbl.reshape(10,310,220,22);
		fEastWildCardTeamLbl.setBackground(new Color(12632256));
		fBorderPnl.add(fEastWildCardTeamLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("(to be determined)");
			fEastWildCardTeamLbl.setTextList(tempString);
		}
		fEastWildCardTeamLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fEastWildCardTeamLbl.setShadowThickness(2);
		fEastWildCardTagLbl = new jclass.bwt.JCLabel();
		fEastWildCardTagLbl.reshape(10,332,220,18);
		fEastWildCardTagLbl.setFont(new Font("Helvetica", Font.BOLD, 10));
		fBorderPnl.add(fEastWildCardTagLbl);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("East Div Wild Card");
			fEastWildCardTagLbl.setTextList(tempString);
		}
		verticalLine1 = new symantec.itools.awt.shape.VerticalLine();
		verticalLine1.reshape(119,55,2,50);
		fBorderPnl.add(verticalLine1);
		verticalLine2 = new symantec.itools.awt.shape.VerticalLine();
		verticalLine2.reshape(119,255,2,50);
		fBorderPnl.add(verticalLine2);
		verticalLine3 = new symantec.itools.awt.shape.VerticalLine();
		verticalLine3.reshape(289,107,2,145);
		fBorderPnl.add(verticalLine3);
		horizontalLine1 = new symantec.itools.awt.shape.HorizontalLine();
		horizontalLine1.reshape(121,71,50,2);
		fBorderPnl.add(horizontalLine1);
		horizontalLine2 = new symantec.itools.awt.shape.HorizontalLine();
		horizontalLine2.reshape(121,270,50,2);
		fBorderPnl.add(horizontalLine2);
		horizontalLine3 = new symantec.itools.awt.shape.HorizontalLine();
		horizontalLine3.reshape(291,172,60,2);
		fBorderPnl.add(horizontalLine3);
		//}}

		loadData();
	}

	/**************************************************************************/

	protected void getPlayoffs() throws IOException
	{
		PlayoffResp pResponse =
			((ASFantasySeasonRequestor)fAppRequestor).playoffRequest();

		if(pResponse == null)
		{
			String msg = "Unable to access playoff data.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fPlayoffTeams = pResponse.fPlayoffTeams;
		fTeamVector = pResponse.fTeamInfoNameVector;
	}
	
	/**************************************************************************/

	protected void loadData()
	{
		fEastWinnerTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fEastWinnerTeamID,fPlayoffTeams.fEastWinnerScore));
		fWestWildCardTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fWestWildCardTeamID,fPlayoffTeams.fWestWildCardScore));

		fWestWinnerTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fWestWinnerTeamID,fPlayoffTeams.fWestWinnerScore));
		fEastWildCardTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fEastWildCardTeamID,fPlayoffTeams.fEastWildCardScore));

		fFinalistOneTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fFinalistOneTeamID,fPlayoffTeams.fFinalistOneScore));
		fFinalistTwoTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fFinalistTwoTeamID,fPlayoffTeams.fFinalistTwoScore));

		fLeagueChampTeamLbl.setText(buildTeamLabel(
			fPlayoffTeams.fLeagueChampTeamID,(byte)0));
	}

	/**************************************************************************/

	protected String buildTeamLabel(int teamID,byte score)
	{
		if(teamID != 0)
		{
			TeamInfoName team = fTeamVector.getByID(teamID);

			if(score != 0)
				return(team.buildName() + " - " + score);
			return(team.buildName());
		}

		return("");
	}

}

/******************************************************************************/
/******************************************************************************/

