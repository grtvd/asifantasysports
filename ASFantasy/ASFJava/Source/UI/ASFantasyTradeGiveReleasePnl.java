/* ASFantasyTradeGiveReleasePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.bwt.*;

/******************************************************************************/

public class ASFantasyTradeGiveReleasePnl extends ASFantasyTradeSubPnl
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
	jclass.bwt.JCLabel fReleasePlayersLbl;
	jclass.bwt.JCLabel fReleaseOneLbl;
	java.awt.Choice fReleaseOneChc;
	jclass.bwt.JCLabel fReleaseTwoLbl;
	java.awt.Choice fReleaseTwoChc;
	jclass.bwt.JCLabel fReleaseThreeLbl;
	java.awt.Choice fReleaseThreeChc;
	jclass.bwt.JCLabel fReleaseFourLbl;
	java.awt.Choice fReleaseFourChc;
	jclass.bwt.JCLabel fRosterLbl;
	jclass.bwt.JCMultiColumnList fRosterMCLst;
	//}}
	
	java.awt.Choice fGiveChcArray[] = new java.awt.Choice[5];
	java.awt.Choice fReleaseChcArray[] = new java.awt.Choice[4];

	/**************************************************************************/

	public ASFantasyTradeGiveReleasePnl(TGameLevel gameLevel)
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
		fReleasePlayersLbl = new jclass.bwt.JCLabel();
		fReleasePlayersLbl.reshape(0,131,150,18);
		add(fReleasePlayersLbl);
		fReleasePlayersLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Release Players");
			fReleasePlayersLbl.setTextList(tempString);
		}
		fReleaseOneLbl = new jclass.bwt.JCLabel();
		fReleaseOneLbl.reshape(5,156,30,16);
		fReleaseOneLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fReleaseOneLbl);
		fReleaseOneLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("1.");
			fReleaseOneLbl.setTextList(tempString);
		}
		fReleaseOneChc = new java.awt.Choice();
		add(fReleaseOneChc);
		fReleaseOneChc.reshape(40,154,230,19);
		fReleaseOneChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fReleaseTwoLbl = new jclass.bwt.JCLabel();
		fReleaseTwoLbl.reshape(5,177,30,16);
		fReleaseTwoLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fReleaseTwoLbl);
		fReleaseTwoLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("2.");
			fReleaseTwoLbl.setTextList(tempString);
		}
		fReleaseTwoChc = new java.awt.Choice();
		add(fReleaseTwoChc);
		fReleaseTwoChc.reshape(40,175,230,19);
		fReleaseTwoChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fReleaseThreeLbl = new jclass.bwt.JCLabel();
		fReleaseThreeLbl.reshape(5,198,30,16);
		fReleaseThreeLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fReleaseThreeLbl);
		fReleaseThreeLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("3.");
			fReleaseThreeLbl.setTextList(tempString);
		}
		fReleaseThreeChc = new java.awt.Choice();
		add(fReleaseThreeChc);
		fReleaseThreeChc.reshape(40,196,230,19);
		fReleaseThreeChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fReleaseFourLbl = new jclass.bwt.JCLabel();
		fReleaseFourLbl.reshape(5,219,30,16);
		fReleaseFourLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fReleaseFourLbl);
		fReleaseFourLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("4.");
			fReleaseFourLbl.setTextList(tempString);
		}
		fReleaseFourChc = new java.awt.Choice();
		add(fReleaseFourChc);
		fReleaseFourChc.reshape(40,217,230,19);
		fReleaseFourChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fRosterLbl = new jclass.bwt.JCLabel();
		fRosterLbl.reshape(0,241,150,18);
		add(fRosterLbl);
		fRosterLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Roster");
			fRosterLbl.setTextList(tempString);
		}
		fRosterMCLst = new jclass.bwt.JCMultiColumnList();
		fRosterMCLst.reshape(4,262,275,136);
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

		fReleaseChcArray[0] = fReleaseOneChc;
		fReleaseChcArray[1] = fReleaseTwoChc;
		fReleaseChcArray[2] = fReleaseThreeChc;
		fReleaseChcArray[3] = fReleaseFourChc;

		setUpMCListHeader(fRosterMCLst);
	}

	/**************************************************************************/

	protected void loadData(PlayerInfoVector playerInfoVector,
		PlayerIDVector givePlayerIDVector,PlayerIDVector releasePlayerIDVector)
		throws Exception
	{
		fillSelChoiceArrayWithPlayerInfoVector(playerInfoVector,
			givePlayerIDVector,fGiveChcArray);

		fillSelChoiceArrayWithPlayerInfoVector(playerInfoVector,
			releasePlayerIDVector,fReleaseChcArray);

		fillMCListWithPlayerInfoVector(playerInfoVector,fRosterMCLst);
	}

	/**************************************************************************/

	public void enablePlayers(boolean enableGivePlayers,boolean enableReleasePlayers)
	{
		enableChoiceArray(fGiveChcArray,enableGivePlayers);
		enableChoiceArray(fReleaseChcArray,enableReleasePlayers);
	}

	/**************************************************************************/

	public void clear()
	{
		clearChoiceArray(fGiveChcArray);
		clearChoiceArray(fReleaseChcArray);
	}

	/**************************************************************************/

	protected void unloadData(PlayerInfoVector playerInfoVector,
		PlayerIDVector givePlayerIDVector,PlayerIDVector releasePlayerIDVector)
	{
		addPlayerIDToVectorFromChoiceArray(playerInfoVector,fGiveChcArray,
			givePlayerIDVector);
		addPlayerIDToVectorFromChoiceArray(playerInfoVector,fReleaseChcArray,
			releasePlayerIDVector);
	}

}

/******************************************************************************/
/******************************************************************************/
