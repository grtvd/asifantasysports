/* LeagueSignupResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class LeagueSignupResp implements Streamable
{
	public boolean fSuccess;
	public String fLeagueName;
	public String fReasonFailed;

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fSuccess = stream.readBoolean();
		fLeagueName = stream.readUTF();
		fReasonFailed = stream.readUTF();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
