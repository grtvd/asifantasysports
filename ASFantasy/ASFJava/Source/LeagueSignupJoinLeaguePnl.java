/* LeagueSignupJoinLeaguePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.util.*;

/******************************************************************************/

public class LeagueSignupJoinLeaguePnl extends LeagueSignupSubPnl
{
	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fCriteriaPnl;
	java.awt.Label fNameLbl;
	java.awt.TextField fNameEdt;
	java.awt.Button fLookupBtn;
	symantec.itools.awt.BorderPanel fFoundPnl;
	java.awt.List fList;
	java.awt.Label fPasswordLbl;
	java.awt.TextField fPasswordEdt;
	//}}
	
	private ASFantasyRequestor fAppRequestor;
	private LeagueSignupRqst fLeagueSignupRqst;

	private Vector fElementList = new Vector();

	/**************************************************************************/

	public LeagueSignupJoinLeaguePnl(ASFantasyRequestor appRequestor,
		LeagueSignupRqst leagueSignupRqst)
	{
		fAppRequestor = appRequestor;
		fLeagueSignupRqst = leagueSignupRqst;
	}

	/**************************************************************************/

	public void open()
	{
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(255,240);
		setFont(new Font("Helvetica", Font.BOLD, 12));
		setBackground(new Color(12632256));
		fCriteriaPnl = new symantec.itools.awt.BorderPanel();
		fCriteriaPnl.setLayout(null);
		fCriteriaPnl.reshape(10,10,235,50);
		fCriteriaPnl.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fCriteriaPnl);
		fCriteriaPnl.setLabel("Enter League Name");
		fCriteriaPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
		fCriteriaPnl.setPaddingTop(1);
		fCriteriaPnl.setPaddingBottom(1);
		fCriteriaPnl.setPaddingLeft(1);
		fCriteriaPnl.setPaddingRight(1);
		fCriteriaPnl.setIPadTop(1);
		fCriteriaPnl.setIPadBottom(1);
		fCriteriaPnl.setIPadSides(1);
		fCriteriaPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_LOWERED);
		fNameLbl = new java.awt.Label("Name");
		fNameLbl.reshape(10,4,40,14);
		fCriteriaPnl.add(fNameLbl);
		fNameEdt = new java.awt.TextField();
		fNameEdt.reshape(55,0,95,21);
		fNameEdt.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fCriteriaPnl.add(fNameEdt);
		fLookupBtn = new java.awt.Button("Lookup");
		fLookupBtn.reshape(165,0,60,20);
		fCriteriaPnl.add(fLookupBtn);
		fFoundPnl = new symantec.itools.awt.BorderPanel();
		fFoundPnl.setLayout(null);
		fFoundPnl.reshape(10,70,235,135);
		fFoundPnl.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fFoundPnl);
		fFoundPnl.setLabel("Leagues Found");
		fFoundPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
		fFoundPnl.setPaddingTop(1);
		fFoundPnl.setPaddingBottom(1);
		fFoundPnl.setPaddingLeft(1);
		fFoundPnl.setPaddingRight(1);
		fFoundPnl.setIPadTop(1);
		fFoundPnl.setIPadBottom(1);
		fFoundPnl.setIPadSides(1);
		fFoundPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_LOWERED);
		fList = new java.awt.List(6,false);
		fFoundPnl.add(fList);
		fList.reshape(10,10,215,100);
		fPasswordLbl = new java.awt.Label("League Password");
		fPasswordLbl.reshape(20,215,110,14);
		fPasswordLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		add(fPasswordLbl);
		fPasswordEdt = new java.awt.TextField();
		fPasswordEdt.reshape(135,211,91,21);
		fPasswordEdt.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fPasswordEdt);
		//}}
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fLookupBtn)
			{
				lookupLeagues();
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void loadData()
	{
		SignupLeagueListElement element;

		fElementList.removeAllElements();
		fList.clear();

		// If user has already selected the League, setup the lists.
		if(fLeagueSignupRqst.fLeagueID != 0)
		{
			element = new SignupLeagueListElement();
			element.fLeagueID = fLeagueSignupRqst.fLeagueID;
			element.fLeagueName = fLeagueSignupRqst.fLeagueName;
			fElementList.addElement(element);

			fList.addItem(fLeagueSignupRqst.fLeagueName);
			fList.select(0);
		}

		fPasswordEdt.setText(fLeagueSignupRqst.fLeaguePassword);
	}

	/**************************************************************************/

	protected boolean unloadData(boolean validate)
	{
		SignupLeagueListElement element;
		int listItem;

		listItem = fList.getSelectedIndex();
		if(validate && (listItem == -1))
		{
			//fList.requestFocus();
			if(fList.countItems() > 0)
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"Choose the league you would like to join by selecting it in the list box.");
			else
				MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"Enter the name (parital or full) of the league you would like to join and press [Lookup].");
			return(false);
		}

		if(listItem != -1)
		{
			element = (SignupLeagueListElement)fElementList.elementAt(listItem);
			fLeagueSignupRqst.fLeagueID = element.fLeagueID;
			fLeagueSignupRqst.fLeagueName = element.fLeagueName;
		}

		fLeagueSignupRqst.fLeaguePassword = fPasswordEdt.getText();
		if(validate && (fLeagueSignupRqst.fLeaguePassword.length() == 0))
		{
			//fPasswordEdt.requestFocus();
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"The League Password is required to join a private league.");
			return(false);
		}

		return(true);
	}

	/**************************************************************************/

	protected String getInstructions()
	{
		return("Enter the name of the league that you would like to join and press [Lookup].  If you don't know the complete name, enter the first few letters.\r\rThen select the league from the list.\r\rFinally, enter the league's password and press [Next].");
	}

	/**************************************************************************/

	private void lookupLeagues()
	{
		SignupLeagueListElement element;
		int i;
		int numItems;
		boolean success = false;

		String partialLeagueName;
		SignupLeagueListResp response;

		try
		{
//BOB			TAGWaitUnknown.open(this,"Please wait...");
			fLookupBtn.enable(false);

			partialLeagueName = fNameEdt.getText();
			response =
				((ASFantasyDraftRequestor)fAppRequestor).signupLeagueListRequest(
				partialLeagueName);

			if(response != null)
			{
				fElementList = response.fElementVector;

				fList.clear();
				while(fList.countItems() > 0)
					fList.delItem(0);

				numItems = fElementList.size();
				for(i = 0; i < numItems; i++)
				{
					element = (SignupLeagueListElement)fElementList.elementAt(i);

					fList.addItem(element.fLeagueName);
				}

				fList.select(0);
				fList.requestFocus();
				success = true;

				if(numItems == 0)
					MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"No leagues were found that match the specified criteria.");
			}
		}
		catch(Throwable t)
		{
		}
		finally
		{
//BOB			TAGWaitUnknown.close();
			fLookupBtn.enable(true);
		}

		if(!success)
			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,"An error has occurred.  Please try again later.");
	}

}

/******************************************************************************/
/******************************************************************************/
