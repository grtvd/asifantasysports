/* PlayerStatType.java */

/******************************************************************************/
/******************************************************************************/

public class PlayerStatType
{
	public final static PlayerStatType pst_Undefined = new PlayerStatType();

	public final static PlayerStatType pst_TotalPoints = new PlayerStatType();
	public final static PlayerStatType pst_GamesPlayed = new PlayerStatType();
	public final static PlayerStatType pst_MinutesPlayed = new PlayerStatType();
	public final static PlayerStatType pst_PointsScored = new PlayerStatType();

	public final static PlayerStatType pst_FieldGoalsMade = new PlayerStatType();
	public final static PlayerStatType pst_FieldGoalsAttempted = new PlayerStatType();
	public final static PlayerStatType pst_FieldGoalPercentage = new PlayerStatType();
	public final static PlayerStatType pst_FreeThrowsMade = new PlayerStatType();
	public final static PlayerStatType pst_FreeThrowsAttempted = new PlayerStatType();
	public final static PlayerStatType pst_FreeThrowPercentage = new PlayerStatType();
	public final static PlayerStatType pst_ThreePointGoalsMade = new PlayerStatType();
	public final static PlayerStatType pst_ThreePointGoalsAttempted = new PlayerStatType();

	public final static PlayerStatType pst_OffensiveRebounds = new PlayerStatType();
	public final static PlayerStatType pst_DefensiveRebounds = new PlayerStatType();
	public final static PlayerStatType pst_Assists = new PlayerStatType();
	public final static PlayerStatType pst_Steals = new PlayerStatType();
	public final static PlayerStatType pst_Blocks = new PlayerStatType();

	public final static PlayerStatType pst_Turnovers = new PlayerStatType();
	public final static PlayerStatType pst_PersonalFouls = new PlayerStatType();
	public final static PlayerStatType pst_TechnicalFouls = new PlayerStatType();

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
				return(pst_MinutesPlayed);
			case 4:
				return(pst_PointsScored);
			case 5:
				return(pst_FieldGoalsMade);
			case 6:
				return(pst_FieldGoalsAttempted);
			case 7:
				return(pst_FieldGoalPercentage);
			case 8:
				return(pst_FreeThrowsMade);
			case 9:
				return(pst_FreeThrowsAttempted);
			case 10:
				return(pst_FreeThrowPercentage);
			case 11:
				return(pst_ThreePointGoalsMade);
			case 12:
				return(pst_ThreePointGoalsAttempted);
			case 13:
				return(pst_OffensiveRebounds);
			case 14:
				return(pst_DefensiveRebounds);
			case 15:
				return(pst_Assists);
			case 16:
				return(pst_Steals);
			case 17:
				return(pst_Blocks);
			case 18:
				return(pst_Turnovers);
			case 19:
				return(pst_PersonalFouls);
			case 20:
				return(pst_TechnicalFouls);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(PlayerStatType playerStatType)
	{
		if(playerStatType == pst_TotalPoints)
			return((byte)1);
		else if(playerStatType == pst_GamesPlayed)
			return((byte)2);
		else if(playerStatType == pst_MinutesPlayed)
			return((byte)3);
		else if(playerStatType == pst_PointsScored)
			return((byte)4);
		else if(playerStatType == pst_FieldGoalsMade)
			return((byte)5);
		else if(playerStatType == pst_FieldGoalsAttempted)
			return((byte)6);
		else if(playerStatType == pst_FieldGoalPercentage)
			return((byte)7);
		else if(playerStatType == pst_FreeThrowsMade)
			return((byte)8);
		else if(playerStatType == pst_FreeThrowsAttempted)
			return((byte)9);
		else if(playerStatType == pst_FreeThrowPercentage)
			return((byte)10);
		else if(playerStatType == pst_ThreePointGoalsMade)
			return((byte)11);
		else if(playerStatType == pst_ThreePointGoalsAttempted)
			return((byte)12);
		else if(playerStatType == pst_OffensiveRebounds)
			return((byte)13);
		else if(playerStatType == pst_DefensiveRebounds)
			return((byte)14);
		else if(playerStatType == pst_Assists)
			return((byte)15);
		else if(playerStatType == pst_Steals)
			return((byte)16);
		else if(playerStatType == pst_Blocks)
			return((byte)17);
		else if(playerStatType == pst_Turnovers)
			return((byte)18);
		else if(playerStatType == pst_PersonalFouls)
			return((byte)19);
		else if(playerStatType == pst_TechnicalFouls)
			return((byte)20);
		else //if(playerStatType == pst_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/
	
	public static Object convertStatForDisplay(PlayerStatType playerStatType,
		String statAsStr)
	{
		if(playerStatType == pst_Undefined)
			return(new String());

		if(playerStatType == pst_FieldGoalPercentage)
			return(new String(statAsStr));

		if(playerStatType == pst_FreeThrowPercentage)
			return(new String(statAsStr));

		return(new Integer(statAsStr));
	}

}

/******************************************************************************/
/******************************************************************************/
