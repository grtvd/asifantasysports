/* SignupLeagueListElement.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class SignupLeagueListElement implements Streamable
{
	int fLeagueID;
	String fLeagueName = "";
	String fCommisName = "";

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fLeagueID = stream.readInt();
		fLeagueName = stream.readUTF();
		fCommisName = stream.readUTF();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeInt(fLeagueID);
		stream.writeUTF(fLeagueName);
		stream.writeUTF(fCommisName);
	}                         

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}              

/******************************************************************************/
/******************************************************************************/
