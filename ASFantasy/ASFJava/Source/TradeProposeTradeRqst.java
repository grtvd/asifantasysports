/* TradeProposeTeamRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TradeProposeTeamRqst extends EncodedParticRqst
{
	int fProposeToTeamID;

	/**************************************************************************/

	public TradeProposeTeamRqst(String encodedParticID,int proposeToTeamID)
	{
		super(encodedParticID);
		fProposeToTeamID = proposeToTeamID;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		super.readFromFiler(stream);
		fProposeToTeamID = stream.readInt();
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		super.writeToFiler(stream);
		stream.writeInt(fProposeToTeamID);
	}

}

/******************************************************************************/
/******************************************************************************/
