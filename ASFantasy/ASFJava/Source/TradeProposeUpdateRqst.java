/* TradeProposeUpdateRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TradeProposeUpdateRqst extends EncodedParticRqst
{
	int fTradeID;
	int fProposeToTeamID;
	PlayerIDVector fGetPlayerIDVector;
	PlayerIDVector fGivePlayerIDVector;
	PlayerIDVector fReleasePlayerIDVector;

	/**************************************************************************/

	public TradeProposeUpdateRqst(String encodedParticID,int tradeID,
		int proposeToTeamID,PlayerIDVector getPlayerIDVector,
		PlayerIDVector givePlayerIDVector,PlayerIDVector releasePlayerIDVector)
	{
		super(encodedParticID);
		fTradeID = tradeID;
		fProposeToTeamID = proposeToTeamID;
		fGetPlayerIDVector = getPlayerIDVector;
		fGivePlayerIDVector = givePlayerIDVector;
		fReleasePlayerIDVector = releasePlayerIDVector;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);
		fTradeID = stream.readInt();
		fProposeToTeamID = stream.readInt();
		fGetPlayerIDVector.readFromFiler(stream);
		fGivePlayerIDVector.readFromFiler(stream);
		fReleasePlayerIDVector.readFromFiler(stream);
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);
		stream.writeInt(fTradeID);
		stream.writeInt(fProposeToTeamID);
		fGetPlayerIDVector.writeToFiler(stream);
		fGivePlayerIDVector.writeToFiler(stream);
		fReleasePlayerIDVector.writeToFiler(stream);
	}

}

/******************************************************************************/
/******************************************************************************/
