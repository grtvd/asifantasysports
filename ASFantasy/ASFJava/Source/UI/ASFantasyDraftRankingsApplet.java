/* ASFantasyDraftRankingsApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.applet.*;
import java.lang.*;
import java.util.*;
import java.io.*;

import jclass.bwt.*;
import jclass.util.*;

/******************************************************************************/
/******************************************************************************/

public abstract class ASFantasyDraftRankingsApplet extends ASFBaseApplet
	implements DialogClient
{
	protected static final int fRankingRankCol = 0;
	protected static final int fScoutPlayerIDCol = 6;

	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	java.awt.Button fSubmitBtn;
	TAGLabel fYourRankingsLbl;
	jclass.bwt.JCMultiColumnList fRankingMCLst;
	symantec.itools.awt.ImageButton fRemoveBtn;
	symantec.itools.awt.DirectionButton fMoveDownBtn;
	symantec.itools.awt.DirectionButton fMoveUpBtn;
	symantec.itools.awt.DirectionButton fMoveLeftBtn;
	TAGLabel fEligiblePlayersLbl;
	jclass.bwt.JCMultiColumnList fScoutMCLst;
	java.awt.Button fScoutBtn;
	TAGLabel fScoutSortLbl;
	java.awt.Choice fScoutSortChc;
	//}}

	private TGameLevel fGameLevel = TGameLevel.gml_Undefined;
	private DraftRankingPlayerVector fRankingPlayerVector = null;
	private PlayerScoutRqst fPlayerScoutRqst = new PlayerScoutRqst();
	private PlayerScoutPlayerVector fScoutPlayerVector = new PlayerScoutPlayerVector();

	private PlayerScoutDialog fPlayerScoutDialog = null;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Draft Rankings");
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
		jclass.bwt.JCHeader header;
		Component headerButtons[];
		int i;
		
		//BOB		super.openSubPanel();

		// Take	out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getDraftRanking();

		// Setup player stat request for total points only
		if(fGameLevel == TGameLevel.gml_Standard)
		{
			PlayerScoutStat playerScoutStat = new PlayerScoutStat();

			playerScoutStat.fStatType = PlayerStatType.pst_TotalPoints;
			playerScoutStat.fStatYear = StatYearType.syr_LastYear;

			fPlayerScoutRqst.fStatVector.addElement(playerScoutStat);
			fPlayerScoutRqst.fSelectByStat = (byte)1;
		}

		setLayout(null);
		addNotify();
		resize(685,390);
		setFont(new Font("Helvetica", Font.PLAIN, 12));
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,685,390);
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setIPadTop(1);
		fBorderPnl.setIPadBottom(1);
		fBorderPnl.setIPadSides(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);

		// Submit Button
		fSubmitBtn = new java.awt.Button("Submit");
		fSubmitBtn.reshape(8,8,70,20);
		fSubmitBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fSubmitBtn);

		// "Your Draft Rankings"
		fYourRankingsLbl = new TAGLabel();
		fYourRankingsLbl.reshape(10,40,224,14);
		fYourRankingsLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fYourRankingsLbl);
		fYourRankingsLbl.setAlignment(0);

		// Roster List
		fRankingMCLst = new jclass.bwt.JCMultiColumnList();
		fRankingMCLst.reshape(8,60,275,280);
		fRankingMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fRankingMCLst);
		fRankingMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fRankingMCLst.setSelectedBackground(new Color(255));
		fRankingMCLst.setSelectedForeground(Color.white);

		{
			java.lang.String[] tempString = new java.lang.String[4];
			tempString[0] = new java.lang.String("Rank");
			tempString[1] = new java.lang.String("Player");
			tempString[2] = new java.lang.String("PT");
			tempString[3] = new java.lang.String("Pos");
			fRankingMCLst.setColumnButtons(tempString);
		}

		fRankingMCLst.setNumColumns(4);

		header = fRankingMCLst.getHeader();
		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));

		fRankingMCLst.setColumnWidth(0,45);
		fRankingMCLst.setColumnWidth(1,130);
		fRankingMCLst.setColumnWidth(2,40);
		fRankingMCLst.setColumnWidth(3,40);

		fRankingMCLst.setColumnAlignment(0,BWTEnum.MIDDLECENTER);
		fRankingMCLst.setColumnAlignment(1,BWTEnum.MIDDLELEFT);
		fRankingMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		fRankingMCLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);

		header.setColumnAlignment(0,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(1,BWTEnum.MIDDLELEFT);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(3,BWTEnum.MIDDLECENTER);

		header.disable();	// disable header sorting
		headerButtons = header.getComponents();
		for(i = 0; i < headerButtons.length; i++)
			headerButtons[i].enable();	// re-enble columns for active look

		fRankingMCLst.setAutoSelect(true);
		fRankingMCLst.getList().setBackground(Color.white);

		// Remove Button
		fRemoveBtn = new symantec.itools.awt.ImageButton();
		fRemoveBtn.reshape(18,348,24,24);
		fBorderPnl.add(fRemoveBtn);
		fRemoveBtn.setNotifyDelay(100);

		// Down Button
		fMoveDownBtn = new symantec.itools.awt.DirectionButton();
		fMoveDownBtn.reshape(120,348,24,24);
		fBorderPnl.add(fMoveDownBtn);
		fMoveDownBtn.setDirection(symantec.itools.awt.DirectionButton.DOWN);
		fMoveDownBtn.setArrowIndent(3);

		// Up Button
		fMoveUpBtn = new symantec.itools.awt.DirectionButton();
		fMoveUpBtn.reshape(148,348,24,24);
		fBorderPnl.add(fMoveUpBtn);
		fMoveUpBtn.setDirection(symantec.itools.awt.DirectionButton.UP);
		fMoveUpBtn.setArrowIndent(3);

		// Left Button
		fMoveLeftBtn = new symantec.itools.awt.DirectionButton();
		fMoveLeftBtn.reshape(291,120,24,24);
		fBorderPnl.add(fMoveLeftBtn);
		fMoveLeftBtn.setNotifyDelay(100);
		fMoveLeftBtn.setArrowIndent(3);

		// Scout Button
		fScoutBtn = new java.awt.Button("Scout");
		fScoutBtn.reshape(603,8,70,20);
		fScoutBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fScoutBtn);

		// "Eligible Players"
		fEligiblePlayersLbl = new TAGLabel();
		fEligiblePlayersLbl.reshape(323,40,270,14);
		fEligiblePlayersLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fEligiblePlayersLbl);
		fEligiblePlayersLbl.setAlignment(0);

		// Scout List
		fScoutMCLst = new jclass.bwt.JCMultiColumnList();
		fScoutMCLst.reshape(323,60,350,280);
		fScoutMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fScoutMCLst);
		fScoutMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fScoutMCLst.setSelectedBackground(new Color(255));
		fScoutMCLst.setSelectedForeground(Color.white);

		if(fGameLevel == TGameLevel.gml_Standard)
		{
			java.lang.String[] tempString = new java.lang.String[4];

			tempString[0] = new java.lang.String("Player");
			tempString[1] = new java.lang.String("PT");
			tempString[2] = new java.lang.String("Pos");
			tempString[3] = new java.lang.String("TP");
			fScoutMCLst.setColumnButtons(tempString);

			fScoutMCLst.setNumColumns(4);
		}
		else
		{
			java.lang.String[] tempString = new java.lang.String[6];

			tempString[0] = new java.lang.String("Player");
			tempString[1] = new java.lang.String("PT");
			tempString[2] = new java.lang.String("Pos");
			tempString[3] = new java.lang.String("St-1");
			tempString[4] = new java.lang.String("St-2");
			tempString[5] = new java.lang.String("St-3");
			fScoutMCLst.setColumnButtons(tempString);

			fScoutMCLst.setNumColumns(6);
		}

		header = fScoutMCLst.getHeader();
		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));

		if(fGameLevel == TGameLevel.gml_Standard)
		{
			fScoutMCLst.setColumnWidth(0,230);
			fScoutMCLst.setColumnWidth(1,40);
			fScoutMCLst.setColumnWidth(2,40);
			fScoutMCLst.setColumnWidth(3,40);
		}
		else
		{
			fScoutMCLst.setColumnWidth(0,130);
			fScoutMCLst.setColumnWidth(1,40);
			fScoutMCLst.setColumnWidth(2,40);
			fScoutMCLst.setColumnWidth(3,40);
			fScoutMCLst.setColumnWidth(4,40);
			fScoutMCLst.setColumnWidth(5,40);
		}

		fScoutMCLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		fScoutMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fScoutMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		fScoutMCLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			fScoutMCLst.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
			fScoutMCLst.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
		}

		header.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		if(fGameLevel == TGameLevel.gml_Premium)
		{
			header.setColumnAlignment(4,BWTEnum.MIDDLECENTER);
			header.setColumnAlignment(5,BWTEnum.MIDDLECENTER);
		}

		fScoutMCLst.setAutoSelect(true);
		fScoutMCLst.getList().setBackground(Color.white);

		// "Sort By"
		fScoutSortLbl = new TAGLabel();
		fScoutSortLbl.reshape(323,350,54,14);
		fScoutSortLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fScoutSortLbl);
		fScoutSortLbl.setAlignment(0);

		// Sort Choice
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
		fScoutSortChc.reshape(383,346,110,23);
		//}}

		try {
			java.net.URL imageURL = new java.net.URL(getCodeBase().toString() +
				"../Images/RedX_20x20.gif");
			fRemoveBtn.setImageURL(imageURL);
		} catch (java.net.MalformedURLException error) {
		}
			 
		fYourRankingsLbl.setText("Your Draft Rankings");
		fEligiblePlayersLbl.setText("Eligible Players");
		fScoutSortLbl.setText("Sort by");
		fScoutSortLbl.setAlignment(TAGLabel.RIGHT);

		loadRankingList();
		loadScoutList();
	}

	/**************************************************************************/

	public boolean handleEvent(Event event)
	{
		return super.handleEvent(event);
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
				updateDraftRanking();
				enable(true);
				fSubmitBtn.enable(true);
			}
			else if(evt.target == fScoutBtn)
			{
				fScoutBtn.enable(false);
				enable(false);
				
				fPlayerScoutDialog =
					new PlayerScoutDialog(this,this,fPlayerScoutRqst,fGameLevel);
				
				fPlayerScoutDialog.show();
			}
			else if(evt.target == fMoveUpBtn)
			{
				moveItemInRankingList(false);
			}
			else if(evt.target == fMoveDownBtn)
			{
				moveItemInRankingList(true);
			}
			else if(evt.target == fMoveLeftBtn)
			{
				moveScoutPlayerToRankingList();
			}
			else if(evt.target == fRemoveBtn)
			{
				removeItemFromRankingList();
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
	/**************************************************************************/

	protected void getDraftRanking() throws IOException
	{
		DraftRankingQueryResp pResponse =
			((ASFantasyDraftRequestor)fAppRequestor).draftRankingQueryRequest();

		if(pResponse == null)
		{
			String msg = "Unable to access draft ranking.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameLevel = pResponse.fGameLevel;
		fRankingPlayerVector = pResponse.fPlayerVector;
	}
	
	/**************************************************************************/

	private void updateDraftRanking()
	{
		DraftRankingUpdateResp pResponse;
		String msg;
		
		fSubmitBtn.enable(false);
		pResponse = ((ASFantasyDraftRequestor)fAppRequestor).draftRankingUpdateRequest(
			fRankingPlayerVector);
		fSubmitBtn.enable(true);

		if(pResponse != null)
			msg = "Your draft ranking has been saved.";
		else
			msg = "Unable to save draft ranking.  Please try again later.";

		MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,msg);
	}
	
	/**************************************************************************/

	private void getPlayerScoutPlayers()
	{
		PlayerScoutResp pResponse;
		
		pResponse = fAppRequestor.playerScoutRequest(fPlayerScoutRqst);

		if(pResponse != null)
		{
			fScoutPlayerVector = pResponse.fPlayerVector;

			/*
			fScoutPlayerVector.sort(new PlayerScoutPlayerByNameCmpr());
			fScoutSortChc.select(0);
			*/
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

	abstract protected int getMaxPlayersInRanking();

	/**************************************************************************/

	protected JCVector buildRankingRowFromPlayer(int rank,DraftRankingPlayer player)
	{
		JCVector row = new JCVector();

		row.addElement(new Integer(rank));
		row.addElement(player.fName.buildRevFullName());
		row.addElement(player.fProfTeamAbbr);
		row.addElement(player.fPosition.toString());

		return(row);
	}

	/**************************************************************************/

	protected void loadRankingList()
	{
		DraftRankingPlayer player;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = fRankingPlayerVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			player = (DraftRankingPlayer)fRankingPlayerVector.elementAt(i);
			row = buildRankingRowFromPlayer(i + 1,player);
			items.addElement(row);
		}
			
		fRankingMCLst.setItems(items);
	}
	
	/**************************************************************************/
	/**************************************************************************/

	protected JCVector buildScoutRowFromPlayer(PlayerScoutPlayer player)
	{
		JCVector row = new JCVector();

		row.addElement(player.fName.buildRevFullName());
		row.addElement(player.fProfTeamAbbr);
		row.addElement(player.fPosition.toString());

		row.addElement(buildScoutStatFromValueType(player,0));
		row.addElement(buildScoutStatFromValueType(player,1));
		row.addElement(buildScoutStatFromValueType(player,2));

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
	/**************************************************************************/
	/*

	protected boolean isRankingListStillSortedByRank()
	{
		DraftRankingPlayer player;
		int i,numItems = fRankingPlayerVector.size();
		int rank;
		JCVector items = fRankingMCLst.getItems();
		JCVector row;

		if(items.size() != numItems)
			return(false);

		for(i = 0; i < numItems; i++)
		{
			player = (DraftRankingPlayer)fRankingPlayerVector.elementAt(i);
			row = (JCVector)(items.elementAt(i));
			rank = ((Integer)row.elementAt(fRankingRankCol)).intValue();

			if(rank != i + 1)
				return(false);
		}

		return(true);
	}

	*/
	/**************************************************************************/
	
	protected boolean moveItemInRankingList(boolean moveDown)
	{
		DraftRankingPlayer player;
		int numItems = fRankingPlayerVector.size();

		int itemPos = fRankingMCLst.getSelectedIndex();
		int newPos = (moveDown ? itemPos + 1 : itemPos - 1);

		JCVector items;
		JCVector row;
		
		if((itemPos < 0) || (itemPos >= numItems) ||
				(newPos < 0) || (newPos >= numItems))
			return(false);

		player = (DraftRankingPlayer)fRankingPlayerVector.elementAt(itemPos);
		fRankingPlayerVector.removeElementAt(itemPos);
		fRankingPlayerVector.insertElementAt(player,newPos);
		
		items = fRankingMCLst.getItems();

		row = buildRankingRowFromPlayer(newPos + 1,player);
		items.setElementAt(newPos,row);

		player = (DraftRankingPlayer)fRankingPlayerVector.elementAt(itemPos);
		row = buildRankingRowFromPlayer(itemPos + 1,player);
		items.setElementAt(itemPos,row);

		fRankingMCLst.deselect(itemPos);
		fRankingMCLst.select(newPos);
		fRankingMCLst.makeVisible(newPos);

		return(true);
	}
	
	/**************************************************************************/
	
	protected boolean removeItemFromRankingList()
	{
		int numItems = fRankingPlayerVector.size();
		int itemPos = fRankingMCLst.getSelectedIndex();
		
		if((itemPos < 0) || (itemPos >= numItems))
			return(false);

		fRankingPlayerVector.removeElementAt(itemPos);
		
		if(itemPos == numItems - 1)
			itemPos--;
		loadRankingList();
		if(itemPos >= 0)
			fRankingMCLst.select(itemPos);
		
		return(true);
	}
	
	/**************************************************************************/
	
	protected void moveScoutPlayerToRankingList()
	{
		PlayerScoutPlayer player;
		DraftRankingPlayer rankingPlayer;
		int rankingPos = fRankingMCLst.getSelectedIndex();
		int playerRankingPos;
		int scoutPos = fScoutMCLst.getSelectedIndex();
		JCVector scoutRow;
		int playerID;
		int numRankingPlayers = fRankingPlayerVector.size();
	
		if(fScoutPlayerVector.size() == 0)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Your Eligible Players list is empty.  Press the Scout button to search for eligible players.");
			return;
		}

		scoutRow = (JCVector)fScoutMCLst.getSelectedItem();
		if(scoutRow == null)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Select the player you wish to add from the Eligible Players list.");
			return;
		}
		playerID = ((Integer)scoutRow.elementAt(fScoutPlayerIDCol)).intValue();
		player = fScoutPlayerVector.getByID(playerID);
		if(player == null)
			return;

		if((playerRankingPos = fRankingPlayerVector.getPosByID(playerID)) != -1)
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Player is already ranked at #" + (playerRankingPos + 1) + ".");
			return;
		}
			
		if(numRankingPlayers >= getMaxPlayersInRanking())
		{
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				"Your Draft Ranking may only hold " +
					getMaxPlayersInRanking() + " players.");
			return;
		}

		if(rankingPos == BWTEnum.NOTFOUND)
		{
			if(numRankingPlayers > 0)
			{
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
					"Select the position in the Your Draft Rankings list for where the new player should be added.");
				return;
			}
			else
				rankingPos = 0;
		}

		if((rankingPos < 0) || (rankingPos >= numRankingPlayers))
			rankingPos = numRankingPlayers;

		rankingPlayer = new DraftRankingPlayer();
		rankingPlayer.fPlayerID = player.fPlayerID;
		rankingPlayer.fName = player.fName;
		rankingPlayer.fProfTeamAbbr = player.fProfTeamAbbr;
		rankingPlayer.fPosition = player.fPosition;

		/* Add to ranking lists */
		fRankingPlayerVector.insertElementAt(rankingPlayer,rankingPos);
		loadRankingList();
		if(rankingPos < fRankingPlayerVector.size() - 1)
			rankingPos++;
		fRankingMCLst.select(rankingPos);
		fRankingMCLst.makeVisible(rankingPos);
		
		/* Remove from scout lists */
		fScoutPlayerVector.removeByID(playerID);
		if(scoutPos >= fScoutPlayerVector.size())
			scoutPos--;
		loadScoutList();
		if(scoutPos >= 0)
			fScoutMCLst.select(scoutPos);
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

		fScoutMCLst.clear();	// to reset selection and top row
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
				//BOB loadScoutList(); - Already called by sortScoutList()
			}
			
			fPlayerScoutDialog = null;
			fScoutBtn.enable(true);
			enable(true);
		}
	}
	
}

/******************************************************************************/
/******************************************************************************/
