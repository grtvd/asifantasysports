/* LineupQueryRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class LineupQueryRqst implements Streamable
{
	String fEncodedParticID;
	int fShowTeamID;

	/**************************************************************************/

	public LineupQueryRqst(String encodedParticID,int showTeamID)
	{
		fEncodedParticID = encodedParticID;
		fShowTeamID = showTeamID;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fEncodedParticID = stream.readUTF();
		fShowTeamID = stream.readInt();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fEncodedParticID);
		stream.writeInt(fShowTeamID);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
