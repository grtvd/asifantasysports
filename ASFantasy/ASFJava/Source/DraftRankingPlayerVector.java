/* DraftRankingPlayerVector.java */

/******************************************************************************/
/******************************************************************************/

import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class DraftRankingPlayerVector extends Vector
{
	DraftRankingPlayerByIDCmpr fIDComparer = new DraftRankingPlayerByIDCmpr();
	
	/**************************************************************************/
	/*
	
	public void sort(TAGComparer comparer)        
	{
		TAGVectorSorter.quickSort(this,comparer);
	}

	*/
	/**************************************************************************/

	public DraftRankingPlayer getByID(int playerID)
	{
		DraftRankingPlayer playerSearch = new DraftRankingPlayer();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		if(pos != -1)
		{
			playerSearch = (DraftRankingPlayer)(elementAt(pos));
			return(playerSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public int getPosByID(int playerID)
	{
		DraftRankingPlayer playerSearch = new DraftRankingPlayer();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		return(pos);
	}

	/**************************************************************************/

	public void removeByID(int playerID)
	{
		DraftRankingPlayer playerSearch = new DraftRankingPlayer();
		int pos;

		playerSearch.fPlayerID = playerID;
		pos = TAGVectorSearcher.sequentialSearch(this,playerSearch,fIDComparer);

		if(pos != -1)
			removeElementAt(pos);
	}
}              

/******************************************************************************/
/******************************************************************************/
 
