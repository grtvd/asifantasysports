/* LineupPlayer.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class LineupPlayer extends ASFantasyLineupPlayer
{
	String fOppProfTeamGame = new String();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);

		fOppProfTeamGame = stream.readUTF();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);
		
		stream.writeUTF(fOppProfTeamGame);
	}
}

/******************************************************************************/
/******************************************************************************/
