/* PlayerInfoExt.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class PlayerInfoExt extends PlayerInfo
{
	short fTotalPoints;
	short fLastWeeksPoints;
	
	String fRosterStatus;
	String fInjuryStatus;

	/**************************************************************************/

	public void clear()
	{
		fTotalPoints = 0;
		fLastWeeksPoints = 0;

		fRosterStatus = new String();
		fInjuryStatus = new String();
	}

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
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);

		fTotalPoints = stream.readShort();
		fLastWeeksPoints = stream.readShort();
	
		fRosterStatus = stream.readUTF();
		fInjuryStatus = stream.readUTF();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);

		stream.writeShort(fTotalPoints);
		stream.writeShort(fLastWeeksPoints);
	
		stream.writeUTF(fRosterStatus);
		stream.writeUTF(fInjuryStatus);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
