/* LeagueSignupSubPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;

/******************************************************************************/

public abstract class LeagueSignupSubPnl extends Panel
{
	/**************************************************************************/

	public void open()
	{
	}

	/**************************************************************************/

	abstract protected void loadData();

	/**************************************************************************/

	abstract protected boolean unloadData(boolean validate);

	/**************************************************************************/

	abstract protected String getInstructions();
}

/******************************************************************************/
/******************************************************************************/
