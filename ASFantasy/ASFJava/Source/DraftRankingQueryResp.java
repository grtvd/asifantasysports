/* DraftRankingQueryResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class DraftRankingQueryResp implements Streamable
{
	public TGameLevel fGameLevel = TGameLevel.gml_Undefined;
	public DraftRankingPlayerVector fPlayerVector = new DraftRankingPlayerVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		DraftRankingPlayer player;

		short count;
		int i;

		fGameLevel = TGameLevel.convertFromByte(stream.readByte());

		// Read list of DraftRankingPlayer
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			player = new DraftRankingPlayer();
			player.readFromFiler(stream);

			fPlayerVector.addElement(player);
		}

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
