/* GameResultsDayVector.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class GameResultsDayVector extends Vector
{
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		GameResultsDay gameResultsDay;

		short count;
		int i;

		try
		{
			removeAllElements();
		
			count = stream.readShort();
			for(i = 0; i < count; i++)
			{
				gameResultsDay = new GameResultsDay();
				gameResultsDay.readFromFiler(stream);

				addElement(gameResultsDay);
			}
		}
		catch(Exception e)
		{
			throw new IOException("GameResultsDayVector.readFromFiler: proprogating: " + e.toString());
		}
	}
	
}              

/******************************************************************************/
/******************************************************************************/
 
