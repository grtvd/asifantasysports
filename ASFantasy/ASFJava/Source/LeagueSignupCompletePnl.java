/* LeagueSignupCompletePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class LeagueSignupCompletePnl extends LeagueSignupMessagePnl
{
	public LeagueSignupCompletePnl(LeagueSignupRqst leagueSignupRqst,
		LeagueSignupResp leagueSignupResp)
	{
		super("Congratulations!\r\rLeague sign-up was successful.  "
			+ "You have been enrolled in the \"" + leagueSignupResp.fLeagueName
			+ "\" League.","League Sign-Up was successful!\r\rGood Luck!!");
	}

}

/******************************************************************************/
/******************************************************************************/
