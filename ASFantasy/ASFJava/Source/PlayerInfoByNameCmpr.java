/* PlayerInfoByNameCmpr.java */

/******************************************************************************/
/******************************************************************************/

class PlayerInfoByNameCmpr implements TAGComparer
{
	public int compare(Object objectOne,Object objectTwo)
	{
		PlayerInfo playerOne = (PlayerInfo)objectOne;
		PlayerInfo playerTwo = (PlayerInfo)objectTwo;

		return(playerOne.fName.compare(playerTwo.fName));
	}
}

/******************************************************************************/
/******************************************************************************/

