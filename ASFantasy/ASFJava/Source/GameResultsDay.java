/* GameResultsDay.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class GameResultsDay implements Streamable
{
	public String fGameDate = new String();
	public String fDescrip = new String();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fGameDate = stream.readUTF();
		fDescrip = stream.readUTF();
	}   
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fGameDate);
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
