/* GameResultsGame.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class GameResultsGame implements Streamable
{
	public int fHomeTeamID = 0;
	public String fDescrip = new String();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fHomeTeamID = stream.readInt();
		fDescrip = stream.readUTF();
	}   
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeInt(fHomeTeamID);
		stream.writeUTF(fDescrip);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
