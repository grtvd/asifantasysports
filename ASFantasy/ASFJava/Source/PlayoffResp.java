/* PlayoffResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class PlayoffResp implements Streamable
{
	public PlayoffTeams fPlayoffTeams = new PlayoffTeams();
	public TeamInfoNameByIDVector fTeamInfoNameVector = new TeamInfoNameByIDVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fPlayoffTeams.readFromFiler(stream);

		// Read list of TeamInfoName
		fTeamInfoNameVector.readFromFiler(stream,new TeamInfoName(0).getClass());
	}                      
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
