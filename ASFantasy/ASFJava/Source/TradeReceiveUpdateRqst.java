/* TradeReceiveUpdateRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TradeReceiveUpdateRqst extends EncodedParticRqst
{
	int fTradeID;
	boolean fAccept;
	PlayerIDVector fReleasePlayerIDVector;

	/**************************************************************************/

	public TradeReceiveUpdateRqst(String encodedParticID,int tradeID,
		boolean accept,PlayerIDVector releasePlayerIDVector)
	{
		super(encodedParticID);
		fTradeID = tradeID;
		fAccept = accept;
		fReleasePlayerIDVector = releasePlayerIDVector;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);
		fTradeID = stream.readInt();
		fAccept = stream.readBoolean();
		fReleasePlayerIDVector.readFromFiler(stream);
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);
		stream.writeInt(fTradeID);
		stream.writeBoolean(fAccept);
		fReleasePlayerIDVector.writeToFiler(stream);
	}

}

/******************************************************************************/
/******************************************************************************/
