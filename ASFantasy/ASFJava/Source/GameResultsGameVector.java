/* GameResultsGameVector.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

public class GameResultsGameVector extends Vector
{
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		GameResultsGame gameResultsGame;

		short count;
		int i;

		try
		{
			removeAllElements();
		
			count = stream.readShort();
			for(i = 0; i < count; i++)
			{
				gameResultsGame = new GameResultsGame();
				gameResultsGame.readFromFiler(stream);

				addElement(gameResultsGame);
			}
		}
		catch(Exception e)
		{
			throw new IOException("GameResultsGameVector.readFromFiler: proprogating: " + e.toString());
		}
	}
	
}              

/******************************************************************************/
/******************************************************************************/
 
