/* StatYearType.java */

/******************************************************************************/
/******************************************************************************/

public class StatYearType
{
	/*
	syr_Undefined
	syr_YearToDate
	syr_LastTwoWeeks
	syr_LastFourWeeks
	syr_LastEightWeeks
	syr_LastYear
	syr_TwoYearsAgo
	syr_ThreeYearsAgo
	*/

	public final static StatYearType syr_Undefined = new StatYearType();
	public final static StatYearType syr_YearToDate = new StatYearType();
	public final static StatYearType syr_LastTwoWeeks = new StatYearType();
	public final static StatYearType syr_LastFourWeeks = new StatYearType();
	public final static StatYearType syr_LastEightWeeks = new StatYearType();
	public final static StatYearType syr_LastYear = new StatYearType();
	public final static StatYearType syr_TwoYearsAgo = new StatYearType();
	public final static StatYearType syr_ThreeYearsAgo = new StatYearType();

	/**************************************************************************/

	private StatYearType()
	{
	}
	
	/**************************************************************************/

	public static StatYearType convertFromByte(byte value)
	{
		switch(value)
		{
			case 0:
			default:
				return(syr_Undefined);
			case 1:
				return(syr_YearToDate);
			case 2:
				return(syr_LastTwoWeeks);
			case 3:
				return(syr_LastFourWeeks);
			case 4:
				return(syr_LastEightWeeks);
			case 5:
				return(syr_LastYear);
			case 6:
				return(syr_TwoYearsAgo);
			case 7:
				return(syr_ThreeYearsAgo);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(StatYearType statYearType)
	{
		if(statYearType == syr_YearToDate)
			return((byte)1);
		else if(statYearType == syr_LastTwoWeeks)
			return((byte)2);
		else if(statYearType == syr_LastFourWeeks)
			return((byte)3);
		else if(statYearType == syr_LastEightWeeks)
			return((byte)4);
		else if(statYearType == syr_LastYear)
			return((byte)5);
		else if(statYearType == syr_TwoYearsAgo)
			return((byte)6);
		else if(statYearType == syr_ThreeYearsAgo)
			return((byte)7);
		else //if(statYearType == syr_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/
}                              

/******************************************************************************/
/******************************************************************************/

