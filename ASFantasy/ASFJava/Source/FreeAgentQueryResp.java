/* FreeAgentQueryResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class FreeAgentQueryResp implements Streamable
{
	public TGameLevel fGameLevel = TGameLevel.gml_Undefined;

	public PlayerInfo fClaimPlayer = new PlayerInfo();
	public int fReleasePlayerID = 0;
	
	public PlayerInfoVector fRosterPlayerVector = new PlayerInfoVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fGameLevel = TGameLevel.convertFromByte(stream.readByte());

		fClaimPlayer.readFromFiler(stream);
		fReleasePlayerID = stream.readInt();

		fRosterPlayerVector.readFromFiler(stream,new PlayerInfo().getClass());
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
