/* SignupLeagueListRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class SignupLeagueListRqst implements Streamable
{
	String fPartialLeagueName;

	/**************************************************************************/

	public SignupLeagueListRqst(String partialLeagueName)
	{
		fPartialLeagueName = partialLeagueName;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fPartialLeagueName = stream.readUTF();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeUTF(fPartialLeagueName);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
