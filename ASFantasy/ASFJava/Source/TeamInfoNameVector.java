/* TeamInfoNameVector.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class TeamInfoNameVector extends Vector
{
	public void readFromFiler(DataInputStream stream,Class elementClass)
		throws IOException
	{
		TeamInfoName team;

		short count;
		int i;

		try
		{
			removeAllElements();
		
			count = stream.readShort();
			for(i = 0; i < count; i++)
			{
				team = (TeamInfoName)elementClass.newInstance();
				team.readFromFiler(stream);

				addElement(team);
			}
		}
		catch(Exception e)
		{
			throw new IOException("TeamInfoNameVector.readFromFiler: proprogating: " + e.toString());
		}
	}

	/**************************************************************************/

	public int getPosByID(int teamID)
	{
		TeamInfoName teamSearch = new TeamInfoName(teamID);

		int pos = TAGVectorSearcher.sequentialSearch(this,teamSearch,
			TeamInfoNameByIDCmpr.getThe());

		return(pos);
	}

	/**************************************************************************/

	public TeamInfoName getByID(int teamID)
	{
		TeamInfoName teamSearch;

		int pos = getPosByID(teamID);

		if(pos != -1)
		{
			teamSearch = (TeamInfoName)(elementAt(pos));
			return(teamSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public void removeByID(int teamID)
	{
		TeamInfoName teamSearch = new TeamInfoName(teamID);

		int pos = TAGVectorSearcher.sequentialSearch(this,teamSearch,
			TeamInfoNameByIDCmpr.getThe());

		if(pos != -1)
			removeElementAt(pos);
	}
	
}              

/******************************************************************************/
/******************************************************************************/
 
