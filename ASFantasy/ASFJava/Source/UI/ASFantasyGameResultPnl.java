/* ASFantasyGameResultPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;

/******************************************************************************/

abstract public class ASFantasyGameResultPnl extends Panel
{
	/**************************************************************************/

	public ASFantasyGameResultPnl()
	{
	}

	/**************************************************************************/

	abstract public void open();

	/**************************************************************************/

	abstract protected void loadData(ScheduleDayStatus status,
		TeamInfoName visitTeam,short visitScore,
		PlayerInfoVector visitPlayerVector,TeamInfoName homeTeam,
		short homeScore,PlayerInfoVector homePlayerVector);

}

/******************************************************************************/
/******************************************************************************/
