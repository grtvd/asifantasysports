/* ASFantasyLineupApplet.java */

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

public abstract class ASFantasyLineupApplet extends ASFBaseApplet
{
	//{{DECLARE_CONTROLS
	protected symantec.itools.awt.BorderPanel fShowPnl;
	protected jclass.bwt.JCLabel fShowLineupLbl;
	protected java.awt.Choice fShowLineupChc;
	protected symantec.itools.awt.BorderPanel fBorderPnl;
	protected java.awt.Button fSubmitBtn;
	protected jclass.bwt.JCLabel fWhichLineupLbl;
	protected symantec.itools.awt.BorderPanel fLineupPnl;
	protected jclass.bwt.JCLabel fRosterLbl;
	protected jclass.bwt.JCMultiColumnList fRosterMCLst;
	/*protected jclass.bwt.JCLabel fLegionLbl;*/
	//}}
	
	protected TGameLevel fGameLevel = TGameLevel.gml_Undefined;
	protected int fShowTeamID;
	protected TeamInfoNameVector fTeamInfoVector;
	protected boolean fLineupEnabled = false;
	protected PlayerIDArray fPlayerIDArray;
	protected PlayerInfoVector fLineupPlayerVector;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Lineup");
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
		int numRosterListCols;
		int i;

		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getLineup(0);

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(600,410);
		setBackground(new Color(12632256));
		fShowPnl = new symantec.itools.awt.BorderPanel();
		fShowPnl.setLayout(null);
		fShowPnl.reshape(0,0,600,40);
		fShowPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fShowPnl);
		fShowPnl.setPaddingTop(1);
		fShowPnl.setPaddingBottom(1);
		fShowPnl.setPaddingLeft(1);
		fShowPnl.setPaddingRight(1);
		fShowPnl.setIPadTop(4);
		fShowPnl.setIPadBottom(4);
		fShowPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fShowLineupLbl = new jclass.bwt.JCLabel();
		fShowLineupLbl.reshape(4,6,110,18);
		fShowLineupLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fShowPnl.add(fShowLineupLbl);
		fShowLineupLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Show Lineup For:");
			fShowLineupLbl.setTextList(tempString);
		}
		fShowLineupChc = new java.awt.Choice();
		fShowPnl.add(fShowLineupChc);
		fShowLineupChc.reshape(120,4,300,23);
		fShowLineupChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,40,600,370);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fSubmitBtn = new java.awt.Button("Submit");
		fSubmitBtn.reshape(8,8,70,20);
		fSubmitBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fSubmitBtn);

		fWhichLineupLbl = new jclass.bwt.JCLabel();
		fWhichLineupLbl.reshape(8,39,50,18);
		fWhichLineupLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fWhichLineupLbl);
		fWhichLineupLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Lineup");
			fWhichLineupLbl.setTextList(tempString);
		}

		createWhichLineup(fBorderPnl,65,37);

		fLineupPnl = new symantec.itools.awt.BorderPanel();
		fLineupPnl.setLayout(null);
		fLineupPnl.reshape(8,67,200,285);
		fLineupPnl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fLineupPnl);
		//fLineupPnl.setLabel("Lineup");
		//fLineupPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
		fLineupPnl.setPaddingTop(0);
		fLineupPnl.setPaddingBottom(0);
		fLineupPnl.setPaddingLeft(0);
		fLineupPnl.setPaddingRight(0);
		fLineupPnl.setIPadBottom(2);
		fLineupPnl.setIPadSides(2);
		fLineupPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_LOWERED);

		createLineupLabels(fLineupPnl);
		createLineupChoices(fLineupPnl);

		fRosterLbl = new jclass.bwt.JCLabel();
		fRosterLbl.reshape(230,8,55,14);
		fRosterLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fRosterLbl);
		fRosterLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Roster");
			fRosterLbl.setTextList(tempString);
		}
		fRosterMCLst = new jclass.bwt.JCMultiColumnList();
		fRosterMCLst.reshape(225,28,355,325);
		fRosterMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fRosterMCLst);
		fRosterMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fRosterMCLst.setSelectedBackground(new Color(255));
		/*fLegionLbl = new jclass.bwt.JCLabel();
		fLegionLbl.reshape(8,331,570,30);
		fLegionLbl.setFont(new Font("Helvetica", Font.PLAIN, 10));
		fBorderPnl.add(fLegionLbl);
		fLegionLbl.setAlignment(jclass.bwt.JCLabel.TOPLEFT);
		{
			java.lang.String[] tempString = new java.lang.String[2];
			tempString[0] = new java.lang.String("Points for Season (Pts), Last Week's Points (LW), Roster-Injury Status (R-I, A = Active, I = Inactive, O = Out,");
			tempString[1] = new java.lang.String("D = Doubtful, Q = Questionable, P = Probable, X = No Injury Reported)");
			fLegionLbl.setTextList(tempString);
		}*/
		//}}

		// Roster List
		fRosterMCLst.setSelectedForeground(Color.white);
		numRosterListCols = getNumRosterListCols();
		{
			java.lang.String[] tempString = new java.lang.String[numRosterListCols];

			for(i = 0; i < numRosterListCols; ++i)
				tempString[i] = new java.lang.String(getRosterListColLabel(i));
			fRosterMCLst.setColumnButtons(tempString);
		}
		fRosterMCLst.setNumColumns(numRosterListCols);

		jclass.bwt.JCHeader header = fRosterMCLst.getHeader();
		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));

		for(i = 0; i < numRosterListCols; ++i)
		{
			fRosterMCLst.setColumnWidth(i,getRosterListColWidth(i));
			fRosterMCLst.setColumnAlignment(i,getRosterListColAlign(i));
			header.setColumnAlignment(i,getRosterListColAlign(i));
		}

		fRosterMCLst.setAutoSelect(true);
		fRosterMCLst.getList().setBackground(Color.white);

		loadData(true);

		if(fGameLevel == TGameLevel.gml_Standard)
			fShowLineupChc.enable(false);
	}

	/**************************************************************************/

	abstract protected void createWhichLineup(symantec.itools.awt.BorderPanel panel,
		int left,int top) throws Exception;
	abstract protected void createLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception;
	abstract protected void removeLineupLabels(symantec.itools.awt.BorderPanel panel) throws Exception;
	abstract protected void createLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception;
	abstract protected void removeLineupChoices(symantec.itools.awt.BorderPanel panel) throws Exception;
	abstract protected void enableLineupChoices() throws Exception;

	/**************************************************************************/

	protected int getNumRosterListCols()
	{
		return(6);
	}

	/**************************************************************************/

	protected String getRosterListColLabel(int col)
	{
		if(col == 0)
			return("Player");
		else if(col == 1)
			return("PT");
		else if(col == 2)
			return("Pos");
		else if(col == 3)
			return("Pts");
		else if(col == 4)
			return("TW");
		else if(col == 5)
			return("S");
		return("");
	}

	/**************************************************************************/

	protected int getRosterListColWidth(int col)
	{
		if(col == 0)
			return(135);
		else if(col == 1)
			return(40);
		else if(col == 2)
			return(40);
		else if(col == 3)
			return(40);
		else if(col == 4)
			return(40);
		else if(col == 5)
			return(40);
		return(0);
	}

	/**************************************************************************/

	protected int getRosterListColAlign(int col)
	{
		if(col == 0)
			return(BWTEnum.MIDDLELEFT);
		return(BWTEnum.MIDDLECENTER);
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
				if(unloadPlayerIDVector())
					updateLineup();
				enable(true);
				fSubmitBtn.enable(true);
			}
			else if(evt.target == fShowLineupChc)
			{
				showOtherTeamLineup();
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void getLineup(int showTeamID) throws IOException
	{
		LineupQueryResp pResponse =
			((ASFantasySeasonRequestor)fAppRequestor).lineupQueryRequest(showTeamID);

		if(pResponse == null)
		{
			String msg = "Unable to access the lineup.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameLevel = pResponse.fGameLevel;
		fShowTeamID = pResponse.fShowTeamID;
		fTeamInfoVector = pResponse.fTeamInfoVector;
		fLineupEnabled = pResponse.fEnableChanges;
		fPlayerIDArray = pResponse.fPlayerIDArray;
		fLineupPlayerVector = pResponse.fLineupPlayerVector;

		TAGVectorSorter.quickSort(fLineupPlayerVector,new LineupPlayerByPointsCmpr());
	}

	/**************************************************************************/

	protected void updateLineup()
	{
		LineupUpdateResp pResponse;
		String msg;
		
		pResponse = ((ASFantasySeasonRequestor)fAppRequestor).lineupUpdateRequest(fPlayerIDArray);

		if(pResponse != null)
			msg = "Your lineup has been saved.";
		else
			msg = "Unable to save your lineup.  Please try again later.";

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,msg);
	}
	
	/**************************************************************************/

	protected void showOtherTeamLineup()
	{
		int pos = fShowLineupChc.getSelectedIndex();

		if((pos >= 0) && (pos < fTeamInfoVector.size()))
		{
			int teamID = ((TeamInfoName)fTeamInfoVector.elementAt(pos)).fTeamID;
			
			if(teamID != fShowTeamID)
			{
				enable(false);
				try
				{
					getLineup(teamID);
					loadData(false);
				}
				catch(Exception e)
				{
				}
				enable(true);
			}
		}
	}
	
	/**************************************************************************/

	protected void loadData(boolean firstTime) throws Exception
	{
		if(firstTime)
			loadShowTeams();
	
		loadLineupChoices(firstTime);
		loadRosterList();

		fSubmitBtn.enable(fLineupEnabled);
		enableLineupChoices();
	}
	
	/**************************************************************************/

	protected void loadShowTeams() throws Exception
	{
		TeamInfoName teamInfo;
		int i,numItems;
		int pos;
		
		// Load fShowLinupChc.
		numItems = fTeamInfoVector.size();
		for(i = 0; i < numItems; i++)
		{
			teamInfo = (TeamInfoName)fTeamInfoVector.elementAt(i);
			fShowLineupChc.addItem(teamInfo.buildName());
		}

		// Select team to be shown
		pos = fTeamInfoVector.getPosByID(fShowTeamID);

		if(pos == -1)
			throw new Exception("LineupApplet.loadShowTeams: show team not found");
			
		fShowLineupChc.select(pos);
	}
	
	/**************************************************************************/

	protected void addToLineupVectorChoice(Vector playerVector,
		Choice playerChoice,Integer playerID,String playerName)
	{
		playerVector.addElement(playerID);
		playerChoice.addItem(playerName);
	}

	/**************************************************************************/

	protected void addPlayerToLineupVectorChoice(Vector playerVector,
		Choice playerChoice,LineupPlayer player)
	{
		addToLineupVectorChoice(playerVector,playerChoice,
			new Integer(player.fPlayerID),player.fName.buildRevFullName());
	}

	/**************************************************************************/
	
	protected void selLineupChoiceByID(Vector playerVector,
		Choice playerChoice,Integer playerID) throws Exception
	{
		int i,numItems = playerVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			if(((Integer)playerVector.elementAt(i)).intValue() ==
				playerID.intValue())
			{
				playerChoice.select(i);
				return;
			}
		}

		throw new Exception("LineupApplet.selLineupChoiceByID: player not found in Choice");
	}
	
	/**************************************************************************/

	protected Integer getPlayerIDFromLineupChoice(Vector playerVector,
		Choice playerChoice)
	{
		return((Integer)playerVector.elementAt(playerChoice.getSelectedIndex()));
	}
	
	/**************************************************************************/
	
	abstract protected void emptyLineupVectors() throws Exception;

	/**************************************************************************/

	protected void resetLineupVectorChoices() throws Exception
	{
		emptyLineupVectors();
	
	
		//BOB When converting to Java 1.1, this method can simply clear the
		//	items from each of the Choice components.
		
		fLineupPnl.show(false);
		
		removeLineupLabels(fLineupPnl);
		removeLineupChoices(fLineupPnl);
		createLineupLabels(fLineupPnl);
		createLineupChoices(fLineupPnl);
		
		fLineupPnl.show(true);
	}
	
	/**************************************************************************/

	protected void loadLineupChoices(boolean firstTime) throws Exception
	{
		LineupPlayer player;
		int i,numItems = fLineupPlayerVector.size();
		
		if(!firstTime)
			resetLineupVectorChoices();
		
		addOpenSlotToAllLineupVectorChoices();
		
		// Fill all Choices with specific players
		for(i = 0; i < numItems; i++)
		{
			player = (LineupPlayer)fLineupPlayerVector.elementAt(i);

			addPlayerToSelectLineupVectorChoices(player);
		}

		// Set Choices based on lineup (fPlayerIDArray)
		selAllLineupChoices();
	}

	/**************************************************************************/

	abstract protected void addOpenSlotToAllLineupVectorChoices() throws Exception;
	abstract protected void addPlayerToSelectLineupVectorChoices(LineupPlayer player)
		throws Exception;

	abstract protected void selAllLineupChoices() throws Exception;
	abstract protected boolean unloadAllLineupChoices() throws Exception;

	/**************************************************************************/
		
	protected boolean unloadPlayerIDVector()
	{
		try
		{
			if(unloadAllLineupChoices())
				return(true);
		}
		catch(Exception e)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Unable to save your lineup. Internal Error: " + e.getMessage());
		}
		
		return(false);
	}
	
	/**************************************************************************/

	protected void loadRosterList()
	{
		LineupPlayer player;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = fLineupPlayerVector.size();
		
		fRosterMCLst.clear();	// to reset selection and top row

		for(i = 0; i < numItems; i++)
		{
			player = (LineupPlayer)fLineupPlayerVector.elementAt(i);
			row = createRosterListPlayer(player);
			items.addElement(row);
		}
		
		fRosterMCLst.setItems(items);
	}

	/**************************************************************************/

	protected JCVector createRosterListPlayer(LineupPlayer player)
	{
		JCVector row;
		
		row = new JCVector();
		row.addElement(player.fName.buildRevFullName());
		row.addElement(player.fProfTeamAbbr);
		row.addElement(player.fPosition.toString());
		row.addElement(new Integer(player.fTotalPoints));
		row.addElement(new Integer(player.fLastWeeksPoints));
		row.addElement(player.getStatus());

		return(row);
	}
}

/******************************************************************************/
/******************************************************************************/

