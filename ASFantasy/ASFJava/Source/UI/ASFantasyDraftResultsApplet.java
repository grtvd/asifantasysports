/* ASFantasyDraftResultsApplet.java */

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

public class ASFantasyDraftResultsApplet extends ASFBaseApplet
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	jclass.bwt.JCMultiColumnList fPlayersMCLst;
	//}}
	
	Vector fPlayerVector;
	TeamInfoNameByIDVector fTeamVector;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Draft Results");
	}

	/**************************************************************************/

	protected ASFantasyRequestor newFantasyRequestor(String hostName,
		int hostPortID,String requestDll,String encodedParticID)
	{
		return(new ASFantasyDraftRequestor(hostName,hostPortID,requestDll,
			encodedParticID));
	}

	/**************************************************************************/

	public void open() throws Exception
	{
		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getDraftResults();

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(450,390);
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,450,390);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fPlayersMCLst = new jclass.bwt.JCMultiColumnList();
		fPlayersMCLst.reshape(8,8,426,366);
		fPlayersMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fPlayersMCLst);
		fPlayersMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		{
			java.lang.String[] tempString = new java.lang.String[5];
			tempString[0] = new java.lang.String("Rnd");
			tempString[1] = new java.lang.String("Pick");
			tempString[2] = new java.lang.String("Player");
			tempString[3] = new java.lang.String("Pos");
			tempString[4] = new java.lang.String("Team");
			fPlayersMCLst.setColumnButtons(tempString);
		}
		fPlayersMCLst.setSelectedBackground(new Color(255));
		//}}
		fPlayersMCLst.setSelectedForeground(Color.white);

		fPlayersMCLst.setNumColumns(5);

		jclass.bwt.JCHeader header = fPlayersMCLst.getHeader();
		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));

		fPlayersMCLst.setColumnWidth(0,40);
		fPlayersMCLst.setColumnWidth(1,40);
		fPlayersMCLst.setColumnWidth(2,125);
		fPlayersMCLst.setColumnWidth(3,40);
		fPlayersMCLst.setColumnWidth(4,161);

		fPlayersMCLst.setColumnAlignment(0,BWTEnum.MIDDLECENTER);
		fPlayersMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fPlayersMCLst.setColumnAlignment(2,BWTEnum.MIDDLELEFT);
		fPlayersMCLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		fPlayersMCLst.setColumnAlignment(4,BWTEnum.MIDDLELEFT);

		fPlayersMCLst.setAutoSelect(true);
		fPlayersMCLst.getList().setBackground(Color.white);

		loadPlayerList();
	}

	/**************************************************************************/

	protected void getDraftResults() throws IOException
	{
		DraftResultResp pResponse =
			((ASFantasyDraftRequestor)fAppRequestor).draftResultRequest();

		if(pResponse == null)
		{
			String msg = "Unable to access draft results.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fPlayerVector = pResponse.fPlayerVector;
		fTeamVector = pResponse.fTeamInfoNameVector;
	}
	
	/**************************************************************************/
	
	protected void loadPlayerList()
	{
		DraftResultPlayer player;
		TeamInfoName team;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = fPlayerVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			player = (DraftResultPlayer)fPlayerVector.elementAt(i);
			team = fTeamVector.getByID(player.fTeamID);

			row = new JCVector();
			row.addElement(new Integer(player.fRound));
			row.addElement(new Integer(player.fPick));
			row.addElement(player.fName.buildRevFullName());
			row.addElement(player.fPosition.toString());
			row.addElement(team.buildName());
			items.addElement(row);
		}
		
		fPlayersMCLst.setItems(items);
	}
}

/******************************************************************************/
/******************************************************************************/
