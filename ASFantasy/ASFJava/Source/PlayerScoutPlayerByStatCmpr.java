/* PlayerScoutPlayerByStatCmpr.java */

/******************************************************************************/
/******************************************************************************/

class PlayerScoutPlayerByStatCmpr implements TAGComparer
{
	int fStat;
	boolean fAscending;

	/**************************************************************************/
	
	public PlayerScoutPlayerByStatCmpr(int stat,boolean ascending)
	{
		fStat = stat;
		fAscending = ascending;
	}
	
	/**************************************************************************/
	
	public int compare(Object objectOne,Object objectTwo)
	{
		PlayerScoutPlayer playerOne = (PlayerScoutPlayer)objectOne;
		PlayerScoutPlayer playerTwo = (PlayerScoutPlayer)objectTwo;
		
		String statOne = (playerOne.fPlayerStatValueVector.size() > fStat)
			? (String)playerOne.fPlayerStatValueVector.elementAt(fStat) : "";
			
		String statTwo = (playerTwo.fPlayerStatValueVector.size() > fStat)
			? (String)playerTwo.fPlayerStatValueVector.elementAt(fStat) : "";

		if(fAscending)
			return(TAGNativeCompare.compareString(statOne,statTwo));
		else
			return(TAGNativeCompare.compareString(statTwo,statOne));
	}
}

/******************************************************************************/
/******************************************************************************/

