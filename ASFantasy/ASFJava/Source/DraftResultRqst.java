/* DraftResultRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class DraftResultRqst implements Streamable
{
	String fEncodedParticID;

	/**************************************************************************/

	public DraftResultRqst(String encodedParticID)
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
