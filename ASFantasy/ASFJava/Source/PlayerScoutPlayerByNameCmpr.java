/* PlayerScoutPlayerByNameCmpr.java */

/******************************************************************************/
/******************************************************************************/

class PlayerScoutPlayerByNameCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		PlayerScoutPlayer playerOne = (PlayerScoutPlayer)objectOne;
		PlayerScoutPlayer playerTwo = (PlayerScoutPlayer)objectTwo;

		return(TAGNativeCompare.compareString(playerOne.fName.fLastName,
			playerTwo.fName.fLastName));
	}
}

/******************************************************************************/
/******************************************************************************/

