/* ScheduleDayStatus.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

public class ScheduleDayStatus
{
	public final static ScheduleDayStatus sdst_Undefined = new ScheduleDayStatus();
	public final static ScheduleDayStatus sdst_Missed = new ScheduleDayStatus();
	public final static ScheduleDayStatus sdst_NotStarted = new ScheduleDayStatus();
	public final static ScheduleDayStatus sdst_InProgress = new ScheduleDayStatus();
	public final static ScheduleDayStatus sdst_Completed = new ScheduleDayStatus();

	/**************************************************************************/

	private ScheduleDayStatus()
	{
	}
	
	/**************************************************************************/

	public static ScheduleDayStatus convertFromByte(byte value)
	{
		switch(value)
		{
			case 0:
			default:
				return(sdst_Undefined);
			case 1:
				return(sdst_Missed);
			case 2:
				return(sdst_NotStarted);
			case 3:
				return(sdst_InProgress);
			case 4:
				return(sdst_Completed);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(ScheduleDayStatus position)
	{
		if(position == sdst_Missed)
			return((byte)1);
		else if(position == sdst_NotStarted)
			return((byte)2);
		else if(position == sdst_InProgress)
			return((byte)3);
		else if(position == sdst_Completed)
			return((byte)4);
		else //if(position == sdst_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/

	public static ScheduleDayStatus readFromFiler(DataInputStream stream) throws IOException
	{
		return(convertFromByte(stream.readByte()));
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeByte(convertToByte(this));
	}

	/**************************************************************************/
}

/******************************************************************************/
/******************************************************************************/

