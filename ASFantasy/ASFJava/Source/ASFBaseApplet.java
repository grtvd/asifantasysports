/* ASFBaseApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.applet.*;

/******************************************************************************/

public abstract class ASFBaseApplet extends Applet
{
	private String fErrorMsg;
	protected ASFantasyRequestor fAppRequestor;

	/**************************************************************************/

	public abstract String getAppletName();

	/**************************************************************************/

	public abstract void open() throws Exception;

	/**************************************************************************/

	public void init()
	{
		super.init();

		getGraphics().drawString("Loading Java Code, please wait...",10,25);

		try
		{
			String host = getParameter("Host");
			String requestDll = getParameter("RequestDll");
			String portIDParam = getParameter("PortID");
			int portID = 0;
			String encodedParticID = getParameter("User");

			if(host == null)
				host = getCodeBase().getHost();
			if(host == null)
				host = "localhost";

			if(portIDParam != null)
				portID = Integer.parseInt(portIDParam);

			fAppRequestor = newFantasyRequestor(host,portID,requestDll,
				encodedParticID);
			
			open();
		}
		catch(Throwable t)
		{
			removeAll();
			fErrorMsg = t.toString();
		}
	}

	/**************************************************************************/

	protected abstract ASFantasyRequestor newFantasyRequestor(String hostName,
		int hostPortID,String requestDll,String encodedParticID);

	/**************************************************************************/

	public void paint(Graphics g)
	{
		super.paint(g);

		if(fErrorMsg != null)
		{
			g.drawString(getAppletName() + " could not be opened due to an error.",10,25);
			g.drawString("Reason: " + fErrorMsg,10,50);
		}
	}

}

/******************************************************************************/
/******************************************************************************/
