/* GameResultsRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class GameResultsRqst extends EncodedParticRqst
{
	String fGameDate;
	int fHomeTeamID;

	public GameResultsRqst(String encodedParticID,String gameDate,int homeTeamID)
	{
		super(encodedParticID);

		fGameDate = gameDate;
		fHomeTeamID = homeTeamID;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);

		fGameDate = stream.readUTF();
		fHomeTeamID = stream.readInt();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);

		stream.writeUTF(fGameDate);
		stream.writeInt(fHomeTeamID);
	}

}

/******************************************************************************/
/******************************************************************************/
