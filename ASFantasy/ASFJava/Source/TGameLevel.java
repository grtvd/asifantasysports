/* TGameLevel.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;

/******************************************************************************/
/******************************************************************************/

public class TGameLevel
{
	public final static TGameLevel gml_Undefined = new TGameLevel();
	public final static TGameLevel gml_Premium = new TGameLevel();
	public final static TGameLevel gml_Standard = new TGameLevel();

	/**************************************************************************/

	private TGameLevel()
	{
	}
	
	/**************************************************************************/

	public static TGameLevel convertFromByte(byte value)
	{
		switch(value)
		{
			case 0:
			default:
				return(gml_Undefined);
			case 1:
				return(gml_Premium);
			case 2:
				return(gml_Standard);
		}
	}
	
	/**************************************************************************/
	
	public static byte convertToByte(TGameLevel position)
	{
		if(position == gml_Premium)
			return((byte)1);
		else if(position == gml_Standard)
			return((byte)2);
		else //if(position == gml_Undefined)
			return((byte)0);
	}
	
	/**************************************************************************/

	public static TGameLevel readFromFiler(DataInputStream stream) throws IOException
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

