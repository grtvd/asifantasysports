/* TPosition.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

public class TPosition
{
	public final static TPosition pos_Undefined = new TPosition();
	public final static TPosition pos_PointGuard = new TPosition();
	public final static TPosition pos_ShootingGuard = new TPosition();
	public final static TPosition pos_SmallForward = new TPosition();
	public final static TPosition pos_PowerForward = new TPosition();
	public final static TPosition pos_Center = new TPosition();

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
		if(position == pos_PointGuard)
			return("PG");
		else if(position == pos_ShootingGuard)
			return("SG");
		else if(position == pos_SmallForward)
			return("SF");
		else if(position == pos_PowerForward)
			return("PF");
		else if(position == pos_Center)
			return("C");
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
				return(pos_PointGuard);
			case 2:
				return(pos_ShootingGuard);
			case 3:
				return(pos_SmallForward);
			case 4:
				return(pos_PowerForward);
			case 5:
				return(pos_Center);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(TPosition position)
	{
		if(position == pos_PointGuard)
			return((byte)1);
		else if(position == pos_ShootingGuard)
			return((byte)2);
		else if(position == pos_SmallForward)
			return((byte)3);
		else if(position == pos_PowerForward)
			return((byte)4);
		else if(position == pos_Center)
			return((byte)5);
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
