/* LeagueSignupFailedPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class LeagueSignupFailedPnl extends LeagueSignupMessagePnl
{
	public LeagueSignupFailedPnl(String reason)
	{
		super("Signup could not be successfully completed.\r\rReason: " + reason,
			"Signup Failed.\r\rYou can select [Previous] to correct information and retry.");
	}

}

/******************************************************************************/
/******************************************************************************/
