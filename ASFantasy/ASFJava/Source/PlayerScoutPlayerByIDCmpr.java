/* PlayerScoutPlayerByIDCmpr.java */

/******************************************************************************/
/******************************************************************************/

class PlayerScoutPlayerByIDCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		PlayerScoutPlayer playerOne = (PlayerScoutPlayer)objectOne;
		PlayerScoutPlayer playerTwo = (PlayerScoutPlayer)objectTwo;

		return(TAGNativeCompare.compareInt(playerOne.fPlayerID,
			playerTwo.fPlayerID));
	}
}

/******************************************************************************/
/******************************************************************************/

