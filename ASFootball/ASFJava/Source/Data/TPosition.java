/* TPosition.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

public class TPosition
{
	/*
	pos_Undefined
	pos_Quarterback
	pos_WideReceiver
	pos_RunningBack
	pos_TightEnd
	pos_Kicker
	pos_Defense
	*/

	public final static TPosition pos_Undefined = new TPosition();
	public final static TPosition pos_Quarterback = new TPosition();
	public final static TPosition pos_WideReceiver = new TPosition();
	public final static TPosition pos_RunningBack = new TPosition();
	public final static TPosition pos_TightEnd = new TPosition();
	public final static TPosition pos_Kicker = new TPosition();
	public final static TPosition pos_Defense = new TPosition();

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
		if(position == pos_Quarterback)
			return("QB");
		else if(position == pos_WideReceiver)
			return("WR");
		else if(position == pos_RunningBack)
			return("RB");
		else if(position == pos_TightEnd)
			return("TE");
		else if(position == pos_Kicker)
			return("K");
		else if(position == pos_Defense)
			return("D");
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
				return(pos_Quarterback);
			case 2:
				return(pos_WideReceiver);
			case 3:
				return(pos_RunningBack);
			case 4:
				return(pos_TightEnd);
			case 5:
				return(pos_Kicker);
			case 6:
				return(pos_Defense);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(TPosition position)
	{
		if(position == pos_Quarterback)
			return((byte)1);
		else if(position == pos_WideReceiver)
			return((byte)2);
		else if(position == pos_RunningBack)
			return((byte)3);
		else if(position == pos_TightEnd)
			return((byte)4);
		else if(position == pos_Kicker)
			return((byte)5);
		else if(position == pos_Defense)
			return((byte)6);
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
