/* TProfPlayerByIDVector.java */

/******************************************************************************/
/******************************************************************************/

import java.util.*;

/******************************************************************************/
/******************************************************************************/

class ProfPlayerByIDComparer implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		TProfPlayer profPlayerOne = (TProfPlayer)objectOne;
		TProfPlayer profPlayerTwo = (TProfPlayer)objectTwo;

		return(TAGNativeCompare.compareInt(profPlayerOne.fPlayerID,
			profPlayerTwo.fPlayerID));
	}
}

/******************************************************************************/

public class TProfPlayerByIDVector extends Vector
{
	ProfPlayerByIDComparer fComparer = new ProfPlayerByIDComparer();
	
	/**************************************************************************/
	
	public void sort()        
	{
		TAGVectorSorter.quickSort(this,fComparer);
	}

	/**************************************************************************/

	public TProfPlayer getByID(int playerID)
	{
		TProfPlayer profPlayerSearch = new TProfPlayer(playerID,new TFullName(),
			TPosition.pos_Undefined);
		int pos;

		pos = TAGVectorSearcher.binarySearch(this,profPlayerSearch,fComparer);

		if(pos != -1)
		{
			profPlayerSearch = (TProfPlayer)(elementAt(pos));
			return(profPlayerSearch);
		}

		return(null);
	}

	/**************************************************************************/

	public void removeByID(int playerID)
	{
		TProfPlayer profPlayerSearch = new TProfPlayer(playerID,new TFullName(),
			TPosition.pos_Undefined);
		int pos;

		pos = TAGVectorSearcher.binarySearch(this,profPlayerSearch,fComparer);

		if(pos != -1)
			removeElementAt(pos);
	}
}              

/******************************************************************************/
/******************************************************************************/
 
