/* PlayerScoutStat.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class PlayerScoutStat implements Streamable
{
	PlayerStatType fStatType = PlayerStatType.pst_Undefined;
	StatYearType fStatYear = StatYearType.syr_Undefined;

	/**************************************************************************/

	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fStatType = PlayerStatType.convertFromByte(stream.readByte());
		fStatYear = StatYearType.convertFromByte(stream.readByte());
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
		stream.writeByte(PlayerStatType.convertToByte(fStatType));
		stream.writeByte(StatYearType.convertToByte(fStatYear));
	}   

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
	
}                              

/******************************************************************************/
/******************************************************************************/

