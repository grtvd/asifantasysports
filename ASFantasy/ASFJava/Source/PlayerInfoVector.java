/* PlayerInfoVector.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class PlayerInfoVector extends Vector
{
	PlayerInfoByIDCmpr fIDComparer = new PlayerInfoByIDCmpr();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream,Class elementClass)
		throws IOException
	{
		PlayerInfo player;
		short count;
		int i;

		try
		{
			removeAllElements();
		
			// Read list of PlayerInfo
			count = stream.readShort();
			for(i = 0; i < count; i++)
			{
				player = (PlayerInfo)elementClass.newInstance();
				player.readFromFiler(stream);

				addElement(player);
			}
		}
		catch(Exception e)
		{
			throw new IOException("PlayerInfoVector.readFromFiler: proprogating: " + e.toString());
		}
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		PlayerInfo player;
		int count;
		int i;

		// Write list of PlayerInfo
		count = size();
		stream.writeShort(count);
		for(i = 0; i < count; i++)
		{
			player = (PlayerInfo)elementAt(i);
			player.writeToFiler(stream);
		}
	}                         
	
	/**************************************************************************/

	public PlayerInfo getByID(int playerID)
	{
		PlayerInfo playerSearch = new PlayerInfo();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		if(pos != -1)
		{
			playerSearch = (PlayerInfo)(elementAt(pos));
			return(playerSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public void removeByID(int playerID)
	{
		PlayerInfo playerSearch = new PlayerInfo();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		if(pos != -1)
			removeElementAt(pos);
	}
}              

/******************************************************************************/
/******************************************************************************/
 
