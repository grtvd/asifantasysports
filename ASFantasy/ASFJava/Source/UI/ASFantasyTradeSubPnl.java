/* ASFantasyTradeSubPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.bwt.*;
import jclass.util.*;

/******************************************************************************/

abstract public class ASFantasyTradeSubPnl extends Panel
{
	protected TGameLevel fGameLevel = TGameLevel.gml_Standard;

	/**************************************************************************/

	public ASFantasyTradeSubPnl(TGameLevel gameLevel)
	{
		fGameLevel  = gameLevel;
	}

	/**************************************************************************/

	abstract public void open();

	/**************************************************************************/

	protected void setUpMCListHeader(jclass.bwt.JCMultiColumnList mcLst)
	{
		jclass.bwt.JCHeader header = mcLst.getHeader();
		jclass.bwt.JCMultiColumnListComponent body = mcLst.getList();
		
		if(fGameLevel == TGameLevel.gml_Standard)
			mcLst.setNumColumns(4);
		else
			mcLst.setNumColumns(5);

		header.setFont(new java.awt.Font("Helvetica",java.awt.Font.BOLD,12));
		header.setBackground(new Color(12632256));
		body.setBackground(Color.white);

		{
			java.lang.String[] tempString = new java.lang.String[5];
			tempString[0] = new java.lang.String("Player");
			tempString[1] = new java.lang.String("PT");
			tempString[2] = new java.lang.String("Pos");
			tempString[3] = new java.lang.String("Pts");
			if(fGameLevel == TGameLevel.gml_Premium)
				tempString[4] = new java.lang.String("S");
			mcLst.setColumnButtons(tempString);
		}
		
		if(fGameLevel == TGameLevel.gml_Standard)
		{
			mcLst.setColumnWidth(0,140);
			mcLst.setColumnWidth(1,40);
			mcLst.setColumnWidth(2,40);
			mcLst.setColumnWidth(3,35);
		}
		else
		{
			mcLst.setColumnWidth(0,105);
			mcLst.setColumnWidth(1,40);
			mcLst.setColumnWidth(2,40);
			mcLst.setColumnWidth(3,35);
			mcLst.setColumnWidth(4,35);
		}

		mcLst.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		mcLst.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		mcLst.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		mcLst.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		if(fGameLevel == TGameLevel.gml_Premium)
			mcLst.setColumnAlignment(4,BWTEnum.MIDDLECENTER);

		header.setColumnAlignment(0,BWTEnum.MIDDLELEFT);
		header.setColumnAlignment(1,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(2,BWTEnum.MIDDLECENTER);
		header.setColumnAlignment(3,BWTEnum.MIDDLECENTER);
		if(fGameLevel == TGameLevel.gml_Premium)
			header.setColumnAlignment(4,BWTEnum.MIDDLECENTER);

		mcLst.setAutoSelect(true);
	}

	/**************************************************************************/

	protected void fillMCListWithPlayerInfoVector(
		PlayerInfoVector playerInfoVector,jclass.bwt.JCMultiColumnList mcLst)
	{
		PlayerInfoExt player;
		JCVector items = new JCVector();
		JCVector row;
		int i,numItems = playerInfoVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			player = (PlayerInfoExt)playerInfoVector.elementAt(i);

			row = new JCVector();
			row.addElement(player.fName.buildRevFullName());
			row.addElement(player.fProfTeamAbbr);
			row.addElement(player.fPosition.toString());

			row.addElement(new Integer(player.fTotalPoints));
			if(fGameLevel == TGameLevel.gml_Premium)
				row.addElement(player.getStatus());

			items.addElement(row);
		}
		
		mcLst.setItems(items);
	}

	/**************************************************************************/

	protected void fillChoiceWithPlayerInfoVector(
		PlayerInfoVector playerInfoVector,Choice chc)
	{
		PlayerInfo player;
		int i,numItems = playerInfoVector.size();

		chc.addItem("--No Player Selected--");
		
		for(i = 0; i < numItems; i++)
		{
			player = (PlayerInfo)playerInfoVector.elementAt(i);
			chc.addItem(player.fName.buildRevFullName());
		}
	}

	/**************************************************************************/

	protected void fillSelChoiceArrayWithPlayerInfoVector(
		PlayerInfoVector playerInfoVector,PlayerIDVector playerIDVector,
		Choice chcArray[]) throws Exception
	{
		int i;
		int numItems;

		numItems = playerIDVector.size();

		for(i = 0; i < chcArray.length; i++)
		{
			fillChoiceWithPlayerInfoVector(playerInfoVector,chcArray[i]);

			if(numItems > i)
				selChoiceByPlayerID(chcArray[i],playerInfoVector,
					(Integer)playerIDVector.elementAt(i));
		}
	}

	/**************************************************************************/
	
	protected void selChoiceByPlayerID(Choice chc,PlayerInfoVector playerInfoVector,
		Integer playerID) throws Exception
	{
		int i,numItems = playerInfoVector.size();
		
		for(i = 0; i < numItems; i++)
		{
			if(((PlayerInfo)playerInfoVector.elementAt(i)).fPlayerID ==
				playerID.intValue())
			{
				chc.select(i + 1);
				return;
			}
		}

		throw new Exception("TradeSubPnl.selChoiceByPlayerID: player not found in Choice");
	}
	
	/**************************************************************************/

	protected void enableChoiceArray(Choice chcArray[],boolean enable)
	{
		int i;

		for(i = 0; i < chcArray.length; i++)
			chcArray[i].enable(enable);
	}

	/**************************************************************************/

	protected void clearChoiceArray(Choice chcArray[])
	{
		int i;

		for(i = 0; i < chcArray.length; i++)
			chcArray[i].select(0);
	}

	/**************************************************************************/

	protected void addPlayerIDToVectorFromChoice(
		PlayerInfoVector playerInfoVector,Choice chc,
		PlayerIDVector getPlayerIDVector)
	{
		int pos;

		if((pos = chc.getSelectedIndex()) > 0)
			getPlayerIDVector.addElement(new Integer(
				((PlayerInfo)playerInfoVector.elementAt(pos - 1)).fPlayerID));
	}

	/**************************************************************************/

	protected void addPlayerIDToVectorFromChoiceArray(
		PlayerInfoVector playerInfoVector,Choice chcArray[],
		PlayerIDVector playerIDVector)
	{
		int i;

		playerIDVector.removeAllElements();

		for(i = 0; i < chcArray.length; i++)
			addPlayerIDToVectorFromChoice(playerInfoVector,chcArray[i],
				playerIDVector);
	}
}

/******************************************************************************/
/******************************************************************************/
