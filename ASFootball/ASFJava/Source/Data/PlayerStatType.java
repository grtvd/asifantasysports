/* PlayerStatType.java */

/******************************************************************************/
/******************************************************************************/

public class PlayerStatType
{
/*	
Undefined
TotalPoints
PassingYards
PassingTDs
Interceptions
TwoPointPasses
RushingYards
RushingTDs
Fumbles
TwoPointRushes
ReceivingYards
ReceivingTDs
TwoPointReceptions
KickReturnTDs
MiscTDs
PATsMade
PATsMissed
FieldGoalsMade
FieldGoalsMissed
YardsAllowed
Safeties
Sacks
BlockedKicks
FumblesRecovered
DefInterceptions
DefensiveTDs
*/	

	public final static PlayerStatType pst_Undefined = new PlayerStatType();
	public final static PlayerStatType pst_TotalPoints = new PlayerStatType();
	
	public final static PlayerStatType pst_PassingYards = new PlayerStatType();
	public final static PlayerStatType pst_PassingTDs = new PlayerStatType();
	public final static PlayerStatType pst_Interceptions = new PlayerStatType();
	public final static PlayerStatType pst_TwoPointPasses = new PlayerStatType();
	
	public final static PlayerStatType pst_RushingYards = new PlayerStatType();
	public final static PlayerStatType pst_RushingTDs = new PlayerStatType();
	public final static PlayerStatType pst_Fumbles = new PlayerStatType();
	public final static PlayerStatType pst_TwoPointRushes = new PlayerStatType();
	
	public final static PlayerStatType pst_ReceivingYards = new PlayerStatType();
	public final static PlayerStatType pst_ReceivingTDs = new PlayerStatType();
	public final static PlayerStatType pst_TwoPointReceptions = new PlayerStatType();
	
	public final static PlayerStatType pst_KickReturnTDs = new PlayerStatType();
	public final static PlayerStatType pst_MiscTDs = new PlayerStatType();
	
	public final static PlayerStatType pst_PATsMade = new PlayerStatType();
	public final static PlayerStatType pst_PATsMissed = new PlayerStatType();
	public final static PlayerStatType pst_FieldGoalsMade = new PlayerStatType();
	public final static PlayerStatType pst_FieldGoalsMissed = new PlayerStatType();
	
	public final static PlayerStatType pst_YardsAllowed = new PlayerStatType();
	public final static PlayerStatType pst_Safeties = new PlayerStatType();
	public final static PlayerStatType pst_Sacks = new PlayerStatType();
	public final static PlayerStatType pst_BlockedKicks = new PlayerStatType();
	public final static PlayerStatType pst_FumblesRecovered = new PlayerStatType();
	public final static PlayerStatType pst_DefInterceptions = new PlayerStatType();
	public final static PlayerStatType pst_DefensiveTDs = new PlayerStatType();

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
				return(pst_PassingYards);
			case 3:
				return(pst_PassingTDs);
			case 4:
				return(pst_Interceptions);
			case 5:
				return(pst_TwoPointPasses);
			case 6:
				return(pst_RushingYards);
			case 7:
				return(pst_RushingTDs);
			case 8:
				return(pst_Fumbles);
			case 9:
				return(pst_TwoPointRushes);
			case 10:
				return(pst_ReceivingYards);
			case 11:
				return(pst_ReceivingTDs);
			case 12:
				return(pst_TwoPointReceptions);
			case 13:
				return(pst_KickReturnTDs);
			case 14:
				return(pst_MiscTDs);
			case 15:
				return(pst_PATsMade);
			case 16:
				return(pst_PATsMissed);
			case 17:
				return(pst_FieldGoalsMade);
			case 18:
				return(pst_FieldGoalsMissed);
			case 19:
				return(pst_YardsAllowed);
			case 20:
				return(pst_Safeties);
			case 21:
				return(pst_Sacks);
			case 22:
				return(pst_BlockedKicks);
			case 23:
				return(pst_FumblesRecovered);
			case 24:
				return(pst_DefInterceptions);
			case 25:
				return(pst_DefensiveTDs);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(PlayerStatType playerStatType)
	{
		if(playerStatType == pst_TotalPoints)
			return((byte)1);
		else if(playerStatType == pst_PassingYards)
			return((byte)2);
		else if(playerStatType == pst_PassingTDs)
			return((byte)3);
		else if(playerStatType == pst_Interceptions)
			return((byte)4);
		else if(playerStatType == pst_TwoPointPasses)
			return((byte)5);
		else if(playerStatType == pst_RushingYards)
			return((byte)6);
		else if(playerStatType == pst_RushingTDs)
			return((byte)7);
		else if(playerStatType == pst_Fumbles)
			return((byte)8);
		else if(playerStatType == pst_TwoPointRushes)
			return((byte)9);
		else if(playerStatType == pst_ReceivingYards)
			return((byte)10);
		else if(playerStatType == pst_ReceivingTDs)
			return((byte)11);
		else if(playerStatType == pst_TwoPointReceptions)
			return((byte)12);
		else if(playerStatType == pst_KickReturnTDs)
			return((byte)13);
		else if(playerStatType == pst_MiscTDs)
			return((byte)14);
		else if(playerStatType == pst_PATsMade)
			return((byte)15);
		else if(playerStatType == pst_PATsMissed)
			return((byte)16);
		else if(playerStatType == pst_FieldGoalsMade)
			return((byte)17);
		else if(playerStatType == pst_FieldGoalsMissed)
			return((byte)18);
		else if(playerStatType == pst_YardsAllowed)
			return((byte)19);
		else if(playerStatType == pst_Safeties)
			return((byte)20);
		else if(playerStatType == pst_Sacks)
			return((byte)21);
		else if(playerStatType == pst_BlockedKicks)
			return((byte)22);
		else if(playerStatType == pst_FumblesRecovered)
			return((byte)23);
		else if(playerStatType == pst_DefInterceptions)
			return((byte)24);
		else if(playerStatType == pst_DefensiveTDs)
			return((byte)25);
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

