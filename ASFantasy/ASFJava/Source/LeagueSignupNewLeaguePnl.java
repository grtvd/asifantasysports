/* LeagueSignupNewLeaguePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class LeagueSignupNewLeaguePnl extends LeagueSignupSubPnl
{
	//{{DECLARE_CONTROLS
	java.awt.Label fPasswordLbl;
	java.awt.TextField fPasswordEdt;
	//}}
	private LeagueSignupRqst fLeagueSignupRqst;

	/**************************************************************************/

	public LeagueSignupNewLeaguePnl(LeagueSignupRqst leagueSignupRqst)
	{
		fLeagueSignupRqst = leagueSignupRqst;
	}

	/**************************************************************************/

	public void open()
	{
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(255,240);
		setBackground(new Color(12632256));
		fPasswordLbl = new java.awt.Label("Password");
		fPasswordLbl.reshape(10,10,75,14);
		fPasswordLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fPasswordLbl);
		fPasswordEdt = new java.awt.TextField();
		fPasswordEdt.reshape(90,6,91,21);
		fPasswordEdt.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fPasswordEdt);
		//}}
	}

	/**************************************************************************/

	protected void loadData()
	{
		fPasswordEdt.setText(fLeagueSignupRqst.fLeaguePassword);
	}

	/**************************************************************************/

	protected boolean unloadData(boolean validate)
	{
		fLeagueSignupRqst.fLeaguePassword = fPasswordEdt.getText();
		if(validate && (fLeagueSignupRqst.fLeaguePassword.length() == 0))
		{
			//fSignupNewLeagueComp.fPasswordEdt.requestFocus();
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"You must supply a Password for your private league.");
			return(false);
		}
		if(validate && (fLeagueSignupRqst.fLeaguePassword.length() < 6))
		{
			//fSignupNewLeagueComp.fPasswordEdt.requestFocus();
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"The Password must be at least 6 characters in length.");
			return(false);
		}
		if(validate && (fLeagueSignupRqst.fLeaguePassword.length() > 10))
		{
			//fSignupNewLeagueComp.fPasswordEdt.requestFocus();
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"The Password must not be greater than 10 characters in length.");
			return(false);
		}
		return(true);
	}

	/**************************************************************************/

	protected String getInstructions()
	{
		return("Enter the password of your private league.\r\rThe password must be given to the individuals who wish to join your newly created league.");
	}
}

/******************************************************************************/
/******************************************************************************/
