/* GameResultsPlayer.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class GameResultsPlayer extends PlayerInfo
{
	public short fTotalPoints;

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);

		fTotalPoints = stream.readShort();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);

		stream.writeShort(fTotalPoints);
	}                         

}              

/******************************************************************************/
/******************************************************************************/
