/* TradeProposeQueryResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class TradeProposeQueryResp implements Streamable
{
	public TGameLevel fGameLevel = TGameLevel.gml_Undefined;

	public int fTradeID = 0;
	public boolean fEnableChanges = false;

	public int fTeamID = 0;
	public int fProposeToTeamID = 0;
	public PlayerIDVector fGetPlayerIDVector = new PlayerIDVector();
	public PlayerIDVector fGivePlayerIDVector = new PlayerIDVector();
	public PlayerIDVector fReleasePlayerIDVector = new PlayerIDVector();

	public TeamInfoNameVector fTeamInfoVector = new TeamInfoNameVector();
	public PlayerInfoVector fMyPlayerInfoVector = new PlayerInfoVector();
	public PlayerInfoVector fTheirPlayerInfoVector = new PlayerInfoVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fGameLevel = TGameLevel.convertFromByte(stream.readByte());

		fTradeID = stream.readInt();
		fEnableChanges = stream.readBoolean();

		fTeamID = stream.readInt();
		fProposeToTeamID = stream.readInt();
		fGetPlayerIDVector.readFromFiler(stream);
		fGivePlayerIDVector.readFromFiler(stream);
		fReleasePlayerIDVector.readFromFiler(stream);

		fTeamInfoVector.readFromFiler(stream,new TeamInfoName().getClass());
		fMyPlayerInfoVector.readFromFiler(stream,new PlayerInfoExt().getClass());
		fTheirPlayerInfoVector.readFromFiler(stream,new PlayerInfoExt().getClass());
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
