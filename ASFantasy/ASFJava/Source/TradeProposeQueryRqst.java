/* TradeProposeQueryRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TradeProposeQueryRqst extends EncodedParticRqst
{
	int fTradeID;

	public TradeProposeQueryRqst(String encodedParticID,int tradeID)
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

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}

}

/******************************************************************************/
/******************************************************************************/
