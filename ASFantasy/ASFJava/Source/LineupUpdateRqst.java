/* LineupUpdateRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class LineupUpdateRqst implements Streamable
{
	String fEncodedParticID;
	PlayerIDArray fPlayerIDArray;

	/**************************************************************************/

	public LineupUpdateRqst(String encodedParticID,
		PlayerIDArray playerIDArray)
	{
		fEncodedParticID = encodedParticID;
		fPlayerIDArray = playerIDArray;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fEncodedParticID);
		fPlayerIDArray.writeToFiler(stream);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
