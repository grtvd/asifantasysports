/* PlayerIDVector.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class PlayerIDVector extends Vector
{
	TAGIntegerComparer fIDComparer = new TAGIntegerComparer();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		Integer playerID;
		short count;
		int i;

		removeAllElements();
		
		// Read list of PlayerID
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			playerID = new Integer(stream.readInt());
			addElement(playerID);
		}
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		Integer playerID;
		int count;
		int i;

		// Write list of PlayerID
		count = size();
		stream.writeShort(count);
		for(i = 0; i < count; i++)
		{
			playerID = (Integer)elementAt(i);
			stream.writeInt(playerID.intValue());
		}
	}                         

	/**************************************************************************/
	
	public boolean doesContainDups(boolean ignoreZeroIDs)
	{
		int i,j,numItems = size();

		for(i = 0; i < numItems; i++)
			for(j = i + 1; j < numItems; j++)
			{
				if(((Integer)elementAt(i)).intValue() ==
					((Integer)elementAt(j)).intValue())
				{
					if(((Integer)elementAt(i)).intValue() == 0)
					{
						if(!ignoreZeroIDs)
							return(true);
					}
					else
						return(true);
				}
			}

		return(false);
	}
	
	/**************************************************************************/

	// Does 'this' contain any of same IDs as in playerIDVector?

	public boolean containsAny(PlayerIDVector playerIDVector,boolean skipZeroIDs)
	{
		int i,j;
		int thisItems = size();
		int thatItems = playerIDVector.size();

		for(i = 0; i < thisItems; i++)
			for(j = 0; j < thatItems; j++)
			{
				if(((Integer)elementAt(i)).intValue() ==
					((Integer)playerIDVector.elementAt(j)).intValue())
				{
					if(((Integer)elementAt(i)).intValue() == 0)
					{
						if(!skipZeroIDs)
							return(true);
					}
					else
						return(true);
				}
			}

		return(false);
	}


	/**************************************************************************/

	public Integer getByID(int playerID)
	{
		Integer playerIDSearch = new Integer(playerID);
		int pos;

		pos = TAGVectorSearcher.sequentialSearch(this,playerIDSearch,fIDComparer);

		if(pos != -1)
		{
			playerIDSearch = (Integer)(elementAt(pos));
			return(playerIDSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public void removeByID(int playerID)
	{
		Integer playerIDSearch = new Integer(playerID);
		int pos;

		pos = TAGVectorSearcher.sequentialSearch(this,playerIDSearch,fIDComparer);

		if(pos != -1)
			removeElementAt(pos);
	}
}              

/******************************************************************************/
/******************************************************************************/
 
