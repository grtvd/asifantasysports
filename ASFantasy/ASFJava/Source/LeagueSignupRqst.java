/* LeagueSignupRqst.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class LeagueSignupRqst implements Streamable
{
	/* LeagueSignupType Values */
	static final public short lst_JoinOpenPublic = 0;
	static final public short lst_CreatePrivate = 1;
	static final public short lst_JoinPrivate = 2;
	
	/* LeagueSignupType */
	short fLst;

	/* Partic Info */
	String fEncodedParticID;
	
	/* League Info */
	int fLeagueID;
	String fLeagueName;		// not part of request, only used locally
	String fLeaguePassword;
	
	/**************************************************************************/

	public LeagueSignupRqst()
	{
		clear();
	}

	/**************************************************************************/

	public void clear()
	{
		fLst = lst_JoinOpenPublic;

		fEncodedParticID = null;
		
		fLeagueID = 0;
		fLeagueName = null;
		fLeaguePassword = null;
	}

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeShort(fLst);
		
		stream.writeUTF(fEncodedParticID);

		if(fLst == lst_CreatePrivate)
		{
			stream.writeUTF(fLeaguePassword);
		}
		else if(fLst == lst_JoinPrivate)
		{
			stream.writeInt(fLeagueID);
			stream.writeUTF(fLeaguePassword);
		}
		else if(fLst != lst_JoinOpenPublic)
			throw new RuntimeException("LeagueSignupRqst.WriteToFiler: bad fLst (" + fLst + ")");
	}                                   

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
