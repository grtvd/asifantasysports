/* LeagueSignupPickLeaguePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class LeagueSignupPickLeaguePnl extends LeagueSignupSubPnl
{
	//{{DECLARE_CONTROLS
	java.awt.Label fInstrucLbl;
	java.awt.Checkbox fPublicLeagueChk;
	CheckboxGroup Group1;
	java.awt.Checkbox fNewLeagueChk;
	java.awt.Checkbox fJoinLeagueChk;
	//}}
	private LeagueSignupRqst fLeagueSignupRqst;

	/**************************************************************************/

	public LeagueSignupPickLeaguePnl(LeagueSignupRqst signupRequest)
	{
		fLeagueSignupRqst = signupRequest;
	}

	/**************************************************************************/

	public void open()
	{
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(255,240);
		fInstrucLbl = new java.awt.Label("Please choose from one of the following:");
		fInstrucLbl.reshape(10,10,230,14);
		fInstrucLbl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fInstrucLbl);
		Group1 = new CheckboxGroup();
		fPublicLeagueChk = new java.awt.Checkbox("Join the next available public league", Group1, false);
		fPublicLeagueChk.reshape(10,40,235,21);
		fPublicLeagueChk.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fPublicLeagueChk);
		fNewLeagueChk = new java.awt.Checkbox("Create a new private league", Group1, false);
		fNewLeagueChk.reshape(10,70,235,21);
		fNewLeagueChk.setFont(new Font("Helvetica", Font.BOLD, 12));
		fNewLeagueChk.setForeground(new Color(0));
		add(fNewLeagueChk);
		fJoinLeagueChk = new java.awt.Checkbox("Join an exisiting private league", Group1, false);
		fJoinLeagueChk.reshape(10,100,235,21);
		fJoinLeagueChk.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fJoinLeagueChk);
		//}}
	}

	/**************************************************************************/

	protected void loadData()
	{
		if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_CreatePrivate)
			fNewLeagueChk.setState(true);
		else if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinPrivate)
			fJoinLeagueChk.setState(true);
		else //if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinOpenPublic)
			fPublicLeagueChk.setState(true);
	}

	/**************************************************************************/

	protected boolean unloadData(boolean validate)
	{
		if(fNewLeagueChk.getState())
			fLeagueSignupRqst.fLst = LeagueSignupRqst.lst_CreatePrivate;
		else if(fJoinLeagueChk.getState())
			fLeagueSignupRqst.fLst = LeagueSignupRqst.lst_JoinPrivate;
		else //if(fPublicLeagueChk.getState())
			fLeagueSignupRqst.fLst = LeagueSignupRqst.lst_JoinOpenPublic;

		return(true);
	}

	/**************************************************************************/

	protected String getInstructions()
	{
		return("Tips:\r\rPublic League:  For individuals not competing within their own select group.\r\rPrivate League:  For individuals who wish to compete within a select group.");
	}

}

/******************************************************************************/
/******************************************************************************/
