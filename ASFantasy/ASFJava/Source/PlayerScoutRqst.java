/* PlayerScoutRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class PlayerScoutRqst implements Streamable
{
	public final static short maxSelectNumPlayers = 250;

	String fEncodedParticID = new String();
	
	String fPartialPlayerLastName = new String();	// Include by Partial Last Name
	String fProfTeamAbbr = new String();			// Include Prof Team
	Vector fPositionVector = new Vector();			// Include Positions
	
	Vector fStatVector = new Vector();				// Return stats
	short fSelectNumPlayers = (short)25;			// Number of players to return.
	byte fSelectByStat = (byte)0;					// Offset into fStatVector, top
													//	fSelectNumPlayers by fStatVector stat.
	boolean fSelectByStatAsc = false;				// Ascending or Descending

	boolean fIsFreeAgentRequest = false;			// Is this a draft or free agent request?
	boolean fShowRanked = false;					// Show Players already ranked (Draft)
	boolean fShowDrafted = false;					// Show Players already drafted (Draft)
	boolean fShowMyTeamPlayers = false;				// Show Players on my Team (Free Agent)
	boolean fShowOtherTeamsPlayers = false;			// Show Players on other Teams in League (Free Agent)
	
	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		TPosition position;
		PlayerScoutStat stat;
		int count;
		int i;
		
		stream.writeUTF(fEncodedParticID);
		
		stream.writeUTF(fPartialPlayerLastName);
		stream.writeUTF(fProfTeamAbbr);

		// Write list of Positions
		count = fPositionVector.size();
		stream.writeByte(count);
		for(i = 0; i < count; i++)
		{
			position = (TPosition)fPositionVector.elementAt(i);
			position.writeToFiler(stream);
		}

		// Write list of Stats to return
		count = fStatVector.size();
		stream.writeByte(count);
		for(i = 0; i < count; i++)
		{
			stat = (PlayerScoutStat)fStatVector.elementAt(i);
			stat.writeToFiler(stream);
		}
		
		stream.writeShort(fSelectNumPlayers);
		stream.writeByte(fSelectByStat);
		stream.writeByte(fSelectByStatAsc ? (byte)1 : (byte)0);
		stream.writeByte(fIsFreeAgentRequest ? (byte)1 : (byte)0);
		stream.writeByte(fShowRanked ? (byte)1 : (byte)0);
		stream.writeByte(fShowDrafted ? (byte)1 : (byte)0);
		stream.writeByte(fShowMyTeamPlayers ? (byte)1 : (byte)0);
		stream.writeByte(fShowOtherTeamsPlayers ? (byte)1 : (byte)0);
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
