/* GameResultsResp.java */

/******************************************************************************/
/******************************************************************************/

import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class GameResultsResp implements Streamable
{
	public TGameLevel fGameLevel = TGameLevel.gml_Undefined;

	public GameResultsDayVector fGameResultsDayVector = new GameResultsDayVector();
	public short fShowDay = -1;

	public GameResultsGameVector fGameResultsGameVector = new GameResultsGameVector();
	public short fShowGame = -1;

	public ScheduleDayStatus fStatus = ScheduleDayStatus.sdst_Undefined;

	public TeamInfoName fVisitTeam = new TeamInfoName(0);
	public short fVisitScore;
	public PlayerInfoVector fVisitPlayerVector = new PlayerInfoVector();

	public TeamInfoName fHomeTeam = new TeamInfoName(0);
	public short fHomeScore;
	public PlayerInfoVector fHomePlayerVector = new PlayerInfoVector();
	
	/**************************************************************************/
	
	public void readFromFiler(DataInputStream stream) throws IOException
	{
		fGameLevel = TGameLevel.convertFromByte(stream.readByte());

		fGameResultsDayVector.readFromFiler(stream);
		fShowDay = stream.readShort();

		fGameResultsGameVector.readFromFiler(stream);
		fShowGame = stream.readShort();

		fStatus = ScheduleDayStatus.readFromFiler(stream);

		fVisitTeam.readFromFiler(stream);
		fVisitScore = stream.readShort();
		fVisitPlayerVector.readFromFiler(stream,new GameResultsPlayer().getClass());
		
		fHomeTeam.readFromFiler(stream);
		fHomeScore = stream.readShort();
		fHomePlayerVector.readFromFiler(stream,new GameResultsPlayer().getClass());
	}
	
	/**************************************************************************/

	public void writeToFiler(DataOutputStream stream) throws IOException
	{
	}

	/**************************************************************************/

	public void writeToSystemOut()
	{
		System.out.println("Class: " + getClass().getName());
	}
}

/******************************************************************************/
/******************************************************************************/
