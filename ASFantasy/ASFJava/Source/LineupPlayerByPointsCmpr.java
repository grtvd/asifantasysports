/* LineupPlayerByPointsCmpr.java */

/******************************************************************************/
/******************************************************************************/

class LineupPlayerByPointsCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		LineupPlayer playerOne = (LineupPlayer)objectOne;
		LineupPlayer playerTwo = (LineupPlayer)objectTwo;
		int rc;

		// Total Points - Descending
		rc = TAGNativeCompare.compareInt(playerTwo.fTotalPoints,
			playerOne.fTotalPoints);
		if(rc != 0)
			return(rc);
			
		// LastWeeksPoints - Descending
		rc = TAGNativeCompare.compareInt(playerTwo.fLastWeeksPoints,
			playerOne.fLastWeeksPoints);
		if(rc != 0)
			return(rc);

		return(playerOne.fName.compare(playerTwo.fName));
	}
}

/******************************************************************************/
/******************************************************************************/

