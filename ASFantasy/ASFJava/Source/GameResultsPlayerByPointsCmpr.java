/* GameResultsPlayerByPointsCmpr.java */

/******************************************************************************/
/******************************************************************************/

class GameResultsPlayerByPointsCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		GameResultsPlayer playerOne = (GameResultsPlayer)objectOne;
		GameResultsPlayer playerTwo = (GameResultsPlayer)objectTwo;
		int rc;

		// Total Points - Descending
		rc = TAGNativeCompare.compareInt(playerTwo.fTotalPoints,
			playerOne.fTotalPoints);
		if(rc != 0)
			return(rc);

		return(playerOne.fName.compare(playerTwo.fName));
	}
}

/******************************************************************************/
/******************************************************************************/

