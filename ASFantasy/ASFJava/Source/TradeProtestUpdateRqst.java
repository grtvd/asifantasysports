/* TradeProtestUpdateRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TradeProtestUpdateRqst extends EncodedParticRqst
{
	int fTradeID;

	/**************************************************************************/

	public TradeProtestUpdateRqst(String encodedParticID,int tradeID)
	{
		super(encodedParticID);
		fTradeID = tradeID;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);
		fTradeID = stream.readInt();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);
		stream.writeInt(fTradeID);
	}

}

/******************************************************************************/
/******************************************************************************/
