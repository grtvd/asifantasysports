/* ASFantasyGameResultNonePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;
import jclass.bwt.*;
import jclass.util.*;

/******************************************************************************/

public class ASFantasyGameResultNonePnl extends ASFantasyGameResultPnl
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	jclass.bwt.JCLabel fNoResultsLbl;
	//}}

	/**************************************************************************/

	public ASFantasyGameResultNonePnl()
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
		fNoResultsLbl = new jclass.bwt.JCLabel();
		fNoResultsLbl.reshape(4,6,300,18);
		fNoResultsLbl.setFont(new Font("Helvetica", Font.BOLD, 14));
		fBorderPnl.add(fNoResultsLbl);
		fNoResultsLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("No Game Results");
			fNoResultsLbl.setTextList(tempString);
		}
		//}}
	}

	/**************************************************************************/

	protected void loadData(ScheduleDayStatus status,TeamInfoName visitTeam,
		short visitScore,PlayerInfoVector visitPlayerVector,
		TeamInfoName homeTeam,short homeScore,
		PlayerInfoVector homePlayerVector)
	{
	}

}

/******************************************************************************/
/******************************************************************************/
