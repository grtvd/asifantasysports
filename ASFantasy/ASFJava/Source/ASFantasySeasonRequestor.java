/* ASFantasySeasonRequestor.java */

/******************************************************************************/
/******************************************************************************/

//import java.io.*;
import java.util.*;

/******************************************************************************/
/******************************************************************************/

class ASFantasySeasonRequestor extends ASFantasyRequestor
{
	/**************************************************************************/

	public ASFantasySeasonRequestor(String hostName,int hostPortID,
		String requestDll,String encodedParticID)
	{
		super(hostName,hostPortID,requestDll,encodedParticID);
	}

	/**************************************************************************/
	
	public ScheduleResp scheduleRequest()
	{
		ScheduleRqst requestObj = new ScheduleRqst(fEncodedParticID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof ScheduleResp)
			{
				return((ScheduleResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public LineupQueryResp lineupQueryRequest(int showTeamID)
	{
		LineupQueryRqst requestObj = new LineupQueryRqst(fEncodedParticID,
			showTeamID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof LineupQueryResp)
			{
				return((LineupQueryResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public LineupUpdateResp lineupUpdateRequest(PlayerIDArray playerIDArray)
	{
		LineupUpdateRqst requestObj = new LineupUpdateRqst(fEncodedParticID,
			playerIDArray);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof LineupUpdateResp)
			{
				return((LineupUpdateResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public GameResultsResp gameResultsRequest(String gameDate,int homeTeamID)
	{
		GameResultsRqst requestObj = new GameResultsRqst(fEncodedParticID,
			gameDate,homeTeamID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof GameResultsResp)
			{
				return((GameResultsResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public StandingsResp standingsRequest()
	{
		StandingsRqst requestObj = new StandingsRqst(fEncodedParticID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof StandingsResp)
			{
				return((StandingsResp)responseObj);
			}
		}

		return(null);
	}
	
	/**************************************************************************/
	
	public FreeAgentQueryResp freeAgentQueryRequest()
	{
		FreeAgentQueryRqst requestObj = new FreeAgentQueryRqst(fEncodedParticID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof FreeAgentQueryResp)
			{
				return((FreeAgentQueryResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public FreeAgentUpdateResp freeAgentUpdateRequest(int claimPlayerID,
		int releasePlayerID)
	{
		FreeAgentUpdateRqst requestObj = new FreeAgentUpdateRqst(fEncodedParticID,
			claimPlayerID,releasePlayerID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof FreeAgentUpdateResp)
			{
				return((FreeAgentUpdateResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public TradeProposeQueryResp tradeProposeQueryRequest(int tradeID)
	{
		TradeProposeQueryRqst requestObj = new TradeProposeQueryRqst(
			fEncodedParticID,tradeID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof TradeProposeQueryResp)
			{
				return((TradeProposeQueryResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public TradeProposeTeamResp tradeProposeTeamRequest(int proposeToTeamID)
	{
		TradeProposeTeamRqst requestObj = new TradeProposeTeamRqst(fEncodedParticID,
			proposeToTeamID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof TradeProposeTeamResp)
			{
				return((TradeProposeTeamResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public TradeProposeUpdateResp tradeProposeUpdateRequest(int tradeID,
		int proposeToTeamID,PlayerIDVector getPlayerIDVector,
		PlayerIDVector givePlayerIDVector,PlayerIDVector releasePlayerIDVector)
	{
		TradeProposeUpdateRqst requestObj = new TradeProposeUpdateRqst(
			fEncodedParticID,tradeID,proposeToTeamID,getPlayerIDVector,
			givePlayerIDVector,releasePlayerIDVector);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof TradeProposeUpdateResp)
			{
				return((TradeProposeUpdateResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public TradeReceiveUpdateResp tradeReceiveUpdateRequest(int tradeID,
		boolean accept,PlayerIDVector releasePlayerIDVector)
	{
		TradeReceiveUpdateRqst requestObj = new TradeReceiveUpdateRqst(
			fEncodedParticID,tradeID,accept,releasePlayerIDVector);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof TradeReceiveUpdateResp)
			{
				return((TradeReceiveUpdateResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public TradeProtestUpdateResp tradeProtestUpdateRequest(int tradeID)
	{
		TradeProtestUpdateRqst requestObj = new TradeProtestUpdateRqst(
			fEncodedParticID,tradeID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof TradeProtestUpdateResp)
			{
				return((TradeProtestUpdateResp)responseObj);
			}
		}

		return(null);
	}

	/**************************************************************************/
	
	public PlayoffResp playoffRequest()
	{
		PlayoffRqst requestObj = new PlayoffRqst(fEncodedParticID);

		Object responseObj = request(requestObj);

		if(responseObj instanceof Streamable)
		{
			if(responseObj instanceof PlayoffResp)
			{
				return((PlayoffResp)responseObj);
			}
		}

		return(null);
	}

}

/******************************************************************************/
/******************************************************************************/
