/* ASFantasyTradeGetPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.bwt.*;

/******************************************************************************/

public class ASFantasyTradeGetPnl extends ASFantasyTradeSubPnl
{
	//{{DECLARE_CONTROLS
	jclass.bwt.JCLabel fGetPlayersLbl;
	jclass.bwt.JCLabel fGetOneLbl;
	java.awt.Choice fGetOneChc;
	jclass.bwt.JCLabel fGetTwoLbl;
	java.awt.Choice fGetTwoChc;
	jclass.bwt.JCLabel fGetThreeLbl;
	java.awt.Choice fGetThreeChc;
	jclass.bwt.JCLabel fGetFourLbl;
	java.awt.Choice fGetFourChc;
	jclass.bwt.JCLabel fGetFiveLbl;
	java.awt.Choice fGetFiveChc;
	jclass.bwt.JCLabel fRosterLbl;
	jclass.bwt.JCMultiColumnList fRosterMCLst;
	//}}
	
	java.awt.Choice fGetChcArray[] = new java.awt.Choice[5];

	/**************************************************************************/

	public ASFantasyTradeGetPnl(TGameLevel gameLevel)
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
		fGetPlayersLbl = new jclass.bwt.JCLabel();
		fGetPlayersLbl.reshape(0,0,150,18);
		add(fGetPlayersLbl);
		fGetPlayersLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Get Players");
			fGetPlayersLbl.setTextList(tempString);
		}
		fGetOneLbl = new jclass.bwt.JCLabel();
		fGetOneLbl.reshape(5,25,30,16);
		fGetOneLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGetOneLbl);
		fGetOneLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("1.");
			fGetOneLbl.setTextList(tempString);
		}
		fGetOneChc = new java.awt.Choice();
		add(fGetOneChc);
		fGetOneChc.reshape(40,23,230,19);
		fGetOneChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGetTwoLbl = new jclass.bwt.JCLabel();
		fGetTwoLbl.reshape(5,46,30,16);
		fGetTwoLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGetTwoLbl);
		fGetTwoLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("2.");
			fGetTwoLbl.setTextList(tempString);
		}
		fGetTwoChc = new java.awt.Choice();
		add(fGetTwoChc);
		fGetTwoChc.reshape(40,44,230,19);
		fGetTwoChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGetThreeLbl = new jclass.bwt.JCLabel();
		fGetThreeLbl.reshape(5,67,30,16);
		fGetThreeLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGetThreeLbl);
		fGetThreeLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("3.");
			fGetThreeLbl.setTextList(tempString);
		}
		fGetThreeChc = new java.awt.Choice();
		add(fGetThreeChc);
		fGetThreeChc.reshape(40,65,230,19);
		fGetThreeChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGetFourLbl = new jclass.bwt.JCLabel();
		fGetFourLbl.reshape(5,88,30,16);
		fGetFourLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGetFourLbl);
		fGetFourLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("4.");
			fGetFourLbl.setTextList(tempString);
		}
		fGetFourChc = new java.awt.Choice();
		add(fGetFourChc);
		fGetFourChc.reshape(40,86,230,19);
		fGetFourChc.setFont(new Font("Helvetica", Font.BOLD, 9));
		fGetFiveLbl = new jclass.bwt.JCLabel();
		fGetFiveLbl.reshape(5,109,30,16);
		fGetFiveLbl.setFont(new Font("Helvetica", Font.BOLD, 9));
		add(fGetFiveLbl);
		fGetFiveLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("5.");
			fGetFiveLbl.setTextList(tempString);
		}
		fGetFiveChc = new java.awt.Choice();
		add(fGetFiveChc);
		fGetFiveChc.reshape(40,107,230,19);
		fGetFiveChc.setFont(new Font("Helvetica", Font.BOLD, 9));
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

		fGetChcArray[0] = fGetOneChc;
		fGetChcArray[1] = fGetTwoChc;
		fGetChcArray[2] = fGetThreeChc;
		fGetChcArray[3] = fGetFourChc;
		fGetChcArray[4] = fGetFiveChc;

		setUpMCListHeader(fRosterMCLst);
	}

	/**************************************************************************/

	protected void loadData(PlayerInfoVector playerInfoVector,
		PlayerIDVector getPlayerIDVector) throws Exception
	{
		fillSelChoiceArrayWithPlayerInfoVector(playerInfoVector,
			getPlayerIDVector,fGetChcArray);

		fillMCListWithPlayerInfoVector(playerInfoVector,fRosterMCLst);
	}

	/**************************************************************************/

	public void enablePlayers(boolean enable)
	{
		enableChoiceArray(fGetChcArray,enable);
	}

	/**************************************************************************/

	protected void unloadData(PlayerInfoVector playerInfoVector,
		PlayerIDVector getPlayerIDVector)
	{
		addPlayerIDToVectorFromChoiceArray(playerInfoVector,fGetChcArray,
			getPlayerIDVector);
	}
}

/******************************************************************************/
/******************************************************************************/
