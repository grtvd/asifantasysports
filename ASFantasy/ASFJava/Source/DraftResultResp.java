/* DraftResultResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class DraftResultResp implements Streamable
{
	public Vector fPlayerVector = new Vector();
	public TeamInfoNameByIDVector fTeamInfoNameVector = new TeamInfoNameByIDVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		DraftResultPlayer player;
		TeamInfoName team;

		short count;
		int i;

		// Read list of DraftResultPlayer
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			player = new DraftResultPlayer();
			player.readFromFiler(stream);

			fPlayerVector.addElement(player);
		}

		// Read list of TeamInfoName
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			team = new TeamInfoName(0);
			team.readFromFiler(stream);

			fTeamInfoNameVector.addElement(team);
		}

		fTeamInfoNameVector.sort();
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
