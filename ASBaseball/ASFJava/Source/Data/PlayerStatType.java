/* PlayerStatType.java */

/******************************************************************************/
/******************************************************************************/

public class PlayerStatType
{
	public final static PlayerStatType pst_Undefined = new PlayerStatType();

	public final static PlayerStatType pst_TotalPoints = new PlayerStatType();
	public final static PlayerStatType pst_GamesPlayed = new PlayerStatType();
	public final static PlayerStatType pst_GamesStarted = new PlayerStatType();
	public final static PlayerStatType pst_Errors = new PlayerStatType();

	public final static PlayerStatType pst_BattingAverage = new PlayerStatType();
	public final static PlayerStatType pst_AtBats = new PlayerStatType();

	public final static PlayerStatType pst_Hits = new PlayerStatType();
	public final static PlayerStatType pst_Doubles = new PlayerStatType();
	public final static PlayerStatType pst_Triples = new PlayerStatType();

	public final static PlayerStatType pst_OneRunHomers = new PlayerStatType();
	public final static PlayerStatType pst_TwoRunHomers = new PlayerStatType();
	public final static PlayerStatType pst_ThreeRunHomers = new PlayerStatType();
	public final static PlayerStatType pst_GrandSlams = new PlayerStatType();

	public final static PlayerStatType pst_RunsScored = new PlayerStatType();
	public final static PlayerStatType pst_RunsBattedIn = new PlayerStatType();
	public final static PlayerStatType pst_Sacrifices = new PlayerStatType();
	public final static PlayerStatType pst_HitByPicth = new PlayerStatType();
	public final static PlayerStatType pst_Walks = new PlayerStatType();

	public final static PlayerStatType pst_Strkeouts = new PlayerStatType();
	public final static PlayerStatType pst_StolenBases = new PlayerStatType();
	public final static PlayerStatType pst_CaughtStealing = new PlayerStatType();
	public final static PlayerStatType pst_GroundedDoublePlay = new PlayerStatType();
	public final static PlayerStatType pst_HitForCycle = new PlayerStatType();

	public final static PlayerStatType pst_EarnedRunAverage = new PlayerStatType();

	public final static PlayerStatType pst_Wins = new PlayerStatType();
	public final static PlayerStatType pst_Losses = new PlayerStatType();
	public final static PlayerStatType pst_Saves = new PlayerStatType();

	public final static PlayerStatType pst_InningsPitched = new PlayerStatType();
	public final static PlayerStatType pst_HitsAllowed = new PlayerStatType();
	public final static PlayerStatType pst_DoublesAllowed = new PlayerStatType();
	public final static PlayerStatType pst_TriplesAllowed = new PlayerStatType();

	public final static PlayerStatType pst_OneRunHomersAllowed = new PlayerStatType();
	public final static PlayerStatType pst_TwoRunHomersAllowed = new PlayerStatType();
	public final static PlayerStatType pst_ThreeRunHomersAllowed = new PlayerStatType();
	public final static PlayerStatType pst_GrandSlamsAllowed = new PlayerStatType();

	public final static PlayerStatType pst_RunsAllowed = new PlayerStatType();
	public final static PlayerStatType pst_EarnedRunsAllowed = new PlayerStatType();
	public final static PlayerStatType pst_SacrificesAllowed = new PlayerStatType();
	public final static PlayerStatType pst_HitBatsmen = new PlayerStatType();
	public final static PlayerStatType pst_WalkedBatsmen = new PlayerStatType();
	public final static PlayerStatType pst_StruckoutBatsmen = new PlayerStatType();
	public final static PlayerStatType pst_WildPitches = new PlayerStatType();
	public final static PlayerStatType pst_Balks = new PlayerStatType();
	
	public final static PlayerStatType pst_CompleteGames = new PlayerStatType();
	public final static PlayerStatType pst_Shutouts = new PlayerStatType();
	public final static PlayerStatType pst_NoHitters = new PlayerStatType();
	public final static PlayerStatType pst_PerfectGames = new PlayerStatType();

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
				return(pst_GamesStarted);
			case 4:
				return(pst_Errors);
			case 5:
				return(pst_BattingAverage);
			case 6:
				return(pst_AtBats);
			case 7:
				return(pst_Hits);
			case 8:
				return(pst_Doubles);
			case 9:
				return(pst_Triples);
			case 10:
				return(pst_OneRunHomers);
			case 11:
				return(pst_TwoRunHomers);
			case 12:
				return(pst_ThreeRunHomers);
			case 13:
				return(pst_GrandSlams);
			case 14:
				return(pst_RunsScored);
			case 15:
				return(pst_RunsBattedIn);
			case 16:
				return(pst_Sacrifices);
			case 17:
				return(pst_HitByPicth);
			case 18:
				return(pst_Walks);
			case 19:
				return(pst_Strkeouts);
			case 20:
				return(pst_StolenBases);
			case 21:
				return(pst_CaughtStealing);
			case 22:
				return(pst_GroundedDoublePlay);
			case 23:
				return(pst_HitForCycle);
			case 24:
				return(pst_EarnedRunAverage);
			case 25:
				return(pst_Wins);
			case 26:
				return(pst_Losses);
			case 27:
				return(pst_Saves);
			case 28:
				return(pst_InningsPitched);
			case 29:
				return(pst_HitsAllowed);
			case 30:
				return(pst_DoublesAllowed);
			case 31:
				return(pst_TriplesAllowed);
			case 32:
				return(pst_OneRunHomersAllowed);
			case 33:
				return(pst_TwoRunHomersAllowed);
			case 34:
				return(pst_ThreeRunHomersAllowed);
			case 35:
				return(pst_GrandSlamsAllowed);
			case 36:
				return(pst_RunsAllowed);
			case 37:
				return(pst_EarnedRunsAllowed);
			case 38:
				return(pst_SacrificesAllowed);
			case 39:
				return(pst_HitBatsmen);
			case 40:
				return(pst_WalkedBatsmen);
			case 41:
				return(pst_StruckoutBatsmen);
			case 42:
				return(pst_WildPitches);
			case 43:
				return(pst_Balks);
			case 44:
				return(pst_CompleteGames);
			case 45:
				return(pst_Shutouts);
			case 46:
				return(pst_NoHitters);
			case 47:
				return(pst_PerfectGames);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(PlayerStatType playerStatType)
	{
		if(playerStatType == pst_TotalPoints)
			return((byte)1);
		else if(playerStatType == pst_GamesPlayed)
			return((byte)2);
		else if(playerStatType == pst_GamesStarted)
			return((byte)3);
		else if(playerStatType == pst_Errors)
			return((byte)4);
		else if(playerStatType == pst_BattingAverage)
			return((byte)5);
		else if(playerStatType == pst_AtBats)
			return((byte)6);
		else if(playerStatType == pst_Hits)
			return((byte)7);
		else if(playerStatType == pst_Doubles)
			return((byte)8);
		else if(playerStatType == pst_Triples)
			return((byte)9);
		else if(playerStatType == pst_OneRunHomers)
			return((byte)10);
		else if(playerStatType == pst_TwoRunHomers)
			return((byte)11);
		else if(playerStatType == pst_ThreeRunHomers)
			return((byte)12);
		else if(playerStatType == pst_GrandSlams)
			return((byte)13);
		else if(playerStatType == pst_RunsScored)
			return((byte)14);
		else if(playerStatType == pst_RunsBattedIn)
			return((byte)15);
		else if(playerStatType == pst_Sacrifices)
			return((byte)16);
		else if(playerStatType == pst_HitByPicth)
			return((byte)17);
		else if(playerStatType == pst_Walks)
			return((byte)18);
		else if(playerStatType == pst_Strkeouts)
			return((byte)19);
		else if(playerStatType == pst_StolenBases)
			return((byte)20);
		else if(playerStatType == pst_CaughtStealing)
			return((byte)21);
		else if(playerStatType == pst_GroundedDoublePlay)
			return((byte)22);
		else if(playerStatType == pst_HitForCycle)
			return((byte)23);
		else if(playerStatType == pst_EarnedRunAverage)
			return((byte)24);
		else if(playerStatType == pst_Wins)
			return((byte)25);
		else if(playerStatType == pst_Losses)
			return((byte)26);
		else if(playerStatType == pst_Saves)
			return((byte)27);
		else if(playerStatType == pst_InningsPitched)
			return((byte)28);
		else if(playerStatType == pst_HitsAllowed)
			return((byte)29);
		else if(playerStatType == pst_DoublesAllowed)
			return((byte)30);
		else if(playerStatType == pst_TriplesAllowed)
			return((byte)31);
		else if(playerStatType == pst_OneRunHomersAllowed)
			return((byte)32);
		else if(playerStatType == pst_TwoRunHomersAllowed)
			return((byte)33);
		else if(playerStatType == pst_ThreeRunHomersAllowed)
			return((byte)34);
		else if(playerStatType == pst_GrandSlamsAllowed)
			return((byte)35);
		else if(playerStatType == pst_RunsAllowed)
			return((byte)36);
		else if(playerStatType == pst_EarnedRunsAllowed)
			return((byte)37);
		else if(playerStatType == pst_SacrificesAllowed)
			return((byte)38);
		else if(playerStatType == pst_HitBatsmen)
			return((byte)39);
		else if(playerStatType == pst_WalkedBatsmen)
			return((byte)40);
		else if(playerStatType == pst_StruckoutBatsmen)
			return((byte)41);
		else if(playerStatType == pst_WildPitches)
			return((byte)42);
		else if(playerStatType == pst_Balks)
			return((byte)43);
		else if(playerStatType == pst_CompleteGames)
			return((byte)44);
		else if(playerStatType == pst_Shutouts)
			return((byte)45);
		else if(playerStatType == pst_NoHitters)
			return((byte)46);
		else if(playerStatType == pst_PerfectGames)
			return((byte)47);
		else //if(playerStatType == pst_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/
	
	public static Object convertStatForDisplay(PlayerStatType playerStatType,
		String statAsStr)
	{
		if(playerStatType == pst_Undefined)
			return(new String());

		if(playerStatType == pst_BattingAverage)
			return(new String(statAsStr));

		if(playerStatType == pst_EarnedRunAverage)
			return(new String(statAsStr));

		return(new Integer(statAsStr));
	}

}

/******************************************************************************/
/******************************************************************************/
