/* TradeProposeTeamResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class TradeProposeTeamResp implements Streamable
{
	public PlayerInfoVector fPlayerInfoVector = new PlayerInfoVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fPlayerInfoVector.readFromFiler(stream,new PlayerInfoExt().getClass());
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
