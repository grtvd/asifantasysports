/* PlayerIDArray.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class PlayerIDArray extends Vector
{
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		PlayerIDVector playerIDVector;
		short count;
		int i;

		removeAllElements();
		
		// Read list of PlayerID
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			playerIDVector = new PlayerIDVector();
			playerIDVector.readFromFiler(stream);
			addElement(playerIDVector);
		}
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		PlayerIDVector playerIDVector;
		int count;
		int i;

		// Write list of PlayerID
		count = size();
		stream.writeShort(count);
		for(i = 0; i < count; i++)
		{
			playerIDVector = (PlayerIDVector)elementAt(i);
			playerIDVector.writeToFiler(stream);
		}
	}

}

/******************************************************************************/
/******************************************************************************/
