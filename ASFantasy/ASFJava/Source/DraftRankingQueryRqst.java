/* DraftRankingQueryRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class DraftRankingQueryRqst implements Streamable
{
	String fEncodedParticID;

	/**************************************************************************/

	public DraftRankingQueryRqst(String encodedParticID)
	{
		fEncodedParticID = encodedParticID;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fEncodedParticID = stream.readUTF();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fEncodedParticID);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
