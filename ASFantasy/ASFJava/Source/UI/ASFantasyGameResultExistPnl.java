/* ASFantasyGameResultExistPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.bwt.*;
import jclass.util.*;

/******************************************************************************/

public class ASFantasyGameResultExistPnl extends ASFantasyGameResultPnl
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	jclass.bwt.JCLabel fVisitTeamNameLbl;
	jclass.bwt.JCLabel fVisitTeamScoreLbl;
	jclass.bwt.JCMultiColumnList fVisitPlayersMCLst;
	jclass.bwt.JCLabel fHomeTeamNameLbl;
	jclass.bwt.JCLabel fHomeTeamScoreLbl;
	jclass.bwt.JCMultiColumnList fHomePlayersMCLst;
	//}}

	/**************************************************************************/

	public ASFantasyGameResultExistPnl()
	{
	}

	/**************************************************************************/

	public void open()
	{
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(550,260);
		setFont(new Font("Helvetica", Font.BOLD, 12));
		setBackground(new Color(12632256));
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,550,260);
		fBorderPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fBorderPnl);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fVisitTeamNameLbl = new jclass.bwt.JCLabel();
		fVisitTeamNameLbl.reshape(8,8,195,26);
		fVisitTeamNameLbl.setFont(new Font("Helvetica", Font.BOLD, 14));
		fVisitTeamNameLbl.setForeground(new Color(16777215));
		fVisitTeamNameLbl.setBackground(new Color(8421504));
		fBorderPnl.add(fVisitTeamNameLbl);
		fVisitTeamNameLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Visit Team");
			fVisitTeamNameLbl.setTextList(tempString);
		}
		fVisitTeamNameLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fVisitTeamNameLbl.setShadowThickness(3);
		fVisitTeamScoreLbl = new jclass.bwt.JCLabel();
		fVisitTeamScoreLbl.reshape(205,8,40,26);
		fVisitTeamScoreLbl.setFont(new Font("Helvetica", Font.BOLD, 14));
		fVisitTeamScoreLbl.setForeground(new Color(16777215));
		fVisitTeamScoreLbl.setBackground(new Color(8421504));
		fBorderPnl.add(fVisitTeamScoreLbl);
		fVisitTeamScoreLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("999");
			fVisitTeamScoreLbl.setTextList(tempString);
		}
		fVisitTeamScoreLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fVisitTeamScoreLbl.setShadowThickness(3);
		fVisitPlayersMCLst = new jclass.bwt.JCMultiColumnList();
		fVisitPlayersMCLst.reshape(8,45,255,200);
		fVisitPlayersMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fVisitPlayersMCLst);
		fVisitPlayersMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fVisitPlayersMCLst.setSelectedBackground(new Color(255));
		fHomeTeamNameLbl = new jclass.bwt.JCLabel();
		fHomeTeamNameLbl.reshape(275,8,195,26);
		fHomeTeamNameLbl.setFont(new Font("Helvetica", Font.BOLD, 14));
		fHomeTeamNameLbl.setForeground(new Color(16777215));
		fHomeTeamNameLbl.setBackground(new Color(8421504));
		fBorderPnl.add(fHomeTeamNameLbl);
		fHomeTeamNameLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Home Team");
			fHomeTeamNameLbl.setTextList(tempString);
		}
		fHomeTeamNameLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fHomeTeamNameLbl.setShadowThickness(3);
		fHomeTeamScoreLbl = new jclass.bwt.JCLabel();
		fHomeTeamScoreLbl.reshape(472,8,40,26);
		fHomeTeamScoreLbl.setFont(new Font("Helvetica", Font.BOLD, 14));
		fHomeTeamScoreLbl.setForeground(new Color(16777215));
		fHomeTeamScoreLbl.setBackground(new Color(8421504));
		fBorderPnl.add(fHomeTeamScoreLbl);
		fHomeTeamScoreLbl.setAlignment(jclass.bwt.JCLabel.MIDDLERIGHT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("999");
			fHomeTeamScoreLbl.setTextList(tempString);
		}
		fHomeTeamScoreLbl.setShadowType(jclass.bwt.JCLabel.SHADOW_OUT);
		fHomeTeamScoreLbl.setShadowThickness(3);
		fHomePlayersMCLst = new jclass.bwt.JCMultiColumnList();
		fHomePlayersMCLst.reshape(275,45,255,200);
		fHomePlayersMCLst.setBackground(new Color(12632256));
		fBorderPnl.add(fHomePlayersMCLst);
		fHomePlayersMCLst.setScrollbarDisplay(jclass.bwt.JCMultiColumnList.DISPLAY_VERTICAL_ONLY);
		fHomePlayersMCLst.setSelectedBackground(new Color(255));

		java.awt.Font font = new java.awt.Font("Helvetica",java.awt.Font.BOLD,12);
		Color color = new Color(12632256);

		jclass.bwt.JCHeader header = fVisitPlayersMCLst.getHeader();
		header.setFont(font);
		header.setBackground(color);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);

		header = fHomePlayersMCLst.getHeader();
		header.setFont(font);
		header.setBackground(color);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);

		{
			java.lang.String[] tempString = new java.lang.String[3];
			tempString[0] = new java.lang.String("Player");
			tempString[1] = new java.lang.String("Pos");
			tempString[2] = new java.lang.String("Pts.");

			fVisitPlayersMCLst.setColumnButtons(tempString);
			fHomePlayersMCLst.setColumnButtons(tempString);
		}
		fVisitPlayersMCLst.setSelectedForeground(Color.white);
		fHomePlayersMCLst.setSelectedForeground(Color.white);
		//}}

		fVisitPlayersMCLst.setNumColumns(3);
		fHomePlayersMCLst.setNumColumns(3);

		fVisitPlayersMCLst.setColumnWidth(0,155);
		fVisitPlayersMCLst.setColumnWidth(1,40);
		fVisitPlayersMCLst.setColumnWidth(2,40);

		fHomePlayersMCLst.setColumnWidth(0,155);
		fHomePlayersMCLst.setColumnWidth(1,40);
		fHomePlayersMCLst.setColumnWidth(2,40);

		fVisitPlayersMCLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		fVisitPlayersMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fVisitPlayersMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);

		fHomePlayersMCLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		fHomePlayersMCLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		fHomePlayersMCLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);

		fVisitPlayersMCLst.getList().setBackground(Color.white);
		fHomePlayersMCLst.getList().setBackground(Color.white);

		fVisitPlayersMCLst.setAutoSelect(true);
		fHomePlayersMCLst.setAutoSelect(true);
	}

	/**************************************************************************/

	protected void loadData(ScheduleDayStatus status,TeamInfoName visitTeam,
		short visitScore,PlayerInfoVector visitPlayerVector,
		TeamInfoName homeTeam,short homeScore,
		PlayerInfoVector homePlayerVector)
	{
		fVisitTeamNameLbl.setText(visitTeam.buildName());
		fVisitTeamScoreLbl.setText(Integer.toString(visitScore));
		loadPlayerList(fVisitPlayersMCLst,visitPlayerVector);

		fHomeTeamNameLbl.setText(homeTeam.buildName());
		fHomeTeamScoreLbl.setText(Integer.toString(homeScore));
		loadPlayerList(fHomePlayersMCLst,homePlayerVector);

		if(status == ScheduleDayStatus.sdst_Completed)
		{
			if(visitScore > homeScore)
			{
				fVisitTeamNameLbl.setForeground(Color.yellow);
				fVisitTeamScoreLbl.setForeground(Color.yellow);
			}
			else if(homeScore > visitScore)
			{
				fHomeTeamNameLbl.setForeground(Color.yellow);
				fHomeTeamScoreLbl.setForeground(Color.yellow);
			}
			//else tie
		}
	}

	/**************************************************************************/

	protected void loadPlayerList(jclass.bwt.JCMultiColumnList fPlayersMCLst,
		PlayerInfoVector fPlayerVector)
	{
		GameResultsPlayer player;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = fPlayerVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			player = (GameResultsPlayer)fPlayerVector.elementAt(i);

			row = new JCVector();
			row.addElement(player.fName.buildRevFullName());
			row.addElement(player.fPosition.toString());
			row.addElement(new Integer(player.fTotalPoints));
			items.addElement(row);
		}
		
		fPlayersMCLst.setItems(items);
	}

}

/******************************************************************************/
/******************************************************************************/
