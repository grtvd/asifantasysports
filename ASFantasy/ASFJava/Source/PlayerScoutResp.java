/* PlayerScoutResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class PlayerScoutResp implements Streamable
{
	public PlayerScoutPlayerVector fPlayerVector = null;
	public TeamInfoNameByIDVector fTeamInfoNameVector = null;

	/**************************************************************************/

	public PlayerScoutResp()
	{
		fPlayerVector = new PlayerScoutPlayerVector();
		fTeamInfoNameVector = new TeamInfoNameByIDVector();
	}

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		PlayerScoutPlayer player;

		short count;
		int i;

		// Read list of PlayerScoutPlayer
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			player = new PlayerScoutPlayer();
			player.readFromFiler(stream);

			fPlayerVector.addElement(player);
		}

		// Read list of TeamInfoName
		fTeamInfoNameVector.readFromFiler(stream,new TeamInfoName(0).getClass());
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
