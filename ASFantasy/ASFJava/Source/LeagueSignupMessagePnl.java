/* LeagueSignupMessagePnl.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;

/******************************************************************************/

public class LeagueSignupMessagePnl extends LeagueSignupSubPnl
{
	//{{DECLARE_CONTROLS
	TAGMultiLineText fMessageMLTxt;
	//}}
	
	private String fMessage;
	private String fInstructions;

	/**************************************************************************/

	public LeagueSignupMessagePnl(String message,String instructions)
	{
		fMessage = message;
		fInstructions = instructions;
	}

	/**************************************************************************/

	public LeagueSignupMessagePnl(String message)
	{
		this(message,null);
	}

	/**************************************************************************/

	public void open()
	{
		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(255,240);
		setFont(new Font("Dialog", Font.BOLD, 12));
		fMessageMLTxt = new TAGMultiLineText();
		fMessageMLTxt.reshape(10,10,235,220);
		fMessageMLTxt.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fMessageMLTxt);
		//}}
	}

	/**************************************************************************/

	public void setMessage(String message)
	{
		fMessage = message;
		if(fMessageMLTxt != null)	// has open been called yet?
			loadData();
	}

	/**************************************************************************/

	protected void loadData()
	{
		fMessageMLTxt.setText(fMessage);
	}

	/**************************************************************************/

	protected boolean unloadData(boolean validate)
	{
		return(true);
	}

	/**************************************************************************/

	protected String getInstructions()
	{
		return(fInstructions);
	}

}

/******************************************************************************/
/******************************************************************************/
