/* PlayerScoutPlayerVector.java */

/******************************************************************************/
/******************************************************************************/

import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class PlayerScoutPlayerVector extends Vector
{
	PlayerScoutPlayerByIDCmpr fIDComparer = new PlayerScoutPlayerByIDCmpr();
	
	/**************************************************************************/
	
	public void sort(TAGComparer comparer)        
	{
		TAGVectorSorter.quickSort(this,comparer);
	}

	/**************************************************************************/

	public PlayerScoutPlayer getByID(int playerID)
	{
		PlayerScoutPlayer playerSearch = new PlayerScoutPlayer();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		if(pos != -1)
		{
			playerSearch = (PlayerScoutPlayer)(elementAt(pos));
			return(playerSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public void removeByID(int playerID)
	{
		PlayerScoutPlayer playerSearch = new PlayerScoutPlayer();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		if(pos != -1)
			removeElementAt(pos);
	}
}              

/******************************************************************************/
/******************************************************************************/
 
