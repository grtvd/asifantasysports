/* PlayerInfo.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class PlayerInfo implements Streamable
{
	int fPlayerID = 0;
	TFullName fName = new TFullName();
	String fProfTeamAbbr = new String();
	TPosition fPosition = TPosition.pos_Undefined;

	/**************************************************************************/

	public void clear()
	{
		fPlayerID = 0;
		fName.clear();
		fProfTeamAbbr = new String();
		fPosition = TPosition.pos_Undefined;
	}
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fPlayerID = stream.readInt();
		fName.readFromFiler(stream);
		fProfTeamAbbr = stream.readUTF();
		fPosition = TPosition.readFromFiler(stream);
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeInt(fPlayerID);
		fName.writeToFiler(stream);
		stream.writeUTF(fProfTeamAbbr);
		fPosition.writeToFiler(stream); 
	}                         

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}              

/******************************************************************************/
/******************************************************************************/
