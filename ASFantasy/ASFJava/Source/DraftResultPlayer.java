/* DraftResultPlayer.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class DraftResultPlayer implements Streamable
{
	byte fRound;
	byte fPick;
	TFullName fName = new TFullName();
	TPosition fPosition = TPosition.pos_Undefined;
	int fTeamID;
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fRound = stream.readByte();
		fPick = stream.readByte();
		fName.readFromFiler(stream);
		fPosition = TPosition.readFromFiler(stream);
		fTeamID = stream.readInt();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeByte(fRound);
		stream.writeByte(fPick);
		fName.writeToFiler(stream);
		fPosition.writeToFiler(stream);
		stream.writeInt(fTeamID);
	}                         

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}              

/******************************************************************************/
/******************************************************************************/
