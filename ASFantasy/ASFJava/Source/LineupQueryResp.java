/* LineupQueryResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class LineupQueryResp implements Streamable
{
	public TGameLevel fGameLevel = TGameLevel.gml_Undefined;
	public int fShowTeamID = 0;
	public TeamInfoNameVector fTeamInfoVector = new TeamInfoNameVector();
	public boolean fEnableChanges = false;
	public PlayerIDArray fPlayerIDArray = new PlayerIDArray();
	public PlayerInfoVector fLineupPlayerVector = new PlayerInfoVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fGameLevel = TGameLevel.convertFromByte(stream.readByte());
		fShowTeamID = stream.readInt();
		fTeamInfoVector.readFromFiler(stream,new TeamInfoName().getClass());
		fEnableChanges = stream.readBoolean();
		fPlayerIDArray.readFromFiler(stream);
		fLineupPlayerVector.readFromFiler(stream,new LineupPlayer().getClass());
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
