/* PlayerInfoByIDCmpr.java */

/******************************************************************************/
/******************************************************************************/

class PlayerInfoByIDCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		PlayerInfo playerOne = (PlayerInfo)objectOne;
		PlayerInfo playerTwo = (PlayerInfo)objectTwo;

		return(TAGNativeCompare.compareInt(playerOne.fPlayerID,
			playerTwo.fPlayerID));
	}
}

/******************************************************************************/
/******************************************************************************/

