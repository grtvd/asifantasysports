/* FreeAgentUpdateRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class FreeAgentUpdateRqst implements Streamable
{
	String fEncodedParticID;
	int fClaimPlayerID;
	int fReleasePlayerID;

	/**************************************************************************/

	public FreeAgentUpdateRqst(String encodedParticID,int claimPlayerID,
		int releasePlayerID)
	{
		fEncodedParticID = encodedParticID;
		fClaimPlayerID = claimPlayerID;
		fReleasePlayerID = releasePlayerID;
	}     

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fEncodedParticID);
		stream.writeInt(fClaimPlayerID);
		stream.writeInt(fReleasePlayerID);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
