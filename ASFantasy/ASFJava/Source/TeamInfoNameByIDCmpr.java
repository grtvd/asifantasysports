/* TeamInfoNameByIDCmpr.java */

/******************************************************************************/
/******************************************************************************/

import java.util.*;

/******************************************************************************/
/******************************************************************************/

class TeamInfoNameByIDCmpr implements TAGComparer
{
	// Since different instances of this object would all be identical,
	// why not just have one instance.

	private static final TeamInfoNameByIDCmpr fTheComparer = new TeamInfoNameByIDCmpr();

	/**************************************************************************/

	public static TeamInfoNameByIDCmpr getThe()
	{
		return(fTheComparer);
	}

	/**************************************************************************/

	public int compare(Object objectOne,Object objectTwo)
	{
		TeamInfoName profPlayerOne = (TeamInfoName)objectOne;
		TeamInfoName profPlayerTwo = (TeamInfoName)objectTwo;

		return(TAGNativeCompare.compareInt(profPlayerOne.fTeamID,
			profPlayerTwo.fTeamID));
	}
}

/******************************************************************************/
/******************************************************************************/

