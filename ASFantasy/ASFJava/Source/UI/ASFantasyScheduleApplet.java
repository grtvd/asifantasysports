/* ASFantasyScheduleApplet.java */

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

public class ASFantasyScheduleApplet extends ASFBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	jclass.bwt.JCMultiColumnList fGamesMCLst;
	//}}
	
	Vector fGameVector;
	TeamInfoNameByIDVector fTeamVector;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Schedule");
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

		getSchedule();

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(344,345);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,344,345);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fGamesMCLst = new jclass.bwt.JCMultiColumnList();
		fGamesMCLst.reshape(8,8,320,321);
		fGamesMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fGamesMCLst);
		fGamesMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		{
			java.lang.String[] tempString = new java.lang.String[3];
			tempString[0] = new java.lang.String("Week");
			tempString[1] = new java.lang.String("Opponent");
			tempString[2] = new java.lang.String("Result");
			fGamesMCLst.setColumnButtons(tempString);
		}
		fGamesMCLst.setSelectedBackground(new Color(255));
		//}}
		fGamesMCLst.setSelectedForeground(Color.white);

		fGamesMCLst.setNumColumns(3);

		jclass.bwt.JCHeader header = fGamesMCLst.getHeader();
		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));

		fGamesMCLst.setColumnWidth(0,50);
		fGamesMCLst.setColumnWidth(1,160);
		fGamesMCLst.setColumnWidth(2,90);

		fGamesMCLst.setColumnAlignment(0,BWTEnum.MIDDLECENTER);
		fGamesMCLst.setColumnAlignment(1,BWTEnum.MIDDLELEFT);
		fGamesMCLst.setColumnAlignment(2,BWTEnum.MIDDLELEFT);

		fGamesMCLst.setAutoSelect(true);
		fGamesMCLst.getList().setBackground(Color.white);

		loadGameList();
	}

	/**************************************************************************/

	protected void getSchedule() throws IOException
	{
		ScheduleResp pResponse =
			((ASFantasySeasonRequestor)fAppRequestor).scheduleRequest();

		if(pResponse == null)
		{
			String msg = "Unable to access your schedule.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameVector = pResponse.fGameVector;
		fTeamVector = pResponse.fTeamInfoNameVector;
	}
	
	/**************************************************************************/

	protected void loadGameList()
	{
		ScheduleDayGame game;
		TeamInfoName oppTeam;
		JCVector items = new JCVector();
		JCVector row;
		String str;
		int i,numItems = fGameVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			game = (ScheduleDayGame)fGameVector.elementAt(i);

			row = new JCVector();
			row.addElement(new Integer(game.fProfGameWeek));
			
			if(game.fGameIsScheduled)
			{
				// Show Opponent.
				if(game.fIsHome)
					str = "vs. ";
				else
					str = "at ";

				oppTeam = fTeamVector.getByID(game.fOppTeamID);
				row.addElement(str + oppTeam.buildName());

				// Was game played? Show score.
				if((game.fWinningScore != 0) || (game.fLosingScore != 0))
				{
					if(game.fDidWin)
						str = "W ";
					else if(game.fWinningScore == game.fLosingScore)
						str = "T ";
					else
						str = "L ";

					str += game.fWinningScore + "-" + game.fLosingScore;
				}
				else
					str = "";
					
				row.addElement(str);
			}
			else
			{
				row.addElement("No Game Scheduled");
				row.addElement("");
			}
			
			items.addElement(row);
		}
		
		fGamesMCLst.setItems(items);
	}

}

/******************************************************************************/
/******************************************************************************/

