/* LeagueSignupVerifyPnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class LeagueSignupVerifyPnl extends LeagueSignupMessagePnl
{
	/**************************************************************************/
	
	public LeagueSignupVerifyPnl(LeagueSignupRqst leagueSignupRqst)
	{
		super(null,"Please verify that your information is correct.\r\r"
			+ "Press the [Previous] button if you need to make any "
			+ "changes.\r\rWhen you are ready, press the [Sign Up] button "
			+ "to submit your request.");

		setMessage(buildMessage(leagueSignupRqst));
	}

	/**************************************************************************/

	private String buildMessage(LeagueSignupRqst leagueSignupRqst)
	{
		String str;

		if(leagueSignupRqst.fLst == LeagueSignupRqst.lst_CreatePrivate)
		{
			str = "You are creating a new private league.";
		}
		else if(leagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinPrivate)
		{
			str = "You are joining the existing private league named \""
				+ leagueSignupRqst.fLeagueName + "\".";
		}
		else
			str = "You are joining the next available public league.";

		return(str);
	}

}

/******************************************************************************/
/******************************************************************************/
