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
	pos_Winger
	pos_Center
	pos_Defenseman
	pos_Goalie
	*/

	public final static TPosition pos_Undefined = new TPosition();
	public final static TPosition pos_Winger = new TPosition();
	public final static TPosition pos_Center = new TPosition();
	public final static TPosition pos_Defenseman = new TPosition();
	public final static TPosition pos_Goalie = new TPosition();

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
		if(position == pos_Winger)
			return("W");
		else if(position == pos_Center)
			return("C");
		else if(position == pos_Defenseman)
			return("D");
		else if(position == pos_Goalie)
			return("G");
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
				return(pos_Winger);
			case 2:
				return(pos_Center);
			case 3:
				return(pos_Defenseman);
			case 4:
				return(pos_Goalie);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(TPosition position)
	{
		if(position == pos_Winger)
			return((byte)1);
		else if(position == pos_Center)
			return((byte)2);
		else if(position == pos_Defenseman)
			return((byte)3);
		else if(position == pos_Goalie)
			return((byte)4);
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
