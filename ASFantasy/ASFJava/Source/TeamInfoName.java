/* TeamInfoName.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

class TeamInfoName implements Streamable
{
	int fTeamID;
	String fRegionName;
	String fTeamName;

	/**************************************************************************/

	public TeamInfoName(int teamID,String regionName,String teamName)
	{
		fTeamID = teamID;
		fRegionName = regionName;
		fTeamName = teamName;
	}
	
	/**************************************************************************/

	public TeamInfoName(int teamID)
	{
		this(teamID,new String(),new String());
	}
	
	/**************************************************************************/

	public TeamInfoName()
	{
		this(0,new String(),new String());
	}
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fTeamID = stream.readInt();
		fRegionName = stream.readUTF();
		fTeamName = stream.readUTF();
	}

	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeInt(fTeamID);
		stream.writeUTF(fRegionName);
		stream.writeUTF(fTeamName);
	}                         

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
	
	/**************************************************************************/

	public String buildName()
	{
		String str = new String();

		if((fRegionName != null) && (fRegionName.length() > 0))
			str = fRegionName;
		if((fTeamName != null) && (fTeamName.length() > 0))
		{
			if(str.length() != 0)
				str += " ";
			str += fTeamName;
		}

		return(str);
	}        
			  
}              

/******************************************************************************/
/******************************************************************************/
 
