/* PlayoffTeams.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class PlayoffTeams implements Streamable
{
	// Semi-Finals Game 1
	int fEastWinnerTeamID;
	byte fEastWinnerScore;
	int fWestWildCardTeamID;
	byte fWestWildCardScore;

	// Semi-Finals Game 2
	int fWestWinnerTeamID;
	byte fWestWinnerScore;
	int fEastWildCardTeamID;
	byte fEastWildCardScore;

	// Finals Game
	int fFinalistOneTeamID;
	byte fFinalistOneScore;
	int fFinalistTwoTeamID;
	byte fFinalistTwoScore;

	// League Champ
	int fLeagueChampTeamID;

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		// Semi-Finals Game 1
		fEastWinnerTeamID = stream.readInt();
		fEastWinnerScore = stream.readByte();
		fWestWildCardTeamID = stream.readInt();
		fWestWildCardScore = stream.readByte();

		// Semi-Finals Game 2
		fWestWinnerTeamID = stream.readInt();
		fWestWinnerScore = stream.readByte();
		fEastWildCardTeamID = stream.readInt();
		fEastWildCardScore = stream.readByte();

		// Finals Game
		fFinalistOneTeamID = stream.readInt();
		fFinalistOneScore = stream.readByte();
		fFinalistTwoTeamID = stream.readInt();
		fFinalistTwoScore = stream.readByte();

		// League Champ
		fLeagueChampTeamID = stream.readInt();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		// Semi-Finals Game 1
		stream.writeByte(fEastWinnerTeamID);
		stream.writeByte(fEastWinnerScore);
		stream.writeByte(fWestWildCardTeamID);
		stream.writeByte(fWestWildCardScore);

		// Semi-Finals Game 2
		stream.writeByte(fWestWinnerTeamID);
		stream.writeByte(fWestWinnerScore);
		stream.writeByte(fEastWildCardTeamID);
		stream.writeByte(fEastWildCardScore);

		// Finals Game
		stream.writeByte(fFinalistOneTeamID);
		stream.writeByte(fFinalistOneScore);
		stream.writeByte(fFinalistTwoTeamID);
		stream.writeByte(fFinalistTwoScore);

		// League Champ
		stream.writeByte(fLeagueChampTeamID);
	}                         

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}              

/******************************************************************************/
/******************************************************************************/
