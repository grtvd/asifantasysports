/* PlayerScoutPlayer.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class PlayerScoutPlayer extends PlayerInfo
{
	String fRosterStatus = new String();
	String fInjuryStatus = new String();
	int fTeamID = 0;
	String fFreeAgentAvail = new String();

	Vector fPlayerStatValueVector = new Vector();

	/**************************************************************************/

	public String getStatus()
	{
		String str = new String();

		if((fRosterStatus != null) && (fRosterStatus.length() > 0))
		{
			str = fRosterStatus;
		}

		if((fInjuryStatus != null) && (fInjuryStatus.length() > 0))
		{
			if(str.length() != 0)
				str += "-";
			str += fInjuryStatus;
		}

		return(str);
	}

	/**************************************************************************/

	public boolean isFreeAgent()
	{
		return(fTeamID == 0);
	}

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		int i,numItems;

		super.readFromFiler(stream);

		fRosterStatus = stream.readUTF();
		fInjuryStatus = stream.readUTF();
		fTeamID = stream.readInt();
		fFreeAgentAvail = stream.readUTF();
		
		numItems = (int)stream.readByte();
		for(i = 0; i < numItems; i++)
			fPlayerStatValueVector.addElement(stream.readUTF());
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		int i,numItems;
		
		super.writeToFiler(stream);
		
		stream.writeUTF(fRosterStatus);
		stream.writeUTF(fInjuryStatus);
		stream.writeInt(fTeamID);
		stream.writeUTF(fFreeAgentAvail);
		
		numItems = (byte)fPlayerStatValueVector.size();
		stream.writeByte(numItems);
		for(i = 0; i < numItems; i++)
			stream.writeUTF((String)fPlayerStatValueVector.elementAt(i));
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
