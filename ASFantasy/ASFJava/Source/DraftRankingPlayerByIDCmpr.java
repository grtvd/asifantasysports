/* DraftRankingPlayerByIDCmpr.java */

/******************************************************************************/
/******************************************************************************/

class DraftRankingPlayerByIDCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		DraftRankingPlayer playerOne = (DraftRankingPlayer)objectOne;
		DraftRankingPlayer playerTwo = (DraftRankingPlayer)objectTwo;

		return(TAGNativeCompare.compareInt(playerOne.fPlayerID,
			playerTwo.fPlayerID));
	}
}

/******************************************************************************/
/******************************************************************************/

