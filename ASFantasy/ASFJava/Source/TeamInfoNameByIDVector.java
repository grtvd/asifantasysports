/* TeamInfoNameByIDVector.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class TeamInfoNameByIDVector extends TeamInfoNameVector
{
	TeamInfoNameByIDCmpr fComparer = new TeamInfoNameByIDCmpr();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream,Class elementClass)
		throws IOException
	{
		super.readFromFiler(stream,elementClass);
		sort();
	}
	
	/**************************************************************************/
	
	public void sort()        
	{
		TAGVectorSorter.quickSort(this,fComparer);
	}

	/**************************************************************************/

	public TeamInfoName getByID(int teamID)
	{
		TeamInfoName teamInfoNameSearch = new TeamInfoName(teamID);
		int pos;

		pos = TAGVectorSearcher.binarySearch(this,teamInfoNameSearch,fComparer);

		if(pos != -1)
		{
			teamInfoNameSearch = (TeamInfoName)(elementAt(pos));
			return(teamInfoNameSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public void removeByID(int teamID)
	{
		TeamInfoName teamInfoNameSearch = new TeamInfoName(teamID);
		int pos;

		pos = TAGVectorSearcher.binarySearch(this,teamInfoNameSearch,fComparer);

		if(pos != -1)
			removeElementAt(pos);
	}
}              

/******************************************************************************/
/******************************************************************************/
 
