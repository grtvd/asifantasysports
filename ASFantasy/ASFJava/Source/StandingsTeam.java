/* StandingsTeam.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class StandingsTeam extends TeamInfoName
{
	short fWins;
	short fLoses;
	short fTies;
	short fDivWins;
	short fDivLoses;
	short fDivTies;
	short fStreak;
	String fWinPercent;
	short fTotalPoints;

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);
	
		fWins = stream.readShort();
		fLoses = stream.readShort();
		fTies = stream.readShort();
		fDivWins = stream.readShort();
		fDivLoses = stream.readShort();
		fDivTies = stream.readShort();
		fStreak = stream.readShort();
		fWinPercent = stream.readUTF();
		fTotalPoints = stream.readShort();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeShort(fWins);
		stream.writeShort(fLoses);
		stream.writeShort(fTies);
		stream.writeShort(fDivWins);
		stream.writeShort(fDivLoses);
		stream.writeShort(fDivTies);
		stream.writeShort(fStreak);
		stream.writeUTF(fWinPercent);
		stream.writeShort(fTotalPoints);
	}                         

}              

/******************************************************************************/
/******************************************************************************/
 
