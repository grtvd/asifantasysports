/* DraftRankingUpdateRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class DraftRankingUpdateRqst implements Streamable
{
	String fEncodedParticID;
	DraftRankingPlayerVector fPlayerVector;

	/**************************************************************************/

	public DraftRankingUpdateRqst(String encodedParticID,
		DraftRankingPlayerVector playerVector)
	{
		fEncodedParticID = encodedParticID;
		fPlayerVector = playerVector;
	}     

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		DraftRankingPlayer player;
		int count;
		int i;

		stream.writeUTF(fEncodedParticID);

		// Write list of DraftRankingPlayer
		count = fPlayerVector.size();
		stream.writeShort(count);
		for(i = 0; i < count; i++)
		{
			player = (DraftRankingPlayer)fPlayerVector.elementAt(i);
			stream.writeInt(player.fPlayerID);
		}
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
