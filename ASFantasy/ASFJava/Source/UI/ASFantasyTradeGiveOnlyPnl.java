/* ASFantasyTradeGiveOnlyPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.bwt.*;

/******************************************************************************/

public class ASFantasyTradeGiveOnlyPnl extends ASFantasyTradeSubPnl
{
	//{{DECLARE_CONTROLS
	jclass.bwt.JCLabel fGivePlayersLbl;
	jclass.bwt.JCLabel fGiveOneLbl;
	java.awt.Choice fGiveOneChc;
	jclass.bwt.JCLabel fGiveTwoLbl;
	java.awt.Choice fGiveTwoChc;
	jclass.bwt.JCLabel fGiveThreeLbl;
	java.awt.Choice fGiveThreeChc;
	jclass.bwt.JCLabel fGiveFourLbl;
	java.awt.Choice fGiveFourChc;
	jclass.bwt.JCLabel fGiveFiveLbl;
	java.awt.Choice fGiveFiveChc;
	jclass.bwt.JCLabel fRosterLbl;
	jclass.bwt.JCMultiColumnList fRosterMCLst;
	//}}

	java.awt.Choice fGiveChcArray[] = new java.awt.Choice[5];
	
	/**************************************************************************/

	public ASFantasyTradeGiveOnlyPnl(TGameLevel gameLevel)
	{
		super(gameLevel);
	}

	/**************************************************************************/

	public void open()
	{
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(282,400);
		setFont(new Font("Helvetica", Font.BOLD, 12));
		setBackground(new Color(12632256));
		fGivePlayersLbl = new jclass.bwt.JCLabel();
		fGivePlayersLbl.reshape(0,0,150,18);
		add(fGivePlayersLbl);
		fGivePlayersLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Give Players");
			fGivePlayersLbl.setTextList(tempString);
		}
		fGiveOneLbl = new jclass.bwt.JCLabel();
		fGiveOneLbl.reshape(5,25,30,16);
		fGiveOneLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGiveOneLbl);
		fGiveOneLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("1.");
			fGiveOneLbl.setTextList(tempString);
		}
		fGiveOneChc = new java.awt.Choice();
		add(fGiveOneChc);
		fGiveOneChc.reshape(40,23,230,19);
		fGiveOneChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGiveTwoLbl = new jclass.bwt.JCLabel();
		fGiveTwoLbl.reshape(5,46,30,16);
		fGiveTwoLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGiveTwoLbl);
		fGiveTwoLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("2.");
			fGiveTwoLbl.setTextList(tempString);
		}
		fGiveTwoChc = new java.awt.Choice();
		add(fGiveTwoChc);
		fGiveTwoChc.reshape(40,44,230,19);
		fGiveTwoChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGiveThreeLbl = new jclass.bwt.JCLabel();
		fGiveThreeLbl.reshape(5,67,30,16);
		fGiveThreeLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGiveThreeLbl);
		fGiveThreeLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("3.");
			fGiveThreeLbl.setTextList(tempString);
		}
		fGiveThreeChc = new java.awt.Choice();
		add(fGiveThreeChc);
		fGiveThreeChc.reshape(40,65,230,19);
		fGiveThreeChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGiveFourLbl = new jclass.bwt.JCLabel();
		fGiveFourLbl.reshape(5,88,30,16);
		fGiveFourLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGiveFourLbl);
		fGiveFourLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("4.");
			fGiveFourLbl.setTextList(tempString);
		}
		fGiveFourChc = new java.awt.Choice();
		add(fGiveFourChc);
		fGiveFourChc.reshape(40,86,230,19);
		fGiveFourChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGiveFiveLbl = new jclass.bwt.JCLabel();
		fGiveFiveLbl.reshape(5,109,30,16);
		fGiveFiveLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGiveFiveLbl);
		fGiveFiveLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("5.");
			fGiveFiveLbl.setTextList(tempString);
		}
		fGiveFiveChc = new java.awt.Choice();
		add(fGiveFiveChc);
		fGiveFiveChc.reshape(40,107,230,19);
		fGiveFiveChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fRosterLbl = new jclass.bwt.JCLabel();
		fRosterLbl.reshape(0,131,150,18);
		add(fRosterLbl);
		fRosterLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Roster");
			fRosterLbl.setTextList(tempString);
		}
		fRosterMCLst = new jclass.bwt.JCMultiColumnList();
		fRosterMCLst.reshape(4,152,275,246);
		fRosterMCLst.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fRosterMCLst.setBackground(new Color(12632256));
		add(fRosterMCLst);
		fRosterMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fRosterMCLst.setSelectedBackground(new Color(255));
		//}}

		fGiveChcArray[0] = fGiveOneChc;
		fGiveChcArray[1] = fGiveTwoChc;
		fGiveChcArray[2] = fGiveThreeChc;
		fGiveChcArray[3] = fGiveFourChc;
		fGiveChcArray[4] = fGiveFiveChc;

		setUpMCListHeader(fRosterMCLst);
	}

	/**************************************************************************/

	protected void loadData(PlayerInfoVector playerInfoVector,
		PlayerIDVector givePlayerIDVector) throws Exception
	{
		fillSelChoiceArrayWithPlayerInfoVector(playerInfoVector,
			givePlayerIDVector,fGiveChcArray);

		fillMCListWithPlayerInfoVector(playerInfoVector,fRosterMCLst);
	}

	/**************************************************************************/

	public void enablePlayers(boolean enableGivePlayers)
	{
		enableChoiceArray(fGiveChcArray,enableGivePlayers);
	}

	/**************************************************************************/

	public void clear()
	{
		clearChoiceArray(fGiveChcArray);
	}
	/**************************************************************************/

	protected void unloadData(PlayerInfoVector playerInfoVector,
		PlayerIDVector givePlayerIDVector)
	{
		addPlayerIDToVectorFromChoiceArray(playerInfoVector,fGiveChcArray,
			givePlayerIDVector);
	}

}

/******************************************************************************/
/******************************************************************************/
