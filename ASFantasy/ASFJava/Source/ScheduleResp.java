/* ScheduleResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class ScheduleResp implements Streamable
{
	public Vector fGameVector = new Vector();
	public TeamInfoNameByIDVector fTeamInfoNameVector = new TeamInfoNameByIDVector();

	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		ScheduleDayGame game;

		short count;
		int i;

		// Read list of ScheduleDayGame
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			game = new ScheduleDayGame();
			game.readFromFiler(stream);

			fGameVector.addElement(game);
		}

		// Read list of TeamInfoName
		fTeamInfoNameVector.readFromFiler(stream,new TeamInfoName(0).getClass());
		/*
		TeamInfoName team;
		count = stream.readShort();
		for(i = 0; i < count; i++)
		{
			team = new TeamInfoName(0);
			team.readFromFiler(stream);

			fTeamInfoNameVector.addElement(team);
		}

		fTeamInfoNameVector.sort();
		*/
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
