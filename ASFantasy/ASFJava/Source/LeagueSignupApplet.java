/* LeagueSignupApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.applet.*;
import java.lang.*;

/******************************************************************************/
/******************************************************************************/

public class LeagueSignupApplet extends ASFBaseApplet
{
	// Signup SubPanels
	private final static int sspUndefined = 0;
	private final static int sspPickLeague = 1;
	private final static int sspNewLeague = 2;
	private final static int sspJoinLeague = 3;
	private final static int sspVerifyData = 4;
	private final static int sspFailed = 5;
	private final static int sspComplete = 6;

	// Signup Data
	private LeagueSignupRqst fLeagueSignupRqst = new LeagueSignupRqst();
	private LeagueSignupResp fLeagueSignupResp;
	private String fSignupError = "";
	private boolean fSignupSuccessful = false;

	private LeagueSignupSubPnl fSubPnl;
	private int fCurSubPnl = sspUndefined;

	//{{DECLARE_CONTROLS
	symantec.itools.awt.BorderPanel fBorderPnl;
	symantec.itools.awt.BorderPanel fInstructionPnl;
	TAGMultiLineText fInstructionMLTxt;
	symantec.itools.awt.BorderPanel fSubPnlBorderPnl;
	java.awt.Button fPreviousBtn;
	java.awt.Button fNextBtn;
	//}}
	
	/**************************************************************************/

	public String getAppletName()
	{
		return("League Sign-Up");
	}

	/**************************************************************************/

	protected ASFantasyRequestor newFantasyRequestor(String hostName,
		int hostPortID,String requestDll,String encodedParticID)
	{
		return(new ASFantasyDraftRequestor(hostName,hostPortID,requestDll,
			encodedParticID));
	}

	/**************************************************************************/

	public void open()
	{
//BOB		super.openSubPanel();

		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(450,305);
		fBorderPnl = new symantec.itools.awt.BorderPanel();
		fBorderPnl.setLayout(null);
		fBorderPnl.reshape(0,0,450,305);
		fBorderPnl.setBackground(new Color(12632256));
		add(fBorderPnl);
		fBorderPnl.setAlignStyle(symantec.itools.awt.BorderPanel.ALIGN_LEFT);
		fBorderPnl.setPaddingTop(1);
		fBorderPnl.setPaddingBottom(1);
		fBorderPnl.setPaddingLeft(1);
		fBorderPnl.setPaddingRight(1);
		fBorderPnl.setIPadTop(1);
		fBorderPnl.setIPadBottom(1);
		fBorderPnl.setIPadSides(1);
		fBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fInstructionPnl = new symantec.itools.awt.BorderPanel();
		fInstructionPnl.setLayout(null);
		fInstructionPnl.reshape(13,13,159,244);
		fBorderPnl.add(fInstructionPnl);
		fInstructionPnl.setPaddingTop(1);
		fInstructionPnl.setPaddingBottom(1);
		fInstructionPnl.setPaddingLeft(1);
		fInstructionPnl.setPaddingRight(1);
		fInstructionPnl.setIPadTop(1);
		fInstructionPnl.setIPadBottom(1);
		fInstructionPnl.setIPadSides(1);
		fInstructionPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fInstructionMLTxt = new TAGMultiLineText();
		fInstructionMLTxt.reshape(7,7,140,230);
		fInstructionMLTxt.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fInstructionPnl.add(fInstructionMLTxt);
		fSubPnlBorderPnl = new symantec.itools.awt.BorderPanel();
		fSubPnlBorderPnl.setLayout(null);
		fSubPnlBorderPnl.reshape(178,13,259,244);
		fBorderPnl.add(fSubPnlBorderPnl);
		fSubPnlBorderPnl.setPaddingTop(1);
		fSubPnlBorderPnl.setPaddingBottom(1);
		fSubPnlBorderPnl.setPaddingLeft(1);
		fSubPnlBorderPnl.setPaddingRight(1);
		fSubPnlBorderPnl.setIPadTop(1);
		fSubPnlBorderPnl.setIPadBottom(1);
		fSubPnlBorderPnl.setIPadSides(1);
		fSubPnlBorderPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);
		fPreviousBtn = new java.awt.Button("Previous");
		fPreviousBtn.reshape(290,268,70,20);
		fPreviousBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fPreviousBtn);
		fNextBtn = new java.awt.Button("Next");
		fNextBtn.reshape(365,268,70,20);
		fNextBtn.setFont(new Font("Helvetica", Font.BOLD, 12));
		fBorderPnl.add(fNextBtn);
		//}}

		showSubPanel(true);
	}

	/**************************************************************************/

	public boolean handleEvent(Event event) {
		return super.handleEvent(event);
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fNextBtn)
			{
				if(fCurSubPnl == sspVerifyData)
					sendSignupRequest();

				if(fCurSubPnl != sspComplete)
					showSubPanel(true);
				else
					return false;
			}
			if(evt.target == fPreviousBtn)
			{
				showSubPanel(false);
			}
			/*
			else if(evt.target == fResetBtn)
			{
				fLeagueSignupRqst.clear();

				if(fSubPnl != null)
				{
					remove(fSubPnl);
					fSubPnl = null;
				}

				fCurSubPnl = sspUndefined;
				showSubPanel(true);
			}
			*/
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	private int determineNextSubPnl(int curSubPnl)
	{
		switch(curSubPnl)
		{
			case sspUndefined:
				return(sspPickLeague);
			case sspPickLeague:
				if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_CreatePrivate)
					return(sspNewLeague);

				if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinPrivate)
					return(sspJoinLeague);

				//if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinOpenPublic)
				return(sspVerifyData);
			case sspNewLeague:
				return(sspVerifyData);
			case sspJoinLeague:
				return(sspVerifyData);
			case sspVerifyData:
				if(fSignupSuccessful)
					return(sspComplete);
				return(sspFailed);
			default:
				throw new RuntimeException("LeagueSignupPnl.determineNextSubPnl: invalid curSubPnl(" +
					curSubPnl + ")");
		}
	}

	/**************************************************************************/

	private int determinePreviousSubPnl(int curSubPnl)
	{
		switch(curSubPnl)
		{
			//case sspPickLeague:
			case sspNewLeague:
				return(sspPickLeague);
			case sspJoinLeague:
				return(sspPickLeague);
			case sspVerifyData:
				if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_CreatePrivate)
					return(sspNewLeague);

				if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinPrivate)
					return(sspJoinLeague);

				//if(fLeagueSignupRqst.fLst == LeagueSignupRqst.lst_JoinOpenPublic)
				return(sspPickLeague);
			case sspFailed:
				return(sspVerifyData);
			default:
				throw new RuntimeException("LeagueSignupPnl.determineNextSubPnl: invalid curSubPnl(" +
					curSubPnl + ")");
		}
	}

	/**************************************************************************/

	private void showSubPanel(boolean nextPnl)
	{
		String textNext = "Next";
		boolean enableNext = true;
		boolean enablePrevious = true;
		boolean enableReset = true;

/*
		if(fSubPnl != null)
		{
			fSubPnlBorderPnl.remove(fSubPnl);
			fSubPnl = null;
		}
		else
		{
			fSubPnl = new LeagueSignupPickLeaguePnl();
			fSubPnl.setLayout(null);
			fSubPnl.move(2,2);
			fSubPnlBorderPnl.add(fSubPnl);
			fSubPnl.open();
		}
*/

		if(fSubPnl != null)
		{
			if(!fSubPnl.unloadData(nextPnl))
				return;

			fSubPnlBorderPnl.remove(fSubPnl);
			fSubPnl = null;
		}

		if(nextPnl)
			fCurSubPnl = determineNextSubPnl(fCurSubPnl);
		else
			fCurSubPnl = determinePreviousSubPnl(fCurSubPnl);

		switch(fCurSubPnl)
		{
			case sspPickLeague:
				fSubPnl = new LeagueSignupPickLeaguePnl(fLeagueSignupRqst);
				enablePrevious = false;
				break;
			case sspNewLeague:
				fSubPnl = new LeagueSignupNewLeaguePnl(fLeagueSignupRqst);
				break;
			case sspJoinLeague:
				fSubPnl = new LeagueSignupJoinLeaguePnl(fAppRequestor,fLeagueSignupRqst);
				break;
			case sspVerifyData:
				fSubPnl = new LeagueSignupVerifyPnl(fLeagueSignupRqst);
				textNext = "Sign Up";
				break;
			case sspFailed:
				fSubPnl = new LeagueSignupFailedPnl(fSignupError);
				enableNext = false;
				break;
			case sspComplete:
				fSubPnl = new LeagueSignupCompletePnl(fLeagueSignupRqst,fLeagueSignupResp);
				//textNext = "Picks";
				enablePrevious = false;
				enableNext = false;
				enableReset = false;
				break;

			default:
				//throw new RuntimeException("SignupPnl.showSubPanel: invalid ssp(" +
				//	ssp + ")");
				break;
		}

		if(fSubPnl != null)
		{
			fSubPnl.setLayout(null);
//			fSubPnl.reshape(2, 2, 255, 240);
			fSubPnl.move(2, 2);
			fSubPnlBorderPnl.add(fSubPnl);
   			fSubPnl.open();

			fInstructionMLTxt.setText(fSubPnl.getInstructions());
			fSubPnl.loadData();
		}

		fNextBtn.enable(enableNext);
		fNextBtn.setLabel(textNext);
		fPreviousBtn.enable(enablePrevious);
//		fResetBtn.enable(enableReset);
	}

	/**************************************************************************/

	private boolean sendSignupRequest()
	{
		fSignupSuccessful = false;
		fSignupError = "";

		fNextBtn.enable(false);
		fPreviousBtn.enable(false);
		try
		{
//BOB			TAGWaitUnknown.open(this,"Please wait...");

			fLeagueSignupRqst.fEncodedParticID = fAppRequestor.getEncodeParticID();
			fLeagueSignupResp =
				((ASFantasyDraftRequestor)fAppRequestor).leagueSignupRequest(
				fLeagueSignupRqst);
			if(fLeagueSignupResp != null)
			{
				if(fLeagueSignupResp.fSuccess)
				{
					fSignupSuccessful = true;
				}
				else
					fSignupError = fLeagueSignupResp.fReasonFailed;
			}
			else
				fSignupError = "Unknown";
		}
		catch(Throwable t)
		{
		}
		finally
		{
//BOB			TAGWaitUnknown.close();
		}

		fNextBtn.enable(true);
		fPreviousBtn.enable(true);
		return(fSignupSuccessful);
	}

}

/******************************************************************************/
/******************************************************************************/
