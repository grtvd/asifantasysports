/* TPosition.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

public class TPosition
{
	public final static TPosition pos_Undefined = new TPosition();
	public final static TPosition pos_FirstBaseman = new TPosition();
	public final static TPosition pos_SecondBaseman = new TPosition();
	public final static TPosition pos_ShortStop = new TPosition();
	public final static TPosition pos_ThirdBaseman = new TPosition();
	public final static TPosition pos_Catcher = new TPosition();
	public final static TPosition pos_Outfielder = new TPosition();
	public final static TPosition pos_DesignatedHitter = new TPosition();
	public final static TPosition pos_StartingPitcher = new TPosition();
	public final static TPosition pos_ReliefPitcher = new TPosition();

	/**************************************************************************/
	
	private TPosition()
	{
	}
	
	/**************************************************************************/

	public String toString()
	{
		return(toStringFromValue(this));
	}

	/**************************************************************************/

	public static String toStringFromValue(TPosition position)
	{
		if(position == pos_FirstBaseman)
			return("1B");
		else if(position == pos_SecondBaseman)
			return("2B");
		else if(position == pos_ShortStop)
			return("SS");
		else if(position == pos_ThirdBaseman)
			return("3B");
		else if(position == pos_Catcher)
			return("C");
		else if(position == pos_Outfielder)
			return("OF");
		else if(position == pos_DesignatedHitter)
			return("DH");
		else if(position == pos_StartingPitcher)
			return("SP");
		else if(position == pos_ReliefPitcher)
			return("RP");
		else //if(position == pos_Undefined)
			return("");
	}
	
	/**************************************************************************/

	public static TPosition convertFromByte(byte value)
	{
		switch(value)
		{
			case 0:
			default:
				return(pos_Undefined);
			case 1:
				return(pos_FirstBaseman);
			case 2:
				return(pos_SecondBaseman);
			case 3:
				return(pos_ShortStop);
			case 4:
				return(pos_ThirdBaseman);
			case 5:
				return(pos_Catcher);
			case 6:
				return(pos_Outfielder);
			case 7:
				return(pos_DesignatedHitter);
			case 8:
				return(pos_StartingPitcher);
			case 9:
				return(pos_ReliefPitcher);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(TPosition position)
	{
		if(position == pos_FirstBaseman)
			return((byte)1);
		else if(position == pos_SecondBaseman)
			return((byte)2);
		else if(position == pos_ShortStop)
			return((byte)3);
		else if(position == pos_ThirdBaseman)
			return((byte)4);
		if(position == pos_Catcher)
			return((byte)5);
		if(position == pos_Outfielder)
			return((byte)6);
		if(position == pos_DesignatedHitter)
			return((byte)7);
		if(position == pos_StartingPitcher)
			return((byte)8);
		if(position == pos_ReliefPitcher)
			return((byte)9);
		else //if(position == pos_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/

	public static TPosition readFromFiler(DataInputStream stream) throws IOException
	{
		return(convertFromByte(stream.readByte()));
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeByte(convertToByte(this));
	}   

}

/******************************************************************************/
/******************************************************************************/
