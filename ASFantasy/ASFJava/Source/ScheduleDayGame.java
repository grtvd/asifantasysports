/* ScheduleDayGame.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class ScheduleDayGame implements Streamable
{
	byte fProfGameWeek;
	boolean fGameIsScheduled;
	
	boolean fIsHome;
	boolean fDidWin;
	
	int fOppTeamID;

	short fWinningScore;
	short fLosingScore;

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fProfGameWeek = stream.readByte();
		fGameIsScheduled = stream.readBoolean();
	
		fIsHome = stream.readBoolean();
		fDidWin = stream.readBoolean();
	
		fOppTeamID = stream.readInt();

		fWinningScore = stream.readShort();
		fLosingScore = stream.readShort();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeByte(fProfGameWeek);
		stream.writeBoolean(fGameIsScheduled);
	
		stream.writeBoolean(fIsHome);
		stream.writeBoolean(fDidWin);
	
		stream.writeInt(fOppTeamID);

		stream.writeShort(fWinningScore);
		stream.writeShort(fLosingScore);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
