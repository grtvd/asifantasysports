/* ASFantasyFreeAgentApplet.java */

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

public class ASFantasyFreeAgentApplet extends ASFBaseApplet implements DialogClient
{
	protected int fScoutPlayerIDCol = 8;
	
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	java.awt.Button fSubmitBtn;
	java.awt.Button fClearBtn;
	java.awt.Button fScoutBtn;

	symantec.itools.awt.BorderPanel fClaimReleasePnl;
	jclass.bwt.JCLabel fClaimingTabLbl;
	jclass.bwt.JCLabel fClaimingLbl;
	jclass.bwt.JCLabel fReleasingTagLbl;
	protected java.awt.Choice fReleasingChc;

	jclass.bwt.JCLabel fPlayersLbl;
	jclass.bwt.JCMultiColumnList fScoutMCLst;

	java.awt.Button fClaimBtn;
	jclass.bwt.JCLabel fScoutSortLbl;
	java.awt.Choice fScoutSortChc;
	//}}
	
	private TGameLevel fGameLevel = TGameLevel.gml_Undefined;
	
	private PlayerInfo fClaimPlayer = null;
	private int fReleasePlayerID = 0;
	
	private PlayerInfoVector fRosterPlayerVector = null;
	
	private PlayerScoutRqst fPlayerScoutRqst = new PlayerScoutRqst();
	private PlayerScoutPlayerVector fScoutPlayerVector = new PlayerScoutPlayerVector();
	private TeamInfoNameByIDVector fTeamInfoNameVector = new TeamInfoNameByIDVector();

	private PlayerScoutDialog fPlayerScoutDialog = null;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Free Agents");
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

		getFreeAgentClaim();
		fPlayerScoutRqst.fIsFreeAgentRequest = true;

		// Setup player stat request for total points only
		if(fGameLevel == TGameLevel.gml_Standard)
		{
			PlayerScoutStat playerScoutStat = new PlayerScoutStat();

			playerScoutStat.fStatType = PlayerStatType.pst_TotalPoints;
			playerScoutStat.fStatYear = StatYearType.syr_YearToDate;

			fPlayerScoutRqst.fStatVector.addElement(playerScoutStat);
			fPlayerScoutRqst.fSelectByStat = (byte)1;
		}

		// Setup player ID column
		if(fGameLevel == TGameLevel.gml_Standard)
			fScoutPlayerIDCol = 4;
		else
			fScoutPlayerIDCol = 8;

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
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fSubmitBtn = new java.awt.Button("Submit");
		fSubmitBtn.reshape(8,8,70,20);
		fSubmitBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fSubmitBtn);
		fClearBtn = new java.awt.Button("Clear");
		fClearBtn.reshape(86,8,70,20);
		fClearBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fClearBtn);
		fScoutBtn = new java.awt.Button("Scout");
		fScoutBtn.reshape(514,8,70,20);
		fScoutBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fScoutBtn);

		fClaimReleasePnl = new symantec.itools.awt.BorderPanel();
		fClaimReleasePnl.setLayout(null);
		fClaimReleasePnl.reshape(4,36,582,32);
		fBorderPnl.add(fClaimReleasePnl);
		fClaimReleasePnl.setPaddingTop(1);
		fClaimReleasePnl.setPaddingBottom(1);
		fClaimReleasePnl.setPaddingLeft(1);
		fClaimReleasePnl.setPaddingRight(1);
		fClaimReleasePnl.setIPadTop(4);
		fClaimReleasePnl.setIPadBottom(4);
		fClaimReleasePnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_LOWERED);

		fClaimingTabLbl = new jclass.bwt.JCLabel();
		fClaimingTabLbl.reshape(2,1,70,18);
		fClaimingTabLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fClaimReleasePnl.add(fClaimingTabLbl);
		fClaimingTabLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Claiming");
			fClaimingTabLbl.setTextList(tempString);
		}

		fClaimingLbl = new jclass.bwt.JCLabel();
		fClaimingLbl.reshape(82,1,115,18);
		fClaimReleasePnl.add(fClaimingLbl);
		fClaimingLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);

		fReleasingTagLbl = new jclass.bwt.JCLabel();
		fReleasingTagLbl.reshape(260,1,70,18);
		fReleasingTagLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fClaimReleasePnl.add(fReleasingTagLbl);
		fReleasingTagLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Releasing");
			fReleasingTagLbl.setTextList(tempString);
		}

		fReleasingChc = new java.awt.Choice();
		fClaimReleasePnl.add(fReleasingChc);
		fReleasingChc.reshape(340,0,200,23);
		fReleasingChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

		fPlayersLbl = new jclass.bwt.JCLabel();
		fPlayersLbl.reshape(8,72,55,18);
		fPlayersLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fPlayersLbl);
		fPlayersLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Players");
			fPlayersLbl.setTextList(tempString);
		}

		fScoutMCLst = new jclass.bwt.JCMultiColumnList();
		fScoutMCLst.reshape(8,92,576,308);
		fScoutMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fScoutMCLst);
		fScoutMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fScoutMCLst.setSelectedBackground(new Color(255));
		fClaimBtn = new java.awt.Button("Claim");
		fClaimBtn.reshape(8,412,70,20);
		fClaimBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fClaimBtn);
		fScoutSortLbl = new jclass.bwt.JCLabel();
		fScoutSortLbl.reshape(402,412,50,18);
		fScoutSortLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fScoutSortLbl);
		fScoutSortLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Sort by");
			fScoutSortLbl.setTextList(tempString);
		}
		fScoutSortChc = new java.awt.Choice();
		fScoutSortChc.addItem("Player Name");
		if(fGameLevel == TGameLevel.gml_Standard)
		{
			fScoutSortChc.addItem("Total Pts/Asc");
			fScoutSortChc.addItem("Total Pts/Des");
		}
		else
		{
			fScoutSortChc.addItem("Stat 1/Asc");
			fScoutSortChc.addItem("Stat 1/Des");
			fScoutSortChc.addItem("Stat 2/Asc");
			fScoutSortChc.addItem("Stat 2/Des");
			fScoutSortChc.addItem("Stat 3/Asc");
			fScoutSortChc.addItem("Stat 3/Des");
		}
		fBorderPnl.add(fScoutSortChc);
		fScoutSortChc.reshape(457,410,110,23);
		//}}

		// FreeAgent List
		fScoutMCLst.setSelectedForeground(Color.white);

		{
			java.lang.String[] tempString = new java.lang.String[8];
			tempString[0] = new java.lang.String("Player");
			tempString[1] = new java.lang.String("PT");
			tempString[2] = new java.lang.String("Pos");
			if(fGameLevel == TGameLevel.gml_Standard)
			{
				tempString[3] = new java.lang.String("TP");
			}
			else
			{
				tempString[3] = new java.lang.String("S");
				tempString[4] = new java.lang.String("St-1");
				tempString[5] = new java.lang.String("St-2");
				tempString[6] = new java.lang.String("St-3");
				tempString[7] = new java.lang.String("Team / Available");
			}
			fScoutMCLst.setColumnButtons(tempString);
		}

		if(fGameLevel == TGameLevel.gml_Standard)
			fScoutMCLst.setNumColumns(4);
		else
			fScoutMCLst.setNumColumns(8);

		jclass.bwt.JCHeader header = fScoutMCLst.getHeader();
		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));

		if(fGameLevel == TGameLevel.gml_Standard)
		{
			fScoutMCLst.setColumnWidth(0,204);
			fScoutMCLst.setColumnWidth(1,40);
			fScoutMCLst.setColumnWidth(2,40);
			fScoutMCLst.setColumnWidth(3,40);
		}
		else
		{
			fScoutMCLst.setColumnWidth(0,144);
			fScoutMCLst.setColumnWidth(1,40);
			fScoutMCLst.setColumnWidth(2,40);
			fScoutMCLst.setColumnWidth(3,40);
			fScoutMCLst.setColumnWidth(4,40);
			fScoutMCLst.setColumnWidth(5,40);
			fScoutMCLst.setColumnWidth(6,40);
			fScoutMCLst.setColumnWidth(7,174);
		}

		fScoutMCLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		fScoutMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fScoutMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		fScoutMCLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			fScoutMCLst.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
			fScoutMCLst.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
			fScoutMCLst.setColumnAlignment(6,BWTEnum.MIDDLECENTER);
			fScoutMCLst.setColumnAlignment(7,BWTEnum.MIDDLELEFT);
		}

		header.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			header.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
			header.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
			header.setColumnAlignment(6,BWTEnum.MIDDLECENTER);
			header.setColumnAlignment(7,BWTEnum.MIDDLELEFT);
		}

		fScoutMCLst.setAutoSelect(true);
		fScoutMCLst.getList().setBackground(Color.white);

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
					updateFreeAgentClaim(false);
				enable(true);
				fSubmitBtn.enable(true);
			}
			else if(evt.target == fClearBtn)
			{
				fClearBtn.enable(false);
				enable(false);
				updateFreeAgentClaim(true);
				enable(true);
				fClearBtn.enable(true);
			}
			else if(evt.target == fScoutBtn)
			{
				fScoutBtn.enable(false);
				enable(false);
				
				fPlayerScoutDialog =
					new PlayerScoutDialog(this,this,fPlayerScoutRqst,fGameLevel);
				
				fPlayerScoutDialog.show();
			}
			else if(evt.target == fClaimBtn)
			{
				setClaimPlayer();
			}
			else if(evt.target == fScoutSortChc)
			{
				sortScoutList(fScoutSortChc.getSelectedIndex());
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void getFreeAgentClaim() throws IOException
	{
		FreeAgentQueryResp pResponse = 
			((ASFantasySeasonRequestor)fAppRequestor).freeAgentQueryRequest();

		if(pResponse == null)
		{
			String msg = "Unable to access your free agent claim.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameLevel = pResponse.fGameLevel;
		
		fClaimPlayer = pResponse.fClaimPlayer;
		fReleasePlayerID = pResponse.fReleasePlayerID;
		fRosterPlayerVector = pResponse.fRosterPlayerVector;

		TAGVectorSorter.quickSort(fRosterPlayerVector,new PlayerInfoByNameCmpr());
	}
	
	/**************************************************************************/

	protected void updateFreeAgentClaim(boolean clear)
	{
		FreeAgentUpdateResp pResponse;

		int releasePlayerID = 0;
		int claimPlayerID = 0;
		String msg;

		if(!clear)
		{
			releasePlayerID = fReleasePlayerID;
			claimPlayerID = fClaimPlayer.fPlayerID;
		}
		
		pResponse = ((ASFantasySeasonRequestor)fAppRequestor).freeAgentUpdateRequest(
			claimPlayerID,releasePlayerID);
		
		if(pResponse != null)
		{
			msg = "Your free agent claim has been " + (clear ? "cleared." : "saved.");
			
			if(clear)
			{
				fReleasePlayerID = 0;
				fClaimPlayer = new PlayerInfo();
			
				fReleasingChc.select(0);
				loadClaimPlayer();
			}
		}
		else
			msg = "Unable to save free agent claim.  Please try again later.";

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,msg);
	}
	
	/**************************************************************************/

	private void getPlayerScoutPlayers()
	{
		PlayerScoutResp pResponse;
		
		pResponse = ((ASFantasySeasonRequestor)fAppRequestor).playerScoutRequest(
			fPlayerScoutRqst);

		if(pResponse != null)
		{
			fScoutPlayerVector = pResponse.fPlayerVector;
			fTeamInfoNameVector = pResponse.fTeamInfoNameVector;

			int sortIndex = determineScoutSortChoiceIndex();
			fScoutSortChc.select(sortIndex);
			sortScoutList(sortIndex);
			
			if(fScoutPlayerVector.size() == 0)
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"No players matched the search criteria.");
		}

		if(pResponse == null)
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Unable to access available players.");
	}
	
	/**************************************************************************/
	/**************************************************************************/

	protected void loadData()
	{
		loadReleasePlayer();
		loadClaimPlayer();
	
		loadScoutList();
	}

	/**************************************************************************/

	protected void loadReleasePlayer()
	{
		PlayerInfo player;
		int i,numItems = fRosterPlayerVector.size();
		int pos = 0;
		
		fReleasingChc.addItem("-- None --");

		for(i = 0; i < numItems; i++)
		{
			player = (PlayerInfo)fRosterPlayerVector.elementAt(i);

			fReleasingChc.addItem(player.fName.buildRevFullName());
			if(player.fPlayerID == fReleasePlayerID)
				pos = i + 1;
		}
		
		fReleasingChc.select(pos);
	}
		
	/**************************************************************************/

	protected void loadClaimPlayer()
	{
		fClaimingLbl.setText(fClaimPlayer.fName.buildFullName());
	}
		
	/**************************************************************************/
	/**************************************************************************/

	protected JCVector buildScoutRowFromPlayer(PlayerScoutPlayer player)
	{
		JCVector row = new JCVector();

		row.addElement(player.fName.buildRevFullName());
		row.addElement(player.fProfTeamAbbr);
		row.addElement(player.fPosition.toString());
		row.addElement(player.getStatus());

		if(fGameLevel == TGameLevel.gml_Standard)
			row.addElement(buildScoutStatFromValueType(player,0));
		else
		{
			row.addElement(buildScoutStatFromValueType(player,0));
			row.addElement(buildScoutStatFromValueType(player,1));
			row.addElement(buildScoutStatFromValueType(player,2));

			if(player.isFreeAgent())
				row.addElement("Available " + player.fFreeAgentAvail);
			else
			{
				TeamInfoName team = fTeamInfoNameVector.getByID(player.fTeamID);
				row.addElement(team.buildName());
			}
		}

		row.addElement(new Integer(player.fPlayerID));

		return(row);
	}

	/**************************************************************************/

	protected Object buildScoutStatFromValueType(PlayerScoutPlayer player,
		int statPos)
	{
		String statAsStr;
		PlayerScoutStat playerScoutStat;
		
		// Any stat to show?
		if(statPos >= player.fPlayerStatValueVector.size())
			return(new String());

		statAsStr = (String)(player.fPlayerStatValueVector.elementAt(statPos));

		// Stat formatting available?
		if(statPos >= fPlayerScoutRqst.fStatVector.size())
			return(new String(statAsStr));
		playerScoutStat =
			(PlayerScoutStat)fPlayerScoutRqst.fStatVector.elementAt(statPos);

		return(PlayerStatType.convertStatForDisplay(playerScoutStat.fStatType,
			statAsStr));
	}

	/**************************************************************************/

	protected void loadScoutList()
	{
		PlayerScoutPlayer player;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = fScoutPlayerVector.size();

		for(i = 0; i < numItems; i++)
		{
			player = (PlayerScoutPlayer)fScoutPlayerVector.elementAt(i);

			row = buildScoutRowFromPlayer(player);
			items.addElement(row);
		}
			
		fScoutMCLst.setItems(items);
	}
	
	/**************************************************************************/

	protected boolean unloadData()
	{
		int pos;

		if(fClaimPlayer.fPlayerID == 0)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You have not selected a player to claim.");
			return(false);
		}
		
		fReleasePlayerID = 0;

		pos = fReleasingChc.getSelectedIndex() - 1;
		if((pos >= 0) && (pos < fRosterPlayerVector.size()))
			fReleasePlayerID = ((PlayerInfo)fRosterPlayerVector.elementAt(pos)).fPlayerID;

		if(fReleasePlayerID == 0)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"You must selected a player to release. The player will not be released if your roster has room at the time the claim is processed.");
			return(false);
		}

		return(true);
	}
	
	/**************************************************************************/

	protected void setClaimPlayer()
	{
		JCVector row = (JCVector)fScoutMCLst.getSelectedItem();

		if(row != null)
		{
			Integer playerID = (Integer)row.elementAt(fScoutPlayerIDCol);
			PlayerScoutPlayer player =
				(PlayerScoutPlayer)(fScoutPlayerVector.getByID(playerID.intValue()));
			
			if(player != null)
			{
				if(player.isFreeAgent())
				{
					fClaimPlayer = player;
					loadClaimPlayer();
				}
				else
					MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
						"The player you selected is not a free agent.");
			}
		}
		else
		{
			if(fScoutPlayerVector.size() == 0)
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"The Players list is empty.  Press the Scout button to search for free agents.");
			else
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"You have not selected a player to claim.");
		}
	}
	
	/**************************************************************************/

	private void sortScoutList(int sortBy)
	{
		int sortStat = 0;
		boolean ascending = true;
		
		if((sortBy >= 1) && (sortBy <= 6))
		{
			switch(sortBy)
			{
				case 1:
					sortStat = 0;
					ascending = true;
					break;
				case 2:
					sortStat = 0;
					ascending = false;
					break;
				case 3:
					sortStat = 1;
					ascending = true;
					break;
				case 4:
					sortStat = 1;
					ascending = false;
					break;
				case 5:
					sortStat = 2;
					ascending = true;
					break;
				case 6:
					sortStat = 2;
					ascending = false;
					break;
			}
			
			fScoutPlayerVector.sort(new PlayerScoutPlayerByStatCmpr(sortStat,ascending));
		}
		else
			fScoutPlayerVector.sort(new PlayerScoutPlayerByNameCmpr());

		loadScoutList();
	}
	
	/**************************************************************************/

	private int determineScoutSortChoiceIndex()
	{
		int index;
		
		if(fPlayerScoutRqst.fSelectByStat == 0)
			index = 0;
		else
		{
			switch(fPlayerScoutRqst.fSelectByStat)
			{
				case 1:
				default:
					index = 1;
					break;
				case 2:
					index = 3;
					break;
				case 3:
					index = 5;
					break;
			}
			
			if(!fPlayerScoutRqst.fSelectByStatAsc)
				index++;
		}

		return(index);
	}
	
	/**************************************************************************/
	
	public void dialogDismissed(Dialog dlog)
	{
		if(dlog == fPlayerScoutDialog)
		{
			if(fPlayerScoutDialog.success())
			{
				getPlayerScoutPlayers();
				loadScoutList();
			}
			
			fPlayerScoutDialog = null;
			fScoutBtn.enable(true);
			enable(true);
		}
	}
}

/******************************************************************************/
/******************************************************************************/

