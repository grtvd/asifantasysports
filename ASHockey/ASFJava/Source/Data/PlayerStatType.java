/* PlayerStatType.java */

/******************************************************************************/
/******************************************************************************/

public class PlayerStatType
{
/*	
Undefined
TotalPoints
GamesPlayed
Goals
Assists
PenaltyMinutes
Shots
PlusMinus
PowerPlayGoals
PowerPlayAssists
ShortHandedGoals
ShortHandedAssists
GameWinningGoals
GameTyingGoals
OvertimeGoals
HatTricks
GamesStarted
Wins
Losses
Ties
GoalsAgainst
Saves
Shutouts
*/

	public final static PlayerStatType pst_Undefined = new PlayerStatType();

	public final static PlayerStatType pst_TotalPoints = new PlayerStatType();
	public final static PlayerStatType pst_GamesPlayed = new PlayerStatType();

	public final static PlayerStatType pst_Goals = new PlayerStatType();
	public final static PlayerStatType pst_Assists = new PlayerStatType();
	public final static PlayerStatType pst_PenaltyMinutes = new PlayerStatType();
	public final static PlayerStatType pst_Shots = new PlayerStatType();
	public final static PlayerStatType pst_PlusMinus = new PlayerStatType();

	public final static PlayerStatType pst_PowerPlayGoals = new PlayerStatType();
	public final static PlayerStatType pst_PowerPlayAssists = new PlayerStatType();
	public final static PlayerStatType pst_ShortHandedGoals = new PlayerStatType();
	public final static PlayerStatType pst_ShortHandedAssists = new PlayerStatType();
	public final static PlayerStatType pst_GameWinningGoals = new PlayerStatType();
	public final static PlayerStatType pst_GameTyingGoals = new PlayerStatType();
	public final static PlayerStatType pst_OvertimeGoals = new PlayerStatType();

	public final static PlayerStatType pst_HatTricks = new PlayerStatType();

	public final static PlayerStatType pst_GamesStarted = new PlayerStatType();

	public final static PlayerStatType pst_Wins = new PlayerStatType();
	public final static PlayerStatType pst_Losses = new PlayerStatType();
	public final static PlayerStatType pst_Ties = new PlayerStatType();

	public final static PlayerStatType pst_GoalsAgainst = new PlayerStatType();
	public final static PlayerStatType pst_Saves = new PlayerStatType();
	public final static PlayerStatType pst_Shutouts = new PlayerStatType();

	/**************************************************************************/

	private PlayerStatType()
	{
	}
	
	/**************************************************************************/

	public static PlayerStatType convertFromByte(byte value)
	{
		switch(value)
		{
			case 0:
			default:
				return(pst_Undefined);
			case 1:
				return(pst_TotalPoints);
			case 2:
				return(pst_GamesPlayed);
			case 3:
				return(pst_Goals);
			case 4:
				return(pst_Assists);
			case 5:
				return(pst_PenaltyMinutes);
			case 6:
				return(pst_Shots);
			case 7:
				return(pst_PlusMinus);
			case 8:
				return(pst_PowerPlayGoals);
			case 9:
				return(pst_PowerPlayAssists);
			case 10:
				return(pst_ShortHandedGoals);
			case 11:
				return(pst_ShortHandedAssists);
			case 12:
				return(pst_GameWinningGoals);
			case 13:
				return(pst_GameTyingGoals);
			case 14:
				return(pst_OvertimeGoals);
			case 15:
				return(pst_HatTricks);
			case 16:
				return(pst_GamesStarted);
			case 17:
				return(pst_Wins);
			case 18:
				return(pst_Losses);
			case 19:
				return(pst_Ties);
			case 20:
				return(pst_GoalsAgainst);
			case 21:
				return(pst_Saves);
			case 22:
				return(pst_Shutouts);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(PlayerStatType playerStatType)
	{
		if(playerStatType == pst_TotalPoints)
			return((byte)1);
		else if(playerStatType == pst_GamesPlayed)
			return((byte)2);
		else if(playerStatType == pst_Goals)
			return((byte)3);
		else if(playerStatType == pst_Assists)
			return((byte)4);
		else if(playerStatType == pst_PenaltyMinutes)
			return((byte)5);
		else if(playerStatType == pst_Shots)
			return((byte)6);
		else if(playerStatType == pst_PlusMinus)
			return((byte)7);
		else if(playerStatType == pst_PowerPlayGoals)
			return((byte)8);
		else if(playerStatType == pst_PowerPlayAssists)
			return((byte)9);
		else if(playerStatType == pst_ShortHandedGoals)
			return((byte)10);
		else if(playerStatType == pst_ShortHandedAssists)
			return((byte)11);
		else if(playerStatType == pst_GameWinningGoals)
			return((byte)12);
		else if(playerStatType == pst_GameTyingGoals)
			return((byte)13);
		else if(playerStatType == pst_OvertimeGoals)
			return((byte)14);
		else if(playerStatType == pst_HatTricks)
			return((byte)15);
		else if(playerStatType == pst_GamesStarted)
			return((byte)16);
		else if(playerStatType == pst_Wins)
			return((byte)17);
		else if(playerStatType == pst_Losses)
			return((byte)18);
		else if(playerStatType == pst_Ties)
			return((byte)19);
		else if(playerStatType == pst_GoalsAgainst)
			return((byte)20);
		else if(playerStatType == pst_Saves)
			return((byte)21);
		else if(playerStatType == pst_Shutouts)
			return((byte)22);
		else //if(playerStatType == pst_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/
	
	public static Object convertStatForDisplay(PlayerStatType playerStatType,
		String statAsStr)
	{
		if(playerStatType == pst_Undefined)
			return(new String());

		return(new Integer(statAsStr));
	}

}

/******************************************************************************/
/******************************************************************************/

