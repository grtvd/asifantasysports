/* ASFantasyGameResultsApplet.java */

/******************************************************************************/
/******************************************************************************/

import java.awt.*;
import java.applet.*;
import java.io.*;
import java.util.*;
import jclass.bwt.*;
import jclass.util.*;

/******************************************************************************/
/******************************************************************************/

public class ASFantasyGameResultsApplet extends ASFBaseApplet
{
	//{{DECLARE_CONTROLS
	protected symantec.itools.awt.BorderPanel fShowPnl;
	protected jclass.bwt.JCLabel fShowDayLbl;
	protected java.awt.Choice fShowDayChc;
	protected jclass.bwt.JCLabel fShowGameLbl;
	protected java.awt.Choice fShowGameChc;
	protected jclass.bwt.JCLabel fStatusTagLbl;
	protected jclass.bwt.JCLabel fStatusLbl;
	//}}

	private TGameLevel fGameLevel = TGameLevel.gml_Undefined;
	
	private GameResultsDayVector fGameResultsDayVector;
	private short fShowDay;

	private GameResultsGameVector fGameResultsGameVector;
	private short fShowGame;

	private ScheduleDayStatus fStatus;

	private TeamInfoName fVisitTeam;
	private short fVisitScore;
	private PlayerInfoVector fVisitPlayerVector;
	
	private TeamInfoName fHomeTeam;
	private short fHomeScore;
	private PlayerInfoVector fHomePlayerVector;

	private ASFantasyGameResultPnl fGameResultPnl;
	
	/**************************************************************************/
	
	public String getAppletName()
	{
		return("Game Results");
	}

	/**************************************************************************/

	protected ASFantasyRequestor newFantasyRequestor(String hostName,
		int hostPortID,String requestDll,String encodedParticID)
	{
		return(new ASFantasySeasonRequestor(hostName,hostPortID,requestDll,
			encodedParticID));
	}

	/**************************************************************************/

	protected String getGameDateParameter()
	{
		String gameDateStr = getParameter("GameDate");

		if(gameDateStr != null)
			return(gameDateStr);

		return("");
	}

	/**************************************************************************/

	public void open() throws Exception
	{
		// Take out this line if you don't use symantec.itools.net.RelativeURL
		symantec.itools.lang.Context.setDocumentBase(getDocumentBase());

		getGameResults(getGameDateParameter(),0);

		//{{INIT_CONTROLS
		setLayout(null);
		addNotify();
		resize(550,325);
		setBackground(new Color(12632256));
		fShowPnl = new symantec.itools.awt.BorderPanel();
		fShowPnl.setLayout(null);
		fShowPnl.reshape(0,0,550,65);
		fShowPnl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		add(fShowPnl);
		fShowPnl.setPaddingTop(1);
		fShowPnl.setPaddingBottom(1);
		fShowPnl.setPaddingLeft(1);
		fShowPnl.setPaddingRight(1);
		fShowPnl.setIPadTop(4);
		fShowPnl.setIPadBottom(4);
		fShowPnl.setBevelStyle(symantec.itools.awt.BorderPanel.BEVEL_RAISED);

		fShowDayLbl = new jclass.bwt.JCLabel();
		fShowDayLbl.reshape(4,6,80,18);
		fShowDayLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fShowPnl.add(fShowDayLbl);
		fShowDayLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Show Week:");
			fShowDayLbl.setTextList(tempString);
		}
		fShowDayChc = new java.awt.Choice();
		fShowPnl.add(fShowDayChc);
		fShowDayChc.reshape(90,4,55,23);
		fShowDayChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

		fShowGameLbl = new jclass.bwt.JCLabel();
		fShowGameLbl.reshape(150,6,80,18);
		fShowGameLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fShowPnl.add(fShowGameLbl);
		fShowGameLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Show Game:");
			fShowGameLbl.setTextList(tempString);
		}
		fShowGameChc = new java.awt.Choice();
		fShowPnl.add(fShowGameChc);
		fShowGameChc.reshape(236,4,290,23);
		fShowGameChc.setFont(new Font("Helvetica", Font.PLAIN, 12));

		fStatusTagLbl = new jclass.bwt.JCLabel();
		fStatusTagLbl.reshape(4,31,50,18);
		fStatusTagLbl.setFont(new Font("Helvetica", Font.BOLD, 12));
		fShowPnl.add(fStatusTagLbl);
		fStatusTagLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		{
			java.lang.String[] tempString = new java.lang.String[1];
			tempString[0] = new java.lang.String("Status:");
			fStatusTagLbl.setTextList(tempString);
		}

		fStatusLbl = new jclass.bwt.JCLabel();
		fStatusLbl.reshape(60,31,160,18);
		fStatusLbl.setFont(new Font("Helvetica", Font.PLAIN, 12));
		fShowPnl.add(fStatusLbl);
		fStatusLbl.setAlignment(jclass.bwt.JCLabel.MIDDLELEFT);
		//}}


		loadData(true);

		if(fGameLevel == TGameLevel.gml_Standard)
		{
			fShowDayChc.enable(false);
			fShowGameChc.enable(false);
		}
	}

	/**************************************************************************/

	protected void openGameResultPnl()
	{
		closeGameResultPnl();

		loadStatusLbl();

		if((fStatus == ScheduleDayStatus.sdst_InProgress) ||
				(fStatus == ScheduleDayStatus.sdst_Completed))
			fGameResultPnl = new GameResultExistPnl();
		else
			fGameResultPnl = new GameResultNonePnl();
		fGameResultPnl.show(false);
		fGameResultPnl.setLayout(null);
		fGameResultPnl.move(0,65);
		add(fGameResultPnl);
		fGameResultPnl.open();

		fGameResultPnl.loadData(fStatus,fVisitTeam,fVisitScore,
			fVisitPlayerVector,fHomeTeam,fHomeScore,fHomePlayerVector);
		fGameResultPnl.show(true);
	}

	/**************************************************************************/

	protected void closeGameResultPnl()
	{
		if(fGameResultPnl != null)
		{
			fGameResultPnl.show(false);
			fGameResultPnl.remove(this);
			fGameResultPnl = null;
		}
	}

	/**************************************************************************/

	public boolean action(Event evt,Object arg)
	{
		if(evt.id == Event.ACTION_EVENT)
		{
			if(evt.target == fShowDayChc)
			{
				showOtherGame(false);
			}
			else if(evt.target == fShowGameChc)
			{
				showOtherGame(true);
			}
			else
				return false;
		}
		else
			return false;

		return true;
	}

	/**************************************************************************/

	protected void getGameResults(String gameDate,int homeTeamID) throws IOException
	{
		GameResultsResp pResponse =
			((ASFantasySeasonRequestor)fAppRequestor).gameResultsRequest(
				gameDate,homeTeamID);
		GameResultsPlayerByPointsCmpr comparer;

		if(pResponse == null)
		{
			String msg = "Unable to access your game results.";

			MsgWinOKDialog.Msg(this,0 /*TAGMsgWin.MWI_STOP | TAGMsgWin.MWB_OK*/,
				msg + "  Please try again later.");
			throw new IOException(msg);
		}

		fGameLevel = pResponse.fGameLevel;

		fGameResultsDayVector = pResponse.fGameResultsDayVector;
		fShowDay = pResponse.fShowDay;

		fGameResultsGameVector = pResponse.fGameResultsGameVector;
		fShowGame = pResponse.fShowGame;

		comparer = new GameResultsPlayerByPointsCmpr();
		
		fStatus = pResponse.fStatus;

		fVisitTeam = pResponse.fVisitTeam;
		fVisitScore = pResponse.fVisitScore;
		fVisitPlayerVector = pResponse.fVisitPlayerVector;
		TAGVectorSorter.quickSort(fVisitPlayerVector,comparer);
		
		fHomeTeam = pResponse.fHomeTeam;
		fHomeScore = pResponse.fHomeScore;
		fHomePlayerVector = pResponse.fHomePlayerVector;
		TAGVectorSorter.quickSort(fHomePlayerVector,comparer);
	}

	/**************************************************************************/

	protected void showOtherGame(boolean gameWasChanged)
	{
		int dayPos = fShowDayChc.getSelectedIndex();
		int gamePos = fShowGameChc.getSelectedIndex();
		boolean doRequest = false;

		if((dayPos >= 0) && (dayPos < fGameResultsDayVector.size()))
		{
			if(dayPos != fShowDay)
				doRequest = true;
			else if(gameWasChanged && (gamePos != fShowGame))
			{
				if((gamePos >= 0) && (gamePos < fGameResultsGameVector.size()))
					doRequest = true;
			}

			if(doRequest)
			{
				String gameDate =
					((GameResultsDay)fGameResultsDayVector.elementAt(dayPos)).fGameDate;
				int homeTeamID = 0;

				if(gameWasChanged)
					homeTeamID = ((GameResultsGame)fGameResultsGameVector.elementAt(gamePos)).fHomeTeamID;
			
				enable(false);
				try
				{
					closeGameResultPnl();
					getGameResults(gameDate,homeTeamID);
					loadData(false);
				}
				catch(Exception e)
				{
				}
				enable(true);
			}
		}
	}
	
	/**************************************************************************/

	protected void loadData(boolean firstTime)
	{
		if(firstTime)
			loadShowDays();

		loadShowGames();

		openGameResultPnl();

/*
		fVisitTeamNameLbl.setText(fVisitTeam.buildName());
		fVisitTeamScoreLbl.setText(Integer.toString(fVisitScore));
		loadPlayerList(fVisitPlayersMCLst,fVisitPlayerVector);

		fHomeTeamNameLbl.setText(fHomeTeam.buildName());
		fHomeTeamScoreLbl.setText(Integer.toString(fHomeScore));
		loadPlayerList(fHomePlayersMCLst,fHomePlayerVector);

		if(fVisitScore > fHomeScore)
		{
			fVisitTeamNameLbl.setForeground(Color.yellow);
			fVisitTeamScoreLbl.setForeground(Color.yellow);
		}
		else if(fHomeScore > fVisitScore)
		{
			fHomeTeamNameLbl.setForeground(Color.yellow);
			fHomeTeamScoreLbl.setForeground(Color.yellow);
		}
*/
		//else tie
	}
	
	/**************************************************************************/

	protected void loadShowDays()
	{
		GameResultsDay gameResultsDay;
		int i,numItems;
		int pos;
		
		// Load fShowLinupChc.
		numItems = fGameResultsDayVector.size();
		for(i = 0; i < numItems; i++)
		{
			gameResultsDay = (GameResultsDay)fGameResultsDayVector.elementAt(i);
			fShowDayChc.addItem(gameResultsDay.fDescrip);
		}

		// Select day to be shown
		fShowDayChc.select(fShowDay);
	}

	/**************************************************************************/

	protected void loadShowGames()
	{
		GameResultsGame gameResultsGame;
		int i,numItems;
		int pos;

		fShowPnl.remove(fShowGameChc);
		fShowGameChc = null;

		fShowGameChc = new java.awt.Choice();
		fShowPnl.add(fShowGameChc);
		fShowGameChc.reshape(236,4,290,23);
		fShowGameChc.setFont(new Font("Helvetica", Font.PLAIN, 12));
		
		if((fShowGame == -1) || (fGameResultsGameVector.size() == 0))
		{
			fShowGameChc.addItem("No Game Results");
			fShowGameChc.select(0);
			fShowGameChc.enable(false);
		}
		else
		{
			// Load fShowLinupChc.
			numItems = fGameResultsGameVector.size();
			for(i = 0; i < numItems; i++)
			{
				gameResultsGame = (GameResultsGame)fGameResultsGameVector.elementAt(i);
				fShowGameChc.addItem(gameResultsGame.fDescrip);
			}

			// Select game to be shown
			fShowGameChc.select(fShowGame);
			fShowGameChc.enable(true);
		}
	}

	/**************************************************************************/

	protected void loadStatusLbl()
	{
		String[] tempString = new String[1];
		Color color = Color.black;

		if(fStatus == ScheduleDayStatus.sdst_Missed)
			tempString[0] = new String("Missed");
		else if(fStatus == ScheduleDayStatus.sdst_NotStarted)
			tempString[0] = new String("Not Started");
		else if(fStatus == ScheduleDayStatus.sdst_InProgress)
		{
			color = Color.red;
			tempString[0] = new String("In Progress");
		}
		else if(fStatus == ScheduleDayStatus.sdst_Completed)
			tempString[0] = new String("Completed");

		fStatusLbl.setForeground(color);
		fStatusLbl.setTextList(tempString);
	}

}

/******************************************************************************/
/******************************************************************************/

