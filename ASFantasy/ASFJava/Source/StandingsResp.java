/* StandingsResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class StandingsResp implements Streamable
{
	public TeamInfoNameVector fEastTeamVector = new TeamInfoNameVector();
	public TeamInfoNameVector fWestTeamVector = new TeamInfoNameVector();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		Class teamClass = new StandingsTeam().getClass();
		
		fEastTeamVector.readFromFiler(stream,teamClass);
		fWestTeamVector.readFromFiler(stream,teamClass);
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
